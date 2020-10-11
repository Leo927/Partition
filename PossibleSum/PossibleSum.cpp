// PossibleSum.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

typedef vector <int> Solution;
void printSolution(const vector<Solution>& solVec);

Solution cpToSol(int k, const Solution& comPos);

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


vector<Solution> partition( int k, int n )
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
            result.push_back(Solution{ i });
        }
        return result;
    }
    auto prev = partition(k, n-1);
    vector<Solution> result;
    for (auto solution : prev)
    {
        
            for (int i = solution.back(); i <= k; i++)
            {
                auto newSol = solution;
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
    sol.push_back(k - comPos[i-1]);
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
        file << k << " " << n<<endl;
        vector<Solution> sol = partition(k, n);
        cpVec2SolVec(k, sol);
        printSolution(sol, cout);
        printSolution(sol, file);
    }   
    file.close();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
