#ifndef __FUNCS_HPP__
#define __FUNCS_HPP__

# include <vector>
# include <string>

using namespace std;

const string INVERTED_IMAGE_FILENAME = "peixe_noise10_inverted.ascii.pgm"; 
const string REDUCED_NOISE_IMAGE_FILENAME = "peixe_reduced_noise.ascii.pgm";
const string BOX_FILTERED_IMAGE_FILENAME = "peixe_box_blur.ascii.pgm";
const string SQUARE_MEDIAN_FILTERED_IMAGE_FILENAME = "peixe_square_median.ascii.pgm";
const string DIAMOND_MEDIAN_FILTERED_IMAGE_FILENAME = "peixe_diamond_median.ascii.pgm";

vector<vector<int>> read_image(string filename); // Read image
void create_image_file(vector<vector<int>> image, string filename); // Create image file
void print_int_histogram(vector<int> histogram); // Print int histogram
void print_double_histogram(vector<double> histogram); // Print double histogram
vector<vector<int>> sum_images(vector<vector<int>> image1, vector<vector<int>> image2); // Sum two images

vector<int> histogram_absolute(vector<vector<int>> image); // Create absolute histogram
vector<double> histogram_relative(vector<vector<int>> image); // Create relative histogram

double calculate_average_color(vector<vector<int>> image); // Calculate average color
double calculate_variance(vector<vector<int>> image); // Calculate variance
double calculate_standard_deviation(vector<vector<int>> image); // Calculate standard deviation
int calculate_median(vector<int> values); // Calculate median of a vector

int calculate_eight_average(vector<vector<int>> image, int i, int j); // Calculate eight average (8 pixels)
int calculate_filtered_average(vector<vector<int>> image, vector<vector<double>> filter, int i, int j); // Calculate filtered average (9 pixels)
int calculate_square_median(vector<vector<int>> image, int i, int j, int r); // Calculate square median (2r+1 pixels)
int calculate_diamond_median(vector<vector<int>> image, int i, int j, int r); // Calculate diamond median (2r+1 pixels)

vector<vector<int>> create_inverted_image(vector<vector<int>> image); // Create inverted image
vector<vector<int>> create_reduced_noise_image(vector<vector<int>> image); // Create reduced noise image
vector<vector<int>> create_box_filtering_image(vector<vector<int>> image); // Create box filtering image
vector<vector<int>> create_square_median_filtering_image(vector<vector<int>> image, int r); // Create square median filtering image (2r+1 pixels)
vector<vector<int>> create_diamond_median_filtering_image(vector<vector<int>> image, int r); // Create diamond median filtering image (2r+1 pixels)

#endif // __FUNCS_HPP__