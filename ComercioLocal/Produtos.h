#ifndef PRODUTOS_H
#define PRODUTOS_H

#include <string>

using namespace std;

void adicionarProduto(string nome, double preco, int quantidade);
void removerProduto(int idProduto);
void editarProduto(int idProduto, string nome, double preco, int quantidade);
void adicionarStock(int idProduto, int quantidade);
void removerStock(int idProduto, int quantidade);
void listarProdutos();
string* encontrarProduto(int idProduto);

#endif
