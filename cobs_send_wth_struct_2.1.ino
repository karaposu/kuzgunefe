/*This code takes values from structure and encode them with...
 * Consistent Overhead Byte Stuffing (COBS) algoritm
 * 
 * First code checks the negative values. Save which values ...
 * have a negative sign. After that converts each 16 bit values...
 * to 8 bit and 8 bit values and stores them in array called
 * "temp_array" . 
 * 
 * Since this process is in function we never .
 * use that array name on the loop.We use return value directly 
 * like this:
 *  "make_prepackage(balance_robot)"  where 'balance_robot' is..
 * the structure and 'make_prepackage' is the name of function.
 * 
 * After that we have a array which can be use as a input for 
 * encoding function:
 * StuffData()
 * 
 */
int16_t adc=0;

typedef struct  {
    int16_t  angle;
    int16_t output_raw;
    int16_t output_pwm;
    int16_t  p_value;
    int8_t  i_value;
    int8_t  d_value;
}Balance_robot;

unsigned char* make_prepackage( Balance_robot x);

Balance_robot balance_robot;

const int8_t length_of_package=13;
void printArray(int *ptr, size_t length);     
void StuffData(const unsigned char *ptr, unsigned long length, unsigned char *dst) ;
unsigned char dest[length_of_package] ;
char* target ;

int xPin = A0; // A0-A5 analog pinlerinden herhangi birine bağlanabilir.
int yPin = A1; // A0-A5 analog pinlerinden herhangi birine bağlanabilir.

int dir_a=0;int dir_b=0;  int dir_c=0; int dir_d=0;
 int dir_a2=0;int dir_b2=0;  int dir_c2=0; int dir_d2=0;





void setup() {
Serial.begin(115200);


balance_robot.angle =35;
balance_robot.output_raw =42;
balance_robot.output_pwm =100;
balance_robot.p_value =0;
balance_robot.i_value =1;
balance_robot.d_value =-16;

}

void loop() {
//    int sensorValue = analogRead(A0);
//    int sensorValue2 = analogRead(A1);
//     int sensorValue3 = analogRead(A2);
//   int sensorValue4 = analogRead(A3);

int xPozisyonu = 0;
int yPozisyonu = 0;

  xPozisyonu = analogRead(xPin);
  yPozisyonu = analogRead(yPin);
   

convert_from_physical( xPozisyonu, yPozisyonu , xPozisyonu, yPozisyonu )    ;   
dir_a= dir_a*(1023/471);

//Serial.print(joystick1_x); Serial.print(" ");
//Serial.println(dir_a);

balance_robot.angle =dir_a;
balance_robot.output_raw =dir_a;
balance_robot.output_pwm =dir_a;
balance_robot.p_value =dir_a;
balance_robot.i_value =1;
balance_robot.d_value =1;
 
    
target=make_prepackage(balance_robot);//neccesary for allocation ?
StuffData(target,(length_of_package-2),dest); 
   for(int i =0 ; i<length_of_package; i++)
  { Serial.write(dest[i]);}
    delay(50);
   }




void convert_from_physical( int joystick1_x , int joystick1_y , int joystick2_x , int joystick2_y  )            
{         
 /* 1 joystickte 4 farklı yön var. 1. yön yukarı  2. yön aşagı 3.yön sag 4. yön sol olarak tanımlandı
  * 1.yönün degerlerini ilk önce 0 -512 arasında değişen hale getirip sonra 2 ile çarpacagız.
  * eger gelen deger 512den büyükse 512 çıkar.bu  benim dir_a degerimdir.
  * 
  */
  
      dir_a=0; dir_b=0;   dir_c=0;  dir_d=0;
      dir_a2=0; dir_b2=0;   dir_c2=0;  dir_d2=0;

     //joystick1_x=joystick1_x-40;

  //   dir_a=  joystick1_x;
     if (joystick1_x>552)      { dir_a=  joystick1_x-552;}
//     else if(joystick1_x<553) {   dir_b=  joystick1_x;} 
//
//      if (joystick1_y>512)      { dir_c=  joystick1_y-512;}
//     else if(joystick1_y<512) {   dir_d=  joystick1_y;} 
//
//     
//     if (joystick2_x>512)      { dir_a2=  joystick2_x-512;}
//     else if(joystick2_x<512) {   dir_b2=  joystick2_x;} 
//
//      if (joystick2_y>512)      { dir_c2=  joystick2_y-512;}
//     else if(joystick2_y<512) {   dir_d2=  joystick2_y;} 
} 











