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
#include <stdint>
// #include "ros/ros.h"
// #include "std_msgs/String.h"
#include <sstream>
#include "word_node.h"

#define INSULTS 2

class insulter {

public:
	~insulter();
	void initialize_insulter_map();
	void make_word_node();
	int8_t get_char();
	int16_t create_new_word_node(std::string word, char val);
	void initialize_insults();
	void initialize_sentences();
	int16_t say_sentences();
	int16_t speak_word();
	int16_t send_uart();
	void sleep_ms(int milliseconds);


private:
	// map to store char commands to speakjet
	std::map<std::string, int8_t> das_map;
	// map to store the head of linked list for a word
	std::map<std::string, word_node*>word_map;
	// int number_of_insults;
	std::string insults[INSULTS];
	// fd to read and write to
	int16_t uart_fd;
}


#endif
