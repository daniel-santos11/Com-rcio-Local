#ifndef LOGS_H
#define LOGS_H

#include <string>
#include "produtos.h"

using namespace std;

void setColor(int color);

void resetColor();

void logMenu(const string *opcoes, int tamanho);

void logInfo(const string &message, bool esperar);

void logErro(const string &message);

void logAviso(const string &message);

void logSucesso(const string &message);

void logTitulo(const string &message);

void logTabela(const TProduto *produtos, int tamanho);

void logFatura(const TProduto *produtos, int tamanho, double valorDado, int nif, int nFatura);

void logMarca();

void espera();

string getTime();

string doubleParaString(double valor);

void ativarLog();

void limparEcra();

#endif