#ifndef ISOGRAM_H
#define ISOGRAM_H

#include <stdbool.h>

typedef struct Node node;

bool is_isogram(const char phrase[]);
node* new_node(char v, node* next);
bool is_node_repeated(node* p, char v);
void debug_node(node *p);
void free_nodes(node* p);

#endif
