#ifndef MACHINE_H 
#define MACHINE_H
#include <bits/stdc++.h> 
using namespace std;
int hexToDec(const std::string &hexStr) {
    int decimalValue;
    std::stringstream ss;
    ss << std::hex << hexStr;
    ss >> decimalValue;
    return decimalValue;
}

string decToHex(int decimal_number) {
    std::stringstream stream;
    stream << std::uppercase << std::setw(2) << std::setfill('0') << std::hex << decimal_number;
    return stream.str();
}
class ALU;

class CU;

class Machine;

class Memory;

class Register;

class CPU;

class MainUI;


class MainUI {
private:
    bool enterFileOrlnstructions;
    Machine *machine;
public:
    MainUI() {
      enterFileOrlnstructions = false;
      machine = nullptr;
    }

    bool getFileOrlnstructions() {
      char choice;
      cout << "Enter 'f' to load instructions from a file or 'm' to enter instructions manually: ";
      cin >> choice;
      enterFileOrlnstructions = (choice == 'f' || choice == 'F');
      return enterFileOrlnstructions;
    }

    void disPlayMenu() {
      cout << "*** CPU Simulator ***\n";
      cout << "1. Load Program\n";
      cout << "2. Run Next Step\n";
      cout << "3. Output State\n";
      cout << "4. Exit\n";
    }

    string inputFileName() {
      string filename;
      cout << "Enter the program file_name: ";
      cin >> filename;
      return filename;
    }

    string inputInstruction() {
      string instruction;
      cout << "Enter the instruction: ";
      cin.ignore();
      getline(cin, instruction);
      return instruction;
    }

    char inputChoice() {
      char choice;
      cout << "Enter your choice: ";
      cin >> choice;
      return choice;
    }
};

class Register {
private:
    int size = 16;
    int memory[16];
    vector<string> reg;
public:
    Register() {
      reg = vector<string>(size, "00");
    }

    string getCell(int address) {
      if (address >= 0 && address < size) {
        return reg[address];
      }
      return "";
    }

    void setCell(int address, string value) {
      if (address >= 0 && address < size) {
        reg[address] = value;
      }
    }

    int getSize() { return size; }
};


class ALU {
public:
    bool isVaild(string &value) {
      for (int i = 0; i < value.size(); i++) {
        if (!isxdigit(value[i])) {
          return false;
        }
      }
      return true;
    }

    void add(int idx1, int idx2, int idx3, Register &reg) {
      int value1 = hexToDec(reg.getCell(idx1));
      int value2 = hexToDec(reg.getCell(idx2));
      int result = (value1 + value2)%reg.getSize();
      reg.setCell(idx3, decToHex(result));
    }

    void addFloat(int idx1, int idx2, int idx3, Register &reg){

    }

    void bitwiseAND(int idx1, int idx2, int idx3, Register &reg){

    }
    void bitwiseXOR(int idx1, int idx2, int idx3, Register &reg){

    }
    void bitwiseOR(int idx1, int idx2, int idx3, Register &reg){

    }
    void rotate(int idx, int x,Register &reg){

    }
};

class Memory {
private:
    int size = 256;
    string memory[256];
public:
    Memory() {
        for (int i = 0; i < size; ++i) {
        memory[i] = "00";
     }
    }
    string getCell(int address) {
       if (address >= 0 && address < size) {
       return memory[address];
    }
    throw out_of_range("Invalid memory address access.");
}

    void setCell(int address, string val) {
      if (address >= 0 && address < size) {
        memory[address] = val;
      }
    }
   
};
class CU {
public:
    void load(int idxReg, int intMem, Register &reg, Memory &mem) {
      reg.setCell(idxReg, mem.getCell(intMem));
    }

    void load(int idxReg, string val, Register &reg) {
      reg.setCell(idxReg, val);
    }

    void store(int idxReg, int idxMem, Register &reg, Memory &mem) {
      mem.setCell(idxMem, reg.getCell(idxReg));
    }

    void move(int idxReg1, int idxReg2, Register &reg) {
      reg.setCell(idxReg1, reg.getCell(idxReg2));
    }

    void jump(int idxReg, int idxMem, Register &reg, int &PC) {
        if(reg.getCell(idxReg) == reg.getCell(0)){
            PC = idxMem; 
        }
    }

    void jump_(int idxReg, int idxMem, Register &reg, int &PC){
        if(reg.getCell(idxReg) > reg.getCell(0)){
            PC = idxMem;
        }
    }

    void halt();
};
class CPU {
private:
    int programCounter;
    string instructionRegister;
    Register *aRegister;
    ALU *alu;
    CU *cu;
    Memory *memory;

public:
    CPU(Register *reg, Memory *mem, ALU *al, CU *controlUnit)
            : aRegister(reg), memory(mem), alu(al), cu(controlUnit), programCounter(0) {}

    void runNextStep(Memory &mem,Register &reg) {
      fetch(mem);
      execute(reg, mem);
    }

    void fetch(Memory &mem) {
      instructionRegister = mem.getCell(programCounter++);
      instructionRegister += mem.getCell(programCounter++);
    }

    void execute(Register &reg, Memory &mem) {
    cout << instructionRegister << endl;
    string opcode = instructionRegister.substr(0, 1); 
    string operand1 = instructionRegister.substr(1, 1); 
    string operand2 = instructionRegister.substr(2, 1); 
    string operand3 = instructionRegister.substr(3, 1); 
    cout << "Opcode: " << opcode << ", Operand1: " << operand1 << ", Operand2: " << operand2 << ", Operand3: " << operand3 << endl;
      if(opcode == "1"){
        int ireg = hexToDec(operand1);
        string xy = operand2 + operand2;
        int imem = hexToDec(xy);
        cu->load(ireg,imem,reg,mem);
      }
      else if(opcode == "2"){
        int ireg = hexToDec(operand1);
        string xy = operand2 + operand3;
        cout << "Before: R" << ireg << " = " << reg.getCell(ireg) << endl;
        cu->load(ireg,xy,reg);
        cout << "After: R" << ireg << " = " << reg.getCell(ireg) << endl;
      }
      else if(opcode == "3"){
        int ireg = hexToDec(operand1);
        string xy = operand2 + operand3;
        int imem = hexToDec(xy);
        cu->store(ireg,imem,reg,mem);
      }
      else if(opcode == "4"){
        int ireg1 = hexToDec(operand2);
        int ireg2 = hexToDec(operand3);
        cu->move(ireg1,ireg2,reg);
      }
      else if(opcode == "5"){
        int ireg1 = hexToDec(operand1);
        int ireg2 = hexToDec(operand2);
        int ireg3 = hexToDec(operand3);
        alu->add(ireg1,ireg2,ireg3,reg);
      }
      else if(opcode == "6"){
        int ireg1 = hexToDec(operand1);
        int ireg2 = hexToDec(operand2);
        int ireg3 = hexToDec(operand3);
        alu->addFloat(ireg1,ireg2,ireg3,reg);
      }
      else if(opcode == "7"){
        int ireg1 = hexToDec(operand1);
        int ireg2 = hexToDec(operand2);
        int ireg3 = hexToDec(operand3);
        alu->bitwiseOR(ireg1,ireg2,ireg3,reg);
      }
      else if(opcode == "8"){
        int ireg1 = hexToDec(operand1);
        int ireg2 = hexToDec(operand2);
        int ireg3 = hexToDec(operand3);
        alu->bitwiseAND(ireg1,ireg2,ireg3,reg);
      }
      else if(opcode == "9"){
        int ireg1 = hexToDec(operand1);
        int ireg2 = hexToDec(operand2);
        int ireg3 = hexToDec(operand3);
        alu->bitwiseXOR(ireg1,ireg2,ireg3,reg);
      }
      else if(opcode == "A"){
        int ireg1 = hexToDec(operand1);
        int x = hexToDec(operand3);
        alu->rotate(ireg1,x,reg);
      }
      else if(opcode == "B"){
        int ireg = hexToDec(operand1);
        string xy = operand2 + operand3;
        int imem = hexToDec(xy);
        cu->jump(ireg,imem,reg,programCounter);
      }
      else if(opcode == "C"){
        cout << "Program Halted!" << endl;
        exit(0);
      }
      else if(opcode == "D"){
        int ireg = hexToDec(operand1);
        string xy = operand2 + operand2;
        int imem = hexToDec(xy);
        cu->jump_(ireg,imem,reg,programCounter);
      }
    }

    void outputState() {
      cout << "Program Counter: " << programCounter << endl;
      cout << "Instruction Register: " << instructionRegister << endl;
    }

private:
    void checkRegister(int reg1, int reg2, int reg3) {
      if (reg1 < 0 || reg1 >= aRegister->getSize() ||
          reg2 < 0 || reg2 >= aRegister->getSize() ||
          reg3 < 0 || reg3 >= aRegister->getSize()) {
        throw out_of_range("Invalid register number.");
      }
    }
};


class Machine {
private:
    CPU *processor;
    Memory *memory;
    Register *reg;
    ALU *alu;
    CU *cu;
public:
    Machine() {
        memory = new Memory();
        reg = new Register();
        alu = new ALU();
        cu = new CU();
        processor = new CPU(reg, memory, alu, cu);
    }

    ~Machine() {
        delete processor;
        delete memory;
        delete reg;
        delete alu;
        delete cu;
    }


    void loadProgramFile(const string &filename) {
      ifstream file(filename);
      if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return;
      }
      string line;
      int address = 0;
      while (getline(file, line) && address < 256) {
        for (size_t i = 0; i < line.size() && address < 256; i += 2) {
            string chunk = line.substr(i, 2);
            if (chunk.size() < 2) chunk += "0"; 
            memory->setCell(address++, chunk);
        }
    }
      file.close();
    }

    void outputState() {
    cout << "Machine State:" << endl;
    processor->outputState();
     cout << "Registers:" << endl;
      for (int i = 0; i < reg->getSize(); ++i) {
        cout << "R" << setw(2) << setfill('0') << hex << uppercase << i << ": ";
        cout << reg->getCell(i) << endl;
    }
    cout << "Memory State:" << endl;
    for (int row = 0; row < 16; ++row) {
        for (int col = 0; col < 16; ++col) {
            int address = row * 16 + col;
            cout << " " << setw(2) << setfill('0') << hex << uppercase << address << ": ";
            cout << memory->getCell(address) << "  ";
        }
        cout << endl;
    }
}

    void runNextStep() {
      processor->runNextStep(*memory,*reg);
    }
};
#endif