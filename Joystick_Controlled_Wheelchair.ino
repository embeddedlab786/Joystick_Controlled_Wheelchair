#define yAxis_pin A0 // Joysticks Y-axis
#define xAxis_pin A1 // Joysticks X-axis

#define enA 5
#define in1 6
#define in2 7

#define in3 8
#define in4 9
#define enB 10

int motorSpeedA = 0;
int motorSpeedB = 0;

void setup(){

pinMode(xAxis_pin, INPUT);
pinMode(yAxis_pin, INPUT);

pinMode(enA, OUTPUT);
pinMode(in1, OUTPUT);
pinMode(in2, OUTPUT);
pinMode(in3, OUTPUT);
pinMode(in4, OUTPUT);
pinMode(enB, OUTPUT);

delay(100);
}

void loop(){ 
int xAxis = analogRead(xAxis_pin); // Read Joysticks X-axis
int yAxis = analogRead(yAxis_pin); // Read Joysticks Y-axis

// If joystick stays in middle the motors are not moving
if(xAxis > 470 && xAxis <550 && yAxis > 470 && yAxis <550){Stop();}

if (xAxis > 470 && xAxis <550){    
// Y-axis used for left and right control
if (yAxis < 470){turnRight();
// Convert the declining Y-axis readings for going backward from 470 to 0 into 0 to 255 value for the PWM signal for increasing the motor speed  
motorSpeedA = map(yAxis, 470, 0, 0, 255);
motorSpeedB = map(yAxis, 470, 0, 0, 255);    
}

if (yAxis > 550) {turnLeft();
// Convert the increasing Y-axis readings for going forward from 550 to 1023 into 0 to 255 value for the PWM signal for increasing the motor speed      
motorSpeedA = map(yAxis, 550, 1023, 0, 255);
motorSpeedB = map(yAxis, 550, 1023, 0, 255); 
}

}else{

if (yAxis > 470 && yAxis <550){   
// X-axis used for forward and backward control  
if (xAxis < 470){forword();}
if (xAxis > 550){backword();}

if (xAxis < 470){
// Convert the declining X-axis readings for going backward from 470 to 0 into 0 to 255 value for the PWM signal for increasing the motor speed  
motorSpeedA = map(xAxis, 470, 0, 0, 255);
motorSpeedB = map(xAxis, 470, 0, 0, 255); 
}

if (xAxis > 550){
// Convert the increasing X-axis readings for going forward from 550 to 1023 into 0 to 255 value for the PWM signal for increasing the motor speed      
motorSpeedA = map(xAxis, 550, 1023, 0, 255);
motorSpeedB = map(xAxis, 550, 1023, 0, 255);
 }
 
}else{

if(xAxis < 470){forword();}
if(xAxis > 550){backword();}

if(yAxis < 470){
    // Convert the declining Y-axis readings from 470 to 0 into increasing 0 to 255 value
    int yMapped = map(yAxis, 470, 0, 0, 255);
    
    // Move to left - decrease left motor speed, increase right motor speed
    motorSpeedA = motorSpeedA + yMapped;
    motorSpeedB = motorSpeedB - yMapped;
    
    // Confine the range from 0 to 255
    if(motorSpeedA > 255) {motorSpeedA = 255;}
    if(motorSpeedB > 70){motorSpeedB = 70;}
}
 
if (yAxis > 550){
    // Convert the increasing Y-axis readings from 550 to 1023 into 0 to 255 value
    int yMapped = map(yAxis, 550, 1023, 0, 255);
    
    // Move right - decrease right motor speed, increase left motor speed
    motorSpeedA = motorSpeedA - yMapped;
    motorSpeedB = motorSpeedB + yMapped;
    
    // Confine the range from 0 to 255
    if(motorSpeedA < 70){motorSpeedA = 70;}
    if(motorSpeedB > 255){motorSpeedB = 255;}
  }
 } 
}

// Prevent buzzing at low speeds (Adjust according to your motors. My motors couldn't start moving if PWM value was below value of 70)
if(motorSpeedA < 70){motorSpeedA = 0;}
if(motorSpeedB < 70){motorSpeedB = 0;}
  
analogWrite(enA, motorSpeedA); // Send PWM signal to motor A
analogWrite(enB, motorSpeedB); // Send PWM signal to motor B

delay(10);
}   

void forword(){
// Set Motor A forward
digitalWrite(in1, HIGH);
digitalWrite(in2, LOW);
// Set Motor B forward
digitalWrite(in3, LOW);
digitalWrite(in4, HIGH);
}

void backword(){    
// Set Motor A backward
digitalWrite(in1, LOW);
digitalWrite(in2, HIGH);
// Set Motor B backward
digitalWrite(in3, HIGH);
digitalWrite(in4, LOW);
}

void turnRight(){
// Set Motor A forward
digitalWrite(in1, HIGH);
digitalWrite(in2, LOW);
// Set Motor B backward 
digitalWrite(in3, HIGH);
digitalWrite(in4, LOW);
}

void turnLeft(){
// Set Motor B backward 
digitalWrite(in1, LOW);
digitalWrite(in2, HIGH);
// Set Motor B forward 
digitalWrite(in3, LOW);
digitalWrite(in4, HIGH);
}

void Stop(){
// Set Motor A stop
digitalWrite(in1, LOW);
digitalWrite(in2, LOW);
// Set Motor B stop
digitalWrite(in3, LOW);
digitalWrite(in4, LOW);
}
     
