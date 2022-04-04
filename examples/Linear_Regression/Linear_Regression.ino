#include <Statistical.h>

void setup() {

	// Start Serial
    Serial.begin(115200);

	// Set Data
    Serial.println("Learning Data...");

}

void loop() {

	// Set Data
	uint8_t Data_X[] = {1, 2, 3, 4, 5, 6, 7};
	float Data_Y[] = {2, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7};

	// Declare Object
	Linear_Regression<uint8_t, float> Regression(Data_X, Data_Y, sizeof(Data_X) / sizeof(Data_X[0]));

	// Print Array X
	Serial.print("Data X Array : ");
	for (size_t i = 0; i < sizeof(Data_X) / sizeof(Data_X[0]); i++) {Serial.print(F("[")); Serial.print(Data_X[i]); Serial.print(F("] "));}
	Serial.println("");
    
	// Print Array X
	Serial.print("Data Y Array : ");
	for (size_t i = 0; i < sizeof(Data_X) / sizeof(Data_X[0]); i++) {Serial.print(F("[")); Serial.print(Data_Y[i]); Serial.print(F("] "));}
	Serial.println("");

	// Print Regression Slope
	Serial.print("Slope        : "); Serial.println(Regression.Slope(),5);
	
	// Print Regression Offset
	Serial.print("Offset       : "); Serial.println(Regression.Offset(),5);

	// Print Regression R2
	Serial.print("R2           : "); Serial.println(Regression.R2(),5);

	// Print Divider
	Serial.println("--------------------------");

	// Delay
    delay(1000);
    
}

