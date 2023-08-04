#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//const char* data_fn = "data_test.txt";
//const char* move_data_fn = "move_data_test.txt";

const char* data_fn = "data.txt";
const char* move_data_fn = "move_data.txt";

typedef struct Node {
    int size;
    char value;
    struct Node* next;
} node;

typedef struct Group {
    int total_tops;
    node** tops;
} group;

node* pop(node* top);
void push(node* top, char value);
void debug_stack(node* top);
void debug_group(group* groups);
void debug_char_array(char* array);
node* new_node(char value, int size, node* next);

int get_pos(int pos, int cont){
    if(pos==1){
        return 0;
    }else if(cont==pos){
        return cont-1;
    }else{
        return get_pos(pos-3, cont+1);
    }
}

char* parse_input_stacks(char* line){
    int sw = 0, pos = 0;
    char* tokens = malloc(sizeof(char*)*strlen(line));

    //fill array
    for(int i=0;i<strlen(line);i++){
        tokens[i] = ' ';
    }
    tokens[strlen(line)] = '\0';

    for(int i=0;i<=strlen(line);i++){
        if (line[i] == '['){
            sw = 1;
            continue;
        }else if (line[i] == ']'){
            sw = 0;
            continue;
        }
        if(sw == 1){
            pos = get_pos(i, 1);
            tokens[pos] = line[i];
        }
    }

    if (pos == 0){
        return "";
    }
    tokens[pos+1] = '\0';

    return tokens;
}

node** inverse_stacks(node** tops, int tops_size){
    // inverse stacks
    node** tops_copy = malloc(sizeof(node*) * tops_size);
    for(int i=0;i<tops_size;i++){
        node* temp;
        int size = tops[i]->size;
        for(int j=0;j<=size;j++){
            temp = pop(tops[i]);
            if (j == 0){
                tops_copy[i] = new_node(temp->value, 0, NULL);
            }else{
                push(tops_copy[i], temp->value);
            }
        }
    }
    return tops_copy;
}

group* data_to_stack(){
    FILE *fptr = NULL;
    char line[1024];
    char *parsed_line;
    node** tops = malloc(sizeof(node*));
    group* groups = malloc(sizeof(group));
    fptr = fopen(data_fn, "r");
    int* pos = malloc(sizeof(int));
    int tops_size = 0;

    while(fgets(line, sizeof(line), fptr)){
        parsed_line = parse_input_stacks(line);

        if (strlen(parsed_line) == 0){
            continue;
        }

        tops = realloc(tops, sizeof(node*)*(strlen(parsed_line)));
        pos = realloc(pos, sizeof(int)*(strlen(parsed_line)+1));
        for (int i=0;i<=strlen(parsed_line);i++){
            if (pos[i]){
                if (pos[i] != 1){
                    pos[i] = 0;
                }
            }else{
                pos[i] = 0;
            }
        }
        for(int i=0;i<strlen(parsed_line);i++){
            if (parsed_line[i] != ' '){
                if (pos[i]==0){
                    tops[i] = new_node(parsed_line[i], 0, NULL);
                    pos[i] = 1;
                    tops_size++;
                }else{
                    push(tops[i], parsed_line[i]);
                }
            }
        }
        free(parsed_line);
    }
    free(pos);
    fclose(fptr);

    // inverse stacks
    node** tops_copy = inverse_stacks(tops, tops_size);

    free(tops);
    groups->total_tops = tops_size;
    groups->tops = tops_copy;
    return groups;
}

int* parse_input_movements(char* line){
    char** tokens = malloc(sizeof(char) * (strlen(line) + 1));

    int pos = 0, j = 0, k = 0, i = 0;
    while (i < strlen(line)){
        if (isdigit(line[i])){
            k = 0;
            pos = i;
            tokens[j] = malloc(sizeof(char*) * (k+1));
            while(isdigit(line[pos])){
                tokens[j] = realloc(tokens[j], sizeof(char*)*(k+1));
                tokens[j][k] = line[pos];
                pos++;
                k++;
            }
            tokens[j][k] = '\0';
            i += k;
            j++;
        }else{
            i++;
        }
    }

    int *numbers = malloc(sizeof(int)*3);

    for (int i=0;i<3;i++){
        numbers[i] = atoi(tokens[i]);
    }
    return numbers;
}

int part1(){
    group* groups = data_to_stack();
    node** tops = groups->tops;
    int tops_size = groups->total_tops;
    FILE *fptr = NULL;
    char line[1024];
    int *numbers;

    fptr = fopen(move_data_fn, "r");
    while(fgets(line, sizeof(line), fptr)){
        numbers = parse_input_movements(line);
        int move=numbers[0], from=numbers[1]-1, to=numbers[2]-1;
        for(int i=0;i<move;i++){
            // How much I gonna move
            node* temp = pop(tops[from]);
            push(tops[to], temp->value);
            free(temp);
        }
        free(numbers);
    }

    printf("result 1:\t");
    for(int i=0;i<tops_size;i++){
        node* temp = pop(tops[i]);
        printf("%c", temp->value);
    }
    printf("\n");
    free(groups);
    fclose(fptr);
    return 0;
}

int part2(){
    group* groups = data_to_stack();
    node** tops = groups->tops;
    int tops_size = groups->total_tops;
    FILE *fptr = NULL;
    char line[1024];
    int *numbers;

    fptr = fopen(move_data_fn, "r");
    while(fgets(line, sizeof(line), fptr)){
        numbers = parse_input_movements(line);
        int move=numbers[0], from=numbers[1]-1, to=numbers[2]-1;
        node** temps = malloc(sizeof(node*)*move);
        for(int i=0;i<move;i++){
            // How much I gonna move
            temps[i] = pop(tops[from]);
        }
        for(int i=move-1;i>=0;i--){
            push(tops[to], temps[i]->value);
            free(temps[i]);
        }
        free(numbers);
    }

    printf("result 2:\t");
    for(int i=0;i<tops_size;i++){
        node* temp = pop(tops[i]);
        printf("%c", temp->value);
    }
    printf("\n");
    free(groups);
    fclose(fptr);
    return 0;
}

int main(){
    part1();
    part2();
    return 0;
}

node* new_node(char value, int size, node* next){
    node* newnode = (node*) malloc(sizeof(node));
    newnode->value = value;
    newnode->size = size;
    newnode->next = next;
    return newnode;
}

node* pop(node* top){
    node* temp = new_node(top->value, top->size, NULL);
    if (top->next != NULL){
        *top = *(top->next);
    }else{
        *top = *new_node(' ', 0, NULL);
    }
    return temp;
}

void push(node* top, char value){
    if (top->value == ' '){
        top->value = value;
        top->size = 0;
        return;
    }
    node* tempTop = new_node(top->value, top->size, top->next);
    node* temp = new_node(value, top->size + 1, tempTop);
    *top = *temp;
}

void debug_stack(node* top){
    node* temp = top;
    printf("debuging...\n");
    while(temp){
        printf("node node: %c, pos: %i\n", temp->value, temp->size);
        temp = temp->next;
    }
}


void debug_group(group* groups){
    group* temp = groups;
    for(int i=0;i<temp->total_tops;i++){
        debug_stack(temp->tops[i]);
    }
}

void debug_char_array(char* array){
    printf("debuging...\n");
    for(int i=0;i<strlen(array);i++){
        printf("v[%i]: %c\n", i, *(array+i));
    }
}
