#ifndef NODE_H
#define NODE_H

typedef enum {
    PROGRAM
} NODE_TYPE;

typedef struct {
    NODE_TYPE type;
    void* left;
    void* right;
} node_t;

node_t* create_node(NODE_TYPE, void*, void*);

char* node_to_string(node_t*);

#endif