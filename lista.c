void createL(List *L){
	L->head=L->tail=NULL;
}
int isEmptyL(List L){
	if(L.head==NULL)
		return true;
	else
		return false;
}

Node *createNode(){
	Node *N;
	N=(Node *)malloc(sizeof(Node));
	return N;
}

void insertAtStart(List *L,Element ncas, Element soe, Node *X){
	Node *N;
	N=createNode();
	N->ncas=ncas;
	N->soe=soe;
	N->sob=X;
	if(!isEmptyL(*L)){
		N->next=L->head;
		L->head=N;
	} 
	else{
		L->head=L->tail=N;
		N->next=NULL;
	}
}

void insertAtEnd(List *L,Element ncas, Element soe, Node *X){
	Node *N;
	N=createNode();
	N->ncas=ncas;
	N->soe=soe;
	N->sob=X;
	if(!isEmptyL(*L)){
		L->tail->next=N;
		L->tail=N;
		N->next=NULL;
	}else{
		L->head=L->tail=N;
		N->next=NULL;
	}
}

void insertAfterNode(List *L,Element ncas, Element soe, Node *X, Node *Ant){
	Node *N;
	N=createNode();
	N->ncas=ncas;
	N->soe=soe;
	N->sob=X;
	if(!isEmptyL(*L)){
		N->next=Ant->next;
		Ant->next=N;
	}else{
		if(Ant==L->tail){
			(L->tail)->next=Ant;
			L->tail=Ant;
			Ant->next=NULL;
		}
		else{
			L->head=L->tail=N;
			N->next=NULL;
		}
	}
}

Node *searchElement(Element dato, List *L){
	Node *aux;
	aux=L->head;
	while((aux->ncas!=dato)&&aux!=NULL){
		aux=aux->next;
	}
	return aux;
}
void deleteList(List *L){
	Node *aux;
	if(!isEmptyL(*L)){
		do{
			aux=L->head;
			L->head=aux->next;
			free(aux);
		}while(L->head!=NULL);
	}
	else
		printf("\nError: Lista vacia\n.");
}

/*
Element deleteAtStart(List *L){
	Node *aux;
	char a='\n';
		
	aux=L->head;
	a=aux->e;
	L->head=aux->next;
	free(aux);
	
	return a;	//Modificar para que devuelva un element
}
Element deleteAtEnd(List *L){
	Node *aux,*ant;
	char a='\n';
	
	aux=L->tail;
	ant=searchAnt(aux,L);
	free(aux);
	L->tail=ant;
	ant->next=NULL;
	
	return a; //Modificar para que devuelva un element
}
Element deleteNode(List *L,Node *act){ //Corregir
	Node *aux;
	char a='\n';
	
	aux=act;
	act=act->next;
	free(aux); //Modificar para que devuelva un element
	
	return a;
}*/
void showList(List *L){
	Node *aux=L->head;
	printf("\nLista\n");
	while(aux!=NULL){
		printf("#%i\nSOE=%i\n\n",aux->ncas,aux->soe);
		aux=aux->next;
	}
}


/*Empiezan nuestras funciones de serpientes y escaleras*/
void createPlayer(Player *J,List *Tablero,int joc){
	J->pos=Tablero->head;
	J->joc=joc;
}

int roll(int joc){ //Tirar()
	if(joc){
		printf("Presiona una tecla para tirar el dado\n");
		getchar();
		fflush(stdin);
	}
	else{
		printf("Tirando el dado\n");
	}
	srand(time(NULL));
	return (rand()%6)+1;
}

int turn(List *Tablero, Player *J,Player *P, int a){
	int dado,cf,win,vof;
	printf("[Turno del jugador %i]\n",a+1);
	
	if(!a){
		updateBoard(J->pos->ncas,P->pos->ncas,Tablero);
	}
	else{
		updateBoard(P->pos->ncas,J->pos->ncas,Tablero);
	}
	dado=roll(J->joc); //Tirar dado
	Sleep(1000);
	system("cls");
	printf("[Turno del jugador %i]\n",a+1);
	printf("Tu dado salio: %i\t",dado);
	printf("Fuiste de la casilla #%i ",J->pos->ncas);
	cf=move(Tablero,J,dado); //Mover al jugador
	printf("a la #%i\n",cf);
	
	if(!a){
		updateBoard(J->pos->ncas,P->pos->ncas,Tablero);
	}
	else{
		updateBoard(P->pos->ncas,J->pos->ncas,Tablero);
	}
	Sleep(2000);
	system("cls");
	printf("[Turno del jugador %i]\n",a+1);
	if(!a){
		updateBoard(J->pos->ncas,P->pos->ncas,Tablero);
	}
	else{
		updateBoard(P->pos->ncas,J->pos->ncas,Tablero);
	}
	win=isWin(cf);
	vof=seon(J);
	if(vof!=-1){
		Sleep(3000);
		system("cls");
		printf("[Turno del jugador %i]\n",a+1);
		if(!a){
			updateBoard(J->pos->ncas,P->pos->ncas,Tablero);
		}
		else{
			updateBoard(P->pos->ncas,J->pos->ncas,Tablero);
		}
	}
	printf("\n\n");
	return win;
}
int move(List *Tablero,Player *J,int dado){
	int posi=J->pos->ncas,posf=posi+dado;
	if(posf>BOARD){
		Sleep(1000);
		printf("\nQuemaste el dado, ");
		posf=BOARD-(posf%BOARD);
		if(posf<posi){ //Se mueve y se quema el dado (Se regresa)
			printf("Te regresaras %i casillas",posi-posf);
			J->pos=searchElement(posf,Tablero); 
			return posf;
		}
		else if (posi==posf){ //No se mueve
			printf("no te mueves\n");
			return posi;
		}
	}
	dado=posf-posi;
	int cont;
	//Se mueve normal 
	cont=0;
	while(cont<dado){
		J->pos=J->pos->next;
		cont++;
	}
	return posf;
}

int isWin(int ncas){
	if(ncas==BOARD)
		return true;
	else
		return false;
}

int seon(Player *J){
	printf("\n");
	int var=((J->pos)->soe);
	if((J->pos)->soe==1){
		printf("Caiste en una escalera\t");
		J->pos=J->pos->sob;
		printf("Subiste a la casilla #%i\n",J->pos->ncas);
	}
	else if((J->pos)->soe==0){
		printf("Caiste en una serpiente\t");
		J->pos=J->pos->sob;
		printf("Bajaste a la casilla: #%i\n",J->pos->ncas);
	}
	return var;
}

void createBoard(List *Tablero){
	createL(Tablero);
	int cont=1;
	do{
		insertAtEnd(Tablero,cont,-1,NULL);
		cont++;
	}while(cont<=BOARD);
}

void createSOE(List *Tablero,int n1,int n2,int soe){
	int flag=-1;
	Node *aux1,*aux2;
	if(n1>n2){
		flag=1;
	}
	else if(n1<n2)
		flag=0;
	aux1=searchElement(n1,Tablero);
	aux2=searchElement(n2,Tablero);
	if(flag!=-1){
		if(soe){//V ESCALERA 1
			if(flag){ //
				aux2->soe=soe;
				aux2->sob=aux1;
			}
			else{
				aux1->soe=soe;
				aux1->sob=aux2;
			}
		}
		else{//F SERPIENTE 0
			if(flag){ //
				aux1->soe=soe;
				aux1->sob=aux2;
			}
			else{
				aux2->soe=soe;
				aux2->sob=aux1;
			}
		}
	}
	else
		printf("ERROR: Se esta apuntando a si misma\n");
}
void updateBoard(int p1,int p2,List *Tablero){
	int aux=BOARD,c=0,res=BOARD%10,i=aux,f=(BOARD/10),a=0;
	Node *d;
	printf("+-------------------------------------------------------------------------------+\n");
	do{
		if((f%2)){
			i=i-10;
			i++;		
			while((i+c)<=aux){
				printf("|%i",i+c);
				if(p1==(i+c))
					printf(" x");
				if(p2==(i+c))
					printf(" o");
				printf("\t");
				c++;
			}
			c=0;
			printf("|\n");
			while((i+c)<=aux){
				d=searchElement(i+c,Tablero);
				if((d->soe)!=-1){
					if(d->soe){
						printf("|" G "[%i]" RESET,(d->sob)->ncas);
					}
					else{
						printf("|" R "[%i]" RESET,(d->sob)->ncas);
					}
					printf("\t");
				}
				else{
					printf("|\t");
				}
				c++;
			}
			aux=aux-10;
			i--;
		}
		else{
			aux=aux-10;
			while((i-a)>aux){
				printf("|%i",(i-a));
				if(p1==(i-a))
					printf(" x");
				if(p2==(i-a))
					printf(" o");
				printf("\t");
				a++;
			}
			a=0;
			printf("|\n");
			while(i>aux){
				d=searchElement(i+c,Tablero);
				if((d->soe)!=-1){
					if(d->soe){
						printf("|" G "[%i]" RESET,(d->sob)->ncas);
					}
					else{
						printf("|" R "[%i]" RESET,(d->sob)->ncas);
					}
					printf("\t");
				}
				else{
					printf("|\t");
				}
				i--;
			}
		}
		printf("|\n");
		printf("+-------------------------------------------------------------------------------+\n");
		c=0;
		f--;
	}while(f!=0);
}