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

class Statistical {

public:

	// ************************************************************
	// Public Variables
	// ************************************************************

	// Stream Calculation Variables
	uint16_t		Stream_Data_Count_Max				= 0;
	float 			Stream_Maximum 						= 0;
	uint16_t		Stream_Data_Count_Min				= 0;
	float 			Stream_Minimum 						= 0;
	uint16_t		Stream_Data_Count_Avg				= 0;
	float 			Stream_Average 						= 0;
	
	// Linear Regression Definations
	uint16_t		Linear_Regression_Data_Count		= 0;
	uint16_t		Linear_Regression_Presicion			= 0;
	float 			Linear_Regression_Slope				= 0;
	float 			Linear_Regression_Offset			= 0;
	
	// ************************************************************
	// Public Functions
	// ************************************************************

	/**
	 * @brief Calculate Stream Maximum Value
	 * @version 01.00.00
	 * @param _Data Data Variable
	 */
	float Stream_Max(float _Data);

	/**
	 * @brief Calculate Stream Minimum Value
	 * @version 01.00.00
	 * @param _Data Data Variable
	 */
	float Stream_Min(float _Data);

	/**
	 * @brief Calculate Stream Average Value
	 * @version 01.00.00
	 * @param _Data Data Variable
	 */
	float Stream_Aritmetic_Average(float _Data);

	/**
	 * @brief Clear Stream Maximum Value
	 * @version 01.00.00
	 */
	void Stream_Clear_Max(void);

	/**
	 * @brief Clear Stream Minimum Value
	 * @version 01.00.00
	 */
	void Stream_Clear_Min(void);

	/**
	 * @brief Clear Stream Average Value
	 * @version 01.00.00
	 */
	void Stream_Clear_Aritmetic_Average(void);

	/**
	 * @brief Calculate Min, Max, Avg Value
	 * @version 01.00.00
	 */
	void Stream_Statistic(float _Data);

	/**
	 * @brief Clear Stream Values
	 * @version 01.00.00
	 */
	void Stream_Clear(void);

	/**
	 * @brief Calculate Linear Regression
	 * @version 01.00.00
	 * @param _X Data array
	 * @param _Y Data size
	 */
	void Linear_Regression(float _X, float _Y);

	/**
	 * @brief Linear Regression Data Clear
	 * @version 01.00.00
	 */
	void Linear_Regression_Data_Clear(void);

	/**
	 * @brief Linear Regression Calculate
	 * @version 01.00.00
	 */
	void Linear_Regression_Calculate(float _Data[][2]);

	/**
	 * @brief Calculate the array sum.
	 * @version 01.00.00
	 * @param _Data Data array
	 * @param _Data_Count Array size
	 * @return float - Sum value of array.
	 */
	float Array_Sum(float _Data[], uint16_t _Data_Count);

	/**
	 * @brief Calculate the array max value.
	 * @version 01.00.00
	 * @param _Data Data array
	 * @param _Data_Count Array size
	 * @return float - Max value of array.
	 */
	float Array_Max(float _Data[], uint16_t _Data_Count);

	/**
	 * @brief Calculate the array min value.
	 * @version 01.00.00
	 * @param _Data Data array
	 * @param _Data_Count Array size
	 * @return float - Min value of array.
	 */
	float Array_Min(float _Data[], uint16_t _Data_Count);

	/**
	 * @brief Calculate the array square sum.
	 * @version 01.00.00
	 * @param _Data Data array
	 * @param _Data_Count Array size
	 * @return float - Square total value of array.
	 */
	float Array_Sq_Sum(float _Data[], uint16_t _Data_Count);

	/**
	 * @brief Calculate the array aritmetic average.
	 * @version 01.00.00
	 * @param _Data Data array
	 * @param _Data_Count Array size
	 * @return float - Aritmetic average value of array.
	 */
	float Array_Aritmetic_Average(float _Data[], uint16_t _Data_Count);

	/**
	 * @brief Calculate the array geometric average.
	 * @version 01.00.00
	 * @param _Data Data array
	 * @param _Data_Count Array size
	 * @return float - Geometric average value of array.
	 */
	float Array_Geometric_Average(float _Data[], uint16_t _Data_Count);

	/**
	 * @brief Calculate the array RMS average.
	 * @version 01.00.00
	 * @param _Data Data array
	 * @param _Data_Count Array size
	 * @return float - RMS average value of array.
	 */
	float Array_RMS_Average(float _Data[], uint16_t _Data_Count);

	/**
	 * @brief Calculate the array extended RMS average.
	 * @version 01.00.00
	 * @param _Data Data array
	 * @param _Data_Count Array size
	 * @return float - Extendet RMS average value of array.
	 */
	float Array_Ext_RMS_Average(float _Data[], uint16_t _Data_Count);

	/**
	 * @brief Sort the array from min to max.
	 * @version 01.00.00
	 * @param _Data Data array
	 * @param _Data_Count Array size
	 */
	void Array_Bubble_Sort(float _Data[], uint16_t _Data_Count);

	/**
	 * @brief Calculate the array median average.
	 * @version 01.00.00
	 * @param _Data Data array
	 * @param _Data_Count Array size
	 * @return float - Median average value of array.
	 */
	float Array_Median(float _Data[], uint16_t _Data_Count);

	/**
	 * @brief Calculate the array standart deviation.
	 * @version 01.00.00
	 * @param _Data Data array
	 * @param _Data_Count Array size
	 * @return float - Standart deviation value of array.
	 */
	float Array_Standart_Deviation(float _Data[], uint16_t _Data_Count);

	/**
	 * @brief Calculate the array standart deviation error.
	 * @version 01.00.00
	 * @param _Data Data array
	 * @param _Data_Count Array size
	 * @return float - Standart deviation error value of array.
	 */
	float Array_Standart_Deviation_Error(float _Data[], uint16_t _Data_Count);

	/**
	 * @brief Calculate the array coefficient factor.
	 * @version 01.00.00
	 * @param _Data Data array
	 * @param _Data_Count Array size
	 * @return float - Coefficient factor value of array.
	 */
	float Array_Coefficient_Factor(float _Data[], uint16_t _Data_Count);

	/**
	 * @brief Calculate the array average batch.
	 * @version 01.00.00
	 * @param _Data Data array
	 * @param _Data_Count Array size
	 * @return float - Average value of array.
	 */
	float Array_Average(float _Data[], int _Data_Count, int _AVG_Type);

	/**
	 * @brief Set Array FILO
	 * @version 01.00.00
	 * @param _Array Data array
	 * @param _Data_Count Array size
	 * @param _Data New Array Data
	 */	
	void Array_FILO(float _Array[][2], uint16_t _Data_Count, float _X, float _Y);

private:

	// ************************************************************
	// Private Variables
	// ************************************************************

	// Linear Regression Variables
	float 			Linear_Regression_MeanX				= 0;
	float 			Linear_Regression_MeanX2			= 0;
	float 			Linear_Regression_VarianceX			= 0;
	float 			Linear_Regression_MeanY				= 0;
	float 			Linear_Regression_MeanY2			= 0;
	float 			Linear_Regression_MeanXY			= 0;
	float 			Linear_Regression_VarianceY			= 0;
	float 			Linear_Regression_CovarianceXY		= 0;
	
	// ************************************************************
	// Private Functions
	// ************************************************************

};

extern Statistical Stats;

#endif /* defined(__Statistical__) */
