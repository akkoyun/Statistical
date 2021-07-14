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
	uint16_t		Data_Count			= 0;

	
	// ************************************************************
	// Public Functions
	// ************************************************************
	void Stream_Statistic(float _Data);
	void Stream_Clear(void);

private:

	// ************************************************************
	// Private Variables
	// ************************************************************


	// ************************************************************
	// Private Functions
	// ************************************************************

};

#endif /* defined(__Statistical__) */
