#define trigPin 13
#define echoPin 12
int motorPin1 = 8;    // Azul   - 28BYJ48 pin 1 motor
int motorPin2 = 9;    // Rosa   - 28BYJ48 pin 2 motor
int motorPin3 = 10;    // Amarillo - 28BYJ48 pin 3 motor
int motorPin4 = 11;    // Naranja - 28BYJ48 pin 4 motor
                        // Rojo   - 28BYJ48 pin 5 (VCC) motor
int status = 0;
int motorSpeed = 1200;  //variable para fijar la velocidad del motor (el retraso entre cada secuencia)
int count = 0;          // cuenta de los pasos dados
int countsperrev = 500; // número de pasos por vuelta completa 
int lookup[8] = {B01000, B01100, B00100, B00110, B00010, B00011, B00001, B01001};

void setup() {
  //declare the motor pins as outputs
  
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop(){
long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  if ( distance < 4 && status == 0) {
    clockwise();    
  }
  else if ( distance < 4 && status == 1 ){
    anticlockwise();
  }
  
}


//creación funciones giro horario y antihorario
void anticlockwise() 
{ 
  for( count = 0; count <= countsperrev ; count ++) {
    for(int i = 0; i < 8; i++)
    {
      setOutput(i);
      delayMicroseconds(motorSpeed);
    }
  }
  status = 0;
}

void clockwise()
{
  for ( count = countsperrev; count >= 0; count --){
    for(int i = 7; i >= 0; i--)
    {
      setOutput(i);
      delayMicroseconds(motorSpeed);
    }
  }
  status = 1;
}

void setOutput(int out) //función secuencia giro
{
  digitalWrite(motorPin1, bitRead(lookup[out], 0));
  digitalWrite(motorPin2, bitRead(lookup[out], 1));
  digitalWrite(motorPin3, bitRead(lookup[out], 2));
  digitalWrite(motorPin4, bitRead(lookup[out], 3));
}
