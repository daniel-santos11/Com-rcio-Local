#include "logs.h"
#include "produtos.h"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

static const size_t TAMANHO_PRODUTO = 4;
static const size_t MAX_PRODUTOS = 250;
static string** produtos = new string * [MAX_PRODUTOS];
static int quantidadeProdutos = 0;
static int idProduto = 1;

void adicionarProduto(string nome, double preco, int quantidade)
{
	produtos[quantidadeProdutos] = new string[4];
	produtos[quantidadeProdutos][0] = to_string(idProduto);
	produtos[quantidadeProdutos][1] = nome;
	produtos[quantidadeProdutos][2] = to_string(preco);
	produtos[quantidadeProdutos][3] = to_string(quantidade);

	quantidadeProdutos++;
	idProduto++;
	logSucesso("Produto com o ID " + to_string(idProduto) + " adicionado com sucesso!");
}

void removerProduto(int idProduto)
{
	for (int i = 0; i < quantidadeProdutos; i++)
	{
		if (produtos[i][0] == to_string(idProduto))
		{
			delete[] produtos[i];
			for (int j = i; j < quantidadeProdutos - 1; j++)
			{
				produtos[j] = produtos[j + 1];
			}
			quantidadeProdutos--;
			logSucesso("Produto com o ID " + to_string(idProduto) + " removido com sucesso!");
			return;
		}
	}

	logErro("Produto com o ID " + to_string(idProduto) + " nao encontrado!");
}



void editarProduto(int idProduto, string nome, double preco, int quantidade)
{
	for (int i = 0; i < quantidadeProdutos; i++)
	{
		if (produtos[i][0] == to_string(idProduto))
		{
			produtos[i][1] = nome;
			produtos[i][2] = to_string(preco);
			produtos[i][3] = to_string(quantidade);
			logSucesso("Produto com o ID " + to_string(idProduto) + " editado com sucesso!");
			return;
		}
	}

	logErro("Produto com o ID " + to_string(idProduto) + " nao encontrado!");

}

string* encontrarProduto(int idProduto)
{
	for (int i = 0; i < quantidadeProdutos; i++)
	{
		if (produtos[i][0] == to_string(idProduto))
		{
			return produtos[i];
		}
	}
	return NULL;
}

void adicionarStock(int idProduto, int quantidade)
{
	string* produto = encontrarProduto(idProduto);
	if (!produto)
	{
		logErro("Produto com o ID " + to_string(idProduto) + " nao encontrado!");
		return;
	}
	editarProduto(idProduto, produto[1], stod(produto[2]), stoi(produto[3]) + quantidade);
}

void removerStock(int idProduto, int quantidade)
{
	string* produto = encontrarProduto(idProduto);
	if (produto == NULL)
	{
		logErro("Produto com o ID " + to_string(idProduto) + " nao encontrado!");
		return;
	}
	int qtd = stoi(produto[3]);
	if (qtd < quantidade)
	{
		logErro("Quantidade de stock insuficiente no produto com o ID " + to_string(idProduto) + "!");
		return;
	}
	editarProduto(idProduto, produto[1], stod(produto[2]), qtd - quantidade);
}

void listarProdutos()
{
	cout << "ID\tNome\t\t\tPreco\tQuantidade" << endl;

	for (int i = 0; i < quantidadeProdutos; i++)
	{
		cout << setw(5) << setfill('0') << produtos[i][0] << "\t";
		cout << produtos[i][1].insert(produtos[i][1].size(), 16 - produtos[i][1].size(), ' ') << "\t";
		cout << (ceil(100 * stod(produtos[i][2])) / 100) * 1.30 << "\t";
		cout << produtos[i][3] << endl;
	}
	cout << endl << "Total: " << quantidadeProdutos << " produtos distintos" << endl;

}