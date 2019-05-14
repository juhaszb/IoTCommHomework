#define DELAYLEN 250
// 1 1 0 1 0 1 0 1 
void sendbegin(){
  int i = 0;
  digitalWrite(5, HIGH);
  delay(DELAYLEN);
  while(i < 3){
    digitalWrite(5, HIGH);
    delay(DELAYLEN);
    digitalWrite(5, LOW);
    delay(DELAYLEN);
    i++;
  }
  digitalWrite(5, HIGH);
  delay(DELAYLEN);
  digitalWrite(5, LOW);
}

String str = "";
void messagelengh(int dummylength){
  str="";
  int nb = 7; // number of bits
  for(nb; nb >=0; nb --)
     str+=String(bitRead(dummylength,nb));
  unsigned int stringlen = str.length();
  for(int i = 0; i < stringlen; i++ )
    if(str[i] == '1'){
        digitalWrite(5,HIGH);
        delay(DELAYLEN);
    }
    else
    {
      digitalWrite(5,LOW);
      delay(DELAYLEN);
    }
    digitalWrite(5,LOW);
  Serial.print("messagelen");
  Serial.println(str);
}

void message(String str_j){
  for(int j = 0; j < str_j.length(); j++){
    int character = str_j[j];
    str="";
    int nb = 7;
    for(nb; nb >= 0; nb--)
       str+=String(bitRead(character, nb));
    unsigned int stringlen = str.length();
    for(int i = 0; i < stringlen; i++ )
    {
      if(str[i] == '1'){
          digitalWrite(5,HIGH);
          delay(DELAYLEN);
      }
      else
      {
        digitalWrite(5,LOW);
        delay(DELAYLEN);
      }
    }
      digitalWrite(5,LOW);
    Serial.print("char:");
    Serial.print((char)character);
    Serial.println(str);
  }
}


void setup() {
  pinMode(5, OUTPUT);
  Serial.begin(115200);
  String valami = "Get a substring of a String. The starting index is inclusive (the corresponding character is included in the substring), but the optional ending index is exclusive (the corresponding character is not included in the substring). If the ending index is omitted, the substring continues to the end of the String.";
  int numofslices = (valami.length()/16)+1;
  String sliced[numofslices];
  for(int i = 0 ; i < numofslices; i ++)
  {
    if((valami.length() - i* 16) < 16 )
    sliced[i] = String(valami.substring(i*16));
    else
    sliced[i] = String(valami.substring(i*16,(i*16)+16));
    Serial.println(sliced[i]);
    Serial.println(sliced[i].length());
    Serial.println();
  }
  for(int i = 0; i < numofslices ; i ++)
  {
    sendbegin();
    messagelengh((sliced[i].length()*8));
    message(sliced[i]);
  }
  
  digitalWrite(5,LOW);
}

void loop() {
}
