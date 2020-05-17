/*
Transpulmonar sensor
 version 3.3.4
 
 Authors:
 Francisco Jose PARRILLA GOMEZ
 Alvaro JANSA MAS
 Marc ESTUDILLO
 Victor BOUTONNET ANTELO
 Andres PARRILLA GOMEZ
 
 Description:
 Transpulmonar sensor using 2 pressure sensors, Arduino MEGA and TFT LCL Elegoo 2.8" touchscreen
 
 modifs:
 v1 2020-04-27 : initial version
 v2 2020-04-30 : analog reference to 3.3V, TFT added, compiler options and bug correction
 v3.0 2020-05-02 : graphics improvements
 v3.1 2020-05-02 : bug corrections
 v3.1.1 2020-05-02 : more bug corrections
 v3.1.2 2020-05-03 : graphics improvements
 v3.2 2020-05-04 : graphics improvements
 v3.3 2020-05-04 : round values to integers (round to 0.5 commented out)
 v3.3.1 2020-05.06 : back to float values
 v3.3.2 2020-05.06 : rounding compiler options added
 v3.3.3 2020-05-09 : changed PL avg to Ratio
 v3.3.4 2020-05-09 : bug fix
 */




// User defined compiling parameters
// *********************************
#define ARDUINOBOARD 'M' // must be 'U' for UNO or 'M' for MEGA. Warning: with UNO, fake values!
#define DEBUG 0 // must be 0 or 1
#define USERCOM 'B' // must be 'B' for BUTTON, 'S' for SERIAL or 'T' for TOUCHSCREEN ( TOUCHSCREEN TODO: not working as of 2.6)
#define ROUNDOPTION 0 //must be 1 to integer values, 5 for .5 rounding or 0 for max resolution
// *********************************





// TFT
#include <Elegoo_GFX.h>
#include <Elegoo_TFTLCD.h>
//#include <stdint.h>
#include <TouchScreen.h>

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4
#define YP A1
#define XM A2
#define YM 7
#define XP 6

#define GREY    0x8410
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#define MINPRESSURE 10
#define MAXPRESSURE 1000

#if USERCOM=='S'
#define DEBUG 1
#endif

Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
#if USERCOM=='T'
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
#endif

// Pin definitions
#if ARDUINOBOARD=='M'
const int PesPin(A13);
const int PawPin(A14);
#endif

#if USERCOM=='B'
const int buttonPin = 21; // Warning, I2C pin too...
unsigned long timeButton(0);
#endif

// Sensors characteristics
int PesVDefaultOffset(512);
int PawVDefaultOffset(512);
int PesVOffset(PesVDefaultOffset); 
int PawVOffset(PawVDefaultOffset);

// gain definitions for class A TE sensors (MS4525 - DS3A001DP)
//for 3V supply and AREF=3.3V
float PesGain(70.31/409); //1 psi = 70,31 cmH2O
float PawGain(70.31/409);

//Data treatment parameters
int nMeasures(10); // number of measures to average (low-cost filtering...)
float precision(0.);
int tmp(0.);

//current values
int PesV(0); // V stands for Volts (direct tension measured)
int PawV(0);
int PesVtmp(0);
int PawVtmp(0);
int PesVmax(0);
int PesVmin(1023);
int PawVmax(0);
int PawVmin(1023);
float Pes(0.);
float Paw(0.);
float PL(0.);
float PLmax(0.);
float PLmin(0.);
float PLavg(0.);
float Pesmax(0.);
float Pesmin(0.);
float Pawmax(0.);
float Pawmin(0.);
int counterMeasures(0);

// behavior variables
bool measuring=false;
//TSPoint tcPoint;

// plotting variables
int HPos (31+250); // pixel corresponding to time=0 + plotting area width
int lastHPos(31+250);

unsigned int Pes2plot(0);
unsigned int Paw2plot(0);
unsigned int PL2plot(0);
unsigned int lastPes2plot(0);
unsigned int lastPaw2plot(0);
unsigned int lastPL2plot(0);

// time variables
float tini(0); //measure start time
float tcurrent(0); //measure start time
int screenNumber(0); // times screen erased and shown again (multiples of 10s)

void setup() {

  // Touchscreen ini
  tft.reset();
  tft.begin(0x9341);
  tft.fillScreen(BLACK);
  tft.setRotation(1);

#if DEBUG==1 || USERCOM=='U'
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
#endif

#if USERCOM=='B'
  pinMode(buttonPin, INPUT_PULLUP);
#if ARDUINOBOARD=='M'
  attachInterrupt(2, buttonPressed, FALLING); // 2 stands for pin 21 (number 2 of Mega board interrupts)
#elif ARDUINOBOARD=='U'
  tft.fillScreen(BLACK);
  tft.setCursor(40,100);
  tft.println("ERROR:Opotions defined are not compatible (UNO board with BUTTON communication");
#endif
#endif



  // Pressure sensors autozero
  analogReference(EXTERNAL);
#if ARDUINOBOARD=='M'
  pinMode(PesPin, INPUT);
  pinMode(PawPin, INPUT);
#endif

  PesVtmp=0;
  PawVtmp=0;
  PesVmax=0;
  PesVmin=1023;
  PawVmax=0;
  PawVmin=1023;
  PesVOffset=0;
  PawVOffset=0;
  for(int i = 0; i < nMeasures; i++){
#if ARDUINOBOARD=='M'
    PesVtmp=analogRead(PesPin);
    PawVtmp=analogRead(PawPin);
#elif ARDUINOBOARD=='U'
    PesVtmp=512+int(random(-3,4)); //UNO fake values
    PawVtmp=520+int(random(-3,4)); //UNO fake values
#endif
    PesVOffset+=PesVtmp;
    PawVOffset+=PawVtmp;
    PesVmax=max(PesVmax,PesVtmp);
    PesVmin=min(PesVmin,PesVtmp);
    PawVmax=max(PawVmax,PawVtmp);
    PawVmin=min(PawVmin,PawVtmp);
    delay(10);
  }
  PesVOffset=PesVOffset/nMeasures;
  PawVOffset=PawVOffset/nMeasures;

#if DEBUG==1
  Serial.println("AUTOZERO");
  if(abs(PesVOffset-PesVDefaultOffset)>50){
    Serial.print("Warning: check autozero for Pes");
  }
  Serial.println("PesVOffset="+String(PesVOffset));
  if(abs(PawVOffset-PawVDefaultOffset)>50){
    Serial.print("Warning: check autozero for Paw");
  }
  Serial.println("PawVOffset="+String(PawVOffset));
  if(PesVmax-PesVmin>50){
    Serial.print("Warning: instable measures of Pes: max="+String(PesVmax)+" ; min="+String(PesVmin));
  }
  if(PawVmax-PawVmin>50){
    Serial.print("Warning: instable measures of Paw: max="+String(PawVmax)+" ; min="+String(PawVmin));
  }
#endif

  tft.setCursor(20,100);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.println("Autozero done");
  tft.setCursor(20,120);
  tft.setTextSize(1);
  precision=max(max(PesGain*float(PesVmax-PesVmin),PawGain*float(PawVmax-PawVmin)),0.2);
  tft.println("precision:+- "+String(round(precision*10.)/10)+"."+String(round(precision*10.)%10)+" cmH2O");
#if DEBUG==1
  Serial.print("PesVmax: ");
  Serial.println(PesVmax);
  Serial.print("PesVmin: ");
  Serial.println(PesVmin);
  Serial.print("PawVmax: ");
  Serial.println(PawVmax);
  Serial.print("PawVmin: ");
  Serial.println(PawVmin);
  Serial.print("precision: ");
  Serial.println(precision);
  Serial.print("round(precision*10.)/10: ");
  Serial.println(round(precision*10.)/10);
  Serial.print("round(precision*10.)%10: ");
  Serial.println(round(precision*10.)%10);
#endif
  delay(2000);
  tft.fillScreen(BLACK);

  //X Y Axis
  tft.fillRect(30,15,1,176,WHITE); // Y
  tft.fillRect(30,143,272,1,WHITE); // X

  //graph key
  tft.setCursor(290,30);
  tft.setTextColor(MAGENTA);
  tft.setTextSize(1);
  tft.println("Pes");

  tft.setCursor(290,20);
  tft.setTextColor(CYAN);
  tft.setTextSize(1);
  tft.println("Paw");

  tft.setCursor(290,40);
  tft.setTextColor(GREEN);
  tft.setTextSize(1);
  tft.println("PL");


  //X axis divider
  for(int i=56;i<=281;i+=25){
    tft.drawLine(i,142,i,145,WHITE);
  }
  //Y axis divider
  //tft.drawLine(25,15,30,15,WHITE); // 60cmH2O
  tft.drawLine(25,28,30,28,WHITE); // 50cmH2O
  tft.drawLine(25,51,30,51,WHITE); // 40cmH2O
  tft.drawLine(25,74,30,74,WHITE); // 30cmH2O
  tft.drawLine(25,97,30,97,WHITE); // 20cmH2O
  tft.drawLine(25,120,30,120,WHITE); // 10cmH2O
  tft.drawLine(25,143,30,143,WHITE); // 00cmH2O
  tft.drawLine(25,166,30,166,WHITE); // -10cmH2O
  tft.drawLine(25,189,30,189,WHITE); // -20cmH2O

  tft.setTextColor(WHITE);
  tft.setTextSize(1);

  tft.setCursor(110,3);
  tft.println("Transpulmonar P Sensor ");

  tft.setCursor(2,3);
  tft.println("cmH2O");

  tft.setCursor(260,163);
  tft.println("Time(s)");

  // Y scale
  tft.setCursor(5,28);
  tft.println("+50");

  tft.setCursor(5,51);
  tft.println("+40");

  tft.setCursor(5,74);
  tft.println("+30");

  tft.setCursor(5,97);
  tft.println("+20");

  tft.setCursor(5,120);
  tft.println("+10");

  tft.setCursor(5,143);
  tft.println("0");

  tft.setCursor(5,166);
  tft.println("-10");

  tft.setCursor(5,189);
  tft.println("-20");

}
void loop() {

  // reset max, min, average values
  PLmax=-100;
  PLmin=100;
  Pesmax=-100;
  Pesmin=100;
  Pawmax=-100;
  Pawmin=100;
  PLavg=0;
  counterMeasures=0;

  tft.fillRect(90,198,200,10,BLACK);
  tft.setCursor(100,200);
  tft.setTextColor(RED);
  tft.println("Pulse para nueva medicion"); //"tap for new measuring"
  tft.setTextColor(WHITE);

  while(!measuring){
#if DEBUG==1
    Serial.println("waiting");
#endif
#if USERCOM=='S'
    if (Serial.available() > 0) {
      char inChar = (char)Serial.read(); 
      if (inChar == 'a') {
        measuring=true;
      }
    }
#elif USERCOM=='T'
    TSPoint tcPoint = ts.getPoint();
    //Serial.println(tcPoint.z);
    if (tcPoint.z > MINPRESSURE && tcPoint.z < MAXPRESSURE) {
      measuring=true;
      //Serial.println("start");
    }
#elif USERCOM=='B'
    // coded in interrupt function
#else
    tft.fillScreen(BLACK);
    tft.setCursor(40,100);
    tft.println("ERROR:No communication defined");
#endif
    delay(100);

  }
#if DEBUG==1
  digitalWrite(13,HIGH);
  Serial.println("starting measures");
#endif

  //starting time
  tini=millis()/1000.; //measure start time
  doMeasure(Pes,Paw,PL);
  Pes2plot=map(Pes,0,50,143,28);
  Paw2plot=map(Paw,0,50,143,28);
  PL2plot=map(PL,0,50,143,28);
  HPos=31+250;
  ;

  //restart screen
  tft.fillRect(31,0,280,215,BLACK); // plot
  tft.setCursor(110,3);
  tft.fillRect(0,198,320,50,BLACK); //max, min data
  //tft.println("Transpulmonar P Sensor ");
  tft.fillRect(33,185,320,100,BLACK);
  tft.fillRect(30,143,272,1,WHITE); // X
  screenNumber=0;  

  tft.setCursor(290,30);
  tft.setTextColor(MAGENTA);
  tft.setTextSize(1);
  tft.println("Pes");

  tft.setCursor(290,20);
  tft.setTextColor(CYAN);
  tft.setTextSize(1);
  tft.println("Paw");

  tft.setCursor(290,40);
  tft.setTextColor(GREEN);
  tft.setTextSize(1);
  tft.println("PL");

  // Loop : measurements until interaction
  while(measuring){ // measuring should change on interaction (touchscreen or button click, serial com)

    // store former values
    lastPes2plot=Pes2plot;
    lastPaw2plot=Paw2plot;
    lastPL2plot=PL2plot;
    lastHPos=HPos;

    tcurrent=millis()/1000.-tini;
    HPos=31+long(tcurrent*25.)%250; //TODO to improve and verify...



    if(long(tcurrent)/10 +1 > screenNumber){ // create new screen
      screenNumber++;

#if DEBUG==1
      Serial.print("screen number : ");
      Serial.println(screenNumber);
#endif
      
      tft.fillRect(31,0,259,215,BLACK);
  tft.setCursor(110,3);
  tft.setTextColor(WHITE);
  tft.println("Transpulmonar P Sensor ");
      tft.fillRect(0,198,320,50,BLACK);
      tft.fillRect(33,185,320,100,BLACK);
      tft.fillRect(30,143,272,1,WHITE); // X
      for(int i=55;i<=280;i+=25){
        tft.drawLine(i,142,i,145,WHITE);
      }
      tft.setCursor(100,200);
      tft.setTextColor(RED);
      tft.println("Pulse para detener la medicion"); //"tap for new measuring"
      tft.setTextColor(WHITE);
      tft.setCursor(260,163);
      tft.println("Time(s)");
      tft.setCursor(34,153);
      tft.println(screenNumber*10-10);
      tft.setCursor(151,153);
      tft.println(screenNumber*10-5);
      tft.setCursor(276,153);
      tft.println(screenNumber*10);

      lastHPos=31;//lastHPos-250; //for better graphics (avoid ugly lines)
    }

    // read values
    doMeasure(Pes,Paw,PL);
    PLmax=max(PLmax,PL);
    PLmin=min(PLmin,PL);
    PLavg+=PL;
    Pesmax=max(Pesmax,Pes);
    Pesmin=min(Pesmin,Pes);
    Pawmax=max(Pawmax,Paw);
    Pawmin=min(Pawmin,Paw);
    counterMeasures++;

    // mapping pressure values to screen coordinates
    Pes2plot=map(Pes,0,50,143,28);
    Paw2plot=map(Paw,0,50,143,28);
    PL2plot=map(PL,0,50,143,28);

    // plot pressures on screen
    /*tft.fillCircle(HPos,Pes2plot,1,MAGENTA);
     tft.fillCircle(HPos,Paw2plot,1,CYAN);
     tft.fillCircle(HPos,PL2plot,1,GREEN);*/
    tft.drawLine(lastHPos,lastPes2plot,HPos,Pes2plot,MAGENTA);
    tft.drawLine(lastHPos,lastPaw2plot,HPos,Paw2plot,CYAN);
    tft.drawLine(lastHPos,lastPL2plot,HPos,PL2plot,GREEN);

    /*if(tcurrent>27){
     measuring=false;
     }*/

#if USERCOM=='S'
    if (Serial.available() > 0) {
      char inChar = (char)Serial.read(); 
      if (inChar == 'a') {
        measuring=false;
      }
    }
#elif USERCOM=='T'
    TSPoint tcPoint = ts.getPoint();
    //Serial.println(tcPoint.z);
    if (tcPoint.z > MINPRESSURE && tcPoint.z < MAXPRESSURE) {
      measuring=false;
      //Serial.println("start");
    }
#elif USERCOM=='B'
    // coded in interrupt function
#else
    tft.fillScreen(BLACK);
    tft.setCursor(40,100);
    tft.println("ERROR:No communication defined");
#endif

  }

#if DEBUG==1
  Serial.println("measures end");
  digitalWrite(13,LOW);
#endif
  // end of PLavg computing
  PLavg/=counterMeasures;

  //text for new measure
  tft.fillRect(33,185,320,100,BLACK);
  tft.setCursor(100,200);
  tft.setTextColor(RED);
  tft.println("Pulse para detener la medicion"); //"tap for new measuring"

  //printing PL max, min, avg & Paw Pes PL delta values
  tft.setTextColor(CYAN);
  tft.setCursor(10,220);
  tft.println("DeltaPaw: ");
  tft.setCursor(70,220);
  #if ROUNDOPTION==1
  tft.println(String(round(Pawmax-Pawmin)));
  #elif ROUNDOPTION==5
  tft.println(String(round(round2dot5(Pawmax-Pawmin)*10.)/10)+"."+String(round(round2dot5(Pawmax-Pawmin)*10.)%10));
  #elif ROUNDOPTION==0
  tft.println(Pawmax-Pawmin);
  #else
  tft.println("???");
  #endif

  tft.setTextColor(MAGENTA);
  tft.setCursor(10,230);
  tft.println("DeltaPes: ");
  tft.setCursor(70,230);
  #if ROUNDOPTION==1
  tft.println(String(round(Pesmax-Pesmin)));
  #elif ROUNDOPTION==5
  tft.println(String(round(round2dot5(Pesmax-Pesmin)*10.)/10)+"."+String(round(round2dot5(Pesmax-Pesmin)*10.)%10));
  #elif ROUNDOPTION==0
  tft.println(Pesmax-Pesmin);
  #else
  tft.println("???");
  #endif

  tft.setTextColor(GREEN);
  tft.setCursor(120,220);
  tft.println("DeltaPL: ");
  tft.setCursor(170,220);
  #if ROUNDOPTION==1
  tft.println(String(round(PLmax-PLmin)));
  #elif ROUNDOPTION==5
  tft.println(String(round(round2dot5(PLmax-PLmin)*10.)/10)+"."+String(round(round2dot5(PLmax-PLmin)*10.)%10));
  #elif ROUNDOPTION==0
  tft.println(PLmax-PLmin);
  #else
  tft.println("???");
  #endif

  tft.setTextColor(WHITE);
  tft.setCursor(120,230);
  tft.println("Ratio: ");
  tft.setCursor(170,230);
  if(((Pesmax-Pesmin)/(Pawmax-Pawmin)>=0.8) && ((Pesmax-Pesmin)/(Pawmax-Pawmin))<=1.2))
  {tft.setTextColor(GREEN);}
  else{tft.setTextColor(YELLOW);}
  #if ROUNDOPTION==1
  tft.println(String(round((Pesmax-Pesmin)/(Pawmax-Pawmin))));
  #elif ROUNDOPTION==5
  tft.println(String(round(round2dot5(PLavg)*10.)/10)+"."+String(round(round2dot5((Pesmax-Pesmin)/(Pawmax-Pawmin))*10.)%10));
  #elif ROUNDOPTION==0
  tft.println((Pesmax-Pesmin)/(Pawmax-Pawmin));
  #else
  tft.println("???");
  #endif
  
  tft.setTextColor(GREEN);
  tft.setCursor(230,230);
  tft.println("PL Min: ");
  tft.setCursor(280,230);
  #if ROUNDOPTION==1
  tft.println(String(round(PLmin)));
  #elif ROUNDOPTION==5
  tft.println(String(round(round2dot5(PLmin)*10.)/10)+"."+String(round(round2dot5(PLmin)*10.)%10));
  #elif ROUNDOPTION==0
  tft.println(PLmin);
  #else
  tft.println("???");
  #endif
  

  tft.setCursor(230,220);
  tft.println("PL Max: ");
  tft.setCursor(280,220);
  #if ROUNDOPTION==1
  tft.println(String(round(PLmax)));
  #elif ROUNDOPTION==5
  tft.println(String(round(round2dot5(PLmax)*10.)/10)+"."+String(round(round2dot5(PLmax)*10.)%10));
  #elif ROUNDOPTION==0
  tft.println(PLmax);
  #else
  tft.println("???");
  #endif
  
  tft.setTextColor(WHITE); //back to default color

}


#if USERCOM=='B' //debounce
void buttonPressed(){
  if(millis()-timeButton>500){
    measuring=!measuring;
    timeButton=millis();
  }
}
#endif

void doMeasure(float & Pes,float & Paw,float & PL){
  // read values
  PesVtmp=0;
  PawVtmp=0;
  for(int i = 0; i < nMeasures; i++){
#if ARDUINOBOARD=='M'
    PesVtmp+=analogRead(PesPin);
    PawVtmp+=analogRead(PawPin);
#elif ARDUINOBOARD=='U' //Warning: fake values for debug without MEGA board, using an UNO
    PesVtmp+=500+50*sin(tcurrent*6./3.)-2*cos(tcurrent*6./.37);
    PawVtmp+=600+80*sin(tcurrent*6./3.+.3)+10*cos(tcurrent*6./.37);
#endif

    delay(10);
  }
  Pes=PesGain*float((PesVtmp/nMeasures)-PesVOffset);
  Paw=PawGain*float((PawVtmp/nMeasures)-PawVOffset);

  // compute values : Pes, Paw, Pt, counter, max, min, average
  PL=Paw-Pes;
#if DEBUG==1
  Serial.println(Pes);
  Serial.println(Paw);
  Serial.println(PL);
#endif
}

#if ROUNDOPTION==5
float round2dot5(float value){
  tmp=round(value*10.);
  if(tmp%10<=2){
    tmp=tmp-tmp%10;
  }
  else if(tmp%10>=3 && tmp%10<=7) {
    tmp=tmp+5-tmp%10;
  }
  else{
    tmp=tmp+10-tmp%10;
  }
  return(float(tmp)/10.);
}
#endif
