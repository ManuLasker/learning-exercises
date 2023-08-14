#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int len(char *line, char i, char f);


typedef struct node {
    bool is_dir;
    int size;
    char *name;
    struct node *parent;
    struct node *child_head;
    struct node *brother;
} node;

const static char *file_name = "test_data.txt";
node** history_node;
// const static char *file_name = "data.txt";

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

    printf("node creation: %s\n", p->name);
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

void part_1() {
    FILE *fptr = NULL;
    char line[1024];
    int i = 0;
    int count = 0;
    node* root;
    node* child;
    char *val_name = "";
    bool is_dir_val;
    int size;

    fptr = fopen(file_name, "r");

    while (fgets(line, sizeof(line), fptr)) {
        printf("line: %s", line);
        clean_line(line, len(line, '\0', '\0'));

        if ('$' == *line) {
            // TODO: need to parse an action
            //"$ cd dir"
            //"$ ls"
            if (count != 0 && *history_node && child){
                node* temp = *history_node;
                temp->child_head = child;
                break;
            }

            if (strstr(line, "cd")) {
                val_name = parse_cd(line);
                if (val_name[0] == '/'){
                    printf("root: %s\n", val_name);
                    root = new_node(val_name, strlen(val_name),
                            true, 0, NULL, NULL, NULL);
                    history_node = &root;
                }else if (strcmp("..", val_name)){
                    //history_node = &root;
                }else {
                    //history_node -> some parent node
                }
            } else if (strstr(line, "ls")) {
                count = 0;
                child = NULL;
            }
        } else {
            // TODO: need to parse values contents
            // 12312321 a.txt
            // dir b
            val_name = get_ls_value(line);
            is_dir_val = is_dir(line);
            size = (is_dir_val) ? 0 : get_file_size(line);
            if (count == 0) {
                // TODO: create parent
                child = new_node(val_name, strlen(val_name), is_dir_val, size,
                        *history_node, NULL, NULL);
            } else {
                // TODO: add to the parent
                insert_brother(child, val_name, strlen(val_name), is_dir_val,
                        size, *history_node);
            }
            count++;
        }

    }

}

int main() {
    part_1();
    return 0;
}
