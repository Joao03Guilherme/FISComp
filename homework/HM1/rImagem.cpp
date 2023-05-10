# include <fstream> // ifstream
# include <vector> // vector
# include <string> // string
# include <sstream> // istringstream
# include <iostream> // cout
# include <cmath> // pow

using namespace std;

const string INVERTED_IMAGE_FILENAME = "glassware_noisy_inverted.ascii.pgm"; 
const string REDUCED_NOISE_IMAGE_FILENAME = "glassware_reduced_noise.ascii.pgm";
const string BOX_FILTERED_IMAGE_FILENAME = "glassware_box_reduced_noise.ascii.pgm";

int N, width, height;
string protocol, line;

vector<vector<int>> read_image(string filename); // Read image
vector<int> histogram_absolute(vector<vector<int>> image); // Create absolute histogram
vector<double> histogram_relative(vector<vector<int>> image); // Create relative histogram
void print_image(vector<vector<int>> image); // Print image
template<typename T> void print_histogram(vector<T> const &histogram); // Print histogram
int average_color(vector<vector<int>> image); // Calculate average color
double variance(vector<vector<int>> image); // Calculate variance
void create_image_file(vector<vector<int>> image, string filename); // Create image file
int calculate_eight_average(vector<vector<int>> image, int i, int j); // Calculate eight average (8 pixels)
vector<vector<int>> create_inverted_image(vector<vector<int>> image); // Create inverted image
vector<vector<int>> create_reduced_noise_image(vector<vector<int>> image); // Create reduced noise image
int calculate_filtered_average(vector<vector<int>> image, vector<vector<double>> filter, int i, int j); // Calculate filtered average (9 pixels)
vector<vector<int>> create_box_filtering_image(vector<vector<int>> image); // Create box filtering image

int main(void) {
    vector<vector<int>> image = read_image("glassware_noisy.ascii.pgm"); // Read image
    vector<vector<int>> inverted_image = create_inverted_image(image); 
    vector<vector<int>> reduced_noise_image = create_reduced_noise_image(image);
    vector<vector<int>> box_filtered_image = create_box_filtering_image(image);
    return 0;
}

vector<vector<int>> read_image(string filename) {
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

vector<int> histogram_absolute(vector<vector<int>> image) {
    vector<int> histogram(N+1, 0); // Create histogram vector

    for (int i = 0; i < height; i++) { // Poupulate histogram
        for (int j = 0; j < width; j++) {
            histogram[image[i][j]]++;    
        }
    }
    
    return histogram;
}

vector<double> histogram_relative(vector<vector<int>> image) {
    vector<int> histogram = histogram_absolute(image); // Get absolute histogram
    vector<double> histogram_relative(N+1, 0.0); // Create relative histogram vector
    double total = width * height; // Total number of pixels

    for (int i = 0; i < N+1; i++) { // Poupulate relative histogram
        histogram_relative[i] = (double) histogram[i] * 100 / (total);
    }

    return histogram_relative;
}

void print_image(vector<vector<int>> image) {
    for (int i = 0; i < height; i++) { // Print image
        for (int j = 0; j < width; j++) {
            cout << image[i][j] << " ";
        }
        cout << endl;
    }
}

template<typename T>    
void print_histogram(vector<T> const &histogram) {
    for (int i = 0; i < N+1; i++) { // Print histogram
        cout << i << ": " << histogram[i] << endl;
    }
}

int average_color(vector<vector<int>> image) {
    double sum = 0.0;
    double total = width * height * 1.0;

    vector<int> histogram = histogram_absolute(image); // Get absolute histogram
    for (int i = 0; i <= N; i++) {
        sum += i * histogram[i];
    }

    return (int) sum / total;
}

double variance(vector<vector<int>> image) { 
    int average = average_color(image); 
    double total = width * height * 1.0; 
    double sum = 0;
    vector<int> histogram = histogram_absolute(image);

    for (int i = 0; i <= N; i++) { 
        sum += histogram[i] * pow(i - average, 2);
    }

    return sum / (total - 1);
}

void create_image_file(vector<vector<int>> image, string filename) {
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

vector<vector<int>> create_inverted_image(vector<vector<int>> image) {
    vector<vector<int>> new_image(height, vector<int>(width));

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            new_image[i][j] = N - image[i][j];
        }
    }

    create_image_file(new_image, INVERTED_IMAGE_FILENAME);
    return new_image;
}

int calculate_eight_average(vector<vector<int>> image, int i, int j) {
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

vector<vector<int>> create_reduced_noise_image(vector<vector<int>> image) {
    vector<vector<int>> new_image(height, vector<int>(width));
    for (int i = 0; i < height; i++) { // Calculate average of 8 pixels
        for (int j = 0; j < width; j++) {
            new_image[i][j] = calculate_eight_average(image, i, j);
        }
    }

    create_image_file(new_image, REDUCED_NOISE_IMAGE_FILENAME);
    return new_image;
}

int calculate_filtered_average(vector<vector<int>> image, vector<vector<double>> filter, int i, int j) {
    double sum = 0;

    for (int dy = -1; dy <= 1; dy++) { // Calculate sum of 9 pixels 
        for (int dx = -1; dx <= 1; dx++) { 
            if (i + dy < 0 || i + dy >= height || j + dx < 0 || j + dx >= width) continue;
            else { // If pixel is not out of bounds
                sum += image[i+dy][j+dx] * filter[dy+1][dx+1];
            }
        }
    }

    return (int) sum;
}

vector<vector<int>> create_box_filtering_image(vector<vector<int>> image) {
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