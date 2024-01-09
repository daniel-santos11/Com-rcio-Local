#include "logs.h"
#include "produtos.h"
#include "carrinhos.h"

#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <ctime>

using namespace std;

static const unsigned int MAX_PRODUTOS_CARRINHO = 1;
static int nfatura = 0;
static string **carrinho = new string *[MAX_PRODUTOS_CARRINHO];
static int tamanhoCarrinho = 0;


bool adicionarProdutoCarrinho(int idProduto, int qtd) {
    string *produto = encontrarProduto(idProduto);
    if (produto == nullptr) {
        logErro("O Produto com o ID " + to_string(idProduto) + " nao existe");
        return false;
    }

    int posicao = encontrarProdutoCarrinho(stoi(produto[0]));

    if (posicao >= 0) {
        int novoTamanho = stoi(carrinho[posicao][1]) + qtd;
        if (novoTamanho > stoi(produto[3])) {
            logErro("O produto  com o ID " + produto[0] + " apenas tem " + produto[3] + " unidades em stock!");
            return false;
        }
        carrinho[posicao][1] = to_string(novoTamanho);
        logSucesso("O produto  com o ID " + produto[0] + " atualizado no carrinho");
    } else {
        if (carrinhoCheio())
        {
            logErro("Nao e possivel adicionar mais produtos ao carrinho");
            return false;
        }
        if (qtd > stoi(produto[3])) {
            logErro("O produto " + produto[0] + " apenas tem " + produto[3] + " unidades em stock!");
            return false;
        }
        carrinho[tamanhoCarrinho] = new string[2];
        carrinho[tamanhoCarrinho][0] = produto[0];
        carrinho[tamanhoCarrinho][1] = to_string(qtd);
        tamanhoCarrinho++;

        logSucesso("O produto  com o ID " + produto[0] + " adicionado ao carrinho");
    }
    return true;
}

TProduto *traduzCarrinho() {
    TProduto *produtosTraduzidos = traduzirTabela(true);
    int qtdProd = qtdProdutos();

    TProduto *carrinhoTraduzido = new TProduto[tamanhoCarrinho];
    for (int i = 0; i < tamanhoCarrinho; i++) {
        for (int j = 0; j < qtdProd; j++) {
            if (produtosTraduzidos[j].id == stoi(carrinho[i][0])) {
                carrinhoTraduzido[i].id = produtosTraduzidos[j].id;
                carrinhoTraduzido[i].nome = produtosTraduzidos[j].nome;
                carrinhoTraduzido[i].precoCompra = -1;
                carrinhoTraduzido[i].precoVenda = produtosTraduzidos[j].precoVenda;
                carrinhoTraduzido[i].precoVendaIVA = produtosTraduzidos[j].precoVendaIVA;
                carrinhoTraduzido[i].quantidade = -1;
                carrinhoTraduzido[i].quantidadeEmCarrinho = stoi(carrinho[i][1]);

            }
        }
    }
    return carrinhoTraduzido;
}

double calcularTotaisCarrinho() {
    if (tamanhoCarrinho == 0) {
        logInfo("O carrinho esta vazio", true);
        return 0;
    }
    double valorSemIVA = 0;
    double valorTotal = 0;
    TProduto *carrinhoTraduzido = traduzCarrinho();
    for (int i = 0; i < tamanhoCarrinho; i++) {
        valorSemIVA += carrinhoTraduzido[i].precoVenda * carrinhoTraduzido[i].quantidadeEmCarrinho;
        valorTotal += carrinhoTraduzido[i].precoVendaIVA * carrinhoTraduzido[i].quantidadeEmCarrinho;
    }

    logTitulo("Carrinho");
    logTabela(carrinhoTraduzido, tamanhoCarrinho);

    cout << setprecision(2) << fixed;
    cout << endl << "Valor sem IVA: " << valorSemIVA << endl;
    cout << "Valor com IVA: " << valorTotal << endl << endl;
    return valorTotal;
}

int encontrarProdutoCarrinho(int idProduto) {
    for (int i = 0; i < tamanhoCarrinho; i++) {
        if (stoi(carrinho[i][0]) == idProduto) {
            return i;
        }
    }
    return -1;
}

bool sortearCompra() {
    int sorteio = rand() % 100 + 1;
    if (sorteio <= 20)
        return true;
    return false;
}

void imprimirFatura(double valorDado, int nif) {
    confirmarCompra();
    TProduto *carrinhoTraduzido = traduzCarrinho();
    logFatura(
            carrinhoTraduzido,
            tamanhoCarrinho,
            valorDado,
            nif,
            ++nfatura
    );

}

void mostrarListaProdutosCarrinho() {
    TProduto *produtosTraduzidos = traduzirTabela(true);
    int qtdProd = qtdProdutos();

    for (int i = 0; i < tamanhoCarrinho; i++) {
        for (int j = 0; j < qtdProd; j++) {
            if (produtosTraduzidos[j].id == stoi(carrinho[i][0])) {
                produtosTraduzidos[j].quantidadeEmCarrinho = stoi(carrinho[i][1]);
                produtosTraduzidos[j].quantidade = produtosTraduzidos[j].quantidade - stoi(carrinho[i][1]);
            }
        }
    }
    logTabela(produtosTraduzidos, qtdProd);
}

void confirmarCompra() {
    for (int i = 0; i < tamanhoCarrinho; i++)
        removerStock(stoi(carrinho[i][0]), stoi(carrinho[i][1]));
}

void resetCarrinho() {
    do {
        delete[] carrinho[--tamanhoCarrinho];
    } while (tamanhoCarrinho != 0);
}

bool produtosNoCarrinho() {
    return tamanhoCarrinho > 0;
}

bool carrinhoCheio() {
	return tamanhoCarrinho >= MAX_PRODUTOS_CARRINHO;
}