#ifndef WALLET_H
#define WALLET_H

#include <iostream>

using namespace std;

class Wallet
{
    public:

        float amt;

        Wallet();
        bool transact(string no, int n);
        void transfer(string no);
        void viewWallet(string no);
        void transactHistory(string no);

};

#endif // WALLET_H
