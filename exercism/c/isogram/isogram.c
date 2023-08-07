#include "isogram.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

struct Node {
    char v;
    struct Node *next;
};

const char exceptions[2] = {' ', '-'};

node *new_node(char v, node *next) {
    node *new_node = (node *)malloc(sizeof(node));
    char temp_v = isupper(v) ? tolower(v) : v;
    new_node->v = temp_v;
    new_node->next = next;
    return new_node;
}

bool is_node_repeated(node *p, char v) {
    node *temp = p;
    bool sw = false;
    char temp_v = isupper(v) ? tolower(v) : v;

    while (temp) {
        if (temp_v == temp->v && v != exceptions[0] && v != exceptions[1]) {
            return true;
        }
        if(temp->next == NULL){
            temp->next = new_node(temp_v, NULL);
            break;
        }
        temp = temp->next;
    }
    return sw;
}

void debug_node(node *p) {
    node *temp = p;
    while (temp) {
        printf("%c", temp->v);
        temp = temp->next;
    }
    printf("\n");
}

void free_nodes(node *p) {
    node *temp;
    while (p) {
        temp = p;
        p = p->next;
        free(temp);
    }
}

bool is_isogram(const char phrase[]) {
    node *p = NULL;
    int i = 0;
    bool sw = true, sw_temp = true;

    if (!phrase)
        return false;

    while (phrase[i] != '\0') {
        if (i == 0) {
            p = new_node(phrase[i], NULL);
        } else {
            sw_temp = is_node_repeated(p, phrase[i]);
            if (sw_temp == true) {
                sw = false;
                break;
            }
        }
        i++;
    }

    if (p) {
        //debug_node(p);
        //printf("%s\n", phrase);
        free_nodes(p);
    }

    return sw;
}
