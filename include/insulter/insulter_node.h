#ifndef PARSER_H
#define PARSER_H

#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <map>
#include <errno.h>
#include <time.h>
#include <stdint.h>
#include <algorithm> //remove if 
// #include "ros/ros.h"
// #include "std_msgs/String.h"
#include <sstream>
#include "word_node.h"
//packaging insulter node
#define INSULTS 2

class insulter {

public:
	~insulter();
	insulter();

	void initialize_insulter_map();
	void make_word_node(std::string line, std::string word);
	uint8_t get_char(std::string key);
	int16_t create_new_word_node(std::string word, int8_t val);
	void initialize_insults();
	void initialize_sentences();
	int16_t say_sentence();
	int16_t speak_word(word_node* head);
	int16_t send_uart();
	void sleep_ms(int milliseconds);
	void initialize_serial();
	void free_word(word_node* word);


private:
	// map to store char commands to speakjet
	std::map<std::string, uint8_t> das_map;
	// map to store the head of linked list for a word
	std::map<std::string, word_node*>word_map;
	// int number_of_insults;
	std::string insults[INSULTS];
	// fd to read and write to
	int16_t uart_fd;
};


#endif
