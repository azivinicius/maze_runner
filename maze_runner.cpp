#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include <iostream>
#include <vector>
#include <chrono> 
#include <thread>



char** maze; 
int num_rows;
int num_cols;

struct pos_t {
    int i;
    int j;
};

struct maze_map{
	pos_t init;
	int rows;
	int cols;

};

std::stack<pos_t> valid_positions;

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
    // para Windows
    system("cls");
    #else
    // para Linux ou macOS
    system("clear");
    #endif
}

void clear_maze_with_delay() {
    // Espera 30 milissegundos (30ms)
    clear_maze();
    std::this_thread::sleep_for(std::chrono::milliseconds(80));

    // Limpa a tela e imprime o próximo estado do labirinto
    print_maze();
}
// Função responsável pela navegação.
// Recebe como entrada a posição initial e retorna um booleando indicando se a saída foi encontrada
bool walk(pos_t pos) {

        std::vector<std::thread> t;
        maze[pos.i][pos.j] = 'o';

        clear_maze_with_delay();

        pos_t aux;
        // avalia baixo
        if(pos.i < num_rows){
         if (maze[pos.i+1][pos.j] == 'x') {
            aux.i = pos.i+1;
            aux.j = pos.j;
            valid_positions.push(aux);
        }
        else if (maze[pos.i+1][pos.j] == 's'){
            pos.i = pos.i+1;
            return true;
        }}
        // avalia direita
        if(pos.j < num_cols){
         if (maze[pos.i][pos.j+1] == 'x') {
            aux.i = pos.i;
            aux.j = pos.j + 1;
            valid_positions.push(aux);
        }
        else if (maze[pos.i][pos.j+1] == 's'){
            pos.j = pos.j+1;
            return true;
        }}

        //avalia cima
        if(pos.i>0){
         if (maze[pos.i-1][pos.j] =='x') {
            aux.i = pos.i-1;
            aux.j = pos.j;
            valid_positions.push(aux);
        }
        else if (maze[pos.i-1][pos.j] == 's'){
            pos.i = pos.i-1;

            return true;
        }}
    
        //avalia esquerda
        if(pos.j>0){
         if (maze[pos.i][pos.j-1] == 'x') {
            aux.i = pos.i;
            aux.j = pos.j-1;
            valid_positions.push(aux);
        }
        else if (maze[pos.i][pos.j-1] == 's'){
            pos.j = pos.j-1;

            return true;
        }}

        if(valid_positions.size()>1){

            maze[pos.i][pos.j] = '.';

            for (int i = 0; i < valid_positions.size(); i++){
                std::thread aux(valid_positions.top());
                aux.detach();
                valid_positions.pop();
            }
        }

        else if (!valid_positions.empty()) {
            pos_t next_position = valid_positions.top();
            valid_positions.pop();
            maze[pos.i][pos.j] = '.';
            walk(next_position);
        }

    
    return false;
};

int main(int argc, char* argv[]) {
   
    pos_t initial_pos = load_maze("/workspaces/maze_runner/data/maze2.txt").init;
    bool exit_found = walk(initial_pos);

    return 0;
};