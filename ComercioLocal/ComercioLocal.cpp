#include "logs.h"
#include "produtos.h"
#include <iostream>

using namespace std;

static string** produtos = new string*[0];
static int quantidadeProdutos = 0;

static unsigned int idProduto = 0;

int main()
{
		int opcao = 0;

		while (opcao != 5)
		{
		cout << "1 - Adicionar produto" << endl;
		cout << "2 - Remover produto" << endl;
		cout << "3 - Editar produto" << endl;
		cout << "4 - Listar produtos" << endl;
		cout << "Digite uma opcao: ";
		cin >> opcao;

		switch (opcao)
		{
		case 1:
		{
			string nome;
			float preco;
			int quantidade;

			cout << "Digite o nome do produto: ";
			cin >> nome;
			cout << "Digite o preco do produto: ";
			cin >> preco;
			cout << "Digite a quantidade do produto: ";
			cin >> quantidade;

			produtos = adicionarProduto(produtos, &quantidadeProdutos, idProduto, nome, preco, quantidade);
			idProduto++;
			break;
		}
		case 2:
		{
			int idProduto;

			cout << "Digite o ID do produto: ";
			cin >> idProduto;

			produtos = removerProduto(produtos, &quantidadeProdutos, idProduto);
			break;
		}
		case 3:
		{
			int idProduto;
			string nome;
			float preco;
			int quantidade;

			cout << "Digite o ID do produto: ";
			cin >> idProduto;
			cout << "Digite o nome do produto: ";
			cin >> nome;
			cout << "Digite o preco do produto: ";
			cin >> preco;
			cout << "Digite a quantidade do produto: ";
			cin >> quantidade;

			editarProduto(produtos, &quantidadeProdutos, idProduto, nome, preco, quantidade);
			break;
		}
		case 4:
		{
			listarProdutos(produtos, quantidadeProdutos);
			break;
		}
		default:
			cout << "Opcao invalida!" << endl;
			break;
		}
	}

	return 0;	
}