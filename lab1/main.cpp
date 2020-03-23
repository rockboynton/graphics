/*
Lab 1
Rock Boynton
CS 3210

Write a C++ console program that will:
• Accept a filename of an ASCII STL file via the command line
• Open and read file (recommend reading line-by-line using getline)
• Identify each facet, and print the coordinates of each of its vertices to the
  console, readable and formatted. The exact formatting is up to you.
• Summarize contents
    o the number of facets in the file
    o the min and max of the x, y, and z coordinates
• No need to store vertices, etc – we will do that later
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>
#include <algorithm>
#include <iomanip>

using namespace std;

ifstream& print_vertices(ifstream& filein, double max[], double min[]);
void print_summary(int facets, double max[], double min[]);

int main(int argc, char * argv[]) {
    // end program if filename is not provided
    if (argc < 2) {
        cout << "Must include a filename" << endl;
        return 1;
    }

    // open stream and declare variables needed to read .stl file
    ifstream filein(argv[1]);
    string line;
    string word;
    int facets = 0;

    // set initial min max values as large and small, respectively
    const double big = numeric_limits<double>::max();
    const double small = numeric_limits<double>::min();
    double max[3] = {small, small, small}; // [x, y, z]
    double min[3] = {big, big, big}; // [x, y, z]

    while (!filein.eof()) {
        getline(filein, line);
        istringstream sstream(line);
        sstream >> word;
        if (!word.compare("facet")) {
            cout << "facet " << facets << endl;
            getline(filein, line); // ignore loop declaration
            getline(filein, line); // get first vertex
            print_vertices(filein, max, min);
            cout << endl;
            facets++;
        }
    }
    print_summary(facets, max, min);
    filein.close();
    return 0;
}

/**
 * @brief Prints a facet's vertices and updates min/max coordinates if 
 * necessary
 * 
 * @param filein - .stl file stream
 * @param max - the max x, y, and z coordinates
 * @param min - the min x, y, and z coordinates
 */
ifstream& print_vertices(ifstream& filein, double max[], double min[]) {
    string line;
    string word;
    double num;
    for (int i = 1; i <= 3; ++i) {
        istringstream sstream(line);
        sstream >> word; // ignore "vertex"
        sstream >> num;

        cout << fixed << setprecision(6);
        cout << setfill(' ');

        cout << setw(5) << "x" << i << ":" << setw(10) << num;
        max[0] = std::max(max[0], num);
        min[0] = std::min(min[0], num);

        sstream >> num;
        cout << setw(5) << "y" << i << ":" << setw(10) << num;
        max[1] = std::max(max[1], num);
        min[1] = std::min(min[1], num);

        sstream >> num;
        cout << setw(5) << "z" << i << ":" << setw(10) << num << endl;
        max[2] = std::max(max[2], num);
        min[2] = std::min(min[2], num);

        getline(filein, line);
    } 
    return filein;
}

/**
 * @brief Prints a summary of the .stl file contents
 * 
 * @param facets - number of facets in the .stl file
 * @param max - the max x, y, and z coordinates
 * @param min - the min x, y, and z coordinates
 */
void print_summary(int facets, double max[], double min[]) {
    cout << setfill(' ');
    cout << "---------------------------------------------" << endl;
    cout << "Summary\n" << endl;

    cout << "Number of Facets: " << facets << "\n" << endl;

    cout << "Max" << endl;
    cout << setw(6) << "x:" << setw(10) << max[0];
    cout << setw(6) << "y:" << setw(10) << max[1];
    cout << setw(6) << "z:" << setw(10) << max[2] << endl;

    cout << "Min" << endl;
    cout << setw(6) <<  "x:" << setw(10) << min[0];
    cout << setw(6) <<  "y:" << setw(10) << min[1];
    cout << setw(6) <<  "z:" << setw(10) << min[2] << endl;   
}