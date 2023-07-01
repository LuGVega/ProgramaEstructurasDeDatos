/*
	Gómez Vega Guadalupe		
Proyecto: 
			Traduce un polinomio en notación infija a una posfija
			-El polinomio puede ser de varias incognitas
			-Las incognitas pueden ser flotantes
			-Sus coeficientes y potencias son de un digito y son enteras*/
/* Librerias a incluir */
#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
/*Definiciones*/
#define T 5000
/*Registros*/
struct nodo
{
	char info;
	struct nodo *liga;
};
struct nodo2
{
	double num;
	struct nodo2 *lig;
};
/*Encabezados*/
void menu(void);
int entrada(void);
int prioridad(char);
struct nodo* conversionPos(struct nodo*, struct nodo*, char[]);
struct nodo * push(struct nodo *, char);
struct nodo2 * push2(struct nodo2 *, double);
struct nodo * pop(struct nodo *);
struct nodo2 * pop2(struct nodo2 *);
void muestra(struct nodo*, char*);
void muestra2(struct nodo2*, double *);
struct nodo *  borrarIzq(struct nodo*);
void mostrarIzq(struct nodo*, char *);
double evaluarPos(struct nodo*, struct nodo2*, char[], double[], int, int);
double operacion(char, double ,double);
void imprimir(struct nodo *);
int main()
{
	struct nodo *pila =NULL;
	struct nodo *epos=NULL;
	struct nodo2 *pila2=NULL;
	char polin[T], incog[T], resp;
	int ent,bandera=0, centi=0, cantidad=0, x=0;
	double resultado=0.0, valor[T];
	printf("Ingresa polinomio en notacion INFIJA SIN ESPACIOS: ");
	scanf("%s", polin);
	menu();
	do
	{
		ent=entrada();
		switch(ent)
		{
			case 1:
				bandera=1;
				epos=conversionPos(pila, epos, polin);
				printf("Expresion posfija: ");
				imprimir(epos);
			break;
			case 2:
				printf("Tu expresion tiene incognitas?S/N: ");
				fflush(stdin);
				scanf("%c", &resp);
				resp=toupper(resp);
				if(resp=='S')
				{
					centi=1;
					printf("Cuantas incognitas tiene? ");
					scanf("%d", &cantidad);
					fflush(stdin);
					printf("Cuales son las incognitas? \n");
					for(x=0; x<cantidad; ++x)
					{
						fflush(stdin);
						printf("Incognita %d: ", x+1); 
						scanf("%c", &incog[x]);
						incog[x]=tolower(incog[x]);
					}
					for(x=0; x<cantidad; ++x)
					{
						printf("Cual es el valor de %c? ", incog[x]);
						scanf("%lf", &valor[x]);
						fflush(stdin);
					}
				}
				else
					centi=0;
				if(bandera==1)
				{
					resultado=evaluarPos(epos, pila2, incog, valor, centi, cantidad);
				}
				printf("Resultado de la expresion: %f\n", resultado);
			break;
			case 3:
				printf("Fin programa\n");
				exit(-1);
			break;
		}
		fflush(stdin);
		printf("Quieres hacer algo mas? S/N: ");
		scanf("%c", &resp);
		resp=toupper(resp);
		if(resp=='N')
			printf("Fin programa");
	}while(resp=='S');
	
	return 0;
}
void menu(void)
{
	printf("1)Traducir a posfija\n");
	printf("2)Evaluar expresion\n");
	printf("3)Salir\n");
}
int entrada(void)
{
	int ent;
	char c;
	printf("Opcion: ");
	while(!(scanf("%d%c", &ent, &c)==2 && c=='\n') || (ent<1 || ent>3))
	{
		printf("No existe esa opcion digite otra opcion: ");
		fflush(stdin);
	}
	return ent;
}
int prioridad(char c)
{
	int prio;
	if(c>='a'&& c<='z')
		prio=0;
	else
		if(c=='+'|| c=='-')
			prio=1;
		else
			if(c=='*' || c== '/')
				prio=2;
			else
				if(c=='^')
					prio=3;
				else
					if(c=='(' || c==')')
						prio=4;
					else 
						if(c=='#')
							prio=5;
						else
							prio=0;
	return prio;
}
struct nodo * push(struct nodo *inicio, char sim)
{
	struct nodo *nuevo =(struct nodo*)malloc(sizeof(struct nodo));
	nuevo->info=sim;
	nuevo->liga=NULL;
	if(inicio==NULL)
	{
		inicio=nuevo;
	}
	else
	{
		struct nodo *aux=inicio;
		while(aux->liga!=NULL)
		{
			aux=aux->liga;
		}
		aux->liga=nuevo;
	}
	return inicio;
}
struct nodo2 * push2(struct nodo2 *inicio, double sim)
{
	struct nodo2 *nuevo =(struct nodo2*)malloc(sizeof(struct nodo2));
	nuevo->num=sim;
	nuevo->lig=NULL;
	if(inicio==NULL)
	{
		inicio=nuevo;
	}
	else
	{
		struct nodo2 *aux=inicio;
		while(aux->lig!=NULL)
		{
			aux=aux->lig;
		}
		aux->lig=nuevo;
	}
	return inicio;
}
struct nodo * pop(struct nodo *P)
{
	struct nodo *Q;
	if(P==NULL)
		printf("Lista vacia, no se borro nada");
	else
	{
		if(P->liga==NULL)
		{
			free(P);
			P=NULL;
		}
		else
		{
			Q=P;
			while(Q->liga->liga!=NULL)
			{
				Q=Q->liga;
			}
			free(Q->liga);
			Q->liga=NULL;
		}
	}
	return P;
}
struct nodo2 * pop2(struct nodo2 *P)
{
	struct nodo2 *Q;
	if(P==NULL)
		printf("Lista vacia, no se borro nada");
	else
	{
		if(P->lig==NULL)
		{
			free(P);
			P=NULL;
		}
		else
		{
			Q=P;
			while(Q->lig->lig!=NULL)
			{
				Q=Q->lig;
			}
			free(Q->lig);
			Q->lig=NULL;
		}
	}
	return P;
}
void muestra(struct nodo *P, char *compa)
{
	struct nodo *Q;
	if(P==NULL)
		printf("Lista vacia\n");
	else
	{
		if(P->liga==NULL)
		{
			*compa=P->info;
		}
		else
		{
			Q=P;
			while(Q->liga->liga!=NULL)
			{
				Q=Q->liga;
			}
			*compa=Q->liga->info;
		}
	}
}
void muestra2(struct nodo2 *P, double *compa)
{
	struct nodo2 *Q;
	if(P==NULL)
		printf("Lista vacia\n");
	else
	{
		if(P->lig==NULL)
		{
			*compa=P->num;
		}
		else
		{
			Q=P;
			while(Q->lig->lig!=NULL)
			{
				Q=Q->lig;
			}
			*compa=Q->lig->num;
		}
	}
}
void mostrarIzq(struct nodo *P, char *compa)
{
	struct nodo *Q;
	Q=P;
	*compa=P->info;
}
struct nodo * borrarIzq(struct nodo *P)
{
	struct nodo *Q;
	Q=P;
	P=Q->liga;
	free(Q);
	return P;	
}
struct nodo* conversionPos(struct nodo *pila, struct nodo *epos, char polin[])
{
	char compa;
	int  x, longi, pr, pc;
	pila=push(pila, '#');//se agrega # a la pila marca el inicio 
	strcat(polin, "#");//se agrega el # a la expresion infija marca el final
	longi=strlen(polin);//longitud de la cadena
	for(x=0; x<longi; ++x )
	{
		polin[x]=tolower(polin[x]);
		pr=prioridad(polin[x]);
		if(pr==0)
			epos=push(epos, polin[x]);
		else
		{
			if(pr>0)
			{
				muestra(pila, &compa);//muestra el tope de la pila
				if(compa=='#')
				{
					pila=push(pila, polin[x]);	
				}	
				else
				{
					muestra(pila, &compa);
					pc=prioridad(compa);
					if(compa=='(')
					{
						pila=push(pila, polin[x]);
					}
					else
					{
						if(polin[x]==')')
						{
							muestra(pila, &compa);
							pila=pop(pila);
							while(compa!='(')
							{
								if( compa == '+' || compa == '-'  || compa == '*' || compa == '/'|| compa == '^' )
									epos=push(epos, compa);
								muestra(pila, &compa);
								pila=pop(pila);
							}
						}
						else
						{
							if(pr>pc )
								pila=push(pila, polin[x]);
							else
							{
								while((pc>pr || pc==pr) && compa!='#' && compa!='(')
								{
									pila=pop(pila);
									if( compa == '+' || compa == '-'  || compa == '*' || compa == '/'|| compa == '^' )
										epos=push(epos,compa);
									muestra(pila, &compa);
									pc=prioridad(compa);	
								}
								pila=push(pila, polin[x]);
							}
						}	
					}	
				}	
			}
		}
		if(x==longi-1)//se llega al final de la pila
		{
			while(pila!=NULL)
			{
				muestra(pila, &compa);
				pila=pop(pila);
				if(compa == '^' || compa == '*' || compa == '/' || compa == '+' || compa == '-' )
					epos=push(epos,compa);
			}
		}
	}
	return epos;
}
double evaluarPos(struct nodo *epos, struct nodo2 *pila2, char incog[], double valor[], int centi, int cantidad)
{ 
	int pr, x;
	char  compa;
	double numero=0.0,resul=0.0, A=0.0, B=0.0;
	epos=push(epos, ')'); //se agrega el parentesis izquierdo que marca el final
	while(epos!=NULL)
	{
		
		mostrarIzq(epos, &compa);
		pr=prioridad(compa);
		if(pr==0)
		{
			if(centi==1)
			{
				if(compa>='a' && compa<='z')
				{
					for(x=0; x<cantidad; ++x)
					{
						if(compa==incog[x])
							numero=valor[x];	
					}
				}
				else
					numero=(double)(compa-'0');
			}
			else
				numero=(double)(compa-'0');
			pila2=push2(pila2, numero);
		}
		else
		{
			if(compa!=')')
			{
				muestra2(pila2, &A);
				pila2=pop2(pila2);
				muestra2(pila2, &B);
				pila2=pop2(pila2);
				resul=operacion(compa,  A ,B);
				pila2=push2(pila2, resul);
			}
		}
		epos=borrarIzq(epos);
	}	
	pila2=pop2(pila2);
	return resul;
}
double operacion(char o, double A ,double B)
{
	double opera=0.0;
	switch(o)
	{
		case '+':
			opera=B+A;
		break;
		case '-':
			opera=B-A;
		break;
		case '^':
			opera=pow( B, A);
		break;
		case '/':
			opera=B/A;
		break;
		case '*':
			opera=B*A;
		break;
	}
	return opera;
}
void imprimir(struct nodo *P)
{
	struct nodo *Q;
	if(P==NULL)
		printf("Lista vacia\n");	
	else
	{
		Q=P;
		while(Q!=NULL)
		{
			printf("%2c", Q->info);
			Q=Q->liga;
		}
		printf("\n");
	}
}

