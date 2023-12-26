#ifndef CARRINHOS_H
#define CARRINHOS_H


#include <iostream>
#include <string>

using namespace std;

void adicionarProdutoCarrinho(int idProduto, int qtd);
int encontrarProdutoCarrinho(int idProduto);
double calcularTotaisCarrinho();
bool sortearCompra();
void resetCarrinho();
void imprimirFatura(double valorDado, double valorTotal, int nif);

#endif