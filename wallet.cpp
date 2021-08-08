#include "wallet.h"

#include <fstream>
#include <sstream>
#include <string.h>
#include <ctime>
#include <iomanip>

Wallet::Wallet()
{
    amt=0.0;
}



bool Wallet :: transact(string no, int n)
{
    stringstream ss;
    stringstream ss1;
    fstream f;

    string line;

    ss << no << ".txt";

    f.open(ss.str());

    int len = 2;
    while(getline(f,line))
    {
        if(line.find("BALANCE : RS. ") != string::npos)
        {
            string bal;
            float balance;

            bal = line.substr(14,line.length());

            balance = stof(bal);

            if(amt < 0)
            {
                cout << endl << "INVALID ENTRY !!!" << endl;
                return false;
            }

            if(n == 1)
            {
                balance += amt;

                ss1 << "T " << no << ".txt";

                ofstream f1;

                f1.open(ss1.str(),ios::app);

                time_t now = time(0);
                char* dateTime = ctime(&now);

                f1 << "RS.   " << setw(10) << amt << " - " << dateTime << endl;

                f1.close();
            }
            else if(n == 0)
            {
                if(amt <= balance)
                {
                    balance -= amt;

                    ss1 << "T " << no << ".txt";

                    ofstream f1;

                    f1.open(ss1.str(),ios::app);

                    time_t now = time(0);
                    char* dateTime = ctime(&now);

                    f1 << "RS. - " << setw(10) << amt << " - " << dateTime << endl;

                    f1.close();
                }
                else
                {
                    return false;
                }
            }

            f.seekg(len);

            int len1 = line.length();
            int i = 1;
            while(i != len1)
            {
                f << "!";
                i++;
            }

            f << endl;
            f << "BALANCE : RS. " << balance << endl << endl;

            return true;
        }

        len += (line.length() + 1);
    }

    f.close();

    return false;
}

void Wallet :: transfer(string no)
{
    string no1;
    ifstream f;
    string line;

    bool chk;
    int i = 0;

    fflush(stdin);
    cout << "ENTER ACCOUNT NUMBER TO TRANSFER : ";
    getline(cin,no1);

    f.open("USER.txt",ios::in);

    if(!f)
    {
        cout << endl << "ACCOUNT NOT FOUND" << endl;
    }
    else
    {
        while(getline(f,line))
        {
            if(line == no1)
            {
                f.close();


                cout << "ENTER AMOUNT TO TRANSFER         : RS. ";
                cin >> amt;

                chk = transact(no,0);
                if(chk)
                {
                    transact(no1,1);
                    cout << endl << "TRANSFER SUCCESSFUL" << endl;
                }
                else
                {
                    cout << endl << "NO ENOUGH BALANCE TO TRANSFER !!!" << endl;
                    cout << "TRANSFER FAILED" << endl;
                }

                i = 1;

                break;
            }
        }
    }

    if(i == 0)
        cout << endl << "TRANSFER FAILED" << endl;
}

void Wallet :: viewWallet(string no)
{
    stringstream ss;
    ifstream f;

    string line;

    ss << no << ".txt";

    f.open(ss.str());

    while(getline(f,line))
    {
        if(line.find("BALANCE : RS. ") != string::npos)
        {
            cout << "AVAILABLE " << line << endl;

            break;
        }
    }

    f.close();
}

void Wallet :: transactHistory(string no)
{
    stringstream ss;
    ifstream f;

    string line;

    ss << "T " << no << ".txt";

    f.open(ss.str());

    while(getline(f,line))
    {
        cout << line << endl;
    }

    f.close();

}

