/* Triangle Containment.cpp : This file contains the 'main' function. Program execution begins and ends there.       *
 * Problem 102 on projecteuler.net: Using triangles.txt, a 27K text file containing the co-ordinates of one thousand *
 * "random" triangles, find the number of triangles for which the interior contains the origin.                      */

using namespace std;
#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <string>
#include <boost/tokenizer.hpp>


// Returns true or false based on whether the origin is contatined within the triangle
bool testTriangleContainment(vector<int> coords){
    const int origin[2] = { 0, 0 };
    double triangleArea = abs((coords[0] * (coords[3] - coords[5]) + coords[2] * (coords[5] - coords[1]) + coords[4] * (coords[1] - coords[3]))) / 2.0;
    double checkTriangle1 = abs((origin[0] * (coords[3] - coords[5]) + coords[2] * (coords[5] - origin[1]) + coords[4] * (origin[1] - coords[3]))) / 2.0;
    double checkTriangle2 = abs((coords[0] * (origin[1] - coords[5]) + origin[0] * (coords[5] - coords[1]) + coords[4] * (coords[1] - origin[1]))) / 2.0;
    double checkTriangle3 = abs((coords[0] * (coords[3] - origin[1]) + coords[2] * (origin[1] - coords[1]) + origin[0] * (coords[1] - coords[3]))) / 2.0;
    if (checkTriangle1 + checkTriangle2 + checkTriangle3 == triangleArea){ // if the areas of the three triangles formed by the vertexes and  
        cout << "Found a triangle containing the origin!" << '\n';         // origin add up to the actual triangle's area, it contains the origin.
        return true;
    }
    else
        return false;
}

//Parses a line from a CSV file and returns a string vector of the separated words
vector<string> parseCSVLine(string line) {
    using namespace boost;

    vector<string> vec;
    // Tokenizes the input string
    typedef tokenizer<escaped_list_separator<char>> tk;
    tk tok{ line };
    for (const auto &t : tok) {
        vec.push_back(t);
        //cout << "parseCSVLine: " << t << '\n'; //debug output
    }
    return vec;
}


int main(){
    int containedOrigins = 0;
    ifstream trianglesFile;
    trianglesFile.open("p102_triangles.txt");

    if (trianglesFile.is_open()){  // Check if file is open
        cout << "File opened!" << endl;

        string line;
        vector<string> coordsStr;
        vector<int> coords;

        while (trianglesFile) { // while last read operation was successful, repeat
            getline(trianglesFile, line);
            coordsStr = parseCSVLine(line);
            for (int i = 0; i < coordsStr.size(); i++) { // cast string values into ints, put into vector of ints
                int num = atoi(coordsStr.at(i).c_str());
                coords.push_back(num);
                //cout << "Conversion: " << coords.at(i) << '\n'; //debug output
            }
            if (testTriangleContainment(coords) == true)
                containedOrigins++;
            coordsStr.clear();
            coords.clear();
        }
        cout << "There are " << containedOrigins << " triangles containing the origin." << '\n'; // Return how many triangles contain the origin
    }
    else
        cerr << "ERROR: The file did not open!\n";
    trianglesFile.close();
}
