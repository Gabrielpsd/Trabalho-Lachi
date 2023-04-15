/* implementação da biblioteca quadrado_h.h */ 

#include <stdio.h> 
#include <stdlib.h> /* srand(), rand() */ 
#include <time.h> /* time() */ 


#include "conio_v3.2.4.h" /* teXtbackground()*/ 
#include "console_v1.5.4.h" /* COORD , outra soncole*/ 
#include "quadradoAnimado.h" /* cria_janela() */

#define DEPURACAO 0
/* criacao da janela onde o jogo sera executado*/

void set_ambiente(CONSOLE *console, int status )
{
	if(status){
		
		/* armazena todos os valores atuais do console 
		assim como sua posicao maxima, para que o console de usuario 
		seja configurado no jogo e depois consiga retornar ao finalizar o programa
		*/
		
		console->dimensao_inicial = getPosicaoJanela();	
		console->dimensao_maxima = MaxDimensaoJanela();
		console->posicao_inicial = getPosicaoJanela();

		/* em alguns casos os valores iniciais da janela podem vir negativos 
			caso isso ocorra o programa ira determinar um valor valido para os parametros 
			para que quando forem utilizados eles consigam gerar um retorno
		*/
		if(console->dimensao_inicial.X <= 0 || console->dimensao_inicial.Y <= 0)
			{
				console->dimensao_inicial = console->dimensao_maxima; 
			}
		
		if(console->posicao_inicial.X < 0 || console->posicao_inicial.Y < 0 )
		{
				console->posicao_inicial.X = 0; 
				console->posicao_inicial.Y = 0;
		}
		
		/* configura a tela do usuario */ 
		setPosicaoJanela(0,0);
		setDimensaoJanela(console->dimensao_maxima.X, console->dimensao_maxima.Y);
		setEstadoBarraTarefas(INVISIVEL);
		setTituloConsole(TITULO);	
		
	}else{
		setPosicaoJanela(console->posicao_inicial.X,console->posicao_inicial.Y);
		setDimensaoJanela(console->dimensao_inicial.X,console->dimensao_inicial.Y);
		setEstadoBarraTarefas(VISIVEL);
	}
}

/* funcao que ira  criar a Janela na tela 

	 como a janela esta em modo teXto, podemos imprimir utilizando duas funcoes da bibliteca conio, a que troca a cor do fundo do teXto
	 e a funcao que cria uma janela, nesse caso estaremos criando uma janela com espessura de 1(linha ou coluna) logo ela sera uma linha vertical ou horizontal 
	 na tela
*/

void gerencia_janela(JANELA *Janela, int cor, CONSOLE console)
{
	int i, tamanho, RefX, RefY; 
	clrscr();
	textbackground(9);
	
	/* para criar a janela sera criada quatro funcoes que tem como controle o tamanho da linha e da coluna
	essas funcoes serao 4 for's para criar as linhas e as colunas
	*/
	RefX = (console.dimensao_maxima.X/2)/2;
	RefY = (console.dimensao_maxima.Y/2)/2; 
		
	for(i = 0; i < Janela->linha; ++i)
	{
		/* linha superior */ 
		gotoxy(RefX + Janela->ponto1->X + i,RefY + Janela->ponto1->Y);
		putchar(32);
		
		/*linha inferior*/
		gotoxy(RefX + Janela->ponto1->X+i,RefY +Janela->ponto2->Y);
		putchar(32);
	
	}

	for(i = 0; i <= Janela->coluna; ++i)
	{
		/* coluna horizontal da esquerda */ 
		gotoxy(RefX + Janela->ponto1->X,RefY +Janela->ponto1->Y + i);
		putchar(32);
		
		/*coluna horizontal direita */ 
		gotoxy(RefX + Janela->ponto2->X,RefY +Janela->ponto1->Y+i);
		putchar(32);
	}
	
	gotoxy(Janela->centro->X,Janela->centro->Y);
}

void cria_janela1(JANELA janela, int corBorda, CONSOLE console)
{	
	
		/*
	|---------------  Cria janela  ---------------------|
	|	A funcao ira criar as janelas coloridas			|
	|	onde ocorre as movimentações do jogo 			|
	|	a função trablalha utilizando a window da conio	|
	|	e funciona com uma sobreposição de duas janelas |
	|   A mais externa(a Borda) e a mais interna		|
	|  (onde o jogo ocorrera em si) com a coloração 	|
	|	preta											|
	|---------------------------------------------------|
	*/	textbackground(0);
		gotoxy((console.dimensao_maxima.X/2)/2,(console.dimensao_maxima.Y/2)/2);
		textbackground((corBorda%corBorda)+7);
		window(janela.ponto1->X, janela.ponto1->Y, janela.ponto2->X, janela.ponto2->Y);
		gotoxy(1,1);
		clrscr();
}


void cria_ponto(JANELA *Janela,CONSOLE console)
{
	Janela->ponto1 = &(Janela->ref1);
	Janela->ponto2 = &(Janela->ref2);
	Janela->centro = &(Janela->refC);
	
	Janela->linha = 80;
	Janela->coluna = 20;
	
	
	Janela->ponto1->X = 5;
	Janela->ponto1->Y = 5;
	
	Janela->ponto2->X = Janela->ponto1->X + Janela->linha ;
	Janela->ponto2->Y = Janela->ponto1->Y + Janela->coluna ;
	
	Janela->centro->X = (Janela->ponto1->X + (Janela->linha/2)) + (console.dimensao_maxima.X/2)/2;
	Janela->centro->Y = (Janela->ponto1->Y + (Janela->coluna/2)) + (console.dimensao_maxima.Y/2)/2;
}
/*
void cria_janela2(JANELA janela)
{
	textbackground(8);
	window(janela.ponto1->X +1, janela.ponto1->Y+1, janela.ponto2->X-1, janela.ponto2->Y-1);
	getchar();
	gotoxy(1,1);
	textbackground(0);
	clrscr();
	
}
*/

void inicia_jogo()
{	
	int cor; 
	JANELA *Janela, refJanela;
	CONSOLE *monitor , Pointer_console;
	
	monitor = &Pointer_console;
	Janela = &refJanela;
	
	srand(time(NULL));
	
	cor = rand() % 15 + 1;
	
	set_ambiente(monitor, 1);
	
	cria_ponto(Janela, *monitor);
	
	gerencia_janela(Janela, cor, *monitor);

	depuracao(*Janela, *monitor, DEPURACAO);
	
	textbackground(0);
	getchar();
	clrscr();
	
	gotoxy(1,1);
	set_ambiente(monitor, 0);
	
	fim_jogo(monitor);
}

void fim_jogo(CONSOLE * monitor)
{
	monitor->dimensao_inicial = monitor->dimensao_inicial;
}

void depuracao(JANELA Janela, CONSOLE console, int depuracao)
{
	textcolor(RED);
	textbackground(BLACK);
	if(depuracao){
	printf("\n--------------- Dados do console --------------------\n");
	printf("dimnesaoIN X- %d \n",console.dimensao_inicial.X);
	printf("dimensaoIN Y- %d \n",console.dimensao_inicial.Y);
		
	printf("PosicaoIN X- %d \n",console.posicao_inicial.X);
	printf("PosicaoIN Y- %d \n",console.posicao_inicial.Y);
	
	printf("dimnesaoMAX X- %d \n",console.dimensao_maxima.X);
	printf("dimensaoMAX Y- %d \n",console.dimensao_maxima.Y);
	printf("--------------------------------------------------------\n");
	
	printf("--------------- Dados da janela    --------------------\n");
	
	printf("P1 X - %d \n",Janela.ponto1->X);
	printf("P1 Y - %d \n",Janela.ponto1->Y);
	
	printf("P2 X - %d \n",Janela.ponto2->X);
	printf("P2 Y - %d \n",Janela.ponto2->Y);
	
	printf("CENTRO X - %d \n",Janela.centro->X);
	printf("CENTRO Y - %d \n",Janela.centro->Y);
	
	
	printf("linha- %d \n",Janela.linha);
	printf("coluna - %d \n",Janela.coluna);
	
	
	printf("------------------------------------------------------------\n");
	}
}