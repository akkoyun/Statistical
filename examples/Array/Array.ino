// Include Statistal Library
#include <Statistical.h>

void setup() {

	// Start Serial
    Serial.begin(115200);

}

void loop() {

	// Set Data
	Serial.println("Learning Data...");
	float Data_Array[] = {220.14, 221.36, 218.21, 217.6, 215.7, 225.8, 220.14 };

	// Print Array
	Serial.print("Data Array : ");
	for (uint8_t i = 0; i < sizeof(Data_Array); i++) {
        Serial.print("[");
        Serial.print(Data_Array[i]);
        Serial.print("] ");
	}
	Serial.println("");

	// Calculate Array Statistics
	Stats.Array_Statistic(Data_Array, sizeof(Data_Array));

	// Print Stats
	Serial.print("Array Sum                      : "); Serial.println(Stats.Array_Sum);
	Serial.print("Array Square Sum               : "); Serial.println(Stats.Array_Sq_Sum);
	Serial.print("Array Min                      : "); Serial.println(Stats.Array_Min);
	Serial.print("Array Max                      : "); Serial.println(Stats.Array_Max);
	Serial.print("Array Aritmetic Average        : "); Serial.println(Stats.Array_AAvg);
	Serial.print("Array Geometric Average        : "); Serial.println(Stats.Array_GAvg);
	Serial.print("Array RMS Average              : "); Serial.println(Stats.Array_RMS_Avg);
	Serial.print("Array Extended RMS Average     : "); Serial.println(Stats.Array_Ext_RMS_Avg);
	Serial.print("Array Median                   : "); Serial.println(Stats.Array_Med);
	Serial.print("Array Standart Deviation       : "); Serial.println(Stats.Array_SDev);
	Serial.print("Array Standart Deviation Error : "); Serial.println(Stats.Array_SDev_Err);
	Serial.print("Array Coefficient Factor       : "); Serial.println(Stats.Array_Coef);

	Serial.print("Sorted Data Array              : ");
	for (uint8_t i = 0; i < sizeof(Data_Array); i++) {
        Serial.print("[");
        Serial.print(Data_Array[i]);
        Serial.print("] ");
	}
	Serial.println("");

	Serial.println("--------------------------------------------------");

    delay(2000);

}

