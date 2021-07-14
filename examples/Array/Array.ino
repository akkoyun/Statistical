#include <Statistical.h>

Statistical DataSet;

void setup() {

	// Start Serial
    Serial.begin(115200);
    
}

void loop() {

	// Set Data
    Serial.println("Learning Data...");
    float Data_Array[] = {220.14, 221.36, 218.21, 217.6, 215.7, 225.8, 220.14 };
  
	// Calculate Data
	DataSet.Array_Average(Data_Array,15,1);

    Serial.print("Array Avg Value  : "); Serial.println(DataSet.Array_Average);
    Serial.print("Array Min Value  : "); Serial.println(DataSet.Array_Minimum);
    Serial.print("Array Max Value  : "); Serial.println(DataSet.Array_Maximum);
    Serial.print("Array Sdev Value : "); Serial.println(DataSet.Array_SDev);
    
    delay(1000);
    
}

