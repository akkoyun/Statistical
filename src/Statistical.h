#ifndef __Statistical__
#define __Statistical__

	// Include Arduino Library
	#ifndef Arduino_h
		#include <Arduino.h>
	#endif

	// Include Definitions
	#include "Definitions.h"

	// Array Statistics
	template <typename Data_Type>  class Array_Stats {

		protected:
			
			// Declare Data Array
			Data_Type * Data;

			// Declare Data Count
			uint16_t Data_Count;

		public:

			// Function constructor
			Array_Stats(Data_Type * _Data, uint16_t _Data_Count) : Data(_Data), Data_Count(_Data_Count) {

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
			uint16_t Size(void) {

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

			// Bubble Sort Function
			void Bubble_Sort(Data_Type* data, uint16_t count) {

				// Bubble Sort
				for (uint16_t i = 0; i < count - 1; i++) {
					for (uint16_t j = 0; j < count - i - 1; j++) {
						if (data[j] > data[j + 1]) {
							Data_Type temp = data[j];
							data[j] = data[j + 1];
							data[j + 1] = temp;
						}
					}
				}
			}

			// Median Function
			float Median(void) {

				// Declare Variable
				Data_Type sortedData[Data_Count];

				// Copy and Sort Data
				memcpy(sortedData, Data, Data_Count * sizeof(Data_Type));

				// Bubble Sort
				Bubble_Sort(sortedData, Data_Count);

				// Calculate Median
				if (Data_Count % 2 == 0) {
					
					// Return Median
					return (sortedData[Data_Count / 2 - 1] + sortedData[Data_Count / 2]) / 2.0;

				} else {

					// Return Median
					return sortedData[Data_Count / 2];

				}

			}

			// Quartile Function
			float Q1(void) {

				// Declare Variable
				Data_Type temp[Data_Count];
				
				// Copy and Sort Data
				memcpy(temp, Data, Data_Count * sizeof(Data_Type));

				// Bubble Sort
				Bubble_Sort(temp, Data_Count);

				// Calculate Q1
				size_t midIndex = Data_Count / 4;

				// Return Q1
				return temp[midIndex];

			}

			// Quartile Function
			float Q3(void) {

				// Declare Variable
				Data_Type temp[Data_Count];
				
				// Copy and Sort Data
				memcpy(temp, Data, Data_Count * sizeof(Data_Type));

				// Bubble Sort
				Bubble_Sort(temp, Data_Count);

				// Calculate Q1
				size_t midIndex = 3 * Data_Count / 4;

				// Return Q1
				return temp[midIndex];

			}

			// IQR Function
			float IQR() {
				
				// Return IQR
				return Q3() - Q1();

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
			Data_Type M2;

		public:

			// Constructor
			Stream_Stats(void) : Data_Count(0), Average(0), Min(0), Max(0) {

			};

			// Add Function
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

				// Calculate M2 Value
				if (this->Data_Count > 0) this->M2 += ((_Data - this->Average) * (_Data - this->Average));

				// Set Last Value
				this->Last = _Data;

				// Set Data Count (+1)
				this->Data_Count++;
				
			};

			// Clear Function
			void Clear(void) {

				// Clear Data Count
				this->Data_Count = 0;

				// Celar Stream Variables
				this->Max = 0;
				this->Min = 0;
				this->Average = 0;
				this->Last = 0;
				
			};

			// Get Data Count Function
			uint16_t Get_Data_Count(void) {

				// Return Data Count
				return(this->Data_Count);

			};

			// Get Average Function
			float Get_Average(void) {

				// Return Average
				return(this->Average);

			};

			// Get Min Function
			float Get_Min(void) {

				// Return Min
				return(this->Min);

			};

			// Get Max Function
			float Get_Max(void) {

				// Return Max
				return(this->Max);

			};

			// Get Last Function
			float Get_Last(void) {

				// Return Max
				return(this->Last);

			};

			// Get Variance Function
			float Get_Variance(void) {

				// Return Variance
				return (this->Data_Count < 2) ? NAN : this->M2 / (this->Data_Count - 1);

			};

			// Get Standard Deviation Function
			float Get_Standard_Deviation(void) {

				// Return Standard Deviation
				return (this->Data_Count < 2) ? NAN : sqrt(this->M2 / this->Data_Count);

			};

	};

	// XY Data Class
	template<typename X_Data_Type, typename Y_Data_Type> class Data_XY {

		// Public Context
		public:

			// Declare X Variable
			X_Data_Type _Data_X;

			// Declare Y Variable
			Y_Data_Type _Data_Y;

			// Constructor
			Data_XY() : _Data_X(), _Data_Y() {}
			Data_XY(X_Data_Type _X, Y_Data_Type _Y) : _Data_X(_X), _Data_Y(_Y) {}

	};

	// Dynamic Data Class
	template<typename X_Data_Type, typename Y_Data_Type> class Dynamic_Data_2D {

		// Public Context
		private:

			// Declare Data Container
			Data_XY<X_Data_Type, Y_Data_Type>* Data_Container;
			
			// Declare Capacity
			uint16_t Capacity;
			
			// Declare Current Size
			uint16_t Current_Size;

			// Resize Function
			void Resize() {

				// Check Capacity
				Capacity = (Capacity == 0) ? 1 : Capacity * 2;

				// Create New Data
				Data_XY<X_Data_Type, Y_Data_Type>* _New_Data = new Data_XY<X_Data_Type, Y_Data_Type>[Capacity];

				// Copy Data
				for (uint16_t i = 0; i < Current_Size; i++) _New_Data[i] = Data_Container[i];

				// Delete Old Data
				delete[] Data_Container;

				// Set New Data
				Data_Container = _New_Data;

			}

		public:

			// Constructor
			Dynamic_Data_2D() : Data_Container(nullptr), Capacity(0), Current_Size(0) {}

			// Destructor
			~Dynamic_Data_2D() {

				// Delete Data
				delete[] Data_Container;

				// Reset pointers and counters
				Data_Container = nullptr;
				Capacity = 0;
				Current_Size = 0;

			}

			// Add Function
			void Add(X_Data_Type _X, Y_Data_Type _Y) {

				// Check Capacity
				if (Current_Size == Capacity) Resize();

				// Add new data
				Data_Container[Current_Size++] = Data_XY<X_Data_Type, Y_Data_Type>(_X, _Y);

			}

			// Get Function
			Y_Data_Type* Get(X_Data_Type _X) {

				// Search for X
				for (uint16_t i = 0; i < Current_Size; i++) {

					// Check X
					if (Data_Container[i]._Data_X == _X) return &Data_Container[i]._Data_Y;

				}

				// Return Null
				return nullptr;
			}

			// Get X Function
			X_Data_Type GetX(uint16_t index) {

				// Check Index
				if (index < Current_Size) return Data_Container[index]._Data_X;

				// Return Null
				return X_Data_Type();

			}

			// Get Y Function
			Y_Data_Type GetY(uint16_t index) {

				// Check Index
				if (index < Current_Size) return Data_Container[index]._Data_Y;

				// Return Null
				return Y_Data_Type();

			}

			// Size Function
			uint16_t Size() const {

				// Return Size
				return Current_Size;

			}

			// Clear Function
			void Clear() {

				// Delete existing data
				delete[] Data_Container;

				// Reset pointers and counters
				Data_Container = nullptr;
				Capacity = 0;
				Current_Size = 0;

			}

	};

	// Linear Regression
	template<typename X_Data_Type, typename Y_Data_Type> class Regression {

		// Private Context
		private:

			// Declare Data Container
			Dynamic_Data_2D<X_Data_Type, Y_Data_Type> dataContainer;

		// Public Context
		public:

			// Add Function
			void Add(X_Data_Type x, Y_Data_Type y) {
				
				// Add Data
				dataContainer.Add(x, y);

			}

			// Calculate Function
			double Slope(void) {

				// Declare Variables
				double sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0;
				uint16_t n = dataContainer.Size();

				// Calculate Slope
				for (uint16_t i = 0; i < n; i++) {
					double x = dataContainer.GetX(i);
					double y = dataContainer.GetY(i);
					sumX += x;
					sumY += y;
					sumXY += x * y;
					sumX2 += x * x;
				}

				// Return Slope
				return (n * sumXY - sumX * sumY) / (n * sumX2 - sumX * sumX);

			}

			// Calculate Function
			double Offset(void) {

				// Declare Variables
				double sumX = 0, sumY = 0;
				uint16_t n = dataContainer.Size();

				// Calculate Offset
				for (uint16_t i = 0; i < n; i++) {
					double x = dataContainer.GetX(i);
					double y = dataContainer.GetY(i);
					sumX += x;
					sumY += y;
				}

				// Return Offset
				double meanX = sumX / n;
				double meanY = sumY / n;

				// Return Offset
				return meanY - Slope() * meanX;

			}

			// Calculate Function
			double R2() {

				// Declare Variables
				double sumY = 0, sumY2 = 0, sumPredictedY2 = 0;
				uint16_t n = dataContainer.Size();
				double slope = Slope();
				double offset = Offset();

				// Calculate R2
				for (uint16_t i = 0; i < n; i++) {

					// Calculate R2
					double y = dataContainer.GetY(i);
					sumY += y;
					sumY2 += y * y;
					double predictedY = offset + slope * dataContainer.GetX(i);
					sumPredictedY2 += (predictedY - y) * (predictedY - y);

				}

				// Return R2
				double meanY = sumY / n;
				double totalVariance = sumY2 - n * meanY * meanY;
				double unexplainedVariance = sumPredictedY2;

				// Return R2
				return 1 - (unexplainedVariance / totalVariance);

			}

	};

	// Vector Statistics
	class Vector_Stats {

		// Private Context	
		private:

			// Declare Variables
			double sumX = 0;
			double sumY = 0;

		// Public Context
		public:

			// Add Vector Function
			void Add(double magnitude, double angle) {

				// Convert angle to radians
				double angleRad = radians(angle);

				// Add to sum
				sumX += magnitude * cos(angleRad);
				sumY += magnitude * sin(angleRad);

			}

			// Get X Magnitude Function
			double Get_X_Magnitude(void) {
				
				// Return X Magnitude
				return sumX;

			}

			// Get Y Magnitude Function
			double Get_Y_Magnitude(void) {
				
				// Return Y Magnitude
				return sumY;

			}

			// Get Total Magnitude Function
			double Total_Magnitude(void) {
				
				// Return Total Magnitude
				return sqrt(sumX * sumX + sumY * sumY);

			}

			// Get Total Angle Function
			double Total_Angle(void) {
				
				// Return Total Angle
				return degrees(atan2(sumY, sumX));

			}

		};

#endif /* defined(__Statistical__) */
