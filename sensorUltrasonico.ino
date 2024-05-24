const int trigPin = 7;
const int echoPin = 6;

long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // Clear the trigPin by setting it LOW
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Trigger the sensor by setting the trigPin HIGH for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  
  duration = pulseIn(echoPin, HIGH);


  distance = duration * 0.034 / 2;

  // imprimimos la salida
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // un delay entre las lecturas 
  delay(100);
}
