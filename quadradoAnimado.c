/* implementação da biblioteca quadrado_h.h */ 

#include <stdio.h> /*NULL,printf()*/
#include <stdlib.h> /* srand(), rand() */ 
#include <time.h> /* time() */ 


#include "conio_v3.2.4.h" /* textbackground(),gotoxy(),putchar(),textColor() */ 
#include "console_v1.5.4.h" /* COORD ,getPosicaoJanela(),MaxDimensaoJanela(),getPosicaoJanela(), setPosicaoJanela() 
setDimensaoJanela() ,setTituloConsole() ,setCursorStatus(),Sleep() */ 
#include "quadradoAnimado.h" /* cria_janela() */

#define LINHA 20
#define COLUNA 50
#define VELOCIDADE 1000 /*dada em milisegundos */ 
	
#define COR_INICIO_JANELA 9

/* ------------------- Observações iniciais ----------------
	-> sempre que aparecer a palavra "console" esta sendo referido ao prompt de 
	comando onde o programa esta sendo executado;
	-> sempre que aparecer nos comentarios a palavra "janela" 
	esta sendo referenciado a janela colorida por onde o quadrado de asteriscos esta se movimentando;
	-> sempre que aparecer a palavra quadrado esta sendo referido ao quadrado interno formado 
	por asteriscos que se movimenta dentro da janela;

*/ 

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
	/* declara os tipos de dados que serao utiliados e tambem um ponteiro que ira apontar para 
	o endereco de cada estrutura*/ 
	JANELA *Janela, refJanela;
	CONSOLE *console , Pointer_console;
	QUADRADO *quadrado, refquad;
	
	/* aponta cada ponteiro para o seu respectivo tipo de dado */ 
	console = &Pointer_console;
	Janela = &refJanela;
	quadrado = &refquad;
	
	/* seta a semente do funcao geradora de numeros aleatorios para o relogio do computador
	isso garante que a semente geradora de numero aleatorio sempre mudara a cada execução */ 
	srand(time(NULL));
	
	/* determina  cor inicial da janela */
	Janela->cor = COR_INICIO_JANELA;
	
	/* primeiro chama a funcao que ajusta o console */ 
	set_ambiente(console, ATIVAR);
	
	/* cria os pontos de referencia inicial que sera usado para criar a janela no inicio*/
	cria_ponto(Janela);
	
	/* cria o quadrado interno que ficara se movimentado por dentro da janela */ 
	cria_quadrado(quadrado, *Janela);
	
	/* cria a janela inicia do jogo */ 
	gerencia_janela(Janela);
	
	/* imprime as informações inicias que estao contidas dentro do quadrado */ 
	imprime_info(*quadrado);
	
	/* funcoa que ficara responsavel por fazer a leitura do teclado e ira realizar as chamadas das funcoes devidas para cada tecla pressionada */ 
	gerencia_programa( Janela, quadrado);
	
	/* reseta o console para os valores armazenados na estrutura lidos no inico do programa */
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
	
	/* atribui o tamanho da linha e da coluna para criar o ponto de referencia */ 
	Janela->coluna = COLUNA;
	Janela->linha = LINHA;
	
	
	/* cria o ponto inicial do programa*/
	Janela->ponto1.X = 1;
	Janela->ponto1.Y = 1;
	
	/* cria o outro ponto de referencia que esta localizado na transversal do ponto 1 */ 
	Janela->ponto2.X = Janela->ponto1.X + Janela->coluna ;
	Janela->ponto2.Y = Janela->ponto1.Y + Janela->linha ;
	
	
	/* cria um ponto que esta localizado no centro da janela */ 
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
	/* determina a posicao inicial do quadrado */
	quadrado->centro.X = Janela.centro.X;
	quadrado->centro.Y = Janela.centro.Y;
	
	/* atribui uma cor inicial ao quadrado */
	quadrado->cor = 1;
	
	/* seta alguns dados iniciais do quadrado */ 
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
	/* determina a cor do quadrado externo, os valor correto do quadrado esta armazenado dentro de uma variavel no proprio ponteiro*/
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
		gotoxy(Janela->ponto1.X+i,Janela->ponto2.Y-1);
		putchar(32);
	
	}
	
	for(i = 0; i < Janela->linha; ++i)
	{
		/* coluna horizontal da esquerda */ 
		gotoxy(Janela->ponto1.X,Janela->ponto1.Y + i);
		putchar(32);
		
		/*coluna horizontal direita */ 
		gotoxy(Janela->ponto2.X,Janela->ponto1.Y+i);
		putchar(32);
	}
	
	textbackground(0);
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
	int i;
	
	/* variavel que armazenara um evento(interação do usuário com o console) */
	EVENTO evento; 
	BOOLEANO controle;
	controle = VERDADEIRO;
	
	i=10;
	
	do
	{
		timeBeginPeriod(1);
		
		/* essa funcao sleep seguido do do if serve para melhorar a precisao do programa
		pois assim ao inves do meu programa precisar armazenar tempo de sleep para 1000 milisegundos por exemplo
		ele reserva processamento para 100 milissegundo e quando ele fizer esse processo 10 vezes ele ira implemetar o movimento
		desse modo ele faz poucas chamadas e a cada chamada o windows armazena pouco tempo para a execucao 
		se colcoar o sleep(1) por exemplo o programa vai reservar pouco memoria para o tempo, mas fazer 1000 chamadas perde desempenho
		como foi feito em teste nesse mesmo programa*/

		Sleep(100);
		
		if(i == quadrado->velocidade/100){
			movimenta_quadrado(quadrado, *janela);
			i = 1;
		}
		
		/* caso tenha uma interação do usuário com o console(teclado ou mouse) ficará armazenado no buffer e ao chamar essa funcão 
		sera lido o buffer de eventos e entrara na funcao */ 
		if(hit(KEYBOARD_HIT))
		{
			/* pega os dados armazenados no buffer de eventos */
			evento = Evento();
			
			/* verifica se é um evento de teclado */ 
			if(evento.tipo_evento & KEY_EVENT)
			{
				/* verifica se a telca foi liberada pelo usuario */ 
				if(evento.teclado.status_tecla == LIBERADA)
				{
					
					/* caso esteja com a tecla livre e foi um evento de teclado o switch a seguir ira filtrar 
					qual tecla o usuario digitou */
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
								
							/* altera a direção do quadrado apra direita se a tecla correspondente for pressionada */ 
							case SETA_PARA_DIREITA:
							
								quadrado->texto = "Seta Direita";
								quadrado->direcao = DIREITA;
								break;
							
							/* altera a direção do quadrado para esquerda se a tecla correspondente for pressionada */ 
							case SETA_PARA_ESQUERDA:
							
								quadrado->texto = "Seta Esquerda";
								quadrado->direcao = ESQUERDA;
								break;
							
							/* altera a direção do quadrado para baixo se a tecla correspondente for pressionada */ 							
							case SETA_PARA_BAIXO:
								quadrado->direcao = BAIXO;
								quadrado->texto = "Seta Baixo";
								break;
							
							/* altera a direção do quadrado para cima se a tecla correspondente for pressionada */ 							
							case SETA_PARA_CIMA:
							
								quadrado->texto = "Seta Cima";
								quadrado->direcao = CIMA;
								break;
							
							/*-- aumenta area da janela para esquerda - */
							case F3:
							
								/* verifica se o tamanho da janela esta de acordo com o do console */ 
								if(janela->ponto1.X > 1)
								{
									janela->ponto1.X -= 1;
									janela->coluna += 1;
								}
								
								quadrado->texto = "F3";
								gerencia_janela(janela);
								break;
							
							/*-- diminui a borda da janela da esquerda --*/ 							
							case F4:
								
								/* verifica se o tamanho minimo é suficiente para caber o quadrado */
								if(janela->ponto2.X-4 > janela->ponto1.X)
								{
									janela->ponto2.X -= 1;
									janela->coluna -= 1;
									
									/* verifica se o ao se movimetar não estara ooucupando o espaco onde o quadrado esta colocado */
									if(janela->ponto2.X == quadrado->centro.X + 1)
										quadrado->centro.X--;
								}
								quadrado->texto = "Tecla F4";
								gerencia_janela(janela);
								break;
							
							/*-- aumenta a area da janela para direita --*/
							case F5:
								if(janela->coluna < 100 && janela->ponto2.X < 1 + COLUNA)
								{
									janela->coluna += 1;
									janela->ponto2.X += 1; 
								}
								quadrado->texto = "Tecla F5";
								gerencia_janela(janela);
								break;
							
							/*-- diminui a area da do quadrado para direita --*/
							case F6: 
								
								if(janela->ponto1.X < janela->ponto2.X - 4)
								{
									janela->ponto1.X += 1;
									janela->coluna -= 1;
									
									/* verifica se o ao se movimetar não estara ooucupando o espaco onde o quadrado esta colocado */
									if(janela->ponto1.X == quadrado->centro.X-1)
										quadrado->centro.X++;
								}
								
								
								quadrado->texto = "Tecla F6";
								gerencia_janela(janela);
								break;
								
							/*-- aumenta a areda do quadrado para cima --*/
							case F7:
							
								/*verifica se o quadrado esta no limite superior do console */
								if(janela->ponto1.Y > 1)
								{
									janela->ponto1.Y -= 1;
									janela->linha += 1;
								}
								quadrado->texto = "Tecla F7";
								gerencia_janela(janela);
								break;
							
							/*-- diminui a area superior --*/ 
							case F8:
							
								/* verifica se o tamanho minimo é suficiente para caber o quadrado */
								if(janela->ponto1.Y < janela->ponto2.Y - 5)
								{
									janela->ponto1.Y += 1;
									janela->linha -= 1;
									
									/* verifica se o ao se movimetar não estara ooucupando o espaco onde o quadrado esta colocado */
									if(janela->ponto1.Y == quadrado->centro.Y - 1 )
										quadrado->centro.Y++;
								}
								
								quadrado->texto = "Tecla F8";
								gerencia_janela(janela);
								break;
								
							/*-- aumenta a area para baixo --*/
							case F9:
							
							/* verifica se o quadrado nao esta ultrapassando o tamanho maximo definido no limite */
								if(janela->ponto2.Y < LINHA)
								{
									janela->ponto2.Y += 1;
									janela->linha += 1;
								}
								quadrado->texto = "Tecla F9";
								gerencia_janela(janela);
								break;
								
							/*--diminui a area para baixo --*/
							case F10:
							
								/* verifica se o tamanho minimo é suficiente para caber o quadrado */
								if(janela->ponto2.Y > janela->ponto1.Y + 5)
								{
									janela->linha -= 1;
									janela->ponto2.Y -=1;
									
									/* verifica se o ao se movimetar não estara ooucupando o espaco onde o quadrado esta colocado */
									if(janela->ponto2.Y  == quadrado->centro.Y +2 )
										quadrado->centro.Y--;
								}
								quadrado->texto = "Tecla F10";
								gerencia_janela(janela);
								break;
								
							/*--alterna a cor do quadrado --*/
							case ESPACO:
							
								/*altera a cor do quadrado para uma cor aleatoria diferente de preto */ 
								janela->cor = rand() % 15+1;
								quadrado->texto = "Tecla F10";
								break;
								
							/*-- alterna a cor do quadrado --*/
							case TAB:
							
							/* aletera a cor da janela para uma cor aleatoria diferente de preto */
								quadrado->cor = rand() %15+1;
								quadrado->texto = "Tecla TAB";
								gerencia_janela(janela);
								
								break;
								
							/*-- finaliza programa --*/
							case ESC:
							
								/* atribui o valor de saida para a minha variavel de controle */
								controle = FALSO;
								quadrado->texto = "Tecla ESC";
								
								break;
								
							default: 
								/* caso a tecla digitada não seja reconhecida ira exeibir a mensagem de "NULL" para o usuario */
								quadrado->texto = NULL;
								break;
					}
					
					imprime_info(*quadrado);
				
				}
			}
		
		}
		
		++i;
		
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
		
		/* muda a cor de fundo para preto e a cor da letra para vermelha, para uma melhro diferenciação do texto no console*/
		textbackground(BLACK);
		textcolor(RED);
		
		/* posiciona o cursor na referencia dentro de quadrado e imprime a mensagem de direção */
		gotoxy(quadrado.textoRef.X,quadrado.textoRef.Y+1);
		printf("Direcao atual: ");
		
		/*imprime qual a direção */
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
		
		/* posiciona o cursor na posicao de referencia dentro do quadrado, porem na linha de baixo (incremento de 1 em Y)*/
		gotoxy(quadrado.textoRef.X,quadrado.textoRef.Y+2);
		printf("Tecla digitada: %s ", quadrado.texto);
		
		/* posiciona o cursor na posicao de referencia dentro do quadrado, porem na DUAS linhas a baixo (incremento de 2 em Y)*/
		gotoxy(quadrado.textoRef.X,quadrado.textoRef.Y+3);
		printf("Velocidade atual: %d milisegundos",quadrado.velocidade);
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
	
	/* cao a funcao seja de imprimir ira entrar dentro desse primeiro IF */
	if(funcao)
	{
		textcolor(quadrado.cor);
		/* imprime como se fosse uma matriz*/
		for(i = 0; i < 3 ;++i)
		{
			for(j = 0; j < 3; ++j)
			{
				/* condicional para não imrpimir o nada no centro do quadrado */ 
				if(!(j== 1 && i ==1))
				{
				gotoxy((quadrado.centro.X - 1) +j, (quadrado.centro.Y - 1) + i);
				putchar(42);
				}
			}
		}
	}
	else /* caso o parametro seja de apagar a funcao ira entrar dentro desse else*/
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
	/* realiza a movimentação do quadrado */
	imprime_quadrado(*quadrado, 0);

		
	/* posciona o quadrado na proxima direçao para que o quadrado ira andar na proxima chamda */
	switch (quadrado->direcao)
	{
		
		/* case (0) */ 
		case (CIMA):
			imprime_info(*quadrado);
	
			if(quadrado->centro.Y - 2 == janela.ponto1.Y)
				quadrado->direcao = BAIXO;
			else
				quadrado->centro.Y = (quadrado->centro.Y) - 1 ;
			
			break;
		/* case (2) */ 
		case (BAIXO):
			imprime_info(*quadrado);
			
			if(quadrado->centro.Y + 3 == janela.ponto2.Y)
				quadrado->direcao = CIMA;
			else
				quadrado->centro.Y =(quadrado->centro.Y)+1;
			
			break;
		/* case (3) */ 
		case (ESQUERDA):
			imprime_info(*quadrado);
				
			if(quadrado->centro.X - 2 == janela.ponto1.X)
				quadrado->direcao = DIREITA;
			else
				quadrado->centro.X = (quadrado->centro.X) - 1 ;
			
			break;
		/* case (1) */ 
		case (DIREITA):
			imprime_info(*quadrado);
				
			if(quadrado->centro.X + 2 == janela.ponto2.X)
				quadrado->direcao = ESQUERDA;
			else
				quadrado->centro.X = (quadrado->centro.X) + 1 ;
			
			break;
	}
	
	imprime_quadrado(*quadrado, 1);
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

void set_ambiente(CONSOLE *console, ATIVIDADE status)
{
	if(status)
	{
		
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
		
	}
	else
	{
		
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