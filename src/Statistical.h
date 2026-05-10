#ifndef __Statistical__
#define __Statistical__

	#include <Arduino.h>

	// =========================================================================
	// Array_Stats<T>
	// Wraps a user-supplied array. No internal copies, no heap allocation.
	// =========================================================================
	template <typename Data_Type> class Array_Stats {

		private:

			// Compute quartile assuming the array is already sorted.
			// Called internally by Quartile() and IQR() to avoid double-sort.
			float _Quartile_Sorted(const uint8_t _Q) const {
				float _Mult = 0;
				if      (_Q == 1) _Mult = 0.25f;
				else if (_Q == 2) _Mult = 0.50f;
				else if (_Q == 3) _Mult = 0.75f;
				else return 0;
				float  _Pos  = (float)(this->Data_Count + 1) * _Mult;
				size_t _Idx  = (size_t)_Pos;
				if (_Idx == 0)                    _Idx = 1;
				if (_Idx >= this->Data_Count)     _Idx = this->Data_Count - 1;
				float  _Frac = _Pos - (float)(int)_Pos;
				float  _Val  = (float)this->Data[_Idx - 1]
				             + _Frac * ((float)this->Data[_Idx] - (float)this->Data[_Idx - 1]);
				if (isnan(_Val) || isinf(_Val)) return 0;
				return _Val;
			}

		protected:

			Data_Type * Data;
			size_t      Data_Count;

		public:

			// Average type selector
			enum Average_Type : uint8_t {
				Arithmetic_Avg = 1,
				Geometric_Avg  = 2,
				RMS_Avg        = 3,
				Ext_RMS_Avg    = 4,
				Sigma_Avg      = 5
			};

			// Sigma filter width selector
			enum Sigma_Type : uint8_t {
				Sigma_1 = 1,
				Sigma_2 = 2,
				Sigma_3 = 3,
				Sigma_4 = 4
			};

			Array_Stats(Data_Type * _Data, size_t _Data_Count)
				: Data(_Data), Data_Count(_Data_Count) {}

			// Dispatch average by type
			float Average(const uint8_t _Type) {
				if (_Type == Arithmetic_Avg) return Arithmetic_Average();
				if (_Type == Geometric_Avg)  return Geometric_Average();
				if (_Type == RMS_Avg)        return RMS_Average();
				if (_Type == Ext_RMS_Avg)    return Ext_RMS_Average();
				if (_Type == Sigma_Avg)      return Sigma_Average(Sigma_1);
				return 0;
			}

			size_t Size(void) const { return this->Data_Count; }

			float Sum(void) {
				if (this->Data_Count == 0) return 0;
				float _S = 0;
				for (size_t i = 0; i < this->Data_Count; i++) _S += (float)this->Data[i];
				if (isnan(_S) || isinf(_S)) return 0;
				return _S;
			}

			float Max(void) {
				if (this->Data_Count == 0) return 0;
				float _M = (float)this->Data[0];
				for (size_t i = 1; i < this->Data_Count; i++) {
					float v = (float)this->Data[i];
					if (v > _M) _M = v;
				}
				if (isnan(_M) || isinf(_M)) return 0;
				return _M;
			}

			float Min(void) {
				if (this->Data_Count == 0) return 0;
				float _M = (float)this->Data[0];
				for (size_t i = 1; i < this->Data_Count; i++) {
					float v = (float)this->Data[i];
					if (v < _M) _M = v;
				}
				if (isnan(_M) || isinf(_M)) return 0;
				return _M;
			}

			float Sq_Sum(void) {
				if (this->Data_Count == 0) return 0;
				float _S = 0;
				for (size_t i = 0; i < this->Data_Count; i++) {
					float v = (float)this->Data[i];
					_S += v * v;
				}
				if (isnan(_S) || isinf(_S)) return 0;
				return _S;
			}

			float Arithmetic_Average(void) {
				if (this->Data_Count == 0) return 0;
				float _A = Sum() / (float)this->Data_Count;
				if (isnan(_A) || isinf(_A)) return 0;
				return _A;
			}

			// Undefined for non-positive values; returns 0 if any element <= 0
			float Geometric_Average(void) {
				if (this->Data_Count == 0) return 0;
				float _LS = 0;
				for (size_t i = 0; i < this->Data_Count; i++) {
					float v = (float)this->Data[i];
					if (v <= 0) return 0;
					_LS += (log(v) - _LS) / (float)(i + 1);
				}
				float _G = exp(_LS);
				if (isnan(_G) || isinf(_G)) return 0;
				return _G;
			}

			// Rejects values outside ±_Sigma standard deviations, returns mean of survivors.
			// Welford one-pass mean+variance (pass 1), then outlier-filter (pass 2).
			// Previous 4-pass implementation replaced: Arithmetic_Average + Standard_Deviation
			// each did 2 passes; now the same result requires only 2 total passes.
			float Sigma_Average(const uint8_t _Sigma) {
				if (this->Data_Count < 2) return 0;
				// Pass 1: Welford online mean + M2 (sum of squared deviations from running mean)
				float _Mean = 0, _M2 = 0;
				for (size_t i = 0; i < this->Data_Count; i++) {
					float v     = (float)this->Data[i];
					float delta = v - _Mean;
					_Mean += delta / (float)(i + 1);
					_M2   += delta * (v - _Mean);
				}
				float _Dev = sqrt(_M2 / (float)(this->Data_Count - 1));
				// Pass 2: reject outliers, compute filtered mean
				float  _Lo  = _Mean - (float)_Sigma * _Dev;
				float  _Hi  = _Mean + (float)_Sigma * _Dev;
				float  _Sum = 0;
				size_t _N   = 0;
				for (size_t i = 0; i < this->Data_Count; i++) {
					float v = (float)this->Data[i];
					if (v > _Lo && v < _Hi) { _Sum += v; _N++; }
				}
				if (_N == 0) return 0;
				return _Sum / (float)_N;
			}

			float RMS_Average(void) {
				if (this->Data_Count == 0) return 0;
				float _R = sqrt(Sq_Sum() / (float)this->Data_Count);
				if (isnan(_R) || isinf(_R)) return 0;
				return _R;
			}

			// Excludes the single min and max element before computing RMS
			float Ext_RMS_Average(void) {
				if (this->Data_Count <= 2) return 0;
				float _mn = Min(), _mx = Max();
				float _S  = Sq_Sum() - _mn * _mn - _mx * _mx;
				float _E  = sqrt(_S / (float)(this->Data_Count - 2));
				if (isnan(_E) || isinf(_E)) return 0;
				return _E;
			}

			// Sorts array in-place, then returns the requested quartile
			float Quartile(const uint8_t _Q) {
				if (this->Data_Count < 4) return 0;
				Bubble_Sort();
				return _Quartile_Sorted(_Q);
			}

			// Sorts array in-place once; computes Q1 and Q3 without double-sorting
			float IQR(void) {
				if (this->Data_Count < 4) return 0;
				Bubble_Sort();
				float _I = _Quartile_Sorted(3) - _Quartile_Sorted(1);
				if (isnan(_I) || isinf(_I)) return 0;
				return _I;
			}

			float Variance(void) {
				if (this->Data_Count < 2) return 0;
				float _A = Arithmetic_Average();
				float _V = 0;
				for (size_t i = 0; i < this->Data_Count; i++) {
					float d = (float)this->Data[i] - _A;
					_V += d * d;
				}
				if (isnan(_V) || isinf(_V)) return 0;
				return _V / (float)(this->Data_Count - 1);
			}

			// Shared implementation: Standard_Deviation = sqrt(Variance)
			float Standard_Deviation(void) {
				if (this->Data_Count < 2) return 0;
				float _SD = sqrt(Variance());
				if (isnan(_SD) || isinf(_SD)) return 0;
				return _SD;
			}

			float Standard_Deviation_Error(void) {
				if (this->Data_Count == 0) return 0;
				float _E = Standard_Deviation() / sqrt((float)this->Data_Count);
				if (isnan(_E) || isinf(_E)) return 0;
				return _E;
			}

			float Coefficient_Factor(void) {
				float _A = Arithmetic_Average();
				if (_A == 0) return 0;
				float _C = 100.0f * Standard_Deviation() / _A;
				if (isnan(_C) || isinf(_C)) return 0;
				return _C;
			}

			// In-place ascending sort (Bubble Sort, O(n²) — suitable for n ≤ 50)
			void Bubble_Sort(void) {
				size_t    _New_n;
				Data_Type _Tmp;
				do {
					_New_n = 1;
					for (size_t i = 1; i < this->Data_Count; i++) {
						if (this->Data[i - 1] > this->Data[i]) {
							_Tmp              = this->Data[i];
							this->Data[i]     = this->Data[i - 1];
							this->Data[i - 1] = _Tmp;
							_New_n = i;
						}
					}
				} while (_New_n > 1);
			}

			void Array(void) {
				for (size_t i = 0; i < this->Data_Count; i++) {
					Serial.print(F("[")); Serial.print(this->Data[i]); Serial.print(F("] "));
				}
				Serial.println();
			}

			// Shift left and append; loop bound is Data_Count-1 to avoid off-by-one read
			void FILO_Add_Data(const Data_Type _Data) {
				for (size_t i = 0; i < this->Data_Count - 1; i++) this->Data[i] = this->Data[i + 1];
				this->Data[this->Data_Count - 1] = _Data;
			}

			// Requires a heap-allocated pointer. Do NOT call on stack arrays.
			// Prefer FILO_Stats<T,N> for a heap-free alternative.
			bool Set_FILO_Size(const size_t _N) {
				if (_N == 0 || _N > 50) return false;
				void * _Tmp = realloc(this->Data, _N * sizeof(*this->Data));
				if (_Tmp == NULL) return false;
				this->Data       = (Data_Type*)_Tmp;
				this->Data_Count = _N;
				for (size_t i = 0; i < this->Data_Count; i++) this->Data[i] = 0;
				return true;
			}

	};

	// =========================================================================
	// FILO_Stats<T, N>
	// Fixed-size sliding window — owns its buffer, zero heap allocation.
	// All Array_Stats methods are available via inheritance.
	//
	//   FILO_Stats<float, 8> window;
	//   window.Add(23.4f);
	//   float avg = window.Arithmetic_Average();
	// =========================================================================
	template <typename Data_Type, size_t N> class FILO_Stats : public Array_Stats<Data_Type> {

		private:

			Data_Type _Buffer[N];

			// Non-copyable: copying would leave the base-class pointer dangling
			FILO_Stats(const FILO_Stats&)            = delete;
			FILO_Stats& operator=(const FILO_Stats&) = delete;

		public:

			FILO_Stats(void) : Array_Stats<Data_Type>(_Buffer, N) {
				for (size_t i = 0; i < N; i++) _Buffer[i] = 0;
			}

			// Push a new value into the sliding window
			void Add(const Data_Type _Data) { this->FILO_Add_Data(_Data); }

	};

	// =========================================================================
	// Stream_Stats<T>
	// Online Min / Max / Mean with constant memory (no array stored).
	// Internal average accumulator is always float for precision,
	// regardless of the template type T.
	// =========================================================================
	template <typename Data_Type> class Stream_Stats {

		private:

			uint16_t  Data_Count;
			float     _Avg;       // float accumulator prevents integer truncation
			Data_Type _Min;
			Data_Type _Max;
			Data_Type _Last;

		public:

			Stream_Stats(void) : Data_Count(0), _Avg(0), _Min(0), _Max(0), _Last(0) {}

			void Add(const Data_Type _Data) {
				if (this->Data_Count == 0) {
					this->_Max = _Data;
					this->_Min = _Data;
					this->_Avg = (float)_Data;
				} else {
					if (_Data > this->_Max) this->_Max = _Data;
					if (_Data < this->_Min) this->_Min = _Data;
					// Welford online mean — divide by new count before incrementing
					this->_Avg += ((float)_Data - this->_Avg) / (float)(this->Data_Count + 1);
				}
				this->_Last = _Data;
				this->Data_Count++;
			}

			void Clear(void) {
				this->Data_Count = 0;
				this->_Avg       = 0;
				this->_Min       = 0;
				this->_Max       = 0;
				this->_Last      = 0;
			}

			uint16_t Get_Data_Count(void) const { return this->Data_Count; }
			float    Get_Average(void)    const { return this->_Avg; }
			float    Get_Min(void)        const { return (float)this->_Min; }
			float    Get_Max(void)        const { return (float)this->_Max; }
			float    Get_Last(void)       const { return (float)this->_Last; }

	};

	// =========================================================================
	// Linear_Regression<X, Y>
	// Ordinary least squares: y = Slope * x + Offset
	//
	// Use Compute_All() when you need Slope, Offset, and R² together —
	// it computes all three in 2 array passes instead of 4.
	// =========================================================================
	template <typename Data_Type_X, typename Data_Type_Y> class Linear_Regression {

		private:

			Data_Type_X * Data_X;
			Data_Type_Y * Data_Y;
			size_t        Data_Count;

			// All sums needed for Slope and Offset, computed in one pass
			struct _LinSums {
				float Sx, Sy, Sx2, Sxy, Denom;
			};

			_LinSums _Sums(void) const {
				_LinSums s = {0, 0, 0, 0, 0};
				for (size_t i = 0; i < this->Data_Count; i++) {
					float x = (float)this->Data_X[i];
					float y = (float)this->Data_Y[i];
					s.Sx  += x;
					s.Sy  += y;
					s.Sx2 += x * x;
					s.Sxy += x * y;
				}
				s.Denom = (float)this->Data_Count * s.Sx2 - s.Sx * s.Sx;
				return s;
			}

			// Second pass: coefficient of determination from pre-computed sums
			float _R2_From_Sums(const _LinSums& s) const {
				if (s.Denom == 0) return 0;
				float _Mx = s.Sx / (float)this->Data_Count;
				float _My = s.Sy / (float)this->Data_Count;
				float _Sxy = 0, _Sx2 = 0, _Sy2 = 0;
				for (size_t i = 0; i < this->Data_Count; i++) {
					float dx = (float)this->Data_X[i] - _Mx;
					float dy = (float)this->Data_Y[i] - _My;
					_Sxy += dx * dy;
					_Sx2 += dx * dx;
					_Sy2 += dy * dy;
				}
				float _D = _Sx2 * _Sy2;
				if (_D == 0) return 0;
				float _R2 = (_Sxy * _Sxy) / _D;
				if (isnan(_R2) || isinf(_R2)) return 0;
				return _R2;
			}

		public:

			// Result type for Compute_All()
			struct Regression_Result {
				float Slope;
				float Offset;
				float R2;
			};

			Linear_Regression(Data_Type_X * _Dx, Data_Type_Y * _Dy, size_t _N)
				: Data_X(_Dx), Data_Y(_Dy), Data_Count(_N) {}

			float Slope(void) {
				if (this->Data_Count < 2) return 0;
				_LinSums s = _Sums();
				return (s.Denom == 0) ? 0 : ((float)this->Data_Count * s.Sxy - s.Sx * s.Sy) / s.Denom;
			}

			float Offset(void) {
				if (this->Data_Count < 2) return 0;
				_LinSums s = _Sums();
				return (s.Denom == 0) ? 0 : (s.Sx2 * s.Sy - s.Sx * s.Sxy) / s.Denom;
			}

			float R2(void) {
				if (this->Data_Count < 2) return 0;
				return _R2_From_Sums(_Sums());
			}

			// Computes Slope, Offset, and R² in 2 passes — use instead of calling
			// the three functions separately when all values are needed at once.
			Regression_Result Compute_All(void) {
				Regression_Result _Res = {0, 0, 0};
				if (this->Data_Count < 2) return _Res;
				_LinSums s = _Sums();                                 // pass 1
				if (s.Denom != 0) {
					_Res.Slope  = ((float)this->Data_Count * s.Sxy - s.Sx * s.Sy) / s.Denom;
					_Res.Offset = (s.Sx2 * s.Sy - s.Sx * s.Sxy) / s.Denom;
				}
				_Res.R2 = _R2_From_Sums(s);                          // pass 2
				return _Res;
			}

	};

	// =========================================================================
	// Vector_Stats<M, A>
	// Polar vector addition (magnitude + compass bearing).
	// Convention: 0° = North, 90° = East, angles increase clockwise.
	// =========================================================================
	template <typename Data_Type_Magnitude, typename Data_Type_Angle> class Vector_Stats {

		protected:

			Data_Type_Magnitude * Data_Magnitude;
			Data_Type_Angle     * Data_Angle;
			size_t                Vector_Count;

		public:

			struct {
				float Magnitude;
				float Angle;
			} Result;

			Vector_Stats(Data_Type_Magnitude * _Mag, Data_Type_Angle * _Ang, size_t _N)
				: Data_Magnitude(_Mag), Data_Angle(_Ang), Vector_Count(_N) {
				this->Result.Magnitude = 0;
				this->Result.Angle     = 0;
			}

			// Sums all vectors and stores the resultant in Result.Magnitude / Result.Angle
			void Vector_Sum(void) {
				float _Sx = 0, _Sy = 0;
				for (size_t i = 0; i < this->Vector_Count; i++) {
					float _Rad = (float)this->Data_Angle[i] * (PI / 180.0f);
					_Sx += (float)this->Data_Magnitude[i] * sin(_Rad);  // East component
					_Sy += (float)this->Data_Magnitude[i] * cos(_Rad);  // North component
				}
				this->Result.Magnitude = sqrt(_Sx * _Sx + _Sy * _Sy);
				if (this->Result.Magnitude == 0) { this->Result.Angle = 0; return; }
				// atan2 gives CCW from East; convert to CW compass bearing from North
				this->Result.Angle = fmod(90.0f - degrees(atan2(_Sy, _Sx)) + 360.0f, 360.0f);
			}

	};

#endif /* defined(__Statistical__) */
