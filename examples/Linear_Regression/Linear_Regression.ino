/**
 * @brief Linear_Regression — Slope, Offset, R² and Compute_All()
 *
 * Fits y = Slope*x + Offset to a dataset using ordinary least squares.
 *
 * When you need all three values (Slope, Offset, R²), call Compute_All().
 * It computes everything in 2 array passes instead of 4 separate passes.
 *
 * Example: battery voltage vs elapsed time — detecting discharge rate.
 *
 * Hardware : Any Arduino board
 * Baud     : 115200
 */

#include <Statistical.h>

float Time_min[]  = { 0,  5, 10, 15, 20, 25, 30, 35, 40, 45};
float Voltage_V[] = {4.18, 4.12, 4.05, 3.99, 3.93, 3.86, 3.80, 3.74, 3.67, 3.61};
const size_t N    = sizeof(Time_min) / sizeof(Time_min[0]);

Linear_Regression<float, float> Reg(Time_min, Voltage_V, N);

void setup() {

    Serial.begin(115200);
    while (!Serial);

    Serial.println(F("=============================================="));
    Serial.println(F("  Linear_Regression — Battery Discharge"));
    Serial.println(F("=============================================="));

    // Raw data table
    Serial.println(F("  Time(min)  Voltage(V)"));
    for (size_t i = 0; i < N; i++) {
        Serial.print(F("  ")); Serial.print(Time_min[i], 0);
        Serial.print(F("          ")); Serial.println(Voltage_V[i], 2);
    }
    Serial.println(F("----------------------------------------------"));

    // ── Compute_All(): 2 passes, returns Slope + Offset + R² at once ──
    Linear_Regression<float, float>::Regression_Result Res = Reg.Compute_All();

    Serial.print(F("Slope  (b1)   : ")); Serial.print(Res.Slope,  6); Serial.println(F(" V/min"));
    Serial.print(F("Offset (b0)   : ")); Serial.print(Res.Offset, 6); Serial.println(F(" V"));
    Serial.print(F("R²            : ")); Serial.println(Res.R2, 6);
    Serial.println(F("----------------------------------------------"));

    // Equation and prediction
    Serial.print(F("Equation      : V = "));
    Serial.print(Res.Slope, 4); Serial.print(F(" * t + ")); Serial.println(Res.Offset, 4);

    float t_pred = 60.0f;
    float v_pred = Res.Slope * t_pred + Res.Offset;
    Serial.print(F("V at t=60 min : ")); Serial.print(v_pred, 3); Serial.println(F(" V"));

    if      (Res.R2 > 0.99f) Serial.println(F("Fit quality   : Excellent (R² > 0.99)"));
    else if (Res.R2 > 0.95f) Serial.println(F("Fit quality   : Good (R² > 0.95)"));
    else                     Serial.println(F("Fit quality   : Poor"));

    Serial.println(F("=============================================="));

}

void loop() {
    // Nothing to do
}
