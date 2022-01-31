#include <Statistical.h>

Statistical DataSet;

void setup() {

	// Start Serial
    Serial.begin(115200);
    
}

void loop() {

	// Set Data
    Serial.println("Learning Data...");
    
    // Learn Data
    DataSet.LinearRegression(1,220.14);
    DataSet.LinearRegression(2,221.36);
    DataSet.LinearRegression(3,218.21);
    DataSet.LinearRegression(4,217.06);
    DataSet.LinearRegression(5,220.14);

	// Print Calculated Data
    Serial.print("Regression Slope   : "); Serial.println(DataSet.Linear_Regression_a);
    Serial.print("Regression Offset  : "); Serial.println(DataSet.Linear_Regression_b);

	// Clear DataSet
    DataSet.Data_Clear();

    delay(1000);
    
}

