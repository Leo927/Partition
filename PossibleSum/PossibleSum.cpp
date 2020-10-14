// PossibleSum.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

typedef vector <int> Solution;

/// <summary>
/// print the 2d vector to a stream
/// </summary>
/// <param name="solVec">2d vector to be printed</param>
/// <param name="stream">target stream</param>
void printSolution(const vector<Solution>& solVec, ostream& stream);
/// <summary>
/// Generates the comma position arrangements for a given k and n
/// </summary>
/// <param name="k">The sum of all the numbers</param>
/// <param name="n">The count of numbers</param>
/// <returns></returns>
vector<Solution> partition(int k, int n);
/// <summary>
/// Converts the comma position vector to value vector
/// </summary>
/// <param name="k">The sum of values</param>
/// <param name="comPos">The comma position vector</param>
/// <returns></returns>
Solution cpToSol(int k, const Solution& comPos);
/// <summary>
/// Convert a 2d vector of comma position to a 2d vector of values
/// </summary>
/// <param name="k">The sum of values</param>
/// <param name="comPosVec">2d seperator positon vector</param>
void cpVec2SolVec(int k, vector<Solution>& comPosVec);

void printSolution(const vector<Solution>& solVec, ostream& stream)
{
    if (solVec.size() <= 0)
        stream << "empty";
    for (int k = 0; k < solVec.size(); k++)
    {
        stream << "[";
        for (int p = 0; p < solVec[k].size(); p++)
        {
            stream << solVec[k][p] << ", ";
        }
        stream << "]\n";
    }
}

vector<Solution> partition(int k, int n)
{
    //base case n=2
    //get prev = (k,n-1)
    //foreach solution in prev    //  
    //      for i from solution.last() to k
    //          newSol = solution
    //          newSol.push(i)
    //          prev.push(newSol)
    //return prev
    if (n == 2)
    {
        vector<Solution> result;
        for (int i = 0; i <= k; i++)
        {
            Solution solution;
            solution.push_back(i);
            result.push_back(solution);
        }
        return result;
    }
    vector<Solution> prev = partition(k, n - 1);
    vector<Solution> result;
    for (int j = 0; j < prev.size(); j++)
    {
        for (int i = prev[j].back(); i <= k; i++)
        {
            Solution newSol = prev[j];
            newSol.push_back(i);
            result.push_back(newSol);
        }

    }
    return result;
}

void cpVec2SolVec(int k, vector<Solution>& comPosVec)
{
    for (int i = 0; i < comPosVec.size(); i++)
    {
        comPosVec[i] = cpToSol(k, comPosVec[i]);
    }
}

Solution cpToSol(int k, const Solution& comPos)
{
    Solution sol;
    int i;
    for (i = 0; i < comPos.size(); i++)
    {
        if (i == 0)
        {
            sol.push_back(comPos[i]);
            continue;
        }
        sol.push_back(comPos[i] - comPos[i - 1]);
    }
    sol.push_back(k - comPos[i - 1]);
    return sol;
}



int main()
{
    fstream file("log.txt", ios::out);
    while (true)
    {
        cout << "please enter k and n seperated by space: ";
        file << "please enter k and n seperated by space: ";
        int k;
        int n;
        cin >> k;
        cin >> n;
        file << k << " " << n << endl;
        vector<Solution> sol = partition(k, n);
        cpVec2SolVec(k, sol);
        printSolution(sol, cout);
        printSolution(sol, file);
    }
    file.close();
}
