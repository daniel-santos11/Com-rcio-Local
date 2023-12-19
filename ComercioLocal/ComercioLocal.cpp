#include <iostream>
#include <string>

using namespace std;

class Produtos
{
private:
	string **listaProdutos;
	size_t tamanho;
	unsigned int proximoID;

	string *criarProduto(string idProduto, string nome, string preco, string stock)
	{
		string *produto = new string[4];
		produto[0] = idProduto;
		produto[1] = nome;
		produto[2] = preco;
		produto[3] = stock;
		return produto;
	}

public:
	Produtos()
	{
		tamanho = 0;
		proximoID = 0;
		listaProdutos = new string *[tamanho];
	}

	void adicionarProduto(string idProduto, string nome, string preco, string stock)
	{
		string **novaListaProdutos = new string *[tamanho + 1];
		for (int i = 0; i < tamanho; i++)
			novaListaProdutos[i] = listaProdutos[i];

		novaListaProdutos[tamanho] = criarProduto(idProduto, nome, preco, stock);

		tamanho++;
		proximoID++;

		delete[] listaProdutos;
		listaProdutos = novaListaProdutos;
	}

	void removerProduto(string idProduto)
	{
		if (!idAtribuido(idProduto))
		{
			cout << "Produto nao encontrado" << endl;
			return;
		}
		string **novaListaProdutos = new string *[tamanho - 1];
		bool encontrado = false;
		for (int i = 0; i < tamanho; i++)
			if (listaProdutos[i][0] == idProduto)
				encontrado = true;
			else if (encontrado)
				novaListaProdutos[i - 1] = listaProdutos[i];
			else
				novaListaProdutos[i] = listaProdutos[i];

		delete[] listaProdutos;
		listaProdutos = novaListaProdutos;
		tamanho--;
	}

	void atualizarStock(string idProduto, string quantidade)
	{
		for (int i = 0; i < tamanho; i++)
			if (listaProdutos[i][0] == idProduto)
			{
				listaProdutos[i][3] = quantidade;
				cout << "O produto com o ID " << idProduto << " foi atualizado." << endl;
				return;
			}

		cout << "Produto nao encontrado" << endl;
	}

	string *encontrarProduto(string idProduto)
	{
		for (int i = 0; i < tamanho; i++)
			if (listaProdutos[i][0] == idProduto)
				return listaProdutos[i];
		return NULL;
	}

	bool idAtribuido(string idProduto)
	{
		string *p = encontrarProduto(idProduto);
		if (p != NULL)
			return true;
		return false;
	}

	void listarProdutos()
	{
		for (int i = 0; i < tamanho; i++)
			cout << listaProdutos[i][0] << " " << listaProdutos[i][1] << " " << listaProdutos[i][2] << " " << listaProdutos[i][3] << endl;
	}
};

class Carrinho
{
private:
	string **listaDeCompras;
	size_t tamanho;
	Produtos *produtos;

public:
	Carrinho(Produtos *produtos)
	{
		tamanho = 0;
		listaDeCompras = new string *[tamanho];
		produtos = produtos;
	}

	void adicionarProduto(string idProduto, string quantidade)
	{
		if (!produtos->idAtribuido(idProduto))
		{
			cout << "Produto nao encontrado" << endl;
			return;
		}
		string **novaListaDeCompras = new string *[tamanho + 1];
		for (int i = 0; i < tamanho; i++)
			novaListaDeCompras[i] = listaDeCompras[i];

		novaListaDeCompras[tamanho] = produtos->encontrarProduto(idProduto);
		novaListaDeCompras[tamanho][3] = quantidade;

		tamanho++;

		delete[] listaDeCompras;
		listaDeCompras = novaListaDeCompras;
	}

	void removerProduto(string idProduto)
	{
		if (!produtos->idAtribuido(idProduto))
		{
			cout << "Produto nao encontrado" << endl;
			return;
		}
		string **novaListaDeCompras = new string *[tamanho - 1];
		bool encontrado = false;
		for (int i = 0; i < tamanho; i++)
			if (listaDeCompras[i][0] == idProduto)
				encontrado = true;
			else if (encontrado)
				novaListaDeCompras[i - 1] = listaDeCompras[i];
			else
				novaListaDeCompras[i] = listaDeCompras[i];

		delete[] listaDeCompras;
		listaDeCompras = novaListaDeCompras;
		tamanho--;
	}

	void terminarCompra()
	{
		for (int i = 0; i < tamanho; i++)
		{
			string *produto = produtos->encontrarProduto(listaDeCompras[i][0]);
			produtos->atualizarStock(produto[0], to_string(stoi(produto[3]) - stoi(listaDeCompras[i][3])));
		}
	}
};

class Compra
{
private:
	Carrinho carrinho;
	string nCliente;
	string nFatura;

	double valorEntregue;
	double troco;

private:
	void imprimirFatura();
};

int main()
{
	Produtos produtos = Produtos();

	produtos.adicionarProduto("1", "Arroz", "12.00", "10");
	produtos.adicionarProduto("2", "Feijao", "12.00", "10");
	produtos.adicionarProduto("3", "Macarrao", "12.00", "10");

	produtos.listarProdutos();

	string *p = produtos.encontrarProduto("1");
	if (p != NULL)
		cout << "Produto encontrado: " << p[0] << " " << p[1] << " " << p[2] << " " << p[3] << endl;
	else
		cout << ("Produto nao encontrado\n");

	produtos.atualizarStock("1", "5");
	p = produtos.encontrarProduto("1");
	if (p != NULL)
		cout << "Produto encontrado: " << p[0] << " " << p[1] << " " << p[2] << " " << p[3] << endl;
	else
		cout << ("Produto nao encontrado\n");

	produtos.removerProduto("1");
	p = produtos.encontrarProduto("1");
	if (p != NULL)
		cout << "Produto encontrado: " << p[0] << " " << p[1] << " " << p[2] << " " << p[3] << endl;
	else
		cout << ("Produto nao encontrado\n");

	produtos.listarProdutos(); 
}
