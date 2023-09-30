#include <iostream>
#include <string>

#include "fila.hpp"
#include "pilha.hpp"

using namespace std;

struct Incognita {
    char letra = NULL;
    double valor = 0.0;
};

bool ehOperando(const char caractere) {
    return caractere >= '0' && caractere <= '9' ||
        caractere >= 'a' && caractere <= 'z' ||
        caractere >= 'A' && caractere <= 'Z';
}

bool ehOperacao(const char caractere) {
    return caractere >= '(' && caractere <= '/' || caractere == '^';
}

bool ehMenorPrecedente(const char op1, const char op2) {
    if (op1 == '+' || op1 == '-') {
        return op2 == '*' || op2 == '/' || op2 == '^';
    }
    if (op1 == '*' || op1 == '/') {
        return op2 == '^';
    }
    return false;
}

bool parentesesNaoForamFechados(const string& expressao) { // ou nao foram abertos
    int aberturas = 0;
    int fechamentos = 0;

    for (char c : expressao) {
        if (c == '(') {
            aberturas++;
        }
        else if (c == ')') {
            fechamentos++;
        }
    }

    return aberturas != fechamentos;
}

double char2double(const char c) {
    char i = '0';
    double valor = 0.0;
    while (i != c && i != '9' + 1) {
        i++;
        valor++;
    }
    return i == c ? valor : -1;
}

double calcularPotencia(const double expoente, const double base) {
    double resultado = 1;
    for (int i = 1; i <= expoente; i++)
        resultado *= base;
    return resultado;
}

bool calcularOperacao(Pilha<double>& operandos, const char operacao, double& resultado) {
    double operando1, operando2;
    if (!remover(operandos, operando1) || !remover(operandos, operando2)) {
        cout << "\nExcesso de operadores!";
        return false;
    }

    switch (operacao) {
    case '^':
        resultado = calcularPotencia(operando1, operando2);
        return true;
    case '*':
        resultado = operando1 * operando2;
        return true;
    case '/':
        resultado = operando1 / operando2;
        return true;
    case '+':
        resultado = operando1 + operando2;
        return true;
    case '-':
        resultado = operando1 - operando2;
        return true;
    }

    cout << "\nUso de operador invalido!";
    return false;
}

double buscarIncognita(Incognita vetor[52], const char incognita) {
    int i = 0;
    for (; i < 52 && vetor[i].letra != NULL; i++)
        if (vetor[i].letra == incognita)
            return vetor[i].valor;
    cout << "\nInsira o valor da incognita " << incognita << ": ";
    cin >> vetor[i].valor;

    vetor[i].letra = incognita;
    return vetor[i].valor;
}

double calcularExpressao(Fila<char>& expressao) {
    Pilha<double> operandos;
    inicializar(operandos);
    char it;
    double resultado = 0.0;
    Incognita incognitas[52]; // a até z + A até Z = 52

    while (remover(expressao, it)) {
        if (ehOperando(it)) {
            double operando = char2double(it);
            if (operando < 0) {
                operando = buscarIncognita(incognitas, it);
            }
            inserir(operandos, operando);
            continue;
        }
        if (calcularOperacao(operandos, it, resultado)) {
            cout << "Calculo realizado ate a excecao: ";
            return resultado;
        }
        inserir(operandos, resultado);
    }
    return remover(operandos, resultado) ? resultado : 0.0;
}

int main() {
    string expressao;
    cout << "Expressao hungara: ";
    getline(cin, expressao);

    if (parentesesNaoForamFechados(expressao)) {
        cout << "\nQuantidade de parentes invalida!!";
        return 0;
    };

    Fila<char> hungara;
    inicializar(hungara);

    Fila<char> polonesa;
    inicializar(polonesa);

    Pilha<char> operadores;
    inicializar(operadores);

    for (char it : expressao) {
        if (it != ' ')
            inserir(hungara, it);
    }

    char it, itAnterior = NULL;

    while (remover(hungara, it)) {
        char aux = NULL;
        if (it == ')') {
            while (remover(operadores, aux) && aux != '(')
                inserir(polonesa, aux);
        }
        else if (ehOperacao(it)) {
            while (remover(operadores, aux) && ehMenorPrecedente(it, aux)) {
                inserir(polonesa, aux);
                aux = NULL;
            }
            if (aux != NULL)
                inserir(operadores, aux);
            inserir(operadores, it);
        }
        else if (ehOperando(it)) {
            if (ehOperando(itAnterior)) {
                cout << "\nOperandos menores que 0 ou maiores que 9 devem ser inseridos "
                    "como incognitas!";
                return 0;
            }
            inserir(polonesa, it);
        }
        itAnterior = it;
    }

    while (remover(operadores, it))
        inserir(polonesa, it);

    Fila<char> polonesaAux;
    inicializar(polonesaAux);

    cout << "\nExpressao polonesa inversa: ";
    while (remover(polonesa, it)) {
        inserir(polonesaAux, it);
        cout << it;
    }
    cout << endl;

    cout << "\nResultado da expressao: " << calcularExpressao(polonesaAux) << "\n";
}
