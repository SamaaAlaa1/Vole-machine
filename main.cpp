#include <iostream>
#include <vector>

using namespace std;

class ALU;

class CU;

class Machine;

class Memory;

class Register;

class CPU;

class MainUI {
private:
    bool enterFileOrlnstructions;
    Machine *machine;
public:
    bool getFileOrlnstructions();

    void disPlayMenu();

    string inputFileName();

    string inputInstruction();

    char inputChoice();
};

class Machine {
private:
    CPU *processor;
    Memory *memory;
public:
    void loadProgramFile();

    void outputState();
};

class Memory {
private:
    int size = 256;
    string memory[256];
public:
    string getCell(int address);

    void setCell(int address, string val);
};

class CPU {
private:
    int programCounter;
    string instructionRegister;
    Register *aRegister;
    ALU *alu;
    CU *cu;
public:
    void runNextStep(Memory &mem);

    void fetch(Memory &mem);

    void decode();

    void execute(Register &reg, Memory &mem, vector<int> vec);
};

class Register {
private:
    int size = 16;
    int memory[16];
public:
    int getCell(int address);

    void setCell(int address, string val);
};

class ALU {
public:
    string hexToDec();

    string decToHex();

    bool isVaild(string value);

    void add(int idx1, int idx2, int idx3, Register &reg);
};

class CU {
public:
    void load(int idxReg, int intMem, Register &reg, Memory &mem);

    void load(int idxReg, int val, Register &reg);

    void store(int idxReg, int idxMem, Register &reg, Memory &mem);

    void move(int idxReg1, int idxReg2, Register &reg);

    void jump(int idxReg, int idxMem, Register &reg, int &PC);

    void halt();
};

int main() {

  return 0;
}