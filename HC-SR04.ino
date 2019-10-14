int trigPin = 2;
int echoPin = 3;

long _time;
long _distance;
int _time_array[2];

const int _sleep = 5;

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  digitalWrite(trigPin, LOW);
}

void cmToM() {
  if (_distance < 100) {
    _time_array[0] = 0;
    _time_array[1] = _distance;
  } else {
    _time_array[0] = _distance / 100;
    _time_array[1] = _distance - (_time_array[0] * 100);
  }
}

void findDistance() {
  delayMicroseconds(_sleep);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(_sleep);
  digitalWrite(trigPin, LOW);

  _time = pulseIn(echoPin, HIGH);
  _distance = _time / 29.1 / 2;
  cmToM();

  if (_distance > 200)
    Serial.println("Distance : Bigger than 2m.");
  else if (_distance < 100) {
    Serial.print("Distance : 0m ");
    Serial.print(_time_array[1]);
    Serial.println("cm.");
  }
  else {
    Serial.print("Distance : ");
    Serial.print(_time_array[0]);
    Serial.print("m ");
    Serial.print(_time_array[1]);
    Serial.println("cm.");
  }
  delay(_sleep);
}

void loop() {
    findDistance();
}
