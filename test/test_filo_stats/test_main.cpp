#include <unity.h>
#include "Statistical.h"

static const float EPS = 0.001f;

void setUp(void)    {}
void tearDown(void) {}

// ── initial state ─────────────────────────────────────────────────────────────
void test_initial_all_zero(void) {
    FILO_Stats<float, 4> w;
    // All slots initialised to 0
    TEST_ASSERT_FLOAT_WITHIN(EPS, 0.0f, w.Sum());
    TEST_ASSERT_FLOAT_WITHIN(EPS, 0.0f, w.Arithmetic_Average());
    TEST_ASSERT_EQUAL_INT(4, (int)w.Size());
}

// ── filling the window ────────────────────────────────────────────────────────
void test_fill_window(void) {
    FILO_Stats<float, 4> w;
    w.Add(1.0f);
    w.Add(2.0f);
    w.Add(3.0f);
    w.Add(4.0f);
    // Buffer: {1, 2, 3, 4}  →  avg = 2.5
    TEST_ASSERT_FLOAT_WITHIN(EPS, 2.5f, w.Arithmetic_Average());
}

// ── oldest element drops when window overflows ────────────────────────────────
void test_overflow_drops_oldest(void) {
    FILO_Stats<float, 4> w;
    w.Add(1.0f);
    w.Add(2.0f);
    w.Add(3.0f);
    w.Add(4.0f);
    w.Add(5.0f);   // oldest (1) is dropped → {2, 3, 4, 5}
    TEST_ASSERT_FLOAT_WITHIN(EPS, 3.5f, w.Arithmetic_Average());
}

void test_two_overflows(void) {
    FILO_Stats<float, 4> w;
    for (int i = 1; i <= 6; i++) w.Add((float)i);
    // {3, 4, 5, 6}  avg = 4.5
    TEST_ASSERT_FLOAT_WITHIN(EPS, 4.5f, w.Arithmetic_Average());
}

// ── min / max inside window ───────────────────────────────────────────────────
void test_window_min_max(void) {
    FILO_Stats<float, 4> w;
    w.Add(10.0f);
    w.Add(20.0f);
    w.Add(5.0f);
    w.Add(15.0f);
    TEST_ASSERT_FLOAT_WITHIN(EPS,  5.0f, w.Min());
    TEST_ASSERT_FLOAT_WITHIN(EPS, 20.0f, w.Max());
}

// ── integer template ──────────────────────────────────────────────────────────
void test_integer_window(void) {
    FILO_Stats<int, 3> w;
    w.Add(10);
    w.Add(20);
    w.Add(30);
    TEST_ASSERT_FLOAT_WITHIN(EPS, 20.0f, w.Arithmetic_Average());
}

// ── size is compile-time constant ─────────────────────────────────────────────
void test_size_constant(void) {
    FILO_Stats<float, 8> w;
    TEST_ASSERT_EQUAL_INT(8, (int)w.Size());
}

// ── partial fill (zeros still counted in average) ────────────────────────────
void test_partial_fill_average(void) {
    FILO_Stats<float, 4> w;
    w.Add(4.0f);   // buffer: {0, 0, 0, 4}  avg = 1.0
    TEST_ASSERT_FLOAT_WITHIN(EPS, 1.0f, w.Arithmetic_Average());
}

// ── main ──────────────────────────────────────────────────────────────────────
int main(int argc, char **argv) {
    UNITY_BEGIN();

    RUN_TEST(test_initial_all_zero);
    RUN_TEST(test_fill_window);
    RUN_TEST(test_overflow_drops_oldest);
    RUN_TEST(test_two_overflows);
    RUN_TEST(test_window_min_max);
    RUN_TEST(test_integer_window);
    RUN_TEST(test_size_constant);
    RUN_TEST(test_partial_fill_average);

    return UNITY_END();
}
