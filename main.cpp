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
int registor_a = 0, registor_b = 0, program_counter = 0, output_port = 0, input_portA = 0, input_portB = 0, c_flag = 0, count = 1;
string inputA = "0000", inputB = "0000", registor_a_2 = "0000", registor_b_2 = "0000", program_counter_2 = "0000", output_port_2 = "0000";

void purse_order(const string &op, int im)
{
    if (op == "0000")
    {
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
    }
    else if (op == "0101")
    {
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
    }
    else if (op == "0011")
    {
        registor_a = im;
        program_counter++;
    }
    else if (op == "0111")
    {
        registor_b = im;
        program_counter++;
    }
    else if (op == "0001")
    {
        registor_a = registor_b;
        program_counter++;
    }
    else if (op == "0100")
    {
        registor_b = registor_a;
        program_counter++;
    }
    else if (op == "1111")
    {
        program_counter = im;
    }
    else if (op == "1110")
    {
        if (c_flag == 0)
        {
            program_counter = im;
        }
        else
        {
            program_counter++;
        }
    }
    else if (op == "0010")
    {
        registor_a = input_portA;
        program_counter++;
    }
    else if (op == "0110")
    {
        registor_b = input_portB;
        program_counter++;
    }
    else if (op == "1001")
    {
        output_port = registor_b;
        program_counter++;
    }
    else if (op == "1011")
    {
        output_port = im;
        program_counter++;
    }

    cout << "program counter: " << program_counter_2 << " reg A: " << registor_a_2 << " reg B: " << registor_b_2 << " C flag: " << c_flag << " out: " << output_port_2;

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
    do
    {
        map<string, string> instructions;
        instructions["0000"] = "ADD A, ";
        instructions["0101"] = "ADD B, ";
        instructions["0011"] = "MOV A, ";
        instructions["0111"] = "MOV B, ";
        instructions["0001"] = "MOV A, B";
        instructions["0100"] = "MOV B, A";
        instructions["1111"] = "JMP ";
        instructions["1110"] = "JNC ";
        instructions["0010"] = "IN A ";
        instructions["0110"] = "IN B ";
        instructions["1001"] = "OUT B ";
        instructions["1011"] = "OUT ";
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
            string program_counter_3 = bitset<4>(i).to_string();
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
                string program_counter_3 = bitset<4>(i).to_string();
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
    } while (keyboard == '\r');
}