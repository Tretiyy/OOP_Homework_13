#include <iostream>
#include <vector>
using namespace std;

class ArithmeticExpression 
{
public:
    virtual double evaluate() = 0;
};

class NumericOperand : public ArithmeticExpression
{
private:
    double value;
public:
    NumericOperand(double val) : value(val) {}
    double evaluate() override {
        return value;
    }
};

class CompositeOperand : public ArithmeticExpression
{
private:
    char operation;
    vector<ArithmeticExpression*> operands;
public:
    CompositeOperand(char op) : operation(op) {}
    void addOperand(ArithmeticExpression* operand) {
        operands.push_back(operand);
    }
    double evaluate() override {
        if (operands.empty())
            return 0.0;
        double result = operands[0]->evaluate();
        for (size_t i = 1; i < operands.size(); ++i) {
            if (operation == '+')
                result += operands[i]->evaluate();
            else if (operation == '-')
                result -= operands[i]->evaluate();
            else if (operation == '*')
                result *= operands[i]->evaluate();
            else if (operation == '/') {
                if (operands[i]->evaluate() != 0)
                    result /= operands[i]->evaluate();
                else {
                    cerr << "You can't divide by 0!" << endl;
                    return 0.0;
                }
            }
        }
        return result;
    }
};

int main()
{
    NumericOperand* num1 = new NumericOperand(2.0);
    NumericOperand* num2 = new NumericOperand(3.0);
    CompositeOperand* addition = new CompositeOperand('+');
    addition->addOperand(num1);
    addition->addOperand(num2);

    NumericOperand* num3 = new NumericOperand(4.0);
    NumericOperand* num4 = new NumericOperand(6.0);
    CompositeOperand* multiplication = new CompositeOperand('*');
    multiplication->addOperand(num3);
    multiplication->addOperand(num4);

    CompositeOperand* finalExpression = new CompositeOperand('+');
    finalExpression->addOperand(addition);
    finalExpression->addOperand(multiplication);

    cout << "(2 + 3) + (4 * 6)" << endl;
    cout << "Result: " << finalExpression->evaluate() << endl;

    delete finalExpression;
    delete multiplication;
    delete addition;
    delete num4;
    delete num3;
    delete num2;
    delete num1;

    system("pause");

    return 0;
}