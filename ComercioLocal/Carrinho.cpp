#include "menus.h"
#include "logs.h"
#include "produtos.h"
#include "carrinhos.h"
#include <iostream>
#include <string>
#include <math.h>
#include <iomanip>



using namespace std;

// nfatura => autoincremento
static const unsigned int MAX_PRODUTOS_CARRINHO = 100;
double MARIGIN_LUCRO = 1.30;
double IVA = 1.23;
static int nfatura = 0;
static string** carrinho = new string * [MAX_PRODUTOS_CARRINHO];
static int tamanhoCarrinho = 0;


void adicionarProdutoCarrinho(int idProduto, int qtd) {
	string* produto = encontrarProduto(idProduto);
	if (produto == NULL) {
		logErro("O Produto com o ID " + to_string(idProduto) + " nao existe");
		return;
	}

	int posicao = encontrarProdutoCarrinho(stoi(produto[0]));

	if (posicao >= 0)
	{
		int novoTamanho = stoi(carrinho[posicao][3]) + qtd;
		if (novoTamanho > stoi(produto[3])) {
			logErro("Nao ha stock suficiente para adicionar " + to_string(qtd) + " unidades do produto " + produto[0]);
			return;
		}
		carrinho[posicao][3] = to_string(novoTamanho);
		return;
	}
	else
	{
		if (qtd > stoi(produto[3])) {
			logErro("Nao ha stock suficiente para adicionar " + to_string(qtd) + " unidades do produto " + produto[0]);
			return;
		}
		carrinho[tamanhoCarrinho] = new string[4];
		carrinho[tamanhoCarrinho][0] = produto[0];
		carrinho[tamanhoCarrinho][1] = produto[1];
		carrinho[tamanhoCarrinho][2] = to_string(ceil((stod(produto[2]) * MARIGIN_LUCRO) * 100) / 100);
		carrinho[tamanhoCarrinho][3] = to_string(qtd);
		tamanhoCarrinho++;

		logSucesso("Produto " + produto[0] + " adicionado ao carrinho");
	}

}


double  calcularTotaisCarrinho() {
	if (tamanhoCarrinho == 0) {
		logInfo("O carrinho esta vazio");
		return 0;
	}
	double valorTotal = 0;
	cout << setprecision(2) << fixed;
	for (int i = 0; i < tamanhoCarrinho; i++)
	{
		cout << carrinho[i][0] << ": " << carrinho[i][1] << endl;
		int qtd = stoi(carrinho[i][3]);
		cout << "Quantidade: \t" << qtd << endl;
		double preco = stod(carrinho[i][2]);
		cout << "Preco s/Iva:\t" << preco << " /uni\t" << preco * qtd << endl;
		double valorIva = ceil((preco * IVA) * 100) / 100;
		cout << "Preco c/Iva:\t" << valorIva << " /uni\t" << valorIva * qtd << endl;

		valorTotal += valorIva * qtd;

		if (i < tamanhoCarrinho - 1) {
			cout << "-----------------------------------" << endl;
		}
		else
		{
			cout << "/***********************************/" << endl;
			cout << "Valor a Pagar: \t\t" << valorTotal << endl;
		}
	}
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
	if (sorteio <= 10)
		return true;
	return false;
}

void imprimirFatura(double valorDado, int nif)
{
	confirmarCompra();
	system("cls");
	cout << "/***********************************/" << endl; 
	cout << "/************* Fatura **************/" << endl;
	cout << "/***********************************/" << endl << endl;

	cout << "Data: " << time(0) << endl;
	cout << "NIF: " << nif << endl;
	cout << "N. Fatura: " << nfatura++ << endl;
	cout << "Detalhe: " << endl;

	double valorTotal = calcularTotaisCarrinho();

	if (valorDado == 0)
	{
		cout << "Desconto: " << valorTotal << endl;
		cout << "Troco: " << 0 << endl;
		cout << "Obrigado pela sua preferencia!" << endl;
		cout << "/***********************************/" << endl;
		return;
	}

	double troco = valorDado - valorTotal;

	cout << "Valor recebido: " << valorDado << endl;
	cout << setprecision(2) << fixed;
	cout << "O troco: " << troco << endl;
	cout << "Obrigado pela sua preferencia!" << endl;
	cout << "/***********************************/" << endl;
}

void confirmarCompra() {
	for (int i = 0; i < tamanhoCarrinho; i++) {
		removerStock(stoi(carrinho[i][0]), stoi(carrinho[i][3]));
	
	}
}

void resetCarrinho() {
	do {
		delete[] carrinho[--tamanhoCarrinho];
	} while (tamanhoCarrinho != 0);
}