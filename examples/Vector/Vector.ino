// Include Libraries
#include <Statistical.h>

// Define Vector Object
Vector_Stats Vector;

void setup() {

	// Start Serial
    Serial.begin(115200);

    // Add Vectors
    Vector.Add(5, 45);
    Vector.Add(3, 135);

    // Print Results
    Serial.print("Total X : "); Serial.println(Vector.Get_X_Magnitude());
    Serial.print("Total Y : "); Serial.println(Vector.Get_Y_Magnitude());
    Serial.print("Total Magnitude : "); Serial.println(Vector.Total_Magnitude());
    Serial.print("Total Angle : "); Serial.println(Vector.Total_Angle());

}

void loop() {

    
}

