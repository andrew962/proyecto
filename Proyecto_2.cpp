#include <iostream>
#include <cmath>
#include <string>
#include<stdlib.h>
#include <iomanip>
#include <windows.h>

// Constantes

// Para Secante
#define SEC_TOLERANCIA 0

// Newton Rapshson
#define NEW_PRECISION 10
#define NEW_INTERVALOS 6

// Global
// Para Biseccion
// Falsa Posicion
#define MAX_ITERACIONES 100
#define INTERVALOS 10
#define PRECISION 6

using namespace std;

// Metodo de Biseccion
float f_biseccion(double x) {
//	return pow(x, 3) + 4 * (pow(x, 2)) - 10;
//	return exp(-1 * x) - cos(3 * x) - 0.5;
	return pow(x, 3) + (2.0 * pow(x, 2)) + (10 * x) - 20;
}
void intervalos(double a, double b) {
	int puntos = INTERVALOS + 1;
	double ancho = (b - a) / INTERVALOS;
	cout << "\n";
	cout << "\tx\tf(x)\n" << endl;
	for (int i = 0; i < puntos; i++) {
		cout << "\t" << a << "\t" << f_biseccion(a) << endl;
		a = a + ancho;
	}
}
int met_biseccion() {
	system("cls");
	printf("Opcion 1");
//	printf("Metodo BISECCION\n");
	cout << setprecision(PRECISION); // Establecemos la precisión
	double a, b, tolerancia;
	cout << "\nCalculo de las raices de una funcion aplicando el metodo BISECCION" << endl;
	cout << "\nIngrese el intervalo inicial [a, b]" << endl;
	cout << "\nIntervalo a: ";
	cin >> a;
	cout << "Intervalo b: ";
	cin >> b;
	intervalos(a, b);
	cout << "\nEscoja el intervalo adecuado" << endl;
	cout << "\nIntervalo adecuado a: ";
	cin >> a;
	cout << "Intervalo adecuado b: ";
	cin >> b;
	float xr; // raiz de la función
	if (f_biseccion(a) * f_biseccion(b) > 0) {
		cout << "\nNo se puede aplicar el metodo de la biseccion\n";
		cout << "porque f(" << a << ") y f(" << b << ") tienes el mismo signo" << endl;
		system("pause");
		met_biseccion();
	} else {
		cout << "Tolerancia = ";
		cin >> tolerancia;
		printf( "|      a      |      b      |      x      |    f(a)     |    f(b)     |    f(x)     |\n");
		do {
			xr = (a + b) / 2.0;
			printf("|%12.8f |%12.8f |%12.8f |%12.8f |%12.8f |%12.8f |\n"
			       , a, b, xr, f_biseccion(a), f_biseccion(b), f_biseccion(xr));
			// Vemos si cumple o no cumple
			if (abs(f_biseccion(xr)) <= tolerancia) { // xr sería la raiz de f
				cout << "\n\nPara una tolerancia " << tolerancia << " la raiz de f es " << xr << endl;
//				printf ("La solucion es: %g", xr);
				break;
			} else {
				if (f_biseccion(xr) * f_biseccion(a) > 0) {
					a = xr;
				} else if (f_biseccion(xr) * f_biseccion(b) > 0) {
					b = xr;
				}
			}

		} while (1);
	}
	printf("\n");
	system("pause");
	system("cls");
}

// Metodo de Secante
double f_secante (double x) {
	//	x³+2x²+10x-20
	//	pow(x, 3) + (2.0 * pow(x, 2)) + (10 * x) - 20;
	return pow(x, 3) + (2.0 * pow(x, 2)) + (10 * x) - 20;
}
void met_secante() {
	double x0, x1, temp, err;
	int n = 1;
	system("cls");
	printf("Opcion 2\n");
	printf("Calculo de las raices de una funcion aplicando el metodo SECANTE\n");
	printf ("\n\nIngrese la aproximacion inicial x0: ");
	cin  >> x0;
	cout << "Ingrese la aproximacion inicial x1: ";
	cin  >> x1;
	cout << endl << "n                   Xn                  Error" << endl;
	cout << "0                   " << x0 << endl;
	cout.setf (ios::left, ios::adjustfield);
	do {
		err = fabs(x0-x1);
		cout.width(20);
		cout << n;
		cout.width(20);
		cout << x1;
		cout.width(20);
		cout << err << endl;
		if (err!=0) {
			temp = x1;
			x1 = x1 - (x1 - x0) * f_secante(x1) / (f_secante(x1) - f_secante(x0));
			x0 = temp;
		}
		n++;
	} while (err>SEC_TOLERANCIA && n<=MAX_ITERACIONES);
	cout << endl;
	if (n<MAX_ITERACIONES)
		cout << "La soluci\242n es: " << x1;
	else
		cout << "No se encontr\242 la raiz: cambiar aproximaciones iniciales o aumentar ITERACIONES_MAXIMAS";

	printf("\n");
	system ("pause");
	system("cls");
}

// Metodo de Newton Rapshson
double f_no_derivada(double x) {
	return x * exp(cos(x)) / 1.5 - 1;
	//return exp(-x) + 3 * x - 3;
}
double f_derivada(double x) {
	return exp(cos(x)) * (1 - x * sin(x)) / 1.5;
	//return -1 * exp(-x) + 3;
}
void evaluacion_newton(double x0, double tolerancia, int max_iteraciones) {
	double x1; // Siguiente aproximación
	double error;	// Diferencia entre dos aproximaciones sucesivas: x1 - x0
	int iteracion; // # de iteraciones
	bool converge = true;

	// Se imprimen los valores de la primera aproximación
	cout << "\nAproximacion inicial:\n";
	cout << "x0 = " << x0 << "\n"
	     << "f(x0) = " << f_no_derivada(x0) << "\n"
	     << "f'(x0) = " << f_derivada(x0) << endl;

	iteracion = 1;
	do {

		if (iteracion > max_iteraciones) {
			converge = false;	// Se sobrepasó la máxima cantidad de iteraciones permitidas
			break;

		} else {
			x1 = x0 - f_no_derivada(x0) / f_derivada(x0); // Cálculo de la siguiente aproximación
			error = fabs(x1 - x0);	// El error es la diferencia entre dos aproximaciones sucesivas

			// Se imprimen los valores de la siguiente aproximación x1, f(x1), f_derivada(x1), error
			cout << "\a";
			Sleep(500);
			cout << "\n\nIteracion #" << iteracion << endl;
			cout << "\nx" << iteracion << "     = " << x1 << "\n"
			     << "f(x" << iteracion << ")  = " << f_no_derivada(x1) << "\n"
			     << "f'(x" << iteracion << ") = " << f_derivada(x1) << "\n"
			     << "error  = " << error << endl;

			// La diferencia entre dos aproximaciones sucesivas es también conocida como error.
			// La condición de terminación consiste en que que el error debe ser <= que la tolerancia dada
			// Si se cumple la condición de terminación, se ha encontrado la raiz aproximada buscada.
			if (error <= tolerancia) { // Condición de terminación
				converge = true;
				break;

				// Si no se cumple el criterio de terminación, se pasa a la siguiente iteración
			} else {
				x0 = x1;
				iteracion++;
			}
		}

	} while (1);

	// Respuesta final
	cout << "\a";
	Sleep(500);
	if (converge) {
		cout << "\n\nPara una tolerancia de " << tolerancia << " la RAIZ APROXIMADA de f es = " << x1 << endl;

	} else {
		cout << "\n\nSe sobrepasó la máxima cantidad de iteraciones permitidas" << endl;
	}
}
void tabula(double a, double b, int intervalos) {
	int puntos = intervalos + 1;

	double ancho = (b - a) / intervalos;

//	cout << "\n\tx\t\tf(x) " << endl;
	printf( "\n|      x      |     f(x)    |\n");
	for (int i = 0; i < puntos; i++) {
//		cout << "\t" << a << "\t\t" << f(a) << endl;
		printf("|%12.8f |%12.8f |\n",a,f_no_derivada(a));
		a = a + ancho;
	}
	printf( "\n");
}
void met_new_rapshon() {
	system("cls");
	printf("Opcion 3 \n");
	printf("Calculo de las raices de una funcion aplicando el metodo NEWTON RASHPSON\n");
	double a;
	double b;
	double tolerancia;	// Tolerancia
	double x0; // Primera aproximación

	cout << setprecision(NEW_PRECISION);	// Se establece la precisión
	cout << "\nIngrese el intervalo inicial [a,b]: \n" << endl;
	// Se ingresa el intervalo
	cout << "\nIntervalo a: ";
	cin >> a;
	cout << "Intervalo b: ";
	cin >> b;
	// Se tabulan los valores de f para INTERVALOS intervalos
	tabula(a, b, NEW_INTERVALOS);
	// Se pide elegir una aproximación inicial
	cout << "\nEscoja el punto inicial adecuado: x0 = ";
	cin >> x0;
	// Se pide ingresar la tolerancia
	cout << "Tolerancia= ";
	cin >> tolerancia;
	// Newton Raphson
	evaluacion_newton(x0, tolerancia, MAX_ITERACIONES);
	printf("\n");
	system ("pause");
	system("cls");
}

// Metodo de Falsa Posicion
double f_falsa_posicion(double x) {
   	// return exp(-1 * x) - cos(3 * x) - 0.5;
	return exp(-1 * x) - cos(x);
}
void tabula_falsa_posicion(double a, double b){
	int puntos = INTERVALOS + 1;
	double ancho = (b - a) / INTERVALOS;
	printf( "\n|    x    |     f(x)    |\n");
	for (int i = 0; i < puntos; i++) {
		printf("|%4f |%12.8f |\n",a,f_falsa_posicion(a));
		a = a + ancho;
	}
}
void met_falsa_posicion(){
	cout << setprecision(PRECISION);
	cout << "\nCalculo de las raices de una funcion aplicando el metodo de la FALSA POSICION\n";
	cout << "\nIngrese el intervalo inicial [a,b]:" << endl;
	
	double a, b, tolerancia;
	
	cout << "\nIntervalo a: ";
	cin >> a;
	
	cout << "Intervalo b: ";
	cin >> b;
	
	tabula_falsa_posicion(a, b);
	
	cout << "\nEscoja el intervalo adecuado" << endl;
	cout << "\nIntervalo adecuado a: ";
	cin >> a;
	
	cout << "\nIntervalo adecuado b: ";
	cin >> b;
	
	double xr; // La solución aproximada
	double xa = 0; // Solución anterior
	
	if (f_falsa_posicion(a) * f_falsa_posicion(b) > 0) {
		cout << "\nNo se puede aplicar el metodo de la falsa posicion\n";
		cout << "porque f(" << a << ") y f(" << b << ") tienen el mismo signo" << endl;
	
	} else {
		cout << "Tolerancia = ";
		cin >> tolerancia;
		
		printf( "|      a      |      b      |      x      |    f(a)     |    f(b)     |    f(x)     |\n");
		do {
			xr = b - f_falsa_posicion(b) * ((b - a) / (f_falsa_posicion(b) - f_falsa_posicion(a)));
			printf("|%12.8f |%12.8f |%12.8f |%12.8f |%12.8f |%12.8f |\n"
			       , a, b, xr, f_falsa_posicion(a), f_falsa_posicion(b), f_falsa_posicion(xr));
			if (fabs(xr - xa) / fabs(xr) <= tolerancia) {
				cout << "\n\nPara una tolerancia de " << tolerancia << " la raiz de f es: " << xr << endl;
				break;
			} else {
				xa = xr; // Se guarda el valor de la aproximación anterior
				if (f_falsa_posicion(xr) * f_falsa_posicion(a) > 0) {
					a = xr;
			
				} else if (f_falsa_posicion(xr) * f_falsa_posicion(b) > 0) {
					b = xr;
				}
			}
		
		} while (1);
	}
   	printf("\n");
	system ("pause");
	system("cls");
}

// Menu donde se desplegara las distintas opciones.
void menu() {
	int opc = 0;
	while(opc != 5) {
		printf("Elige un metodo para resolver una ecuacion.");
		cout<<"\n1- Biseccion";
		cout<<"\n2- Secante";
		cout<<"\n3- Newton Rapshson";
		cout<<"\n4- Falsa Posicion";
		cout<<"\n5- Salir.";
		cout<<"\nOpcion (solo numeros): ";
		cin>>opc;

		switch(opc) {
			case 1:
				met_biseccion();
				break;
			case 2:
				met_secante();
				break;
			case 3:
				met_new_rapshon();
				break;
			case 4:
				met_falsa_posicion();
				break;
			default:
				printf("Opcion no valida.\n");
				system ("pause");
				system("cls");
				break;
		}

	}
}

int main() {
	menu();
}

