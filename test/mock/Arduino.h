#pragma once
// Mock Arduino.h for PlatformIO native (host) builds.
// Uses plain C headers so the native toolchain always finds them.

#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// math.h puts sqrt/cos/sin/atan2/fmod/log/exp in global scope and
// defines isnan / isinf as macros — no using-declarations needed.

#ifndef PI
#  define PI 3.14159265358979323846f
#endif

// No-op on native builds (PROGMEM only matters on AVR)
#define F(s) (s)

static inline float radians(float d) { return d * (PI / 180.0f); }
static inline float degrees(float r) { return r * (180.0f / PI); }

// Minimal Serial stub — writes to stdout; keeps test output legible
struct _Serial_t {
    void begin(unsigned long) {}
    template<typename T> void print(T v)   { printf("%.6g", (double)v); }
    void print(const char* s)              { printf("%s", s); }
    template<typename T> void println(T v) { printf("%.6g\n", (double)v); }
    void println(const char* s)            { printf("%s\n", s); }
    void println()                          { printf("\n"); }
};

// One instance per translation unit; the guard prevents duplicate-symbol
// linker errors because each test binary is a single TU on PlatformIO native.
static _Serial_t Serial;
