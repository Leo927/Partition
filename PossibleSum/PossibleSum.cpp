// PossibleSum.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
using namespace std;

typedef vector < vector<int>> solution;

typedef vector<vector<solution>> solTable;


void initSolTable(solTable& table, int n, int k)
{
    table = solTable(k + 1, vector<solution>(n + 1, solution()));
    //set (0,0)
    table[0][0] = solution{ {} };
    //initialize the second column (i,1)
    for (int i = 0; i <= k; i++)
    {
        table[i][1] = solution{ {i} };
    }
    //initialize the second column (i,2)
    for (int i = 0; i <= k; i++)
    {
        for (int p = i; p >= 0; p--)
        {
            table[i][2].push_back(vector<int>{p, i - p});
        }
    }
}


void printSolution(const solution& sol)
{
    if (sol.size() <= 0)
        cout << "empty";
    for (int k = 0; k < sol.size(); k++)
    {
        cout << "[";
        for (int p = 0; p < sol[k].size(); p++)
        {
            cout << sol[k][p] << ", ";
        }
        cout << "]\n";
    }
}


void printTable(const solTable& table)
{
    for (int i = 0; i < table.size(); i++)
    {
        for (int j = 0; j < table[0].size(); j++)
        {
            if (table[i][j].size() <= 0)
                cout << "empty";
            for (int k = 0; k < table[i][j].size(); k++)
            {                  
                cout << "[";
                for (int p = 0; p < table[i][j][k].size(); p++)
                {
                    cout << table[i][j][k][p] << ", ";
                }
                cout << "], ";
            }
            cout << "\t";
        }
        cout << endl;
    }
}

/// <summary>
/// 
/// </summary>
/// <param name="n">number of nonnegative integars</param>
/// <param name="k">sum of these integars</param>
/// <returns></returns>
solution& partition(solTable& table, int n, int k)
{
    if (table[k][n].size() > 0)
        return table[k][n];
    /*using dynamic programming method, taking a top-down approach
    * take (n-1,k) solution and mutate it once 
    *   for each combination in the solution
    *       for each number in the combination
    *           temp = partition(2,number)
    *           for each solution in temp
    *               table[k][n].push(combination with the number replaced by temp)
    *return table[k][n]
    *           
    *           
    */
    solution prev = partition(table, n - 1, k);
    for (auto combination : prev)
    {
        for(int i = 0; i < combination.size(); i++)
        {
            if (combination[i] == 0)
                continue;
            auto numSplited = partition(table, 2, combination[i]);
            for (auto c : numSplited)
            {
                
                vector<int> newComb = combination;
                newComb.erase(newComb.begin() + i);
                for (auto num : c)
                {
                    newComb.insert(newComb.begin() + i, num);
                } 
                table[k][n].push_back(newComb);
            }
        }
    }
    return table[k][n];
}




int main()
{
    solTable table;
    int n = 3;
    int k = 3;
    initSolTable(table, n, k);
    printSolution(partition(table, n, k));
    //printTable(table);
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
