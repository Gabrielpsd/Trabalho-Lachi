/* implementação da biblioteca quadrado_h.h */ 

#include <stdio.h> 
#include <stdlib.h> /* srand(), rand() */ 


#include "conio_v3.2.4.h" /* teXtbackground()*/ 
#include "console_v1.5.h" /* COORD */ 
#include "quadrado_h.h" /* cria_janela() */



// criacao da janela onde o jogo sera executado
void set_ambiente(CONSOLE *console, int status )
{
	if(status){
		setEstadoBarraTarefas(INVISIVEL);
		COORD MaxDimensao = MaxDimensaoJanela();	
		
		console->dimensao_atual = tamanhoJanelaConsole();
		console->dimensao_maxima = MaxDimensaoJanela();
		console->inicial_tela = posicaoJanela();

		setPosicaoJanela(0,0);
		setDimensaoJanela(console->dimensao_maxima.X, console->dimensao_maxima.Y);
		setTituloConsole(TITULO);
	}else{
		setDimensaoJanela(1,1);
		setDimensaoJanela(console->dimensao_atual.X,console->dimensao_atual.Y);
		setEstadoBarraTarefas(VISIVEL);
	}
}

/* funcao que ira  criar a Janela na tela 

	 como a janela esta em modo teXto, podemos imprimir utilizando duas funcoes da bibliteca conio, a que troca a cor do fundo do teXto
	 e a funcao que cria uma janela, nesse caso estaremos criando uma janela com espessura de 1(linha ou coluna) logo ela sera uma linha vertical ou horizontal 
	 na tela
*/

void cria_janela(COORD *ponto1, COORD *ponto2,int corBorda, int estado,CONSOLE *console)
{	

	if(estado)
	{	
		textbackground(0);
		window(1,1,console->dimensao_maxima.X, console->dimensao_maxima.Y);
		textbackground(corBorda);
	
	/* ------------------  linha superior  ------------------
		regra da criacao: os valores do eiXo X alteram, mas o do eiXo Y permanecem(sempre do maior Y)
	*/
		window(ponto1->X, ponto1->Y, ponto2->X, ponto2->Y);
		textbackground(2);
		window(ponto1->X +1, ponto1->Y+1, ponto2->X-1, ponto2->Y-1);
	}
	else
	{	
		textbackground(0);
	
		clrscr();
		
	}
}

void inicia_jogo()
{	
	CONSOLE *monitor , Pointer_console;
	
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
	
	fim_jogo(monitor);
}

void fim_jogo(CONSOLE * monitor)
{
	clrscr();
	setDimensaoJanela(monitor->inicial_tela.X,monitor->inicial_tela.Y);
	setPosicaoJanela(monitor->inicial_tela.X,monitor->inicial_tela.Y);
}