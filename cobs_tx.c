/*This code takes values from structure and encode them with...
 * Consistent Overhead Byte Stuffing (COBS) algoritm
 * 
 * First code checks the negative values. Save which values...
 * have a negative sign. After that converts 10 bit values...
 * to 2 bit and 8 bit values and stores them in array called
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
 #include "main.h"

//#include "arm_math.h"
#include "core_cm4.h"
//#include <stdlib.h>

 
 extern UART_HandleTypeDef huart1 ;
 extern uint8_t buffrec[5], paket[11],wgodizi[11],wgodizi2[11],wgodizi3[11],paket[11];
extern    int16_t destination[13];
extern   unsigned char  destination2[13];



//****************************************************************************************************************************//

//char* create_package( Balance_robot x){
//	

//int16_t temporary[6] ; 
//int8_t  length =9;
//char  length2 =9;
//char*  v ;

//int8_t  *temp_array= (int8_t*) malloc(length*sizeof(int8_t));
//int8_t  temp[length];	
//		
////int8_t  temp_array[length];
//	
//int8_t n,n0,n1,n2,n3,n4,n5=0;

////Serial_write( x.angle ) ;Serial_write( x.output_raw ) ; Serial_write( x.output_pwm ) ;
//	//Serial_write( x.p_value ) ; Serial_write( x.i_value ) ;Serial_write( x.d_value ) ;

//          if(x.angle<0){  n0=1; temporary[0]=x.angle*-1;  }
//          else{  n0=0;temporary[0]=(x.angle);}
//        if(x.output_raw<0){ n1=1;  temporary[1]=(x.output_raw)*-1;}
//				  else{ n1=0;temporary[1]=(x.output_raw);}
//                
//        if(x.output_pwm<0){ n2=1;    temporary[2]=(x.output_pwm)*-1;  }
//				else{ n2=0;  temporary[2]=(x.output_pwm);}
//                
//        if(x.p_value<0){ n3=1;  temporary[3]=(x.p_value)*-1;}
//        else{  n3=0; temporary[3]=(x.p_value);}
//                
//         if(x.i_value<0){ n4=1; temporary[4]=(x.i_value)*-1; }
//          else{ n4=0; temporary[4]=(x.i_value);}
//                
//         if(x.d_value<0){ n5=1; temporary[5]=(x.d_value)*-1;  }
//         else{ n5=0;temporary[5]=(x.d_value);}

////   for(int i =0 ; i<6; i++)
////  { 
////    Serial_write( temporary[i] ) ;//x.angle
////   }

//   
//n=n0*1+n1*2+n2*4+n3*8+n4*16+n5*32;
////Serial_write(  n ) ;//x.angle

//temp_array[0]= n;

//temp_array[1]= (char)(temporary[0] & 0x00FF); 
//temp_array[2]= (char)(temporary[0]>> 8);  //  

//temp_array[3]= (char)(temporary[1] & 0x00FF); 
//temp_array[4]= (char)(temporary[2]>> 8);  //  

//temp_array[5]= temporary[2] ;
//temp_array[6]= temporary[3] ;
//temp_array[7]= temporary[4];
//temp_array[8]= temporary[5];


//// for(int i =0 ; i<9; i++)
////  { 
////   Serial_write( temp_array[i] ) ;
////   }

//   
////	Serial_print(temp_array, 9);

//  return temp_array;
//}



//****************************************************************************************************************************//

void resolve_package( unsigned char *ptr){  //function takes array as input

    int8_t n;
    uint8_t temp_array[13] = {0};  //temporary array for calculations and also debugging 

  //  int16_t  *temporary = calloc(8, sizeof(*temporary));  //this gives me garbage (works now)
                                                        //no need to cast return of malloc/calloc
                                                        //temporary must be freed by caller
                                                        //also tested with malloc.
     
         for( int i=0; i < 13; i++ ){
            temp_array[i]        =   *( ptr + i );
         }

         n = temp_array[0];

         //here some bitwise calculations...
				 
				 
        destination[0] = (temp_array[1] + temp_array[2]*256 ) ;
        destination[1] = (temp_array[3]+ temp_array[4]*256)  ;
				 destination[2] = (temp_array[5] + temp_array[6]*256 ) ;
        destination[3] = (temp_array[7]+ temp_array[8]*256)  ;
			  destination[4]= temp_array[9];
        destination[5]= temp_array[10];
        destination[6]= temp_array[11];
        destination[7]= temp_array[12];
    

				for(int i=0;i < 8;i++) { 

									if (((n>> i) & 1)==1) 
										{
											destination[i]=-1*destination[i];
										}
										else{destination[i]=destination[i];}
					 }  
				
					 
		 
					 
					 
}




























// int16_t* make_predec_package( unsigned char *ptr){
//	
//	 // example_data[11]={32,2,140,3,168,100,3,1,16,0}  ;
//	 
//uint8_t temp_array[11] ; 
//int16_t  *temporaryp= (int16_t*) malloc(8*sizeof(int16_t));

////	 int *lenp = malloc(sizeof(int));
//    int16_t temporary = 0;
//      if (!temporaryp)     //check malloc success
//        exit(-1);    

//	*temporaryp= temporary;
//			
//			
//		
//			
//			
//	 for( int i=0; i < 11; i++ ){
//	        temp_array[i]        =   *( ptr + i );
//		       wgodizi[i]=      temp_array[i] ;
//			//Serial_write(  *( ptr + i )  );
//	}
//	 
//int8_t n;

//n = temp_array[0];

//temporaryp[0] = (temp_array[1]*256 ) + temp_array[2]/4  ;
//temporaryp[1] = (temp_array[3]*256 )+ temp_array[4]/ 4  ;
//temporaryp[2]= temp_array[5];
//temporaryp[3]= temp_array[6];
//temporaryp[4]= temp_array[7];
//temporaryp[5]= temp_array[8];
//temporaryp[6]= temp_array[9];
//temporaryp[7]= temp_array[10];


////for( int i=0; i < 6; i++ ){
////	      wgodizi2[i]=	 *( temporary + i ) ;
////	}
//	
//		
//for(int i=0;i < 8;i++) { 

//        	if (((n>> i) & 1)==1) 
//            {
//							temporaryp[i]=-1*temporaryp[i];
//						}
//						else{temporaryp[i]=temporaryp[i];}
//	 }  

//	 
//	 	for( int i=0; i < 6; i++ ){
//	      
//		 // wgodizi[i]= temporary[i];
//			//Serial_write(     temporary[i] );
//	}
//		
//	
//	temporary = *temporaryp;
//    free(temporaryp);
//    return temporary; 

//// return temporary;
//	
//	//free(temporary);
//}





//int16_t* make_predec_package( unsigned char *ptr){  //function takes array as input

//    int8_t n;
//    uint8_t temp_array[11] = {0};  //temporary array for calculations and also debugging 

//    int16_t  *temporary = calloc(8, sizeof(*temporary));  //this gives me garbage (works now)
//                                                        //no need to cast return of malloc/calloc
//                                                        //temporary must be freed by caller
//                                                        //also tested with malloc.
//                                                        //calloc initializes with 0 (better here)
//    if(temporary)
//    {
//         for( int i=0; i < 11; i++ ){
//            temp_array[i]        =   *( ptr + i );
//         }

//         n = temp_array[0];

//         //here some bitwise calculations...
//        temporary[0] = (temp_array[1]*256 ) + temp_array[2]/4  ;
//        temporary[1] = (temp_array[3]*256 )+ temp_array[4]/ 4  ;
//        temporary[2]= temp_array[5];
//        temporary[3]= temp_array[6];
//        temporary[4]= temp_array[7];
//        temporary[5]= temp_array[8];
//        temporary[6]= temp_array[9];
//        temporary[7]= temp_array[10];
//    }

//         // i want to return it but even without using return malloc gives garbage results
//    return temporary;  
//}














#define FinishBlock(X) (*code_ptr = (X),  code_ptr = dst++,   code = 0x01  )
void StuffData(const unsigned char *ptr, unsigned long length, unsigned char *dst) 
{


 unsigned char *zero=0;
 unsigned char *dst2;
 
  const unsigned char *end = ptr + length; //baslangiç adresi + uzunluk ile dizideki son degerin adresini belirle
  unsigned char *code_ptr = dst++;  // dst nin 1. elemaninin adresini code_ptr ye at
  unsigned char code = 0x01; //counter for 255 adet data
while (ptr < end) // ptr dizisinin sonuna ulasana dek...
{ 
   if (*ptr == 0) FinishBlock(code); 
  else { 
    *dst++ = *ptr;
    code++; 
     if (code == 0xFF)FinishBlock(code);
     } 
    
    ptr++; 
   // if (ptr - end==0)  *dst++ = zero;
  dst2  =dst;
  } 
   
FinishBlock(code);
dst=dst2;
 //*dst++ = zero; 
//  *dst++=*zero;
}





