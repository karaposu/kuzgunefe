#ifndef FUNCTIONS_H_ 
#define FUNCTIONS_H_ 

#include "main.h" 


 extern void Serial_write(char ptr)   ; 
 extern void printArray(char *ptr, size_t length);
 
extern void Serial_print(char *ptr, size_t length) ;
extern uint8_t* readByte() ;
 extern void readpaket5(uint8_t number_of_bytes) ;
extern void readpaket4(uint8_t number_of_bytes);
extern uint8_t* readBytes(uint8_t number_of_bytes) ;
extern void UnStuffData(const unsigned char *ptr, unsigned long length,unsigned char *dst) ;
extern Quaternion  quaternion_multiply(Quaternion q1,Quaternion q2) ;
extern Quaternion getConjugate(Quaternion q1) ;
extern float getMagnitude(Quaternion q1);
extern void normalize(Quaternion q1);

#endif