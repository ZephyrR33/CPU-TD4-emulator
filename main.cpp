#include <iostream>
#include <bitset>
#include <vector>
#include <string>
#include <sstream>
#include <windows.h>
#include <fstream>
using namespace std;

int registor_a = 0;
int registor_b = 0;
int program_counter = 0;
int output_port = 0;
string inputA = "0000";
string inputB = "0000";
int input_portA;
int input_portB;
int c_flag = 0;
int count = 1;

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

    string registor_a_2 = bitset<4>(registor_a).to_string();
    string registor_b_2 = bitset<4>(registor_b).to_string();
    string program_counter_2 = bitset<4>(program_counter - 1).to_string();

    cout << "reg A: " << registor_a_2 << " reg B: " << registor_b_2 << " reg C: " << c_flag << " out: " << output_port;

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
    if (ope.size() != 0)
    {
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
        string comand;
        while (true)
        {
            cout << "Input port A: " << inputA << "\n";
            cout << "Input port B: " << inputB << "\n";
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

                if (op == "0000")
                {
                    comand = "ADD A, ";
                }
                else if (op == "0101")
                {
                    comand = "ADD B, ";
                }
                else if (op == "0011")
                {
                    comand = "MOV A, ";
                }
                else if (op == "0111")
                {
                    comand = "MOV B, ";
                }
                else if (op == "0001")
                {
                    comand = "MOV A, B";
                }
                else if (op == "0100")
                {
                    comand = "MOV B, A";
                }
                else if (op == "1111")
                {
                    comand = "JMP ";
                }
                else if (op == "1110")
                {
                    comand = "JNC ";
                }
                else if (op == "0010")
                {
                    comand = "IN A ";
                }
                else if (op == "0110")
                {
                    comand = "IN B ";
                }
                else if (op == "1001")
                {
                    comand = "OUT B";
                }
                else if (op == "1011")
                {
                    comand = "OUT ";
                }
                if (comand == "IN A ")
                {
                    cout << program_counter_3 << "  " << comand << inputA << endl;
                }
                else if (comand == "IN B ")
                {
                    cout << program_counter_3 << "  " << comand << inputB << endl;
                }
                else if (comand != "MOV A, B" || comand != "MOV B, A" || comand != "OUT B")
                {
                    cout << program_counter_3 << "  " << comand << im_str << endl;
                }
                else
                {
                    cout << program_counter_3 << "  " << comand << endl;
                }
                cout << "\x1b[0m";
            }
            cout << '\n';

            const auto &[op, im_str] = ope[program_counter];
            int im = stoi(im_str, nullptr, 2);
            purse_order(op, im);

            Sleep(1000);
            system("cls");
        }
    }
    else
    {
        cout << "Error in file!";
    }

    return 0;
}
