#include <stdio.h> /*para usar printf()*/
#include <stdlib.h> /* para usar atof() */
#include <ctype.h>


#define LONGITUDOPERACIONMAX 100
#define ESNUMERO '0'

int obtenerOperacion(char[]);
int getch(void);
void ungetch(int);


void agregarPilaNumeros(double);
double quitarPilaNumeros(void);

void agregarPilaOperadores(char);	
char quitarPilaOperadores(char);

int main(int argc, char** argv) {
	
	printf("Calculadora infija a postfija\n \n");
	printf("Ingresa una ecuacion:  \n");

	int tipo;
	double operacionTemporal;
	char ecuacion[LONGITUDOPERACIONMAX];

	
	while((tipo = obtenerOperacion(ecuacion)) != EOF){
		 switch (tipo) {
			case ESNUMERO:
				agregarPilaNumeros(atof(ecuacion));
				break;
			case '+':
				agregarPilaOperadores(tipo);
				break;
			case '*':
				printf("es un signo multiplicacion \n");
				break;
      }
  }
	
	return 0;
}

/*
	esta funcion, obtiene el signo de la opercion y regresa 0 si es un digito.
 */
int obtenerOperacion(char ecuacion[]){
	 int indice,caracter;

			while ((ecuacion[0] = caracter = getch()) == ' ' || caracter == '\t');
		ecuacion[1] = '\0';
		if (!isdigit(caracter) && caracter != '.')
			return caracter;		
		indice = 0;
		if (isdigit(caracter))
			while(isdigit(ecuacion[++indice] = caracter = getch()))
			;		
		if (caracter == '.')		
			while (isdigit(ecuacion[++indice] = caracter = getch()))
			;			
		ecuacion[indice] = '\0';
		if (caracter != EOF)
			ungetch(caracter);
	return ESNUMERO;
}


#define BUFFER 100		

static char buf[BUFFER];	
static int pbuf = 0;		
int getch(void)
{
  if (pbuf > 0)			
    return buf[--pbuf]; 	
   else				
    return getchar();		
}
void ungetch(int c)
{
  if (pbuf >= BUFFER)
    printf("ungetch: demasiados caracteres, se agoto el buffer\n");
  else
    buf[pbuf++] = c;
}


int indicePilaNumeros = 0;
int indicePilaOperandores = 0;
double pilaNumeros[LONGITUDOPERACIONMAX];
char pilaOperadores[LONGITUDOPERACIONMAX];

void agregarPilaNumeros(double numero){
	if(indicePilaNumeros < LONGITUDOPERACIONMAX){
	pilaNumeros[indicePilaNumeros] = numero;
	printf("Se agrego el numero % f en la pocicion %i de la pila \n", 	pilaNumeros[indicePilaNumeros] ,indicePilaNumeros);
	indicePilaNumeros++;
	}  else {
			printf("Ha ocurrido un error, la pila ya esta llena \n ");
	}
}

void agregarPilaOperadores(char operador){
	if(indicePilaOperandores < LONGITUDOPERACIONMAX){
		pilaOperadores[indicePilaOperandores] = operador;
		printf("se agrego un operador a la pila \n");
		indicePilaOperandores ++;
	} else {
			printf("Ha ocurrido un error, la pila ya esta llena \n ");
	}

}
