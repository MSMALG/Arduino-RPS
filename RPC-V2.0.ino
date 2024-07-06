#include <LiquidCrystal.h>

int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int RedledPin = 2;    //Red LED for player's loss
const int GreenledPin = 3;  //Green LED for player's win

const int BlackbuttonPin = 4;  //Rock Button
const int GreenbuttonPin = 5;  //Paper Button
const int YellowbuttonPin = 6; //Scissors Button

int BlkbuttonState = HIGH;
int GrbuttonState = HIGH;
int YbuttonState = HIGH;

int buttonStateOldBlk = HIGH;
int buttonStateOldGr = HIGH;
int buttonStateOldYe = HIGH;

int dt = 100;
int bt = 1000;
int computerChoice;

void introMssg() {
  lcd.setCursor(0, 0);
  lcd.print("Welcome Player!");
  delay(1000);
  lcd.clear();
  delay(500);
  lcd.print("Press a button");
  lcd.setCursor(0, 1);
  lcd.print("to play!");
  delay(2000);

  lcd.clear();
  delay(500);
  lcd.setCursor(0, 0);
  lcd.print("Black=Rock,");
  lcd.setCursor(0, 1);
  lcd.print("Green=Paper,");
  delay(2000);
  lcd.clear();
  delay(500);
  lcd.setCursor(0, 0);
  lcd.print("Yellow=Scissors");
  delay(2000);
}

void display_waiting_message() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Waiting for");
  lcd.setCursor(0, 1);
  lcd.print("player's move...");
  delay(bt);
}

void display_computer_choice(int choice) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Computer chose:");
  lcd.setCursor(0, 1);

  if (choice == 0)
  {
    lcd.print("Rock");
  } else if (choice == 1)
  {
    lcd.print("Paper");
  } 
  else if (choice == 2) 
  {
    lcd.print("Scissors");
  }
}

void game_status(String status) {
  if (status == "win") 
  {
    digitalWrite(GreenledPin, HIGH);
  } 
  else if (status == "lose") 
  {
    digitalWrite(RedledPin, HIGH);
  }
  else
  {
    digitalWrite(GreenledPin, HIGH);
    digitalWrite(RedledPin, HIGH);
  }
  delay(bt); 
}

void setup() {
  lcd.begin(16, 2);

  pinMode(RedledPin, OUTPUT);
  pinMode(GreenledPin, OUTPUT);

  pinMode(BlackbuttonPin, INPUT_PULLUP);
  pinMode(GreenbuttonPin, INPUT_PULLUP);
  pinMode(YellowbuttonPin, INPUT_PULLUP);

  randomSeed(analogRead(0)); //Random number generator
  
  introMssg();
  lcd.clear();
  display_waiting_message();
}

void loop() {
  BlkbuttonState = digitalRead(BlackbuttonPin);
  GrbuttonState = digitalRead(GreenbuttonPin);
  YbuttonState = digitalRead(YellowbuttonPin);

  digitalWrite(GreenledPin, LOW);
  digitalWrite(RedledPin, LOW);

  computerChoice = random(3);

  //First Case: Player chooses Rock
  if (BlkbuttonState == LOW && buttonStateOldBlk == HIGH) 
  {
    buttonStateOldBlk = LOW;
    display_computer_choice(computerChoice);

    if (computerChoice == 0)  //Computer chooses Rock
    {
      game_status("draw");
    } 
    else if (computerChoice == 1)  //Computer chooses Paper
    {
      game_status("lose");
    } 
    else if (computerChoice == 2) //Computer chooses Scissors
    {
      game_status("win");
    }
  }
  else if (BlkbuttonState == HIGH && buttonStateOldBlk == LOW) //Resetting the button 
  {
    buttonStateOldBlk = HIGH;
  }

  //Second Case: Player chose paper
  if (GrbuttonState == LOW && buttonStateOldGr == HIGH) 
  {
    buttonStateOldGr = LOW;
    display_computer_choice(computerChoice);

    if (computerChoice == 0)  //Computer chooses rock
    {
      game_status("win");
    } 
    else if (computerChoice == 1) //Computer chooses paper
    {
      game_status("draw");
    } 
    else if (computerChoice == 2) //Computer chooses scissors
    {
      game_status("lose");
    }
  }
  else if (GrbuttonState == HIGH && buttonStateOldGr == LOW) //Resetting the button
  {
    buttonStateOldGr = HIGH;
  }

  //Third case: player chooses Scissors
  if (YbuttonState == LOW && buttonStateOldYe == HIGH) 
  {
    buttonStateOldYe = LOW;
    display_computer_choice(computerChoice);

    if (computerChoice == 0) //Computer chooses Rock
    {
      game_status("lose");
    }
    else if (computerChoice == 1) //Computer chooses Paper
    {
      game_status("win");
    } 
    else if (computerChoice == 2) //Computer chooses Scissors
    {
      game_status("draw");
    }
  } 
  else if (YbuttonState == HIGH && buttonStateOldYe == LOW) //Resetting the button
  {
    buttonStateOldYe = HIGH;
  }

}
