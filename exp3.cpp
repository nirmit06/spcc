#include <bits/stdc++.h>
using namespace std;

// Function to remove left recursion from a production rule
void removeLeftRecursion(string nonTerminal, vector<string> productions) {
    // Split the productions into those with and without left recursion
    vector<string> alpha, beta;
    for (int i = 0; i < productions.size(); i++) {
        if (productions[i].find(nonTerminal) == 0) {
            alpha.push_back(productions[i].substr(nonTerminal.length()));
        }
        else {
            beta.push_back(productions[i]);
        }
    }

    // If there is no left recursion, return the original productions
    if (alpha.size() == 0) {
        for (int i = 0; i < productions.size(); i++) {
            cout << nonTerminal << " -> " << productions[i] << endl;
        }
        return;
    }

    // Create a new non-terminal symbol
    string newNonTerminal = nonTerminal + "'";

    // Output the new productions
    cout << nonTerminal << " -> ";
    for (int i = 0; i < beta.size(); i++) {
        cout << beta[i] << newNonTerminal;
        if (i != beta.size() - 1) {
            cout << " | ";
        }
    }
    cout << endl;

    cout << newNonTerminal << " -> ";
    for (int i = 0; i < alpha.size(); i++) {
        cout << alpha[i]<< newNonTerminal;
        if (i != alpha.size() - 1) {
            cout << " | ";
        }
    }
    cout << "epsilon" << endl;
}

int main() {
    // Example grammar: E -> E+T | T
    vector<string> productions = {"E+T", "T"};
    removeLeftRecursion("E", productions);

    return 0;
}
