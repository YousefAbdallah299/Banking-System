#ifndef BANKING_SYSTEM_H
#define BANKING_SYSTEM_H


#include <iostream>
#include<vector>
using namespace std;

class BankAccount
{
protected:
    static int i;
    int	id;
    double balance;


public:
    BankAccount();
    BankAccount(double balance);
    virtual void set_balance(double balance);
    double get_balace();
    int get_id();
    virtual void withdraw(double money);
    virtual void deposite(double money);
    //Client* get_client();
};


class SavingsBankAccount : public BankAccount
{
protected:
    double minimumBalance;
public:
    SavingsBankAccount(double balance);
    SavingsBankAccount(double balance, double minimumBalance);
    void withdraw(double money);
    void deposite(double money);
    void set_balance(double balance);
    void set_minimumBalance(double minimumBalance);
    double get_minimumBalace();
};

class Client
{
private:
    string name,address,phone;
    BankAccount* normal_account;
public:
    Client(string name ,string address , string phone);

    void set_normalacc(BankAccount* normal_account);

    void set_name(string name);

    void set_address(string address);

    void set_phone(string phone);

    BankAccount* get_normalacc();

    string get_name();

    string get_address();

    string get_phone();

    int get_id()
    {
        return normal_account ->get_id();
    }

    double get_balance()
    {
        return normal_account ->get_balace();
    }
    void withdraw(double b)
    {
        normal_account ->withdraw(b);
    }

    void deposite(double d)
    {
        normal_account ->deposite(d);
    }

};


class BankApplication
{
private:
    vector<Client*> Client_data;
    vector<string> BankAccount_type;
    void save_Bank();
    void load_Bank();

public:

    BankApplication ();

    void add_Client();

    void main_menu();



};

#endif // BANKING_SYSTEM_H
