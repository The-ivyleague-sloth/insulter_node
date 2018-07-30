#include "insulter/insulter_node.h"
#include <assert.h>
#include <wiringPi.h> // Include WiringPi library!

#define DEBUG1

//https://learn.sparkfun.com/tutorials/raspberry-gpio/c-wiringpi-setup
// uint8_t check_pin(int8_t pin)
// {
// 	if (digitalRead(pin)) // sensor tripped
// 	{
// 		return 1;
// 	}
// 	else
// 		return 0;
// }

//empty constructor
insulter::insulter()
{



}

//empty destructor
insulter::~insulter(){
	//std::cout << "entering destructor: " << std::endl;
	std::map<std::string, word_node*>::iterator it;

	for (it=word_map.begin(); it!=word_map.end(); ++it)
	{
	//	std::cout << "freeing: " << it->first << std::endl;
		free_word(it->second);
	}

}

void insulter::free_word(word_node* head)
{
	word_node* temp;

	if(head == NULL)
	{
		std::cout << "nothing to free " << std::endl;
		assert(head == NULL);
	} 

	temp = head;

	while(head != NULL)
	{
		head = head->next;
		free(temp);
		temp = head;
	}

}


void insulter::sleep_ms(int milliseconds) // cross-platform sleep function
{
// #elif _POSIX_C_SOURCE >= 199309L
	struct timespec ts;
	ts.tv_sec = milliseconds / 1000;
	ts.tv_nsec = (milliseconds % 1000) * 1000000;
	nanosleep(&ts, NULL);
// #else
	// usleep(milliseconds * 1000);
// #endif
}

uint32_t check_pin(uint32_t pin)
{
	return digitalRead(pin);
}

/*
* iterates through the linked list of bytes and transmits commands via uart to the speakjet
*/
int16_t insulter::speak_word(word_node* head)
{

	word_node* temp = head;
	while (temp != NULL) {
		// check to see if the speakjet is ready
		while(!check_pin(0)); //wait for rdy signal
		// write a byte to uart lines.

		write(uart_fd, &temp->byte, 1);
#ifdef DEBUG1
		printf("processing through UART %d\n",temp->byte);
#endif
		temp = temp->next;
//	sleep_ms(200);
		//check gpio pin
	}


}

/*
* gets a string sentence and breaks the sentence down into words to enunciate
*/
int16_t insulter::say_sentence()
{
	//get random number based off of size
	// int ind = rand() % INSULTS;
	int pos;
	// std::string end_pos;
	std::string space = " ";
	std::string word;
	word_node* head = NULL;

	std::string insult;
	// get a random insult from our insult table

	// srand(time(NULL));   // should only be called once

	insult = insults[(rand()%4)];
#ifdef DEBUG1
		std::cout << "insult generated: " << insult << std::endl;
#endif

	// string should be like 'you suck' so we parse by space
	while ((pos = insult.find(space)) != std::string::npos)
	{
		// end_pos = line.find(space,1);
		//get our character string to look up in the map
		word = insult.substr(0, pos);
		// get rid of the character to iterate
		insult.erase(0, pos + space.length());

#ifdef DEBUG1
		std::cout << "word about to speak: " << word << std::endl;
#endif
		// look up in map and get the value
		head = word_map[word];
		// send the head of the list to iterate through and output hte bytes
		speak_word(head);
	}
	// after parsing we still need to say the last word
#ifdef DEBUG1
		std::cout << "last word about to speak: " << insult << std::endl;
#endif
		// look up in map and get the value
		head = word_map[insult];
		// send the head of the list to iterate through and output hte bytes
		speak_word(head);

}

// create a new word node if head is null add to front else iterate through and add to tail
int16_t insulter::create_new_word_node(std::string word, int8_t val) {
	word_node* head;
	// get the head of our linked list
	head = word_map[word];

	word_node* new_word_node = (word_node*) malloc (sizeof(word_node));
	if (new_word_node == NULL) { // == -1
		/* return -1 if malloc fails */
		perror("error, malloc for new word node node struct failed");
		return -1;
	}

	// set unique values
	new_word_node->byte = val;
	new_word_node->next = NULL;

	if ((head) == NULL)
	{
		/* if head == NULL, node created is the new head of the list! */
		//head = new_word_node;
		word_map[word] = new_word_node;
	}
	else
	{
		/* otherwise, traverse linked list until we reach the end */
		word_node* current = head;


		while (current->next != NULL)
		{
			current = current->next;
		}
		/* add node to the end of list */
		current->next = new_word_node;
	}
	return 0;
}

// take in a line from the file parse command by command and form our linked list
void insulter::make_word_node(std::string line, std::string word) {

	int16_t start_pos;
	int16_t end_pos;
	std::string token = "/";
	std::string ws = " ";
	std::string character;
	uint8_t val;

	// string should be here \SE\KE\OHIH\FAST\IH find the first \ and last \ and gather
	while ((start_pos = line.find(token)) != std::string::npos)
	{
		end_pos = line.find(token, 1);
		//get our character string to look up in the map
		character = line.substr(start_pos + token.length(), end_pos - token.length());
		// get rid of the character to iterate
		line.erase(start_pos, end_pos);

#ifdef DEBUG 
		std::cout << "character string parsed:" << character << std::endl;
#endif
		// convert to upper case if not already
		std::transform(character.begin(), character.end(),character.begin(), ::toupper);
		// look up in map and get the value
		val = get_char(character);

#ifdef DEBUG 
		// using cout causes for wrong output on terminal
		printf("byte from map:%d\n",val);
#endif
		// create a new node in the linkedlist
		create_new_word_node(word, val);
	}

}

//read in a dictionary file parse it and create a linked list of bytes to send over uart
void insulter::initialize_insults()
{

	int16_t pos;
	std::ifstream config_file;
	std::string file_line;
	// this needs to be custom until I can learn cmake or make or something or be smart...
	std::string file = "/home/pi/BullyBot/catkin_ws/src/insulter_node/src/PhraseALator.Dic";
	// std::string file = "/home/ivyleaguesloth/BullyBot/catkin_ws/src/insulter/src/PhraseALator.Dic";
	std::string word;
	std::string word_delim = "=";
	// open the file as input only
	config_file.open(file.c_str(), std::ios::in);
	// check if open
	if (config_file.is_open())
	{
		// read line by line
		while (getline(config_file, file_line))
		{
			//typical line looks like sky = \SE \KE \OHIH \FAST \IH
			// remove all the white spaces from the line of the file
			file_line.erase(remove_if(file_line.begin(), file_line.end(), isspace), file_line.end());
			pos = file_line.find(word_delim);

#ifdef DEBUG
			std::cout << "after removing spaces: " << file_line << std::endl;
#endif

			// line should look like this now 'sky=\SE\KE\OHIH\FAST\IH' extract the word
			if (pos != std::string::npos)
			{
				//extract the word like 'sky'
				word = file_line.substr(0, pos);
				// after erasing \SE\KE\OHIH\FAST\IH
				file_line.erase(0, pos + word_delim.length());
				// create a null head
				word_node* head = NULL;
				// store the head of our pointer in a map
				word_map[word] = head;
#ifdef DEBUG
			std::cout << "word extracted: " << word << std::endl;
#endif

				make_word_node(file_line, word);
			}
			else
			{
				std::cout << "line formatted incorrectly: " << file_line << std::endl;
			}
		}
	}
	else
	{
		printf("error opening file\n");
	}
}

bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

uint8_t insulter::get_char(std::string key)
{
	//now we want to retrieve information...
	uint8_t rval;
	if(das_map.find(key) != das_map.end())
	{
    	//display information
    	//std::cout << "entry found in map: " << das_map[key] << std::endl;
    	
    	rval = das_map[key];
    	//std::cout << "entry found in map: " << rval << std::endl;

    	return rval;
	}	
	else
	{
		if(is_number(key))
		{
			//std::cout << "entry is a number converting! " << key << std::endl;
			return atoi(key.c_str());
		}
		else
		{
			std::cout << "entry not found in map: " << key << std::endl;
			assert(das_map.find(key) != das_map.end());
			return -1;
		}
	}
	
}

/*
* read from the sentence file and store the lines in the inult array
*/
void insulter::initialize_sentences()
{

	uint8_t i;
	std::ifstream config_file;
	std::string file_line;
	std::string file = "/home/pi/BullyBot/catkin_ws/src/insulter_node/src/Sentences.txt";
	// std::string file = "/home/ivyleaguesloth/BullyBot/catkin_ws/src/insulter/src/Sentences.txt";
	std::string word;
	// open the file as input only
	config_file.open(file.c_str(), std::ios::in);
	// check if open
	if (config_file.is_open())
	{
		// read line by line and store the line read into a string array
		while (getline(config_file, file_line))
		{
			insults[i] = file_line;
#ifdef DEBUG
			std::cout << "insult stored: " << file_line << std::endl;
#endif
			i++;
		}
	}
	else
	{
		printf("error opening sentence.txt file\n");
	}
}


/*
* this map converts a string to a char value to send over UART
* each string is a known voice or command provided by the speakjet data sheet
* https://www.sparkfun.com/datasheets/Components/General/speakjet-usermanual.pdf
*/
void insulter::initialize_insulter_map()
{
	das_map["IY"]    = 128;                   ///< 70ms Voiced Long Vowel
	das_map["IH"]    = 129;                   ///< 70ms Voiced Long Vowel
	das_map["EY"]    = 130;                   ///< 70ms Voiced Long Vowel
	das_map["EH"]    = 131 ;                  ///< 70ms Voiced Long Vowel
	das_map["AY"]    = 132;                   ///< 70ms Voiced Long Vowel
	das_map["AX"]    = 133;                   ///< 70ms Voiced Long Vowel
	das_map["UX"]    = 134;                   ///< 70ms Voiced Long Vowel
	das_map["OH"]    = 135;                   ///< 70ms Voiced Long Vowel
	das_map["AW"]    = 136;                   ///< 70ms Voiced Long Vowel
	das_map["OW"]    = 137;                   ///< 70ms Voiced Long Vowel
	das_map["UH"]   = 138;                   ///< 70ms Voiced Long Vowel
	das_map["UW"]   = 139;					 ///< 70ms Voiced Long Vowel
	das_map["MM"]   = 140;                   ///< 70ms Voiced Nasal
	das_map["NE"]   = 141;                   ///< 70ms Voiced Nasal
	das_map["NO"]   = 142;                   ///< 70ms Voiced Nasal
	das_map["NGE"]  = 143;                   ///< 70ms Voiced Nasal
	das_map["NGO"]  = 144;                   ///< 70ms Voiced Nasal
	das_map["LE"]  = 145;                   ///< 70ms Voiced Resonate
	das_map["LO"]   = 146;                   ///< 70ms Voiced Resonate
	das_map["WW"]   = 147;                   ///< 70ms Voiced Resonate
	das_map["RR"]   = 149;                   ///< 70ms Voiced Resonate
	das_map["IYRR"]  = 149;                   ///< 200ms Voiced R Color Vowel
	das_map["EYRR"]  = 150;                   ///< 200ms Voiced R Color Vowel
	das_map["AXRR"]  = 151;                   ///< 190ms Voiced R Color Vowel
	das_map["AWRR"]  = 152;                   ///< 200ms Voiced R Color Vowel
	das_map["OWRR"]  = 153;                   ///< 185ms Voiced R Color Vowel
	das_map["EYIY"]  = 154;                   ///< 165ms Voiced Diphthong
	das_map["OHIY"]  = 155;                   ///< 200ms Voiced Diphthong
	das_map["OWIY"]  = 156;                   ///< 225ms Voiced Diphthong
	das_map["OHIH"]  = 157;                   ///< 170ms Voiced Diphthong
	das_map["IYEH"]  = 158;                   ///< 140ms Voiced Diphthong
	das_map["EHLE"]  = 159;                   ///< 140ms Voiced Diphthong
	das_map["IYUW"]  = 160;                   ///< 180ms Voiced Diphthong
	das_map["AXUW"]  = 161;                   ///< 170ms Voiced Diphthong
	das_map["IHWW"]  = 162;                   ///< 170ms Voiced Diphthong
	das_map["AYWW"]  = 163;                   ///< 200ms Voiced Diphthong
	das_map["OWWW"]  = 164;                   ///< 131ms Voiced Diphthong
	das_map["JH"]    = 165;                   ///< 70ms Voiced Affricate
	das_map["VV"]    = 166;                   ///< 70ms Voiced Fricative
	das_map["ZZ"]    = 167;                   ///< 70ms Voiced Fricative
	das_map["ZH"]    = 168;                   ///< 70ms Voiced Fricative
	das_map["DH"]    = 169;                   ///< 70ms Voiced Fricative
	das_map["BE"]    = 170;                   ///< 45ms Voiced Stop
	das_map["BO"]    = 171;                   ///< 45ms Voiced Stop
	das_map["EB"]    = 172;                   ///< 10ms Voiced Stop
	das_map["OB"]    = 173;                   ///< 10ms Voiced Stop
	das_map["DE"]    = 174;                   ///< 45ms Voiced Stop
	das_map["DO"]    = 174;                   ///< 45ms Voiced Stop
	das_map["ED"]    = 176;                   ///< 10ms Voiced Stop
	das_map["OD"]    = 177;                   ///< 10ms Voiced Stop
	das_map["GE"]    = 178;                   ///< 55ms Voiced Stop
	das_map["GO"]    = 179;                   ///< 55ms Voiced Stop
	das_map["EG"]    = 180;                   ///< 55ms Voiced Stop
	das_map["OG"]    = 181;                   ///< 55ms Voiced Stop
	das_map["CH"]   = 182;                   ///< 70ms Voiceless Affricate
	das_map["HE"]   = 183;                   ///< 70ms Voiceless Fricative
	das_map["HO"]   = 184;                   ///< 70ms Voiceless Fricative
	das_map["WH"]   = 185;                   ///< 70ms Voiceless Fricative
	das_map["FF"]   = 186;                   ///< 70ms Voiceless Fricative
	das_map["SE"]   = 187;                   ///< 40ms Voiceless Fricative
	das_map["SO"]   = 188;                   ///< 40ms Voiceless Fricative
	das_map["SH"]   = 189;                   ///< 50ms Voiceless Fricative
	das_map["TH"]    = 190;                   ///< 40ms Voiceless Fricative
	das_map["TT"]    = 191 ;                  ///< 50ms Voiceless Stop
	das_map["TU"]    = 192;                   ///< 70ms Voiceless Stop
	das_map["TS"]    = 193;                   ///< 170ms Voiceless Stop
	das_map["KE"]    = 194;                   ///< 55ms Voiceless Stop
	das_map["KO"]    = 195;                   ///< 55ms Voiceless Stop
	das_map["EK"]    = 196;                   ///< 55ms Voiceless Stop
	das_map["OK"]    = 197;                   ///< 45ms Voiceless Stop
	das_map["PE"]    = 198;                   ///< 99ms Voiceless Stop
	das_map["PO"]    = 199  ;                 ///< 99ms Voiceless Stop
	// Robot sound
	das_map["R0"]      = 200;                   ///< 80ms Robot
	das_map["R1"]      = 201;                   ///< 80ms Robot
	das_map["R2"]      = 202;                   ///< 80ms Robot
	das_map["R3"]      = 203;                   ///< 80ms Robot
	das_map["R4"]      = 204;                   ///< 80ms Robot
	das_map["R5"]      = 205;                   ///< 80ms Robot
	das_map["R6"]      = 206;                   ///< 80ms Robot
	das_map["R7"]      = 207;                   ///< 80ms Robot
	das_map["R8"]      = 208;                   ///< 80ms Robot
	das_map["R9"]      = 209;                   ///< 80ms Robot
	// Alarm sound
	das_map["A0"]      = 210;                   ///< 300ms Alarm
	das_map["A1"]      = 211;                   ///< 101ms Alarm
	das_map["A2"]      = 212;                   ///< 102ms Alarm
	das_map["A3"]      = 213;                   ///< 540ms Alarm
	das_map["A4"]      = 214;                   ///< 530ms Alarm
	das_map["A5"]      = 215;                   ///< 500ms Alarm
	das_map["A6"]      = 216;                   ///< 135ms Alarm
	das_map["A7"]      = 217;                   ///< 600ms Alarm
	das_map["A8"]      = 218;                   ///< 300ms Alarm
	das_map["A9"]      = 219;                   ///< 250ms Alarm
	// Beeps
	das_map["B0"]      = 220;                   ///< 200ms Beep
	das_map["B1"]      = 221;                   ///< 270ms Beep
	das_map["B2"]      = 222;                   ///< 280ms Beep
	das_map["B3"]      = 223;                   ///< 260ms Beep
	das_map["B4"]      = 224;                   ///< 300ms Beep
	das_map["B5"]      = 225;                   ///< 100ms Beep
	das_map["B6"]      = 226;                   ///< 104ms Beep
	das_map["B7"]      = 227;                   ///< 100ms Beep
	das_map["B8"]      = 228;                   ///< 270ms Beep
	das_map["B9"]      = 229;                   ///< 262ms Beep
	// Biological
	das_map["C0"]      = 230;                   ///< 160ms Biological
	das_map["C1"]      = 231;                   ///< 300ms Biological
	das_map["C2"]      = 232;                   ///< 182ms Biological
	das_map["C3"]      = 233;                   ///< 120ms Biological
	das_map["C4"]      = 234;                   ///< 175ms Biological
	das_map["C5"]      = 235;                   ///< 350ms Biological
	das_map["C6"]      = 236;                   ///< 160ms Biological
	das_map["C7"]      = 237;                   ///< 260ms Biological
	das_map["C8"]      = 238;                   ///< 95ms Biological
	das_map["C9"]      = 239;                   ///< 75ms Biological
	// DTMF
	das_map["D0"]        = 240;                   ///< DTMF 0 95ms
	das_map["D1"]        = 241;                   ///< DTMF 1 95ms
	das_map["D2"]        = 242;                   ///< DTMF 2 95ms
	das_map["D3"]        = 243;                   ///< DTMF 3 95ms
	das_map["D4"]        = 244;                   ///< DTMF 4 95ms
	das_map["D5"]        = 245;                   ///< DTMF 5 95ms
	das_map["D6"]        = 246;                   ///< DTMF 6 95ms
	das_map["D8"]        = 248;                   ///< DTMF 8 95ms
	das_map["D9"]        = 249;                   ///< DTMF 9 95ms
	das_map["DTMF_STAR"]     = 250;                   ///< DTMF * 95ms
	das_map["DTMF_HASH"]     = 251;                   ///< DTMF # 95ms
	// Miscellaneous
	das_map["M0"]      = 252;                   ///< Sonar ping 125ms
	das_map["M1"]      = 253;                   ///< Pistol shot 250ms
	das_map["M2"] = 254; ///< WOW 530ms
	// command codes upper
	das_map["P0"]        = 0;                     ///< Pause 0ms
	das_map["P1"]        = 1;                     ///< Pause 100ms
	das_map["P2"]        = 2;                     ///< Pause 200ms
	das_map["P3"]        = 3;                     ///< Pause 700ms
	das_map["P4"]        = 4;                     ///< Pause 30ms
	das_map["P5"]        = 5;                     ///< Pause 60ms
	das_map["P6"]        = 6;                     ///< Pause 90ms
	das_map["FAST"]         = 7;                     ///< Next phoneme at 0.5 speed
	das_map["SLOW"]         = 8;                     ///< Next phoneme at 1.5 speed
	das_map["STRESS"]       = 14;                    ///< Next phoneme with some stress
	das_map["RELAX"]        = 15;                    ///< Next phoneme with relaxation
	das_map["WAIT"]         = 16;                    ///< Stops and waits for a Start (see manual)
	das_map["SOFT"]          = 18;                    ///< Stops and waits for a Start (see manual)
	das_map["VOLUME"]        = 20;                    ///< Next octet is volume 0 to 127. Default 96
	das_map["SPEED"]         = 21;                    ///< Next octet is speed 0 to 127. Default 114
	das_map["PITCH"]         = 22;                    ///< Next octet is pitch in Hz = to 255
	das_map["BEND"]         = 23;                    ///< Next octet is frequency bend  to 15. Default is 5
	das_map["PORTCTR"]       = 24;                    ///< Next octet is port control value. See manual. Default is 7
	das_map["PORT"]          = 25;                    ///< Next octet is Port Output Value. See manual. Default is 0
	das_map["REPEAT"]        = 26;                    ///< Next octet is repeat count. 0 to 255
	das_map["CALLPHRASE"]    = 28;                    ///< Next octet is EEPROM phrase to play and return. See manual.
	das_map["GOTOPHRASE"]    = 29;                    ///< Next octet is EEPROM phgrase to go to. See manual.
	das_map["DEKAY"]         = 30;                    ///< Next octet is delay in multiples of 10ms. 0 to 255.
	das_map["RESET"] = 31; ///< Reset Volume Speed, Pitch, Bend to defaults.
	
// 	// needed for some assertions
// 	das_map["3"] = 3;
// 	das_map["4"] = 4;
// 	das_map["120"] = 120;
// das_map["10"] = 10;
// das_map["114"] = 3;
// das_map["3"] = 3;
// das_map["3"] = 3;

}


void insulter::initialize_serial() {
	uart_fd = -1;
	uart_fd = open("/dev/ttyAMA0", O_RDWR | O_NOCTTY );
	if (uart_fd == -1) {
		printf ("Error no is : %d\n", errno);
		printf("Error description is : %s\n", strerror(errno));
		//return (-1);
	}

	// set serial fd to 8n1 9600
	struct termios options;
	tcgetattr(uart_fd, &options);
	cfsetspeed(&options, B9600);

	options.c_cflag &= ~CSTOPB;
	options.c_cflag |= CLOCAL;
	options.c_cflag |= CREAD;

	cfmakeraw(&options);
	tcsetattr(uart_fd, TCSANOW, &options);
}

void insulter::test_serial()
{
//----- TX BYTES -----
	unsigned char tx_buffer[20];
	unsigned char *p_tx_buffer;
	int count = -1;
	p_tx_buffer = &tx_buffer[0];
	*p_tx_buffer++ = 'H';
	*p_tx_buffer++ = 'e';
	*p_tx_buffer++ = 'l';
	*p_tx_buffer++ = 'l';
	*p_tx_buffer++ = 'o';
	
	//if (uart_fd != -1)
	//{
		count = write(uart_fd, &tx_buffer[0], 5);		//Filestream, bytes to write, number of bytes to write
		if (count < 0)
		{
			printf("UART TX error\n");
		}
	// }
		printf("UART write %d\n",count);
		perror("uart write");

	//----- CHECK FOR ANY RX BYTES -----
	//if (uart_fd != -1)
	//{
		// Read up to 255 characters from the port if they are there
		unsigned char rx_buffer[256];
		int rx_length = read(uart_fd, &rx_buffer[0], 255);		//Filestream, buffer to store in, number of bytes to read (max)
		if (rx_length < 0)
		{
			//An error occured (will occur if there are no bytes)
			perror("uart read");
		}
		else if (rx_length == 0)
		{
			//No data waiting
			perror("uart == 0");
		}
		else
		{
			//Bytes received
			rx_buffer[rx_length] = '\0';
			printf("%i bytes read : %s\n", rx_length, rx_buffer);
		}
	//}
	close(uart_fd);
}
