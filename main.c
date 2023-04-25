/* 

	programa: Quadrado animado 
	Descrição: O programa é uma janela que abre no prompt de comando do computador, essa janela sera interativa e  o usuario podera mudar sua cor e seu tamanho
	dentro dessa janela havera um quadrado que ficara se movimentando esse quadrado pode ter suas propriedade de direção e velocidade alteradas pelo usuario caso ele 
	assim dejesar e entrar com as teclas corretas;
	Programador: Gabriel Pereira dos Santos Dias
	data de modificação: 11/04/2023
	
	*-------- Regras de utilização do programa -----* 
	
	Obs: Para evitar erros durante a execução recomenda-se que configure seu prompt de comando para que utilize as propriedades herdadas do prompt 
	
	codigo para compilação: gcc main.c -o saida.exe conio_v3.2.4.c console_v1.5.4.c graphics_v1.1.c quadradoAnimado.c -lgdi32 -Wall -Werror -Wextra -pedantic -lwinmm  
	
*/

#include "quadradoAnimado.h" /* inicia_jogo */ 

int main(int argc, char *argv[])
{	
	argc = argc;
	argv = argv;
	
	inicia_jogo();

	return 0;
}