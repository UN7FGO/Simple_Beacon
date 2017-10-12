// Данный проект направлен на создание маяка на базе переносной радиостанции типа Baofeng или Kenwood
// This project is aimed at creating a lighthouse based on a portable radio station such as Baofeng or Kenwood

// контакт вывода на "ключевание"
#define CW_PIN 13
// контакт вывода звука 
#define CW_AUDIO_KEYER_PIN 10
// частота звука для контроля
#define CW_AUDIO_FREQUENCY 880
// базова длина "точки", определяет скорость передачи сообщения
#define CW_TICK_TIME_MILLISECONDS 70
// контакт PTT
#define CW_PTT_PIN 9
// время повтора сообщения, секунды
unsigned long TIME_RPT = 120;

  int t_tick = CW_TICK_TIME_MILLISECONDS;

  // Length of dot, dash, between characters, between words
  // Динна точки, тире, между символами, между словами
  int t_dot = t_tick * 1;
  int t_dash = t_tick * 3;
  int t_between_char = t_tick * 3;
  int t_between_words = t_tick * 7;
  
  String st_beacon;
  unsigned long last_time;

  
void setup() {
// раздел начальных "динамических" установок
  last_time = 0;
// строка, которую будет выдавать маяк
  st_beacon = "E CQ CQ CQ DE BEACON UN7FGO TEST BEACON LOC MO82LH BAND 70 CM PSE K";
  pinMode(CW_PIN, OUTPUT);
  pinMode(CW_PTT_PIN, OUTPUT);
}

void loop() {
      
// если прошло достаточно времени, то начинаем передавать сообщение
  if ((millis() - last_time) > (TIME_RPT*1000) || last_time == 0 )
  {
    last_time = millis();
     
// включаем режим передачи
// для радиостанций с необходимостью нажатия PTT
      digitalWrite(CW_PTT_PIN, HIGH);
// выдаем строку текста посимвольно кодом Морзе
      int st_len = st_beacon.length();
      for (int i=0; i<st_len; i++) {
        keyCwForCharacter(st_beacon[i]);
      }
  
// выключаем режим передачи
// для радиостанций с необходимостью нажатия PTT
      digitalWrite(CW_PTT_PIN, LOW);
      
    
  }


}

// Функция преобразования символа в строку кода Морзе
// Написано примитивненько, но работает
// можно дополнить любыми символами
char *morseForSymbol(char symbol) {
  char *morse = NULL;

  if (symbol == '.') {
    morse = ".-.-.-";
  } else if (symbol == 'a' || symbol == 'A') {
    morse = ".-";
  } else if (symbol == 'b' || symbol == 'B') {
    morse = "-...";
  } else if (symbol == 'c' || symbol == 'C') {
    morse = "-.-.";
  } else if (symbol == 'd' || symbol == 'D') {
    morse = "-..";
  } else if (symbol == 'e' || symbol == 'E') {
    morse = ".";
  } else if (symbol == 'f' || symbol == 'F') {
    morse = "..-.";
  } else if (symbol == 'g' || symbol == 'G') {
    morse = "--.";
  } else if (symbol == 'h' || symbol == 'H') {
    morse = "....";
  } else if (symbol == 'i' || symbol == 'I') {
    morse = "..";
  } else if (symbol == 'j' || symbol == 'J') {
    morse = ".---";
  } else if (symbol == 'k' || symbol == 'K') {
    morse = "-.-";
  } else if (symbol == 'l' || symbol == 'L') {
    morse = ".-..";
  } else if (symbol == 'm' || symbol == 'M') {
    morse = "--";
  } else if (symbol == 'n' || symbol == 'N') {
    morse = "-.";
  } else if (symbol == 'o' || symbol == 'O') {
    morse = "---";
  } else if (symbol == 'p' || symbol == 'P') {
    morse = ".--.";
  } else if (symbol == 'q' || symbol == 'Q') {
    morse = "--.-";
  } else if (symbol == 'r' || symbol == 'R') {
    morse = ".-.";
  } else if (symbol == 's' || symbol == 'S') {
    morse = "...";
  } else if (symbol == 't' || symbol == 'T') {
    morse = "-";
  } else if (symbol == 'u' || symbol == 'U') {
    morse = "..-";
  } else if (symbol == 'v' || symbol == 'V') {
    morse = "...-";
  } else if (symbol == 'w' || symbol == 'W') {
    morse = ".--";
  } else if (symbol == 'x' || symbol == 'X') {
    morse = "-..-";
  } else if (symbol == 'y' || symbol == 'Y') {
    morse = "-.--";
  } else if (symbol == 'z' || symbol == 'Z') {
    morse = "--..";
  } else if (symbol == '0') {
    morse = "-----";
  } else if (symbol == '1') {
    morse = ".----";
  } else if (symbol == '2') {
    morse = "..---";
  } else if (symbol == '3') {
    morse = "...--";
  } else if (symbol == '4') {
    morse = "....-";
  } else if (symbol == '5') {
    morse = ".....";
  } else if (symbol == '6') {
    morse = "-....";
  } else if (symbol == '7') {
    morse = "--...";
  } else if (symbol == '8') {
    morse = "---..";
  } else if (symbol == '9') {
    morse = "----.";
  } else if (symbol == '?') {
    morse = "..--..";
  } else if (symbol == '=') {
    morse = "-...-";
  } else if (symbol == '/') {
    morse = "-..-.";
  } else if (symbol == '+') {
    morse = ".-.-.";
  } else if (symbol == ',') {
    morse = "--..--";
  } else {
    // For anything else, return a question mark
    morse = "..--.."; 
  }
  return morse;
}

// функция вывода символа азбукой Морзе, в качестве параметра передается символ
void keyCwForCharacter(char symbol) {

  if (symbol == ' ') {
    delay(t_between_words);
  } else {
    char *symbol_in_morse = morseForSymbol(symbol);
    int j_len = strlen(symbol_in_morse);
    int j = 0;

    for (j=0; j<j_len; j++) {
      char dotdash = *(symbol_in_morse + j);
      int t_delay = 0;
      if (dotdash == '.') {
        t_delay = t_dot;
      } else if (dotdash == '-') {
        t_delay = t_dash;
      } else {
        t_delay = t_tick;
      }
  
// нажимаем "ключ"      
      digitalWrite(CW_PIN, HIGH);
// включаем звуковой тон
      tone(CW_AUDIO_KEYER_PIN, CW_AUDIO_FREQUENCY);
// задержка длительности звука/нажатия ключа      
      delay(t_delay);
// выключаем звуковой тон      
      noTone(CW_AUDIO_KEYER_PIN);
// "отпускаем" ключ
      digitalWrite(CW_PIN, LOW);
// выдерживаем паузу между точками/тире      
      delay(t_tick);
    }
// выдерживаем паузу между символами
    delay(t_between_char);
  }
}


