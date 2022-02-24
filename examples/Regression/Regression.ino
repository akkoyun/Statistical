#include <Statistical.h>

Statistical DataSet;

void setup() {

	// Start Serial
    Serial.begin(115200);
    
}

void loop() {

	// Set Data
    Serial.println("Learning Data...");

    // Set Presicion
    DataSet.Linear_Regression_Presicion = 5;

    // Set Array
    float Data[DataSet.Linear_Regression_Presicion][2];

    // Learn Data
    DataSet.Array_FILO(Data, DataSet.Linear_Regression_Presicion, 1, 220.14);
    DataSet.Array_FILO(Data, DataSet.Linear_Regression_Presicion, 2, 221.36);
    DataSet.Array_FILO(Data, DataSet.Linear_Regression_Presicion, 3, 218.21);
    DataSet.Array_FILO(Data, DataSet.Linear_Regression_Presicion, 4, 217.06);
    DataSet.Array_FILO(Data, DataSet.Linear_Regression_Presicion, 5, 220.14);
    DataSet.Array_FILO(Data, DataSet.Linear_Regression_Presicion, 6, 222.14);
    DataSet.Array_FILO(Data, DataSet.Linear_Regression_Presicion, 7, 225.14);

    // Calculate Regression
    DataSet.Linear_Regression_Calculate(Data);

    Serial.print("Learned Data Count    : "); Serial.println(DataSet.Linear_Regression_Data_Count);

	// Print Calculated Data
    Serial.print("Regression Data Count : "); Serial.println(DataSet.Linear_Regression_Data_Count);
    Serial.print("Regression Slope      : "); Serial.println(DataSet.Linear_Regression_Slope);
    Serial.print("Regression Offset     : "); Serial.println(DataSet.Linear_Regression_Offset);

	// Clear DataSet
    DataSet.Linear_Regression_Data_Clear();

    delay(10000);
    
}

