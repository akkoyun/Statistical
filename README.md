# Statistical Library <sup>v3.0.1</sup>

![GitHub release (latest by date)](https://img.shields.io/github/v/release/akkoyun/Statistical) ![arduino-library-badge](https://www.ardu-badge.com/badge/Statistical.svg?) ![Visits Badge](https://badges.pufler.dev/visits/akkoyun/Statistical) ![GitHub stars](https://img.shields.io/github/stars/akkoyun/Statistical?style=flat&logo=github) ![Updated Badge](https://badges.pufler.dev/updated/akkoyun/Statistical) ![PlatformIO Registry](https://badges.registry.platformio.org/packages/akkoyun/library/Statistical.svg)
[![Check Arduino](https://github.com/akkoyun/Statistical/actions/workflows/check-arduino.yml/badge.svg)](https://github.com/akkoyun/Statistical/actions/workflows/check-arduino.yml) [![Compile Examples](https://github.com/akkoyun/Statistical/actions/workflows/compile-examples.yml/badge.svg)](https://github.com/akkoyun/Statistical/actions/workflows/compile-examples.yml) [![Spell Check](https://github.com/akkoyun/Statistical/actions/workflows/spell-check.yml/badge.svg)](https://github.com/akkoyun/Statistical/actions/workflows/spell-check.yml)

---

## Overview

Header-only, template-based statistics library for Arduino and embedded systems. Designed for **ultra-low RAM usage**: all calculations are performed on user-supplied arrays (no internal copies), intermediate values use `float` (4 bytes), and no dynamic allocation is required for core functionality.

Five independent classes cover the most common embedded statistics needs:

| Class | What it does | RAM cost |
|-------|-------------|----------|
| [`Array_Stats<T>`](#array_statst) | Full statistics on a user-supplied array | Pointer + count (≤ 6 bytes) |
| [`FILO_Stats<T,N>`](#filo_stats-t-n) | Sliding window — owns its buffer, zero heap | N × sizeof(T) + 6 bytes |
| [`Stream_Stats<T>`](#stream_statst) | Online Min/Max/Mean without storing data | float + 3 × sizeof(T) + 2 bytes |
| [`Linear_Regression<X,Y>`](#linear_regressionxy) | Least-squares y = b1·x + b0 | 2 pointers + count (≤ 10 bytes) |
| [`Vector_Stats<M,A>`](#vector_statsma) | Polar vector addition | 2 pointers + count + 2 floats (≤ 14 bytes) |

---

## Installation

**Arduino Library Manager** — search for `Statistical` and install.

**Manual** — download the ZIP, then *Sketch → Include Library → Add .ZIP Library*.

**PlatformIO** — add to `platformio.ini`:
```ini
lib_deps = akkoyun/Statistical
```

---

## Quick Start

```cpp
#include <Statistical.h>

float data[] = {10.5, 11.2, 9.8, 12.0, 10.9};
Array_Stats<float> stats(data, 5);

float mean   = stats.Arithmetic_Average(); // 10.88
float stddev = stats.Standard_Deviation(); // 0.825
float median = stats.Quartile(2);          // 10.9
```

---

## API Reference

---

### Array_Stats\<T\>

Wraps a user-supplied array and exposes statistical functions. The array is never copied — all operations work on the original data in-place.

```cpp
// T can be any numeric type: float, double, int, uint8_t, etc.
Array_Stats<float> stats(data, count);
```

#### Enumerations

```cpp
// Pass to Average() to select calculation method
enum Average_Type : uint8_t {
    Arithmetic_Avg = 1,   // (x1 + x2 + … + xn) / n
    Geometric_Avg  = 2,   // nth root of (x1 * x2 * … * xn)
    RMS_Avg        = 3,   // sqrt(mean of squares)
    Ext_RMS_Avg    = 4,   // RMS excluding the single min and max element
    Sigma_Avg      = 5    // arithmetic mean after ±1σ outlier rejection
};

// Pass to Sigma_Average() to set the rejection window
enum Sigma_Type : uint8_t {
    Sigma_1 = 1,   // reject values outside ±1 standard deviation (~68%)
    Sigma_2 = 2,   // reject values outside ±2 standard deviations (~95%)
    Sigma_3 = 3,   // reject values outside ±3 standard deviations (~99.7%)
    Sigma_4 = 4    // reject values outside ±4 standard deviations (~99.99%)
};
```

---

#### `float Average(uint8_t type)`

Dispatches to the selected average function.

| Parameter | Type | Description |
|-----------|------|-------------|
| `type` | `uint8_t` | One of the `Average_Type` enum values |

**Returns:** Computed average as `float`. Returns `0` on empty array or invalid type.

```cpp
float arith = stats.Average(stats.Arithmetic_Avg);
float geo   = stats.Average(stats.Geometric_Avg);
float rms   = stats.Average(stats.RMS_Avg);
float ext   = stats.Average(stats.Ext_RMS_Avg);
float sigma = stats.Average(stats.Sigma_Avg);     // uses ±1σ window
```

---

#### `size_t Size()`

Returns the number of elements in the array.

**Returns:** Element count as `size_t`.

```cpp
size_t n = stats.Size(); // 5
```

---

#### `float Sum()`

Sums all array elements.

**Formula:** `Σ xᵢ`

**Returns:** Sum as `float`. Returns `0` if array is empty or result is NaN/Inf.

```cpp
float total = stats.Sum(); // 54.4 for {10.5, 11.2, 9.8, 12.0, 10.9}
```

---

#### `float Min()`

Finds the smallest value in the array.

**Returns:** Minimum value as `float`. Returns `0` if array is empty.

```cpp
float minimum = stats.Min(); // 9.8
```

---

#### `float Max()`

Finds the largest value in the array.

**Returns:** Maximum value as `float`. Returns `0` if array is empty.

```cpp
float maximum = stats.Max(); // 12.0
```

---

#### `float Sq_Sum()`

Sums the squares of all elements.

**Formula:** `Σ xᵢ²`

**Returns:** Sum of squares as `float`. Returns `0` if array is empty.

```cpp
float sq_total = stats.Sq_Sum(); // 10.5² + 11.2² + …
```

---

#### `float Arithmetic_Average()`

Computes the arithmetic (simple) mean.

**Formula:** `μ = Σxᵢ / n`

**Returns:** Mean as `float`. Returns `0` if array is empty.

```cpp
float mean = stats.Arithmetic_Average(); // 10.88
```

---

#### `float Geometric_Average()`

Computes the geometric mean using a numerically stable log-space accumulation.

**Formula:** `G = exp(Σ ln(xᵢ) / n)`

**Returns:** Geometric mean as `float`. Returns `0` if any element is ≤ 0 (geometric mean is undefined for non-positive values) or if array is empty.

> **Note:** Only use with strictly positive data (e.g. ratios, growth rates).

```cpp
float geo = stats.Geometric_Average();
```

---

#### `float Sigma_Average(uint8_t sigma)`

Removes statistical outliers and returns the mean of the remaining values.

**Algorithm:**
1. Compute arithmetic mean `μ` and standard deviation `σ`
2. Discard any value outside the range `(μ − N·σ, μ + N·σ)`
3. Return the arithmetic mean of the surviving values

| Parameter | Type | Description |
|-----------|------|-------------|
| `sigma` | `uint8_t` | Rejection width: `Sigma_1` / `Sigma_2` / `Sigma_3` / `Sigma_4` |

**Returns:** Filtered mean as `float`. Returns `0` if all values are rejected.

```cpp
float filtered = stats.Sigma_Average(stats.Sigma_1); // tight rejection
float relaxed  = stats.Sigma_Average(stats.Sigma_3); // lenient rejection
```

---

#### `float RMS_Average()`

Root Mean Square average. Gives higher weight to larger values. Commonly used for AC signal amplitude.

**Formula:** `RMS = sqrt(Σxᵢ² / n)`

**Returns:** RMS value as `float`. Returns `0` if array is empty.

```cpp
float rms = stats.RMS_Average();
```

---

#### `float Ext_RMS_Average()`

Extended RMS: excludes the single minimum and maximum element before computing RMS. Useful for reducing the effect of extreme one-off readings.

**Formula:** `ExtRMS = sqrt((Σxᵢ² − min² − max²) / (n − 2))`

**Returns:** Extended RMS as `float`. Returns `0` if `n ≤ 2`.

```cpp
float ext_rms = stats.Ext_RMS_Average();
```

---

#### `float Quartile(uint8_t q)`

Computes the first (Q1), second (Q2/median), or third (Q3) quartile using linear interpolation.

| Parameter | Value | Meaning |
|-----------|-------|---------|
| `q` | `1` | Q1 — 25th percentile |
| `q` | `2` | Q2 — 50th percentile (median) |
| `q` | `3` | Q3 — 75th percentile |

**Returns:** Quartile value as `float`. Returns `0` if `n < 4` or invalid `q`.

> **Side effect:** Calls `Bubble_Sort()` internally — the original array is sorted in-place after this call.

```cpp
float q1     = stats.Quartile(1); // 25th percentile
float median = stats.Quartile(2); // 50th percentile
float q3     = stats.Quartile(3); // 75th percentile
```

---

#### `float IQR()`

Interquartile range — the spread of the middle 50% of the data.

**Formula:** `IQR = Q3 − Q1`

**Returns:** IQR as `float`. Returns `0` if `n < 4`.

> **Side effect:** Sorts the array in-place (calls `Quartile()` twice).

**Outlier detection (Tukey's fences):**
```cpp
float iqr   = stats.IQR();
float q1    = stats.Quartile(1);
float q3    = stats.Quartile(3);
float lower = q1 - 1.5f * iqr;
float upper = q3 + 1.5f * iqr;
// Values outside [lower, upper] are outliers
```

---

#### `float Standard_Deviation()`

Sample standard deviation (divides by `n − 1`, Bessel's correction).

**Formula:** `σ = sqrt(Σ(xᵢ − μ)² / (n − 1))`

**Returns:** Standard deviation as `float`. Returns `0` if `n < 2`.

```cpp
float sd = stats.Standard_Deviation();
```

---

#### `float Standard_Deviation_Error()`

Standard Error of the Mean (SEM) — estimates how far the sample mean is from the true population mean.

**Formula:** `SEM = σ / sqrt(n)`

**Returns:** SEM as `float`. Returns `0` if array is empty.

```cpp
float sem = stats.Standard_Deviation_Error();
```

---

#### `float Coefficient_Factor()`

Coefficient of Variation (CV) — standard deviation expressed as a percentage of the mean. Allows comparing variability across datasets with different units or scales.

**Formula:** `CV = 100 × σ / μ`

**Returns:** CV as `float` percentage. Returns `0` if mean is zero.

```cpp
float cv = stats.Coefficient_Factor(); // e.g. 7.58 means 7.58%
```

---

#### `float Variance()`

Sample variance (Bessel-corrected). Square of the standard deviation.

**Formula:** `Var = Σ(xᵢ − μ)² / (n − 1)`

**Returns:** Variance as `float`. Returns `0` if `n < 2`.

```cpp
float var = stats.Variance();
```

---

#### `void Bubble_Sort()`

Sorts the array in ascending order in-place using bubble sort. No extra memory required.

> **Side effect:** Permanently reorders the original array.

```cpp
stats.Bubble_Sort();
// data[] is now sorted smallest → largest
```

---

#### `void Array()`

Prints all array elements to `Serial` in `[value] [value] …` format.

```cpp
stats.Array(); // [10.50] [11.20] [9.80] [12.00] [10.90]
```

---

#### `bool Set_FILO_Size(size_t n)`

Resizes the internal data buffer using `realloc`. Use this to initialize a FILO sliding window of `n` elements, all zeroed.

| Parameter | Type | Description |
|-----------|------|-------------|
| `n` | `size_t` | Desired window size (1 – 50) |

**Returns:** `true` on success, `false` if `n` is out of range or allocation fails.

> **Warning:** The pointer passed to the constructor must be heap-allocated (`malloc`/`calloc`). Calling `Set_FILO_Size()` on a stack array is undefined behavior. **Prefer `FILO_Stats<T,N>` for a completely heap-free alternative.**

```cpp
float* buf = (float*)malloc(10 * sizeof(float));
Array_Stats<float> window(buf, 10);
window.Set_FILO_Size(8); // resize to 8 elements, zero-filled
```

---

#### `void FILO_Add_Data(T data)`

Pushes a new value into the FILO sliding window. Shifts all elements one position left (oldest is dropped) and writes `data` at the end.

| Parameter | Type | Description         |
|-----------|------|---------------------|
| `data`    | `T`  | New value to append |

```cpp
float buf[6] = {0};
Array_Stats<float> win(buf, 6);
win.FILO_Add_Data(101.5f); // [0, 0, 0, 0, 0, 101.5]
win.FILO_Add_Data(102.1f); // [0, 0, 0, 0, 101.5, 102.1]
float avg = win.Arithmetic_Average();
```

---

### FILO_Stats\<T, N\>

Fixed-size sliding window that **owns its internal buffer** — no heap allocation, no pointer confusion, completely safe. Inherits every method from `Array_Stats<T>`.

The window size `N` is a compile-time constant (template parameter), so the buffer lives inside the object on the stack.

```cpp
FILO_Stats<float, 8> window;   // 8-element window, zero-initialised
window.Add(23.4f);             // push new value
window.Add(25.1f);
float avg = window.Arithmetic_Average();
float sd  = window.Standard_Deviation();
window.Array();                // print current window contents
```

#### `void Add(T data)` — FILO_Stats

Pushes `data` into the window (calls `FILO_Add_Data` internally).

| Parameter | Type | Description         |
|-----------|------|---------------------|
| `data`    | `T`  | New value to append |

> All `Array_Stats` methods (`Arithmetic_Average`, `Standard_Deviation`, `Min`, `Max`, `Quartile`, etc.) are available directly on a `FILO_Stats` object. `FILO_Stats` is non-copyable — the compiler prevents accidental pointer aliasing.

---

### Stream_Stats\<T\>

Computes running statistics for a continuous data stream **without storing any values**. Memory is constant regardless of how many samples are added. Uses Welford's online algorithm for numerically stable mean computation.

```cpp
Stream_Stats<float> sensor;
sensor.Add(23.4f);
sensor.Add(24.1f);
float mean = sensor.Get_Average(); // 23.75
```

---

#### `void Add(T data)`

Feeds one new sample into the stream. Updates Min, Max, and the running mean.

| Parameter | Type | Description |
|-----------|------|-------------|
| `data` | `T` | New measurement to include |

```cpp
sensor.Add(25.3f);
```

> The internal mean accumulator is always `float` regardless of `T`, so precision is preserved even when `T` is an integer type (e.g. `Stream_Stats<uint16_t>` for ADC readings).

---

#### `void Clear()`

Resets all statistics to zero and sets the sample count back to 0. Use at the start of each measurement window.

```cpp
sensor.Clear();
```

---

#### `uint16_t Get_Data_Count()`

Returns the number of samples added since the last `Clear()`.

**Returns:** Sample count as `uint16_t` (max 65535).

```cpp
uint16_t n = sensor.Get_Data_Count();
```

---

#### `float Get_Average()`

Returns the running arithmetic mean of all samples added so far.

**Returns:** Current mean as `float`.

```cpp
float mean = sensor.Get_Average();
```

---

#### `float Get_Min()`

Returns the smallest value seen since the last `Clear()`.

**Returns:** Running minimum as `float`.

```cpp
float minimum = sensor.Get_Min();
```

---

#### `float Get_Max()`

Returns the largest value seen since the last `Clear()`.

**Returns:** Running maximum as `float`.

```cpp
float maximum = sensor.Get_Max();
```

---

#### `float Get_Last()`

Returns the most recently added sample.

**Returns:** Last value as `float`.

```cpp
float last = sensor.Get_Last();
```

---

### Linear_Regression\<X, Y\>

Fits a straight line `y = b1·x + b0` to two parallel arrays using ordinary least squares. Useful for trend detection, calibration curves, and predictive extrapolation.

```cpp
float time_s[]  = {0, 1, 2, 3, 4};
float temp_C[]  = {20.1, 20.5, 20.9, 21.3, 21.8};
Linear_Regression<float, float> reg(time_s, temp_C, 5);
```

---

#### `float Slope()`

Computes the slope `b1` — the rate of change of `y` per unit `x`.

**Formula:** `b1 = (n·Σxy − Σx·Σy) / (n·Σx² − (Σx)²)`

**Returns:** Slope as `float`. Returns `0` if `n < 2` or if the denominator is zero (all x values identical).

```cpp
float slope = reg.Slope(); // positive → y increases with x
```

---

#### `float Offset()`

Computes the y-intercept `b0` — the predicted value of `y` when `x = 0`.

**Formula:** `b0 = (Σx²·Σy − Σx·Σxy) / (n·Σx² − (Σx)²)`

**Returns:** Offset as `float`. Returns `0` if `n < 2` or denominator is zero.

```cpp
float offset = reg.Offset();
float y_pred = reg.Slope() * x + reg.Offset(); // Slope+Offset = 2 separate passes
```

> **Performance tip:** If you need Slope, Offset, and R² together, use `Compute_All()` — it computes all three in 2 passes instead of 4.

---

#### `float R2()`

Coefficient of determination — measures how well the linear model fits the data.

| R² value | Interpretation |
|----------|---------------|
| 1.0 | Perfect linear fit |
| > 0.95 | Strong linear relationship |
| 0.5 – 0.95 | Moderate relationship |
| < 0.5 | Weak or no linear relationship |

**Formula:** `R² = (Σ(dx·dy))² / (Σdx² · Σdy²)` where `dx = x − x̄`, `dy = y − ȳ`

**Returns:** R² as `float` in [0, 1]. Returns `0` if `n < 2` or variance is zero.

> Computed without VLA — stack usage is O(1) regardless of dataset size.

```cpp
float r2 = reg.R2();
if (r2 > 0.99f) Serial.println("Excellent fit");
```

---

#### `Regression_Result Compute_All()`

Computes Slope, Offset, and R² in **2 array passes** instead of 4. Use this whenever you need more than one regression value.

```cpp
struct Regression_Result {
    float Slope;
    float Offset;
    float R2;
};
```

**Returns:** A `Regression_Result` struct with all three values. All fields are `0` if `n < 2`.

```cpp
// 2 passes — optimal for getting all three values
Linear_Regression<float,float>::Regression_Result r = reg.Compute_All();
Serial.println(r.Slope);
Serial.println(r.Offset);
Serial.println(r.R2);

// Predict
float y_pred = r.Slope * x + r.Offset;

// vs. calling separately (4 passes — avoid when all three are needed):
// float s = reg.Slope();   // pass 1
// float o = reg.Offset();  // pass 2
// float r2 = reg.R2();     // passes 3-4
```

---

### Vector_Stats\<M, A\>

Adds multiple polar vectors (magnitude + compass bearing) and returns the resultant vector. Useful for averaging wind speed/direction, forces, or any quantity with both magnitude and direction.

**Compass convention:** 0° = North, 90° = East, angles increase clockwise.

```cpp
float speed[]     = {3.5, 5.2, 4.0};   // m/s
float direction[] = {45.0, 60.0, 30.0}; // compass degrees
Vector_Stats<float, float> wind(speed, direction, 3);
wind.Vector_Sum();
Serial.println(wind.Result.Magnitude); // resultant speed
Serial.println(wind.Result.Angle);     // resultant direction
```

---

#### `void Vector_Sum()`

Converts each vector to Cartesian components, sums them, then converts the resultant back to polar form. Result is stored in `Result.Magnitude` and `Result.Angle`.

**Algorithm:**
1. `Sx = Σ(magnitudeᵢ · cos(bearingᵢ))`, `Sy = Σ(magnitudeᵢ · sin(bearingᵢ))`
2. `Magnitude = sqrt(Sx² + Sy²)`
3. `Angle = (90° − atan2(Sy, Sx) + 360°) mod 360°`

> Uses `atan2()` for correct quadrant handling across all input combinations.

```cpp
wind.Vector_Sum();
```

---

#### `Result.Magnitude`

Resultant vector magnitude. Set by `Vector_Sum()`.

```cpp
float mag = wind.Result.Magnitude;
```

---

#### `Result.Angle`

Resultant compass bearing in degrees [0°, 360°). Set by `Vector_Sum()`.

```cpp
float bearing = wind.Result.Angle;
```

---

## Examples

| Example | Class | What it shows |
|---------|-------|---------------|
| [`Array`](examples/Array/Array.ino) | `Array_Stats` | Every statistical function on a float array |
| [`FILO_Array`](examples/FILO_Array/FILO_Array.ino) | `FILO_Stats` | Heap-free sliding window with per-step stats |
| [`Stream`](examples/Stream/Stream.ino) | `Stream_Stats` | Online Min/Max/Mean, two independent streams |
| [`Linear_Regression`](examples/Linear_Regression/Linear_Regression.ino) | `Linear_Regression` | Battery discharge trend using `Compute_All()` |
| [`Vector`](examples/Vector/Vector.ino) | `Vector_Stats` | Wind vector addition with compass output |
| [`Sigma_Filter`](examples/Sigma_Filter/Sigma_Filter.ino) | `Array_Stats` | Outlier rejection on pressure sensor data |
| [`Quartile_IQR`](examples/Quartile_IQR/Quartile_IQR.ino) | `Array_Stats` | Quartile analysis and Tukey outlier detection |

---

## Memory Guide

| Operation | Stack impact | Notes |
|-----------|--------------|-------|
| `Sum`, `Min`, `Max`, `Sq_Sum` | O(1) — a few `float` locals | Single pass |
| `Arithmetic_Average` | O(1) | Calls `Sum()` |
| `Geometric_Average` | O(1) | Numerically stable log-space accumulation |
| `Variance` | O(1) — two passes, no arrays | Bessel-corrected |
| `Standard_Deviation` | O(1) | Calls `sqrt(Variance())` — no code duplication |
| `Sigma_Average` | O(1) — 2 passes | Pass 1: Welford online mean + variance; Pass 2: filter and mean |
| `RMS_Average`, `Ext_RMS_Average` | O(1) | Single pass via `Sq_Sum` |
| `Quartile`, `IQR` | O(1) stack | Sorts original array in-place; `IQR` sorts only once |
| `Linear_Regression::Slope/Offset` | O(1) — 1 pass each via `_Sums()` helper | |
| `Linear_Regression::R2` | O(1) — 2 passes | No VLA |
| `Linear_Regression::Compute_All` | O(1) — 2 passes | Optimal: all 3 values at once |
| `Stream_Stats::Add` | O(1) — constant regardless of sample count | `float` accumulator always |
| `FILO_Stats<T,N>::Add` | O(N) shift | Buffer is stack-allocated inside the object |
| `Array_Stats::FILO_Add_Data` | O(N) shift | User manages the buffer |
| `Array_Stats::Set_FILO_Size` | Calls `realloc` | Requires heap-allocated pointer; use `FILO_Stats` instead |

---

## Testing & Verification

### Unit Tests — host machine, no hardware needed

```sh
python3 -m platformio test -e native
```

66 tests cover all 5 classes; every test passes green.

| Suite | Tests | Class |
|-------|-------|-------|
| `test_array_stats` | 30 | `Array_Stats` |
| `test_linear_regression` | 12 | `Linear_Regression` |
| `test_filo_stats` | 8 | `FILO_Stats` |
| `test_stream_stats` | 8 | `Stream_Stats` |
| `test_vector_stats` | 8 | `Vector_Stats` |
| **Total** | **66** | all classes |

### AVR RAM Report — ATmega328P (2 KB total)

```sh
python3 -m platformio run -e uno
```

Benchmark exercises all 5 classes simultaneously as global instances:

| Section | Bytes | % of 2 KB |
|---------|-------|-----------|
| `.data` (initialized globals) | 122 B | 5.9% |
| `.bss` (zero-init globals) | 236 B | 11.5% |
| **Total RAM** | **358 B** | **17.5%** |
| Flash | 8 482 B | 26.3% |

1 690 bytes of RAM remain free after all classes are active.

---

## License

[![GitHub](https://img.shields.io/github/license/akkoyun/Statistical)](LICENSE)

Copyright © 2025 Gunce Akkoyun. Released under the MIT License.

---

[![Support me](https://img.shields.io/badge/Support-PATREON-GREEN.svg)](https://www.patreon.com/bePatron?u=62967889) ![Twitter Follow](https://img.shields.io/twitter/follow/gunceakkoyun?style=social) [![E-Mail](https://img.shields.io/badge/E_Mail-Mehmet_Gunce_Akkoyun-blue.svg)](mailto:akkoyun@me.com)
