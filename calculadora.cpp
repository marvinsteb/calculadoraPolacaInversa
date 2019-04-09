#include <stdio.h> /*para usar printf()*/
#include <stdlib.h> /* para usar atof() */
#include <ctype.h>
#include <string>


#define LONGITUDOPERACIONMAX 100
#define ESNUMERO '0'

int obtenerOperacion(char[]);
int getch(void);
void ungetch(int);

/*funciones */
void agregarPilaNumeros(double);
double quitarPilaNumeros(void);

void agregarPilaOperadores(char);	
char quitarPilaOperadores(void);

void calcular(double,double,char);

/*variables para pilas*/

int indicePilaOperandores = 0;
char pilaOperadores[LONGITUDOPERACIONMAX];

int indicePilaNumeros = 0;
double pilaNumeros[LONGITUDOPERACIONMAX];


int parentesisApertura;
int parentesisCierre;

	
int main(int argc, char** argv) {
	
	printf("Calculadora infija a postfija\n \n");
	printf("Ingresa una ecuacion:  \n");

	int tipo;
	double operacionTemporal;
	char ecuacion[LONGITUDOPERACIONMAX];

	
	while((tipo = obtenerOperacion(ecuacion)) != EOF){
		if((parentesisApertura - parentesisCierre) < 0 ) {
			printf("Ecuacion no valida, revisa los parentesis");
		} else {
				if(parentesisApertura > 0 && parentesisCierre > 0 && indicePilaNumeros > 0 ) {
					// ya se puede operar la ecuacion 
					// printf("ya se puede operar la ecuacion \n\n");
					  char signo = quitarPilaOperadores();
						while(signo !='('){
							if (signo !='(' && signo != ')') {
									calcular(quitarPilaNumeros(),quitarPilaNumeros(),signo);
							}
							signo = quitarPilaOperadores();
						}				
				} 
					switch (tipo) {
						case ESNUMERO:
							agregarPilaNumeros(atof(ecuacion));
							break;
						case '(':
							agregarPilaOperadores('(');
							parentesisApertura++;	
							break;
						case ')':
							agregarPilaOperadores(')');
							parentesisCierre++; 
							break;
						case '+':
							agregarPilaOperadores('+');
							break;
						case '-':
							agregarPilaOperadores('-');
							break;
						case '*':
							agregarPilaOperadores('*');
							break;
						case '/':
							agregarPilaOperadores('/');
							break;
					}
		
			
		}

	}

	
	return 0;
}

void calcular(double numero1 , double numero2 , char signo){
	double resultado = 0.00;
		switch (signo)
		{
			case '+':
				resultado = numero1 + numero2;
				printf("sumando %f \n",resultado);
				agregarPilaNumeros(resultado);
				break;
				case '-':
				resultado = numero1 - numero2;
				printf("restando %f \n",resultado);
				agregarPilaNumeros(resultado);
				break;
				case '*':
				resultado = numero1 * numero2;
				printf("multiplicando %f \n",resultado);
				agregarPilaNumeros(resultado);
				break;
				case '/':
				if(numero2 != 0){
				resultado = numero1 / numero2;
				printf("dividiendo %f \n",resultado);
				agregarPilaNumeros(resultado);
				} else {
					printf('No se puede dividir entre cero \n');
				}
				break;
			default:
				break;
		}
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


/* void balanceoDeSimbolos(char ecuacion[]){
	int indice = 0;
	printf("desde balanceo de simbolos");
	printf(ecuacion);
  		while(ecuacion[indice] != '\0'){
			printf(" %i\n",indice);
			indice++;
		} 
}
 */


#define BUFFER 100		

static char buf[BUFFER];	
static int pbuf = 0;		
int getch(void) {
  if (pbuf > 0)			
    return buf[--pbuf]; 	
   else				
    return getchar();		
}
void ungetch(int c) {
  if (pbuf >= BUFFER)
    printf("demasiados caracteres\n");
  else
    buf[pbuf++] = c;
}


void agregarPilaNumeros(double numero){
	if(indicePilaNumeros < LONGITUDOPERACIONMAX){
	pilaNumeros[indicePilaNumeros] = numero;
	printf("Se agrego el numero %f en la pocicion %i de la pila de numeros\n", 	pilaNumeros[indicePilaNumeros] ,indicePilaNumeros);
	indicePilaNumeros++;
	}  else {
			printf("Ha ocurrido un error, la pila ya esta llena \n ");
	}
}

double quitarPilaNumeros(){
	printf(" el indice de los numeros es %i \n",indicePilaNumeros);
	if(indicePilaNumeros > 0 ){
		indicePilaNumeros--;
		return pilaNumeros[indicePilaNumeros];
	} else {
		printf("pila de numeros vacia \n");
		return 0.00;
	}
}

void agregarPilaOperadores(char operador){
	if(indicePilaOperandores < LONGITUDOPERACIONMAX){
		pilaOperadores[indicePilaOperandores] = operador;
		printf("se agrego el operador %c a la pocicio %i de la pila de operadores \n",pilaOperadores[indicePilaOperandores],indicePilaOperandores);
		indicePilaOperandores ++;
	} else {
			printf("Ha ocurrido un error, la pila ya esta llena \n ");
	}

}
char quitarPilaOperadores(){
	if(indicePilaOperandores > 0 ){
		indicePilaOperandores--;
		return pilaOperadores[indicePilaOperandores];	
	} else {
		printf("pila de signos vacia \n");
		return 'V';
	}
};
