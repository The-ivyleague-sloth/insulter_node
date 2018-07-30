# packaging insulter node
instructions for setting up a package
https://w3.cs.jmu.edu/spragunr/CS354_F17/labs/packaging/package_lab.shtml

parse the dictionary file
hashmap returns pointer to head of word
iterate through the list of enunciation bytes which are all stored in a map as well

sentences are linked lists hashmaps store the head
words are linked lists hashmasps store the head
 the bytes to send via uart are bytes sending the hashmap values to convert the strings to an int
 EH -> 232

#High Level overview
upon bootup the insulter object reads in the dictionary file to create the enunciations of words
the sentences.txt file is read in and these are the sentences the insulter can speak when a message is received.

to run the user must have I/O privileges. one can access the I/O with this command
sudo usermod -a -G dialout $USER

I have disabled the bluetooth module to access the UART I/O 
the /boot/config.txt file has this line added.

# Enable audio (loads snd_bcm2835)
dtoverlay=pi3-disable-bt
dtparam=audio=on
start_x=1
gpu_mem=128
enable_uart=1

