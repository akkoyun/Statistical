/* *******************************************************************************
 *  Copyright (C) 2014-2022 Mehmet Gunce Akkoyun Can not be copied and/or
 *	distributed without the express permission of Mehmet Gunce Akkoyun.
 *
 *	Library				: Data Statistical Library
 *	Code Developer		: Mehmet Gunce Akkoyun (akkoyun@me.com)
 *********************************************************************************/

#ifndef __Statistical__
#define __Statistical__

// Define Arduino Library
#ifndef __Arduino__
#include <Arduino.h>
#endif

// Array Statistics
template <typename Data_Type>  class Array_Stats {

	protected:
		
		// Declare Data Array
		Data_Type * Data;

		// Declare Data Count
		size_t Data_Count;

	public:

		// Define Average Type
		enum Average_Type {
			Arithmetic_Avg	= (uint8_t)1,
			Geometric_Avg	= (uint8_t)2,
			RMS_Avg			= (uint8_t)3,
			Ext_RMS_Avg		= (uint8_t)4
		};

		/**
		 * @brief Function constructor
		 * @version 01.00.00
		 * @param _Data Data array
		 * @param _Data_Count Array size
		 */
		Array_Stats(Data_Type * _Data, size_t _Data_Count) : Data(_Data), Data_Count(_Data_Count) {

		}

		/**
		 * @brief Calculate the array average batch.
		 * @version 01.00.00
		 * @param _Average_Type Average Type
		 * @return float - Average value of array.
		 */
		float Average(uint8_t _Average_Type) {

			// Control for Type Limit
			if (_Average_Type > 4) return(0);
			
			// Declare Variable
			double _Result = 0;

			// Calculate Average
			if (_Average_Type == 1) _Result = this->Arithmetic_Average();
			if (_Average_Type == 2) _Result = this->Geometric_Average();
			if (_Average_Type == 3) _Result = this->RMS_Average();
			if (_Average_Type == 4) _Result = this->Ext_RMS_Average();

			// End Function
			return(_Result);

		}

		/**
		 * @brief Get data array size
		 * @version 01.00.00
		 */	
		size_t Size(void) {

			// End Function
			return(this->Data_Count);

		}

		/**
		 * @brief Calculate the array sum.
		 * @version 01.00.00
		 * @return Sum value of array.
		 */
		float Sum(void) {

			// Declare Variable
			double _Sum = 0;

			// Calculate Array Sum
			for (size_t i = 0; i < this->Data_Count; i++) _Sum += (double)this->Data[i];

			// Handle Calculation
			if (isnan(_Sum)) _Sum = 0;
			if (isinf(_Sum)) _Sum = 0;

			// End Function
			return(_Sum);

		}

		/**
		 * @brief Calculate the array max value.
		 * @version 01.00.00
		 * @return float - Max value of array.
		 */
		float Max(void) {

			// Declare Variable
			double _Max = (double)this->Data[0];

			// Calculate Array Max Value
			for (uint16_t i=0; i < this->Data_Count; i++) if ((double)this->Data[i] > _Max) _Max = (double)this->Data[i];

			// Handle Calculation
			if (isnan(_Max)) _Max = 0;
			if (isinf(_Max)) _Max = 0;

			// End Function
			return(_Max);

		}

		/**
		 * @brief Calculate the array min value.
		 * @version 01.00.00
		 * @return float - Min value of array.
		 */
		float Min(void) {

			// Declare Variable
			double _Min = (double)this->Data[0];

			// Calculate Array Min Value
			for (uint16_t i=0; i < this->Data_Count; i++) if ((double)this->Data[i] < _Min) _Min = (double)this->Data[i];

			// Handle Calculation
			if (isnan(_Min)) _Min = 0;
			if (isinf(_Min)) _Min = 0;

			// End Function
			return(_Min);

		}

		/**
		 * @brief Calculate the array square sum.
		 * @version 01.00.00
		 * @return float - Square total value of array.
		 */
		float Sq_Sum(void) {

			// Declare Variable
			double _Sq_Sum = 0;

			// Calculate Array Square Total
			for (uint16_t i = 0; i < this->Data_Count; i++) _Sq_Sum += sq((double)this->Data[i]);

			// Handle Calculation
			if (isnan(_Sq_Sum)) _Sq_Sum = 0;
			if (isinf(_Sq_Sum)) _Sq_Sum = 0;

			// End Function
			return(_Sq_Sum);

		}

		/**
		 * @brief Calculate the array arithmetic average.
		 * @version 01.00.00
		 * @return float - Arithmetic average value of array.
		 */
		float Arithmetic_Average(void) {

			// Calculate Arithmetic Average
			double _Average = Sum() / this->Data_Count;

			// Handle Calculation
			if (isnan(_Average)) _Average = 0;
			if (isinf(_Average)) _Average = 0;

			// End Function
			return(_Average);

		}

		/**
		 * @brief Calculate the array geometric average.
		 * @version 01.00.00
		 * @return float - Geometric average value of array.
		 */
		float Geometric_Average(void) {

			// Declare Variable
			double _GAvg_Sum = 0;

			// Calculate Geometric Average Value
			for (size_t i = 0; i < this->Data_Count; i++) _GAvg_Sum += (log(this->Data[i]) - _GAvg_Sum) / (i + 1);
			
			// Set Geometric Average Variable
			double _GAvg = exp(_GAvg_Sum);

			// Handle Calculation
			if (isnan(_GAvg)) _GAvg = 0;
			if (isinf(_GAvg)) _GAvg = 0;

			// End Function
			return(_GAvg);

		}

		/**
		 * @brief Calculate the array RMS average.
		 * @version 01.00.00
		 * @return float - RMS average value of array.
		 */
		float RMS_Average(void) {

			// Calculate Array Sq Total
			double _Sum = Sq_Sum();

			// Calculate RSM Average
			double _RMS_Avg = (sqrt(_Sum / this->Data_Count));

			// Handle Calculation
			if (isnan(_RMS_Avg)) _RMS_Avg = 0;
			if (isinf(_RMS_Avg)) _RMS_Avg = 0;

			// End Function
			return(_RMS_Avg);

		}

		/**
		 * @brief Calculate the array extended RMS average.
		 * @version 01.00.00
		 * @return float - Extended RMS average value of array.
		 */
		float Ext_RMS_Average(void) {

			// Calculate Array Sq Total
			double _Sum = Sq_Sum();

			// Calculate Extended Sum
			_Sum -= sq(Min());
			_Sum -= sq(Max());

			// Calculate RSM Average
			double _Ext_RMS_Avg = (sqrt(_Sum / this->Data_Count));

			// Handle Calculation
			if (isnan(_Ext_RMS_Avg)) _Ext_RMS_Avg = 0;
			if (isinf(_Ext_RMS_Avg)) _Ext_RMS_Avg = 0;

			// End Function
			return(_Ext_RMS_Avg);

		}

		/**
		 * @brief Calculate the array quartile.
		 * @version 01.00.00
		 * @return float - Quartile value of array.
		 */
		float Quartile(const uint8_t _Q) {

			// Sort Array
			Bubble_Sort();

			// Declare Variable
			double _Quartile = 0;
			double _Multiplier = 0;

			// Decide Q Multiplier
			if (_Q == 1) _Multiplier = 0.25;
			if (_Q == 2) _Multiplier = 0.50;
			if (_Q == 3) _Multiplier = 0.75;

			// Calculate Quartile Position
			double _Position = ((this->Data_Count + 1) * _Multiplier);

			// Calculate Quartile
			_Quartile = this->Data[(int)_Position - 1] + ((_Position - (int)_Position) * (this->Data[(int)_Position] - this->Data[(int)_Position - 1]));

			// Handle Calculation
			if (isnan(_Quartile)) _Quartile = 0;
			if (isinf(_Quartile)) _Quartile = 0;

			// End Function
			return(_Quartile);

		}

		/**
		 * @brief Calculate the array IQR.
		 * @version 01.00.00
		 * @return float - IQR value of array.
		 */
		float IQR(void) {

			// Calculate Q1
			double _Q1 = Quartile(1);

			// Calculate Q3
			double _Q3 = Quartile(3);

			// Calculate IQR
			double _IQR = _Q3 - _Q1;

			// Handle Calculation
			if (isnan(_IQR)) _IQR = 0;
			if (isinf(_IQR)) _IQR = 0;

			// End Function
			return(_IQR);

		}

		/**
		 * @brief Calculate the array standard deviation.
		 * @version 01.00.00
		 * @return float - Standard deviation value of array.
		 */
		float Standard_Deviation(void) {

			// Calculate Arithmetic Average
			double _Avg = Arithmetic_Average();

			// Set Standard Deviation Variable
			double _SDev = 0;

			// Calculate Array Standard Deviation
			for (uint16_t i = 0; i < this->Data_Count; i++) _SDev += sq(this->Data[i] - _Avg);
			_SDev = sqrt(_SDev / (this->Data_Count - 1));

			// Handle Calculation
			if (isnan(_SDev)) _SDev = 0;
			if (isinf(_SDev)) _SDev = 0;

			// End Function
			return(_SDev);

		}

		/**
		 * @brief Calculate the array standard deviation error.
		 * @version 01.00.00
		 * @return float - Standard deviation error value of array.
		 */
		float Standard_Deviation_Error(void) {

			// Calculate Standard Deviation
			double _SDev = Standard_Deviation();

			// Calculate Standard Deviation Error
			double _SDev_Err = (_SDev / sqrt((double)this->Data_Count));

			// Handle Calculation
			if (isnan(_SDev_Err)) _SDev_Err = 0;
			if (isinf(_SDev_Err)) _SDev_Err = 0;

			// End Function
			return(_SDev_Err);

		}

		/**
		 * @brief Calculate the array coefficient factor.
		 * @version 01.00.00
		 * @return float - Coefficient factor value of array.
		 */
		float Coefficient_Factor(void) {

			// Calculate Arithmetic Average
			double _Avg = Arithmetic_Average();

			// Calculate Standard Deviation
			double _SDev = Standard_Deviation();

			// Calculate Coefficient Factor
			double _Coef = (100 * _SDev / _Avg);

			// Handle Calculation
			if (isnan(_Coef)) _Coef = 0;
			if (isinf(_Coef)) _Coef = 0;

			// End Function
			return(_Coef);

		}

		/**
		 * @brief Calculate the array variance.
		 * @version 01.00.00
		 * @return float - Variance value of array.
		 */
		float Variance(void) {

			// Declare Variable
			double _Var = 0;

			// Calculate Arithmetic Average
			double _Avg = Arithmetic_Average();

			// Calculate Array Variance Value
			for (size_t i = 0; i < this->Data_Count; i++) _Var += sq(this->Data[i] - _Avg);
			
			// Handle Calculation
			if (isnan(_Var)) _Var = 0;
			if (isinf(_Var)) _Var = 0;

			// End Function
			return(_Var / (this->Data_Count - 1));

		}

		/**
		 * @brief Sort the array from min to max.
		 * @version 01.00.00
		 */
		void Bubble_Sort(void) {

			// Declare Buffer Variables
			size_t _New_n;
			Data_Type _Temp = 0;

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

		/**
		 * @brief Set Array FILO
		 * @version 01.00.00
		 * @param _Data_X Array size
		 * @param _Data_Y New Array Data
		 */	
		void FILO(float _Array[][2], uint16_t _Data_Count, float _Data_X, float _Data_Y) {
	
			// Redesign Array
			for (uint16_t i = 0; i < _Data_Count-1; i++) {
			
				_Array[i][0] = _Array[i+1][0];
				_Array[i][1] = _Array[i+1][1];
			
			}
			
			// Add New Data
			_Array[_Data_Count-1][0] = _Data_X;
			_Array[_Data_Count-1][1] = _Data_Y;

		}

		/**
		 * @brief Print Full Array
		 * @version 01.00.00
		 */
		void Array(void) {

			// Loop Data Count
			for (uint8_t i = 0; i < this->Data_Count; i++) {
				
				// Print Array
				Serial.print(F("[")); Serial.print(this->Data[i]); Serial.print(F("] "));
				
			} 
			
			// End Line
			Serial.println(F(""));

		}

		/**
		 * @brief Set FILO array size
		 * @version 01.00.00
		 * @param _FILO_Size Array size
		 */	
		bool Set_FILO_Size(const size_t _FILO_Size) {

			// Control for Max Filo Size
			if (_FILO_Size > 50) return(false);

			// Resize Array
			realloc(this->Data, _FILO_Size);

			// Set Array Size Variable
			this->Data_Count = _FILO_Size;

			// Reset Array
			for (size_t i = 0; i < this->Data_Count; i++) this->Data[i] = 0;

			// End Function
			return(true);

		}

		/**
		 * @brief FILO data add to array
		 * @version 01.00.00
		 * @param _Data data
		 */	
		void FILO_Add_Data(const Data_Type _Data) {

			// Redesign Array
			for (size_t i = 0; i < this->Data_Count; i++) this->Data[i] = this->Data[i + 1];
			
			// Add New Data
			this->Data[this->Data_Count - 1] = _Data;

		}

};

// Stream Statistics
template <typename Data_Type>  class Stream_Stats {

	private:

		// Declare Data Count
		uint16_t Data_Count;

		// Declare Stat Variable
		Data_Type Average;
		Data_Type Min;
		Data_Type Max;

	public:

		/**
		 * @brief Function constructor
		 * @version 01.00.00
		 */
		Stream_Stats(void) : Data_Count(0), Average(0), Min(0), Max(0) {

		};

		/**
		 * @brief Add Stream Data
		 * @version 01.00.00
		 * @param _Data Stream Data
		 */
		void Add(Data_Type _Data) {

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
			
		};

		/**
		 * @brief Clear Stream Statistic Parameters
		 * @version 01.00.00
		 */
		void Clear(void) {

			// Clear Data Count
			this->Data_Count = 0;

			// Celar Stream Variables
			this->Max = 0;
			this->Min = 0;
			this->Average = 0;
			
		};

		/**
		 * @brief Get stream data count
		 * @version 01.00.00
		 */
		uint16_t Get_Data_Count(void) {

			// Return Data Count
			return(this->Data_Count);

		};

		/**
		 * @brief Get stream average
		 * @version 01.00.00
		 */
		float Get_Average(void) {

			// Return Average
			return(this->Average);

		};

		/**
		 * @brief Get stream minimum value
		 * @version 01.00.00
		 */
		float Get_Min(void) {

			// Return Min
			return(this->Min);

		};

		/**
		 * @brief Get stream maximum value
		 * @version 01.00.00
		 */
		float Get_Max(void) {

			// Return Max
			return(this->Max);

		};

};

// Linear Regression Statistics
template <typename Data_Type_X, typename Data_Type_Y> class Linear_Regression {

	protected:

		// Declare Data Array X
		Data_Type_X * Data_X;

		// Declare Data Array Y
		Data_Type_Y * Data_Y;

		// Declare Data Count
		size_t Data_Count;

	public:

		/**
		 * @brief Function constructor
		 * @version 01.00.00
		 */
		Linear_Regression(Data_Type_X * _Data_X, Data_Type_Y * _Data_Y, size_t _Data_Count) : Data_X(_Data_X), Data_Y(_Data_Y), Data_Count(_Data_Count)  {

		}

		/**
		 * @brief Calculate Regression Offset
		 * @version 01.00.00
		 * @return float Offset Value
		 */
		float Offset(void) {

			// Declare X Array
			Array_Stats<Data_Type_X> Data_Array_X(Data_X, Data_Count);

			// Declare Y Array
			Array_Stats<Data_Type_Y> Data_Array_Y(Data_Y, Data_Count);

			// Declare Variables
			float _Sum_X = 0;
			float _Sum_Y = 0;
			float _Sum_X2 = 0;
			float _Sum_XY = 0;
			float _b0 = 0;

			// Calculate Sum X
			_Sum_X = Data_Array_X.Sum();

			// Calculate Sum Y
			_Sum_Y = Data_Array_Y.Sum();

			// Calculate Sum X2
			_Sum_X2 = Data_Array_X.Sq_Sum();

			// Calculate Sum XY
			for (size_t i = 0; i < Data_Count; i++) _Sum_XY += Data_X[i] * Data_Y[i];

			// Calculate Slope
			_b0 = ((_Sum_X2 * _Sum_Y) - (_Sum_X * _Sum_XY)) / ((Data_Count * _Sum_X2) - (_Sum_X * _Sum_X));

			// End Function
			return(_b0);

		}

		/**
		 * @brief Calculate Regression Slope
		 * @version 01.00.00
		 * @return float Slope Value
		 */
		float Slope(void) {

			// Declare X Array
			Array_Stats<Data_Type_X> Data_Array_X(Data_X, Data_Count);

			// Declare Y Array
			Array_Stats<Data_Type_Y> Data_Array_Y(Data_Y, Data_Count);

			// Declare Variables
			float _Sum_X = 0;
			float _Sum_Y = 0;
			float _Sum_XY = 0;
			float _Sum_X2 = 0;
			float _b1 = 0;

			// Calculate Sum X
			_Sum_X = Data_Array_X.Sum();

			// Calculate Sum Y
			_Sum_Y = Data_Array_Y.Sum();

			// Calculate Sum X2
			_Sum_X2 = Data_Array_X.Sq_Sum();

			// Calculate Sum XY
			for (size_t i = 0; i < Data_Count; i++) _Sum_XY += Data_X[i] * Data_Y[i];

			// Calculate Slope
			_b1 = ((Data_Count * _Sum_XY) - (_Sum_X * _Sum_Y)) / ((Data_Count * _Sum_X2) - (_Sum_X * _Sum_X));

			// End Function
			return(_b1);

		}
		
		/**
		 * @brief Calculate Regression R2
		 * @version 01.00.00
		 * @return float R2 Value
		 */
		float R2(void) {

			// Declare X Array
			Array_Stats<Data_Type_X> Data_Array_X(Data_X, Data_Count);

			// Declare Y Array
			Array_Stats<Data_Type_Y> Data_Array_Y(Data_Y, Data_Count);

			// Declare Variables
			float _Mean_X = 0;
			float _Mean_Y = 0;
			float _Sum_x2 = 0;
			float _Sum_y2 = 0;
			float _Sum_xy = 0;
			float _x[Data_Count]; // x = X - Xavg
			float _y[Data_Count]; // y = Y - Yavg
			float _R2 = 0;

			// Calculate Mean X
			_Mean_X = Data_Array_X.Arithmetic_Average();

			// Calculate Mean Y
			_Mean_Y = Data_Array_Y.Arithmetic_Average();

			// Set x and y Array
			for (size_t i = 0; i < Data_Count; i++) {

				// Set x
				_x[i] = Data_X[i] - _Mean_X;

				// Set y
				_y[i] = Data_Y[i] - _Mean_Y;

			}

			// Calculate Sum xy
			for (size_t i = 0; i < Data_Count; i++) {

				// Set Sum xy
				_Sum_xy += _x[i] * _y[i];

			}

			// Calculate Sum x2
			for (size_t i = 0; i < Data_Count; i++) {

				// Set Sum x2
				_Sum_x2 += _x[i] * _x[i];

			}

			// Calculate Sum y2
			for (size_t i = 0; i < Data_Count; i++) {

				// Set Sum y2
				_Sum_y2 += _y[i] * _y[i];

			}

			// Calculate R2
			_R2 = (_Sum_xy * _Sum_xy) / (_Sum_x2 * _Sum_y2);

			// End Function
			return(_R2);

		}

};

#endif /* defined(__Statistical__) */
