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

// Array Statistics

float Statistical::Array_Sum(float _Data[], uint16_t _Data_Count) {

	// Declare Variable
	float _Sum = 0;

	// Calculate Array Sum
	for (uint16_t i=0; i < _Data_Count; i++) {

		_Sum += (float)_Data[i];

	} 

	// End Function
	return(_Sum)

}
float Statistical::Array_Max(float _Data[], uint16_t _Data_Count) {

	// Declare Variable
	float _Max = (float)_Data[0];

	// Calculate Array Max Value
	for (uint16_t i=0; i < _Data_Count; i++) {
		
		if ((float)_Data[i] > _Max) _Max = (float)_Data[i];
		
	}

	// End Function
	return(_Max)

}
float Statistical::Array_Min(float _Data[], uint16_t _Data_Count) {

	// Declare Variable
	float _Min = (float)_Data[0];

	// Calculate Array Min Value
	for (uint16_t i=0; i < _Data_Count; i++) {
		
		if ((float)_Data[i] < _Min) _Min = (float)_Data[i];
		
	}

	// End Function
	return(_Min)

}
float Statistical::Array_Sq_Sum(float _Data[], uint16_t _Data_Count) {

	// Declare Variable
	float _Sq_Sum = 0;

	// Calculate Array Square Total
	for (uint16_t i=0; i < _Data_Count; i++) {
		
		_Sq_Sum += sq((float)_Data[i]);
		
	}

	// End Function
	return(_Sq_Sum)

}
float Statistical::Array_Aritmetic_Average(float _Data[], uint16_t _Data_Count) {

	// Declare Variable
	float _Sum = 0;

	// Calculate Array Sum
	_Sum = Array_Sum(_Data, _Data_Count);

	// Calculate Aritmetic Average
	float _Average = _Sum / _Data_Count;

	// End Function
	return(_Average)

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
	return(_GAvg)

}
float Statistical::Array_RMS_Average(float _Data[], uint16_t _Data_Count) {

	// Calculate Array Sq Total
	float _Sum = Array_Sq_Sum(_Data, _Data_Count);

	// Calculate RSM Average
	float _RMS_Avg = (sqrt(Array_Sq_Sum / _Data_Count));

	// End Function
	return(_RMS_Avg)

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
	return(_Ext_RMS_Avg)

}
void Statistical::Array_Bubble_Sort(float _Data[], uint16_t _Data_Count) {

	// Declare Buffer Variables
	uint16_t _New_n;
	float _Temp = 0;

	// Sort Array
	do {

		_New_n = 1;

		for (int i=1; i < _Data_Count; i++) {

			if(_Data[i - 1]>_Data[i]){
				
				_Temp = _Data[i];
				
				_Data[i]=_Data[i - 1];
				
				_Data[i - 1] = _Temp;
				
				_New_n = i;

			} //end if

		}

	} while (_Data_Count > 1);

}
void Statistical::Array_Median(float _Data[], uint16_t _Data_Count) {

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
	return(_Median)

}
float Statistical::Array_Standart_Deviation(float _Data[], uint16_t _Data_Count) {

	// Calculate Aritmetic Average
	float _Avg = Array_Aritmetic_Average(_Data, _Data_Count);

	// Set Standart Deviation Variable
	float _SDev = 0;

	// Calculate Array Standart Deviation
	for (int i=0; i < _Data_Count; i++) _SDev += sq(_Data[i] - _Avg);
	_SDev = sqrt(_SDev / (_Data_Count - 1));

	// End Function
	return(_SDev);

}
float Statistical::Array_Standart_Deviation_Error(float _Data[], uint16_t _Data_Count) {

	// Calculate Standart Deviation
	float _SDev = Array_Standart_Deviation(_Data, _Data_Count);

	// Calculate Standart Deviation Error
	float _SDev_Err = (_SDev / sqrt((float)_Data_Count));

	// End Function
	return(_SDev_Err);

}
float Statistical::Array_Coefficient_Factor(float _Data[], uint16_t _Data_Count) {

	// Calculate Aritmetic Average
	float _Avg = Array_Aritmetic_Average(_Data, _Data_Count);

	// Calculate Standart Deviation
	float _SDev = Array_Standart_Deviation(_Data, _Data_Count);

	// Calculate Coefficient Factor
	float _Coef = (100 * _SDev / _Avg);

	// End Function
	return(_Coef);

}
float Statistical::Array_Average(float _Data[], int _Data_Count, int _AVG_Type) {

	// Select Average Type
	switch (_AVG_Type) {
		
		case 1:
			return(Array_Aritmetic_Average(_Data, _Data_Count));
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

Statistical Stats;