                                          ///// Setting up all the libraries

#include <math.h>
#include <ros.h>
#include <geometry_msgs/Twist.h>

                                          ///// Defining the PWM maximum and minimum range
#define PWMRANGEs 1020 // if you type not "s" it will pick basic pwm range for me it took 255 for the arduino causing problems
#define PWM_MIN 300

                                          ///// Initializing the functions that we will be using through the code 
void setupPins();
void setupSerial();
void setupWiFi();
bool rosConnected();
void onTwist(const geometry_msgs::Twist &msg);
float mapPwm(float x, float out_min, float out_max);

                                          ///// All pins defining
//const uint8_t R_PWM =  5;
const uint8_t R_BACK = 11;
const uint8_t R_FORW = 10;

//const uint8_t L_PWM =  3;
const uint8_t L_BACK = 9;
const uint8_t L_FORW = 6;
                                      

                                           //// Setting up arduino ROS communication handle 
ros::NodeHandle node;
ros::Subscriber<geometry_msgs::Twist> sub("/cmd_vel", &onTwist); // keyboard input subscriber


                                           //// Generic structure of arduino IDE programming

void setup()
{ Serial.begin(57600);
  setupPins(); 
  node.initNode();
  node.subscribe(sub);// starting to subscribe the desired topic
}

                                           //// Difining Functionality of all pins

void setupPins()
{ /// calling this function from setup();
  //pinMode(L_PWM,  OUTPUT);
  pinMode(L_FORW, OUTPUT);
  pinMode(L_BACK, OUTPUT);
  //pinMode(R_PWM,  OUTPUT);
  pinMode(R_FORW, OUTPUT);
  pinMode(R_BACK, OUTPUT);
  stop(); // making robot to not move
}

                                            //// Connecting esp to common ROSCORE wifi                               

                                           //// Stop function to stop the robot movement
void stop()
{
  digitalWrite(L_FORW, 0);
  digitalWrite(L_BACK, 0);
  digitalWrite(R_FORW, 0);
  digitalWrite(R_BACK, 0);
  //analogWrite(L_PWM,   0);
  //analogWrite(R_PWM,   0);
}

                                           //// Starting the commands dealing mathemetically

void onTwist(const geometry_msgs::Twist &msg)
{ 
  
  float x = max(min(msg.linear.x, 1.0f), -1.0f);// minimum value (-1) maximum value (1)
  float z = max(min(msg.angular.z, 1.0f), -1.0f);// minimum value (-1) maximum value (1)
  
                                          /// Transforming linear and angular velocities to speed for the LEFT RIGHT MOTORS
  float l = (msg.linear.x - msg.angular.z) / 2;
  float r = (msg.linear.x + msg.angular.z) / 2;
                                          ///According to the speed derived we get pwm for motors
  uint16_t lPwm = mapPwm(fabs(l), 450, 1050);
  uint16_t rPwm = mapPwm(fabs(r), 450, 1050);
  
  digitalWrite(L_FORW, HIGH);
  digitalWrite(R_FORW, LOW);
  
  digitalWrite(L_BACK, HIGH);
  digitalWrite(R_BACK, LOW);
  
  //analogWrite(L_PWM, lPwm);
  //analogWrite(R_PWM, rPwm);
}



                                           //// Main loop just spins on the back subscribing node gets the work done
void loop()
{
  node.spinOnce();
  delay(10);
}


float mapPwm(float x, float out_min, float out_max)
{
  return x * (out_max - out_min) + out_min;
}