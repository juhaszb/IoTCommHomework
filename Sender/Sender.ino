#define DELAYLEN 50

void sendbegin(){
  int i = 0;
  digitalWrite(5, HIGH);
  delay(DELAYLEN);
  digitalWrite(5, LOW);
  delay(DELAYLEN*3);

  while(i < 3){
    digitalWrite(5, HIGH);
    delay(DELAYLEN);
    digitalWrite(5, LOW);
    delay(DELAYLEN);
    i++;
  }
  digitalWrite(5, HIGH);
  delay(DELAYLEN);
}

String str = "";
void messagelengh(int dummylength){
  int nb = 10;
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
  Serial.println(str);
}

void message(String str_j){
  for(int j = 0; j < str_j.length(); j++){
    int character = str_j[j];
    str="";
    int nb = 10;
    for(nb; nb >= 0; nb--)
       str+=String(bitRead(character, nb));
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
    Serial.println(str);
  }
}

void setup() {
  pinMode(5, OUTPUT);
  Serial.begin(9600);
  String valami = "Hosszabb, mint 2048 bitjbkgsdvhfgsajfasbkdjshdfasfsakjhskd bhfaskdaskdjsbdkfsak jasbdfasdkfgvasdfj shdjgfaksjdaskdjhagskda skdjsadkfsafkjasfbgaksjd gfsakdjgf";
  sendbegin(); 
  messagelengh(valami.length()*11);
  message(valami);
  digitalWrite(5,LOW);
}

void loop() {
}
