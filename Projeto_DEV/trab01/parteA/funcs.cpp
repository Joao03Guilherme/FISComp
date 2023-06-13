# include <fstream> // ifstream
# include <vector> // vector
# include <string> // string
# include <sstream> // istringstream
# include <iostream> // cout
# include <cmath> // pow, sqrt
# include <algorithm> // sort
# include "funcs.hpp" 

using namespace std;

int N, width, height;
string protocol, line;

vector<vector<int>> read_image(string filename) {
    /*
    Reads image from file given a filename
    */

    ifstream FILE(filename);

    getline(FILE, protocol); // Read first line (protocol)

    getline(FILE, line); // Read width and height
    istringstream iss(line);
    iss >> width >> height; // Split width and height

    getline(FILE, line); // Read max value
    N = stoi(line); // Convert string to int (max value

    // Create image matrix
    vector<vector<int>> image(height, vector<int>(width));

    // Read image
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            FILE >> image[i][j];
        }
    }

    FILE.close(); // Close file
    return image;
}

void create_image_file(vector<vector<int>> image, string filename) {
    /*
    Creates image file from image matrix
    */

    ofstream FILE(filename);

    FILE << protocol << "\n"; // Protocol
    FILE << width << " " << height << "\n"; // Width and height
    FILE << N << "\n"; // Max value

    for (int i = 0; i < height; i++) { 
        for (int j = 0; j < width; j++) {
            FILE << image[i][j] << " ";
        }
        FILE << "\n";
    }
}

void print_int_histogram(vector<int> histogram) {
    /*
    Prints histogram of integers (as values) to stdout
    */

    for (int i = 0; i < N+1; i++) { // Print histogram
        cout << i << ": " << histogram[i] << endl;
    }
}

void print_double_histogram(vector<double> histogram) {
    /*
    Prints histogram of doubles (as values) to stdout
    */

    for (int i = 0; i < N+1; i++) { // Print histogram
        cout << i << ": " << histogram[i] << endl;
    }
}

vector<vector<int>> sum_images(vector<vector<int>> image1, vector<vector<int>> image2) {
    /*
    Sums two images
    */

    vector<vector<int>> new_image(height, vector<int>(width));

    for (int i = 0; i < height; i++) { // Sum images
        for (int j = 0; j < width; j++) {
            new_image[i][j] = image1[i][j] + image2[i][j];
        }
    }

    return new_image;
}

vector<int> histogram_absolute(vector<vector<int>> image) {
    /*
    Creates absolute histogram from image
    */

    vector<int> histogram(N+1, 0); // Create histogram vector

    for (int i = 0; i < height; i++) { // Poupulate histogram
        for (int j = 0; j < width; j++) {
            histogram[image[i][j]]++;    
        }
    }
    
    return histogram;
}

vector<double> histogram_relative(vector<vector<int>> image) {
    /*
    Creates relative histogram from image
    */

    vector<int> histogram = histogram_absolute(image); // Get absolute histogram
    vector<double> histogram_relative(N+1, 0.0); // Create relative histogram vector
    double total = width * height; // Total number of pixels

    for (int i = 0; i < N+1; i++) { // Poupulate relative histogram
        histogram_relative[i] = (double) histogram[i] * 100 / (total);
    }

    return histogram_relative;
}

double calculate_average_color(vector<vector<int>> image) {
    /*
    Calculates average color of image
    */

    double sum = 0.0;
    double total = width * height * 1.0;

    vector<int> histogram = histogram_absolute(image); // Get absolute histogram
    for (int i = 0; i <= N; i++) {
        sum += i * histogram[i];
    }

    return sum / total;
}

double calculate_variance(vector<vector<int>> image) { 
    /*
    Calculates color variance of image
    */

    double average = calculate_average_color(image); 
    double total = width * height * 1.0; 
    double sum = 0;
    vector<int> histogram = histogram_absolute(image);

    for (int i = 0; i <= N; i++) { 
        sum += histogram[i] * pow(i - average, 2);
    }

    return sum / (total - 1);
}

double calculate_standard_deviation(vector<vector<int>> image) {
    /*
    Calculates standard deviation of vector
    */

    double variance = calculate_variance(image);
    return sqrt(variance);
}

int calculate_median(vector<int> v) {
    /*
    Calculates median of vector
    */

    sort(v.begin(), v.end());
    if (v.size() % 2 == 0) { // If vector has even number of elements
        return (v[v.size()/2] + v[v.size()/2 - 1]) / 2;
    } else { // If vector has odd number of elements
        return v[v.size()/2];
    }
}

int calculate_eight_average(vector<vector<int>> image, int i, int j) {
    /*
    Calculates average of 8 pixels around pixel (i, j)
    Ignores center pixel and pixels out of bounds
    */

    int sum = 0;
    int cnt = 0;

    for (int dy = -1; dy <= 1; dy++) { // Calculate average of 8 pixels (except center pixel)
        for (int dx = -1; dx <= 1; dx++) {
            if (i + dy < 0 || i + dy >= height || j + dx < 0 || j + dx >= width || (dx == 0 && dy == 0)) continue;
            else { // If pixel is not out of bounds
                sum += image[i+dy][j+dx];
                cnt++;
            }
        }
    }

    return sum / cnt;
}

int calculate_filtered_average(vector<vector<int>> image, vector<vector<double>> filter, int i, int j) {
    /*
    Calculates average of 9 pixels around pixel (i, j) using filter
    Ignores pixels out of bounds and does not ignore center pixel
    */

    double sum = 0.0;
    double cnt = 0.0;

    for (int dy = -1; dy <= 1; dy++) { // Calculate sum of 9 pixels 
        for (int dx = -1; dx <= 1; dx++) { 
            if (i + dy < 0 || i + dy >= height || j + dx < 0 || j + dx >= width) continue;
            else { // If pixel is not out of bounds
                sum += image[i+dy][j+dx] * filter[dy+1][dx+1];
                cnt += 1.0;
            }
        }
    }

    return (int) sum * 9.0 / cnt; // Normalize sum
}

int calculate_square_median(vector<vector<int>> image, int r, int i, int j) {
    /*
    Calculates median of square of pixels radius r around pixel (i, j)
    */

    vector<int> square;
    for (int dx = -r; dx <= r; dx++) {
        for (int dy = -r; dy <= r; dy++) {
            if (i + dy < 0 || i + dy >= height || j + dx < 0 || j + dx >= width) continue;
            square.push_back(image[i+dy][j+dx]);
            }
        }

    return calculate_median(square);
}

int calculate_diamond_median(vector<vector<int>> image, int r, int i, int j) {
    /*
    Calculates median of diamond of pixels radius r around pixel (i, j)
    */

    vector<int> diamond;
    for (int dx = -r; dx <= r; dx++) {
        for (int dy = -r; dy <= r; dy++) {
            if (i + dy < 0 || i + dy >= height || j + dx < 0 || j + dx >= width) continue;
            if (abs(dx) + abs(dy) <= r) diamond.push_back(image[i+dy][j+dx]);
        }
    }

    return calculate_median(diamond);
}

vector<vector<int>> create_inverted_image(vector<vector<int>> image) {
    /*
    Creates inverted image from image matrix
    */

    vector<vector<int>> new_image(height, vector<int>(width));

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            new_image[i][j] = N - image[i][j];
        }
    }

    create_image_file(new_image, INVERTED_IMAGE_FILENAME);
    return new_image;
}


vector<vector<int>> create_reduced_noise_image(vector<vector<int>> image) {
    /*
    Creates reduced noise image from image matrix
    */

    vector<vector<int>> new_image(height, vector<int>(width));
    for (int i = 0; i < height; i++) { // Calculate average of 8 pixels
        for (int j = 0; j < width; j++) {
            new_image[i][j] = calculate_eight_average(image, i, j);
        }
    }

    create_image_file(new_image, REDUCED_NOISE_IMAGE_FILENAME);
    return new_image;
}


vector<vector<int>> create_box_filtering_image(vector<vector<int>> image) {
    /*
    Creates box filtered image from image matrix
    */

    vector<vector<double>> filter(3, vector<double>(3, 0.11111)); // Populate array with 1/9
    vector<vector<int>> new_image(height, vector<int>(width));

    for (int i = 0; i < height; i++) { // Calculate average of 9 pixels
        for (int j = 0; j < width; j++) {
            new_image[i][j] = calculate_filtered_average(image, filter, i, j);
        }
    }

    create_image_file(new_image, BOX_FILTERED_IMAGE_FILENAME);
    return new_image;
}

vector<vector<int>> create_square_median_filtering_image(vector<vector<int>> image, int r) {
    /*
    Creates square median filtered image from image matrix
    */

    vector<vector<int>> new_image(height, vector<int>(width));
    
    for (int i = 0; i < height; i++) { // Calculate median of square
        for (int j = 0; j < width; j++) {
            new_image[i][j] = calculate_square_median(image, r, i, j);
        }
    }

    create_image_file(new_image, SQUARE_MEDIAN_FILTERED_IMAGE_FILENAME);
    return new_image;
}

vector<vector<int>> create_diamond_median_filtering_image(vector<vector<int>> image, int r) {
    /*
    Creates diamond median filtered image from image matrix
    */

    vector<vector<int>> new_image(height, vector<int>(width));
    
    for (int i = 0; i < height; i++) { // Calculate median of diamond
        for (int j = 0; j < width; j++) {
            new_image[i][j] = calculate_diamond_median(image, r, i, j);
        }
    }

    create_image_file(new_image, DIAMOND_MEDIAN_FILTERED_IMAGE_FILENAME);
    return new_image;
}
