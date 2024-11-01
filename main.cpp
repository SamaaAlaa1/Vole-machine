#include <bits/stdc++.h>

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
    MainUI()  {
        enterFileOrlnstructions = false;
        machine =nullptr;
    }
    bool getFileOrlnstructions(){
        char choice;
        cout << "Enter 'f' to load instructions from a file or 'm' to enter instructions manually: ";
        cin >> choice;
        enterFileOrlnstructions = (choice == 'f' || choice == 'F');
        return enterFileOrlnstructions;
    }

    void disPlayMenu(){
        cout << "*** CPU Simulator ***\n";
        cout << "1. Load Program\n";
        cout << "2. Run Next Step\n";
        cout << "3. Output State\n";
        cout << "4. Exit\n";
    }

    string inputFileName(){
        string filename;
        cout << "Enter the program file_name: ";
        cin >> filename;
        return filename;
    }

    string inputInstruction(){
        string instruction;
        cout << "Enter the instruction: ";
        cin.ignore();
        getline(cin, instruction);
        return instruction;
    }

    char inputChoice(){
        char choice;
        cout << "Enter your choice: ";
        cin >> choice;
        return choice;
    }
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
    string getCell(int address){
        return memory[address];
    }

    void setCell(int address, string val){
        memory[address] = val;
    }
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
    vector<string>reg;
public:
    Register(){
        reg = vector<string>(size, "00");
    }
    string getCell(int address){
        if (address>=0&&address<size){
            return reg[address];
        }
        return "";
    }

    void setCell(int address, string value){
        if (address >= 0 && address < size) {
            reg[address] = value;
        }
    }
};

class ALU {
public:
    string hexToDec(string hex_number){
        string Hex_To_Dec= to_string(stoi(hex_number, nullptr, 16));
        return Hex_To_Dec;
    }

    string decToHex(int decimal_number){
        return format("{:x}", decimal_number);
    }

    bool isVaild(string value){
        for (int i=0;i<value.size();i++){
            if (!isxdigit(i)) {
                return false;
            }
        }
        return true;
    }

    void add(int idx1, int idx2, int idx3, Register &reg){
        int value1 = stoi(reg.getCell(idx1), nullptr, 16);
        int value2 = stoi(reg.getCell(idx2), nullptr, 16);
        int result = value1 + value2;
        reg.setCell(idx3, decToHex(result));
    }
};

class CU {
public:
    void load(int idxReg, int intMem, Register &reg, Memory &mem){
        reg.setCell(idxReg, mem.getCell(intMem));
    }

    void load(int idxReg, int val, Register &reg) {
        std::stringstream stream;
        stream << std::hex << val;
        reg.setCell(idxReg, stream.str());
    }

    void store(int idxReg, int idxMem, Register &reg, Memory &mem){
        mem.setCell(idxMem, reg.getCell(idxReg));
    }

    void move(int idxReg1, int idxReg2, Register &reg){
        reg.setCell(idxReg1, reg.getCell(idxReg2));
    }

    void jump(int idxReg, int idxMem, Register &reg, int &PC){

    }

    void halt();
};

int main() {

    return 0;
}