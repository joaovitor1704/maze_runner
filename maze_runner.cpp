#include <stdio.h>
#include <cstdio>
#include <stack>
#include <iostream>
#include <vector>
#include <unistd.h>

using namespace std;

// Matriz de char representnado o labirinto
vector<vector<char>>maze; // Voce também pode representar o labirinto como um vetor de vetores de char (vector<vector<char>>)

// Numero de linhas e colunas do labirinto
int num_rows;
int num_cols;

// Representação de uma posição
struct pos_t {
	int i;
	int j;
};

// Estrutura de dados contendo as próximas
// posicões a serem exploradas no labirinto
std::stack<pos_t> valid_positions;
/* Inserir elemento: 

	 pos_t pos;
	 pos.i = 1;
	 pos.j = 3;
	 valid_positions.push(pos)
 */
// Retornar o numero de elementos: 
//    valid_positions.size();
// 
// Retornar o elemento no topo: 
//  valid_positions.top(); 
// 
// Remover o primeiro elemento do vetor: 
//    valid_positions.pop();


// Função que le o labirinto de um arquivo texto, carrega em 
// memória e retorna a posição inicial
pos_t load_maze(const char* file_name) {
	pos_t initial_pos;
	// Abre o arquivo para leitura (fopen)
	FILE *arq;
	arq = fopen(file_name, "r");
	if(arq == NULL){
		std::cout<<"erro";
	}
	// Le o numero de linhas e colunas (fscanf) 
	// e salva em num_rows e num_cols
	fscanf(arq, "%d %d\n", &num_rows, &num_cols);


	// Aloca a matriz maze (malloc)
	vector<char> caracteres;
	for (int i = 0; i < num_rows+1; ++i){
		caracteres.clear();
		char aux;
			
		for(int j = 0; j < num_cols; ++j){
			fscanf(arq, "%c ", &aux);
			caracteres.push_back(aux);
			if(aux == 'e'){
				initial_pos.i = i;
				initial_pos.j = j;
			}
		}
		maze.push_back(caracteres);
	}
		
	return initial_pos;
}

// Função que imprime o labirinto
void print_maze() {

	for (int i = 0; i < num_rows; ++i) {
		for (int j = 0; j < num_cols; ++j) {
			//printf("%c", maze[i][j]);
			cout<<maze[i][j];
		}
		printf("\n");
	}
	usleep(10000);
}


// Função responsável pela navegação.
// Recebe como entrada a posição initial e retorna um booleando indicando se a saída foi encontrada
bool walk(pos_t pos) {
	
	// Repita até que a saída seja encontrada ou não existam mais posições não exploradas
		// Marcar a posição atual com o símbolo '.'
		// Limpa a tela
		// Imprime o labirinto
	int num = 0;
	while (num < 4)
	{
		/* Dado a posição atual, verifica quais sao as próximas posições válidas
			Checar se as posições abaixo são validas (i>0, i<num_rows, j>0, j <num_cols)
		 	e se são posições ainda não visitadas (ou seja, caracter 'x') e inserir
		 	cada uma delas no vetor valid_positions
		 		- pos.i, pos.j+1
		 		- pos.i, pos.j-1
		 		- pos.i+1, pos.j
		 		- pos.i-1, pos.j
		 	Caso alguma das posiçÕes validas seja igual a 's', retornar verdadeiro
	 	*/
		maze[pos.i][pos.j] = 'o';
		system("clear");
		num = 0;
		print_maze();
		if (pos.i >= 0 && pos.i < num_rows+1 && pos.j + 1  >= 0 && pos.j + 1 < num_cols+1){
			if(maze[pos.i][pos.j+1] == 'x'){
				pos_t pos_aux;
				pos_aux.i = pos.i;
				pos_aux.j = pos.j+1;
				valid_positions.push(pos_aux);
				num++;
			} else if(maze[pos.i][pos.j+1] == 's'){
				return true;
			}
			else{
				num++;
			}
		}
		else{
			num++;
		}

		if (pos.i >= 0 && pos.i < num_rows+1 && pos.j - 1  >= 0 && pos.j - 1 < num_cols+1){
			if(maze[pos.i][pos.j-1] == 'x'){
				pos_t pos_aux;
				pos_aux.i = pos.i;
				pos_aux.j = pos.j-1;
				valid_positions.push(pos_aux);
				num++;
			}else if(maze[pos.i][pos.j-1] == 's'){
				return true;
			}
			else{
				num++;
			}
		}
		else{
			num++;
		}

		if (pos.i+1 > 0 && pos.i+1 < num_rows+1 && pos.j >= 0 && pos.j < num_cols+1){
			if(maze[pos.i+1][pos.j] == 'x'){
				pos_t pos_aux;
				pos_aux.i = pos.i+1;
				pos_aux.j = pos.j;
				valid_positions.push(pos_aux);
				num++;
			}else if(maze[pos.i+1][pos.j] == 's'){
				return true;
			}
			else{
				num++;
			}
		}
		else{
			num++;
		}

		if (pos.i-1 >= 0 && pos.i-1 < num_rows+1 && pos.j >= 0 && pos.j < num_cols+1){
			if(maze[pos.i-1][pos.j] == 'x'){
				pos_t pos_aux;
				pos_aux.i = pos.i-1;
				pos_aux.j = pos.j;
				valid_positions.push(pos_aux);
				num++;
			}else if(maze[pos.i-1][pos.j] == 's'){
				return true;
			}
			else{
				num++;
			}
		}
		else{
			num++;
		}

		maze[pos.i][pos.j] = '.';
		
	}
	
		// Verifica se a pilha de posições nao esta vazia 
		//Caso não esteja, pegar o primeiro valor de  valid_positions, remove-lo
		// e chamar a funçao walk com esse valor
		// Caso contrario, retornar falso
		if (!valid_positions.empty()) {
			pos_t next_position = valid_positions.top();
			valid_positions.pop();
			walk(next_position);
		}
	return false;
}

int main(int argc, char* argv[]) {
	// carregar o labirinto com o nome do arquivo recebido como argumento
	pos_t initial_pos = load_maze("../data/maze6.txt");


	// chamar a função de navegação
	bool exit_found = walk(initial_pos);
	// Tratar o retorno (imprimir mensagem)
	if(exit_found == true)
	{
		cout<<"Saída encontrada";
	}


	return 0;
}
