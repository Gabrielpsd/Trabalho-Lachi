/* implementação da biblioteca quadrado_h.h */ 

#include <stdio.h> 
#include <stdlib.h> /* srand(), rand() */ 
#include <time.h> /* time() */ 


#include "conio_v3.2.4.h" /* teXtbackground()*/ 
#include "console_v1.5.4.h" /* COORD , outra soncole*/ 
#include "quadradoAnimado.h" /* cria_janela() */

#define DEPURACAO 0


	/*
	|---------------  INICIO ---------------------------|
	|	 Unica funcao fora da ordem alfabetica 			|
	|	por ser a principal do programa, ela aparecera	|
	|	em primeiro;									|
	|													|
	|	 Atraves dessa funcao que o programa executa as |
	|	chamadas para as outras funcoes do programa		|
	|---------------------------------------------------|
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

}

	/*
	|---------------  Cria ponto ---------------------------|
	|	 Para que possa ser criado as zonas de impacto		|
	|	do quadrado interno, ele seguira refernecia por 3 	|
	|	pontos princiapais(centro e diagonais) essa funcao 	|
	|	tem o objetivo de criar esses valores inicias para 	|
	|	o programa trabalhar								|
	|-------------------------------------------------------|
	*/
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
	|---------------  Gerencia Janela ----------------------|
	|	 Cria a janela principal.							|	
	|	A funcao utiliza os 3 pontos da estrutura PONTO 	|
	|	como referencia, trocando a cor do fundo 		 	|
	|	caracter por caracter conectando os  pontos das  	|
	|	diagonais											|
	|-------------------------------------------------------|
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

	/*
	|---------------  Set ambiente -------------------------|
	|	 Configura o console inicial ao mesmo tempo			|	
	|	ele armazena os dados para que a janela retorne		|
	|	a como estava no inicio do programa 	 		 	|
	|	 Essa funcao tem tanto a atividade de configurar   	|
	|	o console inicial como de restaurar as configurações|
	|	que estavam anteriormente							|
	|-------------------------------------------------------|
	*/

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


/*
	|---------------  depuracao   --------------------------|
	|	 Não utilizado na versão final 						|
	|	serve apenas para imprimir o valor das variaveis 	|
	|	quando necessario									|
	|-------------------------------------------------------|
	*/
	
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