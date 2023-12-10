int i;

int sign;

long value;

float result;

int clockpin = 4;

int datapin = 5;

unsigned long tempmicros;





void setup() {

  Serial.begin(9600);

  pinMode(clockpin, INPUT);

  pinMode(datapin, INPUT);

  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
}

void loop () {
  while (digitalRead(clockpin) == LOW) {} //if clock is LOW wait until it turns to HIGH

  tempmicros = micros();

  while (digitalRead(clockpin) == HIGH) {} //wait for the end of the HIGH pulse

  if ((micros() - tempmicros) > 500) { //if the HIGH pulse was longer than 500 micros we are at the start of a new bit sequence

    decode(); //decode the bit sequence

  }

}



void decode() {

  sign = 1;

  value = 0;

  for (i = 0; i < 23; i++) {

    while (digitalRead(clockpin) == HIGH) { } //wait until clock returns to HIGH- the first bit is not needed

    while (digitalRead(clockpin) == LOW) {} //wait until clock returns to LOW

    if (digitalRead(datapin) == LOW) {

      if (i < 20) {

        value |= 1 << i;

      }

      if (i == 20) {

        sign = -1;

      }

    }

  }

  result = (value * sign) / 100.00;

  Serial.println(result, 2); //print result with 2 decimals
  if ((-2.55 <= result) && (result <= -2.45)) {
    tone(3, 1000);
    digitalWrite(11, LOW);
    digitalWrite(10, HIGH);
    digitalWrite(9, LOW);
  }
  else if ((-1.35 <= result) && (result <= -1.25)) {

    tone(3, 2000);
    digitalWrite(11, LOW);
    digitalWrite(10, LOW);
    digitalWrite(9, HIGH);

  }     
  else if (result==0.01) {

    tone(3, 3000, 10);
    digitalWrite(11, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(9, HIGH);

  } else {
    noTone(3);
    digitalWrite(11, HIGH);
    digitalWrite(10, LOW);
    digitalWrite(9, LOW);
  }


  //delay(10);

}
