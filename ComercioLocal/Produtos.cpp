#include "logs.h"
#include "produtos.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <utility>

using namespace std;

static const size_t TAMANHO_PRODUTO = 4;
static const size_t MAX_PRODUTOS = 250;
static string **produtos = new string *[MAX_PRODUTOS];
static int quantidadeProdutos = 0;
static int idProximoProduto = 1;
static double MARIGIN_LUCRO = 1.30;
static double IVA = 1.23;


void adicionarProduto(string nome, double preco, int quantidade) {
    if (quantidadeProdutos >= MAX_PRODUTOS)
    {
        logErro("Nao possivel adicionar mais produtos");
        return;
    }

    produtos[quantidadeProdutos] = new string[TAMANHO_PRODUTO];
    produtos[quantidadeProdutos][0] = to_string(idProximoProduto);
    produtos[quantidadeProdutos][1] = std::move(nome);
    produtos[quantidadeProdutos][2] = to_string(round(preco * 100) / 100);
    produtos[quantidadeProdutos][3] = to_string(quantidade);

    quantidadeProdutos++;
    idProximoProduto++;
    logSucesso("O produto com o ID " + to_string(idProximoProduto) + " adicionado!");
}

bool removerProduto(int idProduto) {
    for (int i = 0; i < quantidadeProdutos; i++) {
        if (produtos[i][0] == to_string(idProduto)) {
            delete[] produtos[i];
            for (int j = i; j < quantidadeProdutos - 1; j++) {
                produtos[j] = produtos[j + 1];
            }
            quantidadeProdutos--;
            logSucesso("O produto com o ID " + to_string(idProduto) + " removido com sucesso!");
            return true;
        }
    }
    logErro("O produto com o ID " + to_string(idProduto) + " nao removido!");
    return false;
}


bool editarProduto(const int idProduto, const string &nome, const double preco, int quantidade) {
    for (int i = 0; i < quantidadeProdutos; i++) {
        if (produtos[i][0] == to_string(idProduto)) {
            produtos[i][1] = nome;
            produtos[i][2] = to_string(preco);
            produtos[i][3] = to_string(quantidade);
            return true;
        }
    }
    return false;
}

string *encontrarProduto(int idProduto) {
    for (int i = 0; i < quantidadeProdutos; i++) {
        if (produtos[i][0] == to_string(idProduto)) {
            return produtos[i];
        }
    }
    return nullptr;
}

void adicionarStock(int idProduto, int quantidade) {
    string *produto = encontrarProduto(idProduto);
    if (!produto) {
        logErro("O produto com o ID " + to_string(idProduto) + " nao encontrado!");
        return;
    }
    if (editarProduto(idProduto, produto[1], stod(produto[2]), stoi(produto[3]) + quantidade))
        logSucesso("O stock do produto com o ID " + to_string(idProduto) + " adicionado com sucesso!");
}

void removerStock(int idProduto, int quantidade) {
    string *produto = encontrarProduto(idProduto);
    if (produto == nullptr) {
        logErro("O produto com o ID " + to_string(idProduto) + " nao encontrado!");
        return;
    }
    int qtd = stoi(produto[3]);
    if (qtd < quantidade) {
        logErro("Quantidade de stock insuficiente no produto com o ID " + to_string(idProduto) + "!");
        return;
    }
    if (!editarProduto(idProduto, produto[1], stod(produto[2]), qtd - quantidade))
        logErro("O stock do produto com o ID " + to_string(idProduto) + " nao removido!");
}

void atualizarPreco(int idProduto, double preco) {
    string *produto = encontrarProduto(idProduto);
    if (produto == nullptr) {
        logErro("O produto com o ID " + to_string(idProduto) + " nao encontrado!");
        return;
    }
    if (editarProduto(idProduto, produto[1], preco, stoi(produto[3])))
        logSucesso("O preco do produto com o ID " + to_string(idProduto) + " atualizado com sucesso!");

}

TProduto *traduzirTabela(bool compra) {
    TProduto *produtosTraduzidos = new TProduto[quantidadeProdutos];
    for (int i = 0; i < quantidadeProdutos; i++) {
        produtosTraduzidos[i] = {
                stoi(produtos[i][0]),
                produtos[i][1],
                compra ? (double) -1 : stod(produtos[i][2]),
                stod(produtos[i][2]) * MARIGIN_LUCRO,
                (stod(produtos[i][2]) * MARIGIN_LUCRO) * IVA,
                stoi(produtos[i][3]),
                compra ? 0 : -1
        };
    }
    return produtosTraduzidos;

}

void listarProdutos() {
    TProduto *produtosTraduzidos = traduzirTabela(false);
    logTabela(produtosTraduzidos, quantidadeProdutos);
}

bool nomeExiste(const string &n) {
    for (int i = 0; i < quantidadeProdutos; i++) {
        if (produtos[i][1] == n) {
            return true;
        }
    }
    return false;
}

int qtdProdutos() {
    return quantidadeProdutos;
}