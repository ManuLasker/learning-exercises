#include <stdio.h>

const char FILENAME[] = "data.txt";
//const char FILENAME[] = "test.txt";

int getScoreMatch(char option){
    switch(option){
        case 'X':
            return 0;
        case 'Y':
            return 3;
        case 'Z':
            return 6;
    }
}

int getScoreOption(char oponent, char option){
    switch(oponent){
        case 'A': //rock
            if(option=='X'){ //lose
                return 3;
            }else if(option=='Y'){ //tie
                return 1;
            }else if(option=='Z'){ //win
                return 2;
            }
        case 'B': //paper
            if(option=='X'){
                return 1;
            }else if(option=='Y'){
                return 2;
            }else if(option=='Z'){
                return 3;
            }
        case 'C': //scissors
            if(option=='X'){
                return 2;
            }else if(option=='Y'){
                return 3;
            }else if(option=='Z'){
                return 1;
            }
    }
}

int getScore(char matchValues[]){
    char oponent=*(matchValues), option=*(matchValues+2);
    return getScoreMatch(option) + getScoreOption(oponent, option);
}

int main(){
    FILE *fPtr = NULL;
    char line[1024] = {};
    //open file
    fPtr = fopen(FILENAME, "r");
    int totalScore = 0;
    while(fgets(line, sizeof(line), fPtr)){
        totalScore += getScore(line);
    }
    printf("Score: %i\n", totalScore);
    return 0;
}
