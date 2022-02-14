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
	uint8_t Data_Size = 7;

	// Print Array
	Serial.print("Data Array : ");
	for (uint8_t i = 0; i < Data_Size; i++) {Serial.print("["); Serial.print(Data_Array[i]); Serial.print("] ");} Serial.println("");

	// Print Stats
	Serial.print("Array Sum                      : "); Serial.println(Stats.Array_Sum(Data_Array, Data_Size));
	Serial.print("Array Square Sum               : "); Serial.println(Stats.Array_Sq_Sum(Data_Array, Data_Size));
	Serial.print("Array Min                      : "); Serial.println(Stats.Array_Min(Data_Array, Data_Size));
	Serial.print("Array Max                      : "); Serial.println(Stats.Array_Max(Data_Array, Data_Size));
	Serial.print("Array Aritmetic Average        : "); Serial.println(Stats.Array_Aritmetic_Average(Data_Array, Data_Size));
	Serial.print("Array Geometric Average        : "); Serial.println(Stats.Array_Geometric_Average(Data_Array, Data_Size));
	Serial.print("Array RMS Average              : "); Serial.println(Stats.Array_RMS_Average(Data_Array, Data_Size));
	Serial.print("Array Extended RMS Average     : "); Serial.println(Stats.Array_Ext_RMS_Average(Data_Array, Data_Size));
	Serial.print("Array Median                   : "); Serial.println(Stats.Array_Median(Data_Array, Data_Size));
	Serial.print("Array Standart Deviation       : "); Serial.println(Stats.Array_Standart_Deviation(Data_Array, Data_Size));
	Serial.print("Array Standart Deviation Error : "); Serial.println(Stats.Array_Standart_Deviation_Error(Data_Array, Data_Size));
	Serial.print("Array Coefficient Factor       : "); Serial.println(Stats.Array_Coefficient_Factor(Data_Array, Data_Size));

	Serial.print("Sorted Data Array              : ");
	for (uint8_t i = 0; i < Data_Size; i++) {Serial.print("["); Serial.print(Data_Array[i]); Serial.print("] ");} Serial.println("");

	Serial.println("--------------------------------------------------");

    delay(2000);

}

