#include <Statistical.h>

Statistical DataSet1;

void setup() {

	// Start Serial
    Serial.begin(115200);
    
}

void loop() {

	// Set Data
    Serial.println("Learning Data...");
	DataSet1.Stream_Statistic(125.2);
	DataSet1.Stream_Statistic(122.2);
	DataSet1.Stream_Statistic(121.2);
	DataSet1.Stream_Statistic(128.2);
	DataSet1.Stream_Statistic(132.2);

	// Datas
	Serial.print(DataSet1.Data_Count); Serial.println(" Point Stream Statistic Calculation...");
    Serial.print("Min Value: "); Serial.println(DataSet1.Stream_Minimum);
    Serial.print("Max Value: "); Serial.println(DataSet1.Stream_Maximum);
    Serial.print("Avg Value: "); Serial.println(DataSet1.Stream_Average);

	// Reset
	DataSet1.Stream_Clear();
    
    delay(5000);
    
}

