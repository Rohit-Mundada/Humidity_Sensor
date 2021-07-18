#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <Wire.h>

#define GREEN ILI9341_GREEN
#define BLACK ILI9341_BLACK
#define WHITE ILI9341_WHITE
#define RED ILI9341_RED
#define YELLOW ILI9341_YELLOW
#define CYAN ILI9341_CYAN
#define BAR_WIDTH 150.0
#define VERTICAL_START 10
#define HORIZONTAL_START 10
#define SPACING 60
#define BUTTON1 6
#define BUTTON2 7
#define HOUR_AND_DAY_X_DISP 30
#define MINUTE_AND_MONTH_X_DISP 47
#define YEAR_X_DISP 78

Adafruit_ILI9341 tft = Adafruit_ILI9341(8, 9, 11, 13, 10, 12);

float analogValue = 0, ppm = 0, current = 0, percentHumidity = 0;

char Time[] = "  :  :  ";
char Date[] = "  /  /20  ";

byte i, second, minute, hour, date, month, year;

void printHumidity(float ppm, int fontSize)
{
    tft.setCursor(HORIZONTAL_START, VERTICAL_START);
    tft.setTextColor(GREEN, BLACK);
    tft.setTextSize(fontSize);
    tft.print("HUMIDITY: ");
    tft.setTextColor(WHITE, BLACK);
    tft.print(ppm);
    tft.println(" ppm");
}

void printBar(float n, int fontSize)
{
    float width = (n * (BAR_WIDTH - 2)) / 100;
    tft.drawRect(HORIZONTAL_START, VERTICAL_START + SPACING / 2, BAR_WIDTH, 10, WHITE);
    tft.fillRect(HORIZONTAL_START + 1, VERTICAL_START + SPACING / 2 + 1, width, 8, GREEN);
    tft.fillRect(HORIZONTAL_START + 1 + width, VERTICAL_START + SPACING / 2 + 1, BAR_WIDTH - width - 2, 8, BLACK);
    tft.setTextSize(fontSize);
    tft.setCursor(HORIZONTAL_START + BAR_WIDTH + 10, VERTICAL_START + SPACING / 2);
    tft.print(n);
    tft.setCursor(HORIZONTAL_START + BAR_WIDTH + 50, VERTICAL_START + SPACING / 2);
    tft.print("%");
}

void printCurrent(float current, int fontSize)
{
    tft.setTextSize(fontSize);
    tft.setTextColor(GREEN, BLACK);
    tft.setCursor(HORIZONTAL_START, VERTICAL_START + 1.5 * SPACING);
    tft.print("CURRENT: ");
    tft.setTextColor(RED, BLACK);
    tft.print(current);
    tft.setCursor(HORIZONTAL_START + 180, VERTICAL_START + 1.5 * SPACING);
    tft.print("uA");
}

void printDateAndTime(int fontSize)
{
    if (!digitalRead(BUTTON2))
    { // If button (pin #7) is pressed
        i = 0;
        hour = edit(HORIZONTAL_START + HOUR_AND_DAY_X_DISP * fontSize, VERTICAL_START + 2.5 * SPACING, hour);
        minute = edit(HORIZONTAL_START + MINUTE_AND_MONTH_X_DISP * fontSize, VERTICAL_START + 2.5 * SPACING, minute);
        date = edit(HORIZONTAL_START + HOUR_AND_DAY_X_DISP * fontSize, VERTICAL_START + 3.5 * SPACING, date);
        month = edit(HORIZONTAL_START + MINUTE_AND_MONTH_X_DISP * fontSize, VERTICAL_START + 3.5 * SPACING, month);
        year = edit(HORIZONTAL_START + YEAR_X_DISP * fontSize, VERTICAL_START + 3.5 * SPACING, year);
        // Convert decimal to BCD
        minute = ((minute / 10) << 4) + (minute % 10);
        hour = ((hour / 10) << 4) + (hour % 10);
        date = ((date / 10) << 4) + (date % 10);
        month = ((month / 10) << 4) + (month % 10);
        year = ((year / 10) << 4) + (year % 10);
        // End conversion
        // Write data to DS3231 RTC
        Wire.beginTransmission(0x68); // Start I2C protocol with DS3231 address
        Wire.write(0);                // Send register address
        Wire.write(0);                // Reset sesonds and start oscillator
        Wire.write(minute);           // Write minute
        Wire.write(hour);             // Write hour
        Wire.write(1);                // Write day (not used)
        Wire.write(date);             // Write date
        Wire.write(month);            // Write month
        Wire.write(year);             // Write year
        Wire.endTransmission();       // Stop transmission and release the I2C bus
        delay(200);                   // Wait 200ms
    }
    Wire.beginTransmission(0x68); // Start I2C protocol with DS3231 address
    Wire.write(0);                // Send register address
    Wire.endTransmission(false);  // I2C restart
    Wire.requestFrom(0x68, 7);    // Request 7 bytes from DS3231 and release I2C bus at end of reading
    second = Wire.read();         // Read seconds from register 0
    minute = Wire.read();         // Read minuts from register 1
    hour = Wire.read();           // Read hour from register 2
    Wire.read();                  // Read day from register 3 (not used)
    date = Wire.read();           // Read date from register 4
    month = Wire.read();          // Read month from register 5
    year = Wire.read();           // Read year from register 6
    tft.setTextSize(fontSize);
    DS3231_display(); // Display time & calendar
}

void DS3231_display()
{
    // Convert BCD to decimal
    second = (second >> 4) * 10 + (second & 0x0F);
    minute = (minute >> 4) * 10 + (minute & 0x0F);
    hour = (hour >> 4) * 10 + (hour & 0x0F);
    date = (date >> 4) * 10 + (date & 0x0F);
    month = (month >> 4) * 10 + (month & 0x0F);
    year = (year >> 4) * 10 + (year & 0x0F);
    // End conversion
    Time[7] = second % 10 + 48;
    Time[6] = second / 10 + 48;
    Time[4] = minute % 10 + 48;
    Time[3] = minute / 10 + 48;
    Time[1] = hour % 10 + 48;
    Time[0] = hour / 10 + 48;
    Date[9] = year % 10 + 48;
    Date[8] = year / 10 + 48;
    Date[4] = month % 10 + 48;
    Date[3] = month / 10 + 48;
    Date[1] = date % 10 + 48;
    Date[0] = date / 10 + 48;
    tft.setCursor(HORIZONTAL_START, VERTICAL_START + 2.5 * SPACING);
    tft.setTextColor(GREEN, BLACK);
    tft.print("TIME:");
    tft.setTextColor(YELLOW, BLACK);
    tft.print(Time);
    tft.setCursor(HORIZONTAL_START, VERTICAL_START + 3.5 * SPACING);
    tft.setTextColor(GREEN, BLACK);
    tft.print("DATE:");
    tft.setTextColor(YELLOW, BLACK);
    tft.print(Date);
}

void blink_parameter()
{
    byte j = 0;
    while (j < 10 && digitalRead(BUTTON1) && digitalRead(BUTTON2))
    {
        j++;
        delay(25);
    }
}

byte edit(byte x, byte y, byte parameter)
{
    char text[3];
    while (!digitalRead(BUTTON1))
        ; // Wait until button (pin #6) released
    while (true)
    {
        while (!digitalRead(BUTTON2))
        { // If button (pin #7) is pressed
            parameter++;
            if (i == 0 && parameter > 23) // If hours > 23 ==> hours = 0
                parameter = 0;
            if (i == 1 && parameter > 59) // If minutes > 59 ==> minutes = 0
                parameter = 0;
            if (i == 2 && parameter > 31) // If date > 31 ==> date = 1
                parameter = 1;
            if (i == 3 && parameter > 12) // If month > 12 ==> month = 1
                parameter = 1;
            if (i == 4 && parameter > 99) // If year > 99 ==> year = 0
                parameter = 0;
            sprintf(text, "%02u", parameter);
            tft.setTextColor(YELLOW, BLACK);
            tft.setCursor(x, y);
            tft.print(text);
            delay(100); // Wait 200ms
        }
        tft.setCursor(x, y);
        tft.print("  "); // Display two spaces
        blink_parameter();
        sprintf(text, "%02u", parameter);
        tft.setTextColor(YELLOW, BLACK);
        tft.setCursor(x, y);
        tft.print(text);
        blink_parameter();
        if (!digitalRead(BUTTON1))
        {                     // If button (pin #6) is pressed
            i++;              // Increament 'i' for the next parameter
            return parameter; // Return parameter value and exit
        }
    }
}

void printText(int fontSize)
{
    tft.setTextColor(CYAN, BLACK);
    tft.setCursor(HORIZONTAL_START, VERTICAL_START + 5 * SPACING);
    tft.setTextSize(fontSize);
    tft.print("PS1 PROJECT BY ROHIT MUNDADA");
}

void setup()
{
    pinMode(A0, INPUT);
    pinMode(BUTTON1, INPUT_PULLUP);
    pinMode(BUTTON2, INPUT_PULLUP);
    tft.begin();
    tft.fillScreen(BLACK);
    Wire.begin();
}

void loop(void)
{
    analogValue = analogRead(A0);

    ppm = (5.6 / 1023) * analogValue;
    percentHumidity = (ppm / 5.6) * 100;
    current = (105.0 / 1023) * analogValue;

    printHumidity(ppm, 2);
    printBar(percentHumidity, 1);
    printCurrent(current, 2);
    printDateAndTime(2);
    printText(1);

    delay(20);
}
