#include "logs.h"
#include <iostream>
#include <string>

#include <chrono>
#include <thread>

using namespace std;

bool logAtivo = false;

void logInfo(string message)
{
	cout << "[INFO] " << message << endl;
	espera();
}

void logErro(string message)
{
	cout << "[ERRO] " << message << endl;
	espera();

}

void logAviso(string message)
{
	cout << "[AVISO] " << message << endl;
	espera();

}

void logSucesso(string message)
{
	cout << "[SUCESSO] " << message << endl;
	espera();

}

void logTitulo(string message)
{
	cout << "/********** " << message << " **********/" << endl;
	espera();

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
  /$$$$$$                                                        /$$          
 /$$__  $$                                                      |__/          
| $$  \__/  /$$$$$$  /$$$$$$/$$$$   /$$$$$$   /$$$$$$   /$$$$$$$ /$$  /$$$$$$ 
| $$       /$$__  $$| $$_  $$_  $$ /$$__  $$ /$$__  $$ /$$_____/| $$ /$$__  $$
| $$      | $$  \ $$| $$ \ $$ \ $$| $$$$$$$$| $$  \__/| $$      | $$| $$  \ $$
| $$    $$| $$  | $$| $$ | $$ | $$| $$_____/| $$      | $$      | $$| $$  | $$
|  $$$$$$/|  $$$$$$/| $$ | $$ | $$|  $$$$$$$| $$      |  $$$$$$$| $$|  $$$$$$/
 \______/  \______/ |__/ |__/ |__/ \_______/|__/       \_______/|__/ \______/ 
                                                                              
                                                                              
 /$$                                     /$$                                  
| $$                                    | $$                                  
| $$        /$$$$$$   /$$$$$$$  /$$$$$$ | $$                                  
| $$       /$$__  $$ /$$_____/ |____  $$| $$                                  
| $$      | $$  \ $$| $$        /$$$$$$$| $$                                  
| $$      | $$  | $$| $$       /$$__  $$| $$                                  
| $$$$$$$$|  $$$$$$/|  $$$$$$$|  $$$$$$$| $$                                  
|________/ \______/  \_______/ \_______/|__/                                  
                                                                       
    )" << '\n';
}