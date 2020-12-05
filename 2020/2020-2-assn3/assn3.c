// Started at 14:32 11/20/2020

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

#define W 30
#define H 5
#define MAPFILE "map.txt"

#define TREE_MAX 7
#define CAR_MAX 3

#define _CAR_THERE(X) (*(X) == '[' || *(X) == '=' || *(X) == ']' || *((X) + 1) == '[' )

typedef enum { EASY = 200, NORMAL = 100, HARD = 50 } Level;
typedef enum { TREE = 1, CAR = 2 } Object;

int menu_draw() {
    int input;
    system("cls");
    printf("=====================\n");
    printf("1. Quit the game (1)\n");
    printf("2. Set the level (2)\n");
    printf("3. Start the game (3)\n");
    printf("=====================\n");
    while (1) {
        input = _getch();
        switch (input) {
        case '1':
        case '2':
        case '3': return input;
        default: continue;
        }
    }
}

Level set_level() {
    int input;
    system("cls");
    printf("=====================\n");
    printf("1. Easy (1)\n");
    printf("2. Normal (2)\n");
    printf("3. Hard (3)\n");
    printf("=====================\n");
    while (1) {
        input = _getch();
        switch (input) {
        case '1': return EASY;
        case '2': return NORMAL;
        case '3': return HARD;
        default: continue;
        }
    }
}

void print_map(char** map, int user_pos, int cur_step, int steps) {
    system("cls");
    printf("Score: %d/%d\n", cur_step, steps);

    for (int h = H - 1; h >= 0; h--) {
        for (int w = 0; w < W; w++) {
            if (h == 0 && (w == user_pos || w == user_pos + 1))
                printf("@");
            else printf("%c", map[h][w]);
        }
        printf("\n");
        for (int w = 0; w < W; w++) printf("-");
        printf("\n");
    }
}

// return position for object, considering inverval with previous one
int set_pos(Object obj, int remain_obj_num, int cur_pos,
    int* new_obj_siz) {
    int min_obj_siz, max_obj_siz, obj_siz_range;
    int min_space_siz, max_space_siz, space_siz_range;
    int remain_space = W - cur_pos;
    int obj_pos;

    int _min_obj_siz, _max_obj_siz, _min_space_siz;
    int _no_next_interval = 0;

    if (obj == TREE) {
        _min_obj_siz = 2;
        _max_obj_siz = 5;
        _min_space_siz = 2;
        _no_next_interval = (remain_obj_num == 0);
    }
    else {
        _min_obj_siz = 4;
        _max_obj_siz = 7;
        _min_space_siz = 4;
    }

    min_space_siz = _min_space_siz;

    min_obj_siz = _min_obj_siz;
    max_obj_siz = min(remain_space / remain_obj_num - min_space_siz, _max_obj_siz);
    if (max_obj_siz == min_obj_siz) *new_obj_siz = min_obj_siz;
    else if (max_obj_siz < min_obj_siz)
    {
        printf("FATAL ERROR: max_obj_siz(%d) smaller than min_obj_siz(%d)", max_obj_siz, min_obj_siz);
        exit(2);
    }
    else {
        obj_siz_range = max_obj_siz - min_obj_siz;
        *new_obj_siz = rand() % obj_siz_range + min_obj_siz;
    }

    // remain_space -= *new_obj_siz;
    if (obj == TREE && cur_pos == 0)
        min_space_siz = 0;
    max_space_siz = remain_space / remain_obj_num - min_obj_siz;
    if (remain_obj_num == 1)
        max_space_siz = remain_space - *new_obj_siz;
    if (max_space_siz == min_space_siz) obj_pos = min_space_siz;
    else if (max_space_siz < min_space_siz)
    {
        printf("FATAL ERROR: max_space_siz(%d) smaller than min_space_siz(%d)", max_space_siz, min_space_siz);
        exit(3);
    }
    else {
        space_siz_range = max_space_siz - min_space_siz;
        obj_pos = rand() % space_siz_range + min_space_siz;
    }
    return cur_pos + obj_pos;

}

char* new_map(int obstacle[2]) {
    Object obj = (Object)obstacle[0];
    int num = obstacle[1], remain_num, i;
    int obj_pos = 0, obj_siz, next_pos;

    char* newmap = malloc(W, sizeof(char));
    for (int i = 0; i < W; i++)
        newmap[i] = ' ';

    for (remain_num = num; remain_num > 0; remain_num--) {
        obj_pos = set_pos(obj, remain_num, obj_pos, &obj_siz);
        if (obj == TREE)
            for (i = 0; i < obj_siz; i++)
                newmap[obj_pos + i] = '#';
        else {
            newmap[obj_pos] = '[';
            for (i = 1; i < obj_siz - 1; i++)
                newmap[obj_pos + i] = '=';
            newmap[obj_pos + obj_siz - 1] = ']';
        }
        obj_pos += obj_siz;
    }

    return newmap;
}

void map_time_elapse(char** map, int is_car_line[]) {
    int car_len;
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (!is_car_line[i])
                break;
            if (map[i][j] == '[') {
                car_len = 3;
                while (map[i][(j + car_len) % W] != ']') car_len++;
                for (int c = j + car_len; c >= j; c--)
                    map[i][(c + 1) % W] = map[i][c % W];
                map[i][j] = ' ';
                j += car_len + 1;
            }
            
        }
    }
}

void map_proceed(char** map, int(*obstacle)[2], 
                int is_car_line[], int *cur_step, int steps) {
    free(map[0]);
    for (int i = 0; i < H - 1; i++) {
        map[i] = map[i + 1];
        is_car_line[i] = is_car_line[i + 1];
    }

    if (*cur_step + H < steps) {
        map[H - 1] = new_map(obstacle[*cur_step + H]);
        is_car_line[H - 1] = (obstacle[*cur_step + H][0] == CAR);
    }
    else {
        map[H - 1] = (char*)malloc(W * sizeof(char));
        for (int w = 0; w < W; w++)
            map[H - 1][w] = ' ';
        is_car_line[H - 1] = 0;
    }
    *cur_step += 1;
}

int run_game(int(*obstacle)[2], int steps, Level speed) {
    char** map;
    int is_car_line[H];
    int cur_step = 0;
    int user_pos = 14, win = 0, game_over = 0;
    int i, j, ms = 0;
    char cmd;

    // Initialization
    map = (char**)malloc(H * sizeof(char*));
    for (int h = 0; h < H; h++)
        map[h] = new_map(obstacle[h]);

    for (i = 0; i < H; i++) {
        for (j = 0; j < W; j++) 
            if (_CAR_THERE(&map[i][j]))
                break;
        if (j == W) is_car_line[i] = 0;
        else is_car_line[i] = 1;
    }

    print_map(map, user_pos, cur_step, steps);
    
    while (1) {
        if (_kbhit()) {
            cmd = _getch();
            switch (cmd) {
            case 'W': case 'w':
                if (map[1][user_pos] == '#' || map[1][user_pos + 1] == '#')
                    break;
                if (_CAR_THERE(&map[1][user_pos])) {
                    game_over = 1;
                    break;
                }
                map_proceed(map, obstacle, is_car_line, &cur_step, steps);
                break;
            case 'A': case 'a': 
                if (user_pos > 0 && map[0][user_pos - 1] != '#') {
                    if (map[0][user_pos - 1] == ']') {
                        game_over = 1;
                        break;
                    }
                    user_pos -= 1;
                }
                break;
            case 'D': case 'd':
                if (user_pos < W - 2 && map[0][user_pos + 2] != '#') {
                    if (map[0][user_pos + 2] == '[') {
                        game_over = 1;
                        break;
                    }
                    user_pos += 1;
                }
                break;
            }
            print_map(map, user_pos, cur_step, steps);
            if (cur_step == steps) {
                win = 1;
                break;
            }
        }
        if (game_over) break;

        Sleep(25);
        ms += 25;
        if (ms >= speed) {
            map_time_elapse(map, is_car_line);
            if (map[0][user_pos]==']')  // Hit by car
                break;
            ms = 0;
            print_map(map, user_pos, cur_step, steps);
        }
    }

    if (win)
        printf("Congratulations!!! You Win!!!\n");
    else
        printf("Game Over!!!\n");
    printf("Press Enter key... ");
    while (getchar() != '\n');

    for (int h = 0; h < H; h++)
        free(map[h]);
}

int load_map_info(int(**obstacle)[2]) {
    FILE* f;
    int num_step;
    int warning = 0;
    if ((f = fopen(MAPFILE, "r")) == NULL) {
        printf("File open error!! Cannot open %s\n", MAPFILE);
        exit(100);
    }

    fscanf(f, "%d", &num_step);
    *obstacle = (int(*)[2])malloc(num_step * sizeof(int[2]));
    for (int i = 0; i < num_step; i++) {
        fscanf(f, "%d%d", &(*obstacle)[i][0], &(*obstacle)[i][1]);
        if ((*obstacle)[i][0] == TREE && (*obstacle)[i][1] > TREE_MAX) {
            printf("NOTICE: Too many Tree objects (%d), automatically set to TREE_MAX (%d)\n",
                (*obstacle)[i][1], TREE_MAX);
            (*obstacle)[i][1] = TREE_MAX;
            warning = 1;
        }
        else if ((*obstacle)[i][0] == CAR && (*obstacle)[i][1] > CAR_MAX) {
            printf("NOTICE: Too many Car objects (%d), automatically set to CAR_MAX (%d)\n",
                (*obstacle)[i][1], CAR_MAX);
            (*obstacle)[i][1] = CAR_MAX;
            warning = 1;
        }
    }
    if (warning) {
        printf("(Press Enter...) ");
        while (getchar() != '\n');
    }
    return num_step;
}

int main()
{
    int(*obstacle)[2];
    int steps;
    Level game_speed = NORMAL;

    srand(time(NULL));
    steps = load_map_info(&obstacle);

    while (1) {
        switch (menu_draw()) {
        case '1': return 0;
        case '2': game_speed = set_level(); break;
        case '3': run_game(obstacle, steps, game_speed);
        }
    }
    free(obstacle);
}