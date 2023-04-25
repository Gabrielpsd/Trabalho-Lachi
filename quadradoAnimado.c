/* implementação da biblioteca quadrado_h.h */ 

#include <stdio.h> /*NULL,printf()*/
#include <stdlib.h> /* srand(), rand() */ 
#include <time.h> /* time() */ 


#include "conio_v3.2.4.h" /* textbackground(),gotoxy(),putchar(),textColor() */ 
#include "console_v1.5.4.h" /* COORD ,getPosicaoJanela(),MaxDimensaoJanela(),getPosicaoJanela(), setPosicaoJanela() 
setDimensaoJanela() ,setTituloConsole() ,setCursorStatus(),Sleep() */ 
#include "quadradoAnimado.h" /* cria_janela() */

/* essa referencia é utilizada para imprimir as infromacoes na tela
ela somasse a posicao do ponto apenas para poder imprimir em determinado local da tela(no canto inferior esquerdo nesse caso)
*/

#define LINHA 40
#define COLUNA 100
#define VELOCIDADE 100 /*dada em milisegundos */ 
#define CARACTER_HORIZONTAL 32
#define CARACTER_VERTICAL 32	
#define COR_INICIO_JANELA 9


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
	JANELA *Janela, refJanela;
	CONSOLE *console , Pointer_console;
	QUADRADO *quadrado, refquad;
	
	console = &Pointer_console;
	Janela = &refJanela;
	quadrado = &refquad;
	
	srand(time(NULL));
	
	Janela->cor = COR_INICIO_JANELA;
	
	set_ambiente(console, ATIVAR);
	cria_ponto(Janela);
	cria_quadrado(quadrado, *Janela);
	gerencia_janela(Janela);
	imprime_info(*quadrado);
	
	gerencia_programa( Janela, quadrado);
	
	set_ambiente(console,DESATIVAR);
	
}

/*	|---------------  Cria ponto ---------------------------|
	|	 Para que possa ser criado as zonas de impacto		|
	|	do quadrado interno, ele seguira refernecia por 3 	|
	|	pontos princiapais(centro e diagonais) essa funcao 	|
	|	tem o objetivo de criar esses valores inicias para 	|
	|	o programa trabalhar								|
	|-------------------------------------------------------|
*/

void cria_ponto(JANELA *Janela)
{	
	
	Janela->coluna = COLUNA;
	Janela->linha = LINHA;
	
	
	Janela->ponto1.X = 1;
	Janela->ponto1.Y = 1;
	
	Janela->ponto2.X = Janela->ponto1.X + Janela->coluna ;
	Janela->ponto2.Y = Janela->ponto1.Y + Janela->linha ;
	
	Janela->centro.X = Janela->ponto2.X/2;
	Janela->centro.Y = Janela->ponto2.Y/2;
}

/*	|---------------  Cria quadrado  -----------------------|
	|	 	Funcao ira definir os valores padrao do quadrado|
	|	interno, essa funcao so sera chamada na 			|
	|	inicializaçao do programa, a partir dai as 			|
	|	alterações na estrutura sera feita por outras 		|
	|	funcoes;												|
	|-------------------------------------------------------|
*/

void cria_quadrado(QUADRADO *quadrado , JANELA Janela)
{
	quadrado->centro.X = Janela.centro.X;
	quadrado->centro.Y = Janela.centro.Y;
	
	quadrado->cor = 1;
	
	quadrado->velocidade = VELOCIDADE;
	quadrado->direcao = rand()%3;
	quadrado->texto = NULL;
	imprime_quadrado(*quadrado,ATIVAR);
	quadrado->textoRef.X = Janela.ponto1.X;
	quadrado->textoRef.Y = Janela.ponto2.Y;
}

/*	|---------------  Gerencia Janela ----------------------|
	|	 Cria a janela principal.							|	
	|	A funcao utiliza os 3 pontos da estrutura PONTO 	|
	|	como referencia, trocando a cor do fundo 		 	|
	|	caracter por caracter conectando os  pontos das  	|
	|	diagonais											|
	|-------------------------------------------------------|
*/

void gerencia_janela(JANELA *Janela)
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
		putchar(CARACTER_HORIZONTAL);
		
		/*linha inferior*/
		gotoxy(Janela->ponto1.X+i,Janela->ponto2.Y);
		putchar(CARACTER_HORIZONTAL);
	
	}
	
	for(i = 0; i <= Janela->linha; ++i)
	{
		/* coluna horizontal da esquerda */ 
		gotoxy(Janela->ponto1.X,Janela->ponto1.Y + i);
		putchar(CARACTER_VERTICAL);
		
		/*coluna horizontal direita */ 
		gotoxy(Janela->ponto2.X,Janela->ponto1.Y+i);
		putchar(CARACTER_VERTICAL);
	}
	
	
}

/*	|---------------  Gerencia Programa --------------------|
	|		Essa funcao é a funcao que realiza a leitura das| 
	|	teclas digitadas pelo usuario, como a cada interação|
	|	o programa ira realizar a verficação e ,caso 		|
	|	necessario, realizar a chama de outras funcoes, ele |	
	|	recebe como parametro todas as estruturas			|
	|-------------------------------------------------------|
*/

void gerencia_programa(JANELA *janela, QUADRADO *quadrado)
{	
	EVENTO evento; 
	BOOLEANO controle;
	controle = VERDADEIRO;
	
	do
	{
		timeBeginPeriod(1);
		movimenta_quadrado(quadrado, *janela);
		
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
								
								if(quadrado->velocidade > 100)
								{
								quadrado->texto = "F2";
								quadrado->velocidade -= 100;
								}
								
								break;
							
						/*-- diminui a velocidade interna do quadrado -- */ 
							case F1: 
								
								if(quadrado->velocidade < 2000)
								{
									quadrado->texto = "Tecla F1";
									quadrado->velocidade += 100;
								}
								break;
								
							
							case SETA_PARA_DIREITA:
							
								quadrado->texto = "Seta Direita";
								quadrado->direcao = DIREITA;
								break;
								
							case SETA_PARA_ESQUERDA:
							
								quadrado->texto = "Seta Esquerda";
								quadrado->direcao = ESQUERDA;
								break;
								
							case SETA_PARA_BAIXO:
								quadrado->direcao = BAIXO;
								quadrado->texto = "Seta Baixo";
								break;
								
							case SETA_PARA_CIMA:
							
								quadrado->texto = "Seta Cima";
								quadrado->direcao = CIMA;
								break;
							
							/*-- aumenta area do quadrado externo para esquerda -- */
							case F3:
							
								if(janela->ponto1.X > 1)
								{
									janela->ponto1.X -= 1;
									janela->coluna += 1;
								}
								
								quadrado->texto = "F3";
								break;
							
							/*-- diminui a borda do quadrado da esquerda --*/ 							
							case F4:
								
								if(janela->ponto2.X-3 > janela->ponto1.X)
								{
									janela->ponto2.X -= 1;
									janela->coluna -= 1;
									
									if(janela->ponto2.X == quadrado->centro.X + 2)
										quadrado->centro.X--;
								}
								quadrado->texto = "Tecla F4";
								break;
							
							/*-- aumenta a area do quadrado para direita --*/
							case F5:
								if(janela->coluna < 100 && janela->ponto2.X < 1 + COLUNA)
								{
									janela->coluna += 1;
									janela->ponto2.X += 1; 
								}
								quadrado->texto = "Tecla F5";
								break;
							
							/*-- diminui a area da do quadrado para direita --*/
							case F6: 
								
								if(janela->ponto1.X < janela->ponto2.X - 3)
								{
									janela->ponto1.X += 1;
									janela->coluna -= 1;
									
									if(janela->ponto1.X == quadrado->centro.X-2)
										quadrado->centro.X++;
								}
								quadrado->texto = "Tecla F6";
								break;
								
							/*-- aumenta a areda do quadrado para cima --*/
							case F7:
								if(janela->ponto1.Y > 1)
								{
									janela->ponto1.Y -= 1;
									janela->linha += 1;
								}
								quadrado->texto = "Tecla F7";
								break;
							
							/*-- diminui a area superior --*/ 
							case F8:
								if(janela->ponto1.Y < janela->ponto2.Y -3)
								{
									janela->ponto1.Y += 1;
									janela->linha -= 1;
									
									if(janela->ponto1.Y == quadrado->centro.Y- 2 )
										quadrado->centro.Y++;
								}
								
								quadrado->texto = "Tecla F8";
								break;
								
							/*-- aumenta a area para baixo --*/
							case F9:
								if(janela->ponto2.Y < LINHA)
								{
									janela->ponto2.Y += 1;
									janela->linha += 1;
								}
								quadrado->texto = "Tecla F9";
								break;
								
							/*--diminui a area para baixo --*/
							case F10:
								if(janela->ponto2.Y > janela->ponto1.Y + 3)
								{
									janela->linha -= 1;
									janela->ponto2.Y -=1;
									
									if(janela->ponto2.Y  == quadrado->centro.Y + 2)
										quadrado->centro.Y--;
								}
								quadrado->texto = "Tecla F10";
								break;
								
							/*--alterna a cor do quadrado --*/
							case ESPACO:
								janela->cor = rand() % 15+1;
								quadrado->texto = "Tecla F10";
								break;
								
							/*-- alterna a cor do quadrado --*/
							case TAB:
								quadrado->cor = rand() %15+1;
								quadrado->texto = "Tecla TAB";
								break;
								
							/*-- finaliza programa --*/
							case ESC:
								controle = FALSO;
								quadrado->texto = "Tecla ESC";
								
								break;
					}
					
					gerencia_janela(janela);
					imprime_info(*quadrado);
				
				}
			}
		
		}
		
		timeEndPeriod(1);
		
	}while(controle == VERDADEIRO);

}

/*	|---------------  imprime info -------------------------|
	|	 Funcao ira realizar a impressao das informacoes 	|
	|	solicitadas no exercicio, essas informações estao	|
	|	contidas dentro da estrutura QUADRADO, a funcao 	|
	|	apenas lea informação que esta la dentro e 			|
	|	imprime o valor, tambem dentro do quadrado			|
	|	ha um coord que serve como referencia para 			|
	|	posicionar os textos na tela do usuario, essas 		|
	|	posicoes sao criadas no inicio do programa e nao 	|
	|	sofrem alteracao com o decorrer do mesmo;		|
	|-------------------------------------------------------|
*/
void imprime_info(QUADRADO quadrado)
{
		
		textbackground(BLACK);
		textcolor(RED);
		
		gotoxy(quadrado.textoRef.X,quadrado.textoRef.Y+1);
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
		
		gotoxy(quadrado.textoRef.X,quadrado.textoRef.Y+2);
		printf("Tecla digitada: %s ", quadrado.texto);
		
		gotoxy(quadrado.textoRef.X,quadrado.textoRef.Y+3);
		printf("Velocidade atual: %.2f segundos",quadrado.velocidade);
}

/*	|----------------  Imprime Quadrado --------------------|
	|	 	A funcao recebe o quadrado como referencia, 	|
	|	a partir dai ele pega o ponto centro e atraves desse| 
	|	ponto ele realiza as operacoes, a cor dos caracteres|
	|	e a posicao de referencia estao contidas dentro da 	|
	|	estrutura;											|
	|		A funcao recebe o parametro enum que serve para |
	|	imprimir ou apagar o quadrado da tela, caso o 		|
	|	parametro seja para ativar ele imprime os dados como| 
	|	sendo uma matriz; e caso o parametro seja DESTIVAR	|
	|	ela realiza a exclusao sobreponto as posicoes do 	|
	|	quadrado porem com um novo caracter 'espaco' com o 	|
	|	fundo de cor preto;									|
	|-------------------------------------------------------|
*/

void imprime_quadrado(QUADRADO quadrado, ATIVIDADE funcao)
{
	int i, j; 
	
	if(funcao)
	{
		textcolor(quadrado.cor);
		/* imprime como se fosse uma matriz*/
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
		/* imprime como se fosse uma matriz*/
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

/*	|---------------  movimenta quadrado -------------------|
	|	 A funcao movimenta quadrado, realiza o deslocamento|
	|	do ponto central do quadrado para uma posicao em 	|
	|	direcao a que esta contida no campo direcao 		|
	|	armazenado dentro da propria estrura QAUDRADO 	 	|
	|-------------------------------------------------------|
*/

void movimenta_quadrado(QUADRADO *quadrado, JANELA janela)
{
	
	imprime_quadrado(*quadrado, 1);
	Sleep(quadrado->velocidade);
	imprime_quadrado(*quadrado, 0);
		
	switch (quadrado->direcao)
	{
		
		/* case (0) */ 
		case (CIMA):

			quadrado->centro.Y = (quadrado->centro.Y) - 1 ;
	
			if(quadrado->centro.Y - 2 == janela.ponto1.Y)
				quadrado->direcao = BAIXO;
			
			break;
		/* case (2) */ 
		case (BAIXO):

				quadrado->centro.Y =(quadrado->centro.Y)+1;
			
			if(quadrado->centro.Y + 2 == janela.ponto2.Y)
				quadrado->direcao = CIMA;
			
			break;
		/* case (3) */ 
		case (ESQUERDA):

			quadrado->centro.X = (quadrado->centro.X) - 1 ;
				
			if(quadrado->centro.X - 2 == janela.ponto1.X)
				quadrado->direcao = DIREITA;
			
			break;
		/* case (1) */ 
		case (DIREITA):
		
				quadrado->centro.X = (quadrado->centro.X) + 1 ;
				
			if(quadrado->centro.X + 2 == janela.ponto2.X)
				quadrado->direcao = ESQUERDA;
			
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
		
		gotoxy(console->dimensao_maxima.X/4,console->dimensao_maxima.Y/4);
		textcolor(WHITE);
		printf("FIM DA EXECUCAO DO PROGRAMA");
		gotoxy(console->dimensao_maxima.X,console->dimensao_maxima.Y);
		setPosicaoJanela(console->posicao_inicial.X,console->posicao_inicial.Y);
		setDimensaoJanela(console->dimensao_inicial.X,console->dimensao_inicial.Y);
		setEstadoBarraTarefas(VISIVEL);
		setCursorStatus(LIGAR);
	}
}