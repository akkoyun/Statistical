#include <Statistical.h>

// Construct Object
Stream_Stats _Stream;

void setup() {

	// Start Serial
    Serial.begin(115200);
    
}

void loop() {

	// Set Data
    Serial.println("Learning Data...");
    _Stream.Add_Data(125.2);
	_Stream.Add_Data(122.2);
	_Stream.Add_Data(121.2);
	_Stream.Add_Data(128.2);
	_Stream.Add_Data(132.2);
    
    // Print Calculations
    Serial.print("Stream Data Count : "); Serial.println(_Stream.Get_Data_Count());
    Serial.print("Stream Avg Value  : "); Serial.println(_Stream.Get_Average());
    Serial.print("Stream Min Value  : "); Serial.println(_Stream.Get_Min());
    Serial.print("Stream Max Value  : "); Serial.println(_Stream.Get_Max());
    Serial.println("----------------");

	// Reset
    _Stream.Data_Clear();
    
    delay(1000);
    
}

