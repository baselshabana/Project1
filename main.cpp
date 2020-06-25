/*
 This is just a skeleton. It DOES NOT implement all the requirements.
 It only recognizes the "ADD" and "SUB" instructions and prints
 "Unkown Instruction" for all other instructions!
 
 References:
 (1) The risc-v ISA Manual ver. 2.1 @ https://riscv.org/specifications/
 (2) https://github.com/michaeljclark/riscv-meta/blob/master/meta/opcodes
 */

#include <iostream>
#include <fstream>
#include "stdlib.h"
#include <iomanip>

using namespace std;

unsigned char buffer[8*1024];    // Buffer to hold the machine code

void emitError(string s)
{
    cout << s;
    exit(0);
}


void instDecExec(unsigned int instWord)
{
    unsigned int rd, rs1, rs2, funct3, funct7, opcode;
    unsigned int I_imm, S_imm, B_imm, U_imm, J_imm;
    opcode = instWord & 0x0000007F;
    rd = (instWord >> 7) & 0x0000001F;
    funct3 = (instWord >> 12) & 0x00000007;
    rs1 = (instWord >> 15) & 0x0000001F;
    rs2 = (instWord >> 20) & 0x0000001F;
    
    
    
    
    
    if(opcode == 0x33){
        funct7 = (instWord >> 25) & 0x0000007F;
        switch(funct3){
            case 0: if(funct7 == 32) {
                cout << "\tSUB\tx" << dec << rd << ", x" << rs1 << ", x" << rs2 << "\n";
            } else {
                cout << "\tADD\tx" << dec << rd << ", x" << rs1 << ", x" << rs2 << "\n";
                
            }
                break;
                
                case 1: cout << "\tSLL\tx" << dec << rd << ", x" << rs1 << ", x" << rs2 << "\n";
                break;
                case 2: cout << "\tSLT\tx" << dec << rd << ", x" << rs1 << ", x" << rs2 << "\n";
                break;
                case 3:cout << "\tSLTU\tx" << dec << rd << ", x" << rs1 << ", x" << rs2 << "\n";
                break;
                case 4:cout << "\tXOR\tx" << dec << rd << ", x" << rs1 << ", x" << rs2 << "\n";
                break;
                case 5:  if(funct7 == 32) {
                    cout << "\tSRA\tx" << dec << rd << ", x" << rs1 << ", x" << rs2 << "\n";
                } else {
                    cout << "\tSRL\tx" << dec << rd << ", x" << rs1 << ", x" << rs2 << "\n";
                    
                }
                break;
                case 6:cout << "\tOR\tx" << dec << rd << ", x" << rs1 << ", x" << rs2 << "\n";
                break;
                case 7:cout << "\tAND\tx" << dec << rd << ", x" << rs1 << ", x" << rs2 << "\n";
                break;
            default: cout << "\tUnkown R Instruction \n";
                break;
        }
    } else      // R Instructions
    if(opcode == 0x3){
        I_imm = (instWord >> 20) & 0x00000FFF;        //rs2=immediate value
        switch (funct3) {
            case 0:cout << "\tLB\tx" << dec << rd << "," << I_imm << "(x" << rs1 << ")\n";
                break;
            case 1:cout << "\tLH\tx" << dec << rd << "," << I_imm << "(x" << rs1 << ")\n";
                break;
            case 2:cout << "\tLW\tx" << dec << rd << "," << I_imm << "(x" << rs1 << ")\n";
                break;
            case 4:cout << "\tLBU\tx" << dec << rd << "," << I_imm << "(x" << rs1 << ")\n";
                break;
            case 5:cout << "\tLHU\tx" << dec << rd << "," << I_imm << "(x" << rs1 << ")\n";
                break;
            default:cout << "\tUnkown I Instruction \n";
                break;
        }
    } else      // I Instructions
    if(opcode == 0x13){
    I_imm = (instWord >> 20) & 0x00000FFF;
    switch (funct3) {
        case 0: cout<< "\tADDI\tx" << dec << rd << ", x" << rs1 << ", " << I_imm << "\n";
            break;
        case 1: cout<< "\tSLLI\tx" << dec << rd << ", x" << rs1 << ", " << I_imm << "\n";
            break;
        case 2: cout<< "\tSLTI\tx" << dec << rd << ", x" << rs1 << ", " << I_imm << "\n";
            break;
        case 3: cout<< "\tSLTIU\tx" << dec << rd << ", x" << rs1 << ", " << I_imm << "\n";
            break;
        case 4: cout<< "\tXORI\tx" << dec << rd << ", x" << rs1 << ", " << I_imm << "\n";
            break;
        case 5: cout<< "\tSRLI\tx" << dec << rd << ", x" << rs1 << ", " << I_imm << "\n";
            break;
        case 6: cout<< "\tORI\tx" << dec << rd << ", x" << rs1 << ", " << I_imm << "\n";
            break;
        case 7: cout<< "\tANDI\tx" << dec << rd << ", x" << rs1 << ", " << I_imm << "\n";
            break;
        default: cout << "\tUnkown I Instruction \n";
            break;
    }
} else      // I instructions
    if(opcode == 0x37){
        U_imm = (instWord >> 12) & 0x000FFFFF;
        cout << "\tLUI\tx" << dec << rd << ", 0x" << hex << U_imm << "\n";
        
    } else      // LUI instruction
    if(opcode == 0x17){
        U_imm = (instWord >> 12) & 0x000FFFFF;
        cout << "\tAUIPC\tx" << dec << rd << ", " << U_imm << "\n";
        } else       // AUIPC instruction//
    if(opcode == 0x6F){
        J_imm = (instWord >> 31) & 0x00000001;
        J_imm= (J_imm << 8) | ((instWord >> 12)& 0x000000FF);
        J_imm= (J_imm << 1) | ((instWord >> 20)& 0x00000001);
        J_imm= (J_imm << 10) | ((instWord >> 21)& 0x000003FF);
        
        cout << "\tJAL\tx" << dec << rd << ", 0x" << hex << J_imm << "\n";
            } else      // JAL instruction**
    if(opcode == 0x67){
        J_imm = (instWord >> 20) & 0x00000FFF;
        cout << "\tJALR\tx" << dec << rd << ", x" << rs1 << ", " << J_imm << "\n";
    } else      // JALR instruction
    if(opcode == 0x23){                // S Instructions
        S_imm = (instWord >> 25) & 0x0000007F;
        S_imm = (S_imm << 5) |( (instWord >> 7) & 0x0000001F ) ;
        switch(funct3){
                case 0: cout << dec << "\tSB\tx" << rs2 << ", " << S_imm << "(x" << rs1 << ")\n";
                    break;
                case 1: cout << dec << "\tSH\tx" << rs2 << ", " << S_imm << "(x" << rs1 << ")\n";
                    break;
                case 2: cout << dec << "\tSW\tx" << rs2 << ", " << S_imm << "(x" << rs1 << ")\n";
                    break;
            }
        
    } else      // S instructions
    if(opcode == 0x63){
            B_imm = (instWord >> 7) & 0x00000001;
            B_imm |= (instWord >> 8) & 0x0000000f;
            B_imm |= (instWord >> 25) & 0x0000003f;
            B_imm |= (instWord >> 31) & 0x00000001;
            
            switch(funct3){
                case 0: cout << dec << "\tBEQ\tx" << rs1 << ", x" << rs2 << ", " << B_imm << "\n";
                    break;
                case 1: cout << dec << "\tBNE\tx" << rs1 << ", x" << rs2 << ", " << B_imm << "\n";
                    break;
                case 4: cout << dec << "\tBLT\tx" << rs1 << ", x" << rs2 << ", " << B_imm << "\n";
                    break;
                case 5: cout<< dec  << "\tBGE\tx" << rs1 << ", x" << rs2 << ", " << B_imm << "\n";
                    break;
                case 6: cout << dec << "\tBLTU\tx" << rs1 << ", x" << rs2 << ", " << B_imm << "\n";
                    break;
                case 7: cout << dec << "\tBGEU\tx" << rs1 << ", x" << rs2 << ", " << B_imm << "\n";
                    break;
            }
        } else      // B instructions**
    if(opcode == 0x73){
        cout << "\tecall\n";
            } else      // ecall

    {cout << "\tUnkown Instruction\n";}
}



int main(int argc, char *argv[]){
    
    unsigned int instWord=0;
    ifstream inFile;
    ofstream outFile;
    unsigned int pc = 0;
    
    if(argc<1) emitError("use: disasm <machine_code_file_name>\n");
    
    inFile.open(argv[1], ios::in | ios::binary | ios::ate);
    
    if(inFile.is_open())
    {
        long fsize = inFile.tellg();
        
        inFile.seekg (0, inFile.beg);
        if(!inFile.read((char *)buffer, fsize)) emitError("Cannot read from input file\n");
        
        while(true){
            if(buffer[pc]== '\0') break;
            instWord =     (unsigned char)buffer[pc] |
            (((unsigned char)buffer[pc+1])<<8) |
            (((unsigned char)buffer[pc+2])<<16) |
            (((unsigned char)buffer[pc+3])<<24);
            pc += 4;
            instDecExec(instWord);
        }
        
        
    } else emitError("Cannot access input file\n");
}

