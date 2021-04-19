/******************************************************************************
* CSCE 4600 - Operating Systems Section 002
*  Instructor: Dr. Marty O'Neill
*  Due Date: April 23rd, 2021
*
*  Contributors: - Gabriel Lopez (gabriellopez3@my.unt.edu)
*                - Joseph Fergen
*                - Garret 
*                -
*
*  Summary: In this program, we must develop a system that can determine
*  whether or not a particular resource allocation graph represents a deadlock
*  state, either through graph reduction or knot detection.
* 
*******************************************************************************/
#include <stdio.h>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

using namespace std;

int main() 
{
    //Strings
    string line;    // Used for a row of the matrix
    string filename = "Project-2-input-example.txt";  

    //Counters
    num_processes;  // Number of processes.
    num_resources;  // Number of resources.

    //Vectors
    vector <int> resources;             // Vector with a list of available resources
    vector <vector<int>> inputMatrix;   // Input matrix from the file
    vector <vector<int>> aMatrix;       // Alloc matrix
    vector <vector<int>> rMatrix;       // Request Matrix

     //File opening
    ifstream infile(filename);

    if (infile.is_open())   // Success
    {
        //Do the parsing

        while (getline(infile, line))
        {
           //Using Delimiters, use getline and only get the important values. Make sure to convert to int if needed.

        }
    }

    else                    // Failure
    {
        cout << "Unable to open file: " << filename << endl;
        exit(1);

    }


    return 0;
}