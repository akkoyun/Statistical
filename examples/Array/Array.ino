// Include Statistal Library
#include <Statistical.h>

void setup() {

	// Start Serial
    Serial.begin(115200);

	// Set Data
	Serial.println(F("Learning Data..."));

}

void loop() {

	// Set Data
//	float Data[] = {220.14, 221.36, 218.21, 217.6, 215.7, 225.8, 220.14};
//	double Data[] = {220.14, 221.36, 218.21, 217.6, 215.7, 225.8, 220.14};
	uint8_t Data[] = {14, 36, 21, 6, 7, 14};

	// Construct Object
	Array_Stats<uint8_t> Data_Array(Data, sizeof(Data) / sizeof(Data[0]));

	// Print Stats
	Serial.println(F("------------------------------------------------"));
	Serial.print(F("Data Array                     : ")); Data_Array.Array();
	Serial.println(F("------------------------------------------------"));
	Serial.print(F("Array Size                     : ")); Serial.println(Data_Array.Size());
	Serial.print(F("Array Sum                      : ")); Serial.println(Data_Array.Sum());
	Serial.print(F("Array Min                      : ")); Serial.println(Data_Array.Min());
	Serial.print(F("Array Max                      : ")); Serial.println(Data_Array.Max());
	Serial.print(F("Array Square Sum               : ")); Serial.println(Data_Array.Sq_Sum());
	Serial.print(F("Array Arithmetic Average       : ")); Serial.println(Data_Array.Average(Data_Array.Arithmetic_Avg));
	Serial.print(F("Array Geometric Average        : ")); Serial.println(Data_Array.Average(Data_Array.Geometric_Avg));
	Serial.print(F("Array RMS Average              : ")); Serial.println(Data_Array.Average(Data_Array.RMS_Avg));
	Serial.print(F("Array Extended RMS Average     : ")); Serial.println(Data_Array.Average(Data_Array.Ext_RMS_Avg));
	Serial.print(F("Array Q1                       : ")); Serial.println(Data_Array.Quartile(1));
	Serial.print(F("Array Q2 (Median)              : ")); Serial.println(Data_Array.Quartile(2));
	Serial.print(F("Array Q3                       : ")); Serial.println(Data_Array.Quartile(3));
	Serial.print(F("Array IQR                      : ")); Serial.println(Data_Array.IQR());
	Serial.print(F("Array Standard Deviation       : ")); Serial.println(Data_Array.Standard_Deviation());
	Serial.print(F("Array Standard Deviation Error : ")); Serial.println(Data_Array.Standard_Deviation_Error());
	Serial.print(F("Array Coefficient Factor       : ")); Serial.println(Data_Array.Coefficient_Factor());
	Serial.print(F("Array Variance                 : ")); Serial.println(Data_Array.Variance());
	Serial.println(F("------------------------------------------------"));
	Serial.print(F("Sorted Data Array              : ")); Data_Array.Array();

	// Loop Delay
	delay(5000);

}

