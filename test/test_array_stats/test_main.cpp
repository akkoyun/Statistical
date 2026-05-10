#include <unity.h>
#include "Statistical.h"

// ── helpers ───────────────────────────────────────────────────────────────────
static const float EPS = 0.001f;

void setUp(void)    {}
void tearDown(void) {}

// ── Sum ───────────────────────────────────────────────────────────────────────
void test_sum(void) {
    float d[] = {2, 4, 6};
    Array_Stats<float> s(d, 3);
    TEST_ASSERT_FLOAT_WITHIN(EPS, 12.0f, s.Sum());
}

void test_sum_empty(void) {
    float d[] = {1};
    Array_Stats<float> s(d, 0);
    TEST_ASSERT_FLOAT_WITHIN(EPS, 0.0f, s.Sum());
}

// ── Min / Max ─────────────────────────────────────────────────────────────────
void test_min(void) {
    float d[] = {5, 1, 3};
    Array_Stats<float> s(d, 3);
    TEST_ASSERT_FLOAT_WITHIN(EPS, 1.0f, s.Min());
}

void test_max(void) {
    float d[] = {5, 1, 3};
    Array_Stats<float> s(d, 3);
    TEST_ASSERT_FLOAT_WITHIN(EPS, 5.0f, s.Max());
}

// ── Sq_Sum ────────────────────────────────────────────────────────────────────
void test_sq_sum(void) {
    float d[] = {2, 4, 6};
    Array_Stats<float> s(d, 3);
    // 4 + 16 + 36 = 56
    TEST_ASSERT_FLOAT_WITHIN(EPS, 56.0f, s.Sq_Sum());
}

// ── Arithmetic_Average ────────────────────────────────────────────────────────
void test_arithmetic_average(void) {
    float d[] = {2, 4, 6};
    Array_Stats<float> s(d, 3);
    TEST_ASSERT_FLOAT_WITHIN(EPS, 4.0f, s.Arithmetic_Average());
}

void test_arithmetic_average_integers(void) {
    int d[] = {1, 2, 3, 4, 5};
    Array_Stats<int> s(d, 5);
    TEST_ASSERT_FLOAT_WITHIN(EPS, 3.0f, s.Arithmetic_Average());
}

// ── Geometric_Average ─────────────────────────────────────────────────────────
void test_geometric_average(void) {
    // cbrt(1 * 4 * 16) = cbrt(64) = 4.0
    float d[] = {1, 4, 16};
    Array_Stats<float> s(d, 3);
    TEST_ASSERT_FLOAT_WITHIN(EPS, 4.0f, s.Geometric_Average());
}

void test_geometric_average_zero_guard(void) {
    float d[] = {2, 0, 4};
    Array_Stats<float> s(d, 3);
    TEST_ASSERT_FLOAT_WITHIN(EPS, 0.0f, s.Geometric_Average());
}

// ── RMS_Average ───────────────────────────────────────────────────────────────
void test_rms_average(void) {
    // sqrt((4+16+36)/3) = sqrt(56/3) ≈ 4.3205
    float d[] = {2, 4, 6};
    Array_Stats<float> s(d, 3);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 4.3205f, s.RMS_Average());
}

// ── Ext_RMS_Average ───────────────────────────────────────────────────────────
void test_ext_rms_average(void) {
    // {2,4,6}: remove min=2 and max=6, only 4 remains
    // sqrt((56 - 4 - 36) / 1) = sqrt(16) = 4.0
    float d[] = {2, 4, 6};
    Array_Stats<float> s(d, 3);
    TEST_ASSERT_FLOAT_WITHIN(EPS, 4.0f, s.Ext_RMS_Average());
}

void test_ext_rms_average_too_small(void) {
    float d[] = {1, 2};
    Array_Stats<float> s(d, 2);
    TEST_ASSERT_FLOAT_WITHIN(EPS, 0.0f, s.Ext_RMS_Average());
}

// ── Sigma_Average ─────────────────────────────────────────────────────────────
void test_sigma_average_rejects_outlier(void) {
    // 1000 is far outside 1-sigma window; survivors {10,20,30} avg = 20.0
    float d[] = {10, 20, 30, 1000};
    Array_Stats<float> s(d, 4);
    TEST_ASSERT_FLOAT_WITHIN(EPS, 20.0f, s.Sigma_Average(1));
}

void test_sigma_average_no_outliers(void) {
    // Tight cluster — all inside 3-sigma, mean = 3.0
    float d[] = {1, 2, 3, 4, 5};
    Array_Stats<float> s(d, 5);
    TEST_ASSERT_FLOAT_WITHIN(EPS, 3.0f, s.Sigma_Average(3));
}

void test_sigma_average_too_small(void) {
    float d[] = {5};
    Array_Stats<float> s(d, 1);
    TEST_ASSERT_FLOAT_WITHIN(EPS, 0.0f, s.Sigma_Average(2));
}

// ── Variance / Standard_Deviation ─────────────────────────────────────────────
void test_variance(void) {
    // {2,4,6}: mean=4, sum_sq_dev=8, var=8/2=4.0  (Bessel n-1)
    float d[] = {2, 4, 6};
    Array_Stats<float> s(d, 3);
    TEST_ASSERT_FLOAT_WITHIN(EPS, 4.0f, s.Variance());
}

void test_standard_deviation(void) {
    float d[] = {2, 4, 6};
    Array_Stats<float> s(d, 3);
    TEST_ASSERT_FLOAT_WITHIN(EPS, 2.0f, s.Standard_Deviation());
}

void test_standard_deviation_error(void) {
    // SDE = SD / sqrt(n) = 2.0 / sqrt(3) ≈ 1.1547
    float d[] = {2, 4, 6};
    Array_Stats<float> s(d, 3);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 1.1547f, s.Standard_Deviation_Error());
}

void test_coefficient_factor(void) {
    // CV = 100 * SD / mean = 100 * 2 / 4 = 50.0
    float d[] = {2, 4, 6};
    Array_Stats<float> s(d, 3);
    TEST_ASSERT_FLOAT_WITHIN(EPS, 50.0f, s.Coefficient_Factor());
}

// ── Quartile / IQR ────────────────────────────────────────────────────────────
void test_quartile_q1(void) {
    // {1,3,5,7}: pos=(4+1)*0.25=1.25, idx=1, frac=0.25
    // Q1 = 1 + 0.25*(3-1) = 1.5
    float d[] = {1, 3, 5, 7};
    Array_Stats<float> s(d, 4);
    TEST_ASSERT_FLOAT_WITHIN(EPS, 1.5f, s.Quartile(1));
}

void test_quartile_q2(void) {
    // {1,3,5,7}: pos=2.5, idx=2, frac=0.5 → 3 + 0.5*(5-3) = 4.0
    float d[] = {1, 3, 5, 7};
    Array_Stats<float> s(d, 4);
    TEST_ASSERT_FLOAT_WITHIN(EPS, 4.0f, s.Quartile(2));
}

void test_quartile_q3(void) {
    // {1,3,5,7}: pos=3.75, idx=3, frac=0.75 → 5 + 0.75*(7-5) = 6.5
    float d[] = {1, 3, 5, 7};
    Array_Stats<float> s(d, 4);
    TEST_ASSERT_FLOAT_WITHIN(EPS, 6.5f, s.Quartile(3));
}

void test_iqr(void) {
    float d[] = {1, 3, 5, 7};
    Array_Stats<float> s(d, 4);
    // Q3 - Q1 = 6.5 - 1.5 = 5.0
    TEST_ASSERT_FLOAT_WITHIN(EPS, 5.0f, s.IQR());
}

void test_quartile_sorts_input(void) {
    // unsorted input — Quartile() must sort first
    float d[] = {7, 5, 1, 3};
    Array_Stats<float> s(d, 4);
    TEST_ASSERT_FLOAT_WITHIN(EPS, 1.5f, s.Quartile(1));
}

void test_quartile_too_small(void) {
    float d[] = {1, 2, 3};
    Array_Stats<float> s(d, 3);
    TEST_ASSERT_FLOAT_WITHIN(EPS, 0.0f, s.Quartile(1));
}

// ── Bubble_Sort ───────────────────────────────────────────────────────────────
void test_bubble_sort(void) {
    float d[] = {5, 2, 8, 1};
    Array_Stats<float> s(d, 4);
    s.Bubble_Sort();
    TEST_ASSERT_FLOAT_WITHIN(EPS, 1.0f, d[0]);
    TEST_ASSERT_FLOAT_WITHIN(EPS, 2.0f, d[1]);
    TEST_ASSERT_FLOAT_WITHIN(EPS, 5.0f, d[2]);
    TEST_ASSERT_FLOAT_WITHIN(EPS, 8.0f, d[3]);
}

// ── FILO_Add_Data ─────────────────────────────────────────────────────────────
void test_filo_add_data(void) {
    float d[] = {0, 0, 0, 5};
    Array_Stats<float> s(d, 4);
    s.FILO_Add_Data(7.0f);
    TEST_ASSERT_FLOAT_WITHIN(EPS, 0.0f, d[0]);
    TEST_ASSERT_FLOAT_WITHIN(EPS, 0.0f, d[1]);
    TEST_ASSERT_FLOAT_WITHIN(EPS, 5.0f, d[2]);
    TEST_ASSERT_FLOAT_WITHIN(EPS, 7.0f, d[3]);
}

// ── Average dispatch ──────────────────────────────────────────────────────────
void test_average_dispatch_arithmetic(void) {
    float d[] = {2, 4, 6};
    Array_Stats<float> s(d, 3);
    TEST_ASSERT_FLOAT_WITHIN(EPS, 4.0f,
        s.Average(Array_Stats<float>::Arithmetic_Avg));
}

void test_average_dispatch_rms(void) {
    float d[] = {2, 4, 6};
    Array_Stats<float> s(d, 3);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 4.3205f,
        s.Average(Array_Stats<float>::RMS_Avg));
}

// ── Size ──────────────────────────────────────────────────────────────────────
void test_size(void) {
    float d[] = {1, 2, 3, 4, 5};
    Array_Stats<float> s(d, 5);
    TEST_ASSERT_EQUAL_INT(5, (int)s.Size());
}

// ── main ──────────────────────────────────────────────────────────────────────
int main(int argc, char **argv) {
    UNITY_BEGIN();

    RUN_TEST(test_sum);
    RUN_TEST(test_sum_empty);
    RUN_TEST(test_min);
    RUN_TEST(test_max);
    RUN_TEST(test_sq_sum);
    RUN_TEST(test_arithmetic_average);
    RUN_TEST(test_arithmetic_average_integers);
    RUN_TEST(test_geometric_average);
    RUN_TEST(test_geometric_average_zero_guard);
    RUN_TEST(test_rms_average);
    RUN_TEST(test_ext_rms_average);
    RUN_TEST(test_ext_rms_average_too_small);
    RUN_TEST(test_sigma_average_rejects_outlier);
    RUN_TEST(test_sigma_average_no_outliers);
    RUN_TEST(test_sigma_average_too_small);
    RUN_TEST(test_variance);
    RUN_TEST(test_standard_deviation);
    RUN_TEST(test_standard_deviation_error);
    RUN_TEST(test_coefficient_factor);
    RUN_TEST(test_quartile_q1);
    RUN_TEST(test_quartile_q2);
    RUN_TEST(test_quartile_q3);
    RUN_TEST(test_iqr);
    RUN_TEST(test_quartile_sorts_input);
    RUN_TEST(test_quartile_too_small);
    RUN_TEST(test_bubble_sort);
    RUN_TEST(test_filo_add_data);
    RUN_TEST(test_average_dispatch_arithmetic);
    RUN_TEST(test_average_dispatch_rms);
    RUN_TEST(test_size);

    return UNITY_END();
}
