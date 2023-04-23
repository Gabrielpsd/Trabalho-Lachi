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
	JANELA *Janela, refJanela;
	CONSOLE *console , Pointer_console;
	QUADRADO *quadrado, refquad;
	
	console = &Pointer_console;
	Janela = &refJanela;
	quadrado = &refquad;
	
	srand(time(NULL));
	
	Janela->cor = rand() % 15 + 1;
	
	set_ambiente(console, ATIVAR);
	cria_ponto(Janela, *console);
	cria_quadrado(quadrado, *Janela);
	gerencia_janela(Janela, *console);
	imprime_info(*quadrado);
	movimenta_quadrado(quadrado, *Janela);
	depuracao(*Janela, *console, DEPURACAO);
	
	gerencia_programa( Janela,  console,  quadrado);
	
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
	
	Janela->coluna = 80;
	Janela->linha = 20;
	
	
	Janela->ponto1.X = (console.dimensao_maxima.X/2)/2;
	Janela->ponto1.Y = (console.dimensao_maxima.Y/2)/2;
	
	Janela->ponto2.X = Janela->ponto1.X + Janela->coluna ;
	Janela->ponto2.Y = Janela->ponto1.Y + Janela->linha ;
	
	Janela->centro.X = Janela->ponto1.X + Janela->coluna/2;
	Janela->centro.Y = Janela->ponto1.Y  + Janela->linha/2;
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

void gerencia_janela(JANELA *Janela, CONSOLE console)
{
	int i; 	
	clrscr();
	textbackground(Janela->cor);
	/* para criar a janela sera criada quatro funcoes que tem como controle o tamanho da linha e da coluna
	essas funcoes serao 4 for's para criar as linhas e as colunas
	*/
		
	for(i = 0; i < Janela->coluna; ++i)
	{
		/* linha superior */ 
		gotoxy(Janela->ponto1.X + i,Janela->ponto1.Y);
		putchar(32);
		
		/*linha inferior*/
		gotoxy(Janela->ponto1.X+i,Janela->ponto2.Y);
		putchar(32);
	
	}
	
	for(i = 0; i <= Janela->linha; ++i)
	{
		/* coluna horizontal da esquerda */ 
		gotoxy(Janela->ponto1.X,Janela->ponto1.Y + i);
		putchar(32);
		
		/*coluna horizontal direita */ 
		gotoxy(Janela->ponto2.X,Janela->ponto1.Y+i);
		putchar(32);
	}
	
	
}

void gerencia_programa(JANELA *janela, CONSOLE *console, QUADRADO *quadrado)
{	
	EVENTO evento; 
	
	do
	{
		if(hit(KEYBOARD_HIT))
		{
			evento = Evento();
			
			if(evento.tipo_evento & KEY_EVENT)
			{
				if(evento.teclado.status_tecla == LIBERADA)
				{
					switch(evento.teclado.codigo_tecla)
					{
						/*-- aumenta a velocidade do quadrado interno -- */
							case F2:
								//quadrado->velocidade += 100;
								quadrado->tecla_pressionada_atual = F2;
								break;
							
						/*-- diminui a velocidade interna do quadrado -- */ 
							case F1: 
								/*
								if(quadrado->velocidade > 2000)
									quadrado->velocidade -= 100;
								*/
								quadrado->tecla_pressionada_atual = F1;	
								quadrado->texto = "Tecla F1";
								break;
								
							
							case SETA_PARA_DIREITA:
								//quadrado->direcao = DIREITA;
								quadrado->tecla_pressionada_atual = SETA_PARA_DIREITA;
								break;
								
							case SETA_PARA_ESQUERDA:
								//quadrado->direcao = ESQUERDA;
								quadrado->tecla_pressionada_atual = SETA_PARA_ESQUERDA;
								break;
								
							case SETA_PARA_BAIXO:
								quadrado->direcao = BAIXO;
								quadrado->tecla_pressionada_atual = SETA_PARA_BAIXO;
								break;
								
							case SETA_PARA_CIMA:
								//quadrado->direcao = CIMA;
								quadrado->tecla_pressionada_atual = SETA_PARA_CIMA;
								break;
							
							/*-- aumenta area do quadrado externo para esquerda -- */
							case F3:
							/*
								if(janela->ponto1.X < 1)
								{
									janela->ponto1.X -= 1;
									janela->coluna += ;
								}
								*/
								quadrado->tecla_pressionada_atual = F3;
								break;
							
							/*-- diminui a borda do quadrado para esquerda --*/ 							
							case F4:
							/*
								if(janela->ponto1.X < (janela->ponto2.X -3))
								{
									janela->ponto1.X += 1;
									janela->coluna -= 1;
								}
							*/
								quadrado->tecla_pressionada_atual = F4;
								break;
							
							/*-- aumenta a area do quadrado para direita --*/
							case F5:
								quadrado->tecla_pressionada_atual = F5;
								break;
							
							/*-- diminui a areda do quadrado para direita --*/
							case F6: 
								quadrado->tecla_pressionada_atual = F6;
								break;
								
							/*-- aumenta a areda do quadrado para cima --*/
							case F7:
								quadrado->tecla_pressionada_atual = F7;
								break;
							
							/*-- diminui a area superior --*/ 
							case F8:
								quadrado->tecla_pressionada_atual = F8;
								break;
								
							/*-- auemnta a area para baixo --*/
							case F9:
								quadrado->tecla_pressionada_atual = F9;
								break;
								
							/*--diminui a area para baixo --*/
							case F10:
								quadrado->tecla_pressionada_atual = F10;
								break;
								
							/*--alterna a cor do quadrado --*/
							case ESPACO:
								quadrado->tecla_pressionada_atual = ESPACO;
								break;
								
							/*-- alterna a cor do quadrado --*/
							case TAB:
								quadrado->tecla_pressionada_atual = TAB;
								break;
								
							/*-- finaliza programa --*/
							case ESC:
								quadrado->tecla_pressionada_atual = ESC;
								break;
					}
					
					gerencia_janela(janela, *console);
					imprime_info(*quadrado);
					movimenta_quadrado(quadrado, *janela);
				
				}
			}
		}
	}while(1);
}

void imprime_info(QUADRADO quadrado)
{
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
		printf("Tecla digitada: %s ", quadrado.texto);
		
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
void movimenta_quadrado(QUADRADO *quadrado, JANELA janela)
{	
	float controle = (2.0 - quadrado->velocidade)*100;
		
	
	switch (quadrado->direcao)
	{
		/* case (0) */ 
		case (CIMA):
			imprime_info(*quadrado);
			
			while((quadrado->centro.Y - 2) > janela.ponto1.Y)
			{
				imprime_quadrado(*quadrado, 1);
				Sleep(controle);
				imprime_quadrado(*quadrado, 0);
				quadrado->centro.Y = (quadrado->centro.Y) - 1 ;
			}
			
			quadrado->direcao = BAIXO;
			movimenta_quadrado(quadrado, janela);
			break;
		/* case (2) */ 
		case (BAIXO):
			imprime_info(*quadrado);
			
			while((quadrado->centro.Y + 2) < janela.ponto2.Y)
			{
				imprime_quadrado(*quadrado, 1);
				Sleep(controle);
				imprime_quadrado(*quadrado, 0);
				quadrado->centro.Y = (quadrado->centro.Y) + 1 ;
			}
			
			quadrado->direcao = CIMA;
			movimenta_quadrado(quadrado, janela);
			break;
		/* case (3) */ 
		case (ESQUERDA):
			imprime_info(*quadrado);
			
			while((quadrado->centro.X - 2) > janela.ponto1.X)
			{
				imprime_quadrado(*quadrado, 1);
				Sleep(controle);
				imprime_quadrado(*quadrado, 0);
				quadrado->centro.X = (quadrado->centro.X) - 1 ;
			}
			quadrado->direcao = DIREITA;
			movimenta_quadrado(quadrado, janela);
			
			break;
		/* case (1) */ 
		case (DIREITA):
			imprime_info(*quadrado);
			while((quadrado->centro.X + 2) < janela.ponto2.X)
			{
				imprime_quadrado(*quadrado, 1);
				Sleep(controle);
				imprime_quadrado(*quadrado, 0);
				quadrado->centro.X = (quadrado->centro.X) + 1 ;
			}
			
			quadrado->direcao = ESQUERDA;
			movimenta_quadrado(quadrado, janela);
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