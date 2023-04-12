/* implementação da biblioteca quadrado_h.h */ 

#include <stdio.h> 
#include "conio_v3.2.4.h" /* teXtbackground()*/ 
#include "console_v1.5.h" /* COORD */ 

/* funcao que ira  criar a Janela na tela 

	 como a janela esta em modo teXto, podemos imprimir utilizando duas funcoes da bibliteca conio, a que troca a cor do fundo do teXto
	 e a funcao que cria uma janela, nesse caso estaremos criando uma janela com espessura de 1(linha ou coluna) logo ela sera uma linha vertical ou horizontal 
	 na tela
*/

void cria_janela(COORD *ponto1, COORD *ponto2,int corBorda)
{	
	printf("Entrou aqui!!! \n");
	
	/*
	ponto1->X = 6;
	ponto1->Y = 7;
	
	ponto2->X = 10;
	ponto2->Y = 11;
	
	*/
	gotoxy(4,5);
	
	textbackground(10);
	
	/* ------------------  linha superior  ------------------
		regra da criacao: os valores do eiXo X alteram, mas o do eiXo Y permanecem(sempre do maior Y)
	 
	window(ponto1->X, ponto1->Y, ponto2->X, ponto1->Y);
	*/
	
	window(6,7,10,11);
	
	/* ------------------  linha inferior ------------------
		regra da criacao: os valores do eiXo X alteram, mas o do eiXo Y permanecem(sempre do menor Y)
	*/ 	
	window(ponto1->X, ponto2->Y, ponto2->X, ponto2->Y);
	
	/* ------------------  coluna esquerda ------------------
		regra da criacao: os valores do eiXo X parmanecem(sempre do menor ), mas o do eiXo Y alteram
	*/ 	
	window(ponto1->X, ponto1->Y, ponto1->X, ponto2->Y);
	
	/* ------------------  coluna esquerda ------------------
		regra da criacao: os valores do eiXo X parmanecem(sempre do menor ), mas o do eiXo Y alteram
	*/ 	
	window(ponto2->X, ponto1->Y, ponto2->X, ponto2->Y);
}