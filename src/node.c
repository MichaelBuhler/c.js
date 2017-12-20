#include <stdlib.h>
#include <string.h>
#include "node.h"

node_t* create_node(NODE_TYPE type, void* left, void* right) {
    node_t* node_ptr = (node_t*) malloc(sizeof(node_t));
    node_ptr->type = type;
    node_ptr->left = left;
    node_ptr->right = right;
    return node_ptr;
}

char* node_to_string(node_t* node_ptr) {
    char* char_ptr;
    switch (node_ptr->type) {
        case PROGRAM:
            char_ptr = (char *) calloc(8, sizeof(char));
            strcpy(char_ptr, "Program");
            return char_ptr;
    }
}