#include <iostream>
#include <stdlib.h>
#include <windows.h>

#include "user.h"
#include "wallet.h"

using namespace std;

class Menu
{
public:
    int choice;
    void menuProg()
    {
      while(1)
    {
        system("cls");
        cout << "1. SIGN UP" << endl;
        cout << "2. LOGIN" << endl;
        cout << "3. EXIT" << endl << endl;

        cout << "ENTER YOUR CHOICE : ";
        cin >> choice;

        switch(choice)
        {
        case 1:
        {
            system("cls");
            cout << "SIGNUP" << endl << endl;
            User obj;
            obj.signup();
            break;
        }
        case 2:
        {
            system("cls");
            User obj;
            string no;
            bool chk;
            cout << "LOGIN" << endl << endl;
            fflush(stdin);
            cout << "ENTER YOUR ACCOUNT NUMBER : ";
            getline(cin,no);
            chk = User :: login(no);
            if(chk)
            {
                obj.display(no);
            }
            else
            {
                cout << endl << "ACCOUNT NOT FOUND OR INVALID PIN!!!" << endl << endl;
            }
            break;
        }
        case 3:
            exit(0);
        default:
            cout << endl << "INVALID CHOICE !!!" << endl;
        }

        cout << endl;
        system("pause");
    }

    }
};
int main()
{
    Menu p1;
    p1.menuProg();
    return 0;
}
