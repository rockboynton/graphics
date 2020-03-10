/*
Lab 1
Rock Boynton
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>
#include <algorithm>

using namespace std;

int main(int argc, char * argv[]) {
    if (argc < 2) {
        cout << "Must include a filename" << endl;
        return 1;
    }

    ifstream filein(argv[1]);
    string line;
    string word;
    double num;
    int facets = 0;

    const double big = numeric_limits<double>::max();
    const double small = numeric_limits<double>::min();

    double max[3] = {small, small, small};
    double min[3] = {big, big, big};

    while (!filein.eof()) {
        getline(filein, line);
        istringstream sstream(line);
        sstream >> word;
        if (!word.compare("facet")) {
            cout << "facet " << facets << endl;

            getline(filein, line); // ignore loop declaration
            getline(filein, line);

            for (int i = 1; i <= 3; ++i) {
                istringstream sstream(line);
                sstream >> word; // ignore "vertex"
                sstream >> num;

                cout << "   x" << i << ":" << num << " ";
                max[0] = std::max(max[0], num);
                min[0] = std::min(min[0], num);

                sstream >> num;
                cout << "   y" << i << ":" << num << " ";
                max[1] = std::max(max[1], num);
                min[1] = std::min(min[1], num);

                sstream >> num;
                cout << "   z" << i << ":" << num << endl;
                max[2] = std::max(max[2], num);
                min[2] = std::min(min[2], num);

                getline(filein, line);
            }

            cout << endl;
            facets++;
        }
    }
    cout << "Summary" << endl;

    cout << "   Max" << endl;
    cout << "       x" << max[0];
    cout << "       y" << max[1];
    cout << "       z" << max[2] << endl;

    cout << "   Min" << endl;
    cout << "       x" << min[0];
    cout << "       y" << min[1];
    cout << "       z" << min[2] << endl;


    filein.close();
    return 0;
}