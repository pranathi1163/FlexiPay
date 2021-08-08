#include <iostream>
#include "wallet.h"

using namespace std;

class User
{
    public:
        Wallet w;

        string name;
        string mobile;
        float balance;
        int pin;

        User();
        void signup();
        bool check();
        static bool login(string no);
        void display(string no);

    protected:

    private:
};

//#endif // USER_H
