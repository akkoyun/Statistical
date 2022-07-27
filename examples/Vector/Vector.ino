#include <Statistical.h>

void setup() {

	// Start Serial
    Serial.begin(115200);
    
}

void loop() {

	// Learn Print
    Serial.println("Learning Data...");

	// Set Data
	float Data_X[] = {-1, -5, 5};
	float Data_Y[] = {90, -30, -150};

    // Print Calculations
    Serial.print("Vector A : ["); Serial.print(Data_X[0], 2); Serial.print(" - "); Serial.print(abs(Data_Y[0] - 90), 2); Serial.println("]");
    Serial.print("Vector B : ["); Serial.print(Data_X[1], 2); Serial.print(" - "); Serial.print(abs(Data_Y[1] - 90), 2); Serial.println("]");
    Serial.print("Vector C : ["); Serial.print(Data_X[2], 2); Serial.print(" - "); Serial.print(abs(Data_Y[2] - 90), 2); Serial.println("]");

	// Declare Object
	Vector_Stats<float, float> Vector(Data_X, Data_Y, 3);

    // Calculate Vector Sum
    Vector.Vector_Sum();
    
    // Print Calculations
    Serial.print("Vector Sum Magnitude : "); Serial.println(Vector.Result.Magnitude);
    Serial.print("Vector Sum Angle     : "); Serial.println(Vector.Result.Angle);
    Serial.println("----------------");

    // Loop Delay
    delay(10000);
    
}

