#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

const char filename[] = "data.txt";

typedef struct Node {
    int data;
    struct Node *next;
} node;

node* new_node(int _data, node* _next){
    node *p = (node*) malloc(sizeof(node));
    p->data = _data;
    p->next = _next;
    return p;
}

void print_ord_linked_list(node* _head){
    int sum = 0;
    node *temp=_head;
    while(temp!=NULL){
        printf("data: %i\n", temp->data);
        sum += temp->data;
        temp = temp->next;
    }
    printf("total ammount: %i\n", sum);
}

void top_n(node* _head, int n){
    node *temp=_head;
    int i=1;
    while(temp!=NULL){
        if (i<n){
            temp = temp->next;
            i++;
        }else{
            temp->next = NULL;
            break;
        }
    }
}

node* insert_node(node* head, node* _node){
    node *temp, *copy_head;
    copy_head = head;

    if (copy_head->data <= _node->data){
        _node->next = copy_head;
        copy_head = _node;
    }else{
        temp = head;
        if (temp->next == NULL){
            temp->next = _node;
        }else{
            while(temp->next != NULL){
                if (_node->data >= temp->next->data){
                    _node->next = temp->next;
                    temp->next = _node;
                    break;
                }else{
                    temp=temp->next;
                }
            }
        }
    }
    return copy_head;
}

int char_to_double(char c){
    return (double) c-'0';
}

int string_to_int(char number[]) {
    int sum = 0;
    int N = strlen(number)-1;
    for(int i=0; i<N ;i++) {
        sum += (int) char_to_double(number[i])*pow(10, N-(i+1));
    }
    return sum;
}

int max(int x, int y){
    return x <= y ? y : x;
}

node* get_max_calories(const char filename[]){
    FILE *fptr; // Define file pointer

    fptr = fopen(filename, "r");
    char line[1024];
    int sum_calories = 0;
    int max_calories = INT_MIN;
    int insertion_count = 1;

    node *head=new_node(max_calories, NULL), *temp_node;

    if (fptr != NULL){
        while(fgets(line, sizeof line, fptr)){
            if (strcmp(line, "\n") == 0){//strcmp return 0 if both strings are equal
                //enter if line is equal to newline
                //calculate max calories
                temp_node = new_node(sum_calories, NULL);
                head=insert_node(head, temp_node);
                insertion_count++;
                sum_calories = 0;
            }else{
                //enter if line is different to newline
                sum_calories += string_to_int(line);
            }

            if (insertion_count>3){
                insertion_count=0;
                top_n(head, 3);
            }
        }
    }
    //close file
    fclose(fptr);
    return head;
}

int main() {
    printf("reading file %s\n", filename);
    node *max_calories = get_max_calories(filename);
    print_ord_linked_list(max_calories);
    free(max_calories);
    return 0;
}
