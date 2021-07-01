String action;
int motor1=11;
int motor11=10;
int motor2=9;
int motor22=6;
int recievedmsg1,recievedmsg2,recievedmsg3;
int concat_init_1=0;


int led=13;

void setup()
{
Serial.begin(9600);
pinMode(motor1,OUTPUT);
pinMode(motor11,OUTPUT);
pinMode(motor2,OUTPUT);
pinMode(motor22,OUTPUT);
Serial.println("REDx PWM Firmware");
pinMode(led,OUTPUT);
}

void loop()
{
    digitalWrite(led,HIGH);
    delay(500);
    digitalWrite(led,LOW);
    delay(500);
    if(Serial.available()>0)
    {
        action=Serial.readString();
        action.trim();
        

        if(action =="F")
        {
            forward();
        }
        else if(action == "B")
        {
            backward();
        }

        else if(action == "L")
        {
            left();
        }

        else if(action == "R")
        {
            right();
        }

        else if(action == "S")
        {
            stop();
        }
        
    }
}

void forward()
{
    digitalWrite(motor1,HIGH);
    digitalWrite(motor11,LOW);
    digitalWrite(motor2,HIGH);
    digitalWrite(motor22,LOW);
    Serial.println(HIGH);
    
}

void backward()
{
    digitalWrite(motor1,LOW);
    digitalWrite(motor11,HIGH);
    digitalWrite(motor2,LOW);
    digitalWrite(motor22,HIGH);
    Serial.println(HIGH);
    
}

void right()
{
    digitalWrite(motor1,HIGH);
    digitalWrite(motor11,LOW);
    digitalWrite(motor2,LOW);
    digitalWrite(motor22,HIGH);
    Serial.println(HIGH);
    
}

void left()
{
    digitalWrite(motor1,LOW);
    digitalWrite(motor11,HIGH);
    digitalWrite(motor2,HIGH);
    digitalWrite(motor22,LOW);
    Serial.println(HIGH);
    
}


void stop()
{
    digitalWrite(motor1,LOW);
    digitalWrite(motor11,LOW);
    digitalWrite(motor2,LOW);
    digitalWrite(motor22,LOW);
    Serial.println("HIGH: 0");

}
