    // code for max 7219 from maxim

     
    int dataIn = 2;
    int load = 3;
    int clock = 4;
     
    int maxInUse = 1;    //change this variable to set how many MAX7219's you'll use
     
    int e = 0;           // just a varialble
     
    int cnum = 0;
                         // define max7219 registers
    byte max7219_reg_noop        = 0x00;
    byte max7219_reg_digit0      = 0x01;
    byte max7219_reg_digit1      = 0x02;
    byte max7219_reg_digit2      = 0x03;
    byte max7219_reg_digit3      = 0x04;
    byte max7219_reg_digit4      = 0x05;
    byte max7219_reg_digit5      = 0x06;
    byte max7219_reg_digit6      = 0x07;
    byte max7219_reg_digit7      = 0x08;
    byte max7219_reg_decodeMode  = 0x09;
    byte max7219_reg_intensity   = 0x0a;
    byte max7219_reg_scanLimit   = 0x0b;
    byte max7219_reg_shutdown    = 0x0c;
    byte max7219_reg_displayTest = 0x0f;
     
    void putByte(byte data) {
      byte i = 8;
      byte mask;
      while(i > 0) {
        mask = 0x01 << (i - 1);      // get bitmask
        digitalWrite( clock, LOW);   // tick
        if (data & mask){            // choose bit
          digitalWrite(dataIn, HIGH);// send 1
        }else{
          digitalWrite(dataIn, LOW); // send 0
        }
        digitalWrite(clock, HIGH);   // tock
        --i;                         // move to lesser bit
      }
    }
     
    void maxSingle( byte reg, byte col) {    
    //maxSingle is the "easy"  function to use for a     //single max7219
     
      digitalWrite(load, LOW);       // begin    
      putByte(reg);                  // specify register
      putByte(col);//((data & 0x01) * 256) + data >> 1); // put data  
      //digitalWrite(load, LOW);       // and load da shit
      digitalWrite(load,HIGH);
    }
     
    void maxAll (byte reg, byte col) {    // initialize  all  MAX7219's in the system
      int c = 0;
      digitalWrite(load, LOW);  // begin    
      for ( c =1; c<= maxInUse; c++) {
      putByte(reg);  // specify register
      putByte(col);
        }
      digitalWrite(load,HIGH);
    }
     
    void setup () {
     
     
      pinMode(dataIn, OUTPUT);
      pinMode(clock,  OUTPUT);
      pinMode(load,   OUTPUT);
     
      //Serial.begin(9600);
      digitalWrite(clock, HIGH);  
     
    //initiation of the max 7219
      maxSingle(max7219_reg_scanLimit, 0x01);      
      maxSingle(max7219_reg_decodeMode, 0x0F);  // using an led matrix (not digits)
      maxSingle(max7219_reg_shutdown, 0x01);    // not in shutdown mode
      maxSingle(max7219_reg_displayTest, 0x00); // no display test
       for (e=1; e<=8; e++) {    // empty registers, turn all LEDs off
        maxSingle(e,0);
      }
      maxSingle(max7219_reg_intensity, 0x0f and 0x0f);    // the first 0x0f is the value you can set
                                                      // range: 0x00 to 0x0f
    }  
     
    void loop () {
      //++cnum;
      //if (cnum > 16)
      //  cnum=0;
       //Serial.println(cnum); 
       maxSingle(1,1);                       //  + - - - - - - -
       //maxSingle(2,0x0C);                       //  - + - - - - - -
       //maxSingle(3,cnum+2);                       //  - - + - - - - -

      delay(500);
    }

