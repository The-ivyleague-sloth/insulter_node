#ifndef WORD_NODE
#define WORD_NODE

#include <stdint> 

typdef struct word_node{
	int8_t byte;
	word_node* next;
}word_node;

#endif
