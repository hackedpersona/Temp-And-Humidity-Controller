#include <dht.h>
#define dht_apin A0
dht DHT;          // creating an object for analysing the temperature and humidity
int temp=0;
int hum=0;
const int ldr=A1; // pin that detects the presence of day and light
int sensorValue=0;
int led1=10;      //led for humidity
int led2=11;      // led for temperature
int ledState2=LOW;
int ledState1=LOW;
char buffer[5];
int pId=0;        // program id for gobetwino to return the program id
int count=0;
int Time=0;       // time for 7-segment display

void setup() {
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(ldr,INPUT);
  Serial.begin(9600);
  delay(500);
  Serial.println("Evaluating a greenhouse tmp");
  delay(1000);
  Serial.println("#S|SPXL|[]#"); // Start Excel
  for (int i=2;i<9;i++)

       {

         pinMode(i, OUTPUT);// taking all pins from 2-8 as output

       }
}



void loop() {
  sensorValue=analogRead(ldr);  //this is used for the detection light and dark for different vegetables
  DHT.read11(dht_apin);
  temp=DHT.temperature;
  hum=DHT.humidity;
  if (count==10)
  {

  count=0;// if count integer value is equal to 10, reset it to zero.

 }

switch (count)

                {

            case 0://when count value is zero show”0” on disp
            digitalWrite(2, LOW);
            digitalWrite(3, LOW);
            digitalWrite(4, LOW);
            digitalWrite(5, LOW);
            digitalWrite(6, LOW);
            digitalWrite(7, LOW);
            digitalWrite(8, HIGH);
            break;
            
            case 1:// when count value is 1 show”1” on disp
            digitalWrite(2, HIGH);
            digitalWrite(3, LOW);
            digitalWrite(4, LOW);
            digitalWrite(5, HIGH);
            digitalWrite(6, HIGH);
            digitalWrite(7, HIGH);
            digitalWrite(8, HIGH);
            break;

            case 2:// when count value is 2 show”2” on disp
            digitalWrite(2, LOW);
            digitalWrite(3, LOW);
            digitalWrite(4, HIGH);
            digitalWrite(5, LOW);
            digitalWrite(6, LOW);
            digitalWrite(7, HIGH);
            digitalWrite(8, LOW);
            break;

            case 3:// when count value is 3 show”3” on disp
            digitalWrite(2, LOW);
            digitalWrite(3, LOW);
            digitalWrite(4, LOW);
            digitalWrite(5, LOW);
            digitalWrite(6, HIGH);
            digitalWrite(7, HIGH);
            digitalWrite(8, LOW);
            break;

            case 4:// when count value is 4 show”4” on disp
             digitalWrite(2, HIGH);
             digitalWrite(3, LOW);
             digitalWrite(4, LOW);
             digitalWrite(5, HIGH);
             digitalWrite(6, HIGH);
             digitalWrite(7, LOW);
             digitalWrite(8, LOW);
             break;

             case 5:// when count value is 5 show”5” on disp
             digitalWrite(2, LOW);
             digitalWrite(3, HIGH);
             digitalWrite(4, LOW);
             digitalWrite(5, LOW);
             digitalWrite(6, HIGH);
             digitalWrite(7, LOW);
             digitalWrite(8, LOW);                   
             break;

             case 6:// when count value is 6 show”6” on disp
              digitalWrite(2, LOW);
              digitalWrite(3, HIGH);
              digitalWrite(4, LOW);
              digitalWrite(5, LOW);
              digitalWrite(6, LOW);
              digitalWrite(7, LOW);
              digitalWrite(8, LOW);
              break;


                case 7:// when count value is 7 show”7” on disp
                digitalWrite(2, LOW);
                digitalWrite(3, LOW);
                digitalWrite(4, LOW);
                digitalWrite(5, HIGH);
                digitalWrite(6, HIGH);
                digitalWrite(7, HIGH);
                digitalWrite(8, HIGH);
                break;

                case 8:// when count value is 8 show”8” on disp
                digitalWrite(2, LOW);
                digitalWrite(3, LOW);
                digitalWrite(4, LOW);
                digitalWrite(5, LOW);
                digitalWrite(6, LOW);
                digitalWrite(7, LOW);
                digitalWrite(8, LOW);
                break;

                case 9:// when count value is 9 show”9” on disp
                digitalWrite(2, LOW);
                digitalWrite(3, LOW);
                digitalWrite(4, LOW);
                digitalWrite(5, LOW);
                digitalWrite(6, HIGH);
                digitalWrite(7, LOW);
                digitalWrite(8, LOW);
                break;

 

                default:
                break;

                }
 if(count<10)
 {
  count++;
 }

        
 /*for tomato daytime:80-90  nighttime:65-75 Tomatoes grow best when the daytime temperature is between 19 and 30 degrees Celsius. They stop growing above 35 degrees Celcius.
 If nighttime temperatures are above 30  degrees Fahrenheit, the fruit will not turn red. Tomatoes need full sun and warm, well-drained soil.*/
 if(sensorValue<=100)        //This loop is for night
 {   
  if(hum<=65 || hum>=75)
  {    
    digitalWrite(led1,HIGH);
  } 
  else
  {
    digitalWrite(led1,LOW);
  }
   if(temp>32){
    digitalWrite(led2,HIGH);
  }
  else
  {
    digitalWrite(led2,LOW);
  }

  Serial.print("#S|SENDK|[");
   Serial.print(itoa((pId), buffer, 10));
   Serial.print("&");
   Serial.print(temp);
   Serial.print(" {TAB} ");
   Serial.print(hum);    
   Serial.print(" {DOWN} ");
   Serial.print(" {LEFT} ");
   Serial.println("]#");
  // readSerialString(serInString, 1000); // read response from PC
   // Deal with response from PC here. Ignored for now.
   delay(2000); // block code for 2 seconds - ensure excel has fully executed commands on PC
 
   // Save file after each write
   Serial.print("#S|SENDK|[");
   Serial.print(itoa((pId), buffer, 10));
   Serial.print("& ");
   Serial.print("%Fs");  //=   ALT f   ALT g  = save and exit in danish Excell
   Serial.println("]#");
   // Wait 2 seconds for the save to finish
   delay(2000);

 }


 

 else
 {
   if(hum<=70 || hum>=80)
  {
    digitalWrite(led1,HIGH);
    
  }
  else
  {
    digitalWrite(led1,LOW);
  }

 if(temp>33){
   digitalWrite(led2,HIGH);
  }
  else
  {
    digitalWrite(led2,LOW);
  }

  Serial.print("#S|SENDK|[");
   Serial.print(itoa((pId), buffer, 10));
   Serial.print("&");
   Serial.print(temp);
   Serial.print(" {TAB} ");
   Serial.print(hum);    
   Serial.print(" {DOWN} ");
   Serial.print(" {LEFT} ");
   Serial.println("]#");

   delay(2000); // block code for 2 seconds - ensure excel has fully executed commands on PC
 
   // Save file after each write
   Serial.print("#S|SENDK|[");
   Serial.print(itoa((pId), buffer, 10));
   Serial.print("& ");
   Serial.print("%Fs");  //=   ALT f   ALT g  = save and exit in danish Excell
   Serial.println("]#");
   // Wait 2 seconds for the save to finish
   delay(2000);
 
   

 }
 /*for cabbage temp 40 degree cel optimum can go up to 80 deg cel */
 /* for citrus fruits dies below 0 degree celsius best range between 20-30 degree celsuis humidity 60-65 */
 /* for spinach cold time crop grows best when the temp is around 21-24 degree Celsius */


delay(3000);

}
