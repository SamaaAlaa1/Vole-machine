#include <bits/stdc++.h>
#include "Machine.h"
using namespace std;

void app() {
    Machine machine;
    MainUI ui;
    while (true) {
        ui.disPlayMenu();
        char choice = ui.inputChoice();

        
        switch (choice) {
            case '1': 
                if (ui.getFileOrlnstructions()) {
                    string filename = ui.inputFileName();
                    machine.loadProgramFile(filename);
                    machine.outputState();
                }
                else {
                    string instruction = ui.inputInstruction();
                    machine.loadProgram(instruction);
                }
                break;
            case '2':  
                cout << "Running Next Step:" << endl;
                machine.runNextStep();
                break;
            case '3':  
                cout << "Outputting Machine State:" << endl;
                machine.outputState();
                break;
            case '4':  
                cout << "Exiting program." << endl;
                return;
            default:
                cout << "Invalid choice, please try again." << endl;
        }
    }
}

int main() {
  app();
  return 0;
}
