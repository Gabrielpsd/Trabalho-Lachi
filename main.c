/* 

	programa: Quadrado animado 
	Descrição: O programa é uma janela que abre no prompt de comando do computador, essa janela sera interativa e  o usuario podera mudar sua cor e seu tamanho
	dentro dessa janela havera um quadrado que ficara se movimentando esse quadrado pode ter suas propriedade de direção e velocidade alteradas pelo usuario caso ele 
	assim dejesar e entrar com as teclas corretas;
	Programador: Gabriel Pereira dos Santos Dias
	data de modificação: 11/04/2023
	
	*-------- Regras de utilização do programa -----* 
	
	Obs: Para evitar erros durante a execução recomenda-se que configure seu prompt de comando para que utilize as propriedades herdadas do prompt 
	
	codigo para compilação: gcc main.c -o saida.exe conio_v3.2.4.c console_v1.5.c graphics_v1.1.c quadrado_h.c -lgdi32
	
*/
#include <stdio.h> /* NULL */ 
#include <stdlib.h> /* srand(), rand() */ 
#include <time.h> /* time()*/ 

#include "console_v1.5.h" /* COORD. */  
#include "quadrado_h.h" /* cria janela */ 

int main(int argc, char *argv[])
{	
	printf("estou aqui(1)\n");
	CONSOLE *console;
	int cor;
	srand(time(NULL));
	
	cor = rand() % 15 + 1; 
	COORD *ponto1, *ponto2,p1,p2;  
	int linha = 100,coluna = 50;
	
	ponto1 = &p1;
	ponto2 = &p2;
	
	ponto1->X = 6;
	ponto1->Y = 7;
	

	ponto2->X = ponto1->X + linha;
	ponto2->Y = ponto1->Y + coluna;
	
	clrscr();
	set_ambiente(console,ATIVAR);
	
	gotoxy(4,5);
	cria_janela(ponto1,ponto2,cor,ATIVAR, console);
	
	gotoxy(0,0);
	cria_janela(ponto1,ponto2,cor,DESATIVAR,console);
	set_ambiente(console,DESATIVAR);
	
	
	return 0;
}