#include <unity.h>
#include "Statistical.h"

static const float EPS = 0.001f;

void setUp(void)    {}
void tearDown(void) {}

// ── single sample ─────────────────────────────────────────────────────────────
void test_single_sample(void) {
    Stream_Stats<float> s;
    s.Add(42.0f);
    TEST_ASSERT_EQUAL_INT(1, (int)s.Get_Data_Count());
    TEST_ASSERT_FLOAT_WITHIN(EPS, 42.0f, s.Get_Average());
    TEST_ASSERT_FLOAT_WITHIN(EPS, 42.0f, s.Get_Min());
    TEST_ASSERT_FLOAT_WITHIN(EPS, 42.0f, s.Get_Max());
    TEST_ASSERT_FLOAT_WITHIN(EPS, 42.0f, s.Get_Last());
}

// ── two samples ───────────────────────────────────────────────────────────────
void test_two_samples_average(void) {
    // Welford: first=100 → avg=100; second=0 → avg += (0-100)/2 = 50
    Stream_Stats<float> s;
    s.Add(100.0f);
    s.Add(0.0f);
    TEST_ASSERT_FLOAT_WITHIN(EPS, 50.0f, s.Get_Average());
    TEST_ASSERT_FLOAT_WITHIN(EPS,  0.0f, s.Get_Min());
    TEST_ASSERT_FLOAT_WITHIN(EPS,100.0f, s.Get_Max());
}

// ── three samples ─────────────────────────────────────────────────────────────
void test_three_samples_average(void) {
    // {3, 6, 9}: online mean should converge to 6.0
    Stream_Stats<float> s;
    s.Add(3.0f);
    s.Add(6.0f);
    s.Add(9.0f);
    TEST_ASSERT_FLOAT_WITHIN(EPS, 6.0f, s.Get_Average());
    TEST_ASSERT_EQUAL_INT(3, (int)s.Get_Data_Count());
}

// ── min / max tracking ────────────────────────────────────────────────────────
void test_min_max_tracking(void) {
    Stream_Stats<float> s;
    s.Add(5.0f);
    s.Add(2.0f);
    s.Add(8.0f);
    s.Add(1.0f);
    TEST_ASSERT_FLOAT_WITHIN(EPS, 1.0f, s.Get_Min());
    TEST_ASSERT_FLOAT_WITHIN(EPS, 8.0f, s.Get_Max());
}

// ── Get_Last ──────────────────────────────────────────────────────────────────
void test_get_last(void) {
    Stream_Stats<float> s;
    s.Add(10.0f);
    s.Add(20.0f);
    s.Add(30.0f);
    TEST_ASSERT_FLOAT_WITHIN(EPS, 30.0f, s.Get_Last());
}

// ── Clear ─────────────────────────────────────────────────────────────────────
void test_clear(void) {
    Stream_Stats<float> s;
    s.Add(5.0f);
    s.Add(10.0f);
    s.Clear();
    TEST_ASSERT_EQUAL_INT(0, (int)s.Get_Data_Count());
    TEST_ASSERT_FLOAT_WITHIN(EPS, 0.0f, s.Get_Average());
    TEST_ASSERT_FLOAT_WITHIN(EPS, 0.0f, s.Get_Min());
    TEST_ASSERT_FLOAT_WITHIN(EPS, 0.0f, s.Get_Max());
}

// ── integer template ──────────────────────────────────────────────────────────
void test_integer_type_precision(void) {
    // Internal float accumulator must avoid integer truncation
    Stream_Stats<int> s;
    s.Add(1);
    s.Add(2);
    // avg = 1 + (2-1)/2 = 1.5 — must NOT truncate to 1
    TEST_ASSERT_FLOAT_WITHIN(EPS, 1.5f, s.Get_Average());
}

// ── long run ──────────────────────────────────────────────────────────────────
void test_long_run_average(void) {
    // Sum 1..10 = 55, mean = 5.5
    Stream_Stats<float> s;
    for (int i = 1; i <= 10; i++) s.Add((float)i);
    TEST_ASSERT_FLOAT_WITHIN(EPS, 5.5f, s.Get_Average());
    TEST_ASSERT_EQUAL_INT(10, (int)s.Get_Data_Count());
}

// ── main ──────────────────────────────────────────────────────────────────────
int main(int argc, char **argv) {
    UNITY_BEGIN();

    RUN_TEST(test_single_sample);
    RUN_TEST(test_two_samples_average);
    RUN_TEST(test_three_samples_average);
    RUN_TEST(test_min_max_tracking);
    RUN_TEST(test_get_last);
    RUN_TEST(test_clear);
    RUN_TEST(test_integer_type_precision);
    RUN_TEST(test_long_run_average);

    return UNITY_END();
}
