#include<bits/stdc++.h>
using namespace std;

unordered_map<char, vector<string>> productions;
unordered_map<char, unordered_set<char>> first_sets;
unordered_map<char, unordered_set<char>> follow_sets;

void find_first_sets(char symbol) {
    vector<string> production_rules = productions[symbol];
    unordered_set<char> first_set;

    for (string rule : production_rules) {
        char first_symbol = rule[0];

        first_set.insert(first_symbol);
    }

    first_sets[symbol] = first_set;
}

void find_follow_sets(char symbol) {
    unordered_set<char> follow_set;

    if (symbol == 'S') {
        follow_set.insert('$');
    }

    for (auto production : productions) {
        char non_terminal = production.first;
        // cout<<non_terminal<<"\n";
        vector<string> production_rules = production.second;

        for (string rule : production_rules) {
            size_t index = rule.find(symbol);

            if (index != string::npos) {
                    char next_symbol = rule[index + 1];
                    follow_set.insert(next_symbol);
            }    
        }
    }
    follow_sets[symbol] = follow_set;
}

int main() {
    productions['S'] = {"aAa", "bBb"};
    productions['A'] = {"aBa", "aa"};
    productions['B'] = {"b"};

    // compute first sets for all non-terminals in the grammar
for (auto production : productions) {
    char symbol = production.first;
    find_first_sets(symbol);
}

// compute follow sets for all non-terminals in the grammar
for (auto production : productions) {
    char symbol = production.first;
    find_follow_sets(symbol);
}

    cout << "First sets:" << endl;

    for (auto first_set : first_sets) {
        char symbol = first_set.first;
        unordered_set<char> symbols = first_set.second;

        cout << symbol << " : { ";

        for (char symbol : symbols) {
            cout << symbol << " ";
        }

        cout << "}" << endl;
    }

    cout << endl << "Follow sets:" << endl;

    for (auto follow_set : follow_sets) {
        char symbol = follow_set.first;
        unordered_set<char> symbols = follow_set.second;

        cout << symbol << " : { ";

        for (char symbol : symbols) {
            cout << symbol << " ";
        }

        cout << "}" << endl;
    }

    return 0;
}
