#include <unity.h>
#include "Statistical.h"
#include <math.h>

static const float EPS = 0.1f;   // vector trig needs a bit more slack

void setUp(void)    {}
void tearDown(void) {}

// Helper: wrap angle difference into [-180, 180] to compare compass angles
static float angle_diff(float a, float b) {
    float d = a - b;
    while (d >  180.0f) d -= 360.0f;
    while (d < -180.0f) d += 360.0f;
    return d < 0 ? -d : d;
}

// ── single North vector ───────────────────────────────────────────────────────
void test_single_north(void) {
    float mag[] = {10.0f};
    float ang[] = {0.0f};    // 0° = North
    Vector_Stats<float, float> v(mag, ang, 1);
    v.Vector_Sum();
    TEST_ASSERT_FLOAT_WITHIN(EPS, 10.0f, v.Result.Magnitude);
    TEST_ASSERT_TRUE(angle_diff(v.Result.Angle, 0.0f) < EPS);
}

// ── single East vector ────────────────────────────────────────────────────────
void test_single_east(void) {
    float mag[] = {10.0f};
    float ang[] = {90.0f};   // 90° = East
    Vector_Stats<float, float> v(mag, ang, 1);
    v.Vector_Sum();
    TEST_ASSERT_FLOAT_WITHIN(EPS, 10.0f, v.Result.Magnitude);
    TEST_ASSERT_TRUE(angle_diff(v.Result.Angle, 90.0f) < EPS);
}

// ── single South vector ───────────────────────────────────────────────────────
void test_single_south(void) {
    float mag[] = {10.0f};
    float ang[] = {180.0f};  // 180° = South
    Vector_Stats<float, float> v(mag, ang, 1);
    v.Vector_Sum();
    TEST_ASSERT_FLOAT_WITHIN(EPS, 10.0f, v.Result.Magnitude);
    TEST_ASSERT_TRUE(angle_diff(v.Result.Angle, 180.0f) < EPS);
}

// ── single West vector ────────────────────────────────────────────────────────
void test_single_west(void) {
    float mag[] = {10.0f};
    float ang[] = {270.0f};  // 270° = West
    Vector_Stats<float, float> v(mag, ang, 1);
    v.Vector_Sum();
    TEST_ASSERT_FLOAT_WITHIN(EPS, 10.0f, v.Result.Magnitude);
    TEST_ASSERT_TRUE(angle_diff(v.Result.Angle, 270.0f) < EPS);
}

// ── two equal North vectors → double magnitude, same direction ────────────────
void test_two_north_vectors(void) {
    float mag[] = {10.0f, 10.0f};
    float ang[] = {0.0f,  0.0f};
    Vector_Stats<float, float> v(mag, ang, 2);
    v.Vector_Sum();
    TEST_ASSERT_FLOAT_WITHIN(EPS, 20.0f, v.Result.Magnitude);
    TEST_ASSERT_TRUE(angle_diff(v.Result.Angle, 0.0f) < EPS);
}

// ── opposite vectors cancel → near-zero magnitude ────────────────────────────
void test_opposite_cancel(void) {
    float mag[] = {10.0f, 10.0f};
    float ang[] = {0.0f, 180.0f};  // N + S
    Vector_Stats<float, float> v(mag, ang, 2);
    v.Vector_Sum();
    TEST_ASSERT_FLOAT_WITHIN(EPS, 0.0f, v.Result.Magnitude);
}

// ── NE diagonal (45°): equal N and E components ───────────────────────────────
void test_ne_diagonal(void) {
    // 10 N + 10 E → resultant = 10*sqrt(2) ≈ 14.142 at 45°
    float mag[] = {10.0f, 10.0f};
    float ang[] = {0.0f,  90.0f};
    Vector_Stats<float, float> v(mag, ang, 2);
    v.Vector_Sum();
    TEST_ASSERT_FLOAT_WITHIN(EPS, 14.142f, v.Result.Magnitude);
    TEST_ASSERT_TRUE(angle_diff(v.Result.Angle, 45.0f) < EPS);
}

// ── three balanced vectors at 120° apart → near-zero resultant ───────────────
void test_three_balanced(void) {
    float mag[] = {10.0f,  10.0f,  10.0f};
    float ang[] = {  0.0f, 120.0f, 240.0f};
    Vector_Stats<float, float> v(mag, ang, 3);
    v.Vector_Sum();
    TEST_ASSERT_FLOAT_WITHIN(EPS, 0.0f, v.Result.Magnitude);
}

// ── main ──────────────────────────────────────────────────────────────────────
int main(int argc, char **argv) {
    UNITY_BEGIN();

    RUN_TEST(test_single_north);
    RUN_TEST(test_single_east);
    RUN_TEST(test_single_south);
    RUN_TEST(test_single_west);
    RUN_TEST(test_two_north_vectors);
    RUN_TEST(test_opposite_cancel);
    RUN_TEST(test_ne_diagonal);
    RUN_TEST(test_three_balanced);

    return UNITY_END();
}
