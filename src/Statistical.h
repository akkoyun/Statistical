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
			#define _Arithmetic_Average_		1
			#define _Geometric_Average_			2
			#define _RMS_Average_				3
			#define _Ext_RMS_Average_			4
			#define _Sigma_Average_				5

			// Define Sigma Type
			#define _1_Sigma_					1
			#define _2_Sigma_					2
			#define _3_Sigma_					3
			#define _4_Sigma_					4

			// Function constructor
			Array_Stats(Data_Type * _Data, size_t _Data_Count) : Data(_Data), Data_Count(_Data_Count) {

			}

			// Calculate the array average batch.
			float Average(uint8_t _Average_Type) {

				// Declare Variable
				double _Result = 0;

				// Calculate Average
				if (_Average_Type == _Arithmetic_Average_) _Result = this->Arithmetic_Average();
				else if (_Average_Type == _Geometric_Average_) _Result = this->Geometric_Average();
				else if (_Average_Type == _RMS_Average_) _Result = this->RMS_Average();
				else if (_Average_Type == _Ext_RMS_Average_) _Result = this->Ext_RMS_Average();
				else if (_Average_Type == _Sigma_Average_) _Result = this->Sigma_Average(_1_Sigma_);
				else return(0);

				// End Function
				return(_Result);

			}

			// Get data array size
			size_t Size(void) {

				// End Function
				return(this->Data_Count);

			}

			// Calculate the array sum.
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

			// Calculate the array max value.
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

			// Calculate the array min value.
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

			// Calculate the array square sum.
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

			// Calculate the array arithmetic average.
			float Arithmetic_Average(void) {

				// Calculate Arithmetic Average
				double _Average = Sum() / this->Data_Count;

				// Handle Calculation
				if (isnan(_Average)) _Average = 0;
				if (isinf(_Average)) _Average = 0;

				// End Function
				return(_Average);

			}

			// Calculate the array geometric average.
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

			// Calculate the array x Sigma average.
			float Sigma_Average(const uint8_t _Sigma) {

				// Get Average
				Data_Type _Average = this->Arithmetic_Average();

				// Get Deviation
				Data_Type _Deviation = this->Standard_Deviation();

				// Declare Valid Data Count
				size_t _Valid_Data_Count = 0;

				// Declare Sum Variable
				double _Sum = 0;

				// Calculate Sigma Average Sum
				for (size_t i = 0; i < this->Data_Count; i++) {

					// Control for Valid Data
					if (this->Data[i] > (_Average - (_Sigma * _Deviation)) && this->Data[i] < (_Average + (_Sigma * _Deviation))) {

						// Add to Sum
						_Sum += this->Data[i];

						// Increment Valid Data Count
						_Valid_Data_Count++;

					}

				}

				// Control for Valid Data Count
				if (_Valid_Data_Count == 0) return(0);

				// Calculate Sigma Average
				Data_Type _Sigma_Avg = _Sum / _Valid_Data_Count;			

				// End Function
				return(_Sigma_Avg);

			}

			// Calculate the array RMS average.
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

			// Calculate the array extended RMS average.
			float Ext_RMS_Average(void) {

				// Calculate Array Sq Total
				double _Sum = Sq_Sum();

				// Calculate Extended Sum
				_Sum -= sq(Min());
				_Sum -= sq(Max());

				// Calculate RSM Average
				double _Ext_RMS_Avg = (sqrt(_Sum / (this->Data_Count - 2)));

				// Handle Calculation
				if (isnan(_Ext_RMS_Avg)) _Ext_RMS_Avg = 0;
				if (isinf(_Ext_RMS_Avg)) _Ext_RMS_Avg = 0;

				// End Function
				return(_Ext_RMS_Avg);

			}

			// Calculate the array quartile.
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

			// Calculate the array IQR.
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

			// Calculate the array standard deviation.
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

			// Calculate the array standard deviation error.
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

			// Calculate the array coefficient factor.
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

			// Calculate the array variance.
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

			// Sort the array from min to max.
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

			// Set Array FILO
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

			// Print Full Array
			void Array(void) {

				// Loop Data Count
				for (uint8_t i = 0; i < this->Data_Count; i++) {
					
					// Print Array
					Serial.print(F("[")); Serial.print(this->Data[i]); Serial.print(F("] "));
					
				} 
				
				// End Line
				Serial.println(F(""));

			}

			// Set FILO array size
			bool Set_FILO_Size(const size_t _FILO_Size) {

				// Control for Max Filo Size
				if (_FILO_Size > 50) return(false);

				// ReSize Arrays
				void* tempData = realloc(this->Data, _FILO_Size * sizeof(*this->Data));

				// Control for Realloc
				if (tempData == NULL) {

					// End Function
					return(false);

				}

				// Set New Array
				this->Data = tempData;

				// Set Array Size Variable
				this->Data_Count = _FILO_Size;

				// Reset Array
				for (size_t i = 0; i < this->Data_Count; i++) this->Data[i] = 0;

				// End Function
				return(true);

			}

			// FILO data add to array
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
			Data_Type Last;

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

				// Set Last Value
				this->Last = _Data;

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
				this->Last = 0;
				
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

			/**
			 * @brief Get stream last value
			 * @version 01.00.00
			 */
			float Get_Last(void) {

				// Return Max
				return(this->Last);

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

	// Array Statistics
	template <typename Data_Type_Magnitude, typename Data_Type_Angle>  class Vector_Stats {

		protected:
			
			// Declare Vector Magnitude
			Data_Type_Magnitude * Data_Magnitude;

			// Declare Vector Angle
			Data_Type_Angle * Data_Angle;

			// Declare Vector Count
			size_t Vector_Count;

			// Declare Vector Magnitude X
			Data_Type_Magnitude Magnitude_X[3];

			// Declare Vector Magnitude Y
			Data_Type_Magnitude Magnitude_Y[3];

			/**
			 * @brief Set array size
			 * @version 01.00.00
			 * @param _Size Array size
			 */	
			bool Set_Array_Size(const size_t _Size) {

				// Control for Max Filo Size
				if (_Size == 3) return(false);

				// Resize Array
				void* _New_Magnitude_X = realloc(this->Magnitude_X, _Size);

				// Control for Realloc
				if (_New_Magnitude_X != NULL) {

					// Set New Array
					this->Magnitude_X = _New_Magnitude_X;

				} else {
					
					// End Function
					return(false);

				}

				// Resize Array
				void* _New_Magnitude_Y = realloc(this->Magnitude_Y, _Size);

				// Control for Realloc
				if (_New_Magnitude_Y != NULL) {

					// Set New Array
					this->Magnitude_Y = _New_Magnitude_Y;

				} else {

					// End Function
					return(false);

				}

				// End Function
				return(true);

			}

			/**
			 * @brief Degree to Radian Convert Function
			 * @version 01.00.00
			 * @param _Angle Degree
			 * @return float 
			 */
			float Degree2Radian(Data_Type_Angle _Angle) {

				// Convert Degree to Radian
				return (radians(_Angle));

			}

			/**
			 * @brief Degree to Radian Convert Function
			 * @version 01.00.00
			 * @param _Angle Degree
			 * @return float 
			 */
			float Radian2Degree(Data_Type_Angle _Angle) {

				// Convert Radian to Degree
				return (degrees(_Angle));
			}

			/**
			 * @brief Set Vector Components
			 * @version 01.00.00
			 */
			void Set_Vector_Components(void) {

				// Calculate Vector Parameters
				for (size_t i = 0; i < this->Vector_Count; i++) {

					// Calculate Vector X
					this->Magnitude_X[i] = (float)this->Data_Magnitude[i] * cos(this->Degree2Radian(this->Data_Angle[i]));

					// Calculate Vector Y
					this->Magnitude_Y[i] = (float)this->Data_Magnitude[i] * sin(this->Degree2Radian(this->Data_Angle[i]));

				}

			}

		public:

			// Vector Sum Struct
			struct Vector_Sum {

				// Vector Total Magnitude
				float Magnitude;

				// Vector Total Angle
				float Angle;

			} Result;

			/**
			 * @brief Function constructor
			 * @version 01.00.00
			 * @param _Data Data array
			 * @param _Data_Count Array size
			 */
			Vector_Stats(Data_Type_Magnitude * _Data_Magnitude, Data_Type_Angle * _Data_Angle, size_t _Vector_Count) : Data_Magnitude(_Data_Magnitude), Data_Angle(_Data_Angle), Vector_Count(_Vector_Count) {

			}

			/**
			 * @brief Vector add function
			 * @version 01.00.00
			 */
			void Vector_Sum(void) {

				// Declare Vector Sum Variables
				float _Vector_Sum_X = 0;
				float _Vector_Sum_Y = 0;
				float _Angle = 0;

				// ReSize Arrays
				this->Set_Array_Size(this->Vector_Count);

				// Calculate Vector Parameters
				this->Set_Vector_Components();

				// Calculate Vector Parameters Sum
				for (size_t i = 0; i < this->Vector_Count; i++) {

					// Calculate Sums
					_Vector_Sum_X += this->Magnitude_X[i];
					_Vector_Sum_Y += this->Magnitude_Y[i];

				}

				// Calculate Result Vector Magnitude
				this->Result.Magnitude = sqrt(sq(_Vector_Sum_X) + sq(_Vector_Sum_Y));

				Serial.println("------------------");
				Serial.print("SUM X     : "); Serial.println(_Vector_Sum_X);
				Serial.print("SUM Y     : "); Serial.println(_Vector_Sum_Y);
				Serial.print("Magnitude : "); Serial.println(this->Result.Magnitude);

				// Calculate Result Vector Angle
				_Angle = (Radian2Degree(atan(_Vector_Sum_Y / _Vector_Sum_X)));

				Serial.print("Angle     : "); Serial.println(_Angle);
				Serial.println("------------------");

				// Handle Angle
				if (_Vector_Sum_X > 0 and _Vector_Sum_Y > 0) {

					Serial.println("Bölge : 1");

					// Set Angle
					this->Result.Angle = 90 - abs(_Angle);

				}
				if (_Vector_Sum_X < 0 and _Vector_Sum_Y > 0) {

					Serial.println("Bölge : 2");

					// Set Angle
					this->Result.Angle = 360 + (abs(_Angle) - 90);

				}
				if (_Vector_Sum_X > 0 and _Vector_Sum_Y < 0) {

					Serial.println("Bölge : 3");

					// Set Angle
					this->Result.Angle = 180 - (_Angle + 90);

				}
				if (_Vector_Sum_X < 0 and _Vector_Sum_Y < 0) {

					Serial.println("Bölge : 4");

					// Set Angle
					this->Result.Angle = 270 - abs(_Angle);

				}

			}

	};

#endif /* defined(__Statistical__) */
