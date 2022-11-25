int noor;
int darsad;
int tool;
int count=0;
int k=0;
char in;
String s="";
//int count;
int tanzimp=9;
int jahat1=11;
int jahat2=10;
//int pl=A4;
//int pr=A2;
int button_right=A1;
int button_left=A2;
int onoff=8;
int to=A0;
const int echoPin = 2; // Echo Pin of Ultrasonic Sensor
const int pingPin = 3; // Trigger Pin of Ultrasonic Sensor
void setup() {
  // put your setup code here, to run once:
  pinMode(pingPin, OUTPUT); // initialising pin 3 as output
  pinMode(echoPin, INPUT); // initialising pin 2 as input
pinMode(to,INPUT);
pinMode(button_right,INPUT);
pinMode(button_left,INPUT);
pinMode(onoff,INPUT);
pinMode(jahat1,OUTPUT);
pinMode(jahat2,OUTPUT);
pinMode(tanzimp,OUTPUT);
//pinMode(pl,INPUT);
//pinMode(pr,INPUT);
Serial.begin(9600);
}

void loop() {
  int on_off=digitalRead(onoff);
  //rahandazi
  if(on_off==1){
  // put your main code here, to run repeatedly:
  count=0;
 k=0;
 //daryaft etelaat az veb va ekhtesas dadane moteghayerha
 while (Serial.available()) {
  in=Serial.read();
  if(in=!'/'){
 s=s+in;   
  }
  }
  count=s.toInt();
  s="";
  if(0<=count<=100){
    darsad=count;
  }
  if(100<count<1111){
    tool=count/1.5;
  }
  if(count==6000){
    noor=1;
  }
  if(count==7000){
    noor=0;
  }
  //ultrasonic sensor
long duration, inches, place;
  
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  
  digitalWrite(pingPin, LOW);

  
  duration = pulseIn(echoPin, HIGH); // using pulsin function to determine total time
 place = microsecondsToCentimeters(duration); // calling method
  
//app:gharar gereftan parde dar jaye monaseb
int newplace=tool*darsad/100;
int fasele=abs(place-newplace);
int outputvalue=map(fasele,0,1023,0,255);
//andaze dutty cycle
analogWrite(tanzimp,outputvalue);
//tanzim pwm
if(place<newplace-2)
{
    digitalWrite(jahat1,HIGH);
  digitalWrite(jahat2,LOW);
}
if(place>newplace+2)
{
    digitalWrite(jahat1,LOW);
  digitalWrite(jahat2,HIGH);
}
//app
/*dasti*/
int buttonstate_r=digitalRead(button_right);
int buttonstate_l=digitalRead(button_left);
if(buttonstate_r==1){
  int outputvalue=map(50,0,1023,0,255);
//andaze dutty cycle
analogWrite(tanzimp,outputvalue);
   digitalWrite(jahat1,LOW);
  digitalWrite(jahat2,HIGH);
  Serial.println(place);
}
if(buttonstate_l==1){
   int outputvalue=map(50,0,1023,0,255);
//andaze dutty cycle
analogWrite(tanzimp,outputvalue);
   digitalWrite(jahat1,HIGH);
  digitalWrite(jahat2,LOW);
  Serial.println(place);
}
/*dasti*/
//photocell
if(noor==1){
int torch=digitalRead(to);
 int outputvalue=map(50,0,1023,0,255);
//andaze dutty cycle
analogWrite(tanzimp,outputvalue);
if(0.1<torch<4.5 && place<tool-2){
  digitalWrite(jahat1,HIGH);
  digitalWrite(jahat2,LOW);
}
if(4.5<torch<9.5 && place>4){
   digitalWrite(jahat1,LOW);
  digitalWrite(jahat2,HIGH);
}
}
//photocell
//car nakardan motor dar sar va tah
if(place<=4 || place>=tool-2)
{
   digitalWrite(jahat1,LOW);
  digitalWrite(jahat2,LOW);
}
 //Serial.println(place);

  }
}
//ultrasonic sensor

long microsecondsToCentimeters(long microseconds) // method to covert microsec to centimeters
{
   return microseconds / 29 / 2;
}
