#include <iostream>
#include <string>
#include <stack>

using namespace std;

// --- VERIFICAR QUAL OP TEM MAIOR PIORIDADE
int prioridade(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == 'x' || op == '/')
        return 2;
    return 0;
}

// - REALIZA AS OPERACOES
double calcular(int num1, int num2, char op)
{
    switch (op)
    {
    case '+':
        return num1 + num2;
    case '-':
        return num1 - num2;
    case '*':
        return num1 * num2;
    case 'x':
        return num1 * num2;
    case '/':
        return num1 / num2;
    default:
        return 0;
    }
}

// ---- ORGANIZA OS NUMEROS E CALCULA EM ORDEM
double realizarCalculo(string calculo)
{
    stack<double> numeros;
    stack<char> operadores;

    for (size_t i = 0; i < calculo.length(); i++)
    {
        char caractere = calculo[i];
        if (isspace(caractere))
            continue;

        if (isdigit(caractere))
        {
            double numero = 0;
            while (i < calculo.length() && isdigit(calculo[i]))
            {
                numero = numero * 10 + (calculo[i] - '0');
                i++;
            }
            i--;
            numeros.push(numero);
        }
        else if (caractere == '(')
        {
            operadores.push(caractere);
        }
        else if (caractere == ')')
        {
            while (!operadores.empty() && operadores.top() != '(')
            {
                double num2 = numeros.top();
                numeros.pop();
                double num1 = numeros.top();
                numeros.pop();
                char op = operadores.top();
                operadores.pop();
                numeros.push(calcular(num1, num2, op));
            }
            operadores.pop();
        }
        else
        {
            while (!operadores.empty() && prioridade(operadores.top()) >= prioridade(caractere))
            {
                double num2 = numeros.top();
                numeros.pop();
                double num1 = numeros.top();
                numeros.pop();
                char op = operadores.top();
                operadores.pop();
                numeros.push(calcular(num1, num2, op));
            }
            operadores.push(caractere);
        }
    }
    while (!operadores.empty())
    {
        double num2 = numeros.top();
        numeros.pop();
        double num1 = numeros.top();
        numeros.pop();
        char op = operadores.top();
        operadores.pop();
        numeros.push(calcular(num1, num2, op));
    }
    return numeros.top();
}

// ------ FUNCAO PRINCIPAL
int main()
{
    string calculo;
    cout << "Informe o calculo que deseja realizar(ex: 2x(1+3): \n";
    getline(cin, calculo);

    double resultado = realizarCalculo(calculo);

    cout << "Resultado: " << resultado;
    return 0;
}