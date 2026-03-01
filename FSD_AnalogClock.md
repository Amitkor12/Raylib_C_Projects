# Functional Specification Document (FSD)
## Raylib Analog Clock Application

---

## 1. Overview

**Project Name:** Raylib Analog Clock  
**Programming Language:** C  
**Framework:** Raylib (Graphics Library)  
**Platform:** Linux  
**Version:** 1.0  

### Purpose
A real-time analog clock application that displays the current system time with animated hour, minute, and second hands. The clock features visual elements including clock face, hour markers, and color-coded hands.

---

## 2. System Architecture

### 2.1 Technology Stack
- **Language:** C (C99 standard)
- **Graphics Library:** Raylib
- **Build System:** CMake
- **Compiler:** GCC (C Compiler)
- **Target OS:** Linux

### 2.2 Dependencies
- **raylib** - Graphics and window management library
- **libc** - C standard library (for time functions)
- **X11** - Linux display server
- **OpenGL** - Graphics rendering
- **POSIX pthread** - Threading support

### 2.3 Code Structure
```
main.c                  - Application entry point
src/AnalogClock.h       - Header file with data structures and function declarations
src/AnalogClock.c       - Implementation of analog clock functionality
```

---

## 3. Data Structures

### 3.1 AnalogClockData Structure
```c
typedef struct AnalogClockData {
    int size;           // Clock radius in pixels
    int minute;         // Current minute (0-59)
    int hour;          // Current hour in 12-hour format (0-11)
    int second;        // Current second (0-59)
    int day;            // current Day of the month (1-31)
    int month;          // current month of the year (1 - 12)
    int year;           // current year (year - 1900)
    Vector2 position;  // Center position of clock on screen
} s_AnalogClockData;
```

**Fields:**
- `size`: Diameter/radius of the clock face
- `minute`: Extracted from system time, range 0-59
- `hour`: Extracted from system time in 12-hour format, range 0-11
- `second`: Extracted from system time, range 0-59
- `position`: X and Y coordinates defining clock center location

---

## 4. Functional Requirements

### 4.1 Window Management
**Requirement:** The application shall create and manage a graphical window.
- **Window Width:** 600 pixels
- **Window Height:** 600 pixels
- **Window Title:** "Raylib C Example"
- **Target FPS:** 60 frames per second

### 4.2 Clock Initialization
**Requirement:** Initialize the analog clock with specified parameters.
- **Function:** `AnalogClock_Init()`
- **Parameters:** Pointer to clock data, size (250 pixels), and position (300, 300)
- **Initialization Values:**
  - Hour: 0
  - Minute: 0
  - Second: 0
  - Day : 1
  - Month: 1
  - Year: 2026

### 4.3 Time Update
**Requirement:** Update clock data with current system time every frame.
- **Function:** `Update()`
- **Behavior:**
  - Reads current system time using `time()` and `localtime()`
  - Extracts hour, minute, and second values
  - Converts hour to 12-hour format (modulo 12)

### 4.4 Clock Rendering
**Requirement:** Render the analog clock with all visual components.
- **Function:** `Draw()`
- **Components rendered in order:**
  1. Clock face (background)
  2. Hour markers (12 positions)
  3. Minute hand
  4. Hour hand
  5. Second hand
  6. Clock label text ("Amit's Clock")
  7. Date display box (DD/MM/YYYY format)
  8. Center circle (pivot point)

### 4.5 Clock Face
**Requirement:** Draw the clock face background.
- **Function:** `DrawFace()`
- **Visual Elements:**
  - Outer circle: Gray (GRAY), radius = clock size
  - Middle circle: Light Gray (LIGHTGRAY), radius = size - 30
  - Inner circle: Ray White (RAYWHITE), radius = size - 40
  - Creates a 3D-like appearance with concentric circles

### 4.6 Hour Markers
**Requirement:** Display 12 hour markers around the clock face.
- **Function:** `DrawHourMarks()`
- **Visual Properties:**
  - 12 rectangular markers positioned at 30-degree intervals
  - Marker dimensions: 10 pixels wide, size pixels tall
  - Color: Black (BLACK)
  - Inner boundary circle: Ray White, radius = size - 50

### 4.7 Minute Hand
**Requirement:** Display rotating minute hand indicating current minute.
- **Function:** `DrawMinuteHand()`
- **Properties:**
  - Width: 10 pixels
  - Length: 70% of clock size
  - Color: Green (GREEN)
  - Rotation: minute × 6 degrees (360° ÷ 60 minutes)
  - Updates every minute

### 4.8 Hour Hand
**Requirement:** Display rotating hour hand indicating current hour.
- **Function:** `DrawHourHand()`
- **Properties:**
  - Width: 15 pixels
  - Length: 60% of clock size
  - Color: Gray (GRAY)
  - Rotation: (30 × hour) + (minute × 0.5) degrees
  - Smooth rotation accounting for minute progression

### 4.9 Second Hand
**Requirement:** Display rotating second hand indicating current second.
- **Function:** `DrawSecondHand()`
- **Properties:**
  - Width: 5 pixels
  - Length: 105% of clock size (extends beyond clock face)
  - Color: Red (RED)
  - Rotation: second × 6 degrees (360° ÷ 60 seconds)
  - Offset: 55 pixels (center pivot offset)

### 4.10 Generic Hand Drawing
**Requirement:** Provide generic function to draw clock hands with custom parameters.
- **Function:** `DrawHand()`
- **Parameters:**
  - Clock data pointer
  - Hand width (pixels)
  - Hand length (pixels)
  - Rotation angle (degrees)
  - Hand color
  - Offset from pivot point
- **Used by:** Minute, hour, and second hand functions

### 4.11 Date Display
**Requirement:** Display the current date in a rectangular box with black border.
- **Function:** `DrawDate()`
- **Visual Properties:**
  - Background: Light Gray (LIGHTGRAY)
  - Border: Thin black border (BLACK)
  - Dimensions: 120 pixels wide × 45 pixels tall
  - Position: Below clock label text
  - Date Format: DD/MM/YYYY
  - Text Color: Black (BLACK)
  - Font Size: 16 pixels
  - Text is center-aligned within the box

---

## 5. Functional Flow

```
[Application Start]
    ↓
[Initialize Raylib Window]
    ├─ Width: 600px, Height: 600px
    └─ Title: "Raylib C Example"
    ↓
[Create Clock Data Structure]
    ↓
[Initialize Clock]
    ├─ Size: 250 pixels
    ├─ Position: (300, 300)
    └─ Time values: 0, 0, 0, 1, 1, 2026
    ↓
[Enter Main Rendering Loop]
    ├─ [Update Phase]
    │   ├─ Read system time
    │   ├─ Extract hour, minute, second
    │   ├─ Extract day, month, year
    │   └─ Store in clock structure
    ├─ [Render Phase]
    │   ├─ Clear background (Light Gray)
    │   ├─ Draw clock face (3 concentric circles)
    │   ├─ Draw 12 hour markers
    │   ├─ Draw minute hand (green, 70% length)
    │   ├─ Draw hour hand (gray, 60% length)
    │   ├─ Draw second hand (red, 105% length)
    │   ├─ Draw "Amit's Clock" label text
    │   ├─ Draw date box (DD/MM/YYYY format)
    │   └─ Draw center pivot circle
    └─ [Check Window Close]
        ├─ YES → Exit loop
        └─ NO → Continue
    ↓
[Close Window]
    ↓
[Terminate Application]
```

---

## 6. Detailed Function Specifications

### 6.1 AnalogClock_Init()
**Purpose:** Initialize analog clock data structure

**Signature:**
```c
void AnalogClock_Init(s_AnalogClockData *clock, int size, Vector2 position)
```

**Parameters:**
- `clock`: Pointer to clock data structure
- `size`: Clock radius in pixels (typically 250)
- `position`: Center position as Vector2 (x, y)

**Operations:**
1. Set clock size
2. Set clock position
3. Initialize hour to 0
4. Initialize minute to 0
5. Initialize second to 0

**Return:** void

---

### 6.2 Update()
**Purpose:** Update clock with current system time

**Signature:**
```c
void Update(s_AnalogClockData *analogClock)
```

**Parameters:**
- `analogClock`: Pointer to clock data structure

**Operations:**
1. Get current system time using `time(0)`
2. Convert to local time using `localtime()`
3. Extract hour and apply modulo 12 for 12-hour format
4. Extract minute
5. Extract second

**Return:** void

**System Call Dependencies:**
- `time()` - Get current time
- `localtime()` - Convert to local time structure

---

### 6.3 Draw()
**Purpose:** Main rendering function for all clock components

**Signature:**
```c
void Draw(s_AnalogClockData *analogClock)
```

**Parameters:**
- `analogClock`: Pointer to clock data structure

**Rendering Order:**
1. DrawFace() - Clock background circles
2. DrawHourMarks() - 12 hour position markers
3. DrawMinuteHand() - Minute indicator
4. DrawHourHand() - Hour indicator
5. DrawSecondHand() - Second indicator
6. DrawText() - "Amit's Clock" label text
7. DrawDate() - Date display box (DD/MM/YYYY)
8. DrawCircleV() - Center pivot point (10px radius, gray)

**Return:** void

---

### 6.4 DrawFace()
**Purpose:** Render the clock face background

**Signature:**
```c
void DrawFace(s_AnalogClockData *analogClock)
```

**Circles Drawn:**
1. Outer: Radius = size, Color = GRAY
2. Middle: Radius = size - 30, Color = LIGHTGRAY
3. Inner: Radius = size - 40, Color = RAYWHITE

**Return:** void

---

### 6.5 DrawHourMarks()
**Purpose:** Draw 12 hour position markers

**Signature:**
```c
void DrawHourMarks(s_AnalogClockData *analogClock)
```

**Specifications:**
- Rectangle width: 10 pixels
- Rectangle height: Clock size
- Rotation points: 12 positions (0°, 30°, 60°, ..., 330°)
- Color: BLACK
- Boundary circle: Radius = size - 50, Color = RAYWHITE

**Return:** void

---

### 6.6 DrawHand()
**Purpose:** Generic function to draw any clock hand

**Signature:**
```c
void DrawHand(s_AnalogClockData *analogClock, float handWidth, 
              float handLength, int angle, Color color, int offset)
```

**Parameters:**
- `analogClock`: Clock data
- `handWidth`: Width of hand rectangle
- `handLength`: Length of hand rectangle
- `angle`: Rotation angle in degrees
- `color`: Color of hand
- `offset`: Vertical offset for pivot point

**Operations:**
1. Create rectangle at clock position
2. Draw rectangle with rotation around offset point

**Return:** void

---

### 6.7 DrawMinuteHand()
**Purpose:** Render the minute hand

**Signature:**
```c
void DrawMinuteHand(s_AnalogClockData *analogClock, int minute)
```

**Properties:**
- Width: 10 pixels
- Length: 70% of clock size
- Angle: minute × 6 degrees
- Color: GREEN
- Uses DrawHand() with offset 0

**Return:** void

---

### 6.8 DrawHourHand()
**Purpose:** Render the hour hand with smooth minute adjustment

**Signature:**
```c
void DrawHourHand(s_AnalogClockData *analogClock, int hour, int minute)
```

**Properties:**
- Width: 15 pixels
- Length: 60% of clock size
- Angle: (30 × hour) + (minute ÷ 60.0 × 30) degrees
- Color: GRAY
- Uses DrawHand() with offset 0

**Smooth Rotation:**
- Moves continuously as minutes progress
- Completes 30° rotation per hour

**Return:** void

---

### 6.9 DrawSecondHand()
**Purpose:** Render the second hand

**Signature:**
```c
void DrawSecondHand(s_AnalogClockData *analogClock, int second)
```

**Properties:**
- Width: 5 pixels
- Length: 80% of clock size
- Angle: second × 6 degrees
- Color: RED
- Offset: 0 pixels from center
- Uses DrawHand()

**Return:** void

---

### 6.11 DrawDate()
**Purpose:** Render the date display box with current date

**Signature:**
```c
void DrawDate(s_AnalogClockData *analogClock)
```

**Parameters:**
- `analogClock`: Pointer to clock data structure

**Operations:**
1. Calculate box position (120×45 pixels below clock label)
2. Draw light gray background rectangle
3. Draw thin black border
4. Format date string as DD/MM/YYYY using sprintf
5. Measure text width for centering
6. Draw date text centered in the box (font size 16)

**Visual Properties:**
- Box dimensions: 120px wide × 45px tall
- Background: Light Gray (LIGHTGRAY)
- Border: Black (BLACK) - 1 pixel
- Text color: Black (BLACK)
- Text font size: 16 pixels
- Position: X = center.x - 55, Y = center.y + 100

**Return:** void

---

### 6.12 main()
**Purpose:** Application entry point

**Signature:**
```c
int main(void)
```

**Operations:**
1. Define window dimensions (600×600)
2. Initialize Raylib window
3. Set target FPS to 60
4. Create and initialize clock structure with:
   - Size: 250 pixels
   - Position: (300, 300)
   - Date initialized to: 1/1/2026
5. Main loop:
   - Update clock with current system time
   - Begin drawing
   - Clear background (LIGHTGRAY)
   - Draw all clock components
   - End drawing
   - Check for window close event
6. Close window
7. Return 0

**Return:** int (0 on success)

---

## 7. Non-Functional Requirements

### 7.1 Performance
- Maintain 60 FPS rendering frame rate
- Update time from system at 60 Hz frequency
- Smooth, flicker-free animation

### 7.2 Timing Accuracy
- Synchronize with system time
- Update only on actual time changes (integer seconds)
- Display current time within 1 second accuracy

### 7.3 Compatibility
- C99 standard compliance
- Cross-platform (Linux, Windows, macOS support via Raylib)
- Requires Raylib library installation

### 7.4 Visual Quality
- Anti-aliased circles and rectangles (Raylib default)
- Color-coded hands for easy identification
- Proper scaling of elements with clock size

---

## 8. Update() Function Details

### 6.2 Update()
**Purpose:** Update clock with current system time and date

**Signature:**
```c
void Update(s_AnalogClockData *analogClock)
```

**Parameters:**
- `analogClock`: Pointer to clock data structure

**Operations:**
1. Get current system time using `time(0)`
2. Convert to local time using `localtime()`
3. Extract hour and apply modulo 12 for 12-hour format
4. Extract minute
5. Extract second
6. Extract day (tm_mday)
7. Extract month (tm_mon + 1, since tm_mon is 0-indexed)
8. Extract year (tm_year + 1900, since tm_year is years since 1900)

**System Call Dependencies:**
- `time()` - Get current time
- `localtime()` - Convert to local time structure (struct tm)

**Return:** void

**Update Frequency:** Called once per frame (60 times per second at 60 FPS)

---

## 9. Color Scheme

| Component | Color | RGB Value |
|-----------|-------|-----------|
| Outer Clock Face | GRAY | (130, 130, 130, 255) |
| Middle Ring | LIGHTGRAY | (200, 200, 200, 255) |
| Inner Face | RAYWHITE | (245, 245, 245, 255) |
| Hour Markers | BLACK | (0, 0, 0, 255) |
| Minute Hand | GREEN | (0, 228, 48, 255) |
| Hour Hand | GRAY | (130, 130, 130, 255) |
| Second Hand | RED | (230, 41, 55, 255) |
| Center Circle | GRAY | (130, 130, 130, 255) |
| Date Box Background | LIGHTGRAY | (200, 200, 200, 255) |
| Date Box Border | BLACK | (0, 0, 0, 255) |
| Background | LIGHTGRAY | (200, 200, 200, 255) |

---

## 9. Angle Calculations

### Minute Hand Rotation
- Formula: `minute × 6 degrees`
- Reason: 360° ÷ 60 minutes = 6° per minute
- Updates once per minute

### Hour Hand Rotation
- Formula: `(30 × hour) + (minute ÷ 60.0 × 30) degrees`
- Reason: 360° ÷ 12 hours = 30° per hour
- Smooth continuous rotation

### Second Hand Rotation
- Formula: `second × 6 degrees`
- Reason: 360° ÷ 60 seconds = 6° per second
- Updates once per second

---

## 10. Constraints and Limitations

1. **12-Hour Format**: Hours are displayed in 12-hour format (not 24-hour)
2. **Local Time Only**: Always displays local system time
3. **Time Zone**: Respects system time zone settings
4. **Time Resolution**: Precision limited to 1-second intervals
5. **Date Precision**: Precision limited to 1-day intervals
6. **Window Size**: Fixed 600×600 pixel window
7. **Clock Position**: Fixed center at (300, 300)
8. **Clock Size**: Fixed 250-pixel radius
9. **Date Format**: Always displays as DD/MM/YYYY
10. **Date Box Position**: Fixed position below clock label

---

## 11. Exit Criteria

Application terminates when:
1. User closes the window using window manager
2. System sends close window signal
3. `WindowShouldClose()` returns true

---

## 12. Build and Deployment

### 12.1 Build Process
```bash
./build_script.sh
```

### 12.2 Execution
```bash
./build/raylib_c_demo
```

### 12.3 Build Script Details
- Removes previous build artifacts
- Runs CMake configuration
- Compiles and links executable
- Launches application

---

## 12. Files Structure

| File | Lines | Purpose |
|------|-------|---------|
| main.c | ~25 | Application entry point, window setup, main loop |
| src/AnalogClock.h | ~32 | Data structure definition, function declarations |
| src/AnalogClock.c | ~115 | Implementation of all clock functions |
| CMakeLists.txt | ~20 | Build configuration |
| build_script.sh | ~6 | Automated build script |

---

## 14. Version History

| Version | Date | Changes |
|---------|------|---------|
| 1.0 | 2026-03-01 | Initial specification and implementation |

---

**Document Status:** Complete  
**Last Updated:** 1 March 2026  
**Author:** GitHub Copilot
