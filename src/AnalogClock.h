#ifndef ANALOGCLOCK_H
#define ANALOGCLOCK_H

#include <raylib.h>
#include <time.h>

typedef struct AnalogClockData {
    int size;
    int minute;
    int hour;
    int second;
    int day;
    int month;
    int year;
    Vector2 position;
}s_AnalogClockData;

void AnalogClock_Init(s_AnalogClockData*, int, Vector2);
void Draw(s_AnalogClockData*);
void Update(s_AnalogClockData *clock);
void DrawFace(s_AnalogClockData *clock);
void DrawHourMarks(s_AnalogClockData *clock);
void DrawMinuteHand(s_AnalogClockData *clock,int);
void DrawHand(s_AnalogClockData *Clock, float handWidth, float handLength, int angle, Color color, int offset);
void DrawHourHand(s_AnalogClockData *clock,int,int);
void DrawSecondHand(s_AnalogClockData *clock,int);
void DrawDate(s_AnalogClockData *clock);

#endif //ANALOGCLOCK_H