
/*
 * MFRC522 - Library to use ARDUINO RFID MODULE KIT 13.56 MHZ WITH TAGS SPI W AND R BY COOQROBOT.
 * The library file MFRC522.h has a wealth of useful info. Please read it.
 * The functions are documented in MFRC522.cpp.
 *
 * Based on code Dr.Leong   ( WWW.B2CQSHOP.COM )
 * Created by Miguel Balboa (circuitito.com), Jan, 2012.
 * Rewritten by Søren Thing Andersen (access.thing.dk), fall of 2013 (Translation to English, refactored, comments, anti collision, cascade levels.)
 * Extended by Tom Clement with functionality to write to sector 0 of UID changeable Mifare cards.
 * 
 * Released into the public domain.
 *
 
 ----------------------------------------------------------------------------- Nicola Coppola
 * Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno           Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 *
 */

#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

/* Set your new UID here! */
#define NEW_UID {0xDE, 0xAD, 0xBE, 0xEF}
#define SS_PIN 53
#define RST_PIN 5


MFRC522 mfrc522(SS_PIN, RST_PIN);        // Create MFRC522 instance.
MFRC522::MIFARE_Key key;
byte heba[1]={20};
byte israa[1]={4};
int hebamoney=50;
int israamoney=40;



Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards
int pos = 0;
int i =0;// variable to store the servo position



int Senval=0;
int Senval2=0;
int Senpin=A0;
int Senpin2=A1;
int bright1 = 0;
int bright2 =0;


void setup() {
        
        Serial.begin(9600);// Initialize serial communications with the PC
        pinMode(12,OUTPUT);
        pinMode(13,OUTPUT);
         myservo.attach(9);  // attaches the servo on pin 9 to the servo object
        while (!Serial);           // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
        SPI.begin();               // Init SPI bus
        mfrc522.PCD_Init();        // Init MFRC522 card
        Serial.println(F("Warning: this example overwrites the UID of your UID changeable card, use with care!"));
        
        // Prepare key - all keys are set to FFFFFFFFFFFFh at chip delivery from the factory.
        for (byte i = 0; i < 6; i++) {
                key.keyByte[i] = 0xFF;
        }
}



void loop() {
  pressure ();
  
        // Look for new cards, and select one if present
        if ( ! mfrc522.PICC_IsNewCardPresent() || ! mfrc522.PICC_ReadCardSerial() ) {
            delay(50);
            return;
        }
        
        // Now a card is selected. The UID and SAK is in mfrc522.uid.
        
        // Dump UID
        Serial.print(F("Card UID:"));
         Serial.println(mfrc522.uid.uidByte[0]);
                if(mfrc522.uid.uidByte[0]==heba[0]&&(bright1==0||bright2==0)){
                   i=1;
                Serial.println("Heba");
                if(hebamoney<10){
                  Serial.println("No Enough Money");
                  }
                  else{
                  //  pressure();
                  hebamoney=hebamoney-10;
                    if (i==1){
                       servo();
                          i=0;
                               }
                               
                    }
                }
                if(mfrc522.uid.uidByte[0]==israa[0]&&(bright1==0||bright2==0)){
                  i=1;
                
                Serial.println("Israa");if(israamoney<10){
                  Serial.println("No Enough Money");
                  }
                  else{
                   // pressure();
                  israamoney=israamoney-10;
                  if (i==1){
                       servo();
                          i=0;
                               }
                    }
                }
       
        
        Serial.println();
        
         delay(2000);

}

void servo(){
    for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);     
    // waits 15ms for the servo to reach the position
  }
  for (pos = 90; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);  
    //Serial.println ("ana hnaaa");// tell servo to go to position in variable 'pos'
    delay(20); 

    
     // waits 15ms for the servo to reach the position
  }
}

void pressure(){
    Senval=analogRead(Senpin);
    Senval2=analogRead(Senpin2);

    if(Senval>=10 && Senval<=600){
    digitalWrite(13, HIGH);
    bright1 =1; //first car parked
    }
    else{
     digitalWrite(13, LOW);
      bright1 =0;
     
    }

     if(Senval2>=10 && Senval2<=600){
    digitalWrite(12, HIGH);
    bright2 =1;} 
    else{
     digitalWrite(12, LOW);
     bright2 =0;
    }
    Serial.println(Senval);
    
    Serial.println(Senval2);

    if (bright1==1&&bright2==1){
      Serial.println("Sorry ,There is no place available");
      }
    

    delay(200);}

