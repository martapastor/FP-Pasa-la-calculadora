//Pr�ctica 1 versi�n 1.0
//Pasa la calculadora
//Por Marta Pastor Puente y �ngela Mart�nez Ros


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <string>
//#include <fstream>
using namespace std;

typedef enum { Nadie, Automata, Persona } tJugador;
tJugador pasaCalculadora ();
tJugador quienEmpieza ();

bool mismaFila (int ultimo, int nuevo);
bool mismaColumna (int ultimo, int nuevo);
bool digitoValido (int ultimo, int nuevo);

int digitoAleatorio ();
int digitoAutomata (int ultimo);
int digitoPersona ();
int digitoPersona (int ultimo);


int main ()
{
	string nombre;
	cout << "�Bienvenido a Pasa la calculadora!" << endl;
	cout << "Por favor, introduce tu nombre: ";
	cin >> nombre;
	cout << "Encantado de conocerte, " << nombre << endl << endl;

	srand (time(NULL)); //con escribirla aqu� ya sirve la semilla para el PROGRAMA ENTERO
	
	tJugador quienGana;
	quienGana = pasaCalculadora ();

	//Falta definir los cout dependiendo de quien haya ganado pasaCalculadora ()
	if (quienGana == Automata)
		cout << "Lo siento, " << nombre << ", has perdido. Gracias por jugar." << endl << endl;

	else if (quienGana == Persona)
		cout << "�Enhorabuena, " << nombre << ", has ganado! Gracias por jugar." << endl << endl;

	else
		cout << "Has abandonado la partida. Gracias por jugar." << endl << endl;

	system ("pause");

	return 0;
}					

tJugador pasaCalculadora ()
//Conduce el desarrollo del juego y devuelve el ganador. 
//Si se abandona devuelve Nadie. 
{
	tJugador ganador;
	tJugador turno;
	
	int ultimo;
	int nuevo;

	turno = quienEmpieza ();

	if (turno == Automata)
	{
		nuevo = digitoAleatorio ();
		ultimo = nuevo;

		cout << "Yo pulso: " << ultimo << endl << endl;

		turno = Persona;
	}

	else //turno == Persona
	{
		nuevo = digitoPersona ();
		ultimo = nuevo;

		turno = Automata;
	}

	const int META = 31;

	int suma;
	suma = nuevo;

	if (suma != 0)
		cout << "La suma es " << suma << endl << endl;

	while (nuevo != 0 && suma < META) 
	{
		if (turno == Automata)
		{
			nuevo = digitoAutomata (ultimo);
			suma = suma + nuevo;
			ultimo = nuevo;

			cout << "La suma es " << suma << endl << endl;

			turno = Persona;
		}

		else //turno == Persona
		{				 
			nuevo = digitoPersona (ultimo);
			suma = suma + nuevo;
			ultimo = nuevo;

			cout << "La suma es " << suma << endl << endl;

			turno = Automata;
		}
	}
	
	if (nuevo == 0)
	{
		turno = Nadie;
	}

	ganador = turno;

	return ganador;
}

tJugador quienEmpieza ()
//Decide aleatoriamente quien empieza.
{
	tJugador primero;

	int p;
	p = (rand() % 2) + 1;

	if (p == 1)
	{
		cout << "Empiezo yo" << endl << endl;
		primero = Automata;
	}
	
	else // p == 2
	{
		cout << "Empiezas tu" << endl << endl;
		primero = Persona;
	}

	return primero;
}

bool mismaFila (int ultimo, int nuevo)
//Devuelve true si nuevo est� en la misma fila que ultimo; en caso contrario devuelve false. 
//Observa que la fila que ocupa un d�gito, numeradas desde 0, corresponde con (d�gito - 1) / 3.
{
	int fila;
	bool esMismaFila;

	if (nuevo == 1 || nuevo == 2 || nuevo == 3)
		fila = 0;
	else if (nuevo == 4 || nuevo == 5 || nuevo == 6)
		fila = 1;
	else if (nuevo == 7 || nuevo == 8 || nuevo == 9)
		fila = 2;

	if (fila == ((ultimo - 1) / 3))
		esMismaFila = true;

	else 
		esMismaFila = false;

	return esMismaFila;
}

bool mismaColumna (int ultimo, int nuevo)
//Devuelve true si nuevo est� en la misma columna que ultimo; en caso contrario devuelve false.
//Observa que la columna que ocupa un d�gito, numeradas desde 0, corresponde con (d�gito-1) % 3.
{
	int columna;
	bool esMismaColumna;

	if (nuevo == 1 || nuevo == 4 || nuevo == 7)
		columna = 0;
	else if (nuevo == 2 || nuevo == 5 || nuevo == 8)
		columna = 1;
	else if (nuevo == 3 || nuevo == 6 || nuevo == 9)
		columna = 2;

	if (columna == ((ultimo - 1) % 3))
		esMismaColumna = true;

	else 
		esMismaColumna = false;

	return esMismaColumna;
}

bool digitoValido (int ultimo, int nuevo)
//Devuelve true si nuevo cumple las reglas del juego con respecto a ultimo.
//En caso contrario devuelve false.
{
	bool correctoFila;
	bool correctoColumna;
	bool esDigitoValido;

	correctoFila = mismaFila (ultimo, nuevo);
	correctoColumna = mismaColumna (ultimo, nuevo);

	if ((correctoFila == true || correctoColumna == true) && nuevo != ultimo)
	{
		esDigitoValido = true;
	} 

	else 
	{
		esDigitoValido = false;
	}

	return esDigitoValido;
}

int digitoAleatorio ()
//Devuelve un d�gito.
{
	int aleatorio;
	//No hace falta volver a escribir srand(time(NULL)) porque ya se ejecut� en la funci�n main ()
	aleatorio = (rand() % 9) + 1;

	return aleatorio;
}

int digitoAutomata (int ultimo)
//Devuelve un d�gito que cumpla las reglas del juego con respecto a ultimo. 
//Por ejemplo, digitoAutomata(2) puede devolver 1,3,5 u 8.
{
	int nuevo;
	nuevo = digitoAleatorio ();

	bool x;
	x = digitoValido (ultimo, nuevo);

	while (x != true)
	{
		nuevo = digitoAleatorio ();
		x = digitoValido (ultimo, nuevo);
	}

	cout << "Yo pulso: " << nuevo << endl << endl;

	return nuevo;
}

int digitoPersona ()
//Pide un d�gito al jugador. 
//S�lo devolver� un valor v�lido (entre 0 y 9). 
//Para cada valor no v�lido, mostrar� un error.
{
	int numero;

	cout << left << setw(5) << 7 <<	left << setw(5) << 8 << left << setw(5) << 9 << endl;
	cout << left << setw(5) << 4 <<	left << setw(5) << 5 << left << setw(5) << 6 << endl;
	cout << left << setw(5) << 1 <<	left << setw(5) << 2 << left << setw(5) << 3 << endl;

	cout << "Introduce un digito (0 para abandonar): ";
	cin >> numero;
	cout << endl;

	while ((numero <= 0) && (9 <= numero))
	{
		cout << "Error: el digito introducido no es v�lido." << endl << endl;

		cout << left << setw(5) << 7 <<	left << setw(5) << 8 << left << setw(5) << 9 << endl;
		cout << left << setw(5) << 4 <<	left << setw(5) << 5 << left << setw(5) << 6 << endl;
		cout << left << setw(5) << 1 <<	left << setw(5) << 2 << left << setw(5) << 3 << endl;

		cout << "Introduce un digito (0 para abandonar): ";
		cin >> numero;
		cout << endl;
	}

	return numero;
}

int digitoPersona (int ultimo)
//Pide un d�gito al jugador mostrando el teclado. 
//S�lo devolver� un valor que cumpla las reglas del juego o 0. 
//Para cada valor no v�lido, mostrar� un error.
{
	int nuevo;
	nuevo = digitoPersona ();
	
	if (nuevo != 0)
	{
		bool v;
		v = digitoValido (ultimo, nuevo);

		while (v != true)
		{
			cout << "Error: el numero debe ser distinto de " << ultimo << " y estar en la misma fila o columna." << endl;

			nuevo = digitoPersona ();
			v = digitoValido (ultimo, nuevo);
		}
	}

	return nuevo;
}