const int YellowledPin = 8;  // Scissors LED
const int WhiteledPin = 9;   // Paper LED
const int BlueledPin = 7;    // Rock LED
const int RedledPin = 12;    // Red LED for player lose
const int GreenledPin = 10;  // Green LED for player win

const int BlackbuttonPin = 2;  // Rock Button
const int GreenbuttonPin = 4;  // Paper Button
const int YellowbuttonPin = 6; // Scissors Button

int BlkbuttonState = 0;
int GrbuttonState = 0;
int YbuttonState = 0;

int buttonStateOldBlk = HIGH;
int buttonStateOldGr = HIGH;
int buttonStateOldYe = HIGH;

int dt = 100;
int computerChoice;


void setup() {
  pinMode(YellowledPin, OUTPUT);
  pinMode(WhiteledPin, OUTPUT);
  pinMode(BlueledPin, OUTPUT);
  pinMode(RedledPin, OUTPUT);
  pinMode(GreenledPin, OUTPUT);

  pinMode(BlackbuttonPin, INPUT_PULLUP);
  pinMode(GreenbuttonPin, INPUT_PULLUP);
  pinMode(YellowbuttonPin, INPUT_PULLUP);

  randomSeed(analogRead(0)); //random number generator

  Serial.begin(9600);
}

void loop() {
  BlkbuttonState = digitalRead(BlackbuttonPin);
  GrbuttonState = digitalRead(GreenbuttonPin);
  YbuttonState = digitalRead(YellowbuttonPin);

  computerChoice = random(3); 

  digitalWrite(YellowledPin, LOW);
  digitalWrite(WhiteledPin, LOW);
  digitalWrite(BlueledPin, LOW);
  digitalWrite(RedledPin, LOW);
  digitalWrite(GreenledPin, LOW);

  // First case: Player chooses Rock
  if (buttonStateOldBlk == HIGH && BlkbuttonState == LOW) {
    if (computerChoice == 0) {
      digitalWrite(WhiteledPin, HIGH);  //Computer chooses Paper (Player loses)
      digitalWrite(RedledPin, HIGH);    //Turn on Red LED 
    } else if (computerChoice == 1) {
      digitalWrite(YellowledPin, HIGH);  //Computer chooses Scissors (Player wins)
      digitalWrite(GreenledPin, HIGH);   //Turn on Green LED 
    } else {
      digitalWrite(BlueledPin, HIGH);  //Computer chooses Rock (Draw)
    }
    delay(1000);
  }
  buttonStateOldBlk = BlkbuttonState;

  // Second case: Player chooses Paper
  if (buttonStateOldGr == HIGH && GrbuttonState == LOW) {
    if (computerChoice == 0) {
      digitalWrite(YellowledPin, HIGH);  //Computer chooses Scissors (Player loses)
      digitalWrite(RedledPin, HIGH);    //Turn on Red LED 
    } else if (computerChoice == 1) {
      digitalWrite(BlueledPin, HIGH);  //Computer chooses Rock (Player wins)
      digitalWrite(GreenledPin, HIGH);   //Turn on Green LED 
    } else {
      digitalWrite(WhiteledPin, HIGH);  //Computer chooses Paper (Draw)
    }
    delay(1000);
  }
  buttonStateOldGr = GrbuttonState;

  // Third case: Player chooses Scissors
  if (buttonStateOldYe == HIGH && YbuttonState == LOW) {
    if (computerChoice == 0) {
      digitalWrite(BlueledPin, HIGH);  //Computer chooses Rock (Player loses)
      digitalWrite(RedledPin, HIGH);    //Turn on Red LED 
    } else if (computerChoice == 1) {
      digitalWrite(WhiteledPin, HIGH);  //Computer chooses Paper (Player wins)
      digitalWrite(GreenledPin, HIGH);   //Turn on Green LED 
    } else {
      digitalWrite(YellowledPin, HIGH);  //Computer chooses Scissors (Draw)
    }
    delay(1000);
  }
  buttonStateOldYe = YbuttonState;

  digitalWrite(YellowledPin, LOW);
  digitalWrite(WhiteledPin, LOW);
  digitalWrite(BlueledPin, LOW);
  digitalWrite(RedledPin, LOW);
  digitalWrite(GreenledPin, LOW);

  delay(dt);
}
