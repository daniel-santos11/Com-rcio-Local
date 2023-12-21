#include "logs.h"
#include "produtos.h"
#include <iostream>
#include <string>

using namespace std;

string** adicionarProduto(string** produtos, int* quantidadeProdutos, int idProduto, string nome, float preco, int quantidade)
{
	string** produtosNovos = new string *[(*quantidadeProdutos) + 1];

	for (int i = 0; i < *quantidadeProdutos; i++)
		produtosNovos[i] = produtos[i];

		produtosNovos[*quantidadeProdutos] = new string[4];
		produtosNovos[*quantidadeProdutos][0] = to_string(idProduto);
		produtosNovos[*quantidadeProdutos][1] = nome;
		produtosNovos[*quantidadeProdutos][2] = to_string(preco);
		produtosNovos[*quantidadeProdutos][3] = to_string(quantidade);

	liberarMemoria(produtos, *quantidadeProdutos);
	*quantidadeProdutos += 1;
	logSucesso("Produto com o ID " + to_string(idProduto) + " adicionado com sucesso!");
	return produtosNovos;
}

string** removerProduto(string** produtos, int* quantidadeProdutos, int idProduto)
{
	if (encontrarProduto(produtos, *quantidadeProdutos, idProduto) == NULL)
	{
		logErro("Produto com o ID " + to_string(idProduto) + " nao encontrado!");
		return produtos;
	}

	string **produtosNovos = new string*[*quantidadeProdutos - 1];

}

void editarProduto(string** produtos, int* quantidadeProdutos, int idProduto, string nome, float preco, int quantidade)
{
	for (int i = 0; i < *quantidadeProdutos; i++)
	{
		if (produtos[i][0] == to_string(idProduto))
		{
			produtos[i][1] = nome;
			produtos[i][2] = to_string(preco);
			produtos[i][3] = to_string(quantidade);

		}
	}
}

void atualizarStock(string** produtos, int* quantidadeProdutos, int idProduto, int quantidade)
{
	string * produto = encontrarProduto(produtos, *quantidadeProdutos, idProduto);
	editarProduto(produtos, quantidadeProdutos, idProduto, produto[1], stof(produto[2]), stoi(produto[3]) + quantidade);
}

void listarProdutos(string** produtos, int quantidadeProdutos)
{
	cout << "ID\tNome\tPreco\tQuantidade" << endl;

	for (int i = 0; i < quantidadeProdutos; i++)
	{
		cout << produtos[i][0] << "\t" << produtos[i][1] << "\t" << produtos[i][2] << "\t" << produtos[i][3] << endl;
	}
	cout << "Total: " << quantidadeProdutos << endl;

}

string* encontrarProduto(string** produtos, int quantidadeProdutos, int idProduto)
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

void liberarMemoria(string** produtos, int quantidadeProdutos)
{
	for (int i = 0; i < quantidadeProdutos; i++)
		delete[] produtos[i];

	delete[] produtos;
}