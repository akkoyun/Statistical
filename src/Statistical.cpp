/* *******************************************************************************
 *  Copyright (C) 2014-2021 Mehmet Gunce Akkoyun Can not be copied and/or
 *	distributed without the express permission of Mehmet Gunce Akkoyun.
 *
 *	Library				: Data Stream Statistical Library
 *	Code Developer		: Mehmet Gunce Akkoyun (akkoyun@me.com)
 *	Revision			: 01.01.02
 *
 *********************************************************************************/

#include "Statistical.h"

void Statistical::Stream_Statistic(float _Data) {

	// Set Data Count (+1)
	Data_Count++;

	// Calculate Max Value
	if (Stream_Maximum == 0) Stream_Maximum = _Data;
	if (_Data > Stream_Maximum) Stream_Maximum = _Data;

	// Calculate Min Value
	if (Stream_Minimum == 0) Stream_Minimum = _Data;
	if (_Data < Stream_Minimum) Stream_Minimum = _Data;

	// Calculate Avg Value
	if (Stream_Average == 0) Stream_Average = _Data;
	Stream_Average = Stream_Average + ((_Data - Stream_Average) / Data_Count);

}
void Statistical::Array_Statistic(float _Data[], int _Data_Count, int _AVG_Type) {

	// Calculate Array Max
	float _Max = float(_Data[0]);
	for (int i=0; i < _Data_Count; i++) {
		
		if (_Data[i] > _Max) _Max = float(_Data[i]);
		
	}
	Array_Maximum = _Max;
	
	// Calculate Array Min
	float _Min = float(_Data[0]);
	for (int i=0; i < _Data_Count; i++) {
		
		if (float(_Data[i]) < _Min) _Min = float(_Data[i]);
		
	}
	Array_Minimum = _Min;

	// Calculate Array Average
	float _Avg = 0;
	for (int i=0; i < _Data_Count; i++) {
		
		_Avg += float(_Data[i]);
		
	}
	_Avg /= _Data_Count;

	// Calculate Array Standart Deviation
	float _SDev = 0;
	for (int i=0; i < _Data_Count; i++) {
		
		_SDev += sq(_Data[i] - _Avg);
				  		
	}
	_SDev = sqrt(_SDev/(_Data_Count-1));
	Array_SDev = _SDev;

	// Define Calculation Variables
	float _Data_Sum = 0;
	int _Valid_Data_Count = 0;
	int _Sigma_1_Count = 0;

	// Calculate Average Data
	for (int Calculation_ID = 0; Calculation_ID < _Data_Count; Calculation_ID++) {
	 
		// Calculate RMS/EXRMS Average
		if (_AVG_Type == 2 or _AVG_Type == 3) {
			
			// Calculate Sum
			_Data_Sum += sq(float(_Data[Calculation_ID]));
			
			// Calculate Valid Data Count
			_Valid_Data_Count++;
			
		}
		
		// Calulate Sigma1 Average
		if (_AVG_Type == 5) {
			
			float _Sigma_1_Max = _Avg + _SDev;
			float _Sigma_1_Min = _Avg - _SDev;
			
			if (_Data[Calculation_ID] >= _Sigma_1_Min and _Data[Calculation_ID] <= _Sigma_1_Max) {
				
				// Calculate Sum
				_Data_Sum += sq(_Data[Calculation_ID]);
				
				// Calculate Valid Data Count
				_Valid_Data_Count++;
				
			}
			
		}
	
	}

	// Control for Valid Data
	if (_AVG_Type != 1 and _AVG_Type != 4 and _Valid_Data_Count < 1) Array_Average = 0;

	// Calculate Average
	if (_AVG_Type == 1) {
		
		// Calculate Average
		Array_Average = _Avg;
		
	}	// Standart Average
	if (_AVG_Type == 2) {
		
		// Calculate Average
		Array_Average = (sqrt(_Data_Sum / _Valid_Data_Count));

	}	// RMS Average
	if (_AVG_Type == 3) {
		
		// Eleminate Max Value
		_Data_Sum -= (_Max * _Max);
		
		// Eleminate Min Value
		_Data_Sum -= (_Min * _Min);
		
		// Eleminate Min/Max Valid Data Count
		_Valid_Data_Count -= 2;
		
		// Calculate Average
		Array_Average = (sqrt(_Data_Sum / _Valid_Data_Count));

	}	// Extendet RMS Average
	if (_AVG_Type == 4) {
		
		// Calculate Average
		Array_Average = ((_Max + _Min) / 2);
		
	}	// Median Average
	if (_AVG_Type == 5) {
		
		// Calculate Average
		Array_Average = (sqrt(_Data_Sum / _Valid_Data_Count));
		
	}	// Sigma1RMS Average
		
}
void Statistical::LinearRegression(float _X, float _Y){

	// Increase Data Count Variable
	Data_Count++;
	
	// Calculate Mean X
	Linear_Regression_MeanX = Linear_Regression_MeanX + ((_X - Linear_Regression_MeanX) / Data_Count);

	// Calculate Mean X Square
	Linear_Regression_MeanX2 = Linear_Regression_MeanX2 + (((_X * _X) - Linear_Regression_MeanX2) / Data_Count);
	
	// Calculate Variance X
	Linear_Regression_VarianceX = Linear_Regression_MeanX2 - (Linear_Regression_MeanX * Linear_Regression_MeanX);

	// Calculate Mean Y
	Linear_Regression_MeanY = Linear_Regression_MeanY + ((_Y - Linear_Regression_MeanY) / Data_Count);

	// Calculate Mean Y Square
	Linear_Regression_MeanY2 = Linear_Regression_MeanY2 + (((_Y * _Y) - Linear_Regression_MeanY2) / Data_Count);
	
	// Calculate Variance Y
	Linear_Regression_VarianceY = Linear_Regression_MeanY2 - (Linear_Regression_MeanY * Linear_Regression_MeanY);

	// Calculate Mean XY
	Linear_Regression_MeanXY = Linear_Regression_MeanXY + (((_X * _Y) - Linear_Regression_MeanXY) / Data_Count);

	// Calculate Covariance XY
	Linear_Regression_CovarianceXY = Linear_Regression_MeanXY - (Linear_Regression_MeanX * Linear_Regression_MeanY);

	// Calculate a
	Linear_Regression_a = Linear_Regression_CovarianceXY / Linear_Regression_VarianceX;
	
	// Calculate b
	Linear_Regression_b = Linear_Regression_MeanY - (Linear_Regression_a * Linear_Regression_MeanX);
	
}
void Statistical::Data_Clear(void) {

	// Clear Data Count
	Data_Count = 0;

	// Celar Stream Variables
	Stream_Average = 0;
	Stream_Maximum = 0;
	Stream_Minimum = 0;

	// Clear Regression Variables
	Linear_Regression_MeanX = 0;
	Linear_Regression_MeanX2 = 0;
	Linear_Regression_VarianceX = 0;
	Linear_Regression_MeanY = 0;
	Linear_Regression_MeanY2 = 0;
	Linear_Regression_MeanXY = 0;
	Linear_Regression_VarianceY = 0;
	Linear_Regression_CovarianceXY = 0;
	Linear_Regression_a = 0;
	Linear_Regression_b	= 0;

	
}

Statistical Stats;
