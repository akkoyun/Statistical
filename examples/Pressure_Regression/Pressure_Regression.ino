#include <Statistical.h>
#include <Environment.h>

Statistical DataSet;

// Set Array
float Data[5][2];

void setup() {

	// Start Serial
    Serial.begin(115200);
    
    // Set Presicion
    DataSet.Linear_Regression_Presicion = 5;

    // First Pressure Read
    for (uint8_t i = 0; i < DataSet.Linear_Regression_Presicion + 5; i++) {
        
        // Measure Pressure
        float _Pressure = Sensor.Read_Analog_Pressure(2, 50);

        // Calculate Time Stamp
        float _Time = ((float)millis() / 1000) / 60;

        // Learn Data
        DataSet.Array_FILO(Data, 5, _Time, _Pressure);

        // Calculate Regression
        DataSet.Linear_Regression_Calculate(Data);

    	// Clear DataSet
        DataSet.Linear_Regression_Data_Clear();

    }
    

}

void loop() {

    // Measure Pressure
    float _Pressure = Sensor.Read_Analog_Pressure(2, 50);

    // Calculate Time Stamp
    float _Time = ((float)millis() / 1000) / 60;

    // Learn Data
    DataSet.Array_FILO(Data, 5, _Time, _Pressure);

    // Calculate Regression
    DataSet.Linear_Regression_Calculate(Data);

    // Calculate Anomaly
    float _Pressure_Anomaly = DataSet.Linear_Regression_Slope * 100;

    // Print Anomaly
    //if (_Pressure_Anomaly > 4) Serial.println("Basinc Artisi");
    //if (_Pressure_Anomaly < -4) Serial.println("Basinc Azalisi");
    
	// Print Calculated Data
    Serial.print("Pressure : "); Serial.print(_Pressure, 4); Serial.println(" Bar");    
    Serial.print("Slope    : "); Serial.print(DataSet.Linear_Regression_Slope * 100, 4); Serial.println(" ");
    Serial.println("----------------");

	// Clear DataSet
    DataSet.Linear_Regression_Data_Clear();

    delay(2000);
    
}

