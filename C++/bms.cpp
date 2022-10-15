#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

int MAX = 9999999999;

class Account
{
private:
    static int CurAccNo;

    bool open = true;
    int AccNo = ++CurAccNo;
    double balance = 0;
    string gender = "N/A";
    string first_name, second_name;

public:
    Account(){}
    Account(string, string, int);

    void deposit(double);
    void withdraw(double);
    void transfer(Account, double);

    static void setCurAccNo(int No){
        if(No > 0)
            CurAccNo = No;
    }

    int getAccNo();
    double getBalance();
    string getGender();
    string getFirstName();
    string getSecondName();

    void setBalance(double);
    void setGender(string);
    void setFirstName(string);
    void setSecondName(string);

    void close();
    bool isOpen();

    friend istream& operator >> (istream& in, Account &acc);
    friend ostream& operator << (ostream& out, Account &acc);

    friend ifstream& operator >> (ifstream& in, Account &acc);
    friend ofstream& operator << (ofstream& out, Account &acc);
};

int Account::CurAccNo = 0;

Account::Account(string first_name, string second_name, int initial_balance)
{
    setFirstName(first_name);
    setSecondName(second_name);
    balance = initial_balance;
}

void Account::deposit(double value){balance += value;}
void Account::withdraw(double value){balance -= value;}
void Account::transfer(Account other, double value){balance -= value ;other.balance += value;}

int Account::getAccNo(){return AccNo;}
double Account::getBalance(){return balance;}
string Account::getGender(){return gender;}
string Account::getFirstName(){return first_name;}
string Account::getSecondName(){return second_name;}

void Account::setBalance(double balance){if(balance >= 0) this -> balance = balance;}
void Account::setGender(string gender){if(gender == "M" || gender == "F") this -> gender = gender;}
void Account::setFirstName(string first_name){if(first_name != "") this -> first_name = first_name;}
void Account::setSecondName(string second_name){if(second_name != "") this -> second_name = second_name;}

void Account::close(){open = false;}
bool Account::isOpen(){return open;}

istream& operator >> (istream& in, Account &acc){
    string first_name, second_name;
    string gender;
    double balance;

    cout << "Enter First Name: "; cin >> first_name;
    cout << "Enter Second Name: "; cin >> second_name;
    cout << "Enter Gender (M / F): "; cin >> gender;
    cout << "Enter Initial Balance: "; cin >> balance;

    acc.setFirstName(first_name);
    acc.setSecondName(second_name);
    acc.setGender(gender);
    acc.setBalance(balance);

    return in;
}

ostream& operator << (ostream& out, Account &acc){
    out << "First Name: " << acc.getFirstName() << endl;
    out << "Second Name: " << acc.getSecondName() << endl;
    out << "Gender: " << acc.getGender() << endl;
    out << "Current Balance: " << acc.getBalance() << endl;
    out << "Account Number: " << acc.getAccNo() << endl;
    out << "Status: " << (acc.isOpen()? "Open" : "Closed") << endl;

    return out;
}

ifstream& operator >> (ifstream& in, Account &acc){
    string first_name, second_name;
    string gender;
    int AccNo; bool open;
    double balance;

    in >> first_name >> second_name;
    in >> gender;
    in >> balance >> AccNo;
    in >> open;

    acc.setFirstName(first_name);
    acc.setSecondName(second_name);
    acc.setGender(gender);
    acc.setBalance(balance);
    acc.open = open;
    acc.AccNo = AccNo;

    return in;
}

ofstream& operator << (ofstream& out, Account &acc){
    out << acc.getFirstName() << endl;
    out << acc.getSecondName() << endl;
    out << acc.getGender() << endl;
    out << acc.getBalance() << endl;
    out << acc.getAccNo() << endl;
    out << acc.isOpen();

    return out;
}

bool isEmpty(ifstream& pFile)
{
    return pFile.peek() == ifstream::traits_type::eof();
}

bool Valid(unsigned int AccNo, vector<Account> Accounts){
    if(AccNo <= Accounts.size() && AccNo > 0 && Accounts[AccNo].isOpen())
        return true;
    return false;
}

int main()
{
    vector<Account> Accounts;

    ofstream otrans("Transactions.txt", ios::app);

    ofstream ofs("BankingSystem.txt", ios::app);
    ifstream ifs("BankingSystem.txt");

    vector<int> AccNos;
    vector<string> types;
    vector<double> values;

    while(!ifs.eof() && !isEmpty(ifs)){
        Account acc;
        ifs >> acc;

        Accounts.push_back(acc);
    }

    Account::setCurAccNo(Accounts.size());

    while(true){
        cout << "|=============================|" << endl;
        cout << "|       WELCOME TO            |" << endl;
        cout << "|          RANDOM BANK        |" << endl;
        cout << "|=============================|" << endl;

        cout << endl;

        cout << "What Would You Like To Do?:" << endl;
        cout << "   1. Open Account" << endl;
        cout << "   2. Close Account" << endl;
        cout << "   3. Show All Accounts" << endl;
        cout << "   4. Deposit in Account" << endl;
        cout << "   5. Withdraw in Account" << endl;
        cout << "   6. Transfer to an Account" << endl;
        cout << "   7. Show Balance" << endl;
        cout << "   8. Show All Transactions" << endl;
        cout << "   9. Quit" << endl;
        cout << endl;

        string option;
        cout << "Please Enter Your Option: "; cin >> option;

        if(option == "1"){
            Account acc;
            cin >> acc;

            if(Accounts.size() != 0)
                ofs << endl;

            Accounts.push_back(acc);
            ofs << acc;

            cout << "Account Opened Successfully!" << endl;
            cout << "Your Account Number is " << acc.getAccNo() << endl;
        }

        else if(option == "2"){
            int AccNo;
            cout << "Enter Account Number: "; cin >> AccNo;

            AccNo--;

            if(Valid(AccNo, Accounts)){
                cout << "Account Closed Successfully!" << endl;
                Accounts[AccNo].close();
            }
            else
                cout << "There Was an Error, Please Try Again!" << endl;
        }

        else if(option == "3"){
            cout << endl;

            for(unsigned int i = 0; i < Accounts.size(); i++)
                cout << Accounts[i] << endl;
        }

        else if(option == "4"){
            int AccNo;
            double value;
            cout << "Enter Account Number: "; cin >> AccNo;
            cout << "Enter Deposit Amount: "; cin >> value;

            AccNo--;

            if(Valid(AccNo, Accounts)){
                if(value < MAX){
                    cout << value << " Deposited to " << Accounts[AccNo].getFirstName() << "'s Account Successfully!" << endl;

                    Accounts[AccNo].deposit(value);
                    cout << "Balance is " << Accounts[AccNo].getBalance() << endl;

                    AccNos.push_back(AccNo);
                    types.push_back("Deposit");
                    values.push_back(value);
                }
                else
                    cout << "Overflow!" << endl;
            }
            else
                cout << "There Was an Error, Please Try Again!" << endl;
        }

        else if(option == "5"){
            int AccNo;
            double value;
            cout << "Enter Account Number: "; cin >> AccNo;
            cout << "Enter Withdrawal Amount: "; cin >> value;

            AccNo--;

            if(Valid(AccNo, Accounts)){
                if(Accounts[AccNo].getBalance() - value >= 0){
                    cout << value << " Withdrawn from " << Accounts[AccNo].getFirstName() << "'s Account Successfully!" << endl;

                    Accounts[AccNo].withdraw(value);
                    cout << "Balance is " << Accounts[AccNo].getBalance() << endl;

                    AccNos.push_back(AccNo);
                    types.push_back("Withdrawal");
                    values.push_back(value);
                }
                else
                    cout << "Not Enough Balance" << endl;
            }
            else
                cout << "There Was an Error, Please Try Again!" << endl;
        }

        else if(option == "6"){
            int AccNo, AccNoOther;
            double value;
            cout << "Enter Account Number: "; cin >> AccNo;
            cout << "Enter Other Account Number: "; cin >> AccNoOther;
            cout << "Enter Transfer Amount: "; cin >> value;

            AccNo--;

            if(Valid(AccNo, Accounts) && Valid(AccNoOther, Accounts)){
                if(Accounts[AccNoOther].getBalance() + value > MAX)
                    cout << "Overflow" << endl;
                else {
                    if(Accounts[AccNo].getBalance() - value >= 0){
                        cout << value << " Transfer to " << Accounts[AccNoOther].getFirstName() << "'s Account Successfully!" << endl;

                        Accounts[AccNo].transfer(Accounts[AccNoOther], value);
                        cout << Accounts[AccNo].getFirstName() << "'s Balance is " << Accounts[AccNo].getBalance() << endl;
                        cout << Accounts[AccNoOther].getFirstName() << "'s Balance is " << Accounts[AccNo].getBalance() << endl;
                    }

                    else
                        cout << "Not Enough Balance" << endl;
                }
            }

            else
                cout << "There Was an Error, Please Try Again!" << endl;
        }

        else if(option == "7"){
            int AccNo;
            cout << "Enter Account Number: "; cin >> AccNo;

            AccNo--;

            cout << endl;

            if(Valid(AccNo, Accounts))
                cout << Accounts[AccNo];
            else
                cout << "There Was an Error, Please Try Again!" << endl;
        }

        else if(option == "8"){
            int AccNo;
            cout << "Enter Account Number: "; cin >> AccNo;

            AccNo--;

            if(Valid(AccNo, Accounts)){
                ifstream itrans("Transactions.txt");
                vector<double> deposits;
                vector<double> withdrawals;

                string x = "Deposits";

                while(!itrans.eof() && !isEmpty(itrans)){
                    int TransAcc;
                    string type;
                    double value;

                    itrans >> TransAcc >> type >> value;

                    if(TransAcc == AccNo){
                        if(type == "Deposit")
                            deposits.push_back(value);
                        if(type == "Withdrawal")
                            withdrawals.push_back(value);
                    }
                }

                for(unsigned int i = 0; i < AccNos.size(); i++){
                    int TransAcc = AccNos[i];
                    string type = types[i];
                    double value = values[i];

                    if(TransAcc == AccNo){
                        if(type == "Deposit")
                            deposits.push_back(value);
                        if(type == "Withdrawal")
                            withdrawals.push_back(value);
                    }
                }

                cout << "=======================================" << endl;
                cout << "Withdrawal         |           Deposits" << endl;
                cout << "=======================================" << endl;
                cout << endl;

                for(unsigned int i = 0; i < (deposits.size(), withdrawals.size()); i++){
                    int s = 0;

                    if(i < withdrawals.size()){
                        string x = to_string(withdrawals[i]);
                        cout << x;

                        s = x.size();
                    }

                    string x = "Deposits           ";

                    for(unsigned int _ = 0; _ < x.size() - s; _++)
                        cout << " ";

                    cout << "|           ";

                    if(i < deposits.size()){
                        string x = to_string(deposits[i]);
                        cout << x;
                    }

                    cout << endl;
                }
            }
            else
                cout << "There Was an Error, Please Try Again!" << endl;
        }

        else if(option == "9"){
            break;
        }

        else {
            cout << "Please Enter a Valid Option" << endl;
        }

        cout << endl;

        system("pause");
        system("cls");
    }

    ofstream ofsn("BankingSystem.txt");

    for(unsigned int i = 0; i < Accounts.size(); i++){
        if(i != 0)
            ofsn << "\n";
        ofsn << Accounts[i];
    }

    for(unsigned int i = 0; i < AccNos.size(); i++){
        if(i != 0)
            otrans << "\n";
        otrans << AccNos[i] << " " << types[i] << " " << values[i] << endl;
    }
}