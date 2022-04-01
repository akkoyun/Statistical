// Include Statistal Library
#include <Statistical.h>


// Set Data
float Data[5];

// Construct Object
Array_Stats Data_Array(Data, 1);


void setup() {

	// Start Serial
    Serial.begin(115200);

	// Set Data
	Serial.println(F("Learning Data..."));

    // Set FILO
    Data_Array.Set_FILO_Size(4);

    // Add Data to FILO Array
    Data_Array.FILO_Add_Data(220.12);
    Data_Array.FILO_Add_Data(214.35);
    Data_Array.FILO_Add_Data(200.14);
    Data_Array.FILO_Add_Data(212.80);
    Data_Array.FILO_Add_Data(242.33);
    Data_Array.FILO_Add_Data(215.99);
    Data_Array.FILO_Add_Data(220.12);

	// Print Stats
	Serial.println(F("------------------------------------------------"));
	Serial.print(F("Array Size                     : ")); Serial.println(Data_Array.Size());
	Serial.println(F("------------------------------------------------"));
	Serial.print(F("Data Array                     : ")); Data_Array.Array();
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

}

void loop() {


}

