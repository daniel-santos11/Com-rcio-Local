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
bool isPosInt(string s);
bool isDouble(string s);

#endif