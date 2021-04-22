/*
*****************************************************************************
* CSCE 4600 - Operating Systems Section 002
*  Instructor: Dr. Marty O'Neill
*  Due Date: April 23rd, 2021
*
*  Contributors: - Gabriel Lopez (gabriellopez3@my.unt.edu)
*                - Joseph Fergen (josephfergen@my.unt.edu)
*                - Garrett Morgan (garrettmorgan3@my.unt.edu) 
*                -
*
*  Summary: In this program, we must develop a system that can determine
*  whether or not a particular resource allocation graph represents a deadlock
*  state, either through graph reduction or knot detection.
* 
******************************************************************************
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

vector<bool> getReachableSet(vector<vector<int>> inputMatrix, int node) //This is a BFS algorithm to find the path each node can reach
{
    vector<bool> ReachableSet;
    ReachableSet.resize(inputMatrix.size(), false);
    queue<int> Queue;
    ReachableSet[node] = true;

    for (int i = 0; i<inputMatrix.size(); i++) //This for loop sets up the first entries into the Queue
    {
        if(inputMatrix[node][i] == 1)
        {
            if(ReachableSet[i] == false)
            {
                Queue.push(i); //Push all nodes this node can reach
            }
        }
    }

    while(!Queue.empty())
    {
        node = Queue.front(); //Get the node on the front
        ReachableSet[node] = true; //Say its reachable
        Queue.pop(); //Remove it from queue

        for (int i = 0; i<inputMatrix.size(); i++)
        {
            if(inputMatrix[node][i] == 1) //If an edge exists
            {
                if(ReachableSet[i] == false) //And its a new unique edge
                {
                    Queue.push(i); //Add it to the queue
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


    // Get filename from user
    cout << "Enter name of file containing data: ";
    cin >> fileName;
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
    
    vector<bool> KnotSolution, KnotTest;
    bool Knot = true; //This is used to find where the Knot is no longer true
    bool KnotFound = false; //This is used to see if a Knot fully exists
    
    //Knot Detection
    for(int i = 0; i < inputMatrix.size(); i++) 
    {
        Knot = true; //Both need to be reset
        KnotFound = false; 

        KnotSolution = getReachableSet(inputMatrix, i); //Get everything reachable from i

        //Testing against KnotSolution
        for(int j = 0; j < KnotSolution.size(); j++)
        {
            if(j != i) //If i and j are the same they have the same reachable set so no need to retest
            {
                KnotTest = getReachableSet(inputMatrix, j);
                if(KnotTest != KnotSolution) //If the sets aren't the same it's not a knot
                {
                    Knot = false;
                }
            }
            if(Knot == false) //If you can prove something isn't a knot at one place, it's not a knot
            {
                break; //So try again
            }

            if((Knot == true) && (j == (KnotSolution.size()-1))) //However if the last j is used and Knot is still true
            {
                KnotFound = true; //Then we found a Knot
            }
        }

        if(KnotFound == true) //Finding one knot is enough
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
            cout<<i<<" ";
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
