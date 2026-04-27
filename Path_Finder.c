#include<stdio.h>
#include<string.h>          // Used becasue it has strcpy
#include<stdlib.h>          // Needed to Clean the Screen
#include<time.h>
#define NUM_ENEMIES 2       // Used to define the number of enemies
#ifdef _WIN32
#include<conio.h>            // Used to get input without pressing enter
#else
#include <unistd.h>
#include <termios.h>       // Used to get input without pressing enter
char getch(void) {
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
#endif
int main(void){
    char map[20][20] ={
    {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
    {'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#'},
    {'#','.','.','.','.','.','=','=','=','.','.','=','.','=','.','.','.','.','.','#'},
    {'#','.','=','=','=','.','=','.','=','.','.','=','=','=','.','=','=','=','.','#'},
    {'#','.','=','=','=','.','.','.','.','.','.','.','.','.','.','=','=','=','.','#'},
    {'#','.','=','=','=','.','.','.','.','.','.','.','.','.','.','=','=','=','.','#'},
    {'#','.','=','=','=','.','=','=','=','=','=','=','=','=','.','=','=','=','.','#'},
    {'#','.','=','=','=','.','=','=','=','=','=','=','=','=','.','=','=','=','.','#'},
    {'#','.','=','=','=','.','=','=','=','=','=','=','=','=','.','=','=','=','.','#'},
    {'#','.','.','.','.','.','=','=','=','=','=','=','=','=','.','.','.','.','.','#'},
    {'#','.','=','=','=','.','=','=','=','=','=','=','=','=','.','=','=','=','.','#'},
    {'#','.','=','=','=','.','.','.','=','=','=','=','.','.','.','=','=','=','.','#'},
    {'#','.','=','=','=','.','.','.','=','=','=','=','.','.','.','=','=','=','.','#'},
    {'#','.','=','=','=','=','=','.','=','=','=','=','.','=','=','=','=','=','.','#'},
    {'#','.','=','=','=','=','=','.','=','=','=','=','.','=','=','=','=','=','.','#'},  
    {'#','.','=','=','=','=','=','.','=','=','=','=','.','=','=','=','=','=','.','#'},
    {'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#'},
    {'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#'},
    {'#','#','#','#','#','#','#','#','.','.','.','.','#','#','#','#','#','#','#','#'},
    {' ',' ',' ',' ',' ',' ',' ','#','.','.','.','.','#',' ',' ',' ',' ',' ',' ',' '}};
    srand(time(NULL));                  // Guesses a random spot in the array
    int rover_select,p=19,q=10,score=1;
    char rover_forward,rover_backward,rover_left,rover_right;
    char rover_name[11];
    int enemy_p[NUM_ENEMIES], enemy_q[NUM_ENEMIES];         // Some necessary setup
    char enemy_under[NUM_ENEMIES];
    char enemy_char = 'X';
    int game_over = 0;

    for (int e = 0; e < NUM_ENEMIES; e++) {                 // Dropping the enemy
        int valid_spawn = 0;
        while (!valid_spawn) {
            enemy_p[e] = rand() % 20;                       // Make sures the srand's output is within the array's grid
            enemy_q[e] = rand() % 20;
            
            if (map[enemy_p[e]][enemy_q[e]] != '#' && 
                map[enemy_p[e]][enemy_q[e]] != '=' && 
                map[enemy_p[e]][enemy_q[e]] != 'X' &&
                map[enemy_p[e]][enemy_q[e]] != ' ' &&
                !(enemy_p[e] == p && enemy_q[e] == q)) {    // Makes sure it doesn't sabotage the map
                valid_spawn = 1;
            }
        }
        enemy_under[e] = map[enemy_p[e]][enemy_q[e]];
        map[enemy_p[e]][enemy_q[e]] = enemy_char;
    }
    printf("============[- ROV-MAN | A SEGFAULT SURVIVOR -]============\n\n");
    printf("1. The Aerial - ( ^ | < | > | v )\n2. The Tanker - ( M | W | E | 3 )\n3. The Minert - ( n | u | c | o )\n\nSelect your Rover (1 - 3): ");
    scanf("%d",&rover_select);
    switch(rover_select){
        case 1:
        strcpy(rover_name,"The Aerial");
            rover_forward = '^';rover_backward = 'v';rover_left = '<';rover_right = '>';
            break;
        case 2:
            strcpy(rover_name,"The Tanker");
            rover_forward = 'M';rover_backward = 'W';rover_left = 'E';rover_right = '3';
            break;
        case 3:
            strcpy(rover_name,"The Digger");
            rover_forward = 'n';rover_backward = 'u';rover_left = 'c';rover_right = 'o';
            break;
        default:
            printf("Choosing default: The Aerial\n");
            strcpy(rover_name, "The Aerial");
            rover_forward = '^'; rover_backward = 'v'; rover_left = '<'; rover_right = '>';
            break;
    }
    char input;
    map[p][q]=rover_forward;
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
    printf("\e[?25l");
    while(score != 160){
        printf("\033[H");
        int i,j,rows=20,cols=20;
        for(i=0;i<rows;i++){
            for(j=0;j<cols;j++){
                if (map[i][j] == '#') {
                printf("  \033[1;38;2;0;0;255m%c\033[0m  ", map[i][j]); // Blue Walls
            } 
            else if (map[i][j] == rover_forward || map[i][j] == rover_backward || map[i][j] == rover_left || map[i][j] == rover_right) {
                printf("  \033[1;38;2;0;255;0m%c\033[0m  ", map[i][j]); // Green Rover
            } 
            else if (map[i][j] == '=') {
                printf("  \033[1;38;2;255;0;255m%c\033[0m  ", map[i][j]); // Black Obstacles    
            }
            else if (map[i][j] == '.') {
                printf("  \033[1;38;2;255;255;0m%c\033[0m  ", map[i][j]); // Yellow Path
            }
            else if (map[i][j] == 'X'){
                printf("  \033[1;38;2;255;0;0m%c\033[0m  ", map[i][j]); // Red Enemies
            }
            else {   
                printf("  %c  ", map[i][j]); // Regular space
            }
            }
            printf("\n");
        }
        printf("\n\033[1;38;2;0;255;0mRover: %s\nScore: %d\nControls: (W,S,A,D)\nWatch out for the Enemies in RED!\033[0m",rover_name,score);
        input = getch();
        //scanf("%c",&input);
        //getchar();
        // for moving forward
        if((input == 'W' || input == 'w') && map[p-1][q] != '#' && map[p-1][q] != '='){
            if(map[p-1][q] == '.'){
                score+=1;
            }
            map[p-1][q] = rover_forward;
            map[p][q] = ' ';
            p--;
        // for moving left
        }else if((input == 'A' || input == 'a') && map[p][q-1] != '#' && map[p][q-1] != '='){
            if(map[p][q-1] == '.'){
                score+=1;
            }
            map[p][q-1] = rover_left;             
            map[p][q] = ' ';
            q--;
        // for moving right
        }else if((input == 'D' || input == 'd') && map[p][q+1] != '#' && map[p][q+1] != '='){
            if(map[p][q+1] == '.'){
                score+=1;
            }
            map[p][q+1] = rover_right;
            map[p][q] = ' ';
            q++;
        // for moving backward
        }else if((input == 'S' || input == 's') && map[p+1][q] != '#' && map[p+1][q] != map[20][q] && map[p+1][q] != '='){
            if(map[p+1][q] == '.'){
                score+=1;
            }
            map[p+1][q] = rover_backward;
            map[p][q] = ' ';
            p++;
        }
        // Moving Moving The Enemies
        for (int e = 0; e < NUM_ENEMIES; e++) {
            if (p == enemy_p[e] && q == enemy_q[e]) {
                game_over = 1;
                break;
            }
        }
        if (game_over) break; 

        for (int e = 0; e < NUM_ENEMIES; e++) {
            map[enemy_p[e]][enemy_q[e]] = enemy_under[e];

            int diff_p = abs(p - enemy_p[e]);
            int diff_q = abs(q - enemy_q[e]);
            
            int test_p = enemy_p[e];
            int test_q = enemy_q[e];
                                        // Based on the difference Between the Rover and the Enemies
            if (diff_p > diff_q) {
                test_p += (p > enemy_p[e]) ? 1 : -1; 
                if (map[test_p][enemy_q[e]] == '#' || map[test_p][enemy_q[e]] == '=' || map[test_p][enemy_q[e]] == 'X') {
                    test_p = enemy_p[e];
                    if (q != enemy_q[e]) test_q += (q > enemy_q[e]) ? 1 : -1;
                }
            } else {
                test_q += (q > enemy_q[e]) ? 1 : -1; 
                if (map[enemy_p[e]][test_q] == '#' || map[enemy_p[e]][test_q] == '=' || map[enemy_p[e]][test_q] == 'X') {
                    test_q = enemy_q[e];
                    if (p != enemy_p[e]) test_p += (p > enemy_p[e]) ? 1 : -1;
                }
            }

            if (map[test_p][test_q] != '#' && map[test_p][test_q] != '=' && map[test_p][test_q] != 'X') {
                enemy_p[e] = test_p;
                enemy_q[e] = test_q;
            }

            if (enemy_p[e] != p || enemy_q[e] != q) {
                enemy_under[e] = map[enemy_p[e]][enemy_q[e]];
            }

            map[enemy_p[e]][enemy_q[e]] = enemy_char;

            if (enemy_p[e] == p && enemy_q[e] == q) {
                game_over = 1;
            }
        }
    }
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
    if(game_over){
        printf("\n\n\n\033[1;38;2;255;0;0mH------H------H------H------H------H------H------H------H\033[0m");
        printf("\n\033[1;38;2;255;0;0m=====================\033[0m[- GAME OVER -]\033[1;38;2;255;0;0m=====================\033[0m");
        printf("\n\033[1;38;2;255;0;0mH------H------H------H------H------H------H------H------H\033[0m\n\n\n");
        printf("\033[1;38;2;255;0;255mH------------->\033[0m\033[1;38;2;255;0;0m YOU GOT SLIMED AT (%d,%d) \033[1;38;2;255;0;255m<-------------H\033[0m\n\n\n", p, q);
    }else{
        printf("\n\n\n\033[1;38;2;0;255;0mH------H------H------H------HH------H------H------H------H\033[0m");
        printf("\n\033[1;38;2;0;255;0m===================\033[0m[- GAME COMPLETED -]\033[1;38;2;0;255;0m===================\033[0m");
        printf("\n\033[1;38;2;0;255;0mH------H------H------H------HH------H------H------H------H\033[0m\n\n\n");
    }
    return 0;
}