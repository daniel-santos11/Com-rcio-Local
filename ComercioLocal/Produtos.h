#ifndef PRODUTOS_H
#define PRODUTOS_H

#include <string>


using namespace std;

typedef struct {
    int id;
    string nome;
    double precoCompra;
    double precoVenda;
    double precoVendaIVA;
    int quantidade;
    int quantidadeEmCarrinho;
} TProduto;

void adicionarProduto(string nome, double preco, int quantidade);

bool removerProduto(int idProduto);

bool editarProduto(int idProduto, const string &nome, double preco, int quantidade);

void adicionarStock(int idProduto, int quantidade);

void removerStock(int idProduto, int quantidade);

void atualizarPreco(int idProduto, double preco);

TProduto *traduzirTabela(bool compra);

void listarProdutos();

string *encontrarProduto(int idProduto);

bool nomeExiste(const string &n);

int qtdProdutos();

bool possivelAdicionar();

#endif
