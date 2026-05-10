/**
 * @brief Array_Stats — Complete function demonstration
 *
 * Shows every statistical function available in Array_Stats using
 * a fixed float array. Ideal as a reference for all available operations.
 *
 * Hardware : Any Arduino board (Uno, Mega, Nano, etc.)
 * Baud     : 115200
 */

#include <Statistical.h>

// Sample dataset — simulated sensor readings (e.g. voltage measurements)
float Data[] = {12.4, 11.8, 13.1, 12.9, 10.2, 13.5, 12.7, 11.9, 12.1, 13.0};
const size_t N = sizeof(Data) / sizeof(Data[0]);

// Construct the statistics object — no heap allocation, just wraps the array
Array_Stats<float> Stats(Data, N);

void setup() {

    Serial.begin(115200);
    while (!Serial);

    Serial.println(F("=============================================="));
    Serial.println(F("  Array_Stats — Full Function Demo"));
    Serial.println(F("=============================================="));

    // ── Raw array ──────────────────────────────────
    Serial.print(F("Data          : ")); Stats.Array();
    Serial.print(F("Count         : ")); Serial.println(Stats.Size());

    // ── Basic aggregates ───────────────────────────
    Serial.println(F("----------------------------------------------"));
    Serial.print(F("Sum           : ")); Serial.println(Stats.Sum(), 3);
    Serial.print(F("Min           : ")); Serial.println(Stats.Min(), 3);
    Serial.print(F("Max           : ")); Serial.println(Stats.Max(), 3);
    Serial.print(F("Square Sum    : ")); Serial.println(Stats.Sq_Sum(), 3);

    // ── Average types ──────────────────────────────
    Serial.println(F("----------------------------------------------"));
    Serial.print(F("Arithmetic Avg: ")); Serial.println(Stats.Average(Stats.Arithmetic_Avg), 4);
    Serial.print(F("Geometric  Avg: ")); Serial.println(Stats.Average(Stats.Geometric_Avg),  4);
    Serial.print(F("RMS        Avg: ")); Serial.println(Stats.Average(Stats.RMS_Avg),         4);
    Serial.print(F("Ext RMS    Avg: ")); Serial.println(Stats.Average(Stats.Ext_RMS_Avg),     4);
    Serial.print(F("1-Sigma    Avg: ")); Serial.println(Stats.Sigma_Average(Stats.Sigma_1),   4);
    Serial.print(F("2-Sigma    Avg: ")); Serial.println(Stats.Sigma_Average(Stats.Sigma_2),   4);

    // ── Distribution ───────────────────────────────
    Serial.println(F("----------------------------------------------"));
    Serial.print(F("Q1  (25th %)  : ")); Serial.println(Stats.Quartile(1), 4);
    Serial.print(F("Q2  (Median)  : ")); Serial.println(Stats.Quartile(2), 4);
    Serial.print(F("Q3  (75th %)  : ")); Serial.println(Stats.Quartile(3), 4);
    Serial.print(F("IQR           : ")); Serial.println(Stats.IQR(), 4);

    // ── Spread ─────────────────────────────────────
    Serial.println(F("----------------------------------------------"));
    Serial.print(F("Std Deviation : ")); Serial.println(Stats.Standard_Deviation(), 4);
    Serial.print(F("Std Dev Error : ")); Serial.println(Stats.Standard_Deviation_Error(), 4);
    Serial.print(F("Coeff Factor  : ")); Serial.print(Stats.Coefficient_Factor(), 2); Serial.println(F(" %"));
    Serial.print(F("Variance      : ")); Serial.println(Stats.Variance(), 4);

    // ── Sorted array (Quartile already sorted it) ──
    Serial.println(F("----------------------------------------------"));
    Serial.print(F("Sorted Data   : ")); Stats.Array();
    Serial.println(F("=============================================="));

}

void loop() {
    // Nothing to do — all output is in setup()
}
