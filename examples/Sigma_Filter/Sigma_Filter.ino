/**
 * @brief Sigma_Average — Outlier-resistant filtered mean
 *
 * Sigma_Average removes values that fall outside ±N standard deviations
 * from the arithmetic mean, then recomputes the mean on the remaining
 * "clean" values. This is effective for sensor data with occasional spikes.
 *
 * Sigma_1 : keeps values within ±1σ  (~68% of a normal distribution)
 * Sigma_2 : keeps values within ±2σ  (~95%)
 * Sigma_3 : keeps values within ±3σ  (~99.7%)
 *
 * Hardware : Any Arduino board
 * Baud     : 115200
 */

#include <Statistical.h>

// Pressure sensor readings (hPa) with three injected outliers
float Pressure[] = {
    1013.2, 1012.8, 1013.5,
    1050.0,                   // outlier: spike high
    1013.1, 1012.9, 1013.4,
    970.0,                    // outlier: spike low
    1013.3, 1013.0, 1012.7,
    1013.6,
    999.5                     // outlier: moderate low
};
const size_t N = sizeof(Pressure) / sizeof(Pressure[0]);

Array_Stats<float> Stats(Pressure, N);

void setup() {

    Serial.begin(115200);
    while (!Serial);

    Serial.println(F("=============================================="));
    Serial.println(F("  Sigma_Average — Outlier Filtering Demo"));
    Serial.println(F("=============================================="));

    Serial.print(F("Dataset       : ")); Stats.Array();
    Serial.print(F("Count         : ")); Serial.println(N);

    // ── Spread metrics ─────────────────────────────
    float arith  = Stats.Arithmetic_Average();
    float stddev = Stats.Standard_Deviation();

    Serial.println(F("----------------------------------------------"));
    Serial.print(F("Arith. Avg    : ")); Serial.println(arith,  3);
    Serial.print(F("Std Deviation : ")); Serial.println(stddev, 3);

    // ── Sigma-filtered averages ────────────────────
    Serial.println(F("----------------------------------------------"));
    Serial.print(F("1-Sigma Avg   : ")); Serial.println(Stats.Sigma_Average(Stats.Sigma_1), 3);
    Serial.print(F("2-Sigma Avg   : ")); Serial.println(Stats.Sigma_Average(Stats.Sigma_2), 3);
    Serial.print(F("3-Sigma Avg   : ")); Serial.println(Stats.Sigma_Average(Stats.Sigma_3), 3);

    // ── Explanation ────────────────────────────────
    Serial.println(F("----------------------------------------------"));
    Serial.println(F("True pressure ~1013 hPa."));
    Serial.println(F("Arithmetic avg is pulled toward outliers."));
    Serial.println(F("1-Sigma avg ignores the spikes => closer to truth."));
    Serial.println(F("=============================================="));

}

void loop() {
    // Nothing to do
}
