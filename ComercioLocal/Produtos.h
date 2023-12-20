#ifndef PRODUTOS_H
#define PRODUTOS_H

#include <string>

using namespace std;

string** adicionarProduto(string** produtos, int* quantidadeProdutos, int idProduto, string nome, float preco, int quantidade);
string** removerProduto(string** produtos, int* quantidadeProdutos, int idProduto);
void editarProduto(string** produtos, int* quantidadeProdutos, int idProduto, string nome, float preco, int quantidade);
void listarProdutos(string** produtos, int quantidadeProdutos);
string* encontrarProduto(string** produtos, int quantidadeProdutos, int idProduto);
void liberarMemoria(string** produtos, int quantidadeProdutos);

#endif // !PRODUTOS_H
