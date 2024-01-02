#include <windows.h>
#include "logs.h"
#include "menus.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <thread>
#include <sstream>

using namespace std;

const int TAMANHO_TITULO = 50;

bool logAtivo = false;


enum Cores {
    PRETO = 0,
    AZUL = 1,
    VERDE = 2,
    AZUL_CLARO = 3,
    VERMELHO = 4,
    ROXO = 5,
    AMARELO = 6,
    BRANCO = 7,
    CINZENTO = 8,
    AZUL_ESCURO = 9,
    VERDE_CLARO = 10,
    AZUL_CLARO_CLARO = 11,
    VERMELHO_CLARO = 12,
    ROXO_CLARO = 13,
    AMARELO_CLARO = 14,
    BRANCO_CLARO = 15
};

enum TamanhosColunas {
    TAMANHO_ID = 8,
    TAMANHO_NOME = 20,
    TAMANHO_PRECO = 10,
    TAMANHO_QUANTIDADE = 10
};


void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD) color);
}

void resetColor() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Cores::BRANCO);
}

void printTag(const string &tag, WORD color) {
    setColor(color);
    cout << "[ " << tag << " ] ";
    resetColor();
    cout << " ";
}

void logMenu(const string *opcoes, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        setColor(Cores::ROXO);
        cout << i + 1 << ". ";
        resetColor();
        cout << opcoes[i] << endl;
    }
    setColor(Cores::ROXO);
    cout << "0. ";
    resetColor();
    cout << "Sair" << endl << endl;

    cout << "Escolha uma opcao (";
    setColor(Cores::ROXO);
    cout << "0 - " << tamanho;
    resetColor();
    cout << "): " << endl;

}

void logInfo(const string &message, bool esperar) {
    printTag("INFO", 11);
    cout << message << endl;
    if (esperar)
        espera();
    cout << endl;
}

void logErro(const string &message) {
    printTag("ERRO", 12);
    cout << message << endl;
}

void logAviso(const string &message) {
    printTag("AVISO", 14);
    cout << message << endl;
}

void logSucesso(const string &message) {
    printTag("SUCESSO", 10);
    cout << message << endl;
    espera();
}

void desenhaTitulo(const string &msg) {
    int side = ((TAMANHO_TITULO / 2) - (int) (msg.length() / 2)) - 2;
    setColor(Cores::AMARELO);
    cout << "/" << setfill('*') << setw(TAMANHO_TITULO) << "/" << endl << "/";
    for (int i = 0; i < side; i++)
        cout << "*";
    resetColor();
    cout << " " + msg + " ";
    setColor(Cores::AMARELO);
    if (msg.length() % 2 == 0)
        cout << " ";
    for (int i = 0; i < side; i++)
        cout << "*";
    cout << "/" << endl;
    cout << "/" << setfill('*') << setw(TAMANHO_TITULO) << "/" << endl;
    resetColor();
}

void logTitulo(const string &msg) {
    limparEcra();
    desenhaTitulo(msg);
    cout << endl;

}

void escreverCel(const string &cel, int tCelula) {
    if ((int) cel.length() > tCelula)
        cout << cel.substr(0, tCelula - 3) << "...";
    else cout << cel;
    for (int i = 0; i < tCelula - (int) cel.length(); i++)
        cout << " ";
}

void escreverCel(const int cel, int tCelula) {
    cout << cel;
    for (int i = 0; i < tCelula - (int) to_string(cel).length(); i++)
        cout << " ";
}

void escreverCel(const double cel, int tCelula) {
    cout << doubleParaString(cel);
    for (int i = 0; i < tCelula - (int) doubleParaString(cel).length(); i++)
        cout << " ";
}

void logPipe(int i) {
    if (i != 1 && i % 2 == 0)
        setColor(Cores::ROXO);
    else
        setColor(ROXO_CLARO);
    cout << "|";
    if (i != 1 && i % 2 == 0)
        setColor(Cores::AZUL_CLARO_CLARO);
    else
        setColor(Cores::BRANCO);
}

void logLinha(const TProduto &prod, int i) {

    logPipe(i);
    if (prod.id > 0) {
        escreverCel(prod.id, TamanhosColunas::TAMANHO_ID);
        logPipe(i);
    }
    if (!prod.nome.empty()) {
        escreverCel(prod.nome, TamanhosColunas::TAMANHO_NOME);
        logPipe(i);
    }
    if (prod.quantidade >= 0) {
        escreverCel(prod.quantidade, TamanhosColunas::TAMANHO_QUANTIDADE);
        logPipe(i);
    }
    if (prod.quantidadeEmCarrinho >= 0) {
        escreverCel(prod.quantidadeEmCarrinho, TamanhosColunas::TAMANHO_QUANTIDADE);
        logPipe(i);
    }
    if (prod.precoCompra > 0) {
        escreverCel(prod.precoCompra, TamanhosColunas::TAMANHO_PRECO);
        logPipe(i);
    }
    if (prod.precoVenda > 0) {
        escreverCel(prod.precoVenda, TamanhosColunas::TAMANHO_PRECO);
        logPipe(i);
    }
    if (prod.precoVendaIVA > 0) {
        escreverCel(prod.precoVendaIVA, TamanhosColunas::TAMANHO_PRECO);
        logPipe(i);
    }
    cout << endl;
    resetColor();
}

void logSeparador(const TProduto &prod) {
    setColor(Cores::ROXO);
    cout << "+";
    if (prod.id > 0) {
        for (int i = 0; i < TamanhosColunas::TAMANHO_ID; i++)
            cout << "-";
        cout << "+";
    }
    if (!prod.nome.empty()) {
        for (int i = 0; i < TamanhosColunas::TAMANHO_NOME; i++)
            cout << "-";
        cout << "+";
    }
    if (prod.quantidade >= 0) {
        for (int i = 0; i < TamanhosColunas::TAMANHO_QUANTIDADE; i++)
            cout << "-";
        cout << "+";
    }
    if (prod.quantidadeEmCarrinho >= 0) {
        for (int i = 0; i < TamanhosColunas::TAMANHO_QUANTIDADE; i++)
            cout << "-";
        cout << "+";
    }
    if (prod.precoCompra > 0) {
        for (int i = 0; i < TamanhosColunas::TAMANHO_PRECO; i++)
            cout << "-";
        cout << "+";
    }
    if (prod.precoVenda > 0) {
        for (int i = 0; i < TamanhosColunas::TAMANHO_PRECO; i++)
            cout << "-";
        cout << "+";
    }
    if (prod.precoVendaIVA > 0) {
        for (int i = 0; i < TamanhosColunas::TAMANHO_PRECO; i++)
            cout << "-";
        cout << "+";
    }
    cout << endl;
    resetColor();
}

void logCabecalho(const TProduto &prod) {
    setColor(Cores::ROXO);
    logSeparador(prod);
    logPipe(1);
    if (prod.id > 0) {
        escreverCel("ID", TamanhosColunas::TAMANHO_ID);
        logPipe(1);
    }
    if (!prod.nome.empty()) {
        escreverCel("Nome", TamanhosColunas::TAMANHO_NOME);
        logPipe(1);
    }
    if (prod.quantidade >= 0) {
        escreverCel("Stock", TamanhosColunas::TAMANHO_QUANTIDADE);
        logPipe(1);
    }
    if (prod.quantidadeEmCarrinho >= 0) {
        escreverCel("Carrinho", TamanhosColunas::TAMANHO_QUANTIDADE);
        logPipe(1);
    }
    if (prod.precoCompra > 0) {
        escreverCel("Custo", TamanhosColunas::TAMANHO_PRECO);
        logPipe(1);
    }
    if (prod.precoVenda > 0) {
        escreverCel("Preco sIVa", TamanhosColunas::TAMANHO_PRECO);
        logPipe(1);
    }
    if (prod.precoVendaIVA > 0) {
        escreverCel("Preco cIVA", TamanhosColunas::TAMANHO_PRECO);
        logPipe(1);
    }

    cout << endl;
    logSeparador(prod);
    resetColor();
}


void logTabela(const TProduto *produtos, int tamanho) {

    logCabecalho(produtos[0]);

    for (int i = 0; i < tamanho; i++)
        logLinha(produtos[i], i);
    logSeparador(produtos[0]);

    if (produtos[0].quantidadeEmCarrinho < 0)
        cout << endl << "Total de produtos: " << tamanho << endl << endl;
}

void logCaixaEsquerda() {
    setColor(Cores::AMARELO);
    cout << "/* ";
    resetColor();
}

void logCaixaDireita() {
    setColor(Cores::AMARELO);
    cout << " */";
    resetColor();
    cout << endl;
}

void logEspaco(int t) {
    for (int i = 0; i < t; i++)
        cout << " ";
}

void logProdFatSep() {
    setColor(Cores::AMARELO);
    logCaixaEsquerda();
    for (int i = 0; i < TAMANHO_TITULO - 5; i++)
        cout << "-";
    logCaixaDireita();
    resetColor();
}

void logFaturaProduto(const TProduto &produtos) {
    logCaixaEsquerda();
    cout << produtos.nome;
    logEspaco(TAMANHO_TITULO - 10 - (int) produtos.nome.length() -
              (int) to_string(produtos.quantidadeEmCarrinho).length());
    cout << "Qtd: " << produtos.quantidadeEmCarrinho;
    logCaixaDireita();

    logCaixaEsquerda();
    cout << produtos.precoVenda;
    logEspaco(TAMANHO_TITULO - 12 - (int) doubleParaString(produtos.precoVenda).length() -
              (int) doubleParaString(produtos.precoVenda * produtos.quantidadeEmCarrinho).length());
    cout << "s/Iva: " << setprecision(2) << fixed << produtos.precoVenda * produtos.quantidadeEmCarrinho;
    logCaixaDireita();


    logCaixaEsquerda();
    cout << produtos.precoVendaIVA;
    logEspaco(TAMANHO_TITULO - 12 - (int) doubleParaString(produtos.precoVendaIVA).length() -
              (int) doubleParaString(produtos.precoVendaIVA * produtos.quantidadeEmCarrinho).length());
    cout << "c/Iva: " << setprecision(2) << fixed << produtos.precoVendaIVA * produtos.quantidadeEmCarrinho;
    logCaixaDireita();

    logProdFatSep();
}

void logLinhaVazia() {
    logCaixaEsquerda();
    logEspaco(TAMANHO_TITULO - 5);
    logCaixaDireita();
}

void logFatura(const TProduto *produtos, int tamanho, double valorDado,
               int nif, int nFatura) {
    limparEcra();

    double valorTotal = 0, valorTotalIVA = 0;
    desenhaTitulo("24 Hrs Drinks");
    logLinhaVazia();

    logCaixaEsquerda();
    cout << "N. Fatura: " << nFatura;
    logEspaco(TAMANHO_TITULO - 22 - (int) to_string(nFatura).length() - (int) getTime().length());
    cout << "Data: " << getTime();
    logCaixaDireita();
    logCaixaEsquerda();
    cout << "NIF: " << nif;
    logEspaco(TAMANHO_TITULO - 9 - (int) to_string(nif).length() - (int) to_string(nFatura).length());
    logCaixaDireita();

    logLinhaVazia();

    logCaixaEsquerda();
    cout << "Detalhe: ";
    logEspaco(TAMANHO_TITULO - 14);
    logCaixaDireita();

    logProdFatSep();
    for (int i = 0; i < tamanho; i++) {
        valorTotal += produtos[i].precoVenda * produtos[i].quantidadeEmCarrinho;
        valorTotalIVA += produtos[i].precoVendaIVA * produtos[i].quantidadeEmCarrinho;
        logFaturaProduto(produtos[i]);
    }

    logLinhaVazia();

    logCaixaEsquerda();
    cout << "Total s/Iva: ";
    logEspaco(TAMANHO_TITULO - 18 - (int) doubleParaString(valorTotal).length());
    cout << setprecision(2) << fixed << valorTotal;
    logCaixaDireita();

    logCaixaEsquerda();
    cout << "Total c/Iva: ";
    logEspaco(TAMANHO_TITULO - 18 - (int) doubleParaString(valorTotalIVA).length());
    cout << setprecision(2) << fixed << valorTotalIVA;
    logCaixaDireita();

    logCaixaEsquerda();
    cout << "Valor recebido: ";
    logEspaco(TAMANHO_TITULO - 21 - (int) doubleParaString(valorDado).length());
    cout << setprecision(2) << fixed << valorDado;
    logCaixaDireita();

    logCaixaEsquerda();
    cout << "Troco: ";
    if (valorDado == 0) {
        logEspaco(TAMANHO_TITULO - 16);
        cout << "0.00";
        logCaixaDireita();
    } else {
        logEspaco(TAMANHO_TITULO - 12 - (int) doubleParaString(valorDado - valorTotalIVA).length());
        cout << setprecision(2) << fixed << (valorDado - valorTotalIVA);
        logCaixaDireita();
    }


    logLinhaVazia();
    if (valorDado == 0) {
        logCaixaEsquerda();
        cout << "Parabens! Ganhou um desconto de 100%!";
        logEspaco(TAMANHO_TITULO - 42);
        logCaixaDireita();
    }
    logLinhaVazia();
    desenhaTitulo("Obrigado pela sua preferencia!");
}

string getTime() {
    time_t rawtime;
    tm timeinfo{};
    char buffer[80];

    time(&rawtime);
    localtime_s(&timeinfo, &rawtime);

    strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", &timeinfo);
    string str(buffer);
    return str;
}

string doubleParaString(double valor) {
    stringstream stream;
    stream << setprecision(2) << fixed << valor;
    return stream.str();
}

void espera() {
    if (logAtivo)
        for (int i = 0; i < 7; i++) {
            setColor(i + 1);
            cout << " *";
            this_thread::sleep_for(chrono::milliseconds(200));
        }
    cout << endl;
    resetColor();
}

void ativarLog() {
    logAtivo = true;
}

void limparEcra() {
    system("cls");
}

void logMarca() {
    const int TAMANHO = 18;
    limparEcra();
    setColor(Cores::AMARELO);
    cout << R"( ___    _  _             __    __  .______          _______.
|__ \  | || |           |  |  |  | |   _  \        /       |
   ) | | || |_          |  |__|  | |  |_)  |      |   (----`
  / /  |__   _|         |   __   | |      /        \   \
 / /_     | |           |  |  |  | |  |\  \----.----)   |
|____|    |_|           |__|  |__| | _| `._____|_______/
 _______  .______      __  .__   __.  __  ___      _______.
|       \ |   _  \    |  | |  \ |  | |  |/  /     /       |
|  .--.  ||  |_)  |   |  | |   \|  | |  '  /     |   (----`
|  |  |  ||      /    |  | |  . `  | |    <       \   \
|  '--'  ||  |\  \----|  | |  |\   | |  .  \  .----)   |
|_______/ | _| `._____|__| |__| \__| |__|\__\ |_______/)" << endl;


    for (int i = 0; i < TAMANHO; i++) {
        setColor(9);
        cout << "*";
    }


    setColor(14);
    cout << "The thirst awakens!";

    for (int i = 0; i < TAMANHO; i++) {
        setColor(4);
        cout << "*";
    }

    resetColor();
    cout << endl << endl;
    desenhaTitulo("Menu Principal");
    cout << endl;
}