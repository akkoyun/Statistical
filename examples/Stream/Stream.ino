#include <Statistical.h>

void setup() {

	// Start Serial
    Serial.begin(115200);
    
}

void loop() {

    // Construct Object
    Stream_Stats<float> _Stream;

	// Learn Print
    Serial.println("Learning Data...");

	// Set Data
    _Stream.Add(125.2);
	_Stream.Add(122.2);
	_Stream.Add(121.2);
	_Stream.Add(128.2);
	_Stream.Add(132.2);
    
    // Print Calculations
    Serial.print("Stream Data Count : "); Serial.println(_Stream.Get_Data_Count());
    Serial.print("Stream Avg Value  : "); Serial.println(_Stream.Get_Average());
    Serial.print("Stream Min Value  : "); Serial.println(_Stream.Get_Min());
    Serial.print("Stream Max Value  : "); Serial.println(_Stream.Get_Max());
    Serial.println("----------------");

	// Reset
    _Stream.Clear();
    
    delay(1000);
    
}

