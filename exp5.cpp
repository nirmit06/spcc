#include <bits/stdc++.h>
//input string: aabb
using namespace std;

// Define the grammar rules
map<int, string> rules = {
    {1, "S -> AB"},
    {2, "A -> aA"},
    {3, "A -> a"},
    {4, "B -> bB"},
    {5, "B -> b"}
};

// Define the SLR parsing table
map<pair<int, char>, int> action = {
    {{0, 'a'}, 2},
    {{2, 'a'}, 2},
    {{2, 'b'}, 3},
    {{3, 'b'}, 4}
};

map<pair<int, char>, int> goTo = {
    {{0, 'A'}, 1},
    {{0, 'B'}, 2},
    {{2, 'A'}, 1}
};

// Define the SLR parser function
bool SLRParser(string input) {
    
    stack<int> stateStack;
    stack<char> symbolStack;
    int currentState = 0;

    symbolStack.push('$');
    stateStack.push(currentState);

    for (char c : input) {
        while (true) {
            int a = action[{currentState, c}];
            stateStack.push(a);
            symbolStack.push(c);
            currentState = a;
            break;
        }
    }

    return true;
}

int main() {
    string input;
    cout << "Enter a string: ";
    cin >> input;

    if (SLRParser(input)) {
        cout << "Accepted!" << endl;
    } else {
        cout << "Rejected!" << endl;
    }

    return 0;
}
