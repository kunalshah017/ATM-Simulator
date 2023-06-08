#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <functional>
#include <cstdlib>
#include <ctime>
#include <random>
#include <fstream>
#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

using namespace std;

void clear_screen() {
#ifdef __linux__
    cout << "\033[2J\033[1;1H" << flush;
#endif
#ifdef _WIN32
    system("cls");
#endif
}

void print_pause() {
    cout << "Press Enter to continue..." << endl;
    cin.get();
}

void print_message_with_bars(std::string message) {
    std::string bars = std::string(message.length() + 2, '-'); // + 2 for the extra bit on the side
    std::cout << bars << "\n " << message << "\n" << bars;
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
            print_message_with_bars("Account has already been created");
            print_pause();
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
            print_message_with_bars("***** Account has been created succesfully *****");
            cout << "\n\nPlease Continue to View your Account Details" << endl;

            print_pause();

            clear_screen();
            cout << "---------------------------------------\n";
            cout << "\nAccount Number :- " << AccountNumber << endl;
            cout << "\nName :- " << name << endl;
            cout << "\nBalance :- " << balance << endl;
            cout << "\n---------------------------------------" << endl;
            print_pause();
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
            print_message_with_bars("No account has been created yet; first create an account");
            print_pause();
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
                    print_pause();
                }
                else
                {
                    pin = "";
                    AccountNumber = 0;

                    clear_screen();
                    print_message_with_bars("PIN does not match, please try again");
                    print_pause();
                }
            }
            else if (!found)
            {
                AccountNumber = 0;
                cout << "\nAccount does not exist under this Acoount Number" << endl;
                file.close();
                cout << "---------------------------------------------------" << endl;
                print_pause();
            }
        }
        else if (name != "null")
        {
            clear_screen();
            print_message_with_bars("An account is already open");
            print_pause();
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
                    print_pause();
                }
                else
                {
                    fpin = "";
                    name = "null";
                    AccountNumber = 1;
                    clear_screen();
                    print_message_with_bars("Your answer is incorrect");
                    print_pause();
                }
            }
            else if (!found)
            {
                AccountNumber = 1;
                cout << "\nAccount does not exist under this Account Number" << endl;
                file.close();
                cout << "\n--------------------------------------------------------" << endl;
                print_pause();
            }
        }
        else if (name != "null")
        {
            clear_screen();
            print_message_with_bars("An account is already open");
            print_pause();
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

                print_pause();
                extpin = "";
            }
            else
            {
                extpin = "";
                clear_screen();
                
                print_pause();
            }
        }
        else
        {
            clear_screen();
            print_message_with_bars("No account has been logged into yet \nFirst login with an account to change its pin");
            print_pause();
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
            print_pause();
        }
        else
        {
            print_message_with_bars("No account has been created yet. First, create an account.");
            print_pause();
        }
    }

    void WithdrawMoney()
    {
        string extpin = "";

        if (name == "null")
        {
            clear_screen();
            print_message_with_bars("No account has been created yet. First, create an account.");
            print_pause();
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
                print_pause();
            }
            if (name != "null" && extpin != pin)
            {
                clear_screen();
                print_message_with_bars("PIN does not match, please try again");
                print_pause();
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
            clear_screen();
            print_message_with_bars("Please login with an account first");
            print_pause();
        }
        else
        {

            clear_screen();

            cout << "---------------------------------------\n";
            cout << "\nAccount Number :- " << AccountNumber << endl;
            cout << "\nName :- " << name << endl;
            cout << "\nBalance :- " << balance << endl;
            cout << "\n---------------------------------------" << endl;

            print_pause();
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

        for (int c = 0; c <= 100; c++)
        {
            clear_screen();
            cout << "--------------------------------\n";
            cout << "Exporting Data File " << c << "%";
            cout << "\nPlease Wait...";
            cout << "\n--------------------------------\n";

#ifdef _WIN32
            Sleep(25);
#else
            usleep(10000);
#endif
        }

        clear_screen();

        print_message_with_bars("Data exported successfully!");

        print_pause();
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

            print_message_with_bars("Welcome to Kunal's ATM Banking");

            cout << "\n\n---------------------------------------------------" << endl;
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

            print_message_with_bars("Welcome to Kunal's ATM Banking");

            cout << "\n---------------------------------------------------" << endl;
            cout << "Choose option by pressing option number eg.1,2,3.." << endl;

            cout << "\n1. Open new a Savings Account" << endl;
            cout << "2. Open a Existing Savings Account" << endl;
            cout << "3. View Account Details" << endl;
            cout << "4. Forgot Pin of your Savings Account" << endl;
            cout << "5. Change Pin of your Savings Account" << endl;
            cout << "6. Add Money to Savings Account" << endl;
            cout << "7. Withdraw Money form Savings Account" << endl;
            cout << "8. Logout" << endl;
            cout << "---------------------------------------------------" << endl;

            cout << "\n>> ";
            cin >> u;
            cin.ignore();

            std::function<void()> methods[] = {
                nullptr,
                [&]() { obj.CreateAccount(); },
                [&]() { obj.ExistingAccount(); },
                [&]() { obj.AccountDetails(); },
                [&]() { obj.ForgotPin(); },
                [&]() { obj.ChangePin(); },
                [&]() { obj.AddMoney(); },
                [&]() { obj.WithdrawMoney(); },
                [&]() { obj.Logout(); }
            };

            if (u >= 1 && u <= 8) {
                methods[u]();
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
        clear_screen();

        print_message_with_bars("Welcome to Kunal's ATM Banking");
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
                print_message_with_bars("Incorrect password");
                print_pause();
            }
        }

        if (u == 3)
        {

// BYE BYE MESSAGE
            clear_screen();
            print_message_with_bars("Thank you for using this program");
            print_pause();
        }

    } while (u != 3);

    return 0;
}