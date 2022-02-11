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

void Statistical::Array_Statistic(float _Data[], int _Data_Count, int _AVG_Type) {

	// Calculate Array Total
	Array_Total(_Data, _Data_Count);

	// Calculate Square Array Total
	Array_Sq_Total(_Data, _Data_Count);

	// Calculate Array Max
	Array_Maximum(_Data, _Data_Count);

	// Calculate Array Min
	Array_Minimum(_Data, _Data_Count);

	// Calculate Array Aritmetic Average
	Array_Aritmetic_Average(_Data, _Data_Count);

	// Calculate Array Geometric Average
	Array_Geometric_Average(_Data, _Data_Count);

	// Calculate Array Standart Deviation
	Array_Standart_Deviation(_Data, _Data_Count);

	// Calculate Array Standart Deviation Error
	Array_Standart_Deviation_Error(_Data, _Data_Count);

	// Calculate Array Coefficient Factor
	Array_Coefficient_Factor(_Data, _Data_Count);

	// Calculate Array Bubble Sort
	Array_Bubble_Sort(_Data, _Data_Count);

	// Calculate Array Median
	Array_Median(_Data, _Data_Count);

	// Calculate Array RMS Average
	Array_RMS_Average(_Data, _Data_Count);

	// Calculate Array Extended RMS Average
	Array_Ext_RMS_Average(_Data, _Data_Count);
		
}
void Statistical::Array_Total(float _Data[], uint16_t _Data_Count) {

	// Calculate Array Max Value
	for (int i=0; i < _Data_Count; i++) {
		
		Array_Sum += float(_Data[i]);
		
	}

}
void Statistical::Array_Sq_Total(float _Data[], uint16_t _Data_Count) {

	// Calculate Array Square Total
	for (int i=0; i < _Data_Count; i++) {
		
		Array_Sq_Sum += sq(float(_Data[i]));
		
	}

}
void Statistical::Array_Maximum(float _Data[], uint16_t _Data_Count) {

	// Set Maximum Variable
	Array_Max = float(_Data[0]);

	// Calculate Array Max Value
	for (int i=0; i < _Data_Count; i++) {
		
		if (float(_Data[i]) > Array_Max) Array_Max = float(_Data[i]);
		
	}

}
void Statistical::Array_Minimum(float _Data[], uint16_t _Data_Count) {

	// Set Minimum Variable
	Array_Min = float(_Data[0]);

	// Calculate Array Min Value
	for (int i=0; i < _Data_Count; i++) {
		
		if (float(_Data[i]) < Array_Min) Array_Min = float(_Data[i]);
		
	}

}
void Statistical::Array_Aritmetic_Average(float _Data[], uint16_t _Data_Count) {

	// Calculate Array Sum
	Array_Total(_Data, _Data_Count);

	// Calculate Aritmetic Average
	Array_AAvg = Array_Sum / _Data_Count;

}
void Statistical::Array_Geometric_Average(float _Data[], uint16_t _Data_Count) {

	// Set Geometric Average Variable
	float _GAvg = 0;

	// Calculate Geometric Average Value
	for (int i=0; i < _Data_Count; i++) {
		
		_GAvg += (log(_Data[i]) - _GAvg) / (i + 1);
		
	}
	
	// Set Geometric Average Variable
	Array_GAvg = exp(_GAvg);

}
void Statistical::Array_Standart_Deviation(float _Data[], uint16_t _Data_Count) {

	// Calculate Array Sum
	Array_Total(_Data, _Data_Count);

	// Calculate Aritmetic Average
	float _Avg = Array_Sum / _Data_Count;

	// Set Standart Deviation Variable
	float _SDev = 0;

	// Calculate Array Standart Deviation
	for (int i=0; i < _Data_Count; i++) {
		
		_SDev += sq(_Data[i] - _Avg);
				  		
	}
	_SDev = sqrt(_SDev / (_Data_Count-1));

	// Calculate Aritmetic Average
	Array_AAvg = _Avg;

	// Set Result
	Array_SDev = _SDev;

}
void Statistical::Array_Standart_Deviation_Error(float _Data[], uint16_t _Data_Count) {

	// Calculate Standart Deviation
	Array_Standart_Deviation(_Data, _Data_Count);

	// Calculate Standart Deviation Error
	Array_SDev_Err = (Array_SDev / sqrt(float(_Data_Count)));

}
void Statistical::Array_Coefficient_Factor(float _Data[], uint16_t _Data_Count) {

	// Calculate Array Sum
	Array_Total(_Data, _Data_Count);

	// Calculate Aritmetic Average
	float _Avg = Array_Sum / _Data_Count;

	// Calculate Standart Deviation
	Array_Standart_Deviation(_Data, _Data_Count);

	// Calculate Coefficient Factor
	Array_Coef = (100 * Array_SDev / _Avg);

}
void Statistical::Array_Bubble_Sort(float _Data[], uint16_t _Data_Count) {

	// Declare Buffer Variables
	uint16_t _New_n;
	uint16_t _n = _Data_Count;
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

	} while (_n > 1);

}
void Statistical::Array_Median(float _Data[], uint16_t _Data_Count) {

	// Sort Array
	Array_Bubble_Sort(_Data, _Data_Count);

	// Calculate Median
	if (_Data_Count % 2 == 0) {
		
		Array_Med = _Data[_Data_Count / 2];

	} else {

		Array_Med = ((_Data[_Data_Count / 2] - 1) + _Data[_Data_Count / 2]) / 2;

	}

}
void Statistical::Array_RMS_Average(float _Data[], uint16_t _Data_Count) {

	// Calculate Array Sq Total
	Array_Sq_Total(_Data, _Data_Count);

	// Calculate RSM Average
	Array_RMS_Avg = (sqrt(Array_Sq_Sum / _Data_Count));

}
void Statistical::Array_Ext_RMS_Average(float _Data[], uint16_t _Data_Count) {

	// Calculate Array Sq Total
	Array_Sq_Total(_Data, _Data_Count);

	// Calculate Array Minimum
	Array_Minimum(_Data, _Data_Count);

	// Calculate Array Minimum
	Array_Maximum(_Data, _Data_Count);

	// Calculate Extended Sum
	Array_Sq_Sum -= sq(Array_Min);
	Array_Sq_Sum -= sq(Array_Max);

	// Calculate RSM Average
	Array_Ext_RMS_Avg = (sqrt(Array_Sq_Sum / _Data_Count));

}
void Statistical::Array_Statistic_Clear(void) {

	// Clear Global Variables
	Array_Sum = 0;
	Array_Sq_Sum = 0;
	Array_Min = 0;
	Array_Max = 0;
	Array_AAvg = 0;
	Array_GAvg = 0;
	Array_RMS_Avg = 0;
	Array_Ext_RMS_Avg = 0;
	Array_Med = 0;
	Array_SDev = 0;
	Array_SDev_Err = 0;
	Array_Coef = 0;
		
}

float Statistical::Array_Average(float _Data[], int _Data_Count, int _AVG_Type) {

	if (_AVG_Type == 1) {Array_Aritmetic_Average(_Data, _Data_Count); return(Array_AAvg);}
	if (_AVG_Type == 2) {Array_Geometric_Average(_Data, _Data_Count); return(Array_GAvg);}
	if (_AVG_Type == 3) {Array_Median(_Data, _Data_Count); return(Array_Med);}
	if (_AVG_Type == 4) {Array_RMS_Average(_Data, _Data_Count); return(Array_RMS_Avg);}
	if (_AVG_Type == 5) {Array_Ext_RMS_Average(_Data, _Data_Count); return(Array_Ext_RMS_Avg);}
			
}


Statistical Stats;
