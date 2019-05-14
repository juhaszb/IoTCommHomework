

int startarray[11] = { 1 ,  1,  0 , 1 , 0 ,1 ,0 , 1};

bool detectStart(int arr[]) 
{
	for(int i = 0; i<  8; i ++ )
	{
		if(arr[7-i] != startarray[i])
		{	
			return false;
		}
	}
	return true;
}

int decodelength(int arr[])
{
	int len = 0;
	int num = 1;
	for(int i = 0; i<8 ; i++){
		if(arr[i] == 1)len+=num;
		num*=2;
	}
	return len;
}






void setup() {
	// initialize serial communication at 9600 bits per second:
	Serial.begin(115200);

	pinMode(16, INPUT);
}

int arrays[8] = { 0 } ;


bool startwas=false;
int lenmessage= -1;
int fullmessage = 0;
bool startready= true;
String message = "";
void loop() {
	int buttonState = digitalRead(16);
	for(int i = 8-1; i > 0; i--){
    //Serial.print(arrays[i]);
		arrays[i] = arrays[i-1];
	}
 //Serial.println();
	arrays[0] = buttonState;
	if(startwas)
		lenmessage++;
	if(startwas==false && startready==false)
		lenmessage++;
	if(lenmessage==8 & startwas){
		fullmessage= decodelength(arrays);
		Serial.println(fullmessage);
		startwas= false;
		lenmessage =0;

	}else if(lenmessage ==8)
	{
		fullmessage -=8;

		lenmessage =0;
		int chargot= decodelength(arrays);
    for(int i = 0 ; i <8 ; i ++)
    arrays[i] = 0 ;
		Serial.print((char)chargot);
		if(fullmessage <=0 ){
			startready=true;
			Serial.println();
		}
	}

		if(startready){
			if(detectStart(arrays)){
				Serial.println("GOT it");
				for(int i = 0 ; i< 8 ; i++)
					arrays[i] = 0 ; 
				startwas=true;
				lenmessage= 0;
				startready=false;
			}
		}
		delay(250);

}
