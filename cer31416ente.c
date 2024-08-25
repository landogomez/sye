#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
typedef int Element;
#include "lista.h"
void main(){
		List *Tablero;
		//Creacion del tablero
		createBoard(Tablero);

		//Creacion de las serpientes y escaleras
		createSOE(Tablero,24,37,1);
		createSOE(Tablero,4,17,1);
		createSOE(Tablero,12,27,1);
		createSOE(Tablero,31,44,1);
		createSOE(Tablero,6,3,0);
		createSOE(Tablero,41,23,0);
		createSOE(Tablero,35,16,0);
		createSOE(Tablero,49,38,0);
		
		//Escalable
		if(BOARD>=100){
			createSOE(Tablero,50,61,1);
			createSOE(Tablero,78,63,0);
			createSOE(Tablero,70,80,1);
			createSOE(Tablero,75,90,1);
			createSOE(Tablero,99,10,0);
			createSOE(Tablero,5,69,1);
		}
		
		//Creacion de los jugadores
		Player P1,P2;
		int opt,win=0,exit;
		do{
			createPlayer(&P1,Tablero,1);
			do{
				system("cls");
				printf("\t" Y "======================" RESET  "\n\n\t" R "Serpientes" RESET " y " G "escaleras" RESET "\n\n\t" Y"======================" RESET "\n\n\t1. Un jugador\n\t2. Dos jugadores\n\t3. Salir\n\t> ");
				scanf("%i",&opt);
				fflush(stdin);
				switch(opt){
					case 1:
						createPlayer(&P2,Tablero,0);
						break;
					case 2:
						createPlayer(&P2,Tablero,1);
						break;
					case 3:
						win=1;
						exit=1;
						break;
					default:
						printf("\tNo existe esa opcion\n");
						Sleep(1000);
				}
			}while(opt<=0||opt>=4);

			//Inicializacion de los parametros del juego
			int cont=-1;

			//Partida
			while(!win){
				system("cls");
				cont=(cont+1)%2;	
				if(cont==0){
					win=turn(Tablero,&P1,&P2,cont);
				}
				else{
					win=turn(Tablero,&P2,&P1,cont);
				}
				printf("[FIN DEL TURNO]\nPresiona una tecla para cambiar de turno");
				getchar();
				system("cls");
			}
			//Verificacion del jugador ganador
			if(opt!=3){
				printf("======================\n\tGana J%i\n=====================\n",cont+1);
				printf("Presione una tecla para continuar\n");
				getchar();
				win=0;
			}
		}while(opt!=3);
		printf("\nAdios");
		deleteList(Tablero);
}