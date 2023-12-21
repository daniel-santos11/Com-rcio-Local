#include "logs.h"
#include <iostream>
#include <string>

using namespace std;

void logInfo(string message)
{
	cout << "[INFO] " << message << endl;
}

void logErro(string message)
{
	cout << "[ERROR] " << message << endl;
}

void logAviso(string message)
{
	cout << "[AVISO] " << message << endl;
}

void logSucesso(string message)
{
	cout << "[SUCESSO] " << message << endl;
}

void logTitulo(string title)
{
	cout << endl << "==============================" << endl;
	cout << title << endl;
	cout << "==============================" << endl << endl;	
}	