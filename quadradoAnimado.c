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
	int cor, direcao; 
	JANELA *Janela, refJanela;
	CONSOLE *console , Pointer_console;
	QUADRADO *quadrado, refquad;
	
	console = &Pointer_console;
	Janela = &refJanela;
	quadrado = &refquad;
	
	srand(time(NULL));
	
	cor = rand() % 15 + 1;
	direcao = rand() % 3 ;
	
	set_ambiente(console, ATIVAR);
	cria_ponto(Janela, *console);
	cria_quadrado(quadrado, *Janela);
	gerencia_janela(Janela, cor, *console);
	imprime_info(*quadrado);
	movimenta_quadrado(quadrado, *Janela, direcao);
	
	depuracao(*Janela, *console, DEPURACAO);
	
	textbackground(0);
	getchar();
	clrscr();
	
	gotoxy(1,1);
	set_ambiente(console, DESATIVAR);

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
	
	Janela->linha = 80;
	Janela->coluna = 20;
	
	
	Janela->ponto1.X = (console.dimensao_maxima.X/2)/2;
	Janela->ponto1.Y = (console.dimensao_maxima.Y/2)/2;
	
	Janela->ponto2.X = Janela->ponto1.X + Janela->linha ;
	Janela->ponto2.Y = Janela->ponto1.Y + Janela->coluna ;
	
	Janela->centro.X = Janela->ponto1.X + Janela->linha/2;
	Janela->centro.Y = Janela->ponto1.Y  + Janela->coluna/2;
}

void cria_quadrado(QUADRADO *quadrado , JANELA Janela)
{
	quadrado->centro.X = Janela.centro.X;
	quadrado->centro.Y = Janela.centro.Y;
	
	quadrado->cor = 4;
	
	quadrado->velocidade = 0.2;
	quadrado->direcao = 1;
	
	imprime_quadrado(*quadrado,ATIVAR);
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
	int i; 
	clrscr();
	textbackground(9);
	
	/* para criar a janela sera criada quatro funcoes que tem como controle o tamanho da linha e da coluna
	essas funcoes serao 4 for's para criar as linhas e as colunas
	*/
		
	for(i = 0; i < Janela->linha; ++i)
	{
		/* linha superior */ 
		gotoxy(Janela->ponto1.X + i,Janela->ponto1.Y);
		putchar(32);
		
		/*linha inferior*/
		gotoxy(Janela->ponto1.X+i,Janela->ponto2.Y);
		putchar(32);
	
	}
	
	for(i = 0; i <= Janela->coluna; ++i)
	{
		/* coluna horizontal da esquerda */ 
		gotoxy(Janela->ponto1.X,Janela->ponto1.Y + i);
		putchar(32);
		
		/*coluna horizontal direita */ 
		gotoxy(Janela->ponto2.X,Janela->ponto1.Y+i);
		putchar(32);
	}
	
	
}

void imprime_info(QUADRADO quadrado){
		int TAMANHO;
		
		TAMANHO = 10;
		textbackground(BLACK);
		textcolor(RED);
		
		gotoxy(80,2);
		printf("QUADRADO ANIMADO!!");
		
		gotoxy(TAMANHO,4);
		printf("Direcao atual: ");
		
		switch(quadrado.direcao)
		{
			case (CIMA):
				printf("Cima  ");
				break;
			case (DIREITA):
				printf("Direita  ");
				break;
			case(BAIXO):
				printf("Baixo  ");
				break;
			case(ESQUERDA):
				printf("Esquerda");
				break;
		}
		
		gotoxy(TAMANHO + 40,4);
		printf("Tecla digitada: ");
		
		gotoxy(TAMANHO + 90,4);
		printf("Velocidade atual: %.2f ",quadrado.velocidade);
}

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
				gotoxy((quadrado.centro.X - 1) +j, (quadrado.centro.Y - 1) + i);
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
				gotoxy((quadrado.centro.X - 1) +j, (quadrado.centro.Y - 1) + i);
				putchar(32);
			}
		}
	}
}

/* ----------------implementando o movimenta janela ---------------------*/ 
void movimenta_quadrado(QUADRADO *quadrado, JANELA janela, DIRECAO direcao)
{	
	float controle = (2.0 - quadrado->velocidade)*100;
		
	
	switch (direcao)
	{
		/* case (0) */ 
		case (CIMA):
			quadrado->direcao = direcao;
			imprime_info(*quadrado);
			
			while((quadrado->centro.Y - 2) > janela.ponto1.Y)
			{
				imprime_quadrado(*quadrado, 1);
				Sleep(controle);
				imprime_quadrado(*quadrado, 0);
				quadrado->centro.Y = (quadrado->centro.Y) - 1 ;
			}
			
			movimenta_quadrado(quadrado, janela, BAIXO);
			break;
		/* case (2) */ 
		case (BAIXO):
			quadrado->direcao = direcao;
			imprime_info(*quadrado);
			
			while((quadrado->centro.Y + 2) < janela.ponto2.Y)
			{
				imprime_quadrado(*quadrado, 1);
				Sleep(controle);
				imprime_quadrado(*quadrado, 0);
				quadrado->centro.Y = (quadrado->centro.Y) + 1 ;
			}
			
			movimenta_quadrado(quadrado, janela, CIMA);
			break;
		/* case (3) */ 
		case (ESQUERDA):
			quadrado->direcao = direcao;
			imprime_info(*quadrado);
			
			while((quadrado->centro.X - 2) > janela.ponto1.X)
			{
				imprime_quadrado(*quadrado, 1);
				Sleep(controle);
				imprime_quadrado(*quadrado, 0);
				quadrado->centro.X = (quadrado->centro.X) - 1 ;
			}
			
			movimenta_quadrado(quadrado, janela, DIREITA);
			
			break;
		/* case (1) */ 
		case (DIREITA):
			quadrado->direcao = direcao;
			imprime_info(*quadrado);
			while((quadrado->centro.X + 2) < janela.ponto2.X)
			{
				imprime_quadrado(*quadrado, 1);
				Sleep(controle);
				imprime_quadrado(*quadrado, 0);
				quadrado->centro.X = (quadrado->centro.X) + 1 ;
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
		setCursorStatus(DESLIGAR);
		
	}else{
		setPosicaoJanela(console->posicao_inicial.X,console->posicao_inicial.Y);
		setDimensaoJanela(console->dimensao_inicial.X,console->dimensao_inicial.Y);
		setEstadoBarraTarefas(VISIVEL);
		setCursorStatus(LIGAR);
	}
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
	
	printf("P1 X - %d \n",Janela.ponto1.X);
	printf("P1 Y - %d \n",Janela.ponto1.Y);
	
	printf("P2 X - %d \n",Janela.ponto2.X);
	printf("P2 Y - %d \n",Janela.ponto2.Y);
	
	printf("CENTRO X - %d \n",Janela.centro.X);
	printf("CENTRO Y - %d \n",Janela.centro.Y);
	
	
	printf("linha- %d \n",Janela.linha);
	printf("coluna - %d \n",Janela.coluna);
	
	
	printf("------------------------------------------------------------\n");
	}
}