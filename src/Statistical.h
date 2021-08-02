/* *******************************************************************************
 *  Copyright (C) 2014-2020 Mehmet Gunce Akkoyun Can not be copied and/or
 *	distributed without the express permission of Mehmet Gunce Akkoyun.
 *
 *	Library				: Linear Regression Library
 *	Code Developer		: Mehmet Gunce Akkoyun (akkoyun@me.com)
 *	Revision			: 01.01.01
 *
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
	int				Data_Count							= 0;

	// Stream Data Definations
	float 			Stream_Average 						= 0;
	float 			Stream_Minimum 						= 0;
	float 			Stream_Maximum 						= 0;
	
	// Array Data Definations
	float 			Array_Average 						= 0;
	float 			Array_SDev 							= 0;
	float 			Array_Minimum 						= 0;
	float 			Array_Maximum 						= 0;

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
	void Array_Statistic(float _Data[], int _Data_Count, int _AVG_Type);
	void LinearRegression(float _X, float _Y);
	
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
