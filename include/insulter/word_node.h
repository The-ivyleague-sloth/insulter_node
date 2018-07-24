#ifndef WORD_NODE
#define WORD_NODE

#include <stdint.h> 

typedef struct word_node_struct{
	uint8_t byte;
	word_node_struct* next;
}word_node;

#endif
