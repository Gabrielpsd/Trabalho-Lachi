#ifndef quadradoAnimado
#define quadradoAnimado

#include <Windows.h> /* COORD */ 

#define TITULO "Quadrado Animado"  

/* #-#-#-#-#-#-#-#-#-# Declaracoes de variaveis e constantes #-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#*/
 

 /*	|------------ ATIVIDADE-----------------------------|
	|		Algumas funcoes tem como parametro ativar 	|
	|	ou desativar, que cotrolam seu comportamento	|
	|	para garantir a integridade das chamadas e a 	|
	|	correta passagem de parametro, foi criada um 	|
	|	enum que representa esses valores				|
	|---------------------------------------------------|
*/

typedef enum
{
	DESATIVAR,
	ATIVAR
}ATIVIDADE;

/*	|------------------- Booleano ------------------|
	|		Tipo de dado que armazena um valor 		|
	|	logico										|
	|-----------------------------------------------|
*/

typedef enum
{	FALSO,
	VERDADEIRO
}BOOLEANO;

/*	|---------------- Direcao  -------------------------|
	|		Nessa estrutura sera numerada as 			|
	|	direções que o quadrado pode seguir				|
	|---------------------------------------------------|
*/

typedef enum
{	CIMA,
	DIREITA,
	BAIXO,
	ESQUERDA
}DIRECAO;

/*	|---------------- console  -------------------------|
	|		Nessa estrutura sera armazenada as 			|
	|	referencias do console, essas informacoes sao 	|
	|	para poder resetar as configurações ao final da |
	|	execução do programa 							|
	|													|
	|---------------------------------------------------|
*/

typedef struct _tela
{
	COORD dimensao_inicial;
	COORD posicao_inicial;
	COORD dimensao_maxima;
	
}CONSOLE;

/*	|---------------- Janela  --------------------------|
	|		Nessa estrutura sera armazenada as 			|
	|	referencias da janela externa					|
	|													|
	|---------------------------------------------------|
*/
	
typedef struct _Janela
{
	COORD ponto1;
	COORD ponto2;
	COORD centro;

	int linha, coluna,cor;
	
}JANELA;

/*	|-------------------  quadrado interno -------------|
	|	Nessa estrutura sera armazenada o quadrado		|
	|	que ficara se movimentando no centro 			|
	|	da janela 										|
	|													|
	|---------------------------------------------------|
*/

typedef struct _quadrado{
	int cor;
	DIRECAO direcao;
	int velocidade;
	COORD centro,textoRef; 
	char *texto;
}QUADRADO;

/* #-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-# FIM DAS DECLARAÇÕES DAS VARIAVEIS E CONSTANTES #-#-#-#-#-#-#-#-#-#-#*/ 

/* ################################## DECLARAÇÕES DE FUNCOES  ###########################################*/ 
	
/*	|---------------  inicia jogo  -------------------------|
	|	unica funcao fora da ordem alfabetica  				|
	|	essa funcao ira realizar a chamada das outras  		|
	|	funcoes do programa;								|
	|	RECEBE: NENHUM PARAMETRO 							|
	|	RETORNA: VOID										|	
	|-------------------------------------------------------|
*/
	
void inicia_jogo();

/*	|---------------  Cria quadrado ------------------------|
	|	 O qudrado central tera uma configuração  			|
	|	padrão, essa funcção serve para colocar 	  		|
	|	a configuração padrão								|
	|	RECEBE:												|
	|	->QUADRADO *: ponteiro que armazena a janela 		|
	|	colorida por onde o quadrado se movimenta.			|
	|	-> JANELA: coordenadas do consolole para criação da |
	|	janela.											|
	|	RETORNA: VOID										|
	|-------------------------------------------------------|
*/
	
void cria_quadrado(QUADRADO *, JANELA);

/*	|---------------  cria ponto ---------------------------|
	|		Ira criar os pontos principais a qual 			|
	|	o programa ira utilizar como referencia para 		|
	|	realizar as configurações e movimentações 			|
	|	RECEBE: 											|
	|	->Janela *: ponteiro que esta armazenada 			|
	|	as coordenadas da janela colorida.					|
	|	RETORNA: VOID										|	
	|-------------------------------------------------------|
*/

void cria_ponto(JANELA *);

/*	|---------------  Janela ---------------------------|
	|	Ira criar a janela principal do jogo			|
	|		Tamanho da janela e posicao da janela		|
	|		Tamanho Maximo;								|
	|	RECEBE:					|
	|	-> JANELA *: ponteiro para a janela do jogo		|	
	|	ETORNA: VOID 									|
	|---------------------------------------------------|
*/	
	
void gerencia_janela(JANELA *);

/*	|---------------  gerencia programa --------------------|
	|		Funcao ira realizar as chamadas das funcoes		|
	|	essa, funcao sera a que ira ler as entradas no 		|
	|	teclado;											|	
	|	RECEBE: 											|
	|	-> QUADRADO * :ponteiro com todas as informações 	|
	|	do quadrado interno que se movimenta				|
	|	->JANELA *: ponteiro que contem todas as informações|
	|	necessarias para manipulação do quadrado colorido 	|
	|	RETORNA: VOID										|
	|-------------------------------------------------------|
*/

void gerencia_programa(JANELA *, QUADRADO *);
	
/*	|---------------  imprime info -------------------------|
	|		Funcao ira imprimir as informacoes na tela		|
	|	(direcao, velocidade  e sentido) armazenadas dentro |
	|	da estrutura QUADRADO;								|
	|	RECEBE:												|
	|	-> QUADRADO: tipo de dado que contem as informações |
	|	do quadrado interno									|
	|	RETORNA: VOID										|
	|-------------------------------------------------------|
*/

void imprime_info(QUADRADO);

/*	|---------------  imprime quadrado -----------------|
	|	 	Funcao realiza a impressa do quadrado		|
	|	utilizando o centro do quadrado como referencia |
	|	ira realizar a impressao dos outros caracteres	|
	|	que compoe a figura na tela						|
	|	RECEBE: 										|
	|	-> QUADRADO: contem os valores do quadrado 		|
	|	interno;										|
	|	->ATIVIDADE: parametro que controla o 			|
	|	comportamento da funcao(ativa ou desativa);		|
	|	RETORNA:VOID									|
	|---------------------------------------------------|
*/

void imprime_quadrado(QUADRADO, ATIVIDADE);

/*	|---------------  movimenta quadrado ---------------|
	|	 	Funcao realiza a movimentacao do quadrado	|
	|	não realiza a impressao do quadrado, a funcao 	|
	|	apenas pega o a direcao do quadrado contido na 	|
	|	estrutura e realiza a movimentacao do centro 	|
	|	na direcao contida la dentro					|
	|	RECEBE: 										|
	|	->QUADRADO *:ponteiro de quadrado que contem 	|
	|	as informações do quadrado interno que sera 	|
	|	movimentado;									|
	|	->JANELA: variavel que armazena a janela por 	|
	|	onde o quadrado interno irra se movimentar;		|
	|	RETORNA:VOID									|
	|---------------------------------------------------|
*/

void movimenta_quadrado(QUADRADO *, JANELA);

/*	|--------------- set Ambiente ----------------------|
	|	Ira criar a definição do prompt do jogo			|
	|	Tamanho da janela e posicao da janela			|
	|	Tamanho Maximo;									|
	|	->CONSOLE *: ponteiro que armazena os valores de| 
	|	referencia do console onde sera executada 		|
	|	o programa principal							|
	|---------------------------------------------------|
*/

void set_ambiente(CONSOLE *, ATIVIDADE);

/*############################  FIM DAS DECLARACOES DAS FUNCOES #####################################*/ 

#endif /* quadradoAnimado */ 