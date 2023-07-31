#include <stdio.h>

const char FILENAME[] = "data.txt";
//const char FILENAME[] = "test.txt";

int getResult(char oponent, char mine){
    switch(oponent){
        case 'A': //rock
            if(mine=='X'){ //rock
                return 3;
            }else if(mine=='Y'){ //paper
                return 6;
            }else if(mine=='Z'){ //scissors
                return 0;
            }
            break;
        case 'B': //paper
            if(mine=='X'){
                return 0;
            }else if(mine=='Y'){
                return 3;
            }else if(mine=='Z'){
                return 6;
            }
            break;
        case 'C': //scissors
            if(mine=='X'){
                return 6;
            }else if(mine=='Y'){
                return 0;
            }else if(mine=='Z'){
                return 3;
            }
            break;
    }
}

int getOptionValue(char option){
    switch(option){
        case 'X':
            return 1;
            break;
        case 'Y':
            return 2;
            break;
        case 'Z':
            return 3;
            break;
    }
}

int calculateScore(char matchValues[]){
    char oponent = *(matchValues), mine = *(matchValues + 2);
    return getOptionValue(mine) + getResult(oponent, mine);
}

int main(){
    printf("reading file\n");
    FILE *filePtr = NULL;
    char line[1024];
    filePtr = fopen(FILENAME, "r");
    int score = 0;
    while(fgets(line, sizeof(line), filePtr)){
        //printf("%s", line);
        score += calculateScore(line);
    }
    printf("score %i\n", score);
    return 0;
}
