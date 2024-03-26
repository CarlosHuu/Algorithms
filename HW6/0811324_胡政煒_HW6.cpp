#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <ctime>
using namespace std;

void generateLCS(vector<double>& X, vector<double>& Y, vector<double>& Z, int i, int j, int k,
    vector<vector<vector<int> > >& lookup, vector<double>& currentLCS, set<vector<double> >& result);

set<vector<double> > findLCS(vector<double>& X, vector<double>& Y, vector<double>& Z);

// Function to find all longest common subsequences of three vectors
set<vector<double> > findLCS(vector<double>& X, vector<double>& Y, vector<double>& Z)
{
    int m = X.size();
    int n = Y.size();
    int p = Z.size();

    // Create a 3D lookup table to store the length of LCS
    vector<vector<vector<int> > > lookup(m + 1, vector<vector<int> >(n + 1, vector<int>(p + 1, 0)));

    // Compute the length of LCS using bottom-up dynamic programming approach
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= p; k++) {
                if (X[i - 1] == Y[j - 1] && Y[j - 1] == Z[k - 1]) {
                    lookup[i][j][k] = lookup[i - 1][j - 1][k - 1] + 1;
                }
                else {
                    lookup[i][j][k] = max(max(lookup[i - 1][j][k], lookup[i][j - 1][k]), lookup[i][j][k - 1] );
                }
            }
        }
    }

    // Backtrack and generate all LCS subsequences
    set<vector<double> > lcsSet;
    vector<double> currentLCS;
    generateLCS(X, Y, Z, m, n, p, lookup, currentLCS, lcsSet);

    return lcsSet;
}

// Function to backtrack and generate all LCS subsequences
void generateLCS(vector<double>& X, vector<double>& Y, vector<double>& Z, int i, int j, int k,
    vector<vector<vector<int> > >& lookup, vector<double>& currentLCS, set<vector<double> >& result)
{
    // If we have reached the end of any vector, add the current LCS subsequence to the result
    if (i == 0 || j == 0 || k == 0) {
        result.insert(currentLCS);
        return;
    }

    // If the current elements in all three vectors are equal, include it in the current LCS subsequence
    // and move to the previous indices in all vectors
    if (X[i - 1] == Y[j - 1] && Y[j - 1] == Z[k - 1]) {
        currentLCS.insert(currentLCS.begin(), X[i - 1]);
        generateLCS(X, Y, Z, i - 1, j - 1, k - 1, lookup, currentLCS, result);
        currentLCS.erase(currentLCS.begin());
    }

    // If the value in the lookup table for the current position came from the top cell, move up
    if (i > 0 && lookup[i][j][k] == lookup[i - 1][j][k]) {
        generateLCS(X, Y, Z, i - 1, j, k, lookup, currentLCS, result);
    }

    // If the value in the lookup table for the current position came from the left cell, move left
    if (j > 0 && lookup[i][j][k] == lookup[i][j - 1][k]) {
        generateLCS(X, Y, Z, i, j - 1, k, lookup, currentLCS, result);
    }

    // If the value in the lookup table for the current position came from the top-left cell, move diagonally
    if (k > 0 && lookup[i][j][k] == lookup[i][j][k - 1]) {
        generateLCS(X, Y, Z, i, j, k - 1, lookup, currentLCS, result);
    }
}

int main()
{
    vector<double> X, Y, Z;
    int lx, ly, lz; // length of X, Y, Z
    // double k; // receive elements input from user

    // // Read the length and elements of sequence X from the user
    // cout << "Enter the length of sequence X: ";
    // cin >> lx;
    // cout << "Enter the elements of sequence X: ";
    // for (int i=0; i<lx; i++) {
    //     cin >> k;
    //     X.push_back(k);
    // }

    // // Read the length and elements of sequence Y from the user
    // cout << "Enter the length of sequence Y: ";
    // cin >> ly;
    // cout << "Enter the elements of sequence Y: ";
    // for (int i=0; i<ly; i++) {
    //     cin >> k;
    //     Y.push_back(k);
    // }

    // // Read the length and elements of sequence Z from the user
    // cout << "Enter the length of sequence Z: ";
    // cin >> lz;
    // cout << "Enter the elements of sequence Z: ";
    // for (int i=0; i<lz; i++) {
    //     cin >> k;
    //     Z.push_back(k);
    // }

    // Generate random elements for sequence X
    cout << "Enter the length of sequence X: ";
    cin >> lx;
    cout << "Sequence X: ";
    srand(time(0)); // seed the random number generator with current time
    for (int i = 0; i < lx; i++) {
        double randomElement = rand() % 10; // generate random number between 0 and 9
        X.push_back(randomElement);
        cout << randomElement << " ";
    }
    cout << endl;

    // Generate random elements for sequence Y
    cout << "Enter the length of sequence Y: ";
    cin >> ly;
    cout << "Sequence Y: ";
    for (int i = 0; i < ly; i++) {
        double randomElement = rand() % 10; // generate random number between 0 and 9
        Y.push_back(randomElement);
        cout << randomElement << " ";
    }
    cout << endl;

    // Generate random elements for sequence Z
    cout << "Enter the length of sequence Z: ";
    cin >> lz;
    cout << "Sequence Z: ";
    for (int i = 0; i < lz; i++) {
        double randomElement = rand() % 10; // generate random number between 0 and 9
        Z.push_back(randomElement);
        cout << randomElement << " ";
    }
    cout << endl;

    set<vector<double> > lcsSet = findLCS(X, Y, Z);

    // Print all LCS subsequences
    for (const vector<double>& lcs : lcsSet) {
        for (const double& num : lcs) {
            cout << num << " ";
        }
        cout << endl;
    }

    return 0;
}

