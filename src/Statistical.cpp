/* *******************************************************************************
 *  Copyright (C) 2014-2022 Mehmet Gunce Akkoyun Can not be copied and/or
 *	distributed without the express permission of Mehmet Gunce Akkoyun.
 *
 *	Library				: Data Statistical Library
 *	Code Developer		: Mehmet Gunce Akkoyun (akkoyun@me.com)
 *********************************************************************************/

#include "Statistical.h"

// Stream Statistics
float Statistical::Stream_Max(float _Data) {

	// Increase Data Count Variable
	Stream_Data_Count_Max++;

	// Calculate Max Value
	if (Stream_Maximum == 0) Stream_Maximum = _Data;
	if (_Data > Stream_Maximum) Stream_Maximum = _Data;

	// End Function
	return(Stream_Maximum);

}
void Statistical::Stream_Clear_Max(void) {

	// Celar Stream Variables
	Stream_Data_Count_Max = 0;
	Stream_Maximum = 0;

}
float Statistical::Stream_Min(float _Data) {

	// Increase Data Count Variable
	Stream_Data_Count_Min++;

	// Calculate Min Value
	if (Stream_Minimum == 0) Stream_Minimum = _Data;
	if (_Data < Stream_Minimum) Stream_Minimum = _Data;

	// End Function
	return(Stream_Minimum);

}
void Statistical::Stream_Clear_Min(void) {

	// Celar Stream Variables
	Stream_Data_Count_Min = 0;
	Stream_Minimum = 0;

}
float Statistical::Stream_Aritmetic_Average(float _Data) {

	// Increase Data Count Variable
	Stream_Data_Count_Avg++;

	// Calculate Avg Value
	if (Stream_Average == 0) Stream_Average = _Data;
	Stream_Average = Stream_Average + ((_Data - Stream_Average) / Stream_Data_Count_Avg);

	// End Function
	return(Stream_Average);

}
void Statistical::Stream_Clear_Aritmetic_Average(void) {

	// Celar Stream Variables
	Stream_Data_Count_Avg = 0;
	Stream_Average = 0;

}
void Statistical::Stream_Statistic(float _Data) {

	// Calculate Maximum
	Stream_Max(_Data);

	// Calculate Minimum
	Stream_Min(_Data);

	// Calculate Average
	Stream_Aritmetic_Average(_Data);

}
void Statistical::Stream_Clear(void) {

	// Celar Stream Variables
	Stream_Data_Count_Max = 0;
	Stream_Maximum = 0;
	Stream_Data_Count_Min = 0;
	Stream_Minimum = 0;
	Stream_Data_Count_Avg = 0;
	Stream_Average = 0;

}

// Linear Regression Statistics
void Statistical::Linear_Regression_Calculate(float _Data[][2]) {

	// Calculate array regression
	for (uint16_t i = 0; i < Linear_Regression_Precision; i++) {

		// Print Array
		//Serial.print(_Data[i][0]); Serial.print("-"); Serial.println(_Data[i][1]);

		// Push Data
		Linear_Regression(_Data[i][0], _Data[i][1]);

	}

	// Control for valid data
	if (isinf(Linear_Regression_Slope)) Linear_Regression_Slope = 0;
	if (isnan(Linear_Regression_Slope)) Linear_Regression_Slope = 0;

}
void Statistical::Linear_Regression(float _Data_X, float _Data_Y){

	// Increase Data Count Variable
	Linear_Regression_Data_Count++;
	
	// Calculate Mean X
	Linear_Regression_MeanX = Linear_Regression_MeanX + ((_Data_X - Linear_Regression_MeanX) / Linear_Regression_Data_Count);

	// Calculate Mean X Square
	Linear_Regression_MeanX2 = Linear_Regression_MeanX2 + (((_Data_X * _Data_X) - Linear_Regression_MeanX2) / Linear_Regression_Data_Count);
	
	// Calculate Variance X
	Linear_Regression_VarianceX = Linear_Regression_MeanX2 - (Linear_Regression_MeanX * Linear_Regression_MeanX);

	// Calculate Mean Y
	Linear_Regression_MeanY = Linear_Regression_MeanY + ((_Data_Y - Linear_Regression_MeanY) / Linear_Regression_Data_Count);

	// Calculate Mean Y Square
	Linear_Regression_MeanY2 = Linear_Regression_MeanY2 + (((_Data_Y * _Data_Y) - Linear_Regression_MeanY2) / Linear_Regression_Data_Count);
	
	// Calculate Variance Y
	Linear_Regression_VarianceY = Linear_Regression_MeanY2 - (Linear_Regression_MeanY * Linear_Regression_MeanY);

	// Calculate Mean XY
	Linear_Regression_MeanXY = Linear_Regression_MeanXY + (((_Data_X * _Data_Y) - Linear_Regression_MeanXY) / Linear_Regression_Data_Count);

	// Calculate Covariance XY
	Linear_Regression_CovarianceXY = Linear_Regression_MeanXY - (Linear_Regression_MeanX * Linear_Regression_MeanY);

	// Calculate a
	Linear_Regression_Slope = Linear_Regression_CovarianceXY / Linear_Regression_VarianceX;
	
	// Calculate b
	Linear_Regression_Offset = Linear_Regression_MeanY - (Linear_Regression_Slope * Linear_Regression_MeanX);
	
}
void Statistical::Linear_Regression_Data_Clear(void) {

	// Clear Regression Variables
	Linear_Regression_Data_Count = 0;
	Linear_Regression_MeanX = 0;
	Linear_Regression_MeanX2 = 0;
	Linear_Regression_VarianceX = 0;
	Linear_Regression_MeanY = 0;
	Linear_Regression_MeanY2 = 0;
	Linear_Regression_MeanXY = 0;
	Linear_Regression_VarianceY = 0;
	Linear_Regression_CovarianceXY = 0;
	Linear_Regression_Slope = 0;
	Linear_Regression_Offset	= 0;

}

// Array Statistics
float Statistical::Array_Sum(float _Data[], uint16_t _Data_Count) {

	// Declare Variable
	float _Sum = 0;

	// Calculate Array Sum
	for (uint16_t i=0; i < _Data_Count; i++) {

		_Sum += (float)_Data[i];

	} 

	// End Function
	return(_Sum);

}
float Statistical::Array_Max(float _Data[], uint16_t _Data_Count) {

	// Declare Variable
	float _Max = (float)_Data[0];

	// Calculate Array Max Value
	for (uint16_t i=0; i < _Data_Count; i++) {
		
		if ((float)_Data[i] > _Max) _Max = (float)_Data[i];
		
	}

	// End Function
	return(_Max);

}
float Statistical::Array_Min(float _Data[], uint16_t _Data_Count) {

	// Declare Variable
	float _Min = (float)_Data[0];

	// Calculate Array Min Value
	for (uint16_t i=0; i < _Data_Count; i++) {
		
		if ((float)_Data[i] < _Min) _Min = (float)_Data[i];
		
	}

	// End Function
	return(_Min);

}
float Statistical::Array_Sq_Sum(float _Data[], uint16_t _Data_Count) {

	// Declare Variable
	float _Sq_Sum = 0;

	// Calculate Array Square Total
	for (uint16_t i=0; i < _Data_Count; i++) {
		
		_Sq_Sum += sq((float)_Data[i]);
		
	}

	// End Function
	return(_Sq_Sum);

}
float Statistical::Array_Arithmetic_Average(float _Data[], uint16_t _Data_Count) {

	// Declare Variable
	float _Sum = 0;

	// Calculate Array Sum
	_Sum = Array_Sum(_Data, _Data_Count);

	// Calculate Arithmetic Average
	float _Average = _Sum / _Data_Count;

	// End Function
	return(_Average);

}
float Statistical::Array_Geometric_Average(float _Data[], uint16_t _Data_Count) {

	// Declare Variable
	float _GAvg_Sum = 0;

	// Calculate Geometric Average Value
	for (uint16_t i=0; i < _Data_Count; i++) {
		
		_GAvg_Sum += (log(_Data[i]) - _GAvg_Sum) / (i + 1);
		
	}
	
	// Set Geometric Average Variable
	float _GAvg = exp(_GAvg_Sum);

	// End Function
	return(_GAvg);

}
float Statistical::Array_RMS_Average(float _Data[], uint16_t _Data_Count) {

	// Calculate Array Sq Total
	float _Sum = Array_Sq_Sum(_Data, _Data_Count);

	// Calculate RSM Average
	float _RMS_Avg = (sqrt(_Sum / _Data_Count));

	// End Function
	return(_RMS_Avg);

}
float Statistical::Array_Ext_RMS_Average(float _Data[], uint16_t _Data_Count) {

	// Calculate Array Sq Total
	float _Sum = Array_Sq_Sum(_Data, _Data_Count);

	// Calculate Array Minimum
	float _Min = Array_Min(_Data, _Data_Count);

	// Calculate Array Minimum
	float _Max = Array_Max(_Data, _Data_Count);

	// Calculate Extended Sum
	_Sum -= sq(_Min);
	_Sum -= sq(_Max);

	// Calculate RSM Average
	float _Ext_RMS_Avg = (sqrt(_Sum / _Data_Count));

	// End Function
	return(_Ext_RMS_Avg);

}
float Statistical::Array_Median(float _Data[], uint16_t _Data_Count) {

	// Sort Array
	Array_Bubble_Sort(_Data, _Data_Count);

	// Declare Variable
	float _Median = 0;

	// Calculate Median
	if (_Data_Count % 2 == 0) {
		
		_Median = _Data[_Data_Count / 2];

	} else {

		_Median = ((_Data[_Data_Count / 2] - 1) + _Data[_Data_Count / 2]) / 2;

	}

	// End Function
	return(_Median);

}
float Statistical::Array_Standard_Deviation(float _Data[], uint16_t _Data_Count) {

	// Calculate Arithmetic Average
	float _Avg = Array_Arithmetic_Average(_Data, _Data_Count);

	// Set Standard Deviation Variable
	float _SDev = 0;

	// Calculate Array Standard Deviation
	for (uint16_t i=0; i < _Data_Count; i++) _SDev += sq(_Data[i] - _Avg);
	_SDev = sqrt(_SDev / (_Data_Count - 1));

	// End Function
	return(_SDev);

}
float Statistical::Array_Standard_Deviation_Error(float _Data[], uint16_t _Data_Count) {

	// Calculate Standard Deviation
	float _SDev = Array_Standard_Deviation(_Data, _Data_Count);

	// Calculate Standard Deviation Error
	float _SDev_Err = (_SDev / sqrt((float)_Data_Count));

	// End Function
	return(_SDev_Err);

}
float Statistical::Array_Coefficient_Factor(float _Data[], uint16_t _Data_Count) {

	// Calculate Arithmetic Average
	float _Avg = Array_Arithmetic_Average(_Data, _Data_Count);

	// Calculate Standard Deviation
	float _SDev = Array_Standard_Deviation(_Data, _Data_Count);

	// Calculate Coefficient Factor
	float _Coef = (100 * _SDev / _Avg);

	// End Function
	return(_Coef);

}
float Statistical::Array_Average(float _Data[], int _Data_Count, int _AVG_Type) {

	// Select Average Type
	switch (_AVG_Type) {
		
		case 1:
			return(Array_Arithmetic_Average(_Data, _Data_Count));
    		break;
  
  		case 2:
    		return(Array_Geometric_Average(_Data, _Data_Count));
    		break;

  		case 3:
    		return(Array_Median(_Data, _Data_Count));
    		break;

  		case 4:
    		return(Array_RMS_Average(_Data, _Data_Count));
    		break;

  		case 5:
    		return(Array_Ext_RMS_Average(_Data, _Data_Count));
    		break;

  		default:
    		return(0);
    		break;
	}

}

// Array Misc Functions
void Statistical::Array_Bubble_Sort(float _Data[], uint16_t _Data_Count) {

	// Declare Buffer Variables
	uint16_t _New_n;
	float _Temp = 0;

	// Sort Array
	do {

		_New_n = 1;

		for (uint16_t i=1; i < _Data_Count; i++) {

			if(_Data[i - 1]>_Data[i]){
				
				_Temp = _Data[i];
				
				_Data[i]=_Data[i - 1];
				
				_Data[i - 1] = _Temp;
				
				_New_n = i;

			} //end if

		}

	} while (_New_n > 1);

}
void Statistical::Array_FILO(float _Array[][2], uint16_t _Data_Count, float _Data_X, float _Data_Y) {
	

	// Redesign Array
	for (uint16_t i = 0; i < _Data_Count-1; i++) {
	
		_Array[i][0] = _Array[i+1][0];
		_Array[i][1] = _Array[i+1][1];
	
	}
	
	// Add New Data
	_Array[_Data_Count-1][0] = _Data_X;
	_Array[_Data_Count-1][1] = _Data_Y;

}

Statistical Stats;