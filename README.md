# Statistical Library <sup>V1.4</sup>

![GitHub release (latest by date)](https://img.shields.io/github/v/release/akkoyun/Statistical) ![arduino-library-badge](https://www.ardu-badge.com/badge/Statistical.svg?) ![Visits Badge](https://badges.pufler.dev/visits/akkoyun/Statistical) ![GitHub stars](https://img.shields.io/github/stars/akkoyun/Statistical?style=flat&logo=github) ![Updated Badge](https://badges.pufler.dev/updated/akkoyun/Statistical) ![PlatformIO Registry](https://badges.registry.platformio.org/packages/akkoyun/library/Statistical.svg) 
[![Check Arduino](https://github.com/akkoyun/Statistical/actions/workflows/check-arduino.yml/badge.svg)](https://github.com/akkoyun/Statistical/actions/workflows/check-arduino.yml) [![Compile Examples](https://github.com/akkoyun/Statistical/actions/workflows/compile-examples.yml/badge.svg)](https://github.com/akkoyun/Statistical/actions/workflows/compile-examples.yml) [![Spell Check](https://github.com/akkoyun/Statistical/actions/workflows/spell-check.yml/badge.svg)](https://github.com/akkoyun/Statistical/actions/workflows/spell-check.yml)

	Build - 01.04.13

---

**Abstract**

 Descriptive statistics for Arduino float arrays

We developed this library to help quickly accomplish median and mode filtering when collecting sensor data. Functions in this library operate on an array of float variables, of dimension "m", and return the corresponding statistic. This library was originally created for a data smoothing strategy for float variables. Using a median or mode filtering strategy (opposed to mean filtering) is better at removing spikes from aberrant readings. 

A bubble sort algorithm is also contained in this library which was necessary to calculate median and mode.


<details>
  <summary>Array Statistics</summary>

</br>
Library calculate listed statistical parameters for fixed size arrays.

	* Sum
	* Maximum
	* Minimum
	* Square Sum
	* Arithmetic Average
	* Geometric Average
	* RMS Average
	* 1 Sigma RMS Average
	* Bubble Sort
	* Median
	* Standard Deviation
	* Standard Deviation Error
	* Coefficient Factor
	* Array FILO

</details>

<details>
  <summary>Stream Statistics</summary>

</br>
Library calculate listed statistical parameters for data streams.

	* Data Count
	* Arithmetic Average
	* Minimum
	* Maximum

</details>

<details>
  <summary>Array Linear Regression</summary>

</br>
Library calculate listed statistical parameters for fixed size arrays.

	* Slope
	* Offset

</details>

<details>
  <summary>Stream Linear Regression</summary>

</br>
Library calculate listed statistical parameters for data stream. User set the regression precision for calculating last n data regression.

	* Precision
	* Slope
	* Offset

</details>

<details>
  <summary>Machine Learning Algorithm</summary>

</br>
This library will calculate slope of data according last n value. With these slope data system can learn sensor anomaly and make decision.

<img src="/Documents/Pressure_Regression.gif" width="800">

</details>

---

[![Support me](https://img.shields.io/badge/Support-PATREON-GREEN.svg)](https://www.patreon.com/bePatron?u=62967889) ![Twitter Follow](https://img.shields.io/twitter/follow/gunceakkoyun?style=social) ![YouTube Channel Views](https://img.shields.io/youtube/channel/views/UCIguQGdaBT1GnnVMz5qAZ2Q?style=social) ![Repos Badge](https://badges.pufler.dev/repos/akkoyun) [![E-Mail](https://img.shields.io/badge/E_Mail-Mehmet_Gunce_Akkoyun-blue.svg)](mailto:akkoyun@me.com) ![GitHub](https://img.shields.io/github/license/akkoyun/Statistical) 