#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ifstream fin;
    string fileName, fileContent;
    int numProcesses, numResources, j = 0, k = 0;
    bool foundProcesses = false, foundUnits = false;
    vector <int> resources;
    vector <vector<int>> inputMatrix;

    fileName = "input-example.txt";
    // cout << "Enter name of file containing data: ";
    // cin >> fileName;
    fin.open(fileName);

    while (fin.fail()) {
        cout << "Invalid file name. Try again: ";
        cin >> fileName;
        fin.open(fileName);
    }

    while (getline(fin, fileContent)) {
        // trim(fileContent);

        if (fileContent.empty() || fileContent[0] == '%') {
            continue;
        }

        // Find and set numProcesses & numResources
        int foundEquals = fileContent.find('=');
        if (foundEquals >= 0 && !foundProcesses) {
            numProcesses = fileContent[foundEquals+1];
            foundEquals = -1;
            foundProcesses = true;
            continue;
        }
        if (foundEquals >= 0 && foundProcesses) {
            numResources = fileContent[foundEquals+1];
            foundEquals = -1;
            continue;
        }

        // cout << "fileContent: " << fileContent.length() << endl;
        // Find and set the units for each resource
        if (!foundUnits) {
            istringstream ss(fileContent);
            string s;
            
            while (ss) {
                if (!getline(ss, s, ',')) {
                    break;
                }

                resources.push_back(stoi(s));
            }

            foundUnits = true;
            continue;
        }

        // Find and set the ajacency matrix from file
        istringstream ss(fileContent);
        string s;
        vector <int> newRow;

        while (ss) {
            if (!getline(ss, s, ',')) {
                inputMatrix.push_back(newRow);
                break;
            }

            newRow.push_back(stoi(s));
        }
    }

    // Print out adjacency matrix
    // for (int i = 0; i < inputMatrix.size(); i++) {
    //     for (int j = 0; j < inputMatrix[i].size(); j++) {
    //         cout << inputMatrix[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    
    fin.close();
    return 0;
}