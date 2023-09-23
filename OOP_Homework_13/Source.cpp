#include <iostream>
using namespace std;

class Payment 
{
public:
    virtual void makePayment(double amount) = 0;
    virtual double amount() = 0;
};

class FundsPaidFromAccount : public Payment 
{
private:
    double balance;
public:
    FundsPaidFromAccount(double initialBalance) : balance(initialBalance) {}
    void makePayment(double amount) override {
        if (balance >= amount) {
            balance -= amount;
            cout << "Payment made: " << amount << "\tNew balance: " << balance << endl;
        }
        else
            cout << "Not enough money!\tBalance: " << balance << endl;
    }
    double amount() override {
        return balance;
    }
};

class CheckProxy : public Payment
{
private:
    FundsPaidFromAccount* realSubject;
public:
    CheckProxy(double initialBalance) {
        realSubject = new FundsPaidFromAccount(initialBalance);
    }
    void makePayment(double amount) override {
        realSubject->makePayment(amount);
    }
    double amount() override {
        return realSubject->amount();
    }
    ~CheckProxy() {
        delete realSubject;
    }
};

int main()
{
    Payment* payment = new CheckProxy(1000.0);
    cout << "Balance: " << payment->amount() << endl;
    payment->makePayment(500.0);
    cout << "Balance: " << payment->amount() << endl;
    payment->makePayment(800.0);
    delete payment;

    system("pause");

    return 0;
}