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

	// Data Count Definations
	uint16_t		Data_Count							= 0;

	// Stream Data Definations
	float 			Stream_Average 						= 0;
	float 			Stream_Minimum 						= 0;
	float 			Stream_Maximum 						= 0;
	
	// Linear Regression Definations
	float 			Linear_Regression_MeanX				= 0;
	float 			Linear_Regression_MeanX2			= 0;
	float 			Linear_Regression_VarianceX			= 0;
	float 			Linear_Regression_MeanY				= 0;
	float 			Linear_Regression_MeanY2			= 0;
	float 			Linear_Regression_MeanXY			= 0;
	float 			Linear_Regression_VarianceY			= 0;
	float 			Linear_Regression_CovarianceXY		= 0;
	float 			Linear_Regression_a					= 0;
	float 			Linear_Regression_b					= 0;
	
	// ************************************************************
	// Public Functions
	// ************************************************************
	void Stream_Statistic(float _Data);
	void LinearRegression(float _X, float _Y);
	void Data_Clear(void);

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

private:

	// ************************************************************
	// Private Variables
	// ************************************************************

	
	// ************************************************************
	// Private Functions
	// ************************************************************

};

extern Statistical Stats;

#endif /* defined(__Statistical__) */
