/* *******************************************************************************
 *  Copyright (C) 2014-2022 Mehmet Gunce Akkoyun Can not be copied and/or
 *	distributed without the express permission of Mehmet Gunce Akkoyun.
 *
 *	Library				: Data Statistical Library
 *	Code Developer		: Mehmet Gunce Akkoyun (akkoyun@me.com)
 *********************************************************************************/

#include "Statistical.h"

// Stream Statistics
void Statistical::Stream_Statistic(float _Data) {

	// Set Data Count (+1)
	Stream_Data_Count++;

	// Calculate Max Value
	if (Stream_Maximum == 0) Stream_Maximum = _Data;
	if (_Data > Stream_Maximum) Stream_Maximum = _Data;

	// Calculate Min Value
	if (Stream_Minimum == 0) Stream_Minimum = _Data;
	if (_Data < Stream_Minimum) Stream_Minimum = _Data;

	// Calculate Avg Value
	if (Stream_Average == 0) Stream_Average = _Data;
	Stream_Average = Stream_Average + ((_Data - Stream_Average) / Stream_Data_Count);

}
void Statistical::Stream_Data_Clear(void) {

	// Clear Data Count
	Stream_Data_Count = 0;

	// Celar Stream Variables
	Stream_Average = 0;
	Stream_Maximum = 0;
	Stream_Minimum = 0;

}

// Linear Regression Statistics
float Statistical::Linear_Regression_Offset(float _Data[][2], uint16_t _Data_Count) {

	// Declare Variables
	float _X[_Data_Count];
	float _Y[_Data_Count];
	float _Sum_X = 0;
	float _Sum_Y = 0;
	float _Sum_X2 = 0;
	float _Sum_XY = 0;
	float _b0 = 0;

	// Set X and Y Array
	for (uint16_t i = 0; i < _Data_Count; i++) {

		// Set X
		_X[i] = _Data[i][0];

		// Set Y
		_Y[i] = _Data[i][1];

	}

	// Calculate Sum X
	_Sum_X = Array_Sum(_X, _Data_Count);

	// Calculate Sum Y
	_Sum_Y = Array_Sum(_Y, _Data_Count);

	// Calculate Sum xy
	for (uint16_t i = 0; i < _Data_Count; i++) {

		// Set Sum xy
		_Sum_XY += _X[i] * _Y[i];

	}

	// Calculate Sum X2
	_Sum_X2 = Array_Sq_Sum(_X, _Data_Count);

	// Calculate Slope
	_b0 = ((_Sum_X2 * _Sum_Y) - (_Sum_X * _Sum_XY)) / ((_Data_Count * _Sum_X2) - (_Sum_X * _Sum_X));

	// End Function
	return(_b0);

}
float Statistical::Linear_Regression_Slope(float _Data[][2], uint16_t _Data_Count) {

	// Declare Variables
	float _X[_Data_Count];
	float _Y[_Data_Count];
	float _Sum_X = 0;
	float _Sum_Y = 0;
	float _Sum_XY = 0;
	float _Sum_X2 = 0;
	float _b1 = 0;

	// Set X and Y Array
	for (uint16_t i = 0; i < _Data_Count; i++) {

		// Set X
		_X[i] = _Data[i][0];

		// Set Y
		_Y[i] = _Data[i][1];

	}

	// Calculate Sum X
	_Sum_X = Array_Sum(_X, _Data_Count);

	// Calculate Sum Y
	_Sum_Y = Array_Sum(_Y, _Data_Count);

	// Calculate Sum xy
	for (uint16_t i = 0; i < _Data_Count; i++) {

		// Set Sum xy
		_Sum_XY += _X[i] * _Y[i];

	}

	// Calculate Sum X2
	_Sum_X2 = Array_Sq_Sum(_X, _Data_Count);

	// Calculate Slope
	_b1 = ((_Data_Count * _Sum_XY) - (_Sum_X * _Sum_Y)) / ((_Data_Count * _Sum_X2) - (_Sum_X * _Sum_X));

	// End Function
	return(_b1);

}
float Statistical::Linear_Regression_R2(float _Data[][2], uint16_t _Data_Count) {

	// Declare Variables
	float _X[_Data_Count];
	float _Y[_Data_Count];
	float _Mean_X;
	float _Mean_Y;
	float _x[_Data_Count]; // x = X - Xavg
	float _y[_Data_Count]; // y = Y - Yavg
	float _Sum_xy;
	float _Sum_x2;
	float _Sum_y2;
	float _R2;

	// Set X and Y Array
	for (uint16_t i = 0; i < _Data_Count; i++) {

		// Set X
		_X[i] = _Data[i][0];

		// Set Y
		_Y[i] = _Data[i][1];

	}

	// Calculate Mean X
	_Mean_X = Array_Arithmetic_Average(_X, _Data_Count);

	// Calculate Mean Y
	_Mean_Y = Array_Arithmetic_Average(_Y, _Data_Count);

	// Set x and y Array
	for (uint16_t i = 0; i < _Data_Count; i++) {

		// Set x
		_x[i] = _X[i] - _Mean_X;

		// Set y
		_y[i] = _Y[i] - _Mean_Y;

	}

	// Calculate Sum xy
	for (uint16_t i = 0; i < _Data_Count; i++) {

		// Set Sum xy
		_Sum_xy += _x[i] * _y[i];

	}

	// Calculate Sum x2
	for (uint16_t i = 0; i < _Data_Count; i++) {

		// Set Sum x2
		_Sum_x2 += _x[i] * _x[i];

	}

	// Calculate Sum y2
	for (uint16_t i = 0; i < _Data_Count; i++) {

		// Set Sum y2
		_Sum_y2 += _y[i] * _y[i];

	}

	// Calculate R2
	_R2 = (_Sum_xy * _Sum_xy) / (_Sum_x2 * _Sum_y2);

	// End Function
	return(_R2);

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