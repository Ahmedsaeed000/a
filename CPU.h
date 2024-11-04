#ifndef CPU_H
#define CPU_H

#include <string>
using namespace std;

class Memory {
private:
    static const int MEMORY_SIZE = 256;
    int memory[MEMORY_SIZE];

public:
    Memory();
    int get(int address) const;
    void set(int address, int value);
    void display() const;
};

class CPU {
private:
    static const int NUM_REGISTERS = 16;
    int registers[NUM_REGISTERS];
    Memory memory;

public:
    CPU();
    int hexToDecimal(const string& hex);
    void extractInstructionComponents(int instruction, int& opCode, int& registerIndex, int& operand);
    void displayRegisters() const;
    void displayMemory() const;
    void executeInstruction(string& input);
};

#endif // CPU_H
