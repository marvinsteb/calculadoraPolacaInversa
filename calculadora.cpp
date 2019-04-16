#include <stdio.h> /*para usar printf()*/
#include <stdlib.h> /* para usar atof() */
#include <ctype.h>
#include <string>
#include <math.h>

#define LONGITUDOPERACIONMAX 100
#define ESNUMERO '0'
//(52.87+20)*8

int obtenerOperacion(char[]);
int getch(void);
void ungetch(int);

/*funciones */
void agregarPilaNumeros(double);
double quitarPilaNumeros(void);
void evaluarPilaParaOperar(void);

void agregarPilaOperadores(char,int);	
char quitarPilaOperadores(void);

void calcular(double,double,char);

/*variables para pilas*/

int indicePilaOperandores = 0;
int precedenciaPilaOperadores = 0;
char pilaOperadores[LONGITUDOPERACIONMAX];

int indicePilaNumeros = 0;
double pilaNumeros[LONGITUDOPERACIONMAX];


int parentesisApertura;
int parentesisCierre;
int error = 0;
int cantidadNumeros;
int cantidadSignos;	
int main(int argc, char** argv) {
	
	printf("Calculadora infija a postfija\n \n");
	printf("Ingresa una ecuacion:  \n");

	int tipo;
	double operacionTemporal;
	char ecuacion[LONGITUDOPERACIONMAX]; 	

	agregarPilaOperadores('(',4);
	
	while(error == 0){
		tipo = obtenerOperacion(ecuacion);
		if(tipo == '\n'){
				agregarPilaOperadores(')',4);
		}
		if(tipo != EOF){
							switch (tipo) {
								case ESNUMERO:
									agregarPilaNumeros(atof(ecuacion));
									break;
								case '(':
									agregarPilaOperadores('(',4);
									break;
								case ')':
									agregarPilaOperadores(')',4);					
									break;
								case '+':
									agregarPilaOperadores('+',3);
									break;
								case '-':
									agregarPilaOperadores('-',3);
									break;
								case '*':
									agregarPilaOperadores('*',2);
									break;
								case '/':
									agregarPilaOperadores('/',2);
									break;
								case '^':
									agregarPilaOperadores('^',1);
									break;
							}	
		}


	}

	
	return 0;
}

void evaluarPilaParaOperar(){
				
									if(parentesisApertura > 0 && parentesisCierre > 0 && indicePilaNumeros > 0 ) {						
											// ya se puede operar la ecuacion 
											// printf("ya se puede operar la ecuacion \n\n");
									char signo = quitarPilaOperadores();
										while(signo !='('){
												if (signo !='(' && signo != ')' && (parentesisApertura-parentesisCierre) >= 0) {
													calcular(quitarPilaNumeros(),quitarPilaNumeros(),signo);
												}else{
													/* 	if(signo =='('){
															parentesisApertura--;
														} 
														if(signo == ')') {
															parentesisCierre--;
														} */
												}
													signo = quitarPilaOperadores();
										}
								}
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
					printf("No se puede dividir entre cero \n");
				}
				break;
			case '^':
				resultado = pow(numero1,numero2);
				agregarPilaNumeros(resultado);
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
			while(isdigit(ecuacion[++indice] = caracter = getch()));		
		if (caracter == '.')		
			while (isdigit(ecuacion[++indice] = caracter = getch()));			
		ecuacion[indice] = '\0';
		if (caracter != EOF){
			ungetch(caracter);
		}
	return ESNUMERO;
}

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
	printf("Agregando a la pila de numeros    %.2f	en la pocicion %i\n", 	pilaNumeros[indicePilaNumeros] ,indicePilaNumeros);
	indicePilaNumeros++;
	}  else {
			printf("Ha ocurrido un error, la pila ya esta llena \n ");
	}
}

double quitarPilaNumeros(){
	if(indicePilaNumeros > 0 ){
		indicePilaNumeros--;
		return pilaNumeros[indicePilaNumeros];
	} else {
		printf("pila de numeros vacia \n");
		error++;
		return 0.00;
	}
}

void agregarPilaOperadores(char operador,int precedencia){
	if(indicePilaOperandores < LONGITUDOPERACIONMAX){
			  if(operador !='(' && operador != ')'){
										cantidadSignos++;
							 			
										if(precedenciaPilaOperadores < precedencia && cantidadSignos > 1) {


											char signoTemporal = quitarPilaOperadores();
											printf("quitando temporalmente signo de mayor presedecia %c	a la pocicio %i\n",pilaOperadores[indicePilaOperandores],indicePilaOperandores);
											calcular(quitarPilaNumeros(),quitarPilaNumeros(),signoTemporal);	
											pilaOperadores[indicePilaOperandores] = operador;
											printf("agregando signo de menor presedecia %c	a la pocicio %i\n",pilaOperadores[indicePilaOperandores],indicePilaOperandores);
											indicePilaOperandores ++;
											precedenciaPilaOperadores = precedencia;
										} else {
												
													pilaOperadores[indicePilaOperandores] = operador;
													printf("*Agregando a la pila de operadores %c	a la pocicio %i\n",pilaOperadores[indicePilaOperandores],indicePilaOperandores);
													indicePilaOperandores ++;
												precedenciaPilaOperadores = precedencia;
										}

							/*			
										} else {
										}	
										 */
				} else {
									pilaOperadores[indicePilaOperandores] = operador;
									printf("Agregando a la pila de operadores %c	a la pocicio %i\n",pilaOperadores[indicePilaOperandores],indicePilaOperandores);
									indicePilaOperandores ++;
				}


	} else {
			printf("Ha ocurrido un error, la pila ya esta llena \n ");
	}

	if(operador == '('){
		parentesisApertura++;
	} else {
			if(operador == ')'){
				parentesisCierre++; 
	
	                if(parentesisApertura-parentesisCierre < 0){
										printf("hay un eror con los parentesis \n\n");
										error++;
									} else {
												evaluarPilaParaOperar();
									}
		} else {
			cantidadSignos++;
		}

	}
		
}
char quitarPilaOperadores(){
	if(indicePilaOperandores > 0 ){
		indicePilaOperandores--;
		return pilaOperadores[indicePilaOperandores];	
	} else {
		printf("pila de signos vacia \n");
			error++;
		return 'V';
	}
};
