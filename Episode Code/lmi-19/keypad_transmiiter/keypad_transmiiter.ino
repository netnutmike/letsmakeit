#define PIN_D2_INT      0
 
// R06A defines - wired to Digital Arduino pins
// Wire the R06A per this assignment
#define R06A_VT 2    // used for INT0
#define R06A_D0 3
#define R06A_D1 4
#define R06A_D2 5
#define R06A_D3 6
 
int r06a_0, r06a_1, r06a_2, r06a_3 = 0; // storage for data states
int dirty = 0;                          // interrupt has occurred flag
 
// Interrupt Service Routine attached to INT0 vector
void pinD2ISR()
{
    // Provide a visual clue of the interrupt
    digitalWrite(13, !digitalRead(13));  // Toggle LED on pin 13
    // Grab the data states
    r06a_0 = digitalRead(R06A_D0);      // Grab data for later consumption in loop()
    r06a_1 = digitalRead(R06A_D1);
    r06a_2 = digitalRead(R06A_D2);
    r06a_3 = digitalRead(R06A_D3);
    dirty = 1;                          // flag interrupt occurance
}
 
void setup()
{ 
  attachInterrupt(PIN_D2_INT, pinD2ISR, RISING);        // Set D2 interrupt
 
  // setup the R06A decoder connections
  pinMode(R06A_D0, INPUT);
  pinMode(R06A_D1, INPUT);
  pinMode(R06A_D2, INPUT);
  pinMode(R06A_D3, INPUT);
  
  Serial.begin(9600);
}
 
void loop()
{
  if(dirty)
  {
    dirty = 0;              // clear interrupt occurance flag
    Serial.print(r06a_0 ? "HIGH": "LOW ");
    Serial.print(r06a_1 ? "HIGH": "LOW ");
    Serial.print(r06a_2 ? "HIGH": "LOW ");
    Serial.print(r06a_3 ? "HIGH": "LOW ");
    Serial.println("");
  }
}
