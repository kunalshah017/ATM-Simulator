#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <random>
#include <fstream>
#include <thread>
#include <chrono>
#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

using namespace std;

void clear_screen()
{
#ifdef __linux__
    cout << "\033[2J\033[1;1H";
#endif
#ifdef _WIN32
    system("cls");
#endif
}

void pause_screen()
{
#ifdef __linux__
    system("read -p 'Press Enter to continue...' var");
#endif
#ifdef _WIN32
    system("pause");
#endif
}

void loadingAnimation(int durationSeconds)
{
    int progressBarWidth = 40;

    std::cout << "Loading: ";
    for (int i = 0; i <= progressBarWidth; ++i)
    {
        std::cout << "\r[";
        for (int j = 0; j < progressBarWidth; ++j)
        {
            if (j <= i)
                std::cout << "=";
            else
                std::cout << " ";
        }
        std::cout << "] " << static_cast<int>((static_cast<float>(i) / progressBarWidth) * 100) << "%";
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(durationSeconds * 1000 / progressBarWidth));
    }
    std::cout << std::endl;
}

class account
{
private:
    string name = "null";
    int balance = 0, withdraw, deposit;
    string pin = "", fpin = "";
    char ch;
    long int random = 9999999, AccountNumber = 1;

public:
    // New Account-------------------------------------------------------------------------
    void CreateAccount()
    {
        ifstream file("data.txt");
        string line;
        bool found = false;

        if (name != "null")
        {
            clear_screen();
            cout << "-----------------------------------" << endl;
            cout << "\nAccount has Already been created" << endl;
            cout << "\n---------------------------------" << endl;
            pause_screen();
        }

        else
        {
            clear_screen();

            cout << "Enter your Full Name :- ";
            getline(cin, name);

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

#ifdef _WIN32
            srand(time(NULL));
            AccountNumber = rand() % random + 1000000;
#else
            srand(time(NULL));
            AccountNumber = rand() % random + 1;
            if (AccountNumber < 1000000)
            {
                srand(time(NULL));
                AccountNumber = rand() % random + 1;
            }

#endif

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
#ifdef _WIN32
                    srand(time(NULL));
                    AccountNumber = rand() % random + 1000000;
#else
                    srand(time(NULL));
                    AccountNumber = rand() % random + 1;

#endif
                }
            } while (found);

            ofstream outfile("data.txt", ios::app);
            outfile << AccountNumber << "^" << name << "%" << pin << "*" << balance << "$" << fpin << endl;
            outfile.close();

            clear_screen();
            cout << "-------------------------------------------------" << endl;
            cout << "***** Account has been created succesfully *****" << endl;
            cout << "-------------------------------------------------" << endl;
            cout << "\n\nPlease Continue to View your Account Details" << endl;

            pause_screen();

            clear_screen();
            cout << "---------------------------------------\n";
            cout << "\nAccount Number :- " << AccountNumber << endl;
            cout << "\nName :- " << name << endl;
            cout << "\nBalance :- " << balance << endl;
            cout << "\n---------------------------------------" << endl;
            pause_screen();
        }
    }

    // Existing Account-------------------------------------------------------------------------

    void ExistingAccount()
    {

        clear_screen();
        cout << "---------------------------------------------------" << endl;
        ifstream file("data.txt");
        string line, balanceline;
        bool found = false, balancefound = false;

        if (!file || !getline(file, line))
        {
            clear_screen();
            cout << "---------------------------------------------------------" << endl;
            cout << "No Account has been created yet First Create one account" << endl;
            cout << "---------------------------------------------------------" << endl;
            pause_screen();
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
                    cout << "---------------------------------------------------" << endl;

                    pause_screen();
                }
                else
                {
                    pin = "";
                    AccountNumber = 0;

                    clear_screen();
                    cout << "------------------------------------" << endl;
                    cout << "Pin does not match please try again" << endl;
                    cout << "------------------------------------" << endl;
                    pause_screen();
                }
            }
            else if (!found)
            {
                AccountNumber = 0;
                cout << "\nAccount does not exist under this Acoount Number" << endl;
                file.close();
                cout << "---------------------------------------------------" << endl;
                pause_screen();
            }
        }
        else if (name != "null")
        {
            clear_screen();
            cout << "-----------------------------" << endl;
            cout << "Already An Account is Opened" << endl;
            cout << "-----------------------------" << endl;
            pause_screen();
        }
    }

    // FORGOT PIN-------------------------------------------------------------------------

    void ForgotPin()
    {
        if (name == "null")
        {
            clear_screen();
            string line;
            ifstream file("data.txt");
            bool found = false;
            cout << "\n--------------------------------------------------------" << endl;

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
                    cout << "\n--------------------------------------------------------" << endl;
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
                    clear_screen();
                    cout << "-------------------------" << endl;
                    cout << "Your Answer is Incorrect" << endl;
                    cout << "-------------------------" << endl;
                    pause_screen();
                }
            }
            else if (!found)
            {
                AccountNumber = 1;
                cout << "\nAccount does not exist under this Account Number" << endl;
                file.close();
                cout << "\n--------------------------------------------------------" << endl;
                pause_screen();
            }
        }
        else if (name != "null")
        {
            clear_screen();
            cout << "-----------------------------" << endl;
            cout << "Already An Account is Opened" << endl;
            cout << "-----------------------------" << endl;
            pause_screen();
        }
    }

    void ChangePin()
    {
        if (name != "null")
        {
            string extpin = "";
            clear_screen();
            cout << "-------------------------------------" << endl;
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
                cout << "\n-------------------------------------" << endl;

                pause_screen();
                extpin = "";
            }
            else
            {
                extpin = "";
                clear_screen();
                cout << "------------------------------------" << endl;
                cout << "Pin does not match please try again" << endl;
                cout << "------------------------------------" << endl;
                pause_screen();
            }
        }
        else
        {
            clear_screen();
            cout << "----------------------------------------" << endl;
            cout << "No Account has been Logged in yet \nFirst login with an account to change pin" << endl;
            cout << "----------------------------------------" << endl;
            pause_screen();
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
            clear_screen();

            cout << "-------------------------------------------------------------" << endl;
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
                    cout << "-------------------------------------------------------------" << endl;
                }
                else
                {
                    tempFile << line << endl;
                }
            }

            inputFile.close();
            tempFile.close();

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
            cout << "------------------------------------------------------------" << endl;
            cout << "No Account has been created yet. First, create one account." << endl;
            cout << "------------------------------------------------------------" << endl;
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
            clear_screen();
            cout << "---------------------------------------------------------" << endl;
            cout << "No Account has been created yet First Create one account" << endl;
            cout << "---------------------------------------------------------" << endl;
            pause_screen();
        }

        else
        {
            clear_screen();
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
                clear_screen();
                cout << "---------------------------------------------------" << endl;
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
                cout << "\n---------------------------------------------------" << endl;
#ifdef _WIN32
                system("pause");
#else
                system("read -p 'Press Enter to continue...' var");
#endif
            }
            if (name != "null" && extpin != pin)
            {
                clear_screen();
                cout << "----------------------------------- " << endl;
                cout << "Pin does not match please try again" << endl;
                cout << "------------------------------------" << endl;
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
        clear_screen();
        cout << "-----------------------------------" << endl;
        cout << "Logging out...\nPlease Wait" << endl;
        loadingAnimation(1);
        cout << "-----------------------------------" << endl;
        clear_screen();
        cout << "-----------------------------------" << endl;
        cout << "Logged out successfully" << endl;
        cout << "-----------------------------------" << endl;
        pause_screen();
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
            clear_screen();
            cout << "-----------------------------------" << endl;
            cout << "Please Login with an account first" << endl;
            cout << "-----------------------------------" << endl;
            pause_screen();
        }
        else
        {

            clear_screen();

            cout << "---------------------------------------\n";
            cout << "\nAccount Number :- " << AccountNumber << endl;
            cout << "\nName :- " << name << endl;
            cout << "\nBalance :- " << balance << endl;
            cout << "\n---------------------------------------" << endl;

            pause_screen();
        }
    }

    void ExportDataFile()
    {
        ifstream inputFile("data.txt");
        if (!inputFile)
        {
            cout << "Data File not Present" << endl;
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

        clear_screen();

        cout << "Exporting Data...\nPlease Wait...";
        loadingAnimation(3);

        clear_screen();

        cout << "-----------------------\n";
        cout << "\nData Exported Successfully" << endl;
        cout << "\n-----------------------" << endl;

        pause_screen();
    }

    void TransferMoney()
    {
        int transferAccountNumber = 0;
        int transferBalance = 0;
        int transferAmount = 0;

        if (AccountNumber == 1 || AccountNumber == 0)
        {
            clear_screen();
            cout << "------------------------------------" << endl;
            cout << "Please Login with an account first" << endl;
            cout << "------------------------------------" << endl;

            pause_screen();
        }

        else
        {
            clear_screen();
            cout << "Enter the account number of the person you want to transfer money to: ";
            cin >> transferAccountNumber;

            if (transferAccountNumber == AccountNumber)
            {
                clear_screen();
                cout << "You cannot transfer money to yourself" << endl;
                pause_screen();
                return;
            }

            if (transferAccountNumber < 1000000)
            {
                clear_screen();
                cout << "Invalid account number" << endl;
                pause_screen();
                return;
            }

            ifstream inputFile("data.txt");
            if (!inputFile)
            {
                cout << "Data File not Present" << endl;
                return;
            }
            string line;
            string transferName = "";
            bool found = false;

            string str_transferAccountNumber = to_string(transferAccountNumber);
            inputFile.seekg(0, ios::beg);
            while (getline(inputFile, line))
            {
                string AccountNumber = line.substr(0, line.find("^"));
                if (AccountNumber == str_transferAccountNumber)
                {
                    transferName = line.substr(line.find("^") + 1, line.find("%") - line.find("^") - 1);
                    transferBalance = stoi(line.substr(line.find("*") + 1, line.find("$") - line.find("*") - 1));
                    found = true;
                    break;
                }
            }

            cout << "Finding Account Number... \nPlease Wait." << endl;
            loadingAnimation(2);

            if (!found)
            {
                clear_screen();
                cout << "Account not found" << endl;
                pause_screen();
                return;
            }
            if (found)
            {
                clear_screen();
                cout << "----------------------------------------------------" << endl;
                cout << "Account Found" << endl;

                cout << "\nAccount Holder Name: " << transferName << endl;
                cout << "Account Number: " << transferAccountNumber << endl;

                cout << "\n----------------------------------------------------" << endl;
                cout << "\nEnter the amount you want to transfer = ";
                cin >> transferAmount;

                if (transferAmount > balance)
                {
                    clear_screen();
                    cout << "----------------------------------------------------" << endl;
                    cout << "You do not have enough balance to transfer" << endl;
                    cout << "----------------------------------------------------" << endl;

                    pause_screen();
                    return;
                }
                else
                {
                    balance = balance - transferAmount;
                    transferBalance = transferBalance + transferAmount;

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
                    string str_transferAccountNumber = to_string(transferAccountNumber);
                    inputFile.seekg(0, ios::beg);
                    while (getline(inputFile, line))
                    {
                        string file_AccountNumber = line.substr(0, line.find("^"));
                        if (file_AccountNumber == str_transferAccountNumber)
                        {
                            tempFile << str_transferAccountNumber << "^" << transferName << "%" << line.substr(line.find("%") + 1, line.find("*") - line.find("%") - 1) << "*" << transferBalance << "$" << line.substr(line.find("$") + 1) << endl;
                        }

                        else
                        {
                            tempFile << line << endl;
                        }
                    }

                    inputFile.close();
                    tempFile.close();

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

                    ifstream inputfile("data.txt");
                    if (!inputfile)
                    {
                        cout << "Error: Unable to open data.txt" << endl;
                        return;
                    }

                    ofstream tempfile("temp.txt");
                    if (!tempfile)
                    {
                        cout << "Error: Unable to open temp.txt" << endl;
                        inputfile.close();
                        return;
                    }

                    inputfile.seekg(0, ios::beg);
                    while (getline(inputfile, line))
                    {
                        string file_AccountNumber = line.substr(0, line.find("^"));

                        if (file_AccountNumber == to_string(AccountNumber))
                        {
                            tempfile << to_string(AccountNumber) << "^" << name << "%" << line.substr(line.find("%") + 1, line.find("*") - line.find("%") - 1) << "*" << balance << "$" << line.substr(line.find("$") + 1) << endl;
                        }

                        else
                        {
                            tempfile << line << endl;
                        }
                    }

                    inputfile.close();
                    tempfile.close();

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

                    cout << "Transferring Money... \nPlease Wait." << endl;
                    loadingAnimation(2);

                    clear_screen();
                    cout << "\n----------------------------------------------------" << endl;
                    cout << "Transfer Successful" << endl;
                    cout << "Your new balance is: " << balance << endl;
                    cout << "----------------------------------------------------" << endl;
                    pause_screen();
                    return;
                }
            }
        }
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
            clear_screen();

            cout << "--------------------------------" << endl;
            cout << " Welcome to Kunal's ATM Banking" << endl;
            cout << "--------------------------------" << endl;

            cout << "\n---------------------------------------------------" << endl;
            cout << "Choose option by pressing option number eg.1,2,3.." << endl;

            cout << "\n1. Export Program Data to Database.csv" << endl;
            cout << "2. Logout" << endl;

            cout << "---------------------------------------------------" << endl;

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
            clear_screen();

            cout << "--------------------------------" << endl;
            cout << " Welcome to Kunal's ATM Banking" << endl;
            cout << "--------------------------------" << endl;

            cout << "\n---------------------------------------------------" << endl;
            cout << "Choose option by pressing option number eg.1,2,3.." << endl;

            cout << "\n1. Open new a Savings Account" << endl;
            cout << "2. Open a Existing Savings Account" << endl;
            cout << "3. View Account Details" << endl;
            cout << "4. Forgot Pin of your Savings Account" << endl;
            cout << "5. Change Pin of your Savings Account" << endl;
            cout << "6. Add Money to Savings Account" << endl;
            cout << "7. Withdraw Money form Savings Account" << endl;
            cout << "8. Transfer Money to Someone" << endl;
            cout << "9. Logout" << endl;
            cout << "---------------------------------------------------" << endl;

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
                obj.TransferMoney();
            }

            if (u == 9)
            {
                obj.Logout();
            }
        } while (u != 9);
    }
};

int main()
{

    class operationmode obj;
    int u;
    string AdminPassword = "admin";

    do
    {
        clear_screen();

        cout << "--------------------------------" << endl;
        cout << " Welcome to Kunal's ATM Banking" << endl;
        cout << "--------------------------------" << endl;
        cout << "\n-------------------------------------------------" << endl;
        cout << "Select Mode by pressing option number eg.1,2,3.." << endl;
        cout << "\n1. User Mode" << endl;
        cout << "2. Admin Mode" << endl;
        cout << "3. Exit" << endl;
        cout << "-------------------------------------------------" << endl;

        cout << "\n>> ";
        cin >> u;
        cin.ignore();

        if (u == 1)
        {
            obj.user();
        }

        if (u == 2)
        {
            clear_screen();

            cout << "\nEnter Admin Password (hint:admin) >> ";

            string pass;
            getline(cin, pass);

            if (pass == AdminPassword)
            {
                obj.admin();
            }
            else
            {
                clear_screen();
                cout << "-----------------------" << endl;
                cout << "Incorrect Password" << endl;
                cout << "-----------------------" << endl;
                pause_screen();
            }
        }

        if (u == 3)
        {

            // BYE BYE MESSAGE
            clear_screen();
            cout << "----------------------------------" << endl;
            cout << "Thank you for trying this program" << endl;
            cout << "----------------------------------" << endl;
            pause_screen();
        }

    } while (u != 3);

    return 0;
}