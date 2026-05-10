/**
 * @brief FILO_Stats<T,N> — Fixed-size sliding window, zero heap
 *
 * FILO_Stats<T,N> owns its internal buffer on the stack.
 * No malloc, no realloc, no pointer confusion — completely safe.
 *
 * window.Add(value) shifts the buffer left and appends the new value.
 * All Array_Stats methods (Average, StdDev, Min, Max, etc.) are
 * available on the window object through inheritance.
 *
 * Hardware : Any Arduino board
 * Baud     : 115200
 */

#include <Statistical.h>

// 6-element sliding window — buffer lives on the stack inside the object
FILO_Stats<float, 6> Window;

// Simulated ADC readings arriving one per loop iteration
float Readings[] = {
    102.3, 105.1, 98.7, 107.4, 103.2,
    101.8, 99.5,  106.0, 104.3, 100.9
};
const uint8_t TOTAL = sizeof(Readings) / sizeof(Readings[0]);

void setup() {

    Serial.begin(115200);
    while (!Serial);

    Serial.println(F("=============================================="));
    Serial.println(F("  FILO_Stats<float,6> — Sliding Window Demo"));
    Serial.println(F("=============================================="));

    for (uint8_t k = 0; k < TOTAL; k++) {

        Window.Add(Readings[k]);

        Serial.print(F("New value     : ")); Serial.println(Readings[k], 1);
        Serial.print(F("Window        : ")); Window.Array();
        Serial.print(F("Arith Avg     : ")); Serial.println(Window.Arithmetic_Average(), 3);
        Serial.print(F("Std Deviation : ")); Serial.println(Window.Standard_Deviation(), 3);
        Serial.print(F("Min           : ")); Serial.println(Window.Min(), 1);
        Serial.print(F("Max           : ")); Serial.println(Window.Max(), 1);
        Serial.println(F("----------------------------------------------"));

    }

    Serial.println(F("=============================================="));

}

void loop() {
    // Nothing to do
}
