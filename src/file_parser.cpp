#include "insulter/file_parser.h"

// void initialize_insults(){
//
//   std::ifstream config_file;
//   std::string file_info;
//   std::string file = "~/BullyBot/catkin_ws/src/insulter/src/PhraseALator.Dic";
//   // open the file as input only
// 	config_file.open(file.c_str(), std::ios::in);// | std::ios:: binary);// | ios::ate);
// 			if(config_file.is_open()){
//         // read line by line
//         while(getline(config_file,file_info)){
// 					std::cout << file_info << std::endl;
//         }
// 			}
//       else{
//         printf("error opening file\n");
//       }
// }

void initialize_map()
{
 std::map<std::string, int> das_map;

 // das_map["FAST"] = FAST;
    das_map["IY"]    = 128                   ///< 70ms Voiced Long Vowel
	das_map["IH"]    = 129                   ///< 70ms Voiced Long Vowel
    das_map["EY"]    = 130                   ///< 70ms Voiced Long Vowel
	das_map["EH"]    = 131                   ///< 70ms Voiced Long Vowel
	das_map["AY"]    = 132                   ///< 70ms Voiced Long Vowel
	das_map["AX"]    = 133                   ///< 70ms Voiced Long Vowel
	das_map["UX"]    = 134                   ///< 70ms Voiced Long Vowel
	das_map["OH"]    = 135                   ///< 70ms Voiced Long Vowel
	das_map["AW"]    = 136                   ///< 70ms Voiced Long Vowel
	das_map["OW"]    = 137                   ///< 70ms Voiced Long Vowel
	das_map["UH"]   = 138                   ///< 70ms Voiced Long Vowel
	das_map["UW"]   = 139                   ///< 70ms Voiced Long Vowel
	das_map["MM"]   = 140                   ///< 70ms Voiced Nasal
	das_map["NE"]   = 141                   ///< 70ms Voiced Nasal
	das_map["NO"]   = 142                   ///< 70ms Voiced Nasal
	das_map["NGE"]  = 143                   ///< 70ms Voiced Nasal
	das_map["NGO"]  = 144                   ///< 70ms Voiced Nasal
	das_map["LE"]  = 145                   ///< 70ms Voiced Resonate
	das_map["LO"]   = 146                   ///< 70ms Voiced Resonate
	das_map["WW"]   = 147                   ///< 70ms Voiced Resonate
	das_map["RR"]   = 149                   ///< 70ms Voiced Resonate
	das_map["IYRR"]  = 149                   ///< 200ms Voiced R Color Vowel
	das_map["EYRR"]  = 150                   ///< 200ms Voiced R Color Vowel
	das_map["AXRR"]  = 151                   ///< 190ms Voiced R Color Vowel
	das_map["AWRR"]  = 152                   ///< 200ms Voiced R Color Vowel
	das_map["OWRR"]  = 153                   ///< 185ms Voiced R Color Vowel
	das_map["EYIY"]  = 154                   ///< 165ms Voiced Diphthong
	das_map["OHIY"]  = 155                   ///< 200ms Voiced Diphthong
	das_map["OWIY"]  = 156                   ///< 225ms Voiced Diphthong
	das_map["OHIH"]  = 158                   ///< 170ms Voiced Diphthong
	das_map["EHLE"]  = 159                   ///< 140ms Voiced Diphthong
	das_map["IYUW"]  = 160                   ///< 180ms Voiced Diphthong
	das_map["AXUW"]  = 161                   ///< 170ms Voiced Diphthong
	das_map["IHWW"]  = 162                   ///< 170ms Voiced Diphthong
	das_map["AYWW"]  = 163                   ///< 200ms Voiced Diphthong
	das_map["OWWW"]  = 164                   ///< 131ms Voiced Diphthong
	das_map["JH"]    = 165                   ///< 70ms Voiced Affricate
	das_map["VV"]    = 166                   ///< 70ms Voiced Fricative
	das_map["ZZ"]    = 167                   ///< 70ms Voiced Fricative
	das_map["ZH"]    = 168                   ///< 70ms Voiced Fricative
	das_map["DH"]    = 169                   ///< 70ms Voiced Fricative
	das_map["BE"]    = 170                   ///< 45ms Voiced Stop
	das_map["BO"]    = 171                   ///< 45ms Voiced Stop
	das_map["EB"]    = 172                   ///< 10ms Voiced Stop
	das_map["OB"]    = 173                   ///< 10ms Voiced Stop
	das_map["DE"]    = 174                   ///< 45ms Voiced Stop
	das_map["DO"]    = 174                   ///< 45ms Voiced Stop
	das_map["ED"]    = 176                   ///< 10ms Voiced Stop
	das_map["OD"]    = 177                   ///< 10ms Voiced Stop
	das_map["GE"]    = 178                   ///< 55ms Voiced Stop
	das_map["GO"]    = 179                   ///< 55ms Voiced Stop
	das_map["EG"]    = 180                   ///< 55ms Voiced Stop
	das_map["OG"]    = 181                   ///< 55ms Voiced Stop
	das_map["CH"]   = 182                   ///< 70ms Voiceless Affricate
	das_map["HE"]   = 183                   ///< 70ms Voiceless Fricative
	das_map["HO"]   = 184                   ///< 70ms Voiceless Fricative
	das_map["WH"]   = 185                   ///< 70ms Voiceless Fricative
	das_map["FF"]   = 186                   ///< 70ms Voiceless Fricative
	das_map["SE"]   = 187                   ///< 40ms Voiceless Fricative
	das_map["SO"]   = 188                   ///< 40ms Voiceless Fricative
	das_map["SH"]   = 189                   ///< 50ms Voiceless Fricative
	das_map["TH"]    = 190                   ///< 40ms Voiceless Fricative
	das_map["TT"]    = 191                   ///< 50ms Voiceless Stop
	das_map["TU"]    = 192                   ///< 70ms Voiceless Stop
	das_map["TS"]    = 193                   ///< 170ms Voiceless Stop
	das_map["KE"]    = 194                   ///< 55ms Voiceless Stop
	das_map["KO"]    = 195                   ///< 55ms Voiceless Stop
	das_map["EK"]    = 196                   ///< 55ms Voiceless Stop
	das_map["OK"]    = 197                   ///< 45ms Voiceless Stop
	das_map["PE"]    = 198                   ///< 99ms Voiceless Stop
	das_map["PO"]    = 199                   ///< 99ms Voiceless Stop
	// Robot sound
	das_map["R0"]      = 200                   ///< 80ms Robot
	das_map["R1"]      = 201                   ///< 80ms Robot
	das_map["R2"]      = 202                   ///< 80ms Robot
	das_map["R3"]      = 203                   ///< 80ms Robot
	das_map["R4"]      = 204                   ///< 80ms Robot
	das_map["R5"]      = 205                   ///< 80ms Robot
	das_map["R6"]      = 206                   ///< 80ms Robot
	das_map["R7"]      = 207                   ///< 80ms Robot
	das_map["R8"]      = 208                   ///< 80ms Robot
	das_map["R9"]      = 209                   ///< 80ms Robot
	// Alarm sound
	das_map["A0"]      = 210                   ///< 300ms Alarm
	das_map["A1"]      = 211                   ///< 101ms Alarm
	das_map["A2"]      = 212                   ///< 102ms Alarm
	das_map["A3"]      = 213                   ///< 540ms Alarm
	das_map["A4"]      = 214                   ///< 530ms Alarm
	das_map["A5"]      = 215                   ///< 500ms Alarm
	das_map["A6"]      = 216                   ///< 135ms Alarm
	das_map["A7"]      = 217                   ///< 600ms Alarm
	das_map["A8"]      = 218                   ///< 300ms Alarm
	das_map["A9"]      = 219                   ///< 250ms Alarm
	// Beeps
	das_map["B0"]      = 220                   ///< 200ms Beep
	das_map["B1"]      = 221                   ///< 270ms Beep
	das_map["B2"]      = 222                   ///< 280ms Beep
	das_map["B3"]      = 223                   ///< 260ms Beep
	das_map["B4"]      = 224                   ///< 300ms Beep
	das_map["B5"]      = 225                   ///< 100ms Beep
	das_map["B6"]      = 226                   ///< 104ms Beep
	das_map["B7"]      = 227                   ///< 100ms Beep
	das_map["B8"]      = 228                   ///< 270ms Beep
	das_map["B9"]      = 229                   ///< 262ms Beep
	// Biological
	das_map["C0"]      = 230                   ///< 160ms Biological
	das_map["C1"]      = 231                   ///< 300ms Biological
	das_map["C2"]      = 232                   ///< 182ms Biological
	das_map["C3"]      = 233                   ///< 120ms Biological
	das_map["C4"]      = 234                   ///< 175ms Biological
	das_map["C5"]      = 235                   ///< 350ms Biological
	das_map["C6"]      = 236                   ///< 160ms Biological
	das_map["C7"]      = 237                   ///< 260ms Biological
	das_map["C8"]      = 238                   ///< 95ms Biological
	das_map["C9"]      = 239                   ///< 75ms Biological
	// DTMF
	das_map["D0"]        = 240                   ///< DTMF 0 95ms
	das_map["D1"]        = 241                   ///< DTMF 1 95ms
	das_map["D2"]        = 242                   ///< DTMF 2 95ms
	das_map["D3"]        = 243                   ///< DTMF 3 95ms
	das_map["D4"]        = 244                   ///< DTMF 4 95ms
	das_map["D5"]        = 245                   ///< DTMF 5 95ms
	das_map["D6"]        = 246                   ///< DTMF 6 95ms
    das_map["D8"]        = 248                   ///< DTMF 8 95ms
	das_map["D9"]        = 249                   ///< DTMF 9 95ms
	das_map["DTMF_STAR"]     = 250                   ///< DTMF * 95ms
	das_map["DTMF_HASH"]     = 251                   ///< DTMF # 95ms
	// Miscellaneous
	das_map["M0"]      = 252                   ///< Sonar ping 125ms
	das_map["M1"]      = 253                   ///< Pistol shot 250ms
	das_map["M2"] = 254 ///< WOW 530ms
	// command codes upper
	das_map["P0"]        = 0,                     ///< Pause 0ms
	das_map["P1"]        = 1,                     ///< Pause 100ms
	das_map["P2"]        = 2,                     ///< Pause 200ms
	das_map["P3"]        = 3,                     ///< Pause 700ms
	das_map["P4"]        = 4,                     ///< Pause 30ms
	das_map["P5"]        = 5,                     ///< Pause 60ms
	das_map["P6"]        = 6,                     ///< Pause 90ms
	das_map["FAST"]         = 7,                     ///< Next phoneme at 0.5 speed
	das_map["SLOW"]         = 8,                     ///< Next phoneme at 1.5 speed
	das_map["STRESS"]       = 14,                    ///< Next phoneme with some stress
	das_map["RELAX"]        = 15,                    ///< Next phoneme with relaxation
	das_map["WAIT"]         = 16,                    ///< Stops and waits for a Start (see manual)
	das_map["SOFT"]          = 18,                    ///< Stops and waits for a Start (see manual)
	das_map["VOLUME"]        = 20,                    ///< Next octet is volume 0 to 127. Default 96
	das_map["SPEED"]         = 21,                    ///< Next octet is speed 0 to 127. Default 114
	das_map["PITCH"]         = 22,                    ///< Next octet is pitch in Hz = to 255
	das_map["BEND"]         = 23,                    ///< Next octet is frequency bend  to 15. Default is 5
	das_map["PORTCTR"]       = 24,                    ///< Next octet is port control value. See manual. Default is 7
	das_map["PORT"]          = 25,                    ///< Next octet is Port Output Value. See manual. Default is 0
	das_map["REPEAT"]        = 26,                    ///< Next octet is repeat count. 0 to 255
	das_map["CALLPHRASE"]    = 28,                    ///< Next octet is EEPROM phrase to play and return. See manual.
	das_map["GOTOPHRASE"]    = 29,                    ///< Next octet is EEPROM phgrase to go to. See manual.
	das_map["DEKAY"]         = 30,                    ///< Next octet is delay in multiples of 10ms. 0 to 255.
	das_map["RESET"] = 31, ///< Reset Volume Speed, Pitch, Bend to defaults.

}
