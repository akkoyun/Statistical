/**
 * @brief Stream_Stats — Online statistics without an array
 *
 * Stream_Stats computes running Min, Max, and arithmetic mean
 * using Welford's online algorithm. No array is stored — memory
 * usage is constant regardless of how many samples are added.
 *
 * Typical use: aggregate sensor readings over a measurement window,
 * then read the summary and call Clear() to start the next window.
 *
 * Hardware : Any Arduino board
 * Baud     : 115200
 */

#include <Statistical.h>

// One stream object per metric you want to track independently
Stream_Stats<float> Temperature;
Stream_Stats<float> Humidity;

// Simulated sensor data (replace with real sensor reads in practice)
float Temp_Data[] = {23.4, 24.1, 22.8, 23.9, 25.0, 22.5, 24.7, 23.3};
float Hum_Data[]  = {55.2, 57.0, 54.8, 56.3, 58.1, 53.9, 56.7, 55.5};
const uint8_t N = sizeof(Temp_Data) / sizeof(Temp_Data[0]);

void print_stream(const __FlashStringHelper* label, Stream_Stats<float>& s) {
    Serial.print(label);
    Serial.print(F("  Count="));  Serial.print(s.Get_Data_Count());
    Serial.print(F("  Avg="));    Serial.print(s.Get_Average(), 2);
    Serial.print(F("  Min="));    Serial.print(s.Get_Min(), 2);
    Serial.print(F("  Max="));    Serial.print(s.Get_Max(), 2);
    Serial.print(F("  Last="));   Serial.println(s.Get_Last(), 2);
}

void setup() {

    Serial.begin(115200);
    while (!Serial);

    Serial.println(F("=============================================="));
    Serial.println(F("  Stream_Stats — Online Statistics Demo"));
    Serial.println(F("=============================================="));

    // ── Feed data sample by sample ─────────────────
    Serial.println(F("Feeding samples one by one:"));
    Serial.println(F("----------------------------------------------"));

    for (uint8_t i = 0; i < N; i++) {

        Temperature.Add(Temp_Data[i]);
        Humidity.Add(Hum_Data[i]);

        Serial.print(F("["));  Serial.print(i + 1); Serial.print(F("] "));
        Serial.print(F("T=")); Serial.print(Temp_Data[i], 1);
        Serial.print(F("  H=")); Serial.println(Hum_Data[i], 1);

    }

    // ── Summary after all samples ──────────────────
    Serial.println(F("----------------------------------------------"));
    Serial.println(F("Summary:"));
    print_stream(F("Temperature"), Temperature);
    print_stream(F("Humidity   "), Humidity);

    // ── Reset and start a new measurement window ───
    Serial.println(F("----------------------------------------------"));
    Serial.println(F("Clearing streams for next window..."));
    Temperature.Clear();
    Humidity.Clear();
    Serial.print(F("Count after clear: ")); Serial.println(Temperature.Get_Data_Count());

    Serial.println(F("=============================================="));

}

void loop() {
    // In a real application: read sensor, call .Add(), then .Clear() periodically
}
