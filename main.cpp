#include "CPU.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    CPU cpu;
    string input;
    string filename;

    cout << "Enter the filename (e.g., instructions.txt): ";
    cin >> filename;

    ifstream inputFile(filename);
    if (!inputFile) {
        cerr << "Error opening file.\n";
        return 1;
    }

    while (getline(inputFile, input)) {
        for (auto& c : input) c = toupper(c);

        if (input == "C000") {
            break;
        }

        if (input.length() != 4) {
            cout << "Invalid input. Please enter a 4-digit hexa value.\n";
            continue;
        }

        cpu.executeInstruction(input);
    }

    inputFile.close();

    cpu.displayRegisters();
    cpu.displayMemory(); // Display memory after program execution
    return 0;
}
