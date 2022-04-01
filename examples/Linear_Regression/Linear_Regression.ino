#include <Statistical.h>

void setup() {

	// Start Serial
    Serial.begin(115200);

	// Set Data
    Serial.println("Learning Data...");

}

void loop() {

	// Set Data
	uint32_t Data_X[] = {1, 2, 3, 4, 5, 6, 7};
	float Data_Y[] = {11, 12, 13, 14, 15, 16, 17};


    // Declare Object
    Linear_Regression Regression(Data_X, Data_Y, 7);




Regression.Offset();





/*


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

*/


    delay(10000);
    
}

