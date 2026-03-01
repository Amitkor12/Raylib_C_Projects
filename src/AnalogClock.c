#include "AnalogClock.h"

void AnalogClock_Init(s_AnalogClockData *clock,int size, Vector2 position)
{
    clock->size = size;
    clock->position = position;
    clock->hour = 0;
    clock->minute =0;
    clock->second = 0;
    clock->day = 1;
    clock->month = 1;
    clock->year = 2026;
}

void Draw(s_AnalogClockData *analogClock)
{
    DrawFace(analogClock);
    DrawHourMarks(analogClock);
    DrawMinuteHand(analogClock,analogClock->minute);
    DrawHourHand(analogClock,analogClock->hour, analogClock->minute);
    DrawSecondHand(analogClock,analogClock->second);
    DrawText("Amit's Clock", analogClock->position.x - 55, analogClock->position.y + 100, 20, BLACK);
    DrawDate(analogClock);
    // DrawRectangle(analogClock->position.x-55,analogClock->position.y+100,120,50,LIGHTGRAY);
    DrawCircleV(analogClock->position, 10, GRAY);
    
    // DrawRectangle(int posX, int posY, int width, int height, Color color); 
}

void DrawFace(s_AnalogClockData *analogClock)
{
    DrawCircleV(analogClock->position, analogClock->size, GRAY);
    DrawCircleV(analogClock->position, (analogClock->size - 30), LIGHTGRAY);
    DrawCircleV(analogClock->position, (analogClock->size - 40), RAYWHITE);
}

void DrawHourMarks(s_AnalogClockData *analogClock)
{
    float rectWidth = 10;
    float rectHeight = analogClock->size;

    Rectangle rect = {analogClock->position.x, analogClock->position.y, rectWidth, rectHeight};
    for(int i =0; i<12; i++)
    {
        DrawRectanglePro(rect, (Vector2){rectWidth/2, rectHeight}, i*30, BLACK);
    }
    DrawCircleV(analogClock->position, (analogClock->size - 50), RAYWHITE);
}

void DrawHand(s_AnalogClockData *analogClock, float handWidth, float handLength, int angle, Color color, int offset)
{
    Rectangle handRect = {analogClock->position.x, analogClock->position.y, handWidth, handLength};
    DrawRectanglePro(handRect, (Vector2){handWidth/2, (handLength - offset)}, angle, color);
}

void DrawMinuteHand(s_AnalogClockData *analogClock, int minute)
{
    float handWidth = 10;
    float handLength = analogClock->size * 0.7;
    int angle = minute * 6;

    DrawHand(analogClock,handWidth, handLength, angle, GREEN, 0);
}

void DrawHourHand(s_AnalogClockData *analogClock,int hour, int minute)
{
    float handWidth = 15;
    float handLength = analogClock->size * 0.6;
    int angle = 30 * hour + (minute / 60.0) * 30;
    DrawHand(analogClock,handWidth, handLength, angle, GRAY, 0);
}

void DrawSecondHand(s_AnalogClockData *analogClock,int second)
{
    float handWidth = 5;
    float handLength = analogClock->size * 0.80;
    int angle = second * 6;
    DrawHand(analogClock,handWidth, handLength, angle, RED, 0);
}

void DrawDate(s_AnalogClockData *analogClock)
{
    // Date box dimensions
    int boxX = analogClock->position.x - 55;
    int boxY = analogClock->position.y + 100;
    int boxWidth = 120;
    int boxHeight = 45;
    
    // Draw light gray background rectangle
    DrawRectangle(boxX, boxY, boxWidth, boxHeight, LIGHTGRAY);
    
    // Draw thin black border
    DrawRectangleLines(boxX, boxY, boxWidth, boxHeight, BLACK);
    
    // Format date string: DD/MM/YYYY
    char dateStr[20];
    sprintf(dateStr, "%02d/%02d/%04d", analogClock->day, analogClock->month, analogClock->year);
    
    // Draw date text centered in the box
    int textWidth = MeasureText(dateStr, 16);
    DrawText(dateStr, boxX + (boxWidth - textWidth) / 2, boxY + 12, 16, BLACK);
}

void Update(s_AnalogClockData *analogClock)
{
    time_t t = time(0);
    struct tm *now = localtime(&t);

    analogClock->hour = now->tm_hour % 12;
    analogClock->minute = now -> tm_min;
    analogClock->second = now -> tm_sec;
    analogClock->day = now->tm_mday;
    analogClock->month = now->tm_mon + 1;
    analogClock->year = now->tm_year + 1900;
}