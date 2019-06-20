
//Constants:
const int APin = A0; //pin A0 to read analog input
const int BPin = A1;
const int CPin = A2;
const int DPin = A3;


//Variables:
int valueA; //save analog value
int valueB;
int valueC;
int valueD;

int sensorValueA = 0;
int sensorValueB = 0;
int sensorValueC = 0;
int sensorValueD = 0;

float EMA_a_lowA = 0.01;    //initialization of EMA alpha
float EMA_a_highA = 0.03;
float EMA_a_lowB = 0.01;    //initialization of EMA alpha
float EMA_a_highB = 0.03;
float EMA_a_lowC = 0.01;    //initialization of EMA alpha
float EMA_a_highC = 0.03;
float EMA_a_lowD = 0.1;    //initialization of EMA alpha
float EMA_a_highD = 0.15;
 
int EMA_S_lowA = 0;        //initialization of EMA S
int EMA_S_highA = 0;
int EMA_S_lowB = 0;        //initialization of EMA S
int EMA_S_highB = 0;
int EMA_S_lowC = 0;        //initialization of EMA S
int EMA_S_highC = 0;
int EMA_S_lowD = 0;        //initialization of EMA S
int EMA_S_highD = 0;
 
int highpassA = 0;
int bandpassA = 0;
int highpassB = 0;
int bandpassB = 0;
int highpassC = 0;
int bandpassC = 0;
int highpassD = 0;
int bandpassD = 0;
  
void setup(){
  
  Serial.begin(115200);       //Begin serial communication
  EMA_S_lowA = analogRead(APin);      //set EMA S for t=1
  EMA_S_highA = analogRead(APin);
  EMA_S_lowB = analogRead(BPin);      //set EMA S for t=1
  EMA_S_highB = analogRead(BPin);
  EMA_S_lowC = analogRead(CPin);      //set EMA S for t=1
  EMA_S_highC = analogRead(CPin);
  EMA_S_lowD = analogRead(DPin);      //set EMA S for t=1
  EMA_S_highD = analogRead(DPin);
}

void loop(){

  float AverageA = 0;
  float AverageB = 0;
  float AverageC = 0;
  float AverageD = 0;
  
  sensorValueA = analogRead(APin); 
  sensorValueB = analogRead(BPin); 
  sensorValueC = analogRead(CPin); 
  sensorValueD = analogRead(DPin);

  EMA_S_lowA = (EMA_a_lowA*sensorValueA) + ((1-EMA_a_lowA)*EMA_S_lowA);  //run the EMA
  EMA_S_highA = (EMA_a_highA*sensorValueA) + ((1-EMA_a_highA)*EMA_S_highA);
  EMA_S_lowB = (EMA_a_lowB*sensorValueB) + ((1-EMA_a_lowB)*EMA_S_lowB);  //run the EMA
  EMA_S_highB = (EMA_a_highB*sensorValueB) + ((1-EMA_a_highB)*EMA_S_highB);
  EMA_S_lowC = (EMA_a_lowC*sensorValueC) + ((1-EMA_a_lowC)*EMA_S_lowC);  //run the EMA
  EMA_S_highC = (EMA_a_highC*sensorValueC) + ((1-EMA_a_highC)*EMA_S_highC);
  EMA_S_lowD = (EMA_a_lowD*sensorValueD) + ((1-EMA_a_lowD)*EMA_S_lowD);  //run the EMA
  EMA_S_highD = (EMA_a_highD*sensorValueD) + ((1-EMA_a_highD)*EMA_S_highD);

  highpassA = sensorValueA - EMA_S_lowA;     //find the high-pass as before (for comparison)
  bandpassA = EMA_S_highA - EMA_S_lowA;      //find the band-pass
  highpassB = sensorValueB;// - EMA_S_lowB;     //find the high-pass as before (for comparison)
  bandpassB = EMA_S_highB;// - EMA_S_lowB;      //find the band-pass
  highpassC = sensorValueC;// - EMA_S_lowC;     //find the high-pass as before (for comparison)
  bandpassC = EMA_S_highC;// - EMA_S_lowC;      //find the band-pass
  highpassD = sensorValueD;// - EMA_S_lowD;     //find the high-pass as before (for comparison)
  bandpassD = EMA_S_highD;// - EMA_S_lowD;      //find the band-pass

  Serial.print(AverageA);
  
  Serial.print(" ");
  Serial.print(highpassD);
  Serial.print(" ");
  Serial.print(bandpassD);
  Serial.print("\n");

  delay(10);
}


