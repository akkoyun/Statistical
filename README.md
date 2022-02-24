# Statistical Library <sup>V1.4</sup>

![GitHub release (latest by date)](https://img.shields.io/github/v/release/akkoyun/Statistical) ![arduino-library-badge](https://www.ardu-badge.com/badge/Statistical.svg?) ![Visits Badge](https://badges.pufler.dev/visits/akkoyun/Statistical) ![GitHub stars](https://img.shields.io/github/stars/akkoyun/Statistical?style=flat&logo=github) ![Updated Badge](https://badges.pufler.dev/updated/akkoyun/Statistical) ![PlatformIO Registry](https://badges.registry.platformio.org/packages/akkoyun/library/Statistical.svg)

	Build - 01.04.02

---

**Abstract**

 Descriptive statistics for Arduino float arrays

We developed this library to help quickly accomplish median and mode filtering when collecting sensor data. Functions in this library operate on an array of float variables, of dimension "m", and return the corresponding statistic. This library was originally created for a data smoothing strategy for float variables. Using a median or mode filtering strategy (opposed to mean filtering) is better at removing spikes from aberrant readings. 

A bubble sort algorithm is also contained in this library which was necessary to calculate median and mode.

**Array Statistics**

Library calculate listed statistical parameters for fixed size arrays.

	* Sum
	* Maximum
	* Minimum
	* Square Sum
	* Aritmetic Average
	* Geometric Average
	* RMS Average
	* 1 Sigma RMS Average
	* Bubble Sort
	* Median
	* Standart Deviation
	* Standart Deviation Error
	* Coefficient Factor
	* Array FILO

**Stream Statistics**

Library calculate listed statistical parameters for data streams.

	* Data Count
	* Aritmetic Average
	* Minimum
	* Maximum

**Array Linear Regression**

Library calculate listed statistical parameters for fixed size arrays.

	* Slope
	* Offset

**Stream Linear Regression**

Library calculate listed statistical parameters for data stream. User set the regression presicion for calculating last n data regression.

	* Presicion
	* Slope
	* Offset

**Machine Learning Algorithm**

This library will calculate slope of data according last n value. With these slope data system can learn sensor anomaly and make desicion.

<img src="/Documents/Pressure_Regression.gif" width="800">

---

[![Support me](https://img.shields.io/badge/Support-PATREON-GREEN.svg)](https://www.patreon.com/bePatron?u=62967889) ![Twitter Follow](https://img.shields.io/twitter/follow/gunceakkoyun?style=social) ![YouTube Channel Views](https://img.shields.io/youtube/channel/views/UCIguQGdaBT1GnnVMz5qAZ2Q?style=social) ![Repos Badge](https://badges.pufler.dev/repos/akkoyun) [![E-Mail](https://img.shields.io/badge/E_Mail-Mehmet_Gunce_Akkoyun-blue.svg)](mailto:akkoyun@me.com) ![GitHub](https://img.shields.io/github/license/akkoyun/Statistical) 