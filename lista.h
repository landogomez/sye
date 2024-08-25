#define true 1
#define false 0
#define BOARD 50 //Escalable a múltiplos de 10
#define R "\x1b[31m"
#define G "\x1b[32m"
#define Y "\x1b[33m"
#define B "\x1b[34m"
#define M "\x1b[35m"
#define C "\x1b[36m"
#define RESET "\x1b[0m"
typedef struct node{
	Element ncas; 		//Numero de casilla
	Element soe;		//Numero que identifica si es serpiente o escalera 1 Escalera ,0 Serpiente y -1 Nada
	struct node *sob; 	//Apuntador hacia donde el jugador se mueve si es serpiente o escalera APUNTADOR - NULL
	struct node *next; 	//Next de la lista
}Node;

typedef struct player{
	Node *pos;		//Apuntador a casilla
	Element joc;	//Jugador o computadora 1 jugador y 0 maquina
}Player;

typedef struct list{
	Node *head;
	Node *tail;
}List;

void createL(List *L);
int isEmptyL(List L);
Node * createNode();
void insertAtStart(List *L,Element ncas, Element soe, Node *N);
void insertAtEnd(List *L,Element ncas, Element soe, Node *N);
void insertAfterNode(List *L,Element ncas, Element soe, Node *N, Node *Ant);
Node *searchElement(Element dato, List *L);
Element deleteAtStart(List *L);
Element deleteAtEnd(List *L);
Element deleteNode(List *L,Node *act);
void showList(List *L);

//Juego
void createPlayer(Player *J,List *Tablero,int joc); 	//Pone a los jugadores en la primer casilla
int roll(int joc);										//Tira los dados dependiendo si es un jugador o una computadora
int turn(List *Tablero, Player *J,Player *P, int a);						//Se encarga de realizar el turno de un jugador
int move(List *Tablero,Player *J,int dado);				//Mueve el jugador a traves del tablero
int isWin(int ncas);									//Verifica si el jugador gano
int seon(Player *J);									//Verifica si la casilla en la que se termino el jugador existe una serpiente o escalera
void createBoard(List *Tablero);						//Crea el tablero
void createSOE(List *Tablero,int n1,int n2,int soe);	//Crea las serpientes y escalera
void updateBoard(int p1,int p2,List *Tablero);

#include "lista.c"