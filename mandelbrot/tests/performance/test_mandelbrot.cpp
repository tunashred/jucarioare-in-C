#include "gtest/gtest.h"
#include <mandelbrot.h>
#include <color_mapping.h>

// TODO: Reuse same image for overwriting + change its save location + sanitizer integration
/* Later TODO:
 * Maybe organize the tests better with TEST_F, INSTANTIATE_TEST_SUITE_P
 * Maybe create vectors with image configs
*/

// Global configurations
int worker_thread_count = 4;

class MandelbrotTest : public ::testing::TestWithParam<float> {
protected:
    bool is_portrait;
    
    int (*color_map_red)(int, int) = sin_x_la_4;
    int (*color_map_green)(int, int) = unu_minus_unu_pe_x;
    int (*color_map_blue)(int, int) = x_patrat_0_1_to_0_2;

    void SetUp() override {
        is_portrait = false; // Default is landscape
    }

    void TearDown() override {}

    void generate_image(const std::string& name, float scale, float x_center, float y_center, 
                        float zoom, int num_iters, int brightness, int rotate_degrees) {
        if (is_portrait) {
            mandelbrot_around_center(name.c_str(), 1080 * scale, 1080 * 1.2 * scale, x_center, y_center, 
                                     zoom, num_iters, rotate_degrees, brightness, color_map_red, 
                                     color_map_green, color_map_blue, mandelbrot_quadratic, worker_thread_count);
        } else {
            mandelbrot_around_center(name.c_str(), 1080 * scale, 1920 * scale, x_center, y_center, 
                                     zoom, num_iters, rotate_degrees, brightness, color_map_red, 
                                     color_map_green, color_map_blue, mandelbrot_quadratic, worker_thread_count);
        }
    }
};

// Mandatory Mandelbrot Tests
TEST_P(MandelbrotTest, mandelbrot_mandatory_tests) {
    float scale = GetParam();
    generate_image("test_image.ppm", scale, -0.43, -0.1, 1, 1500, 0, 0);
}

// Extra Mandelbrot Tests
TEST_P(MandelbrotTest, mandelbrot_extra_tests) {
    float scale = GetParam();
    generate_image("test_image.ppm", scale, -0.43, -0.1, 1, 1500, 0, 0);
}

// Galaxy Mandatory Tests
TEST_P(MandelbrotTest, galaxy_mandatory_tests) {
    is_portrait = true;
    float scale = GetParam();
    generate_image("test_image.ppm", scale, -0.700025 + 0.000000007, -0.26849991525, 
                    0.0000000035, 1500, 0, 0);
}

// Galaxy Extra Tests
TEST_P(MandelbrotTest, galaxy_extra_tests) {
    is_portrait = true;
    float scale = GetParam();
    generate_image("test_image.ppm", scale, -0.700025 + 0.000000007, -0.26849991525, 
                    0.0000000035, 1500, 0, 0);
}

// Stuff Mandatory Tests
TEST_P(MandelbrotTest, stuff_mandatory_tests) {
    is_portrait = true;
    float scale = GetParam();
    generate_image("test_image.ppm", scale, -0.7, -0.26, 0.01, 1500, 0, 1);
}

// Stuff Extra Tests
TEST_P(MandelbrotTest, stuff_extra_tests) {
    is_portrait = true;
    float scale = GetParam();
    generate_image("test_image.ppm", scale, -0.7, -0.26, 0.01, 1500, 0, 1);
}

// Seastar Mandatory Tests
TEST_P(MandelbrotTest, seastar_mandatory_tests) {
    is_portrait = true;
    float scale = GetParam();
    generate_image("test_image.ppm", scale, -0.72413, 0.28644, 0.0004, 1500, 0, 1);
}

// Seastar Extra Tests
TEST_P(MandelbrotTest, seastar_extra_tests) {
    is_portrait = true;
    float scale = GetParam();
    generate_image("test_image.ppm", scale, -0.72413, 0.28644, 0.0004, 1500, 0, 1);
}

// Shells Mandatory Tests
TEST_P(MandelbrotTest, shells_mandatory_tests) {
    is_portrait = true;
    float scale = GetParam();
    generate_image("test_image.ppm", scale, -0.75 + 0.00005, -0.02, 0.00025, 1500, 0, 1);
}

// Shells Extra Tests
TEST_P(MandelbrotTest, shells_extra_tests) {
    is_portrait = true;
    float scale = GetParam();
    generate_image("test_image.ppm", scale, -0.75 + 0.00005, -0.02, 0.00025, 1500, 0, 1);
}

INSTANTIATE_TEST_SUITE_P(
    MandelbrotMandatoryTests,
    MandelbrotTest,
    ::testing::Values(1, 2, 4)
);

INSTANTIATE_TEST_SUITE_P(
    MandelbrotExtraTests,
    MandelbrotTest,
    ::testing::Values(1.5, 2.5, 3, 3.5)
);
