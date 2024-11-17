/*

OmniNest ROBOT ARM

Axis1 = 2
Axis2 = 3
Axis3 = 4
Axis4 = 5 MICRO
Axis5 = 6 MICRO
Axis6 = 7 MICRO
PIR = 45
JOYUP/DOWN - X - Pin A0
JOYLEFT/RIGHT - Y - Pin A2

 */


#include<SoftwareSerial.h>
#include<Servo.h>
#include<EEPROM.h>

Servo Ax1;
Servo Ax2;
Servo Ax3;
Servo Ax4;
Servo Ax5;
Servo Ax6;

int Ax1p;
int Ax2p;
int Ax3p;
int Ax4p;
int Ax5p;
int Ax6p;

int JOYXP;
int JOYYP;
int SWITCHP;

int PJOYXP;
int PJOYYP;
int PSWITCHP;

int INCREMENT = 1;

int data1;

const int bytesPerStep = 3;       // PJOYXP, PJOYYP, PSWITCHP
const int eepromStartAddress = 0; // EEPROM start address
int currentStep = 0;              // Tracks the current step

// State tracking
bool isRecording = false; // Recording mode
bool isReplaying = false; // Replay mode
bool buttonPressed = false; // Tracks if button was pressed

// Joystick and switch variables

void setup() {
  // put your setup code here, to run once:

 Serial.begin(9600);

 pinMode(PSWITCHP, INPUT_PULLUP); // Button pin with internal pull-up
 Serial.println("Ready to record or replay.");

 Ax1.attach(2);
 Ax2.attach(3);
 Ax3.attach(4);
 Ax4.attach(5);
 Ax5.attach(6);
 Ax6.attach(7);

 Ax1.write(90);
 Ax2.write(90);
 Ax3.write(90);
 Ax4.write(90);
 Ax5.write(90);
 Ax6.write(90);
 pinMode(45, INPUT);

 pinMode(A0, INPUT);
 pinMode(A2, INPUT);
 pinMode(A4, INPUT);
 pinMode(A6, INPUT);
 pinMode(44, INPUT);
 pinMode(43, INPUT);

 Ax1p = 0;
 Ax2p = 0;
 Ax3p = 0;
 Ax4p = 0;
 Ax5p = 0;
 Ax6p = 0;

}

void loop() {
  // put your main code here, to run repeatedly:

  if (digitalRead(PSWITCHP) == LOW && !buttonPressed) {
    buttonPressed = true; // Debounce
    if (!isRecording && !isReplaying) {
      // Start recording
      isRecording = true;
      currentStep = 0; // Reset step counter
      Serial.println("Recording started...");
    } else if (isRecording) {
      // Stop recording
      isRecording = false;
      Serial.println("Recording stopped.");
    } else if (!isReplaying) {
      // Start replaying
      isReplaying = true;
      Serial.println("Replaying started...");
      replayAlgorithm();
      isReplaying = false;
      Serial.println("Replaying finished.");
    }
  }

  // Reset button state when released
  if (digitalRead(PSWITCHP) == HIGH) {
    buttonPressed = false;
  }

  // Record algorithm if in recording mode
  if (isRecording) {
    recordAlgorithm();
  }

 JOYYP = analogRead(A0);
 JOYXP = analogRead(A2);
 SWITCHP = digitalRead(44);
 int JOYYP1 = map(JOYYP, 0, 1023, 0, 255);
 int JOYXP1 = map(JOYXP, 0, 1023, 0, 255);

 PJOYYP = analogRead(A4);
 PJOYXP = analogRead(A6);
 PSWITCHP = digitalRead(43);
 int PJOYYP1 = map(PJOYYP, 0, 1023, 0, 255);
 int PJOYXP1 = map(PJOYXP, 0, 1023, 0, 255);


 bool a =  digitalRead(45);
 Serial.println(a);
 Serial.println(JOYYP1);
 Serial.println(SWITCHP);
 Serial.println(JOYXP1);

 Serial.println(PJOYYP1);
 Serial.println(PSWITCHP);
 Serial.println(PJOYXP1);

 int count = 1;

 if(count == 1){

   ALGO();

 }

 MOVEMENT();

}

void ALGO(){

 Ax1.write(90);
 Ax2.write(90);
 Ax3.write(90);
 Ax4.write(90);
 Ax5.write(90);
 Ax6.write(90);

}

void MOVEMENT(){

 if(SWITCHP == 1){

   GRIPPER();

 }

 else if(JOYXP >= 175 && INCREMENT == 1){
 
   LEFT();
  
 }

 else if(JOYXP <= 74 && INCREMENT == 1){
 
   RIGHT();
  
 }

 else if(JOYYP >= 175 && INCREMENT == 1){

   DOWN();

 }

 else if(JOYYP <= 74 && INCREMENT == 1){

   UP();

 }
 
}

void LEFT(){

  int CHECK = 1;

 if(CHECK == 1){
  
   while (Ax1p != 180){

     Ax1p++;
     delay(10);
     Ax1.write(Ax1p);
     CHECK = 0;
     return;
   }

 }

 if(Ax1p == 180){
  
   while (Ax4p != 180){

     Ax4p++;
     delay(10);
     Ax4.write(Ax4p);
     CHECK = 0;
     return;

   }

 }

}
void RIGHT(){


 int CHECK = 1;

 if(CHECK == 1){
  
   while (Ax1p != 180){

     Ax1p++;
     delay(10);
     Ax1.write(Ax1p);
     CHECK = 0;
     return;
   }

 }
 
 if(Ax1p == 0){
  
   while (Ax4p != 0){

     Ax4p--;
     delay(10);
     Ax4.write(Ax4p);
     CHECK = 0;
     return;

   }

 }

}

void DOWN(){

 int CHECK = 1;

 if(CHECK == 1){
  
   while (Ax2p != 180){

     Ax2p++;
     delay(10);
     Ax2.write(Ax2p);
     CHECK = 0;
     return;
   }

 }
 
 if(Ax2p == 180){
  
   while (Ax3p != 180){

     Ax3p++;
     delay(10);
     Ax3.write(Ax3p);
     CHECK = 0;
     return;

   }

 }

 if(Ax3p == 180){
  
   while (Ax5p != 180){

     Ax5p++;
     delay(10);
     Ax5.write(Ax5p);
     CHECK = 0;
     return;

   }

 }

}

void UP(){

 int CHECK = 1;

 if(CHECK == 1){
  
   while (Ax2p != 0){

     Ax2p--;
     delay(10);
     Ax2.write(Ax2p);
     CHECK = 0;
     return;
   }

 }
 
 if(Ax2p == 0){
  
   while (Ax3p != 0){

     Ax3p--;
     delay(10);
     Ax3.write(Ax3p);
     CHECK = 0;
     return;

   }

 }

 if(Ax3p == 0){
  
   while (Ax5p != 0){

     Ax5p--;
     delay(10);
     Ax5.write(Ax5p);
     CHECK = 0;
     return;

   }

 }

}

void recordAlgorithm() {

   int address = eepromStartAddress + currentStep * bytesPerStep;

  // Check if EEPROM has space for the next step
  if (address + bytesPerStep > EEPROM.length()) {
    Serial.println("EEPROM full, stopping recording.");
    isRecording = false;
    return;
  }

  // Simulate reading joystick values (replace with actual joystick logic)
  PJOYXP = analogRead(A0) / 4; // Scale 0-1023 to 0-255
  PJOYYP = analogRead(A2) / 4;
  PSWITCHP = digitalRead(43); // Replace with actual pin for switch

  // Save to EEPROM
  EEPROM.update(address, PJOYXP);
  EEPROM.update(address + 1, PJOYYP);
  EEPROM.update(address + 2, PSWITCHP);

  Serial.print("Step ");
  Serial.print(currentStep + 1);
  Serial.print(" recorded: PJOYXP=");
  Serial.print(PJOYXP);
  Serial.print(", PJOYYP=");
  Serial.print(PJOYYP);
  Serial.print(", PSWITCHP=");
  Serial.println(PSWITCHP);

  currentStep++; // Increment step counter
  delay(100);    // Delay to allow joystick adjustment

}

// Replay the recorded algorithm from EEPROM
void replayAlgorithm() {

   for (int i = 0; i < currentStep; i++) {
    int address = eepromStartAddress + i * bytesPerStep;

    // Retrieve values from EEPROM
    PJOYXP = EEPROM.read(address);
    PJOYYP = EEPROM.read(address + 1);
    PSWITCHP = EEPROM.read(address + 2);

    // Print replayed values (replace with actual action logic)
    Serial.print("Step ");
    Serial.print(i + 1);
    Serial.print(" replayed: PJOYXP=");
    Serial.print(PJOYXP);
    Serial.print(", PJOYYP=");
    Serial.print(PJOYYP);
    Serial.print(", PSWITCHP=");
    Serial.println(PSWITCHP);

    delay(100); // Delay before the next step
  }
}

void GRIPPER(){

 int CHECK = 1;

 if(CHECK == 1){
  
   while (Ax6p != 180){

     Ax6p++;
     delay(10);
     Ax6.write(Ax6p);
     CHECK = 0;

   }

 }

 delay(10000);

 if(CHECK == 0){
  
   while (Ax6p != 0){

     Ax6p--;
     delay(10);
     Ax6.write(Ax6p);
     CHECK = 0;

   }

 }

}