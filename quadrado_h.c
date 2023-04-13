/* implementação da biblioteca quadrado_h.h */ 

#include <stdio.h> 
#include <stdlib.h> /* srand(), rand() */ 


#include "conio_v3.2.4.h" /* teXtbackground()*/ 
#include "console_v1.5.h" /* COORD */ 
#include "quadrado_h.h" /* cria_janela() */



// criacao da janela onde o jogo sera executado
void set_ambiente(tela *console)
{
		
		 console->dimensao_atual = tamanhoJanelaConsole();
		 console->dimensao_maxima = MaxDimensaoJanela();
		 console->inicial_tela = posicaoJanela();
		 
		 setPosicaoJanela(0,0);
		 setDimensaoJanela(console->dimensao_maxima.X, console->dimensao_maxima.Y);
		 setTituloConsole(TITULO);
		 
		 
}

/* funcao que ira  criar a Janela na tela 

	 como a janela esta em modo teXto, podemos imprimir utilizando duas funcoes da bibliteca conio, a que troca a cor do fundo do teXto
	 e a funcao que cria uma janela, nesse caso estaremos criando uma janela com espessura de 1(linha ou coluna) logo ela sera uma linha vertical ou horizontal 
	 na tela
*/

void cria_janela(COORD *ponto1, COORD *ponto2,int corBorda)
{	

	/*
	ponto1->X = 6;
	ponto1->Y = 7;
	
	ponto2->X = 10;
	ponto2->Y = 11;
	
	*/
	gotoxy(4,5);
	
	textbackground(corBorda);
	
	/* ------------------  linha superior  ------------------
		regra da criacao: os valores do eiXo X alteram, mas o do eiXo Y permanecem(sempre do maior Y)
	*/
	window(ponto1->X, ponto1->Y, ponto2->X, ponto1->Y);
	
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

void inicia_jogo()
{	tela *monitor, Pointer_console;
	
	monitor = &Pointer_console;

	int cor;
	
	srand(time(NULL));
	
	cor = rand() % 15 + 1; 
	COORD *ponto1, *ponto2,p1,p2;  
	
	ponto1 = &p1;
	ponto2 = &p2;
	
	ponto1->X = 6;
	ponto1->Y = 7;
	

	ponto2->X = 50;
	ponto2->Y = 70;
	
	set_ambiente(monitor);
	
	cria_janela(ponto1,ponto2,cor);
	
	fim_jogo(monitor);
}

void fim_jogo(tela * monitor)
{
	clrscr();
	setDimensaoJanela(monitor->inicial_tela.X,monitor->inicial_tela.Y);
	setPosicaoJanela(monitor->inicial_tela.X,monitor->inicial_tela.Y);
}