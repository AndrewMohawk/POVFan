
#include <Wire.h>

#include <extEEPROM.h>    //https://github.com/PaoloP74/extEEPROM
extEEPROM eep(kbits_4, 4, 2);         //device size, number of devices, page size

String str;

void setup()
{
  
  Serial.begin(115200);
  Serial.println("starting..");
  uint8_t eepStatus = eep.begin(eep.twiClock100kHz);   //go NOT fast!
  delay(500);
  

  for(int i=0;i<1024;i++)
  {
    //eep.write(i,0x99);
  }

  Serial.println("Ready.");
  
 
  
  
}
byte getHexFromChar(char in)
{
  if (in == 'A')
  {
    return 0xA;
  }
  if (in == 'B')
  {
    return 0xB;
  }
  if (in == 'C')
  {
    return 0xC;
  }
  if (in == 'D')
  {
    return 0xD;
  }
  if (in == 'E')
  {
    return 0xE;
  }
  if (in == 'F')
  {
    return 0xF;
  }
  if (in == '0')
  {
    return 0x0;
  }
  if (in == '1')
  {
    return 0x1;
  }
  if (in == '2')
  {
    return 0x2;
  }
  if (in == '3')
  {
    return 0x3;
  }
  if (in == '4')
  {
    return 0x4;
  }
  if (in == '5')
  {
    return 0x5;
  }
  if (in == '6')
  {
    return 0x6;
  }
  if (in == '7')
  {
    return 0x7;
  }
  if (in == '8')
  {
    return 0x8;
  }
  if (in == '9')
  {
    return 0x9;
  }
  return false;
  
    
  
}
void printMem()
{
  Serial.println("-");
  
  for(int i=0;i<1024;i++)
  {
  
    if(i%8 == 0)
    {
      Serial.println(" ");
      Serial.print("0x");Serial.print(i,HEX);Serial.print("\t");
    }
  
  byte r = eep.read(i);
  if(r < 0x10)
  {
    Serial.print("0");
  }
  if(r == 0x00)
  {
    //Serial.print("00");
  }
  Serial.print(r,HEX);
  Serial.print(" ");
  
  }

  Serial.println("done.");
}

void printMem2()
{
  Serial.println("-");
  
  for(int i=0;i<1024;i++)
  {
  
    if(i%8 == 0)
    {
      //Serial.println(" ");
      //Serial.print("0x");Serial.print(i,HEX);Serial.print("\t");
    }
  
  byte r = eep.read(i);
  //String mystring = sprintf( "Hex %4X wowie",r);
  if(r < 0x10)
  {
    Serial.print("0");
  }
  if(r == 0x00)
  {
    Serial.print("00");
  }
  Serial.print(r,HEX);
  //Serial.print("\t");
  
  }

  Serial.println("done.");
}

int len = 0;
byte currentChar;
void loop() {
  if(Serial.available() > 0)
    {
        str = Serial.readStringUntil('\n');
        Serial.println("writing...");
        if(str.length() == 1)
        {
          Serial.println("Current Memory Content");
          printMem2();
        }
        else
        {
          for (int x=0;x<str.length();x++)
          {
            //Serial.println();
            //Serial.print("convert ");Serial.print(str.charAt(x));Serial.print(" led to:");Serial.println(getHexFromChar(str.charAt(x)));
            len++;
            if(len == 1)
            {
              currentChar = getHexFromChar(str.charAt(x));
            }
            
            if(len == 2)
            {
              currentChar = currentChar << 4;
              currentChar = currentChar  + getHexFromChar(str.charAt(x));
              //Serial.println(currentChar,HEX);
              eep.write((x/2),currentChar);
              len = 0;
              currentChar = 0;
              //Serial.print(currentChar,HEX);
            }
          }
          Serial.println("...Done.");
          Serial.println("Current Memory Content");
          printMem();
        }
    }
  // put your main code here, to run repeatedly:

}
