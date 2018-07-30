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
#include <vector>
#include <errno.h>
#include <time.h>
#include <stdint.h>
#include <algorithm> //remove if 
#include <sstream>
#include "word_node.h"


class insulter {

public:
	// destructor
	~insulter();
	//constructor
	insulter();

	/******************************************************************************/
	/** \brief Initalializes the insulter map. Ths map is a string to char map 
	*	the values assigned and derived are from the speakjet datasheet found below
	*	https://www.sparkfun.com/datasheets/Components/General/speakjet-usermanual.pdf
	*	
	*   \par Assumptions, External Events, and Notes:
	*
	*   \param[in,out] None
	*
	*   \returns None
	*****************************************************************************/
	void initialize_insulter_map();
	/******************************************************************************/
	/** \brief this function takes in a line like \SE\KE\OHIH\FAST\IH and a word like sky
	*	to create a linked list of bytes we transform the line to all uppercase and get the correspoonding string to byte mapping
	* 	\SE\ -> SE -> 187
	*	
	*   \par Assumptions, External Events, and Notes:
	*
	*   \param[in] string line is a string representing how to enunciate a word string word is the word
	*
	*   \returns None
	*****************************************************************************/
	void make_word_node(std::string line, std::string word);
	/******************************************************************************/
	/** \brief this function takes in a single enunciation like "KE" and returns the mapped value
	* for values like "3" we convert the string to an int and return that value. for values not 
	* an int representation or in the map we throw an assertion.
	*	
	*   \par Assumptions, External Events, and Notes:
	*
	*   \param[in] string key is he enunciation like "KE"
	*
	*   \returns the byte value from the map
	*****************************************************************************/
	uint8_t get_char(std::string key);
	/******************************************************************************/
	/** \brief this function takes in a word and char value. the word is used to retrieve the 
	*	head of the linked list from the map. We then malloc for a new word node,store the value passed in as the byte representation
	*	and place the newly created node at the end of the word linked list
	*	
	*   \par Assumptions, External Events, and Notes:
	*
	*   \param[in] string word is a word like "sky" val is the value to store in the list
	*
	*   \returns 0 or - 1 failure
	*****************************************************************************/
	int16_t create_new_word_node(std::string word, int8_t val);
	/******************************************************************************/
	/** \brief this function reads from the phrase a lator file transforms and parses the
	*	lines into words and enunciations for following functions to store
	*	
	*   \par Assumptions, External Events, and Notes:
	*
	*   \param[in] 
	*
	*   \returns none
	*****************************************************************************/
	void initialize_insults();
	/******************************************************************************/
	/** \brief this function reads from the sentences txt file and stores the phrase in an array
	* 	for later processing
	*	
	*   \par Assumptions, External Events, and Notes:
	*
	*   \param[in] 
	*
	*   \returns none
	*****************************************************************************/
	void initialize_sentences();
	/******************************************************************************/
	/** \brief this function chooses a random insult from the array created by the sentences txt file
	* 	it then parses the words from the string. each word is mapped to the head of the linked list which is processed out via serual.
	*	
	*   \par Assumptions, External Events, and Notes:
	*
	*   \param[in] 
	*
	*   \returns none
	*****************************************************************************/
	int16_t say_sentence();
	/******************************************************************************/
	/** \brief this function takes the head of a word node list and iterates through the list
	* 	transmitting the enunciations byte by byte as well as monitor the ready pin on the speakjet
	*	
	*   \par Assumptions, External Events, and Notes:
	*
	*   \param[in] pointer to the head of a list
	*
	*   \returns none
	*****************************************************************************/
	int16_t speak_word(word_node* head);
	/******************************************************************************/
	/** \brief this function initializes the gpio uart serial pins on the rpi3 and zero
	*	
	*   \par Assumptions, External Events, and Notes:
	*	assuming that bluetooth is disabled
	*
	*   \param[in] none
	*
	*   \returns none
	*****************************************************************************/
	void initialize_serial();
	/******************************************************************************/
	/** \brief this function frees the linked list word that was created from the dictionary file
	*	
	*   \par Assumptions, External Events, and Notes:
	*
	*   \param[in] pointer to head of word node list
	*
	*   \returns none
	*****************************************************************************/
	void free_word(word_node* word);
	/******************************************************************************/
	/** \brief this function tests the serial communication by transmitting the receiving the bytes
	*	
	*   \par Assumptions, External Events, and Notes:
	*	UART tx and RX are connected in loopback manner
	*   \param[in] pointer to head of word node list
	*
	*   \returns none
	*****************************************************************************/
	void test_serial();


private:
	// map to store char commands to speakjet
	std::map<std::string, uint8_t> das_map;
	// map to store the head of linked list for a word
	std::map<std::string, word_node*>word_map;
	// int number_of_insults;
	std::vector<std::string> insults;
	// fd to write serial output to the speakjet to
	int16_t uart_fd;
};


#endif
