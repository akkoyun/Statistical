#include <unity.h>
#include "Statistical.h"

static const float EPS = 0.001f;

void setUp(void)    {}
void tearDown(void) {}

// ── perfect line ──────────────────────────────────────────────────────────────
// y = 2x + 1  →  slope=2, offset=1, R²=1
static float lx[] = {0, 1, 2, 3, 4};
static float ly[] = {1, 3, 5, 7, 9};

void test_slope_perfect_line(void) {
    Linear_Regression<float, float> r(lx, ly, 5);
    TEST_ASSERT_FLOAT_WITHIN(EPS, 2.0f, r.Slope());
}

void test_offset_perfect_line(void) {
    Linear_Regression<float, float> r(lx, ly, 5);
    TEST_ASSERT_FLOAT_WITHIN(EPS, 1.0f, r.Offset());
}

void test_r2_perfect_line(void) {
    Linear_Regression<float, float> r(lx, ly, 5);
    TEST_ASSERT_FLOAT_WITHIN(EPS, 1.0f, r.R2());
}

// ── Compute_All matches individual calls ──────────────────────────────────────
void test_compute_all_matches(void) {
    Linear_Regression<float, float> r(lx, ly, 5);
    auto res = r.Compute_All();
    TEST_ASSERT_FLOAT_WITHIN(EPS, 2.0f, res.Slope);
    TEST_ASSERT_FLOAT_WITHIN(EPS, 1.0f, res.Offset);
    TEST_ASSERT_FLOAT_WITHIN(EPS, 1.0f, res.R2);
}

// ── flat line (no correlation) ────────────────────────────────────────────────
static float fx[] = {0, 1, 2};
static float fy[] = {5, 5, 5};

void test_slope_flat_line(void) {
    Linear_Regression<float, float> r(fx, fy, 3);
    TEST_ASSERT_FLOAT_WITHIN(EPS, 0.0f, r.Slope());
}

void test_offset_flat_line(void) {
    Linear_Regression<float, float> r(fx, fy, 3);
    TEST_ASSERT_FLOAT_WITHIN(EPS, 5.0f, r.Offset());
}

void test_r2_flat_line(void) {
    // No variance in y → R² = 0
    Linear_Regression<float, float> r(fx, fy, 3);
    TEST_ASSERT_FLOAT_WITHIN(EPS, 0.0f, r.R2());
}

// ── negative slope ────────────────────────────────────────────────────────────
// y = -3x + 10
static float nx[] = {0, 1, 2, 3};
static float ny[] = {10, 7, 4, 1};

void test_negative_slope(void) {
    Linear_Regression<float, float> r(nx, ny, 4);
    TEST_ASSERT_FLOAT_WITHIN(EPS, -3.0f, r.Slope());
}

void test_negative_slope_offset(void) {
    Linear_Regression<float, float> r(nx, ny, 4);
    TEST_ASSERT_FLOAT_WITHIN(EPS, 10.0f, r.Offset());
}

void test_negative_slope_r2(void) {
    Linear_Regression<float, float> r(nx, ny, 4);
    TEST_ASSERT_FLOAT_WITHIN(EPS, 1.0f, r.R2());
}

// ── too few samples ───────────────────────────────────────────────────────────
void test_too_few_samples(void) {
    float x[] = {1};
    float y[] = {2};
    Linear_Regression<float, float> r(x, y, 1);
    TEST_ASSERT_FLOAT_WITHIN(EPS, 0.0f, r.Slope());
    TEST_ASSERT_FLOAT_WITHIN(EPS, 0.0f, r.Offset());
    TEST_ASSERT_FLOAT_WITHIN(EPS, 0.0f, r.R2());
}

// ── integer types ─────────────────────────────────────────────────────────────
void test_integer_types(void) {
    int ix[] = {0, 1, 2, 3, 4};
    int iy[] = {0, 2, 4, 6, 8};  // y = 2x
    Linear_Regression<int, int> r(ix, iy, 5);
    TEST_ASSERT_FLOAT_WITHIN(EPS, 2.0f, r.Slope());
    TEST_ASSERT_FLOAT_WITHIN(EPS, 0.0f, r.Offset());
}

// ── main ──────────────────────────────────────────────────────────────────────
int main(int argc, char **argv) {
    UNITY_BEGIN();

    RUN_TEST(test_slope_perfect_line);
    RUN_TEST(test_offset_perfect_line);
    RUN_TEST(test_r2_perfect_line);
    RUN_TEST(test_compute_all_matches);
    RUN_TEST(test_slope_flat_line);
    RUN_TEST(test_offset_flat_line);
    RUN_TEST(test_r2_flat_line);
    RUN_TEST(test_negative_slope);
    RUN_TEST(test_negative_slope_offset);
    RUN_TEST(test_negative_slope_r2);
    RUN_TEST(test_too_few_samples);
    RUN_TEST(test_integer_types);

    return UNITY_END();
}
