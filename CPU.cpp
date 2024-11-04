#include "CPU.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <bitset> // For handling binary representation
using namespace std;

// Memory class method implementations

Memory::Memory() {
    for (int i = 0; i < MEMORY_SIZE; ++i) {
        memory[i] = 0;
    }
}

int Memory::get(int address) const {
    if (address >= 0 && address < MEMORY_SIZE) {
        return memory[address];
    }
    return -1; // Error value
}

void Memory::set(int address, int value) {
    if (address >= 0 && address < MEMORY_SIZE) {
        memory[address] = value;
    }
}

void Memory::display() const {
    cout << "Memory:\n";
    for (int i = 0; i < MEMORY_SIZE; i += 16) {
        cout << setw(2) << setfill('0') << hex << i << ":  ";
        for (int j = 0; j < 16; ++j) {
            cout << setw(2) << setfill('0') << memory[i + j] << "  ";
        }
        cout << endl<<endl;
    }
    cout << dec; // Reset to decimal output
}

// CPU class method implementations

CPU::CPU() {
    for (int i = 0; i < NUM_REGISTERS; ++i) {
        registers[i] = 0;
    }
}

int CPU::hexToDecimal(const string& hex) {
    return stoul(hex, nullptr, 16); // Convert string to unsigned integer
}

void CPU::extractInstructionComponents(int instruction, int& opCode, int& registerIndex, int& operand) {
    opCode = (instruction >> 12) & 0xF;          // Extract the operation code (first 4 bits)
    registerIndex = (instruction >> 8) & 0xF;    // Extract the source register index (next 4 bits)
    operand = instruction & 0xFF;                // Extract the operand (last 8 bits)
}

void CPU::displayRegisters() const {
    cout << "Register values:\n";
    for (int i = 0; i < NUM_REGISTERS; i++) {
        cout << "R" << hex << i << ": "
             << setw(2) << setfill('0') << registers[i] << "\n\n";
    }
}

void CPU::displayMemory() const {
    memory.display();
}

void CPU::executeInstruction(string& input) {
    int instruction = hexToDecimal(input);
    int opCode, registerIndex, operand;

    extractInstructionComponents(instruction, opCode, registerIndex, operand);

    switch (opCode) {
        case 1:
            registers[registerIndex] = memory.get(operand);
            break;
        case 2:
            registers[registerIndex] = operand;
            break;
        case 3:
            memory.set(operand, registers[registerIndex]);
            break;
        case 4:
            if ((instruction & 0xFF00) == 0x4000) {
                int srcRegister = (instruction >> 4) & 0xF;
                int destRegister = instruction & 0xF;
                registers[srcRegister] = registers[destRegister];
            }
            break;
        case 5: {
            int dest_Register = (instruction >> 8) & 0xF;
            int reg1 = (instruction >> 4) & 0xF;
            int reg2 = instruction & 0xF;
            registers[dest_Register] = registers[reg1] + registers[reg2];
            break;
        }
        case 12:
            return;
        default:
            cout << "Invalid instruction, try again.\n";
            break;
    }
}
