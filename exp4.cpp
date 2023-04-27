#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

unordered_map<char, vector<string>> productions;
unordered_map<char, unordered_set<char>> first_sets;
unordered_map<char, unordered_set<char>> follow_sets;

void find_first_sets(char symbol) {
    vector<string> production_rules = productions[symbol];
    unordered_set<char> first_set;

    for (string rule : production_rules) {
        char first_symbol = rule[0];

        if (isupper(first_symbol)) {
            find_first_sets(first_symbol);

            unordered_set<char> first_symbols = first_sets[first_symbol];

            for (char symbol : first_symbols) {
                first_set.insert(symbol);
            }
        }
        else {
            first_set.insert(first_symbol);
        }
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
        vector<string> production_rules = production.second;

        for (string rule : production_rules) {
            size_t index = rule.find(symbol);

            if (index != string::npos) {
                if (index + 1 < rule.size()) {
                    char next_symbol = rule[index + 1];

                    if (isupper(next_symbol)) {
                        unordered_set<char> first_symbols = first_sets[next_symbol];

                        for (char symbol : first_symbols) {
                            if (symbol != 'e') {
                                follow_set.insert(symbol);
                            }
                        }

                        if (first_symbols.find('e') != first_symbols.end()) {
                            find_follow_sets(non_terminal);

                            unordered_set<char> follow_symbols = follow_sets[non_terminal];

                            for (char symbol : follow_symbols) {
                                follow_set.insert(symbol);
                            }
                        }
                    }
                    else {
                        follow_set.insert(next_symbol);
                    }
                }
                else {
                    find_follow_sets(non_terminal);

                    unordered_set<char> follow_symbols = follow_sets[non_terminal];

                    for (char symbol : follow_symbols) {
                        follow_set.insert(symbol);
                    }
                }
            }
        }
    }

    follow_sets[symbol] = follow_set;
}

int main() {
    productions['S'] = {"A", "B"};
    productions['A'] = {"aB", "aa"};
    productions['B'] = {"b"};

    for (auto production : productions) {
        char symbol = production.first;
        find_first_sets(symbol);
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
