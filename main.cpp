#include <iostream>
#include <string>
#include <cstring>
#include <conio.h>
#include <fstream>

using namespace std;

class account
{
private:
    string name = "null";
    int balance = 0, withdraw, deposit;
    string pin = "";
    char ch;

public:
    void CreateAccount()
    {
        ifstream file("data.txt");
        string line;
        bool found = false;

        if (name != "null")
        {
            system("cls");
            cout << "-----------------------" << endl;
            cout << "\nAccount has Already been created" << endl;
            cout << "\n-----------------------" << endl;
            system("pause");
        }

        else
        {
            system("cls");
            cout << "-----------------------" << endl;

            cout << "\nEnter your Full Name :- ";
            getline(cin, name);

            file.seekg(0, ios::beg);

            while (getline(file, line))
            {

                string file_name = line.substr(0, line.find("%"));

                if (name == file_name)
                {
                    found = true;
                    break;
                }
            }

            if (found)
            {
                name = "null";
                pin = "";
                cout << "\n\nAlready an accout has been created under this name" << endl;
                cout << "\n-----------------------" << endl;
                system("pause");
            }
            else
            {
                cout << "\nSet a Pin :- ";
                while ((ch = getch()) != '\r')
                {
                    if (ch == '\b')
                    {
                        if (pin.length() > 0)
                        {
                            pin.pop_back();
                            cout << "\b \b";
                        }
                    }
                    else
                    {
                        pin.push_back(ch);
                        cout << "*";
                    }
                }

                ofstream outfile("data.txt", ios::app);
                outfile << name << "%" << pin << "*" << balance << endl;
                outfile.close();

                cout << "\n\n***** Account has been created succesfully *****" << endl;
                cout << "\n-----------------------" << endl;
                system("pause");
            }
        }
    }

    void ExistingAccount()
    {

        system("cls");
        cout << "-----------------------" << endl;
        ifstream file("data.txt");
        string line, balanceline;
        bool found = false, balancefound = false;

        if (!file || !getline(file, line))
        {
            system("cls");
            cout << "-----------------------" << endl;
            cout << "\nNo Account has been created yet \n First Create one account" << endl;
            cout << "\n-----------------------" << endl;
            system("pause");
        }
        else if (name == "null")
        {

            cout << "\nEnter your full name :- ";
            getline(cin, name);

            cout << "\nEnter your Account pin :- ";
            string temppin;
            getline(cin, temppin);

            file.seekg(0, ios::beg);

            while (getline(file, line))
            {

                string file_name = line.substr(0, line.find("%"));

                if (name == file_name)
                {
                    found = true;
                    break;
                }
            }

            file.seekg(0, ios::beg);

            while (getline(file, balanceline))
            {

                string file_name = line.substr(0, line.find("%"));

                if (name == file_name)
                {
                    balancefound = true;
                    break;
                }
            }

            if (found && balancefound)
            {
                pin = line.substr(line.find("%") + 1, line.find("*") - line.find("%") - 1);
                if (temppin == pin)
                {
                    pin = line.substr(line.find("%") + 1, line.find("*") - line.find("%") - 1);
                    string tempbalance;
                    tempbalance = line.substr(line.find("*") + 1);

                    balance = stoi(tempbalance);

                    cout << "\nWelcome " << name << "!" << endl;
                    file.close();
                    cout << "\n-----------------------" << endl;
                    system("pause");
                }
                else
                {
                    pin = "";
                    name = "null";
                    system("cls");
                    cout << "-----------------------" << endl;
                    cout << "\nPin does not match please try again" << endl;
                    cout << "\n-----------------------" << endl;
                    system("pause");
                }
            }
            else if (!found || !balancefound)
            {
                name = "null";
                cout << "\nAccount does not exist under this name" << endl;
                file.close();
                cout << "\n-----------------------" << endl;
                system("pause");
            }
        }
        else if (name != "null")
        {
            system("cls");
            cout << "-----------------------" << endl;
            cout << "\nAlready An Account is Opened" << endl;
            cout << "\n-----------------------" << endl;
            system("pause");
        }
    }

    void ChangePin()
    {
        if (name != "null")
        {
            string extpin = "";
            system("cls");
            cout << "-----------------------" << endl;
            cout << "\nEnter your existing pin :- ";
            while ((ch = getch()) != '\r')
            {
                if (ch == '\b')
                {
                    if (extpin.length() > 0)
                    {
                        extpin.pop_back();
                        cout << "\b \b";
                    }
                }
                else
                {
                    extpin.push_back(ch);
                    cout << "*";
                }
            }

            if (extpin == pin)
            {
                ifstream file("data.txt");
                string line;

                cout << "\nEnter New Pin :- ";
                pin = "";
                while ((ch = getch()) != '\r')
                {
                    if (ch == '\b')
                    {
                        if (pin.length() > 0)
                        {
                            pin.pop_back();
                            cout << "\b \b";
                        }
                    }
                    else
                    {
                        pin.push_back(ch);
                        cout << "*";
                    }
                }

                // ofstream outfile("temp.txt");
                // outfile << line.substr(0, line.find("%")) << "%" << pin << endl;

                // while (getline(file, line))
                // {
                //     if (name == line.substr(0, line.find("%")))
                //     {
                //         outfile << line.substr(0, line.find("%")) << "%" << pin << endl;
                //     }
                //     else
                //     {
                //         outfile << line << endl;
                //     }
                // }

                ofstream outfile("temp.txt");
                while (getline(file, line))
                {
                    if (name == line.substr(0, line.find("%")))
                    {
                        outfile << name << "%" << pin << "*" << balance << endl;
                    }
                    else
                    {
                        outfile << line << endl;
                    }
                }

                file.close();
                outfile.close();

                // delete the original file and rename the temp file
                remove("data.txt");
                rename("temp.txt", "data.txt");
            }
            else
            {
                system("cls");
                cout << "-----------------------" << endl;
                cout << "\nPin does not match please try again" << endl;
                cout << "\n-----------------------" << endl;
                system("pause");
            }
        }
        else
        {
            system("cls");
            cout << "-----------------------" << endl;
            cout << "\nNo Account has been created yet \n First Create one account" << endl;
            cout << "\n-----------------------" << endl;
            system("pause");
        }
    }

    void PrintBalance()
    {
        if (name != "null")
        {
            system("cls");
            cout << "-----------------------" << endl;
            cout << "\nAccount Holder Name :- " << name << endl;
            cout << "Your Savings Account Balance is :- " << balance << " Rupees " << endl;
            cout << "\n-----------------------" << endl;
            system("pause");
        }
        else
        {
            system("cls");
            cout << "-----------------------" << endl;
            cout << "\nNo Account has been created yet \n First Create one account" << endl;
            cout << "\n-----------------------" << endl;
            system("pause");
        }
    }

    void AddMoney()
    {
        if (name != "null")
        {
            string line;
            ifstream file("data.txt");

            system("cls");
            cout << "-----------------------" << endl;
            cout << "\nHow much money do you want to add :- ";
            cin >> deposit;
            cin.ignore();
            balance = balance + deposit;

            ofstream outfile("temp.txt");
            while (getline(file, line))
            {
                if (name == line.substr(0, line.find("%")))
                {
                    outfile << name << "%" << pin << "*" << balance << endl;
                }
                else
                {
                    outfile << line << endl;
                }
            }

            file.close();
            outfile.close();

            // delete the original file and rename the temp file
            remove("data.txt");
            rename("temp.txt", "data.txt");

            cout << "\nRupees " << deposit << " has been added to your account " << endl;
            cout << "\n-----------------------" << endl;
            system("pause");
        }
        else
        {
            system("cls");
            cout << "-----------------------" << endl;
            cout << "\nNo Account has been created yet \n First Create one account" << endl;
            cout << "\n-----------------------" << endl;
            system("pause");
        }
    }

    void WithdrawMoney()
    {
        string extpin = "";

        if (name == "null")
        {
            system("cls");
            cout << "-----------------------" << endl;
            cout << "\nNo Account has been created yet \n First Create one account" << endl;
            cout << "\n-----------------------" << endl;
            system("pause");
        }

        else
        {
            system("cls");
            cout << "-----------------------" << endl;
            cout << "\n Enter your pin :- ";
            while ((ch = getch()) != '\r')
            {
                if (ch == '\b')
                {
                    if (extpin.length() > 0)
                    {
                        extpin.pop_back();
                        cout << "\b \b";
                    }
                }
                else
                {
                    extpin.push_back(ch);
                    cout << "*";
                }
            }
            cout << "\n-----------------------" << endl;

            if (name != "null" && extpin == pin)
            {
                system("cls");
                cout << "-----------------------" << endl;
                cout << "\nHow much money do you want to withdraw :- ";
                cin >> withdraw;
                cin.ignore();

                if (withdraw <= balance)
                {
                    string line;
                    ifstream file("data.txt");

                    balance = balance - withdraw;

                    ofstream outfile("temp.txt");
                    while (getline(file, line))
                    {
                        if (name == line.substr(0, line.find("%")))
                        {
                            outfile << name << "%" << pin << "*" << balance << endl;
                        }
                        else
                        {
                            outfile << line << endl;
                        }
                    }

                    file.close();
                    outfile.close();

                    // delete the original file and rename the temp file
                    remove("data.txt");
                    rename("temp.txt", "data.txt");

                    cout << "\nRupees " << withdraw << " has been withdrawn from your account " << endl;
                }
                else
                {
                    cout << "\n***** Not Enough money in account ***** \nDo you want to take Loan :)" << endl;
                }
                cout << "\n-----------------------" << endl;
                system("pause");
            }
            if (name != "null" && extpin != pin)
            {
                system("cls");
                cout << "-----------------------" << endl;
                cout << "\nPin does not match please try again" << endl;
                cout << "\n-----------------------" << endl;
                system("pause");
            }
        }
    }
};

int main()
{
    int u;
    account obj;

    do
    {
        system("cls");

        cout << "-----------------------" << endl;
        cout << " Welcome to Kunal's ATM Banking" << endl;
        cout << "-----------------------" << endl;

        cout << "\n-----------------------" << endl;
        cout << "\nChoose option by pressing option number eg.1,2,3.." << endl;

        cout << "1.Open new a Savings Account" << endl;
        cout << "2.Open a Existing Savings Account" << endl;
        cout << "3.Change Pin of your Savings Account" << endl;
        cout << "4.Show Balance in Savings Account" << endl;
        cout << "5.Add Money to Savings Account" << endl;
        cout << "6.Withdraw Money form Savings Account" << endl;

        cout << "7.Logout & Exit" << endl;
        cout << "\n-----------------------" << endl;

        cout << "\n>>";
        cin >> u;
        cin.ignore();

        if (u == 1)
        {
            obj.CreateAccount();
        }

        if (u == 2)
        {
            obj.ExistingAccount();
        }

        if (u == 3)
        {
            obj.ChangePin();
        }

        if (u == 4)
        {
            obj.PrintBalance();
        }

        if (u == 5)
        {
            obj.AddMoney();
        }

        if (u == 6)
        {
            obj.WithdrawMoney();
        }

    } while (u != 7);

    system("cls");
    cout << "-----------------------" << endl;
    cout << "\nThank you for trying this program" << endl;
    cout << "\n-----------------------" << endl;
    system("pause");
    return 0;
}
