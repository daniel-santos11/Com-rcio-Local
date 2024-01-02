#ifndef MENUS_H
#define MENUS_H

#include <string>

using namespace std;

void menuPrincipal();

void menuAdicionarProduto();

void menuRemoverProduto();

void atualizarStock();

void iniciarCompra();

void menuListarProdutos();

void bootstrap();

bool isPosInt(const string &s);

bool isDouble(const string &s);

string pedirValidarNome();

double pedirValidarValor(const string &msg, double min);

int pedirValidarQtd(const string &msg);

int pedirValidarIdProduto();

int pedirValidarNumeroCliente();

bool pedirConfimacao();

bool validarCasaDecimais(const string &sDouble);

void aguardarInputSaida();

#endif