# include <fstream> // ifstream
# include <vector> // vector
# include <string> // string
# include <sstream> // istringstream
# include <iostream> // cout
# include <cmath> // pow
# include <algorithm> // sort
# include "funcs.hpp"

using namespace std;

int main(void) {
    vector<vector<int>> image = read_image("imagem.pgm"); // Read image
    print_int_histogram(histogram_absolute(image)); // Print absolute histogram
    print_double_histogram(histogram_relative(image)); // Print relative histogram
    cout << average_color(image) << "\n"; // Print average color
    cout << variance(image) << "\n"; // Print variance

    vector<vector<int>> inverted_image = create_inverted_image(image); // Create inverted image
    print_image(sum_images(inverted_image, image)); // Print inverted image summed with original

    vector<vector<int>> reduced_noise_image = create_reduced_noise_image(image); // Create reduced noise image
    cout << average_color(reduced_noise_image) << "\n"; // Print average color of reduced noise image
    cout << variance(reduced_noise_image) << "\n"; // Print variance of reduced noise image

    vector<vector<int>> boxed_reduce_noise_image = create_box_filtering_image(image); // Create box filtering image
    cout << average_color(boxed_reduce_noise_image) << "\n"; // Print average color of box filtering image
    cout << variance(boxed_reduce_noise_image) << "\n"; // Print variance of box filtering image

    vector<vector<int>> median_square_filtered_image = create_square_median_filtering_image(image, 2); // r = 2
    cout << average_color(median_square_filtered_image) << "\n"; // Print average color of square median filtering image
    cout << variance(median_square_filtered_image) << "\n"; // Print variance of square median filtering image

    vector<vector<int>> median_diamond_filtered_image = create_diamond_median_filtering_image(image, 2); // r = 2
    cout << average_color(median_diamond_filtered_image) << "\n"; // Print average color of diamond median filtering image
    cout << variance(median_diamond_filtered_image) << "\n"; // Print variance of diamond median filtering image
    
    return 0;
}
