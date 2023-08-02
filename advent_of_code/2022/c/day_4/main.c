#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

const char* filename = "data.txt";
//const char *filename = "test_data.txt";

int *getNumbers(char* line){
    char* lineCpy = malloc(sizeof(line));
    strcpy(lineCpy, line);

    char* token = strtok_r(lineCpy, ",", &lineCpy);
    char** tokens = malloc(4 * sizeof(char*));
    int nNumbers = 0;

    for(int i=0;token;i++){
        char* tokenCopy = malloc(sizeof(token));
        strcpy(tokenCopy, token);
        char* number = strtok_r(tokenCopy, "-", &tokenCopy);
        for(int j=0; number; j++){
            tokens[nNumbers] = malloc(sizeof(char*));
            strcpy(tokens[nNumbers], number);
            number = strtok_r(NULL, "-", &tokenCopy);
            nNumbers++;
        }
        token = strtok_r(NULL, ",", &lineCpy);
    }

    int* numbers = malloc(4 * sizeof(int));
    for (int i=0;i<4;i++){
        numbers[i] = atoi(tokens[i]);
    }
    return numbers;
}

int isContained(char* line){
    int* numbers = getNumbers(line);
    if ((numbers[0] >= numbers[2] && numbers[1] <= numbers[3]) || (numbers[2] >= numbers[0] && numbers[3] <= numbers[1])){
        free(numbers);
        return 1;
    } else {
        free(numbers);
        return 0;
    }
}

int isPartiallyContained(char* line){
    int* numbers = getNumbers(line);
    if ( (numbers[0] >= numbers[2] && numbers[0] <= numbers[3]) ||
         (numbers[1] >= numbers[2] && numbers[1] <= numbers[3]) ||
         (numbers[2] >= numbers[0] && numbers[2] <= numbers[1]) ||
         (numbers[3] >= numbers[0] && numbers[3] <= numbers[1])){
        free(numbers);
        return 1;
    } else {
        free(numbers);
        return 0;
    }
}

int part1() {
    FILE* fptr = NULL;
    char line[1024];
    fptr = fopen(filename, "r");
    int sum = 0;
    while(fgets(line, sizeof(line), fptr)){
        //printf("line %s", line);
        sum += isContained(line);
    }
    // printf("still good\n");
    fclose(fptr);
    return sum;
}

int part2() {
    int sum = 0;
    FILE* fptr = NULL;
    char line[1024];
    fptr = fopen(filename, "r");
    while(fgets(line, sizeof(line), fptr)){
        //printf("line %s", line);
        sum += isPartiallyContained(line);
    }
    // printf("still good\n");
    fclose(fptr);
    return sum;
}

int main() {
    int totalpart1 = part1();
    int totalpart2 = part2();
    printf("total part1 repeated: %i\n", totalpart1);
    printf("total part2 repeated: %i\n", totalpart2);
    return 0;
}
