#include <iostream>
#include <bitset>
#include <vector>
#include <string>
#include <sstream>
#include <windows.h>
#include <fstream>
#include <conio.h>
#include <map>
using namespace std;
char keyboard;
int registor_a, c_flag_text, registor_b, program_counter, output_port, input_portA, input_portB, c_flag, count;
string program_counter_3, inputA, inputB, im_str, registor_a_2, registor_b_2, program_counter_2, output_port_2;

void defolt()
{
    registor_a = 0;
    c_flag_text = 0;
    registor_b = 0;
    program_counter = 0;
    output_port = 0;
    input_portA = 0;
    input_portB = 0;
    c_flag = 0;
    count = 1;
    program_counter_3;
    inputA = "0000";
    inputB = "0000";
    im_str;
    registor_a_2 = "0000";
    registor_b_2 = "0000";
    program_counter_2 = "0000";
    output_port_2 = "0000";
}

void purse_order(const string &op, int im)
{
    switch (stoi(op, nullptr, 2))
    {
    case 0:
        if ((registor_a + im) > 15)
        {
            registor_a = (registor_a + im) - 15;
            c_flag = 1;
        }
        else
        {
            registor_a = registor_a + im;
        }
        program_counter++;
        break;
    case 5:
        if ((registor_b + im) > 15)
        {
            registor_b = (registor_b + im) - 15;
            c_flag = 1;
        }
        else
        {
            registor_b = registor_b + im;
        }
        program_counter++;
        break;
    case 3:
        registor_a = im;
        program_counter++;
        break;
    case 7:
        registor_b = im;
        program_counter++;
        break;
    case 1:
        registor_a = registor_b;
        program_counter++;
        break;
    case 4:
        registor_b = registor_a;
        program_counter++;
        break;
    case 15:
        program_counter = im;
        break;
    case 14:
        if (c_flag == 0)
        {
            program_counter = im;
        }
        else
        {
            program_counter++;
        }
        break;
    case 2:
        registor_a = input_portA;
        program_counter++;
        break;
    case 6:
        registor_b = input_portB;
        program_counter++;
        break;
    case 9:
        output_port = registor_b;
        program_counter++;
        break;
    case 11:
        output_port = im;
        program_counter++;
        break;
    }

    cout << "program counter: " << program_counter_2 << " reg A: " << registor_a_2 << " reg B: " << registor_b_2 << " C flag: " << c_flag_text << " out: " << output_port_2;

    if (c_flag == 1 && count == 1)
    {
        count += 1;
    }
    else if (c_flag == 1 && count == 2)
    {
        count = 1;
        c_flag = 0;
    }
}

int main()
{
    map<string, string> instructions = {
        {"0000", "ADD A, "},
        {"0101", "ADD B, "},
        {"0011", "MOV A, "},
        {"0111", "MOV B, "},
        {"0001", "MOV A, B"},
        {"0100", "MOV B, A"},
        {"1111", "JMP "},
        {"1110", "JNC "},
        {"0010", "IN A "},
        {"0110", "IN B "},
        {"1001", "OUT B "},
        {"1011", "OUT "}};
    do
    {
        defolt();
        cout << "\033[2J\033[1;1H";
        vector<pair<string, string>> ope;
        string open;

        ifstream file("instruction.txt");
        if (file.is_open())
        {
            getline(file, open);
        }
        else
        {
            cout << "Error open file!";
        }
        file.close();

        istringstream iss(open);
        string op, im;
        while (iss >> op >> im)
        {
            ope.emplace_back(op, im);
        }
        for (int i = 0; i < ope.size(); i++)
        {
            program_counter_3 = bitset<4>(i).to_string();
            const auto &[op, im_str] = ope[i];
            if (op == "0010")
            {
                cout << "Input port A: ";
                cin >> inputA;
                input_portA = stoi(inputA, nullptr, 2);
            }
            else if (op == "0110")
            {
                cout << "Input port B: ";
                cin >> inputB;
                input_portB = stoi(inputB, nullptr, 2);
            }
        }

        system("cls");
        do
        {
            system("cls");
            c_flag_text = c_flag;
            registor_a_2 = bitset<4>(registor_a).to_string();
            registor_b_2 = bitset<4>(registor_b).to_string();
            output_port_2 = bitset<4>(output_port).to_string();
            program_counter_2 = bitset<4>(program_counter).to_string();
            cout << "Input port A: " << inputA << "\n";
            cout << "Input port B: " << inputB << "\n\n";
            if (program_counter >= ope.size())
            {
                program_counter = 0;
            }

            for (int i = 0; i < ope.size(); i++)
            {
                program_counter_3 = bitset<4>(i).to_string();
                const auto &[op, im_str] = ope[i];
                if (program_counter == i)
                {
                    cout << "\x1b[32m";
                }

                if (instructions[op] == "IN A ")
                {
                    cout << program_counter_3 << "  " << instructions[op] << inputA << endl;
                }
                else if (instructions[op] == "IN B ")
                {
                    cout << program_counter_3 << "  " << instructions[op] << inputB << endl;
                }
                else if (instructions[op] != "MOV A, B" || instructions[op] != "MOV B, A" || instructions[op] != "OUT B ")
                {
                    cout << program_counter_3 << "  " << instructions[op] << im_str << endl;
                }
                else
                {
                    cout << program_counter_3 << "  " << instructions[op] << endl;
                }
                cout << "\x1b[0m";
            }
            cout << "\n";

            const auto &[op, im_str] = ope[program_counter];
            int im = stoi(im_str, nullptr, 2);
            purse_order(op, im);
            keyboard = getch();

        } while (keyboard == ' ');
    } while (keyboard == 'r');
    return 0;
}