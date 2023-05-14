#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <random>
#include <fstream>
#include <unistd.h>
#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#endif

using namespace std;

class account
{
private:
    string name = "null";
    int balance = 0, withdraw, deposit;
    string pin = "", fpin = "";
    char ch;
    long int random = 9999999, AccountNumber = 1;

public:
    void CreateAccount()
    {
        ifstream file("data.txt");
        string line;
        bool found = false;

        if (name != "null")
        {
#ifdef _WIN32
            system("cls");
#else
            system("clear");
#endif
            cout << "-----------------------" << endl;
            cout << "\nAccount has Already been created" << endl;
            cout << "\n-----------------------" << endl;
#ifdef _WIN32
            system("pause");
#else
            system("read -p 'Press Enter to continue...' var");
#endif
        }

        else
        {
#ifdef _WIN32
            system("cls");
#else
            system("clear");
#endif
            cout << "-----------------------" << endl;

            cout << "\nEnter your Full Name :- ";
            getline(cin, name);

            if (found)
            {
                name = "null";
                pin = "";
                cout << "\n\nAlready an accout has been created under this name" << endl;
                cout << "\n-----------------------" << endl;
#ifdef _WIN32
                system("pause");
#else
                system("read -p 'Press Enter to continue...' var");
#endif
            }

            cout << "\nSet a Pin :- ";

#ifdef _WIN32
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

#else
            cin >> pin;
            cin.ignore();
#endif

            cout << "\n\nSet Forgot Pin Question \nName of your First School ? :- ";
            getline(cin, fpin);

            srand(time(NULL));
            AccountNumber = rand() % random + 1;

            do
            {
                file.seekg(0, ios::beg);
                while (getline(file, line))
                {
                    string tempaccno = line.substr(0, line.find("^"));
                    if (tempaccno == to_string(AccountNumber) && AccountNumber != 0)
                    {
                        found = true;
                        break;
                    }
                }

                if (found)
                {
                    srand(time(NULL));
                    AccountNumber = rand() % random + 1;
                }
            } while (found);

            ofstream outfile("data.txt", ios::app);
            outfile << AccountNumber << "^" << name << "%" << pin << "*" << balance << "$" << fpin << endl;
            outfile.close();

#ifdef _WIN32
            system("cls");
#else
            system("clear");
#endif
            cout << "-----------------------" << endl;
            cout << "\n***** Account has been created succesfully *****" << endl;
            cout << "\n-----------------------" << endl;
            cout << "\n\nPlease Continue to View your Account Details" << endl;

#ifdef _WIN32
            system("pause");
#else
            system("read -p 'Press Enter to continue...' var");
#endif

#ifdef _WIN32
            system("cls");
#else
            system("clear");
#endif
            cout << "-----------------------\n";
            cout << "\nAccount Number :- " << AccountNumber << endl;
            cout << "\nName :- " << name << endl;
            cout << "\nBalance :- " << balance << endl;
            cout << "\n-----------------------" << endl;
#ifdef _WIN32
            system("pause");
#else
            system("read -p 'Press Enter to continue...' var");
#endif
        }
    }

    // Existing Account-------------------------------------------------------------------------

    void ExistingAccount()
    {

#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
        cout << "-----------------------" << endl;
        ifstream file("data.txt");
        string line, balanceline;
        bool found = false, balancefound = false;

        if (!file || !getline(file, line))
        {
#ifdef _WIN32
            system("cls");
#else
            system("clear");
#endif
            cout << "-----------------------" << endl;
            cout << "\nNo Account has been created yet \n First Create one account" << endl;
            cout << "\n-----------------------" << endl;
#ifdef _WIN32
            system("pause");
#else
            system("read -p 'Press Enter to continue...' var");
#endif
        }
        else if (name == "null")
        {

            cout << "\nEnter your Account Number :- ";
            cin >> AccountNumber;
            cin.ignore();
            string str_AccountNumber = to_string(AccountNumber);
            file.seekg(0, ios::beg);

            while (getline(file, line))
            {

                string file_AccountNumber = line.substr(0, line.find("^"));

                if (str_AccountNumber == file_AccountNumber)
                {
                    found = true;
                    break;
                }
            }

            if (found)
            {
                cout << "\nEnter your Account pin :- ";
                string temppin;
                getline(cin, temppin);
                pin = line.substr(line.find("%") + 1, line.find("*") - line.find("%") - 1);

                if (temppin == pin)
                {
                    string tempbalance;
                    tempbalance = line.substr(line.find("*") + 1, line.find("$") - line.find("*") - 1);
                    balance = stoi(tempbalance);
                    name = line.substr(line.find("^") + 1, line.find("%") - line.find("^") - 1);
                    fpin = line.substr(line.find("$") + 1);
                    cout << "\nWelcome " << name << "!" << endl;
                    file.close();
                    cout << "\n-----------------------" << endl;
#ifdef _WIN32
                    system("pause");
#else
                    system("read -p 'Press Enter to continue...' var");
#endif
                }
                else
                {
                    pin = "";
                    AccountNumber = 0;
#ifdef _WIN32
                    system("cls");
#else
                    system("clear");
#endif
                    cout << "-----------------------" << endl;
                    cout << "\nPin does not match please try again" << endl;
                    cout << "\n-----------------------" << endl;
#ifdef _WIN32
                    system("pause");
#else
                    system("read -p 'Press Enter to continue...' var");
#endif
                }
            }
            else if (!found)
            {
                AccountNumber = 0;
                cout << "\nAccount does not exist under this Acoount Number" << endl;
                file.close();
                cout << "\n-----------------------" << endl;
#ifdef _WIN32
                system("pause");
#else
                system("read -p 'Press Enter to continue...' var");
#endif
            }
        }
        else if (name != "null")
        {
#ifdef _WIN32
            system("cls");
#else
            system("clear");
#endif
            cout << "-----------------------" << endl;
            cout << "\nAlready An Account is Opened" << endl;
            cout << "\n-----------------------" << endl;
#ifdef _WIN32
            system("pause");
#else
            system("read -p 'Press Enter to continue...' var");
#endif
        }
    }

    // FORGOT PIN-------------------------------------------------------------------------

    void ForgotPin()
    {
        if (name == "null")
        {
#ifdef _WIN32
            system("cls");
#else
            system("clear");
#endif
            string line;
            ifstream file("data.txt");
            bool found = false;
            cout << "-----------------------" << endl;

            cout << "\nEnter your Account Number :- ";
            cin >> AccountNumber;
            cin.ignore();
            string str_AccountNumber = to_string(AccountNumber);
            file.seekg(0, ios::beg);

            while (getline(file, line))
            {

                string file_AccountNumber = line.substr(0, line.find("^"));

                if (str_AccountNumber == file_AccountNumber)
                {
                    found = true;
                    name = line.substr(line.find("^") + 1, line.find("%") - line.find("^") - 1);
                    break;
                }
            }

            if (found)
            {
                cout << "\nGive Answer to your forgot pin question \nName of your First School ? :- ";
                string tempfpin;
                getline(cin, tempfpin);

                fpin = line.substr(line.find("$") + 1);

                if (tempfpin == fpin)
                {
                    cout << "\nWelcome " << name << "!" << endl;

                    cout << "\nEnter Your New Pin :- ";
                    getline(cin, pin);

                    if (pin == "")
                    {
                        pin = fpin;
                    }

                    ifstream inputFile("data.txt");
                    if (!inputFile)
                    {
                        cout << "Error: Unable to open data.txt" << endl;
                        return;
                    }

                    ofstream tempFile("temp.txt");
                    if (!tempFile)
                    {
                        cout << "Error: Unable to open temp.txt" << endl;
                        inputFile.close();
                        return;
                    }

                    string line;

                    while (getline(inputFile, line))
                    {
                        string accountNumStr = line.substr(0, line.find("^"));
                        int accountNum = stoi(accountNumStr);

                        if (AccountNumber == accountNum)
                        {
                            string accountName = line.substr(line.find("^") + 1, line.find("%") - line.find("^") - 1);
                            string password = line.substr(line.find("%") + 1, line.find("*") - line.find("%") - 1);
                            string balanceStr = line.substr(line.find("*") + 1, line.find("$") - line.find("*") - 1);

                            password = pin;

                            tempFile << AccountNumber << "^" << accountName << "%" << password << "*" << balance << "$" << line.substr(line.find("$") + 1) << endl;
                        }
                        else
                        {
                            tempFile << line << endl;
                        }
                    }

                    inputFile.close();

                    if (remove("data.txt") != 0)
                    {
                        cout << "Error: Unable to delete data.txt" << endl;
                        return;
                    }
                    if (rename("temp.txt", "data.txt") != 0)
                    {
                        cout << "Error: Unable to rename temp.txt" << endl;
                        return;
                    }

                    name = "null";
                    fpin = "";
                    AccountNumber = 1;

                    cout << "\n ***** PIN Changed Succesfully *****" << endl;
                    cout << "\n Now try login into your existing account using new pin" << endl;
                    cout << "\n-----------------------" << endl;
#ifdef _WIN32
                    system("pause");
#else
                    system("read -p 'Press Enter to continue...' var");
#endif
                }
                else
                {
                    fpin = "";
                    name = "null";
                    AccountNumber = 1;
#ifdef _WIN32
                    system("cls");
#else
                    system("clear");
#endif
                    cout << "-----------------------" << endl;
                    cout << "\nYour Answer is Incorrect" << endl;
                    cout << "\n-----------------------" << endl;
#ifdef _WIN32
                    system("pause");
#else
                    system("read -p 'Press Enter to continue...' var");
#endif
                }
            }
            else if (!found)
            {
                AccountNumber = 1;
                cout << "\nAccount does not exist under this Account Number" << endl;
                file.close();
                cout << "\n-----------------------" << endl;
#ifdef _WIN32
                system("pause");
#else
                system("read -p 'Press Enter to continue...' var");
#endif
            }
        }
        else if (name != "null")
        {
#ifdef _WIN32
            system("cls");
#else
            system("clear");
#endif
            cout << "-----------------------" << endl;
            cout << "\nAlready An Account is Opened" << endl;
            cout << "\n-----------------------" << endl;
#ifdef _WIN32
            system("pause");
#else
            system("read -p 'Press Enter to continue...' var");
#endif
        }
    }

    void ChangePin()
    {
        if (name != "null")
        {
            string extpin = "";
#ifdef _WIN32
            system("cls");
#else
            system("clear");
#endif
            cout << "-----------------------" << endl;
            cout << "\nEnter your existing pin :- ";

#ifdef _WIN32
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
#else
            cin >> extpin;
#endif

            if (extpin == pin)
            {

                cout << "\nEnter New Pin :- ";
                pin = "";

#ifdef _WIN32
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
#else
                cin >> pin;
#endif

                if (pin == "")
                {
                    pin = extpin;
                }

                ifstream inputFile("data.txt");
                if (!inputFile)
                {
                    cout << "Error: Unable to open data.txt" << endl;
                    return;
                }

                ofstream tempFile("temp.txt");
                if (!tempFile)
                {
                    cout << "Error: Unable to open temp.txt" << endl;
                    inputFile.close();
                    return;
                }

                string line;

                while (getline(inputFile, line))
                {
                    string accountNumStr = line.substr(0, line.find("^"));
                    int accountNum = stoi(accountNumStr);

                    if (AccountNumber == accountNum)
                    {
                        string accountName = line.substr(line.find("^") + 1, line.find("%") - line.find("^") - 1);
                        string password = line.substr(line.find("%") + 1, line.find("*") - line.find("%") - 1);
                        string balanceStr = line.substr(line.find("*") + 1, line.find("$") - line.find("*") - 1);

                        password = pin;

                        tempFile << AccountNumber << "^" << accountName << "%" << password << "*" << balance << "$" << line.substr(line.find("$") + 1) << endl;
                    }
                    else
                    {
                        tempFile << line << endl;
                    }
                }

                inputFile.close();

                if (remove("data.txt") != 0)
                {
                    cout << "Error: Unable to delete data.txt" << endl;
                    return;
                }
                if (rename("temp.txt", "data.txt") != 0)
                {
                    cout << "Error: Unable to rename temp.txt" << endl;
                    return;
                }

                cout << "\n ***** PIN Changed Succesfully *****" << endl;
                cout << "\n-----------------------" << endl;

#ifdef _WIN32
                system("pause");
#else
                system("read -p 'Press Enter to continue...' var");
#endif
                extpin = "";
            }
            else
            {
                extpin = "";
#ifdef _WIN32
                system("cls");
#else
                system("clear");
#endif
                cout << "-----------------------" << endl;
                cout << "\nPin does not match please try again" << endl;
                cout << "\n-----------------------" << endl;
#ifdef _WIN32
                system("pause");
#else
                system("read -p 'Press Enter to continue...' var");
#endif
            }
        }
        else
        {
#ifdef _WIN32
            system("cls");
#else
            system("clear");
#endif
            cout << "-----------------------" << endl;
            cout << "\nNo Account has been Logged in yet \nFirst login with an account to change pin" << endl;
            cout << "\n-----------------------" << endl;
#ifdef _WIN32
            system("pause");
#else
            system("read -p 'Press Enter to continue...' var");
#endif
        }
    }

    void AddMoney()
    {
        if (name != "null")

        {
            ifstream inputFile("data.txt");
            if (!inputFile)
            {
                cout << "Error: Unable to open data.txt" << endl;
                return;
            }

            ofstream tempFile("temp.txt");
            if (!tempFile)
            {
                cout << "Error: Unable to open temp.txt" << endl;
                inputFile.close();
                return;
            }

            string line;
#ifdef _WIN32
            system("cls");
#else
            system("clear");
#endif

            cout << "-----------------------" << endl;
            cout << "\nHow much money do you want to add: ";
            int deposit;
            cin >> deposit;
            cin.ignore();

            while (getline(inputFile, line))
            {
                string accountNumStr = line.substr(0, line.find("^"));
                int accountNum = stoi(accountNumStr);

                if (AccountNumber == accountNum)
                {
                    string accountName = line.substr(line.find("^") + 1, line.find("%") - line.find("^") - 1);
                    string password = line.substr(line.find("%") + 1, line.find("*") - line.find("%") - 1);
                    string balanceStr = line.substr(line.find("*") + 1, line.find("$") - line.find("*") - 1);
                    balance = stoi(balanceStr);

                    balance += deposit;

                    tempFile << AccountNumber << "^" << accountName << "%" << password << "*" << balance << "$" << line.substr(line.find("$") + 1) << endl;

                    cout << "\nRupees " << deposit << " has been added to your account" << endl;
                    cout << "-----------------------" << endl;
                }
                else
                {
                    tempFile << line << endl;
                }
            }

            inputFile.close();

            if (remove("data.txt") != 0)
            {
                cout << "Error: Unable to delete data.txt" << endl;
                return;
            }
            if (rename("temp.txt", "data.txt") != 0)
            {
                cout << "Error: Unable to rename temp.txt" << endl;
                return;
            }

            // Pause the program
#ifdef _WIN32
            system("pause");
#else
            cout << "Press Enter to continue...";
            cin.ignore();
#endif
        }
        else
        {
            cout << "-----------------------" << endl;
            cout << "\nNo Account has been created yet. First, create one account." << endl;
            cout << "-----------------------" << endl;
#ifdef _WIN32
            system("pause");
#else
            cin.ignore();
#endif
        }
    }

    void WithdrawMoney()
    {
        string extpin = "";

        if (name == "null")
        {
#ifdef _WIN32
            system("cls");
#else
            system("clear");
#endif
            cout << "-----------------------" << endl;
            cout << "\nNo Account has been created yet \n First Create one account" << endl;
            cout << "\n-----------------------" << endl;
#ifdef _WIN32
            system("pause");
#else
            system("read -p 'Press Enter to continue...' var");
#endif
        }

        else
        {
#ifdef _WIN32
            system("cls");
#else
            system("clear");
#endif
            cout << "-----------------------" << endl;
            cout << "\n Enter your pin :- ";

#ifdef _WIN32
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
#else
            cin >> extpin;
#endif

            cout << "\n-----------------------" << endl;

            if (name != "null" && extpin == pin)
            {
#ifdef _WIN32
                system("cls");
#else
                system("clear");
#endif
                cout << "-----------------------" << endl;
                cout << "\nHow much money do you want to withdraw :- ";
                cin >> withdraw;
                cin.ignore();

                if (withdraw <= balance)
                {
                    ifstream inputFile("data.txt");
                    if (!inputFile)
                    {
                        cout << "Error: Unable to open data.txt" << endl;
                        return;
                    }

                    ofstream tempFile("temp.txt");
                    if (!tempFile)
                    {
                        cout << "Error: Unable to open temp.txt" << endl;
                        inputFile.close();
                        return;
                    }

                    string line;

                    while (getline(inputFile, line))
                    {
                        string accountNumStr = line.substr(0, line.find("^"));
                        int accountNum = stoi(accountNumStr);

                        if (AccountNumber == accountNum)
                        {
                            string accountName = line.substr(line.find("^") + 1, line.find("%") - line.find("^") - 1);
                            string password = line.substr(line.find("%") + 1, line.find("*") - line.find("%") - 1);
                            string balanceStr = line.substr(line.find("*") + 1, line.find("$") - line.find("*") - 1);
                            balance = stoi(balanceStr);

                            balance -= withdraw;

                            tempFile << AccountNumber << "^" << accountName << "%" << password << "*" << balance << "$" << line.substr(line.find("$") + 1) << endl;

                            cout << "\nRupees " << withdraw << " has been withdrawn from your account " << endl;
                        }
                        else
                        {
                            tempFile << line << endl;
                        }
                    }

                    inputFile.close();
                    if (remove("data.txt") != 0)
                    {
                        cout << "Error: Unable to delete data.txt" << endl;
                        return;
                    }
                    if (rename("temp.txt", "data.txt") != 0)
                    {
                        cout << "Error: Unable to rename temp.txt" << endl;
                        return;
                    }
                }
                else
                {
                    cout << "\n***** Not Enough money in account ***** \nDo you want to take Loan :)" << endl;
                }
                cout << "\n-----------------------" << endl;
#ifdef _WIN32
                system("pause");
#else
                system("read -p 'Press Enter to continue...' var");
#endif
            }
            if (name != "null" && extpin != pin)
            {
#ifdef _WIN32
                system("cls");
#else
                system("clear");
#endif
                cout << "-----------------------" << endl;
                cout << "\nPin does not match please try again" << endl;
                cout << "\n-----------------------" << endl;
#ifdef _WIN32
                system("pause");
#else
                system("read -p 'Press Enter to continue...' var");
#endif
            }
        }
    }

    void Logout()
    {
        name = "null";
        pin = "";
        balance = 0;
        fpin = "";
        AccountNumber = 1;
    }

    void AccountDetails()
    {
        string extpin = "";

        if (name == "null")
        {
#ifdef _WIN32
            system("cls");
#else
            system("clear");
#endif
            cout << "Please Login with an account first" << endl;

            cout << "\nPress Enter to continue...";
            cin.ignore();
        }
        else
        {

#ifdef _WIN32
            system("cls");
#else
            system("clear");
#endif

            cout << "\n\n-----------------------\n\n";
            cout << "\n\nAccount Number :- " << AccountNumber << endl;
            cout << "\nName :- " << name << endl;
            cout << "\nBalance :- " << balance << endl;
            cout << "\n-----------------------" << endl;

#ifdef _WIN32
            system("pause");
#else
            system("read -p 'Press Enter to continue...' var");
#endif
        }
    }

    void ExportDataFile()
    {
        ifstream inputFile("data.txt");
        if (!inputFile)
        {
            cout << "Error: Unable to open data.txt" << endl;
            return;
        }

        ofstream exportFile("database.csv");
        if (!exportFile)
        {
            cout << "Error: Unable to open data.csv" << endl;
            exportFile.close();
            return;
        }

        string line;

        inputFile.seekg(0, ios::beg);
        exportFile << "Account Number,Name,Pin,Balance,Forgot Pin Question" << endl;
        while (getline(inputFile, line))
        {
            string exportAccountNumber = "", exportname = "", exportpin = "", exportbalance = "", exportfpin = "";
            exportAccountNumber = line.substr(0, line.find("^"));
            exportname = line.substr(line.find("^") + 1, line.find("%") - line.find("^") - 1);
            exportpin = line.substr(line.find("%") + 1, line.find("*") - line.find("%") - 1);
            exportbalance = line.substr(line.find("*") + 1, line.find("$") - line.find("*") - 1);
            exportfpin = line.substr(line.find("$") + 1);

            exportFile << exportAccountNumber << "," << exportname << "," << exportpin << "," << exportbalance << "," << exportfpin << endl;

            exportAccountNumber = "";
            exportname = "";
            exportpin = "";
            exportbalance = "";
            exportfpin = "";
        }

        inputFile.close();
        exportFile.close();

        for (int c = 0; c <= 100; c++)
        {
#ifdef _WIN32
            system("cls");
#else
            system("clear");
#endif
            cout << "Exporting Data File " << c << "%";
            cout.flush();
            usleep(10000);
        }

#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

        cout << "-----------------------\n";
        cout << "\nData Exported Successfully" << endl;
        cout << "\n-----------------------" << endl;

#ifdef _WIN32
        system("pause");
#else
        system("read -p 'Press Enter to continue...' var");
#endif
    }
};

class operationmode : public account
{
public:
    // ADMIN MODE
    void admin()
    {
        int a;
        do
        {
#ifdef _WIN32
            system("cls");
#else
            system("clear");
#endif

            cout << "-----------------------" << endl;
            cout << " Welcome to Kunal's ATM Banking" << endl;
            cout << "-----------------------" << endl;

            cout << "\n-----------------------" << endl;
            cout << "\nChoose option by pressing option number eg.1,2,3.." << endl;

            cout << "\n1. Export Program Data to Database.csv" << endl;
            cout << "2. Logout" << endl;

            cout << "\n-----------------------" << endl;

            cout << "\n>> ";
            cin >> a;

            if (a == 1)
            {
                ExportDataFile();
            }
            else if (a == 2)
            {
                Logout();
            }
        } while (a != 2);
    }

    // USER MODE
    void user()
    {
        int u;
        account obj;

        do
        {
#ifdef _WIN32
            system("cls");
#else
            system("clear");
#endif

            cout << "-----------------------" << endl;
            cout << " Welcome to Kunal's ATM Banking" << endl;
            cout << "-----------------------" << endl;

            cout << "\n-----------------------" << endl;
            cout << "\nChoose option by pressing option number eg.1,2,3.." << endl;

            cout << "\n1. Open new a Savings Account" << endl;
            cout << "2. Open a Existing Savings Account" << endl;
            cout << "3. View Account Details" << endl;
            cout << "4. Forgot Pin of your Savings Account" << endl;
            cout << "5. Change Pin of your Savings Account" << endl;
            cout << "6. Add Money to Savings Account" << endl;
            cout << "7. Withdraw Money form Savings Account" << endl;
            cout << "8. Logout" << endl;
            cout << "\n-----------------------" << endl;

            cout << "\n>> ";
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
                obj.AccountDetails();
            }

            if (u == 4)
            {
                obj.ForgotPin();
            }

            if (u == 5)
            {
                obj.ChangePin();
            }

            if (u == 6)
            {
                obj.AddMoney();
            }

            if (u == 7)
            {
                obj.WithdrawMoney();
            }

            if (u == 8)
            {
                obj.Logout();
            }
        } while (u != 8);
    }
};

int main()
{

    class operationmode obj;
    int u;
    string AdminPassword = "admin";

    do
    {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

        cout << "-----------------------" << endl;
        cout << " Welcome to Kunal's ATM Banking" << endl;
        cout << "-----------------------" << endl;
        cout << "\nSelect Mode by pressing option number eg.1,2,3.." << endl;
        cout << "\n1. User Mode" << endl;
        cout << "2. Admin Mode" << endl;
        cout << "3. Exit" << endl;
        cout << "\n-----------------------" << endl;

        cout << "\n>> ";
        cin >> u;
        cin.ignore();

        if (u == 1)
        {
            obj.user();
        }

        if (u == 2)
        {
#ifdef _WIN32
            system("cls");
#else
            system("clear");
#endif

            cout << "\nEnter Admin Password : ";

            string pass;
            getline(cin, pass);

            if (pass == AdminPassword)
            {
                obj.admin();
            }
            else
            {
#ifdef _WIN32
                system("cls");
#else
                system("clear");
#endif
                cout << "-----------------------" << endl;
                cout << "\nIncorrect Password" << endl;
                cout << "\n-----------------------" << endl;
#ifdef _WIN32
                system("pause");
#else
                system("read -p 'Press Enter to continue...' var");
#endif
            }
        }

        if (u == 3)
        {

// BYE BYE MESSAGE
#ifdef _WIN32
            system("cls");
#else
            system("clear");
#endif
            cout << "-----------------------" << endl;
            cout << "\nThank you for trying this program" << endl;
            cout << "\n-----------------------" << endl;
#ifdef _WIN32
            system("pause");
#else
            system("read -p 'Press Enter to continue...' var");
#endif
        }

    } while (u != 3);

    return 0;
}