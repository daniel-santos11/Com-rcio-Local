#include "logs.h"
#include "produtos.h"
#include <iostream>
#include <string>

using namespace std;

static string** produtos = new string*[0];
static int quantidadeProdutos = 0;

static unsigned int idProduto = 1;

int main()
{
		int opcao = 0;

		while (opcao != 9)
		{
		cout << "1 - Adicionar produto" << endl;
		cout << "2 - Remover produto" << endl;
		cout << "3 - Editar produto" << endl;
		cout << "4 - Listar produtos" << endl;
		cout << "5 - Efetuar nova compra" << endl;
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
		case 5: 
		{
			int codProduto, tam = 0, qtd, nif;
			string** carrinho = new string* [100];
			do
			{
				cout << "insira o codigo do produto: (insira 0 se desejar terminar a compra)" << endl;
				cin >> codProduto;
				string* produto = encontrarProduto(produtos, quantidadeProdutos, codProduto);
				if (produto == NULL)
				{
					cout << "o produto nao existe." << endl;
					continue;
				}
				cout << "insira a quantidade que deseja deste produto: ";
				cin >> qtd;
				if (qtd > stoi(produto[3]))
				{
					cout << "a quantidade em stock deste produto é : " << produto[3];
					continue;
				}
				carrinho[tam] = new string[4];
				carrinho[tam][0] = produto[0];
				carrinho[tam][1] = produto[1];
				carrinho[tam][2] = produto[2];
				carrinho[tam][3] = to_string(qtd);
				tam++;
			} while (codProduto != 0);
			cout << "insira o seu numero de contribuinte: ";
			cin >> nif;
			
				break;
		}
		default:
			cout << "Opcao invalida!" << endl;
			break;
		}
	}

	return 0;	
}