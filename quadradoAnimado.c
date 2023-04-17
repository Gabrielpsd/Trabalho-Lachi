/* implementação da biblioteca quadrado_h.h */ 

#include <stdio.h> 
#include <stdlib.h> /* srand(), rand() */ 
#include <time.h> /* time() */ 


#include "conio_v3.2.4.h" /* teXtbackground()*/ 
#include "console_v1.5.4.h" /* COORD , outra soncole*/ 
#include "quadradoAnimado.h" /* cria_janela() */

#define DEPURACAO 0


/*	|---------------  INICIO ---------------------------|
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
	int cor, direcao; 
	JANELA *Janela, refJanela;
	CONSOLE *monitor , Pointer_console;
	QUADRADO *quadrado, refquad;
	INFO_TELA *tela, Reftela;
	
	monitor = &Pointer_console;
	Janela = &refJanela;
	quadrado = &refquad;
	tela = &Reftela;
	
	srand(time(NULL));
	
	cor = rand() % 15 + 1;
	direcao = rand() % 3 ;
	
	/* apagar depois essa parte */ 
	tela->titulo = TITULO;
	
	set_ambiente(monitor);
	printf("sai do ambiente ");
	getchar();
	
	gerencia_janela(Janela, cor, *monitor);
	printf("sai da janela ");
	getchar();
	
	cria_ponto(Janela, *monitor);	
	cria_quadrado(quadrado,*Janela);
	
	imprime_informacao(*tela,*monitor);
	
	depuracao(*Janela, *monitor, DEPURACAO);
	
	textbackground(0);
	getchar();
	clrscr();
	
	gotoxy(1,1);
	fim_programa(*monitor);
}

/*	|---------------  Cria ponto ---------------------------|
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

/*	|---------------- Cria quadrado-------------------------|
	|		A funcao ira apenas fazer a configuração 		|
	|	inicial do quadrado, essa funcao so é utilizada		|
	|	no inicio do programa. 								|
	|-------------------------------------------------------|
*/

void cria_quadrado(QUADRADO *quadrado, JANELA Janela)
{	
	printf("centro quadrado %uh centro janela %uh",quadrado->centro->X , Janela.centro->X );
	quadrado->centro->X = Janela.centro->X;
	printf("centro quadrado %d centro janela %d",quadrado->centro->X , Janela.centro->X );
	quadrado->centro->Y = Janela.centro->Y;
	
	quadrado->cor = 4;
	
	printf("mandei imprimir");
	imprime_quadrado(*quadrado, ATIVAR);
}

/*	|---------------  Fim programa    ----------------------|
	|	   A funcao ira realizar reconfiguração de 			|
	|	  do ambiente voltando para as configurações inicias|
	|-------------------------------------------------------|
*/

void fim_programa(CONSOLE console){

		setPosicaoJanela(console.posicao_inicial.X,console.posicao_inicial.Y);
		setDimensaoJanela(console.dimensao_inicial.X,console.dimensao_inicial.Y);
		setEstadoBarraTarefas(VISIVEL);
		setCursorStatus(LIGAR);
		
		textbackground(0);
		clrscr();
		gotoxy(1,1);
}


/*	|---------------  Gerencia Janela ----------------------|
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
	
	Janela->ponto1->X += RefX;
	Janela->ponto1->Y += RefY;
	
	Janela->ponto2->X += RefX;
	Janela->ponto2->Y += RefY;
	
	Janela->centro->X += RefX;
	Janela->centro->Y += RefY;
	
	printf("saido da janela ");
}

void imprime_informacao(INFO_TELA tela,CONSOLE console)
{	
	int dimensaoX, dimensaoY;
	/* a mensagem inicial sera impresso no topo da tela */ 
	gotoxy((console.dimensao_maxima.X/2),2);
	textcolor(RED);
	printf("%s",tela.titulo);
	 
	 
	gotoxy((console.dimensao_maxima.X * (0.25)),(console.dimensao_maxima.Y * (0.75)));
	printf("Direcao atual: ");
	
	gotoxy((console.dimensao_maxima.X*0.5),(console.dimensao_maxima.Y*0.75));
	printf("Direcao atual: ");
}

/*	|---------------imprime quadrado-----------------------|
	|       A função realizará a impressão do quadrado 	   |
	|     interno utilizando como referencia o ponto 	   |		
	|	  central que é uma variavel da estrutura que 	   |	
	|	  esta contida na estrutura do quadrado			   |
	|------------------------------------------------------|
*/
	
void imprime_quadrado(QUADRADO quadrado, ATIVIDADE funcao)
{
	int i, j; 
	
	if(funcao)
	{
		textcolor(quadrado.cor);
		/* imprima como se fosse uma matriz*/
		for(i = 0; i < 3 ;++i)
		{
			for(j = 0; j < 3; ++j)
			{
				gotoxy((quadrado.centro->X - 1) +j, (quadrado.centro->Y - 1) + i);
				putchar(42);
			}
		}
	}
	else
	{
		textbackground(BLACK);
		textcolor(BLACK);
		/* imprima como se fosse uma matriz*/
		for(i = 0; i < 3; ++i)
		{
			for(j = 0; j < 3; ++j)
			{
				gotoxy((quadrado.centro->X - 1) +j, (quadrado.centro->Y - 1) + i);
				putchar(32);
			}
		}
	}
}


/* 	|---------------- movimenta quadrado -------------------|
	|		A funcao movimenta quadrado ira realizar 		|
	|	a movimentação do quadrado interno, o parametro de 	|
	|	direção se trata de de um ENUM que foi determinado 	|
	|	no cabecalho;										|
	|		Como o quadrado interno só tera um movimentação |
	|	por vez a movimentação funciona alterando os 		|
	|	parametros X ou Y do quadrado e realiza a chamadas	|
	|	da funcao de impressao com a estrutura modificada 	|
	|-------------------------------------------------------|
*/
 
void movimenta_quadrado(QUADRADO *quadrado, JANELA janela, DIRECAO direcao)
{	
	switch (direcao)
	{
		/* case (0) */ 
		case (CIMA):

			while((quadrado->centro->Y - 2) > janela.ponto1->Y)
			{
				imprime_quadrado(*quadrado, ATIVAR);
				sleep(1);
				imprime_quadrado(*quadrado, DESATIVAR);
				quadrado->centro->Y = (quadrado->centro->Y) - 1 ;
			}
			
			movimenta_quadrado(quadrado, janela, BAIXO);
			break;
		/* case (2) */ 
		case (BAIXO):

			while((quadrado->centro->Y + 2) < janela.ponto2->Y)
			{
				imprime_quadrado(*quadrado, ATIVAR);
				sleep(1);
				imprime_quadrado(*quadrado, DESATIVAR);
				quadrado->centro->Y = (quadrado->centro->Y) + 1 ;
			}
			
			movimenta_quadrado(quadrado, janela, CIMA);
			break;
		/* case (3) */ 
		case (ESQUERDA):

			while((quadrado->centro->X - 2) > janela.ponto1->X)
			{
				imprime_quadrado(*quadrado, ATIVAR);
				sleep(1);
				imprime_quadrado(*quadrado, DESATIVAR);
				quadrado->centro->X = (quadrado->centro->X) - 1 ;
			}
			
			movimenta_quadrado(quadrado, janela, DIREITA);
			
			break;
		/* case (1) */ 
		case (DIREITA):
			while((quadrado->centro->X + 2) < janela.ponto2->X)
			{
				imprime_quadrado(*quadrado, ATIVAR);
				sleep(1);
				imprime_quadrado(*quadrado, DESATIVAR);
				quadrado->centro->X = (quadrado->centro->X) + 1 ;
			}
			
			movimenta_quadrado(quadrado, janela, ESQUERDA);
			break;
	}
}	
	
	
/*		|---------------  Set ambiente -------------------------|
		|	 Configura o console inicial ao mesmo tempo			|	
		|	ele armazena os dados para que a janela retorne		|
		|	a como estava no inicio do programa 	 		 	|
		|	 Essa funcao tem tanto a atividade de configurar   	|
		|	o console inicial como de restaurar as configurações|
		|	que estavam anteriormente							|
		|-------------------------------------------------------|
*/

void set_ambiente(CONSOLE *console)
{
	/* armazena todos os valores atuais do console 
	assim como sua posicao maxima, para que o console de usuario 
	seja configurado no jogo e depois consiga retornar ao finalizar o programa
	*/
		
	console->dimensao_inicial = tamanhoJanelaConsole();	
	console->dimensao_maxima = MaxDimensaoJanela();
	console->posicao_inicial = getPosicaoJanela();
	
	/* em alguns casos os valores iniciais da janela podem vir negativos 
		caso isso ocorra o programa ira determinar um valor valido para os parametros 
		para que quando forem utilizados eles consigam gerar um retorno
	*/
	
	/*
	if(console->dimensao_inicial.X <= 0 || console->dimensao_inicial.Y <= 0)
	{
		console->dimensao_inicial = console->dimensao_maxima; 
	}
		
	if(console->posicao_inicial.X < 0 || console->posicao_inicial.Y < 0 )
	{
		console->posicao_inicial.X = 0; 
		console->posicao_inicial.Y = 0;
	}*/
		
	/* configura a tela do usuario */ 
	setPosicaoJanela(0,0);
	setDimensaoJanela(console->dimensao_maxima.X, console->dimensao_maxima.Y);
	setEstadoBarraTarefas(INVISIVEL);
	setTituloConsole(TITULO);	
	setCursorStatus(DESLIGAR);
		
}


/*	|---------------  depuracao   --------------------------|
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