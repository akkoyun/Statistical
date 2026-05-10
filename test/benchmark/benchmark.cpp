// AVR RAM footprint benchmark
// Build: python3 -m platformio run -e uno
// Read DATA + BSS from the build output to confirm ultra-low-RAM budget.
//
// All instances are global (static lifetime) so AVR linker reports their
// combined footprint in the DATA/BSS sections of the .elf summary.

#include <Arduino.h>
#include "Statistical.h"

// ── Array_Stats: wraps a 6-element float buffer (24 bytes on AVR) ─────────────
static float         vol_buf[6] = {3.1f, 3.2f, 3.0f, 3.3f, 3.1f, 3.2f};
static Array_Stats<float> g_array(vol_buf, 6);

// ── FILO_Stats: 6-float ring on the stack (24 bytes data + 6 bytes ptr+size) ──
static FILO_Stats<float, 6> g_filo;

// ── Stream_Stats: 1 float + 1 uint16 + 3 Data_Type members (≈ 14 bytes) ───────
static Stream_Stats<float> g_stream;

// ── Linear_Regression: two pointers + one size_t (≈ 7 bytes on AVR) ──────────
static float reg_x[5] = {1, 2, 3, 4, 5};
static float reg_y[5] = {2, 4, 6, 8, 10};
static Linear_Regression<float, float> g_reg(reg_x, reg_y, 5);

// ── Vector_Stats: two pointers + one size_t + two floats (≈ 13 bytes on AVR) ──
static float vec_mag[3] = {10, 10, 10};
static float vec_ang[3] = {0, 120, 240};
static Vector_Stats<float, float> g_vec(vec_mag, vec_ang, 3);

void setup() {
    Serial.begin(9600);

    // Array_Stats ──────────────────────────────────────────────────────────────
    Serial.print(F("Arith avg : "));
    Serial.println(g_array.Arithmetic_Average());

    Serial.print(F("Sigma avg : "));
    Serial.println(g_array.Sigma_Average(2));

    Serial.print(F("Variance  : "));
    Serial.println(g_array.Variance());

    Serial.print(F("Std dev   : "));
    Serial.println(g_array.Standard_Deviation());

    Serial.print(F("IQR       : "));
    Serial.println(g_array.IQR());

    // FILO_Stats ───────────────────────────────────────────────────────────────
    for (uint8_t i = 0; i < 6; i++) g_filo.Add((float)(i + 1));
    Serial.print(F("FILO avg  : "));
    Serial.println(g_filo.Arithmetic_Average());

    // Stream_Stats ─────────────────────────────────────────────────────────────
    for (uint8_t i = 0; i < 5; i++) g_stream.Add((float)(i * 10));
    Serial.print(F("Stream avg: "));
    Serial.println(g_stream.Get_Average());
    Serial.print(F("Stream min: "));
    Serial.println(g_stream.Get_Min());
    Serial.print(F("Stream max: "));
    Serial.println(g_stream.Get_Max());

    // Linear_Regression ────────────────────────────────────────────────────────
    auto res = g_reg.Compute_All();
    Serial.print(F("Slope     : "));
    Serial.println(res.Slope);
    Serial.print(F("Offset    : "));
    Serial.println(res.Offset);
    Serial.print(F("R2        : "));
    Serial.println(res.R2);

    // Vector_Stats ─────────────────────────────────────────────────────────────
    g_vec.Vector_Sum();
    Serial.print(F("Vec mag   : "));
    Serial.println(g_vec.Result.Magnitude);
    Serial.print(F("Vec angle : "));
    Serial.println(g_vec.Result.Angle);
}

void loop() {}
