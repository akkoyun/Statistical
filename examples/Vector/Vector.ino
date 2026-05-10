/**
 * @brief Vector_Stats — Polar vector addition demonstration
 *
 * Adds multiple vectors given as (magnitude, compass bearing) pairs and
 * returns the resultant vector's magnitude and compass bearing.
 *
 * Compass convention:
 *   0°   = North
 *   90°  = East
 *   180° = South
 *   270° = West
 *   Angles increase clockwise.
 *
 * Example use-case: average wind speed and direction from multiple sensors
 * or from multiple measurement intervals.
 *
 * Hardware : Any Arduino board
 * Baud     : 115200
 */

#include <Statistical.h>

// Wind speed (m/s) for each measurement
float Speed_ms[]  = {3.5,  5.2,  4.0,  6.1,  2.8};

// Wind direction — compass bearing in degrees (where the wind comes FROM)
float Direction[] = {45.0, 60.0, 30.0, 75.0, 50.0};

const size_t N = sizeof(Speed_ms) / sizeof(Speed_ms[0]);

Vector_Stats<float, float> Wind(Speed_ms, Direction, N);

void setup() {

    Serial.begin(115200);
    while (!Serial);

    Serial.println(F("=============================================="));
    Serial.println(F("  Vector_Stats — Wind Vector Addition Demo"));
    Serial.println(F("=============================================="));

    // ── Input vectors ──────────────────────────────
    Serial.println(F("  Speed(m/s)   Direction(°)"));
    Serial.println(F("  ----------   ------------"));
    for (size_t i = 0; i < N; i++) {
        Serial.print(F("  ")); Serial.print(Speed_ms[i], 1);
        Serial.print(F("         ")); Serial.println(Direction[i], 1);
    }

    // ── Compute resultant ──────────────────────────
    Wind.Vector_Sum();

    Serial.println(F("----------------------------------------------"));
    Serial.print(F("Resultant Speed    : ")); Serial.print(Wind.Result.Magnitude, 3); Serial.println(F(" m/s"));
    Serial.print(F("Resultant Direction: ")); Serial.print(Wind.Result.Angle,     2); Serial.println(F(" °"));
    Serial.println(F("----------------------------------------------"));

    // ── Compass rose hint ──────────────────────────
    float a = Wind.Result.Angle;
    Serial.print(F("Quadrant      : "));
    if      (a < 22.5  || a >= 337.5) Serial.println(F("North"));
    else if (a < 67.5)                Serial.println(F("North-East"));
    else if (a < 112.5)               Serial.println(F("East"));
    else if (a < 157.5)               Serial.println(F("South-East"));
    else if (a < 202.5)               Serial.println(F("South"));
    else if (a < 247.5)               Serial.println(F("South-West"));
    else if (a < 292.5)               Serial.println(F("West"));
    else                              Serial.println(F("North-West"));

    Serial.println(F("=============================================="));

}

void loop() {
    // Nothing to do
}
