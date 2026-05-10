/**
 * @brief Quartile & IQR — Distribution analysis and outlier detection
 *
 * Quartiles split sorted data into four equal parts:
 *   Q1 (25th percentile) : 25% of values are below this
 *   Q2 (50th percentile) : median — half below, half above
 *   Q3 (75th percentile) : 75% of values are below this
 *
 * IQR = Q3 - Q1  (interquartile range, measures spread of the middle 50%)
 *
 * Outlier fences (Tukey's method):
 *   Lower fence = Q1 - 1.5 * IQR
 *   Upper fence = Q3 + 1.5 * IQR
 *   Any value outside the fences is a statistical outlier.
 *
 * NOTE: Quartile() sorts the original array in-place as a side effect.
 *
 * Hardware : Any Arduino board
 * Baud     : 115200
 */

#include <Statistical.h>

// Response time measurements (ms) from a network device
float Response_ms[] = {
    42.1, 45.3, 41.8, 44.0, 43.5,
    46.2, 42.7, 43.1, 44.8, 45.0,
    41.3, 43.9,
    120.5,   // outlier: slow response
    44.2, 43.6
};
const size_t N = sizeof(Response_ms) / sizeof(Response_ms[0]);

Array_Stats<float> Stats(Response_ms, N);

void setup() {

    Serial.begin(115200);
    while (!Serial);

    Serial.println(F("=============================================="));
    Serial.println(F("  Quartile & IQR — Outlier Detection Demo"));
    Serial.println(F("=============================================="));

    Serial.print(F("Dataset       : ")); Stats.Array();
    Serial.print(F("Count         : ")); Serial.println(N);

    // ── Basic stats ────────────────────────────────
    Serial.println(F("----------------------------------------------"));
    Serial.print(F("Min           : ")); Serial.println(Stats.Min(), 2);
    Serial.print(F("Max           : ")); Serial.println(Stats.Max(), 2);
    Serial.print(F("Arith. Avg    : ")); Serial.println(Stats.Arithmetic_Average(), 2);

    // ── Quartiles (sorts array in-place) ───────────
    float q1  = Stats.Quartile(1);
    float q2  = Stats.Quartile(2);
    float q3  = Stats.Quartile(3);
    float iqr = Stats.IQR();

    Serial.println(F("----------------------------------------------"));
    Serial.print(F("Q1  (25th %)  : ")); Serial.println(q1,  3);
    Serial.print(F("Q2  (Median)  : ")); Serial.println(q2,  3);
    Serial.print(F("Q3  (75th %)  : ")); Serial.println(q3,  3);
    Serial.print(F("IQR           : ")); Serial.println(iqr, 3);

    // ── Tukey outlier fences ───────────────────────
    float lower_fence = q1 - 1.5f * iqr;
    float upper_fence = q3 + 1.5f * iqr;

    Serial.println(F("----------------------------------------------"));
    Serial.print(F("Lower fence   : ")); Serial.println(lower_fence, 3);
    Serial.print(F("Upper fence   : ")); Serial.println(upper_fence, 3);

    // ── Flag sorted data against fences ───────────
    Serial.println(F("----------------------------------------------"));
    Serial.println(F("Sorted data with outlier flags:"));
    for (size_t i = 0; i < N; i++) {
        float v = Response_ms[i];
        Serial.print(F("  ")); Serial.print(v, 1);
        if (v < lower_fence || v > upper_fence) Serial.print(F("  <-- OUTLIER"));
        Serial.println();
    }

    Serial.println(F("=============================================="));

}

void loop() {
    // Nothing to do
}
