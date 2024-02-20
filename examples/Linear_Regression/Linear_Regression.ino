// Include Libraries
#include <Statistical.h>

// Define Regression Object
Regression<float, float> reg;

void setup() {

	// Serial Communication
    Serial.begin(115200);

    // Add Data
    reg.Add(1.0, 2.0);
    reg.Add(2.0, 3.0);
    reg.Add(3.0, 5.0);
    reg.Add(4.0, 7.0);
    reg.Add(5.0, 11.0);

    // Calculate Regression
    float slope = reg.Slope();
    float offset = reg.Offset();
    float rSquared = reg.R2();

    // Print Results
    Serial.print("Slope: "); Serial.println(slope, 4);
    Serial.print("Offset: "); Serial.println(offset, 4);
    Serial.print("R^2: "); Serial.println(rSquared, 4);	

}

void loop() {

	
}