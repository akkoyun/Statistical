#include <Statistical.h>

Statistical DataSet;

void setup() {

	// Start Serial
    Serial.begin(115200);
    
}

void loop() {

	// Set Data
    Serial.println("Learning Data...");
    DataSet.Stream_Statistic(125.2);
	DataSet.Stream_Statistic(122.2);
	DataSet.Stream_Statistic(121.2);
	DataSet.Stream_Statistic(128.2);
	DataSet.Stream_Statistic(132.2);
    
    // Print Calculations
    Serial.print("Stream Data Count : "); Serial.println(DataSet.Data_Count);
    Serial.print("Stream Avg Value  : "); Serial.println(DataSet.Stream_Average);
    Serial.print("Stream Min Value  : "); Serial.println(DataSet.Stream_Minimum);
    Serial.print("Stream Max Value  : "); Serial.println(DataSet.Stream_Maximum);
    Serial.println("----------------");

	// Reset
	DataSet.Stream_Clear();
    
    delay(1000);
    
}

