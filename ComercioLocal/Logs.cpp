#include "logs.h"
#include <iostream>
#include <string>

#include <chrono>
#include <thread>

using namespace std;

bool logAtivo = false;

void logInfo(string message)
{
	cout << "\033[1;36m[INFO]\033[0m " << message << endl;
	espera();
}

void logErro(string message)
{
	cout << "\033[1;31m[ERRO]\033[0m " << message << endl;
	espera();

}

void logAviso(string message)
{
	cout << "\033[1;33m[AVISO]\033[0m " << message << endl;
	espera();

}

void logSucesso(string message)
{
	cout << "\033[1;32m[SUCESSO]\033[0m " << message << endl;
	espera();

}

void logTitulo(string message)
{
	cout << "/********** " << message << " **********/" << endl;
	espera();

}

void logBold(string message)
{
	cout << "\033[1m" << message << "\033[0m" << endl;
}

void espera() {
	if (logAtivo)
		this_thread::sleep_for(chrono::milliseconds(750));
}

void ativarLog() {
	logAtivo = true;
}

void logMarca()
{
	cout << R"(
 ___    _  _     __    __  .______          _______.
|__ \  | || |   |  |  |  | |   _  \        /       |
   ) | | || |_  |  |__|  | |  |_)  |      |   (----`
  / /  |__   _| |   __   | |      /        \   \          
 / /_     | |   |  |  |  | |  |\  \----.----)   |         
|____|    |_|   |__|  |__| | _| `._____|_______/       

 _______  .______       __  .__   __.  __  ___      _______.
|       \ |   _  \     |  | |  \ |  | |  |/  /     /       |
|  .--.  ||  |_)  |    |  | |   \|  | |  '  /     |   (----`
|  |  |  ||      /     |  | |  . `  | |    <       \   \ 
|  '--'  ||  |\  \----.|  | |  |\   | |  .  \  .----)   |
|_______/ | _| `._____||__| |__| \__| |__|\__\ |_______/                                                           
    )";

	cout << "\t\t\033[1;31mThe thirst awakens!\033[0m " << endl << endl;

}