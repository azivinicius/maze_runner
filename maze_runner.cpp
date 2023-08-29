#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include <cstdlib>



// Matriz de char representnado o labirinto
char** maze; // Voce também pode representar o labirinto como um vetor de vetores de char (vector<vector<char>>)
int num_rows;
int num_cols;
// Numero de linhas e colunas do labirinto

// Representação de uma posição
struct pos_t {
    int i;
    int j;
};

struct maze_map{
	pos_t init;
	int rows;
	int cols;

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
maze_map load_maze(const char* file_name) {
    pos_t initial_pos;
    FILE *file_maze = fopen(file_name, "r");
    if (file_maze == NULL) {
    fprintf(stderr, "Error opening the maze file.\n");
    exit(1);
    }    file_maze = fopen(file_name, "r");
    fscanf(file_maze, "%d %d\n", &num_rows, &num_cols);
    char c;
    maze = (char**)malloc(num_rows * sizeof(char*));

    for (int i = 0; i < num_rows; i++) {
        maze[i] = (char*)malloc(num_cols * sizeof(char));
}
        for (int i = 0; i < num_rows; i++)
    {
        for (int j = 0; j < num_cols; j++)
        {
            // Le o valor da linha i+1,j do arquivo e salva na posição maze[i][j]
            // Se o valor for 'e' salvar o valor em initial_pos

            fscanf(file_maze, "%c", &maze[i][j]);
            if(maze[i][j] == 'e')
            {
				initial_pos.i = i;
				initial_pos.j = j;
            }
        }
        fscanf(file_maze, "%c", &c);  }
    
        maze_map map;
        map.init = initial_pos;
        map.cols = num_cols;
        map.rows = num_rows;
    
    return map;
};

// Função que imprime o labirinto
void print_maze() {
    for (int i = 0; i < num_rows; ++i) {
        for (int j = 0; j < num_cols; ++j) {
            printf("%c", maze[i][j]);
        }
        printf("\n");
    }

};

void clear_maze() {
    #ifdef _WIN32
    // For Windows
    system("cls");
    #else
    // For Unix-like systems (Linux, macOS)
    system("clear");
    #endif
}

// Função responsável pela navegação.
// Recebe como entrada a posição initial e retorna um booleando indicando se a saída foi encontrada
bool walk(pos_t pos) {
    //while (maze[pos.i][pos.j] != 's'){
    // Repita até que a saída seja encontrada ou não existam mais posições não exploradas
        // Marcar a posição atual com o símbolo '.'
        // Limpa a tela
        // Imprime o labirinto
        print_maze();

        maze[pos.i][pos.j] = '.';
        int aux1[4];
        pos_t aux2;
        // avalia baixo
        if(pos.i < num_rows){
        if (maze[pos.i+1][pos.j] == '#') aux1[0] = 0;
        else if (maze[pos.i+1][pos.j] == '.') aux1[0] = 0;
        else if (maze[pos.i+1][pos.j] == 'x') {
            aux2.i = pos.i+1;
            aux2.j = pos.j;
            valid_positions.push(aux2);
        }
        else if (maze[pos.i+1][pos.j] == 's'){
            pos.i = pos.i+1;
            maze[pos.i][pos.j] = '.';

            return true;
        }}
        // avalia direita
        if(pos.j < num_cols){
        if (maze[pos.i][pos.j+1] == '#') aux1[1] = 0;
        if (maze[pos.i][pos.j+1] == '.') aux1[1] = 0;
        else if (maze[pos.i][pos.j+1] == 'x') {
            aux2.i = pos.i;
            aux2.j = pos.j + 1;
            valid_positions.push(aux2);
        }
        else if (maze[pos.i][pos.j+1] == 's'){
            pos.j = pos.j+1;
            maze[pos.i][pos.j] = '.';

            return true;
        }}

        //avalia cima
        if(pos.i>0){
        if (maze[pos.i-1][pos.j] == '#') aux1[2] = 0;
        if (maze[pos.i-1][pos.j] == '.') aux1[2] = 0;
        else if (maze[pos.i-1][pos.j] =='x') {
            aux2.i = pos.i-1;
            aux2.j = pos.j;
            valid_positions.push(aux2);
        }
        else if (maze[pos.i-1][pos.j] == 's'){
            pos.i = pos.i-1;
            maze[pos.i][pos.j] = '.';            
            return true;
        }}
    
        //avalia esquerda
        if(pos.j>0){
        if (maze[pos.i][pos.j-1] == '#') aux1[3] = 0;
        if (maze[pos.i][pos.j-1] == '.') aux1[3] = 0;
        else if (maze[pos.i][pos.j-1] == 'x') {
            aux2.i = pos.i;
            aux2.j = pos.j-1;
            valid_positions.push(aux2);
        }
        else if (maze[pos.i][pos.j-1] == 's'){
            pos.j = pos.j-1;
            maze[pos.i][pos.j] = '.';

            return true;
        }}

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

        //}
    
        // Verifica se a pilha de posições nao esta vazia 
        //Caso não esteja, pegar o primeiro valor de  valid_positions, remove-lo e chamar a funçao walk com esse valor
        // Caso contrario, retornar falso
        if (!valid_positions.empty()) {
            pos_t next_position = valid_positions.top();
            valid_positions.pop();
            clear_maze();
            walk(next_position);
            
        }
    return false;
};

int main(int argc, char* argv[]) {
    // carregar o labirinto com o nome do arquivo recebido como argumento
    pos_t initial_pos = load_maze("/workspaces/maze_runner/data/maze5.txt").init;
    // chamar a função de navegação
    bool exit_found = walk(initial_pos);
    
    // Tratar o retorno (imprimir mensagem)
    
    return 0;
};