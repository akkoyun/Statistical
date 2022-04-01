/* *******************************************************************************
 *  Copyright (C) 2014-2022 Mehmet Gunce Akkoyun Can not be copied and/or
 *	distributed without the express permission of Mehmet Gunce Akkoyun.
 *
 *	Library				: Data Statistical Library
 *	Code Developer		: Mehmet Gunce Akkoyun (akkoyun@me.com)
 *********************************************************************************/

#include "Statistical.h"

// Array Statistics
Array_Stats::~Array_Stats(void) {

	// Set Class Data Variable
	Data = 0;

	// Set Class Data Count Variable
	Data_Count = 0;

}
float Array_Stats::Average(const uint8_t _Average_Type) {

	// Control for Type Limit
	if (_Average_Type > 4) return(0);
	
	// Declare Variable
	float _Result = 0;

	// Calculate Average
	if (_Average_Type == 1) _Result = this->Arithmetic_Average();
	if (_Average_Type == 2) _Result = this->Geometric_Average();
	if (_Average_Type == 3) _Result = this->RMS_Average();
	if (_Average_Type == 4) _Result = this->Ext_RMS_Average();

	// End Function
	return(_Result);

}
uint16_t Array_Stats::Size(void) {

	// End Function
	return(this->Data_Count);

}
float Array_Stats::Sum(void) {

	// Declare Variable
	float _Sum = 0;

	// Calculate Array Sum
	for (size_t i = 0; i < this->Data_Count; i++) _Sum += (float)this->Data[i];

	// Handle Calculation
	if (isnan(_Sum)) _Sum = 0;
	if (isinf(_Sum)) _Sum = 0;

	// End Function
	return(_Sum);

}
float Array_Stats::Max(void) {

	// Declare Variable
	float _Max = (float)this->Data[0];

	// Calculate Array Max Value
	for (uint16_t i=0; i < this->Data_Count; i++) if ((float)this->Data[i] > _Max) _Max = (float)this->Data[i];

	// Handle Calculation
	if (isnan(_Max)) _Max = 0;
	if (isinf(_Max)) _Max = 0;

	// End Function
	return(_Max);

}
float Array_Stats::Min(void) {

	// Declare Variable
	float _Min = (float)this->Data[0];

	// Calculate Array Min Value
	for (uint16_t i=0; i < this->Data_Count; i++) if ((float)this->Data[i] < _Min) _Min = (float)this->Data[i];

	// Handle Calculation
	if (isnan(_Min)) _Min = 0;
	if (isinf(_Min)) _Min = 0;

	// End Function
	return(_Min);

}
float Array_Stats::Sq_Sum(void) {

	// Declare Variable
	float _Sq_Sum = 0;

	// Calculate Array Square Total
	for (uint16_t i = 0; i < this->Data_Count; i++) _Sq_Sum += sq((float)this->Data[i]);

	// Handle Calculation
	if (isnan(_Sq_Sum)) _Sq_Sum = 0;
	if (isinf(_Sq_Sum)) _Sq_Sum = 0;

	// End Function
	return(_Sq_Sum);

}
float Array_Stats::Arithmetic_Average(void) {

	// Calculate Arithmetic Average
	float _Average = Sum() / this->Data_Count;

	// Handle Calculation
	if (isnan(_Average)) _Average = 0;
	if (isinf(_Average)) _Average = 0;

	// End Function
	return(_Average);

}
float Array_Stats::Geometric_Average(void) {

	// Declare Variable
	float _GAvg_Sum = 0;

	// Calculate Geometric Average Value
	for (size_t i = 0; i < this->Data_Count; i++) _GAvg_Sum += (log(this->Data[i]) - _GAvg_Sum) / (i + 1);
	
	// Set Geometric Average Variable
	float _GAvg = exp(_GAvg_Sum);

	// Handle Calculation
	if (isnan(_GAvg)) _GAvg = 0;
	if (isinf(_GAvg)) _GAvg = 0;

	// End Function
	return(_GAvg);

}
float Array_Stats::RMS_Average(void) {

	// Calculate Array Sq Total
	float _Sum = Sq_Sum();

	// Calculate RSM Average
	float _RMS_Avg = (sqrt(_Sum / this->Data_Count));

	// Handle Calculation
	if (isnan(_RMS_Avg)) _RMS_Avg = 0;
	if (isinf(_RMS_Avg)) _RMS_Avg = 0;

	// End Function
	return(_RMS_Avg);

}
float Array_Stats::Ext_RMS_Average(void) {

	// Calculate Array Sq Total
	float _Sum = Sq_Sum();

	// Calculate Extended Sum
	_Sum -= sq(Min());
	_Sum -= sq(Max());

	// Calculate RSM Average
	float _Ext_RMS_Avg = (sqrt(_Sum / this->Data_Count));

	// Handle Calculation
	if (isnan(_Ext_RMS_Avg)) _Ext_RMS_Avg = 0;
	if (isinf(_Ext_RMS_Avg)) _Ext_RMS_Avg = 0;

	// End Function
	return(_Ext_RMS_Avg);

}
float Array_Stats::Quartile(const uint8_t _Q) {

	// Sort Array
	Bubble_Sort();

	// Declare Variable
	float _Quartile = 0;
	float _Multiplier = 0;

	// Decide Q Multiplier
	if (_Q == 1) _Multiplier = 0.25;
	if (_Q == 2) _Multiplier = 0.50;
	if (_Q == 3) _Multiplier = 0.75;

	// Calculate Quartile Position
	float _Position = ((this->Data_Count + 1) * _Multiplier);

	// Calculate Quartile
	_Quartile = this->Data[(int)_Position - 1] + ((_Position - (int)_Position) * (this->Data[(int)_Position] - this->Data[(int)_Position - 1]));

	// Handle Calculation
	if (isnan(_Quartile)) _Quartile = 0;
	if (isinf(_Quartile)) _Quartile = 0;

	// End Function
	return(_Quartile);

}
float Array_Stats::IQR(void) {

	// Calculate Q1
	float _Q1 = Quartile(1);

	// Calculate Q3
	float _Q3 = Quartile(3);

	// Calculate IQR
	float _IQR = _Q3 - _Q1;

	// Handle Calculation
	if (isnan(_IQR)) _IQR = 0;
	if (isinf(_IQR)) _IQR = 0;

	// End Function
	return(_IQR);

}
float Array_Stats::Standard_Deviation(void) {

	// Calculate Arithmetic Average
	float _Avg = Arithmetic_Average();

	// Set Standard Deviation Variable
	float _SDev = 0;

	// Calculate Array Standard Deviation
	for (uint16_t i = 0; i < this->Data_Count; i++) _SDev += sq(this->Data[i] - _Avg);
	_SDev = sqrt(_SDev / (this->Data_Count - 1));

	// Handle Calculation
	if (isnan(_SDev)) _SDev = 0;
	if (isinf(_SDev)) _SDev = 0;

	// End Function
	return(_SDev);

}
float Array_Stats::Standard_Deviation_Error(void) {

	// Calculate Standard Deviation
	float _SDev = Standard_Deviation();

	// Calculate Standard Deviation Error
	float _SDev_Err = (_SDev / sqrt((float)this->Data_Count));

	// Handle Calculation
	if (isnan(_SDev_Err)) _SDev_Err = 0;
	if (isinf(_SDev_Err)) _SDev_Err = 0;

	// End Function
	return(_SDev_Err);

}
float Array_Stats::Coefficient_Factor(void) {

	// Calculate Arithmetic Average
	float _Avg = Arithmetic_Average();

	// Calculate Standard Deviation
	float _SDev = Standard_Deviation();

	// Calculate Coefficient Factor
	float _Coef = (100 * _SDev / _Avg);

	// Handle Calculation
	if (isnan(_Coef)) _Coef = 0;
	if (isinf(_Coef)) _Coef = 0;

	// End Function
	return(_Coef);

}
float Array_Stats::Variance(void) {

	// Declare Variable
	float _Var = 0;

	// Calculate Arithmetic Average
	float _Avg = Arithmetic_Average();

	// Calculate Array Variance Value
	for (size_t i = 0; i < this->Data_Count; i++) _Var += sq(this->Data[i] - _Avg);
	
	// Handle Calculation
	if (isnan(_Var)) _Var = 0;
	if (isinf(_Var)) _Var = 0;

	// End Function
	return(_Var / (this->Data_Count - 1));

}
void Array_Stats::Bubble_Sort(void) {

	// Declare Buffer Variables
	uint16_t _New_n;
	float _Temp = 0;

	// Sort Array
	do {

		_New_n = 1;

		for (size_t i = 1; i < this->Data_Count; i++) {

			if(this->Data[i - 1]>this->Data[i]){
				
				_Temp = this->Data[i];
				
				this->Data[i]=this->Data[i - 1];
				
				this->Data[i - 1] = _Temp;
				
				_New_n = i;

			} //end if

		}

	} while (_New_n > 1);

}
void Array_Stats::FILO(float _Array[][2], uint16_t _Data_Count, float _Data_X, float _Data_Y) {
	
	// Redesign Array
	for (uint16_t i = 0; i < _Data_Count-1; i++) {
	
		_Array[i][0] = _Array[i+1][0];
		_Array[i][1] = _Array[i+1][1];
	
	}
	
	// Add New Data
	_Array[_Data_Count-1][0] = _Data_X;
	_Array[_Data_Count-1][1] = _Data_Y;

}
void Array_Stats::Array(void) {

	// Loop Data Count
	for (uint8_t i = 0; i < this->Data_Count; i++) {
		
		// Print Array
		Serial.print(F("[")); Serial.print(this->Data[i]); Serial.print(F("] "));
		
	} 
	
	// End Line
	Serial.println(F(""));

}
bool Array_Stats::Set_FILO_Size(const uint8_t _FILO_Size) {

	// Control for Max Filo Size
	if (_FILO_Size > 20) return(false);

	// Resize Array
	realloc(this->Data, _FILO_Size);

	// Set Array Size Variable
	this->Data_Count = _FILO_Size;

	// Reset Array
	for (size_t i = 0; i < this->Data_Count; i++) this->Data[i] = 0;

	// End Function
	return(true);

}
void Array_Stats::FILO_Add_Data(float _Data) {

	// Redesign Array
	for (uint16_t i = 0; i < this->Data_Count; i++) this->Data[i] = this->Data[i + 1];
	
	// Add New Data
	this->Data[this->Data_Count - 1] = _Data;

}

// Stream Statistics
Stream_Stats::Stream_Stats(void) {

}
Stream_Stats::~Stream_Stats(void) {

	// Clear Data Count
	Data_Count = 0;

	// Clear Stat Variable
	Average = 0;
	Min = 0;
	Max = 0;

}
void Stream_Stats::Add_Data(const float _Data) {

	// Calculate Max Value
	if (this->Data_Count == 0) this->Max = _Data;
	if (this->Data_Count > 0 and _Data > this->Max) this->Max = _Data;

	// Calculate Min Value
	if (this->Data_Count == 0) this->Min = _Data;
	if (this->Data_Count > 0 and _Data < this->Min) this->Min = _Data;

	// Calculate Avg Value
	if (this->Data_Count == 0) this->Average = _Data;
	if (this->Data_Count > 0) this->Average = this->Average + ((_Data - this->Average) / this->Data_Count);

	// Set Data Count (+1)
	this->Data_Count++;

}
void Stream_Stats::Data_Clear(void) {

	// Clear Data Count
	this->Data_Count = 0;

	// Celar Stream Variables
	this->Max = 0;
	this->Min = 0;
	this->Average = 0;

}
uint16_t Stream_Stats::Get_Data_Count(void) {
	return(this->Data_Count);
}
float Stream_Stats::Get_Average(void) {
	return(this->Average);
}
float Stream_Stats::Get_Min(void) {
	return(this->Min);
}
float Stream_Stats::Get_Max(void) {
	return(this->Max);
}

// Linear Regression Statistics
Linear_Regression::Linear_Regression(uint32_t * _Data_X, float * _Data_Y, uint8_t _Data_Count) {

	// Set Class Data Count Variable
	this->Data_Count = _Data_Count;

	// Set Class Data Variable
	this->Data_X = _Data_X;
	this->Data_Y = _Data_Y;


}
Linear_Regression::~Linear_Regression(void) {

}
float Linear_Regression::Offset(void) {

//	Array_Stats X_Array(this->Data_X, this->Data_Count);


	// Calculate Sum X
//	uint32_t _Sum_X = Array_Sum(_X, _Data_Count);







/*
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
//	_Sum_X = Array_Sum(_X, _Data_Count);

	// Calculate Sum Y
//	_Sum_Y = Array_Sum(_Y, _Data_Count);

	// Calculate Sum xy
	for (uint16_t i = 0; i < _Data_Count; i++) {

		// Set Sum xy
		_Sum_XY += _X[i] * _Y[i];

	}

	// Calculate Sum X2
//	_Sum_X2 = Array_Sq_Sum(_X, _Data_Count);

	// Calculate Slope
	_b0 = ((_Sum_X2 * _Sum_Y) - (_Sum_X * _Sum_XY)) / ((_Data_Count * _Sum_X2) - (_Sum_X * _Sum_X));

	// End Function
	return(_b0);
*/
}
float Linear_Regression::Slope(void) {
/*
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
//	_Sum_X = Array_Sum(_X, _Data_Count);

	// Calculate Sum Y
//	_Sum_Y = Array_Sum(_Y, _Data_Count);

	// Calculate Sum xy
	for (uint16_t i = 0; i < _Data_Count; i++) {

		// Set Sum xy
		_Sum_XY += _X[i] * _Y[i];

	}

	// Calculate Sum X2
//	_Sum_X2 = Array_Sq_Sum(_X, _Data_Count);

	// Calculate Slope
	_b1 = ((_Data_Count * _Sum_XY) - (_Sum_X * _Sum_Y)) / ((_Data_Count * _Sum_X2) - (_Sum_X * _Sum_X));

	// End Function
	return(_b1);
*/
}
float Linear_Regression::R2(void) {
/*
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
//	_Mean_X = Array_Arithmetic_Average(_X, _Data_Count);

	// Calculate Mean Y
//	_Mean_Y = Array_Arithmetic_Average(_Y, _Data_Count);

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
*/
}

