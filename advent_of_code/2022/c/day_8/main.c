#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

// static const char* FILE_NAME = "test_data.txt";
static const char* FILE_NAME = "data.txt";

typedef struct dim {
    int n;
    int m;
} dim;

int
len(char *c){
    int size = 0;
    while(*c != '\0'){
        c++;
        size++;
    }
    return size;
}

void
cleanline(char *line){
    int i = 0;
    while(line[i] != '\0'){
        if (line[i] == '\n'){
            line[i] = '\0';
        }
        i++;
    }
}

int
char_to_int(char c){
    return c - '0';
}

void
debug_mapping(dim dimension, int **m){
    int i, j;
    for(i=0; i<dimension.n; i++){
        for(j=0; j<dimension.m; j++){
            printf("%d", m[i][j]);
        }
        printf("\n");
    }
}

int
validate_all_directions(dim dimension, int **mapping,
        int i, int j){
    int sw_l = 1, sw_r = 1, sw_u = 1, sw_d = 1;

    // all left
    for (int k = j - 1; k >= 0; k--){
        if (mapping[i][k] < mapping[i][j]){
            sw_l = 1;
        } else {
            sw_l = 0;
            break;
        }
    }
    // all right
    for (int k = j + 1; k < dimension.m; k++){
        if (mapping[i][k] < mapping[i][j]){
            sw_r = 1;
        } else {
            sw_r = 0;
            break;
        }
    }
    // all up
    for (int k = i - 1; k >= 0; k--){
        if (mapping[k][j] < mapping[i][j]){
            sw_u = 1;
        } else {
            sw_u = 0;
            break;
        }
    }
    // all down
    for (int k = i + 1; k < dimension.n; k++){
        if (mapping[k][j] < mapping[i][j]){
            sw_d = 1;
        } else {
            sw_d = 0;
            break;
        }
    }

    return sw_d + sw_u + sw_l + sw_r;
}

int
get_total_visible_trees(dim dimension, int **mapping){
    int initial_visible_trees = ((dimension.m - 2) * 2) + dimension.n * 2;
    int count = 0;
    int sw = 0;
    for(int i=1; i<(dimension.n - 1); i++){
        for(int j=1; j<(dimension.m - 1); j++){
            sw = validate_all_directions(dimension, mapping, i, j);
            if (sw != 0) {
                //printf("this is a visible %i\n", mapping[i][j]);
                count++;
            }
        }
    }
    return count + initial_visible_trees;
}

int
get_scenic_score(dim dimension, int **mapping, int i, int j){
    int sw_l = 0, sw_r = 0, sw_u = 0, sw_d = 0;

    // all left
    for (int k = j - 1; k >= 0; k--){
        sw_l++;
        if (mapping[i][k] >= mapping[i][j]){
            break;
        }
    }
    // all right
    for (int k = j + 1; k < dimension.m; k++){
        sw_r++;
        if (mapping[i][k] >= mapping[i][j]){
            break;
        }
    }
    // all up
    for (int k = i - 1; k >= 0; k--){
        sw_u++;
        if (mapping[k][j] >= mapping[i][j]){
            break;
        }
    }
    // all down
    for (int k = i + 1; k < dimension.n; k++){
        sw_d++;
        if (mapping[k][j] >= mapping[i][j]){
            break;
        }
    }
    // printf("sw_l: %i, sw_r: %i, sw_u: %i, sw_d: %i: mapping %i\n", sw_l, sw_r, sw_u, sw_d, mapping[i][j]);
    return sw_d * sw_u * sw_l * sw_r;
}

int
get_max_scenic_score(dim dimension, int **mapping){
    int max = INT_MIN;
    int scenic_score = 0;
    for(int i=0; i<dimension.n; i++){
        for(int j=0; j<dimension.m; j++){
            scenic_score = get_scenic_score(dimension, mapping, i, j);
            if(max <= scenic_score){
                max = scenic_score;
            }
        }
    }
    return max;
}

int
main(){
    FILE *fptr = NULL;
    dim dimension;

    dimension.n = 0;
    dimension.m = 0;

    int i=0, j=0;

    fptr = fopen(FILE_NAME, "r");

    int **mapping = (int**) malloc(sizeof(int*) * (i + 1));
    int c;

    while((c = fgetc(fptr)) != EOF){
        if (c == '\n'){
            i++;
            mapping = (int**) realloc(mapping, sizeof(int*) * (i + 1));
            dimension.m = j;
            j = 0;
        }else{
            mapping[i] = (int*) realloc(mapping[i], sizeof(int) * (j + 1));
            mapping[i][j] = char_to_int(c);
            j++;
        }
    }
    dimension.n = i;

    // debug_mapping(dimension, mapping);
    fclose(fptr);

    int total_visible_trees = get_total_visible_trees(dimension, mapping);
    int max_scenic_score = get_max_scenic_score(dimension, mapping);

    free(mapping);
    printf("total_visible_trees: %i\n", total_visible_trees);
    printf("max_scenic_score: %i\n", max_scenic_score);
}
