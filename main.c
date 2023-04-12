/* 

	programa: Quadrado animado 
	Descrição: O programa é uma janela que abre no prompt de comando do computador, essa janela sera interativa e  o usuario podera mudar sua cor e seu tamanho
	dentro dessa janela havera um quadrado que ficara se movimentando esse quadrado pode ter suas propriedade de direção e velocidade alteradas pelo usuario caso ele 
	assim dejesar e entrar com as teclas corretas;
	Programador: Gabriel Pereira dos Santos Dias
	data de modificação: 11/04/2023
	
	*-------- Regras de utilização do programa -----* 
	
	Obs: Para evitar erros durante a execução recomenda-se que configure seu prompt de comando para que utilize as propriedades herdadas do prompt 
	
	
*/
#include <stdio.h> /* NULL */ 
#include <stdlib.h> /* srand(), rand() */ 
#include <time.h> /* time()*/ 

#include "console_v1.5.h" /* COORD. */  
#include "quadrado_h.h" /* cria janela */ 

int main(int argc, char *argv[])
{	
	printf("Entrou aqui (1) \n");
	int cor;
	
	srand(time(NULL));
	
	cor = rand() % 15 + 1; 
	printf("Entrou aqui (2) \n");
	COORD *ponto1, *ponto2;  

	printf("Entrou aqui (3) \n");
	ponto1->X = 6;
	ponto1->Y = 7;
	
	printf("Entrou aqui (4) \n");
	ponto2->X = 10;
	ponto2->Y = 11;
	
	
	printf("Entrou aqui (5) \n");
	cria_janela(ponto1,ponto2,5);
	printf("Entrou aqui (6) \n");
	return 0;
}