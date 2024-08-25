#include <stdio.h>
#define BOARD 50
void main(){
	int aux=BOARD,c=0,res=BOARD%10,i=aux;
	
	int f=(BOARD/10);
	printf("+-------------------------------------------------------------------------------+\n");
	do{
		if((f%2)){
			i=i-10;
			i++;		
			while((i+c)<=aux){
				printf("|%i\t",i+c);
				c++;
			}
			aux=aux-10;
			i--;
		}
		else{
			aux=aux-10;
			while(i>aux){
				printf("|%i\t",i);
				i--;
			}
		}
		c=0;
		f--;
		printf("|\n");
	}while(f!=0);
	printf("+-------------------------------------------------------------------------------+\n\n");
}