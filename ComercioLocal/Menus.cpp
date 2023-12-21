#include "menus.h"
#include "logs.h"
#include "produtos.h"
#include <iostream>
#include <string>



using namespace std;

void menuPrincipal() {
	bootstrap();
	char opcao;
	do {
		system("cls");
		logTitulo("Menu Principal");
		cout << "1. Adicionar produto" << endl;
		cout << "2. Remover produto" << endl;
		cout << "3. Comprar produto" << endl;
		cout << "4. Listar produtos" << endl;
		cout << "5. Iniciar compra" << endl;
		cout << "0. Sair" << endl;

		cout << "Escolha uma opcao: ";
		cin >> opcao;

		switch (opcao)
		{
		case '1':
			menuAdicionarProduto();
			break;
		case '2':
			menuRemoverProduto();
			break;
			//case 3:
			//	comprarProduto();
			//	break;
		case '4':
			menuListarProdutos();
			break;
			/*case 5:
				iniciarCompra();
				break;*/
		case '0':
			return;
		default:
			system("cls");
			logErro("Opcao invalida!");
			
			break;
		}
	} while (opcao != 0);
}

void menuAdicionarProduto()
{
	system("cls");
	logTitulo("Menu Principal");
	string nome;
	string sPreco;
	string sQuantidade;

	do
	{
		cout << "Digite o nome do produto: ";
		cin >> nome;
		if (nome.size() > 30)
		{
			logErro("Nome do produto nao pode ter mais de 30 caracteres!");
		}
	} while (nome.size() > 30);

	do
	{
		cout << "Digite o preco do produto: ";
		cin >> sPreco;
		if (!isDouble(sPreco))
		{
			logErro("Preco do produto invalido!");
		}
	} while (!isDouble(sPreco));

	do
	{
		cout << "Digite a quantidade do produto: ";
		cin >> sQuantidade;
		if (!isPosInt(sQuantidade))
		{
			logErro("Quantidade do produto invalida!");
		}

	} while (!isPosInt(sQuantidade));

	adicionarProduto(nome, stod(sPreco), stoi(sQuantidade));
}

void menuRemoverProduto()
{
	system("cls");
	logTitulo("Remover Produto");

	listarProdutos();

	string id;


	cout << endl << "Digite o id do produto: ";
	cin >> id;
	if (!isPosInt(id))
		logErro("Id do produto invalido!");
	else
		removerProduto(stoi(id));
}


void menuListarProdutos()
{
	system("cls");
	logTitulo("Lista de Produtos");
	listarProdutos();


	char sair;
	do
	{
		cout << endl << "Pressione 0 para voltar ao menu principal: ";
		cin >> sair;
		cout << endl;
	} while (sair != '0');


}

bool isPosInt(string s)
{
	for (int i = 0; i < s.length(); i++)
		if (isdigit(s[i]) == false)
			return false;

	return true;
}

bool isDouble(string s)
{
	int pontos = 0;
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] == '.')
			pontos++;
		else if (isdigit(s[i]) == false)
			return false;
	}

	if (pontos > 1)
		return false;

	return true;
}




void bootstrap() {
	adicionarProduto("Coca-Cola", 1.5, 10);
	adicionarProduto("Pepsi", 1.5, 150);
	adicionarProduto("Fanta", 1.5, 200);
	adicionarProduto("Sprite", 1.5, 10);
	adicionarProduto("7Up", 1.5, 10);
	adicionarProduto("Sumol", 1.5, 10);
	adicionarProduto("Agua", 1, 10);
	adicionarProduto("Ice Tea", 1.5, 10);
	adicionarProduto("Red Bull", 2, 10);
	adicionarProduto("Monster", 2, 10);
	ativarLog();
}