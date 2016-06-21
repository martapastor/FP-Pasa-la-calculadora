//Práctica 1 versión 3.0
//Pasa la calculadora
//Por Marta Pastor Puente y Ángela Martínez Ros


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <string>
#include <fstream>
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

int menu ();

bool mostrar (string nombArch);

bool actInforme (int jugadas, int ganadas, int abandonos);

int main ()
{
	string nombre;
	cout << "¡Bienvenido a Pasa la calculadora!" << endl;
	cout << "Por favor, introduce tu nombre: ";
	cin >> nombre;
	cout << "Encantado de conocerte, " << nombre << endl << endl;
	cout << "Por favor, selecciona una opcion: " << endl << endl;

	srand (time(NULL)); //con escribirla aquí ya sirve la semilla para el PROGRAMA ENTERO

	int m;
	m = menu ();

	int j = 0, g = 0, a = 0;

	while (m != 0)
	{
		if (m == 1)
		{
			tJugador quienGana;
			quienGana = pasaCalculadora ();

			//actInforme (int jugadas, int ganadas, int abandonos);

			if (quienGana == Automata)
				cout << "Lo siento, " << nombre << ", has perdido. Gracias por jugar." << endl << endl;

			else if (quienGana == Persona)
			{
				cout << "¡Enhorabuena, " << nombre << ", has ganado! Gracias por jugar." << endl << endl;
				g++;
			}

			else
			{
				cout << "Has abandonado la partida. Gracias por jugar." << endl << endl;
				a++;
			}

			j++;

		}

		if (m == 2)
		{
			string nombArch;
			nombArch = "versionPC.txt";
		
			bool n;
			n = mostrar (nombArch);
		}

		m = menu ();
	}

	bool z;
	z = actInforme (j, g, a);

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
//Devuelve true si nuevo está en la misma fila que ultimo; en caso contrario devuelve false. 
//Observa que la fila que ocupa un dígito, numeradas desde 0, corresponde con (dígito - 1) / 3.
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
//Devuelve true si nuevo está en la misma columna que ultimo; en caso contrario devuelve false.
//Observa que la columna que ocupa un dígito, numeradas desde 0, corresponde con (dígito-1) % 3.
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
//Devuelve un dígito.
{
	int aleatorio;
	//No hace falta volver a escribir srand(time(NULL)) porque ya se ejecutó en la función main ()
	aleatorio = (rand() % 9) + 1;

	return aleatorio;
}

int digitoAutomata (int ultimo)
//Devuelve un dígito que cumpla las reglas del juego con respecto a ultimo. 
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
//Pide un dígito al jugador. 
//Sólo devolverá un valor válido (entre 0 y 9). 
//Para cada valor no válido, mostrará un error.
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
		cout << "Error: el digito introducido no es válido." << endl << endl;

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
//Pide un dígito al jugador mostrando el teclado. 
//Sólo devolverá un valor que cumpla las reglas del juego o 0. 
//Para cada valor no válido, mostrará un error.
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

int menu ()
//Muestra el menú, pide la opción y la devuelve como resultado. 
//Sólo devolverá una opción válida. Para cada valor no válido, mostrará un error.
{
	int m;

	cout << "1 - Jugar" << endl;
	cout << "2 - Acerca de" << endl;
	cout << "0 - Salir" << endl << endl;

	cout << "Opcion: ";
	cin >> m;

	while (m < 0 || m > 2)
	{
		cout << "Error: opcion no valida. Por favor, seleccione una opcion valida: ";
		cin >> m;
	}

	return m;
}

bool mostrar (string nombArch)
//Muestra en la consola el contenido del archivo de texto nombArch. 
//Si el archivo no se encuentra, devuelve false, en otro caso true.
{
	bool m; 
	
	ifstream archivo;

	archivo.open (nombArch);

	if (archivo.is_open())
	{
		char c;
		
		while (!archivo.eof())
		{
			archivo.get(c);
			cout.put(c);
		}

		cout << endl;

		archivo.close ();
		
		m = true;
	}

	else
	{
		cout << "El archivo especificado no se encuentra.";
		m = false;
	}

	return m;
}

bool actInforme (int jugadas, int ganadas, int abandonos)
{
	bool y;
	
	const string archivoTexto = "informePC.txt";
	ifstream entrada;
	ofstream salida;

	int e= 0, J = 0, G = 0, A = 0;

	entrada.open (archivoTexto);

	if (entrada.is_open())
	{
		entrada >> e;
		entrada >> J;
		entrada >> G;
		entrada >> A;

		y = true;
	}

	else
		y = false;

	/*	Número de veces que se ha utilizado el programa
		Número total de partidas jugadas (incluidos los abandonos)
		Número total de partidas ganadas por el programa
		Número total de abandonos  */

	e++;
	J+=jugadas;
	G+=ganadas;
	A+=abandonos;

    entrada.close ();

	//

	salida.open (archivoTexto);

	salida << e << endl;
	salida << J << endl;
	salida << G << endl;
	salida << A << endl << endl;

	salida.close ();

	return y;
}