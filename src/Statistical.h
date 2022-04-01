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

class Array_Stats {

	private:
		
		// Declare Data Array
		double * Data;

		// Declare Data Count
		uint16_t Data_Count;

	public:

		// Define Average Type
		enum Average_Type {
			Arithmetic_Avg	= (uint8_t)1,
			Geometric_Avg	= (uint8_t)2,
			RMS_Avg			= (uint8_t)3,
			Ext_RMS_Avg		= (uint8_t)4
		};

		/**
		 * @brief Function constractor
		 * @version 01.00.00
		 * @param _Data Data array
		 * @param _Data_Count Array size
		 */
		template<typename Data_Type> Array_Stats(Data_Type * _Data, uint16_t _Data_Count) : Data(_Data), Data_Count(_Data_Count) {

		}

		/**
		 * @brief Function deconstractor
		 * @version 01.00.00
		 */
		~Array_Stats(void);

		/**
		 * @brief Calculate the array average batch.
		 * @version 01.00.00
		 * @param _Average_Type Average Type
		 * @return float - Average value of array.
		 */
		float Average(uint8_t _Average_Type);

		/**
		 * @brief Get data array size
		 * @version 01.00.00
		 */	
		uint16_t Size(void);

		/**
		 * @brief Calculate the array sum.
		 * @version 01.00.00
		 * @return Sum value of array.
		 */
		float Sum(void);

		/**
		 * @brief Calculate the array max value.
		 * @version 01.00.00
		 * @return float - Max value of array.
		 */
		float Max(void);

		/**
		 * @brief Calculate the array min value.
		 * @version 01.00.00
		 * @return float - Min value of array.
		 */
		float Min(void);

		/**
		 * @brief Calculate the array square sum.
		 * @version 01.00.00
		 * @return float - Square total value of array.
		 */
		float Sq_Sum(void);

		/**
		 * @brief Calculate the array arithmetic average.
		 * @version 01.00.00
		 * @return float - Arithmetic average value of array.
		 */
		float Arithmetic_Average(void);

		/**
		 * @brief Calculate the array geometric average.
		 * @version 01.00.00
		 * @return float - Geometric average value of array.
		 */
		float Geometric_Average(void);

		/**
		 * @brief Calculate the array RMS average.
		 * @version 01.00.00
		 * @return float - RMS average value of array.
		 */
		float RMS_Average(void);

		/**
		 * @brief Calculate the array extended RMS average.
		 * @version 01.00.00
		 * @return float - Extended RMS average value of array.
		 */
		float Ext_RMS_Average(void);

		/**
		 * @brief Calculate the array quartile.
		 * @version 01.00.00
		 * @return float - Quartile value of array.
		 */
		float Quartile(const uint8_t _Q);

		/**
		 * @brief Calculate the array IQR.
		 * @version 01.00.00
		 * @return float - IQR value of array.
		 */
		float IQR(void);

		/**
		 * @brief Calculate the array standard deviation.
		 * @version 01.00.00
		 * @return float - Standard deviation value of array.
		 */
		float Standard_Deviation(void);

		/**
		 * @brief Calculate the array standard deviation error.
		 * @version 01.00.00
		 * @return float - Standard deviation error value of array.
		 */
		float Standard_Deviation_Error(void);

		/**
		 * @brief Calculate the array coefficient factor.
		 * @version 01.00.00
		 * @return float - Coefficient factor value of array.
		 */
		float Coefficient_Factor(void);

		/**
		 * @brief Calculate the array variance.
		 * @version 01.00.00
		 * @return float - Variance value of array.
		 */
		float Variance(void);

		/**
		 * @brief Sort the array from min to max.
		 * @version 01.00.00
		 */
		void Bubble_Sort(void);

		/**
		 * @brief Set Array FILO
		 * @version 01.00.00
		 * @param _Data_X Array size
		 * @param _Data_Y New Array Data
		 */	
		void FILO(float _Array[][2], uint16_t _Data_Count, float _Data_X, float _Data_Y);

		/**
		 * @brief Print Full Array
		 * @version 01.00.00
		 */
		void Array(void);

		/**
		 * @brief Set FILO array size
		 * @version 01.00.00
		 * @param _FILO_Size Array size
		 */	
		bool Set_FILO_Size(const uint8_t _FILO_Size);

		/**
		 * @brief FILO data add to array
		 * @version 01.00.00
		 * @param _Data data
		 */	
		void FILO_Add_Data(const float _Data);

};

class Stream_Stats {

	private:

		// Declare Data Count
		uint16_t Data_Count;

		// Declare Stat Variable
		float Average;
		float Min;
		float Max;

	public:

		/**
		 * @brief Function constractor
		 * @version 01.00.00
		 */
		Stream_Stats(void);

		/**
		 * @brief Function deconstractor
		 * @version 01.00.00
		 */
		~Stream_Stats(void);

		/**
		 * @brief Add Stream Data
		 * @version 01.00.00
		 * @param _Data Stream Data
		 */
		void Add_Data(const float _Data);

		/**
		 * @brief Clear Stream Statistic Parameters
		 * @version 01.00.00
		 */
		void Data_Clear(void);

		/**
		 * @brief Get stream data count
		 * @version 01.00.00
		 */
		uint16_t Get_Data_Count(void);

		/**
		 * @brief Get stream average
		 * @version 01.00.00
		 */
		float Get_Average(void);

		/**
		 * @brief Get stream minimum value
		 * @version 01.00.00
		 */
		float Get_Min(void);

		/**
		 * @brief Get stream maximum value
		 * @version 01.00.00
		 */
		float Get_Max(void);

};

class Linear_Regression {

	private:

		// Declare Data Array X
		uint32_t * Data_X;

		// Declare Data Array Y
		float * Data_Y;

		// Declare Data Count
		uint8_t Data_Count;

	public:

		/**
		 * @brief Function constractor
		 * @version 01.00.00
		 */
		Linear_Regression(uint32_t * _Data_X, float * _Data_Y, uint8_t _Data_Count);

		/**
		 * @brief Function deconstractor
		 * @version 01.00.00
		 */
		~Linear_Regression(void);

		/**
		 * @brief Calculate Regression Offset
		 * @version 01.00.00
		 * @return float Offset Value
		 */
		float Offset(void);

		/**
		 * @brief Calculate Regression Slope
		 * @version 01.00.00
		 * @return float Slope Value
		 */
		float Slope(void);
		
		/**
		 * @brief Calculate Regression R2
		 * @version 01.00.00
		 * @return float R2 Value
		 */
		float R2(void);

};

#endif /* defined(__Statistical__) */
