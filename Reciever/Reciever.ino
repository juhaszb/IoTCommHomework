

int startarray[11] = { 1 , 0 ,0 ,0 , 1,  0 , 1 , 0 ,1 ,0 , 1};

bool detectStart(int arr[]) 
{
	for(int i = 0; i<  11; i ++ )
	{
		if(arr[10-i] != startarray[i])
		{	
			return false;
		}
	}
	return true;
}

int decodelength(int arr[])
{
	int len = 1;
	int num = 1;
	for(int i = 0; i<11 ; i++){
		if(arr[i] == 1)len+=num;
		num*=2;
	}
	return len-1;
}






void setup() {
	// initialize serial communication at 9600 bits per second:
	Serial.begin(9600);

	pinMode(16, INPUT);
}

int arrays[11] = { 0 } ;


bool startwas=false;
int lenmessage= -1;
int fullmessage = 0;
bool startready= true;
String message = "";

void loop() {
	int buttonState = digitalRead(16);
	for(int i = 11-1; i > 0; i--){
		arrays[i] = arrays[i-1];
	}
	arrays[0] = buttonState;
	if(startwas)
		lenmessage++;
	if(startwas==false && startready==false)
		lenmessage++;
	if(lenmessage==11 & startwas){
		fullmessage= decodelength(arrays);
		Serial.println(fullmessage);
		startwas= false;
		lenmessage =0;

	}else if(lenmessage ==11)
	{
		fullmessage -=11;

		lenmessage =0;
		int chargot= decodelength(arrays);
		Serial.print((char)chargot);
		if(fullmessage <=0 ){
			startready=true;
			Serial.println();
		}
	}

		if(startready){
			if(detectStart(arrays)){
				Serial.println("GOT it");
				for(int i = 0 ; i< 11 ; i++)
					arrays[i] = 0 ; 
				startwas=true;
				lenmessage= 0;
				startready=false;
			}
		}
		delay(50);

}
