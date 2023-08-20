#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int len(char *line, char i, char f);

typedef struct link_node {
    int size;
    char* name;
    struct link_node *next;
} link_node;

void insert_new_linked_node(link_node* parent, int size, char *name);

typedef struct node {
    bool is_dir;
    int size;
    char *name;
    struct node *parent;
    struct node *child_head;
    struct node *brother;
} node;

// const static char *file_name = "test_data.txt";
const static char *file_name = "data.txt";
const int total_disk_space = 70000000;
const int total_unused_space_needed = 30000000;

int is_dir(char *line) {
    if ('d' == *line) {
        return 1;
    }
    return 0;
}

int pow_ten(int val) {
    int p = 1;
    for (int i = 0; i < val; i++) {
        p = p * 10;
    }
    return p;
}

int char_to_num(char c) { return c - '0'; }

int get_file_size(char *line) {
    int sum = 0;
    int count = 1;
    int size = len(line, '\0', ' '); // -1 to remove last \0
    while (*line != ' ') {
        sum = sum + char_to_num(*line) * pow_ten(size - count);
        count++;
        line++;
    }
    return sum;
}

char *get_ls_value(char *line) {
    // line += (strstr(line, " ") - line) + 1;
    line += len(line, '\0', ' ') + 1;
    return line;
}

int len(char *line, char i, char f) {
    int count = 0;

    if (i == '\0' && f == '\0') {
        while (*line != f) {
            count++;
            line++;
        }
    } else if (i == '\0' && f != '\0') {
        while (*line != f) {
            count++;
            line++;
        }
    } else if (i != '\0' && f == '\0') {
        while (*line != i) {
            line++;
        }
        line++;
        while (*line != f) {
            count++;
            line++;
        }
    } else if (i != '\0' && f != '\0') {
        while (*line != i) {
            line++;
        }
        line++;
        while (*line != f) {
            count++;
            line++;
        }
    }

    return count;
}

void clean_line(char *line, int size) { line[size - 1] = '\0'; }

char* parse_cd(char *line) {
    line = line + len(line, '\0', ' ') + 1;
    line = line + len(line, '\0', ' ') + 1;
    return line;
}

node* new_node(char *name, int name_size, bool is_dir, int size, node *parent,
        node *child_head, node *brother){
    node *p = (node *)malloc(sizeof(node));

    p->name = (char *)malloc(sizeof(char)*name_size);
    strcpy(p->name, name);

    p->is_dir = is_dir;
    p->size = size;
    p->parent = parent;
    p->child_head = child_head;
    p->brother = brother;

    return p;
}

void insert_brother(node* child, char *name, int name_size, bool is_dir,
        int size, node *parent){
    node* temp = child;
    while(temp->brother){
        temp = temp->brother;
    }
    temp->brother = new_node(name, name_size, is_dir, size, parent, NULL, NULL);
}

node* move_to_child(node **registry_node, char *val_name){
    node *temp = (*registry_node)->child_head;
    while(temp){
        if (strcmp(temp->name, val_name) == 0){
            return temp;
        }
        temp = temp->brother;
    }
    return NULL;
}

void calculate_dir_sizes(node *root){
    /* first left then root then right */
    if (root == NULL){
        return;
    }else{
        calculate_dir_sizes(root->child_head);
        if (root->is_dir){
            node *temp = root->child_head;
            while(temp){
                root->size += temp->size;
                temp = temp->brother;
            }
        }
        calculate_dir_sizes(root->brother);
    }
}


void calculate_result_1(node *root, int* sum){
    /* first left then root then right */
    if (root == NULL){
        return;
    }else{
        calculate_result_1(root->child_head, sum);
        if (root->is_dir && root->size <= 100000){
            (*sum) +=root->size;
        }
        calculate_result_1(root->brother, sum);
    }
}

void traverse_inorder(node *root){
    /* first left then root then right */
    if (root == NULL){
        return;
    }else{
        traverse_inorder(root->child_head);
        printf("%s %i\n", root->name, root->size);
        traverse_inorder(root->brother);
    }
}

void inorder_free(node *root){
    if (root == NULL){
        return;
    }else{
        inorder_free(root->child_head);
        free(root->name);
        free(root);
        inorder_free(root->brother);
    }
}

void create_dirs_list(node *root, link_node *parent){
    if (root == NULL){
        return;
    }else{
        if (root->is_dir)
            insert_new_linked_node(parent, root->size, root->name);
        create_dirs_list(root->child_head, parent) ;
        create_dirs_list(root->brother, parent);
    }
}

link_node* new_link_node(int size, link_node* next, int name_size, char* name){
    link_node* new_node = (link_node*) malloc(sizeof(link_node));

    new_node->size = size;
    new_node->next = next;
    new_node->name = (char*) malloc(sizeof(char) * name_size);

    strcpy(new_node->name, name);

    return new_node;
}

void insert_new_linked_node(link_node* parent, int size, char *name){
    link_node *temp = parent;
    while(temp->next){
        temp = temp->next;
    }
    temp->next = new_link_node(size, NULL, len(name, '\0', '\0'), name);
}

void debug_linked_node(link_node *parent){
    link_node *temp = parent;
    while(temp){
        printf("dir: %s size: %i\n", temp->name, temp->size);
        temp = temp->next;
    }
}

void linked_node_free(link_node *parent){
    link_node* temp;
    while(parent){
        temp = parent;
        parent = parent->next;
        free(temp);
    }
}

int calculate_result_2(link_node* parent, int total_current_unused_space){
    link_node* temp = parent;
    int result = parent->size;
    while(temp){
        if(temp->size + total_current_unused_space >= total_unused_space_needed){
            if (result >= temp->size){
                result = temp->size;
            }
        }
        temp = temp->next;
    }
    return result;
}

void all_parts() {
    FILE *fptr = NULL;
    char line[1024];
    int count = 0;
    node *root = NULL;
    node *child = NULL;
    char *val_name = "";
    bool is_dir_val = false;
    node **registry_node = NULL;
    int size = 0;

    fptr = fopen(file_name, "r");

    while (fgets(line, sizeof(line), fptr)) {
        clean_line(line, len(line, '\0', '\0'));
        //printf("line: |%s|\n", line);
        if ('$' == *line) {
            if (strstr(line, "cd") != NULL) {
                val_name = parse_cd(line);
                if (strcmp("/", val_name) == 0){
                    root = new_node(val_name, len(val_name, '\0', '\0'),
                            true, 0, NULL, NULL, NULL);
                    registry_node = &root;
                }else if (strcmp("..", val_name) == 0){
                    registry_node = &((*registry_node)->parent);
                }else {
                    node *temp_child = move_to_child(registry_node, val_name);
                    registry_node = &temp_child;
                }
            } else if (strstr(line, "ls")) {
                count = 0;
                child = NULL;
            }
        } else {
            val_name = get_ls_value(line);
            is_dir_val = is_dir(line);
            size = (is_dir_val) ? 0 : get_file_size(line);
            if (count == 0) {
                child = new_node(val_name, len(val_name, '\0', '\0'), is_dir_val, size,
                        *(registry_node), NULL, NULL);
                (*registry_node)->child_head = child;
            } else {
                insert_brother(child, val_name, len(val_name, '\0', '\0'), is_dir_val,
                      size, *(registry_node));
            }
            count++;
        }
    }

    fclose(fptr);

    //printf("\ntraversing inorder\n");
    calculate_dir_sizes(root);
    // traverse_inorder(root);

    int sum = 0;
    calculate_result_1(root, &sum);
    printf("results part 1: %i\n", sum);

    int total_current_unused_space = total_disk_space - root->size;
    link_node *parent = new_link_node(root->size, NULL, len(root->name, '\0', '\0'), root->name);

    // printf("total_current_unused_space %i\n", total_current_unused_space);
    // TODO: Make an order linked list instead of normal linked list
    create_dirs_list(root, parent);
    int result = calculate_result_2(parent, total_current_unused_space);

    printf("results part 2: %i\n", result);

    // printf("debugging... linked list with directories\n");
    // debug_linked_node(parent);

    printf("cleaning memory allocated...\n");
    linked_node_free(parent);
    inorder_free(root);
}

int main() {
    all_parts();
    return 0;
}
