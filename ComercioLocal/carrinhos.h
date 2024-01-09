#ifndef CARRINHOS_H
#define CARRINHOS_H

#include <iostream>
#include <string>

using namespace std;

bool adicionarProdutoCarrinho(int idProduto, int qtd);

int encontrarProdutoCarrinho(int idProduto);

double calcularTotaisCarrinho();

bool sortearCompra();

void resetCarrinho();

void imprimirFatura(double valorDado, int nif);

void confirmarCompra();

bool produtosNoCarrinho();

void mostrarListaProdutosCarrinho();

bool carrinhoCheio();

#endif