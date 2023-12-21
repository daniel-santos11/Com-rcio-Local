#include "logs.h"
#include "produtos.h"
#include "menus.h"
#include <iostream>
#include <string>

using namespace std;

//int main()
//{
//		int opcao = 0;
//
//		while (opcao != 9)
//		{
//		cout << "1 - Adicionar produto" << endl;
//		cout << "2 - Remover produto" << endl;
//		cout << "3 - Editar produto" << endl;
//		cout << "4 - Listar produtos" << endl;
//		cout << "5 - Efetuar nova compra" << endl;
//		cout << "Digite uma opcao: ";
//		cin >> opcao;
//
//		switch (opcao)
//		{
//		case 1:
//		{
//			string nome;
//			float preco;
//			int quantidade;
//
//			cout << "Digite o nome do produto: ";
//			cin >> nome;
//			cout << "Digite o preco do produto: ";
//			cin >> preco;
//			cout << "Digite a quantidade do produto: ";
//			cin >> quantidade;
//
//			adicionarProduto(nome, preco, quantidade);
//			break;
//		}
//		/*case 2:
//		{
//			int idProduto;
//
//			cout << "Digite o ID do produto: ";
//			cin >> idProduto;
//
//			produtos = removerProduto(produtos, &quantidadeProdutos, idProduto);
//			break;
//		}
//		case 3:
//		{
//			int idProduto;
//			string nome;
//			float preco;
//			int quantidade;
//
//			cout << "Digite o ID do produto: ";
//			cin >> idProduto;
//			cout << "Digite o nome do produto: ";
//			cin >> nome;
//			cout << "Digite o preco do produto: ";
//			cin >> preco;
//			cout << "Digite a quantidade do produto: ";
//			cin >> quantidade;
//
//			editarProduto(produtos, &quantidadeProdutos, idProduto, nome, preco, quantidade);
//			break;
//		}*/
//		case 4:
//		{
//			listarProdutos();
//			break;
//		}
//		//case 5: 
//		//{
//		//	int codProduto, tam = 0;
//		//	string** carrinho = new string* [100];
//		//	do
//		//	{
//		//		int qtd;
//		//		cout << "insira o codigo do produto: (insira 0 se desejar terminar a compra)" << endl;
//		//		cin >> codProduto;
//		//		string* produto = encontrarProduto(quantidadeProdutos, codProduto);
//		//		if (produto == NULL)
//		//		{
//		//			cout << "o produto nao existe." << endl;
//		//			continue;
//		//		}
//		//		cout << "insira a quantidade que deseja deste produto: ";
//		//		cin >> qtd;
//		//		if (qtd > stoi(produto[3]))
//		//		{
//		//			cout << "a quantidade em stock deste produto é : " << produto[3];
//		//			continue;
//		//		}
//		//		carrinho[tam] = new string[4];
//		//		carrinho[tam][0] = produto[0];
//		//		carrinho[tam][1] = produto[1];
//		//		carrinho[tam][2] = produto[2];
//		//		carrinho[tam][3] = to_string(qtd);
//		//		tam++;
//		//	} while (codProduto != 0);
//		//	int nif;
//		//	cout << "insira o seu numero de contribuinte: ";
//		//	cin >> nif;
//		//	double valorTotal = 0;
//		//	for (int i = 0; i < tam; i++)
//		//	{
//		//		int qtd = stoi(carrinho[i][3]);
//		//		double preco = stod(carrinho[i][2]);
//		//		double valorSiva = (preco * 1,30);
//		//		double valorIva = (valorSiva * 1,23);
//		//		double valorTP = valorSiva * qtd;
//		//		valorTotal = valorTotal + valorTP;
//		//		cout << carrinho[i][1] << endl;
//		//		cout << "Valor sem Iva: " << valorSiva << endl;
//		//		cout << "Valor com Iva: " << valorIva << endl;
//		//		cout << "Valor total do produto: " << valorTP << endl;
//		//	}
//		//	cout << valorTotal << endl;
//		//	double valorDado;
//		//	cout << "insira o valor dado: ";
//		//	cin >> valorDado;
//		//	double troco = valorDado - valorTotal;
//		//	cout << "o troco e: " << troco;
//		//	time_t tempo = time(0); //verificar mais tarde
//		//	cout << tempo;
//		//
//		//	
//		//		break;
//		//}
//		default:
//			cout << "Opcao invalida!" << endl;
//			break;
//		}
//	}
//
//	return 0;	
//}


int main(void)
{
	bootstrap();
	menuPrincipal();
	return 0;
}