#include <Statistical.h>

Statistical DataSet;

void setup() {

	// Start Serial
    Serial.begin(115200);
    
}

void loop() {

	// Set Data
    Serial.println("Learning Data...");

    // Set Precision
    uint8_t Linear_Regression_Precision = 5;

    // Set Array
    float Data[Linear_Regression_Precision][2];

    // Learn Data
    DataSet.Array_FILO(Data, Linear_Regression_Precision, 1, 220.14);
    DataSet.Array_FILO(Data, Linear_Regression_Precision, 2, 221.36);
    DataSet.Array_FILO(Data, Linear_Regression_Precision, 3, 218.21);
    DataSet.Array_FILO(Data, Linear_Regression_Precision, 4, 217.06);
    DataSet.Array_FILO(Data, Linear_Regression_Precision, 5, 220.14);
    DataSet.Array_FILO(Data, Linear_Regression_Precision, 6, 222.14);
    DataSet.Array_FILO(Data, Linear_Regression_Precision, 7, 225.14);

    // Print FILO Array
    Serial.print("Regression Data Array : ");
    for (uint8_t i = 0; i < Linear_Regression_Precision; i++) {
        Serial.print("[");        
        Serial.print(Data[i][0]);
        Serial.print(",");
        Serial.print(Data[i][1]);
        Serial.print("] ");
    }
    Serial.println("");

	// Print Calculated Data
    Serial.print("Regression Data Count : "); Serial.println(Linear_Regression_Precision);
    Serial.print("Regression Slope      : "); Serial.println(DataSet.Linear_Regression_Slope(Data, Linear_Regression_Precision), 4);
    Serial.print("Regression Offset     : "); Serial.println(DataSet.Linear_Regression_Offset(Data, Linear_Regression_Precision), 4);
    Serial.print("Regression R2         : "); Serial.println(DataSet.Linear_Regression_R2(Data, Linear_Regression_Precision), 4);
    Serial.println("------------------------");

    delay(10000);
    
}

