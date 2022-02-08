// Direct Drive Turntable using Arduino Uno and TMC2209
// Created by: Kasidej Khunvattanakarn @ 2020-2021
// https://github.com/ksdj55/dd_turntable
// Modified by isoniks @2022
// https://github.com/isoniks/directdrive
// Licensed under GNU General Public License v3.0


#define LED_PIN 13 // onboard LED
#define M_EN 6 // Enable pin - connect to EN pin on TMC2209
#define M_ST 5 // Step pin - connect to STEP pin on TMC2209
#define M_DR 4 // Direction pin - connect to DIR pin on TMC2209

bool  toggle1 = 0;
long  startspeed = 65000;
long  currentspeed = 65000;
float acc_rate = 0.008;
float acc_pow = 20;
// reference values for setspeed: 33.3 RPM = 8960, 45 RPM = 6632, 68 RPM = 3626
long  setspeed = 9045; //adjusted value - feel free to modify to achieve desired RPM
bool  start = true;
bool  clock_start = true; 

void setup() {
  Serial.begin(115200);
  Serial.println("Started");
  pinMode(LED_PIN, OUTPUT);
  pinMode(M_ST, OUTPUT);
  pinMode(M_DR, OUTPUT);
  pinMode(M_EN, OUTPUT);
  digitalWrite(M_EN, LOW);
  digitalWrite(M_DR, HIGH);

  
  cli();      //stop interrupts 
              //set timer1 interrupt at 1Hz
  TCCR1A = 0; // set entire TCCR1A register to 0
  TCCR1B = 0; // same for TCCR1B
  TCNT1  = 0; //initialize counter value to 0
              // set compare match register for 1hz increments
              //OCR1A = 8955;//8955;//9000;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  OCR1A = startspeed;
             // turn on CTC mode
  TCCR1B |= (1 << WGM12);
            // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS10);  
            // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  sei();    //allow interrupts
}

ISR(TIMER1_COMPA_vect){   //timer1 interrupt 1Hz toggles pin 13 (LED)
                          //generates pulse wave of frequency 1Hz/2 = 0.5kHz (takes two cycles for full wave- toggle high then toggle low)
  if(clock_start) {
    if (toggle1){
      digitalWrite(M_ST,HIGH);
      toggle1 = 0;
    }else{
      digitalWrite(M_ST,LOW);
      toggle1 = 1;
    }
  }
}


void loop() { 
  handle_acc();
  delay(50);
}

void handle_acc() {
  float acc_mlp = 1.0 + (((float)currentspeed / startspeed) * acc_pow);
  if(setspeed > currentspeed) {                     //DECELERATE
    if((currentspeed + (currentspeed * acc_rate * acc_mlp)) >= setspeed) {
      currentspeed = setspeed;
    }else{
      currentspeed += currentspeed * acc_rate * acc_mlp;
    }
    if(currentspeed >= startspeed && !start) {
        digitalWrite(M_EN, HIGH);
        clock_start = false;
    }
    OCR1A = currentspeed;
    Serial.println((String)currentspeed);
  } else if (setspeed < currentspeed && start) {    //ACCELERATE
    if((currentspeed - (currentspeed * acc_rate  * acc_mlp)) <= setspeed) {
      currentspeed = setspeed;
    }else {
      currentspeed -= currentspeed * acc_rate * acc_mlp;
    }
    OCR1A = currentspeed;
    Serial.println((String) currentspeed);
  }
}
