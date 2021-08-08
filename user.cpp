#include "user.h"

#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>

User::User()
{
    name = "";
    mobile = "";
    balance = 0.0;
    pin = 0;
}

void User :: signup()
{
    bool chk;

    stringstream ss;

    fflush(stdin);
    cout << "ENTER YOUR NAME          : ";
    getline(cin,name);
    fflush(stdin);
    cout << "ENTER YOUR MOBILE NUMBER : ";
    getline(cin,mobile);
    cout << "ENTER INITIAL BALANCE    : RS. ";
    cin >> balance;
    cout << "ENTER A 4 DIGIT PIN      : ";
    cin >> pin;

    chk = check();

    if(chk)
    {
        ofstream f;

        ss << mobile << ".txt";

        f.open(ss.str(),ios::out);

        f << pin << endl;
        f << "NAME    : " << name << endl;
        f << "MOBILE  : " << mobile << endl;
        f << "BALANCE : RS. " << balance << endl << endl;

        f.close();

        stringstream ss1;
        ss1 << "T " << mobile << ".txt";

        ofstream f1;

        f1.open(ss1.str(),ios::app);

        time_t now = time(0);
        char* dateTime = ctime(&now);

        f1 << "RS.   " << setw(10) << balance << " - " << dateTime << endl;

        f1.close();

        cout << endl << "ACCOUNT CREATED SUCCESSFULLY" << endl;
        cout << "NOTE : ACCOUNT NUMBER IS SAME AS MOBILE NUMBER" << endl;
    }
    else
    {
        cout << endl << "ACCOUNT NOT CREATED" << endl;
        cout << "INVALID ENTRY FOUND OR ACCOUNT ALREADY EXISTS !!!" << endl;
    }
}

bool User :: check()
{
    string line;
    fstream f;

    f.open("USER.txt",ios::in);

    if(mobile.length() != 10)
        return false;

    if(!f)
    {
        f.close();

        f.open("USER.txt",ios::out);
    }
    else
    {
        while(getline(f,line))
        {
            if(line == mobile)
            {
                f.close();
                return false;
            }
        }
    }

    if(balance <= 0)
        return false;

    if(pin < 1000 || pin >= 10000)
        return false;

    f.close();

    f.open("USER.txt",ios::app);
    f << mobile << endl;
    f.close();

    return true;
}

bool User :: login(string no)
{
    string line;
    fstream f;
    stringstream ss;

    int cpin;

    f.open("USER.txt",ios::in);

    if(!f)
    {
        return false;
    }
    else
    {
        while(getline(f,line))
        {
            if(line == no)
            {
                ss << no << ".txt";
                f.close();

                f.open(ss.str(),ios::in);

                getline(f,line);

                cout << "ENTER YOUR PIN            : ";
                cin >> cpin;

                if(cpin == stoi(line))
                {
                    f.close();
                    return true;
                }
            }
        }
    }

    f.close();

    return false;
}

void User :: display(string no)
{
    int choice;
    bool chk;

    while(1)
    {
        system("cls");
        cout << "1. DEPOSIT" << endl;
        cout << "2. TRANSFER" << endl;
        cout << "3. VIEW WALLET" << endl;
        cout << "4. TRANSACTION HISTORY" << endl;
        cout << "5. LOG OUT" << endl << endl;

        cout << "ENTER YOUR CHOICE : ";
        cin >> choice;

        switch(choice)
        {
        case 1:
        {
            system("cls");
            cout << "ENTER AMOUNT TO DEPOSIT : RS. ";
            cin >> w.amt;
            chk = w.transact(no,1);
            if(chk)
                cout << endl << "DEPOSIT SUCCESSFUL" << endl;
            else
                cout << "DEPOSIT FAILED" << endl;
            break;
        }
        case 2:
        {
            system("cls");
            w.transfer(no);
            break;
        }
        case 3:
        {
            system("cls");
            w.viewWallet(no);
            break;
        }
        case 4:
        {
            system("cls");
            w.transactHistory(no);
            break;
        }
        case 5:
            system("cls");
            cout << "LOGOUT SUCCESSFUL" << endl;
            return;
        default:
            cout << "INVALID CHOICE !!!" << endl;
        }

        cout << endl;
        system("pause");
    }
}
