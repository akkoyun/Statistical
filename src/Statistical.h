/* *******************************************************************************
 *  Copyright (C) 2014-2020 Mehmet Gunce Akkoyun Can not be copied and/or
 *	distributed without the express permission of Mehmet Gunce Akkoyun.
 *
 *	Library				: Linear Regression Library
 *	Code Developer		: Mehmet Gunce Akkoyun (akkoyun@me.com)
 *	Revision			: 01.00.01
 *
 *********************************************************************************/

#ifndef __Statistical__
#define __Statistical__

#include <Arduino.h>

class Statistical {

public:

	// ************************************************************
	// Public Variables
	// ************************************************************
	float 			Stream_Average 		= 0;
	float 			Stream_Minimum 		= 0;
	float 			Stream_Maximum 		= 0;
	int				Data_Count			= 0;
	float 			Array_Average 		= 0;
	float 			Array_SDev 			= 0;
	float 			Array_Minimum 		= 0;
	float 			Array_Maximum 		= 0;

	
	// ************************************************************
	// Public Functions
	// ************************************************************
	void Stream_Statistic(float _Data);
	void Stream_Clear(void);
	void Array_Statistic(float _Data[], int _Data_Count, int _AVG_Type);
	
private:

	// ************************************************************
	// Private Variables
	// ************************************************************


	// ************************************************************
	// Private Functions
	// ************************************************************

};

#endif /* defined(__Statistical__) */
