#include "menus.h"
#include "logs.h"
#include "produtos.h"
#include "carrinhos.h"
#include <iostream>
#include <string>
#include <conio.h>

using namespace std;

const size_t MENU_PRINCIPAL_TAMANHO = 5;
const string *opcoesMenuPrincipal = new string[MENU_PRINCIPAL_TAMANHO]{
        "Adicionar produto",
        "Remover produto",
        "Adicionar Stock",
        "Listar produtos",
        "Iniciar compra",
};

char selecionarMenuPrincipal() {
    char opcao;
    bool opcaoValida = false;

    do {
        opcao = (char) _getch();

        switch (opcao) {
            case '1':
                opcaoValida = true;
                menuAdicionarProduto();
                break;
            case '2':
                opcaoValida = true;
                menuRemoverProduto();
                break;
            case '3':
                opcaoValida = true;
                atualizarStock();
                break;
            case '4':
                opcaoValida = true;
                menuListarProdutos();
                break;
            case '5':
                opcaoValida = true;
                iniciarCompra();
                break;
            case '0':
                opcaoValida = true;
                logInfo("Ate a proxima!", true);
                break;
            default:
                logErro("Opcao invalida!");
                break;
        }
    } while (!opcaoValida);
    return opcao;
}

void menuPrincipal() {
    char opcao;
    do {
        logMarca();
        logMenu(opcoesMenuPrincipal, MENU_PRINCIPAL_TAMANHO);
        opcao = selecionarMenuPrincipal();
    } while (opcao != '0');
}

void menuAdicionarProduto() {
    logTitulo("Adicionar Produto");
    string nome = pedirValidarNome();
    if (nome.empty())
        return;

    double preco = pedirValidarValor("Qual o preco de compra do produto?", 0);
    if (preco == 0)
        return;

    int qtd = pedirValidarQtd("Qual a quantidade do produto");
    if (qtd == 0)
        return;

    cout << endl << "Tem a certeza que deseja adicionar o produto '" << nome << "' com o preco de custo " << preco
         << " e quantidade " << qtd << "? (s/n)" << endl;

    if (!pedirConfimacao()) {
        logInfo("Processo cancelado!", true);
        return;
    }
    adicionarProduto(nome, preco, qtd);
}

void menuRemoverProduto() {
    logTitulo("Remover Produto");
    listarProdutos();

    int id = pedirValidarIdProduto();
    if (id == 0)
        return;

    cout << "Tem a certeza que deseja remover o produto com o id " << id << "? (s/n)" << endl;
    if (!pedirConfimacao()) {
        logInfo("Processo cancelado!", true);
        return;
    }
    removerProduto(id);
}

void atualizarStock() {
    logTitulo("Atualizar Stock");
    listarProdutos();

    int id = pedirValidarIdProduto();
    if (id == 0)
        return;

    int qtd = pedirValidarQtd("Qual a quantidade do produto a adicionar");
    if (qtd == 0)
        return;

    cout << "Tem a certeza que deseja adicionar " << qtd << " unidades ao produto com o id " << id << "? (s/n)" << endl;
    if (!pedirConfimacao()) {
        logInfo("Processo cancelado!", true);
        return;
    }
    adicionarStock(id, qtd);

    cout << "Deseja atualizar o preco de compra? (s/n)" << endl;
    if (!pedirConfimacao()) {
        logInfo("Processo terminado!", true);
        return;
    }

    double preco = pedirValidarValor("Qual o novo preco de compra do produto?", 0);
    if (preco == 0)
        return;

    cout << "Tem a certeza que deseja atualizar o preco de compra do produto com o id " << id << " para " << preco
         << "? (s/n)" << endl;
    if (!pedirConfimacao()) {
        logInfo("Processo cancelado!", true);
        return;
    }
    atualizarPreco(id, preco);
    logInfo("Processo terminado!", true);
}

void iniciarCompra() {
    double total = 0;
    while (true) {
        logTitulo("Menu de Compra");
        mostrarListaProdutosCarrinho();
        
        int id = pedirValidarIdProduto();
        if (id == 0) {
            if (!produtosNoCarrinho()) return;
            else break;
        }

        int qtd;
        do {
            qtd = pedirValidarQtd("Quantas unidades deseja adicionar ao carrinho?");
            if (qtd == 0) {
                if (!produtosNoCarrinho()) return;
                else break;
            }
        } while (!adicionarProdutoCarrinho(id, qtd));


        logTitulo("Descritivo");
        total = calcularTotaisCarrinho();
        if (produtosNoCarrinho()) {
            cout << "Deseja adicionar mais produtos ao carrinho? (s/n)"
                 << endl;
            if (!pedirConfimacao())
                break;
        }
    }

    int nCliente = pedirValidarNumeroCliente();

    if (sortearCompra()) {
        logInfo("O cliente tem direito a um desconto de 100%!", true);
        imprimirFatura(0.0, nCliente);
    } else {
        double valorDado = pedirValidarValor("Qual o valor recebido do cliente?", total);
        if (valorDado > 0)
            imprimirFatura(valorDado, nCliente);
        else
            logInfo("Processo de compra cancelado!", true);
    }
    resetCarrinho();
    aguardarInputSaida();
}


void menuListarProdutos() {
    logTitulo("Lista de Produtos");
    listarProdutos();

    char sair;
    cout << endl << "Pressione 0 para voltar ao menu principal: " << endl;
    do {
        sair = (char) _getch();
        if (sair != '0')
            logErro("Opcao invalida!");
    } while (sair != '0');
}

bool isPosInt(const string &s) {
    for (char c: s) {
        if (!isdigit(c))
            return false;
    }
    return true;
}

bool isDouble(const string &s) {
    int pontos = 0;
    for (char c: s) {
        if (c == '.')
            pontos++;
        else if (isdigit(c) == false)
            return false;
    }

    if (pontos > 1)
        return false;

    return true;
}

bool validarCasaDecimais(const string &sDouble) {
    size_t pos = sDouble.find('.');
    if (pos == string::npos)
        return true;
    size_t tamanho = sDouble.substr(pos + 1).length();
    return tamanho > 0 && tamanho <= 2;
}

int pedirValidarIdProduto() {
    bool inputValido;
    string id;
    do {
        inputValido = true;
        cout << endl << "Qual o id do produto? (0 para sair): ";
        cin >> id;
        if (id == "0") {
            logInfo("Processo cancelado!", true);
            return 0;
        } else if (!isPosInt(id)) {
            logErro("Id do produto invalido!");
            inputValido = false;
        } else if (encontrarProduto(stoi(id)) == nullptr) {
            logErro("Produto com o id " + id + " nao encontrado!");
            inputValido = false;
        }
    } while (!inputValido);
    return stoi(id);
}

int pedirValidarQtd(const string &msg) {
    bool inputValido;
    string sQuantidade;

    do {
        inputValido = true;
        cout << msg << " (0 para sair): ";
        cin >> sQuantidade;
        if (sQuantidade == "0") {
            logInfo("Processo terminado!", true);
            return 0;
        } else if (!isPosInt(sQuantidade)) {
            logErro("A quantida so pode conter numeros!");
            inputValido = false;
        } else if (stoi(sQuantidade) < 0) {
            logErro("A quantidade do produto tem de ser superior a 0!");
            inputValido = false;
        }
    } while (!inputValido);

    return stoi(sQuantidade);
}

double pedirValidarValor(const string &msg, double min) {
    string sValor;
    bool inputValido;
    do {
        inputValido = true;
        cout << msg << " (0 para sair): ";
        cin >> sValor;
        if (sValor == "0") {
            logInfo("Processo cancelado!", true);
            return 0;
        } else if (!isDouble(sValor)) {
            logErro("O valor e invalido!");
            inputValido = false;
        } else if (!validarCasaDecimais(sValor)) {
            logErro("O valor so pode conter 2 casas decimais!");
            inputValido = false;
        } else if (stod(sValor) < min) {
            logErro(min == 0 ? "O valor tem de ser superior a 0!" :
                    "O valor tem de ser superior a " + doubleParaString(min) + "!");
            inputValido = false;
        }
    } while (!inputValido);

    return stod(sValor);
}

string pedirValidarNome() {
    string nome;
    bool inputValido;

    do {
        inputValido = true;
        cout << "Qual o nome do produto (0 para sair): ";
        getline(cin, nome);
        if (nome == "0") {
            logInfo("Processo cancelado!", true);
            return "";
        } else if (nome.size() > 30) {
            logErro("Nome do produto nao pode conter mais de 30 caracteres!");
            inputValido = false;
        } else if (nome.empty()) {
            logErro("Nome do produto nao pode ser vazio!");
            inputValido = false;
        } else if (nomeExiste(nome)) {
            logErro("Ja existe um produto com o nome '" + nome + "'! Pretende continuar? (s/n)");
            char opcao;
            do {
                opcao = (char) _getch();
                if (opcao == 's' || opcao == 'S') {
                    logInfo("Processo cancelado!", true);
                    break;
                } else if (opcao == 'n' || opcao == 'N') {
                    continue;
                } else {
                    logErro("Opcao invalida!");
                }
            } while (opcao != 'n' && opcao != 'N');
        }
    } while (!inputValido);
    return nome;
}

int pedirValidarNumeroCliente() {
    string nif;
    bool inputValido;
    do {
        inputValido = true;
        cout << "Insira o numero do cliente (NIF): ";
        cin >> nif;
        if (!isPosInt(nif)) {
            logErro("O Nif contem apenas numeros!");
            inputValido = false;
        } else if (nif.length() != 9) {
            logErro("O Nif tem de conter 9 digitos!");
            inputValido = false;
        }
    } while (!inputValido);
    return stoi(nif);
}

bool pedirConfimacao() {
    char opcao;
    do {
        opcao = (char) _getch();
        if (opcao == 's' || opcao == 'S')
            return true;
        else if (opcao != 'n' && opcao != 'N')
            logErro("Opcao invalida!");
    } while (opcao != 'n' && opcao != 'N');
    return false;
}

void aguardarInputSaida() {
    char sair;
    do {
        cout << endl << "Pressione 0 para voltar ao menu principal: ";
        sair = (char) _getch();
        cout << endl;
        if (sair != '0')
            logErro("Opcao invalida!");
    } while (sair != '0');
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