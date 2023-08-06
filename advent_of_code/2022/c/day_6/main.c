#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//const char* FILE_NAME = "test_data.txt";
const char* FILE_NAME = "data.txt";

typedef struct Node {
    int v;
    int pos;
    struct Node* next;
} node;

node*
newNode(int v, int pos, node* next){
    node* n = (node*) malloc(sizeof(node));
    n->v = v;
    n->pos = pos;
    n->next = next;
    return n;
}

void
debugString(node* p){
    node* temp = p;
    while(temp){
        printf("%c:%i;", temp->v, temp->pos);
        temp = temp->next;
    }
    printf("\n");
}

void
insertNode(node* p, int c, int pos){
    node* temp = p;
    int compare_sw = 0;
    int insert_sw = 0;
    while(temp){
        if (temp->next == NULL){
            temp->next = newNode(c, pos, NULL);
            insert_sw = 1;
        }
        compare_sw = (temp->v == c) ? 1 : 0;
        if (compare_sw){
            *p = *(temp->next);
        }
        if (insert_sw){
            break;
        }
        temp = compare_sw ? p: temp->next;
    }
}

int
get_pos(node *p, int size){
    int count = 0, pos;
    node *temp = p;
    while(temp){
        pos = temp->pos;
        count++;
        temp = temp->next;
    }
    return count==size ? pos : 0;
}

void get_number_distincts(int message_size){
    FILE* fPtr = NULL;
    int c, pos=1, result, sw=0;
    node* p;

    fPtr = fopen(FILE_NAME, "r");

    while((c = fgetc(fPtr)) != EOF){
        if (c != '\n'){
            if (pos == 1){
                p = newNode(c, pos, NULL);
            }else {
                insertNode(p, c, pos);
                result = get_pos(p, message_size);
                if(result && sw == 0){
                    //debugString(p);
                    printf("result %i\n", result);
                    sw = 1;
                }
            }
            pos++;
        }else{
            free(p);
            pos = 1;
            sw = 0;
        }
    }

    fclose(fPtr);
}


int
main(){
    get_number_distincts(4);
    get_number_distincts(14);
    return 0;
}
