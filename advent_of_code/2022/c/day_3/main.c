#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// const char *filename = "test_data.txt";
const char *filename = "data.txt";
/*
 * FIRST WAY TO DO IT - GREEDY
 */
int getPriority(char *c) {
    return isupper(*c) ? *c-'A'+27 : *c-'a'+1;
}

int calculateRuckSackPriority(char* line){
    long int sizeOfLine = strlen(line);
    long int half = sizeOfLine / 2;
    for (int i=0;i<half;i++){
        for (int j=half;j<sizeOfLine-1;j++){
            if (*(line+i) == *(line+j)){
                return getPriority(line+i);
            }
        }
    }
    return 0;
}

typedef struct Node {
    char c;
    struct Node *next;
} node;

node* newNode(char c, node* next){
    node* p = (node*) malloc(sizeof(node));
    p->c = c;
    p->next = next;
    return p;
}

void displayList(node* head){
    node* temp = head;
    int i = 0;
    while(temp){
        temp->next ? printf("node%i=%c->", i, temp->c) :
            printf("node%i=%c\n", i, temp->c);
        temp=temp->next;
        i++;
    }
}

int getCurrentRuckSackPriority(node* head, node* child, int half, int currentPos){
    node* temp = head;
    int i = 0, priority = -1;
    while(temp->next){
        if(temp->c == child->c && currentPos >= half){
            priority = getPriority(&(child->c));
            break;
        }
        temp = temp->next;
        i++;
    }
    if(currentPos < half){
        temp->next = child;
    }
    if(temp->c == child->c && currentPos >= half){
        priority = getPriority(&(child->c));
    }
    return priority;
}

int calculateRuckSackPriorityLL(char* line){
    int half, priority = -1, sizeOfLine = strlen(line);
    node* head;
    half = sizeOfLine/2;
    head = newNode(line[0], NULL);
    for(int i=1;i<sizeOfLine-1;i++){
        priority = getCurrentRuckSackPriority(head, newNode(line[i], NULL),
                half, i);
        if (priority != -1){
            break;
        }
    }
    free(head);
    return priority;
}

int part1Result(){
    FILE *fPtr = NULL;
    clock_t t;
    char line[1024] = "";
    fPtr = fopen(filename, "r");
    int sum = 0, sum2 = 0;;
    // using linked list
    t = clock();
    while (fgets(line, sizeof(line), fPtr)) {
        sum += calculateRuckSackPriorityLL(line);
    }
    fclose(fPtr);
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
    //printf("LL took %f seconds to execute \n", time_taken);
    //printf("total priority: %i\n", sum);

    // iterative
    char line2[1024] = "";
    fPtr = fopen(filename, "r");
    t = clock();
    while (fgets(line, sizeof(line), fPtr)) {
        sum2 += calculateRuckSackPriorityLL(line);
    }
    t = clock() - t;
    double time_taken_2 = ((double)t)/CLOCKS_PER_SEC; // in seconds
    //printf("Iterative took %f seconds to execute \n", time_taken_2);
    fclose(fPtr);
    return sum2;
}

void removeEndLine(char* line){
    if (line[strlen(line)-1] == '\n') {
        line[strlen(line)-1] = ' ';
    }
}

int* sizesLine(char* line){
    int* size = (int*) malloc(sizeof(int) * 3);
    int j=0, k=0;
    for (int i=0;i<strlen(line);i++){
        if (*(line+i) == ' '){
            *(size+k) = j;
            k++;
            j=0;
        }else{
            j++;
        }
    }
    return size;
}

void displaySizes(int* sizes){
    for(int i=0;i<3;i++){
        printf("sizes=%i\n", *(sizes+i));
    }
}

int getPart2Priorities(char* line, int* sizes){
    int priority = 0;
    //printf("size_line=%i, size_calc=%i\n", (int) strlen(line), *(sizes+0)+*(sizes+1)+*(sizes+2)+3);
    for(int i=0;i<*(sizes+0);i++){
        for(int j=*(sizes+0)+1;j<*(sizes+0)+*(sizes+1)+1;j++){
            for(int k=*(sizes+0)+*(sizes+1)+1;k<*(sizes+0)+*(sizes+1)+*(sizes+2)+3;k++){
                //printf("%c,%c,%c,%i,%i,%i\n", *(line+i), *(line+j), *(line+k), i, j, k);
                if(*(line+i) == *(line+j) && *(line+i) == *(line+k)){
                    priority = getPriority(line+i);
                    //printf("line=%c, i=%i, j=%i, k=%i, priority=%i\n", *(line+i), i, j, k, priority);
                    return priority;
                }
            }
        }
    }
    return priority;
}

int part2Result(){
    FILE *fPtr = NULL;
    char line[1024] = "";
    char concatenateLine[1024*3] = "";
    int* sizes = NULL;

    fPtr = fopen(filename, "r");
    int accum = 0;
    int sum = 0;
    int priority = 0;
    while (fgets(line, sizeof(line), fPtr)) {
        removeEndLine(line);
        accum != 0 ? strcat(concatenateLine, line) : strcpy(concatenateLine, line);
        if(accum == 2){
            //printf("concatenateLine: %s, line: %s\n", concatenateLine, line);
            sizes = sizesLine(concatenateLine);
            priority = getPart2Priorities(concatenateLine, sizes);
            sum += priority;
            //printf("concatenateLine: %s, line: %s, priority: %i\n", concatenateLine, line, priority);
            //displaySizes(sizes);
            free(sizes);
        }
        accum ++;
        accum = accum % 3;
    }
    fclose(fPtr);
    return sum;
}

int main() {
    int part1 = part1Result();
    printf("total priority part1: %i\n", part1);
    int part2 = part2Result();
    printf("total priority part2: %i\n", part2);
    return 0;
}
