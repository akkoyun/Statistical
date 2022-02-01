/* *******************************************************************************
 *  Copyright (C) 2014-2020 Mehmet Gunce Akkoyun Can not be copied and/or
 *	distributed without the express permission of Mehmet Gunce Akkoyun.
 *
 *	Library				: Linear Regression Library
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
	
	// Array Data Definations
	float 			Array_Sum 							= 0;
	float 			Array_Sq_Sum						= 0;
	float 			Array_Min 							= 0;
	float 			Array_Max	 						= 0;
	float 			Array_AAvg	 						= 0;
	float 			Array_GAvg	 						= 0;
	float 			Array_RMS_Avg 						= 0;
	float 			Array_Ext_RMS_Avg					= 0;
	float 			Array_Sigma_Avg 					= 0;
	uint16_t		Array_Sigma_Size 					= 0;
	float 			Array_Med							= 0;
	float 			Array_SDev 							= 0;
	float 			Array_SDev_Err						= 0;
	float 			Array_Coef							= 0;

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
	void Data_Clear(void);
	void LinearRegression(float _X, float _Y);
	
	void Array_Statistic(float _Data[], int _Data_Count);
	float Array_Average(float _Data[], uint16_t _Data_Count, uint8_t _Average_Type);
	void Array_Total(float _Data[], uint16_t _Data_Count);
	void Array_Sq_Total(float _Data[], uint16_t _Data_Count);
	void Array_Maximum(float _Data[], uint16_t _Data_Count);
	void Array_Minimum(float _Data[], uint16_t _Data_Count);
	void Array_Aritmetic_Average(float _Data[], uint16_t _Data_Count);
	void Array_Sigma_Aritmetic_Average(float _Data[], uint16_t _Data_Count, uint8_t _Sigma);
	void Array_Geometric_Average(float _Data[], uint16_t _Data_Count);
	void Array_Standart_Deviation(float _Data[], uint16_t _Data_Count);
	void Array_Standart_Deviation_Error(float _Data[], uint16_t _Data_Count);
	void Array_Coefficient_Factor(float _Data[], uint16_t _Data_Count);
	void Array_Bubble_Sort(float _Data[], uint16_t _Data_Count);
	void Array_Median(float _Data[], uint16_t _Data_Count);
	void Array_RMS_Average(float _Data[], uint16_t _Data_Count);
	void Array_Ext_RMS_Average(float _Data[], uint16_t _Data_Count);
	void Array_Statistic_Clear(void);

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
