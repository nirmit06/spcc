#include<bits/stdc++.h>

using namespace std;

// Define a data structure to represent the intermediate code
struct IntermediateCode {
    string operation;
    string operand1;
    string operand2;
    string result;
};

// Function to generate intermediate code for a binary arithmetic expression
vector<IntermediateCode> generateIntermediateCode(string op, string operand1, string operand2, string result) {
    vector<IntermediateCode> code;
    IntermediateCode ic;

    ic.operation = op;
    ic.operand1 = operand1;
    ic.operand2 = operand2;
    ic.result = result;

    code.push_back(ic);

    return code;
}

int main() {
    // Parse the input source code
    string expression = "a + b * c";

    // Traverse the parse tree and generate intermediate code
    vector<IntermediateCode> code;
    code = generateIntermediateCode("multiply", "b", "c", "t1");

    code.push_back(generateIntermediateCode("add", "a", "t1", "t2")[0]);

    // Print the intermediate code
    for (int i = 0; i < code.size(); i++) {
        cout << code[i].result << " = " << code[i].operand1 << " " << code[i].operation << " " << code[i].operand2 << endl;
    }

    return 0;
}
