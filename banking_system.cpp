#include"banking_system.h"
#include<iostream>
#include<regex>
#include<fstream>
#include<string>

using namespace std;

//------------------------------------------------------------BankAccount------------------------------------------------------------
int BankAccount::i = 1;

BankAccount::BankAccount() : id(i), balance(0.0)
{
    i++;
}
BankAccount::BankAccount(double b) : id(i), balance(b)
{
    i++;
}
void BankAccount::set_balance(double b)
{
    balance = b;
    cout << "your balance has been updated\n";
    cout << "your balance now is: " << get_balace() << '\n';
}
double BankAccount::get_balace()
{
    return balance;
}
int BankAccount::get_id()
{
    return id;
}
void BankAccount::withdraw(double money)
{
    if (balance >= money)
    {
        balance -= money;
        cout << "the withdraw process has been done successfully\n";
        cout << "your balance now is: " << balance << '\n';
    }
    else
    {
        cout << "the account number doesn't have enough money\n";
        int x;
        cout << "please, enter the amount to withdraw again or enter '0' to exit: ";
        cin >> x;
        if(x)
        {
            BankAccount::withdraw(x);
        }
    }
}
void BankAccount::deposite(double money)
{
    balance += money;
    cout << "the deposite has been done successfully\n";
    cout << "your balance now is: " << balance << '\n';
}
/*Client* BankAccount:: get_client()
{
    return client_p;
}*/
//-----------------------------------------------------------------------------------------------------------------------------------


//----------------------------------------------------SavingsBankAccount-------------------------------------------------------------
SavingsBankAccount::SavingsBankAccount(double b)
{
    while (b < 1000)
    {
        cout << "the balance should be bigger than or equal to the minimum balance\n";
        cout << "enter the balance again:\n";
        cin >> b;
    }
    balance = b;
    minimumBalance = 1000;
}
SavingsBankAccount::SavingsBankAccount(double b, double mb)
{
    while (b < mb)
    {
        cout << "the balance should be bigger than or equal to the minimum balance\n";
        cout << "enter the balance and minimum balance again:\n";
        cin >> b >> mb;
    }
    balance = b;
    minimumBalance = mb;
}
void SavingsBankAccount :: set_balance(double b)
{
    if (b >= minimumBalance)
    {
        balance = b;
    }
    else
    {
        cout << "the balance should be bigger than or equal to the current minimum balance\n";
        cout << "please, enter the balance again: ";
        cin >> b;
        SavingsBankAccount::set_balance(b);
    }
}
void SavingsBankAccount::set_minimumBalance(double mb)
{
    if(balance >= mb)
    {
        minimumBalance = mb;
    }
    else
    {
        cout << "the minimum balance should be less than or equal to the current balance\n";
        cout << "please, enter the minimum balance again: ";
        cin >> mb;
        SavingsBankAccount::set_minimumBalance(mb);
    }
}
double SavingsBankAccount::get_minimumBalace()
{
    return minimumBalance;
}
void SavingsBankAccount::withdraw(double money)
{
    if (balance - money >= minimumBalance)
    {
        balance -= money;
        cout << "the withdraw  process has been done successfully\n";
        cout << "your balance now is " << get_balace() << '\n';
    }
    else
    {
        cout << "the amount left after withdrawing should be bigger than or equal to the minimum balance\n";
        cout << "please, enter another amount of money or '0' to exit\n";
        double x;
        cin >> x;
        if(x)
        {
            SavingsBankAccount::withdraw(x);
        }
    }
}

void SavingsBankAccount::deposite(double money)
{
    if (money >= 100)
    {
        balance += money;
        cout << "the deposite has been done successfully\n";
        cout << "your balance now is: " << balance << '\n';
    }
    else
    {
        cout << "the amount of money to deposite should be bigger than or equal to 100\n";
        cout << "please, enter another amount of money or '0' to exit\n";
        double x;
        cin >> x;
        if (x)
        {
            SavingsBankAccount::deposite(x);
        }
    }
}

Client::Client(string name ,string address , string phone)
{
    this -> name = name;
    this -> address = address;
    this -> phone = phone;
}

/*SavingsBankAccount& Client:: set_savingsacc( SavingsBankAccount* savings_account)
{
    this -> savings_account = savings_account;
}
*/
void Client:: set_name(string name)
{
    this -> name = name;
}
void Client:: set_address(string address)
{
    this -> address = address;
}
void Client:: set_phone(string phone)
{
    this -> phone = phone;
}

/*SavingsBankAccount& Client:: get_savingsacc()
{
    return *savings_account;
}
*/
void Client:: set_normalacc(BankAccount* normal_account)
{
    this -> normal_account = normal_account;
}

BankAccount* Client:: get_normalacc()
{
    return normal_account;
}

string Client:: get_name()
{
    return name;
}

string Client:: get_address()
{
    return address;
}

string Client:: get_phone()
{
    return phone;
}

BankApplication::BankApplication()
{
    load_Bank();
}

void BankApplication:: add_Client()
{
    string name, address, phone;
    double balance;
    int choice;

    cout << "Please Enter Client Name=========> ";

    getline(cin >> ws, name);

    cout << "Please Enter Client Address=========> ";

    getline(cin >> ws, address);

    cout << "Please Enter Client Phone=========> ";

    cin >> phone;

    cout << "What Type of Account Do You Like? (1) Basic (2) Saving, Type 1 or 2 =========> ";

    cin >> choice;

    if(choice == 1)
    {
        BankAccount_type.push_back("Basic");
        cout << "Please Enter the Starting Balance =========> ";
        cin >> balance;

        BankAccount* B = new BankAccount(balance);

        Client* C = new Client(name, address, phone);

        C->set_normalacc(B);

        Client_data.push_back(C);

        cout << "An account was created with ID " << B -> get_id() << " and Starting Balance " << B ->get_balace() << "L.E.\n";
    }

    else if(choice == 2)
    {
        int mb_choice;
        double mb;
        BankAccount_type.push_back("saving");
        cout << "do you want to set minimum balance? (1) Yes (2) No, Type 1 or 2 =========> ";
        cin >> mb_choice;
        if(mb_choice == 1)
        {
            cout << "enter minimum balance=========> ";
            cin >> mb;
            cout << "Please Enter the Starting Balance =========> ";
            cin >> balance;
            SavingsBankAccount* SB = new SavingsBankAccount(balance, mb);
            Client* C = new Client(name, address, phone);

            C->set_normalacc(SB);

            Client_data.push_back(C);

            cout << "An account was created with ID " << SB ->get_id() <<  " and Starting Balance " << SB ->get_balace() << " L.E.\n";
        }
        else if(mb_choice == 2)
        {
            cout << "Please Enter the Starting Balance =========> ";
            cin >> balance;
            SavingsBankAccount* SB = new SavingsBankAccount(balance);
            Client* C = new Client(name, address, phone);

            C->set_normalacc(SB);

            Client_data.push_back(C);

            cout << "An account was created with ID " << SB ->get_id() <<  " and Starting Balance " << SB ->get_balace() << " L.E.\n";

        }
    }
    else
    {
        cout << "invalid choice\n";
    }
}

void BankApplication::save_Bank()
{
    fstream bank_data;
    bank_data.open("bank data.txt", ios::out| ios::ate);

    for(int i = 0; i < Client_data.size(); i++)
    {

        bank_data << "name: " << Client_data[i] ->get_name() << "\n";
        bank_data << "address: " << Client_data[i] ->get_address() << "\n";
        bank_data << "phone: " << Client_data[i] ->get_phone() << "\n";
        bank_data << "type: " << BankAccount_type[i] << "\n";
        if(BankAccount_type[i] == "saving")
        {
            SavingsBankAccount* SB = dynamic_cast<SavingsBankAccount*>(Client_data[i] ->get_normalacc());

            if(SB != nullptr)
            {
                bank_data << "minimum balance: " << SB->get_minimumBalace() << "\n";
            }
        }
        bank_data << "balance: " << Client_data[i] ->get_balance() << "\n";
        bank_data << "ID: " << Client_data[i] ->get_id() << "\n";
        bank_data << "---------------------------------------------------------------------" << "\n";
    }
    bank_data.close();

}

void BankApplication::load_Bank()
{

    string bank_content, name, address, phone ,type;
    double balance, mb;
    int ID;
    Client* load_data;
    BankAccount* B;
    SavingsBankAccount* SB;

    fstream bank_data;
    bank_data.open("bank data.txt", ios::in);
    while(getline(bank_data, bank_content))
    {
        int index = bank_content.find(": ");
        if(bank_content.find("name: ") != string::npos)
        {
            name = bank_content.substr(index + 2);
        }
        if(bank_content.find("address: ")!= string::npos)
        {
            address = bank_content.substr(index + 2);

        }
        if(bank_content.find("phone: ")!= string::npos)
        {
            phone = bank_content.substr(index + 2);

        }
        if(bank_content.find("type: ")!= string::npos)
        {
            type = bank_content.substr(index + 2);
        }
        if(bank_content.find("minimum balance: ")!= string::npos)
        {
            mb = stod(bank_content.substr(index + 2));
        }
        if(bank_content.find("balance: ")!= string::npos)
        {
            balance = stod(bank_content.substr(index + 2));
        }
        if(bank_content.find("-") != string::npos)
        {
            load_data = new Client(name, address, phone);
            if(type == "Basic")
            {
                B = new BankAccount(balance);
                load_data ->set_normalacc(B);
            }
            else if(type == "saving")
            {
                SB = new SavingsBankAccount(balance, mb);
                load_data->set_normalacc(SB);
            }
            Client_data.push_back(load_data);
            BankAccount_type.push_back(type);

        }

    }

    bank_data.close();

}

void BankApplication :: main_menu()
{

    int choice;
    while(true)
    {
        cout << "--------------------------------------------------------------------\n";
        cout << "Welcome to FCAI Banking Application\n";
        cout << "1. Create a New Account\n2. List Clients and Accounts\n3. Withdraw Money\n4. Deposit Money\n";
        cout << "Please Enter Choice =========> ";
        cin >> choice;
        if(choice == 1)
        {
            add_Client();
            save_Bank();
        }
        else if(choice == 2)
        {
            for(int i = 0; i < Client_data.size(); i++)
            {
                cout << "--------------------------------------------------------------------\n";
                cout << "Client name : " << Client_data[i] -> get_name() << endl;
                cout << "address: " << Client_data[i] ->get_address() << endl;
                cout << "phone: " << Client_data[i]->get_phone() << endl;
                cout << "account type: " << BankAccount_type[i] << endl;

                if(BankAccount_type[i] == "saving")
                {
                    //BankAccount* B = Client_data[i] ->get_normalacc();
                    SavingsBankAccount* SB = dynamic_cast<SavingsBankAccount*>(Client_data[i] ->get_normalacc());

                    if(SB != nullptr)
                    {
                        cout << "minimum balance: " << SB->get_minimumBalace() << endl;
                    }
                }
                cout << "balance: " << Client_data[i]->get_balance() << endl;
                cout << "ID: " << Client_data[i]->get_id() << endl;
                save_Bank();

            }

        }
        else if(choice == 3)
        {
            int ID;
            double withdrwa;

            cout << "Please Enter Account ID =========> ";
            cin >> ID;

            while(!(ID >= Client_data[0]->get_id() && ID <= Client_data[Client_data.size() - 1]->get_id()))
            {
                cout << "invalid id\nenter your ID: ";
                cin >> ID;
            }

            cout << "ID: " << ID << endl;
            cout << "Account Type: " << BankAccount_type[ID - 1] << endl;

            cout << "Balance: " << Client_data[ID - 1]->get_balance() << endl;

            cout << "Please Enter The Amount to Withdraw =========> ";

            cin >> withdrwa;

            Client_data[ID - 1]->withdraw(withdrwa);

            cout << "Thank you.\n";
            cout << "Account ID: " << ID << endl;
            cout << "New Balance: " << Client_data[ID - 1]->get_balance() << endl;
            save_Bank();


        }
        else if(choice == 4)
        {
            int ID;
            double deposite;

            cout << "Please Enter Account ID =========> ";
            cin >> ID;
            while(!(ID >= Client_data[0]->get_id() && ID <= Client_data[Client_data.size() - 1]->get_id()))
            {
                cout << "invalid id\nenter your ID: ";
                cin >> ID;
            }

            cout << "ID: " << ID << endl;
            cout << "Account Type: " << BankAccount_type[ID - 1] << endl;

            cout << "Balance: " << Client_data[ID - 1]->get_balance() << endl;

            cout << "Please Enter The Amount to deposite =========> ";

            cin >> deposite;

            Client_data[ID - 1]->deposite(deposite);

            cout << "Thank you.\n";
            cout << "Account ID: " << ID << endl;
            cout << "New Balance: " << Client_data[ID - 1]->get_balance() << endl;
            save_Bank();
        }
        else
        {
            break;
        }

    }

}

