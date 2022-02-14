# Statistical 
> version 1.3.0

Descriptive statistics for Arduino float arrays

We developed this library to help quickly accomplish median and mode filtering when collecting sensor data. Functions in this library operate on an array of float variables, of dimension "m", and return the corresponding statistic. This library was originally created for a data smoothing strategy for float variables. Using a median or mode filtering strategy (opposed to mean filtering) is better at removing spikes from aberrant readings. 

A bubble sort algorithm is also contained in this library which was necessary to calculate median and mode.

### Array Statistics

    Array_Sum
    Array_Max
    Array_Min
    Array_Sq_Sum
    Array_Aritmetic_Average
    Array_Geometric_Average
    Array_RMS_Average
    Array_Ext_RMS_Average
    Array_Bubble_Sort
    Array_Median
    Array_Standart_Deviation
    Array_Standart_Deviation_Error
    Array_Coefficient_Factor
    Array_Average

### Stream Statistics

	Stream_Statistic
	Data_Clear
	LinearRegression

	Stream_Average
	Stream_Minimum
	Stream_Maximum
	
	Linear_Regression_MeanX
	Linear_Regression_MeanX2
	Linear_Regression_VarianceX
	Linear_Regression_MeanY
	Linear_Regression_MeanY2
	Linear_Regression_MeanXY
	Linear_Regression_VarianceY
	Linear_Regression_CovarianceXY
	Linear_Regression_a
	Linear_Regression_b

