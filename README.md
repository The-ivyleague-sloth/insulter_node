![alt text](https://github.com/The-ivyleague-sloth/insulter_node/blob/master/pictures/bender.png)


# packaging insulter node
instructions for setting up a package
https://w3.cs.jmu.edu/spragunr/CS354_F17/labs/packaging/package_lab.shtml


sentences are linked lists hashmaps store the head
words are linked lists hashmasps store the head
 the bytes to send via uart are bytes sending the hashmap values to convert the strings to an int
 EH -> 232

# High Level overview
upon bootup the insulter object reads in the dictionary file to create the enunciations of words.

the stirng to char for the enunciations are stored in a map. These must be maintained and updated by the programmer. If new enunciations are found then the developer must update accordingly.

the sentences.txt file is read in and these are the sentences the insulter can speak when a message is received.

to run the user must have I/O privileges. one can access the I/O with this command
sudo usermod -a -G dialout $USER

I have disabled the bluetooth module to access the UART I/O 
the /boot/config.txt file has the highlighted dtoverlay line added.
this diables the bluetooth device allowing for gpio UART access.

Enable audio (loads snd_bcm2835)
#dtoverlay=pi3-disable-bt
dtparam=audio=on
start_x=1
gpu_mem=128
enable_uart=1

# to make
 add the node into an existing catkin_ws/src space then run catkin_make from catkin_ws dir.
 this should build the node. you then can run the node and one insult will be generated. Other insults are generated when a callback is registered. To register callbacks one can use the "monitor node" found on my github. This node publishes messages that the insulter is subscribing to.

# sentences.txt
 This file is where you can add your new insults the node will read this file on boot up. 
 
# PhraseALator.Dic
This file is where all the words are stored and how to enunciate them. to add a new word simply put the name of the word followed by an "=" and then a string of known enunucaiations. If there are any mistakes in the enunciations then the node will throw an assertion.
