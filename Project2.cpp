/******************************************************************************
* CSCE 4600 - Operating Systems Section 002
*  Instructor: Dr. Marty O'Neill
*  Due Date: April 23rd, 2021
*
*  Contributors: - Gabriel Lopez (gabriellopez3@my.unt.edu)
*                - Joseph Fergen (josephfergen@my.unt.edu)
*                - Garret 
*                -
*
*  Summary: In this program, we must develop a system that can determine
*  whether or not a particular resource allocation graph represents a deadlock
*  state, either through graph reduction or knot detection.
* 
*******************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

vector<int> getReachableSet(vector<vector<int>> inputMatrix, int node)
{
    vector<int> ReachableSet;
    queue<int> Queue;
    ReachableSet.push_back(node);
    for (int i = 0; i<inputMatrix.size(); i++)
    {
        if(inputMatrix[node][i] == 1)
        {
            Queue.push(i);
        }
    }
    while(!Queue.empty())
    {
        node = Queue.front();
        ReachableSet.push_back(node);
        Queue.pop();
        for (int i = 0; i<inputMatrix.size(); i++)
        {
            if(inputMatrix[node][i] == 1)
            {
                auto finder = find(begin(ReachableSet), end(ReachableSet), i); //Searchs to find the new node in the reachable set already
                if(finder == end(ReachableSet)) //This means that it wasn't found
                {
                    Queue.push(i);
                }
            }
        }
    }

    return ReachableSet;
}

int main() {
    ifstream fin;
    string fileName, fileContent;
    int numProcesses, numResources;
    bool foundProcesses = false, foundUnits = false;
    vector <int> resources;
    vector <vector<int>> inputMatrix;

    fileName = "input-example.txt"; // DELETE THIS AT END
    // UNCOMMENT THIS AT END
    // Get filename from user
    // cout << "Enter name of file containing data: ";
    // cin >> fileName;
    fin.open(fileName);

    // Check filename and ask for correct file name until it works
    while (fin.fail()) {
        cout << "Invalid file name. Try again: ";
        cin >> fileName;
        fin.open(fileName);
    }

    // Read each line of file
    while (getline(fin, fileContent)) {
        // Skip line if empty or starts with a '%'
        if (fileContent.empty() || fileContent[0] == '\r' || fileContent[0] == '%') {
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

    // Print out resource units
    cout << "Resource units: ";
    for (int i = 0; i < resources.size(); i++) {
        cout << resources[i] << " ";
    }
    cout << endl;

    // Print out adjacency matrix
    cout << "Adjacency matrix: " << endl;
    for (int i = 0; i < inputMatrix.size(); i++) {
        for (int j = 0; j < inputMatrix[i].size(); j++) {
            cout << inputMatrix[i][j] << " ";
        }
        cout << endl;
    }
    
    vector<int> KnotSolution, KnotTest;
    bool Knot = true;
    bool KnotFound = false;
    for(int i = 0; i < inputMatrix.size(); i++)
    {
        KnotSolution = getReachableSet(inputMatrix, i);
        for(int j = 0; j < KnotSolution.size(); j++)
        {
            if(KnotSolution[j] != i)
            {
                KnotTest = getReachableSet(inputMatrix, KnotSolution[j]);
                Knot = equal(KnotSolution.begin(), KnotSolution.end(), KnotTest.begin());
            }
            if(Knot == false)
            {
                break;
            }
            if((Knot == true) && (j == (KnotSolution.size()-1)))
            {
                KnotFound = true;
            }
        }
        if(KnotFound == true)
        {
            break;
        }
    }

    if(KnotFound == true)
    {
        cout<<"Knot Found\n";
        cout<<"Knot: \n";
        for(int i=0; i < KnotSolution.size(); i++)
        {
            cout<<KnotSolution[i]<<" ";
        }
        cout << endl;
    }

    else
    {
        cout<<"No knot found\n";
    }


    fin.close();
    return 0;
}