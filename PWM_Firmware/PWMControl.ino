/*
AUTHOR:Er.Akhil P Jacob
ROBOT:REDx

*/
const int pwm = 5 ;  //initializing pin 2 as pwm
const int in_1 = 11 ;
const int in_2 = 10 ;
const int in_3 = 9 ;
const int in_4 = 6 ;
const int pwm2= 3;
String action;
int recievedmsg1,recievedmsg2,recievedmsg3;
int concat_init_1=0;
int final_speed=0;
char Dir;
int led=13;
//For providing logic to L298 IC to choose the direction of the DC motor 

void setup()
{
pinMode(pwm,OUTPUT) ;   //we have to set PWM pin as output
pinMode(in_1,OUTPUT) ;  //Logic pins are also set as output
pinMode(in_2,OUTPUT) ;
pinMode(pwm2,OUTPUT);
pinMode(in_3,OUTPUT) ;  //Logic pins are also set as output
pinMode(in_4,OUTPUT) ;
Serial.begin(9600);
Serial.println("REDx PWM Firmware");
}

void loop()
{
    digitalWrite(led,HIGH);
    delay(500);
    digitalWrite(led,LOW);
    delay(500);
//For Clock wise motion , in_1 = High , in_2 = Low
if(Serial.available()>0)
{
    action=Serial.readString();
    action.trim();
    
    Dir=action[0];
    recievedmsg1=action[1]-48;
    recievedmsg2=action[2]-48;
    recievedmsg3=action[3]-48;
    concat_init_1=recievedmsg1*10+recievedmsg2;
    final_speed=concat_init_1*10+recievedmsg3;
    Serial.println(Dir);
    
    if(Dir =='F')
    {   
        
        forward(final_speed);
    }
    else if(Dir =='B' )
    {
        backward(final_speed);
        
    }

    else if(Dir =='L')
    {
        left(final_speed);
    }

    else if(Dir =='R')
    {
        right(final_speed);
    }

    else if(Dir == 'S')
    {
        stop();
    }
}


/*setting pwm of the motor to 255
we can change the speed of rotaion
by chaning pwm input but we are only
using arduino so we are using higest
value to driver the motor  */


 }

 void forward(int speed)
{
    digitalWrite(in_1,HIGH) ;
    digitalWrite(in_2,LOW) ;
    digitalWrite(in_3,HIGH) ;
    digitalWrite(in_4,LOW);
    analogWrite(pwm,speed) ;
    analogWrite(pwm2,speed) ;
    Serial.println(speed);

    
}

void backward(int speed)
{
    digitalWrite(in_1,LOW) ;
    digitalWrite(in_2,HIGH) ;
    digitalWrite(in_3,LOW) ;
    digitalWrite(in_4,HIGH);
    analogWrite(pwm,speed) ;
    analogWrite(pwm2,speed) ;
    Serial.println(speed);
    
}

void right(int speed)
{
    digitalWrite(in_1,HIGH) ;
    digitalWrite(in_2,LOW) ;
    digitalWrite(in_3,LOW) ;
    digitalWrite(in_4,HIGH);
    analogWrite(pwm,speed) ;
    analogWrite(pwm2,speed) ;
    Serial.println(speed);
    
}

void left(int speed)
{
    digitalWrite(in_1,LOW) ;
    digitalWrite(in_2,HIGH) ;
    digitalWrite(in_3,HIGH) ;
    digitalWrite(in_4,LOW);
    analogWrite(pwm,speed) ;
    analogWrite(pwm2,speed) ;
    Serial.println(speed);
    
}


void stop()
{
    digitalWrite(in_1,LOW) ;
    digitalWrite(in_2,LOW) ;
    digitalWrite(in_3,LOW) ;
    digitalWrite(in_4,LOW);
    analogWrite(pwm,0) ;
    analogWrite(pwm2,0) ;
    Serial.println("STOPPED");

}
