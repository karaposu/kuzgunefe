#include "functions.h"

 uint16_t	counter_tim2=0;  //isiklardan sorumlu counter. 
  uint8_t	package_arriving=1;
 

extern UART_HandleTypeDef huart1 ;
extern TIM_HandleTypeDef htim2;

 uint16_t packet_arrived=0;
  uint16_t packet_arrived_previous=0;
extern uint8_t counter ,buffrec[5],cout_doku;
extern volatile uint8_t Rx_indx, Rx_data[2], TBuffer[150],Transfer_cplt ,Rx_Buffer[30] ;
extern	void resolve_package( unsigned char *ptr);

extern  volatile int16_t decoded_data[13];
extern  uint8_t un_decoded_data[13];
extern    int16_t destination[13];
extern   unsigned char  destination2[13];

extern uint8_t example_data[13];
		
		
		void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)  
{

    cout_doku++;
	
    if (huart->Instance == USART1)  //current UART
        {
					
				int a=0;
				   
       if (Rx_indx==0) {for (int i=0;i<30;i++) Rx_Buffer[i]=0;}   //clear Rx_Buffer before receiving new data 

        if (Rx_data[0]!=a) //if received data different from 0
            {
							Transfer_cplt=0;
						 
            Rx_Buffer[Rx_indx++]=Rx_data[0];    //add data to Rx_Buffer
            }
        else            //if received data = 0
            {
           
								 		 		for( int i=0; i < 13; i++ ){
												un_decoded_data[i]=	 *( Rx_Buffer + i ) ;  }
												packet_arrived++;
												
												if (packet_arrived==1) //if received data different from 0
            {
													HAL_TIM_Base_Start_IT(&htim2);
												
						}
												
							Rx_indx=0;
							 Transfer_cplt=1;
							 
					 
							 
            }
		HAL_UART_Receive_DMA(&huart1, Rx_data, 1);
          }
				}

				
				
				 void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
											
																					/********************TIMER2 Fonskyonu  ( sadece ledler için )************************************************************/							
											if (htim->Instance == TIM2) {
																	
																	
											//Buraya her girdiginde x. led sönecek x+1 . led yanacak *******/
														
	                      if (package_arriving== 1){
      
																				
																			switch(counter_tim2){
																			
																			case 0:
																			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_14,GPIO_PIN_RESET);
																			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_15,GPIO_PIN_SET);
																			break;
																			
																			case 1:
																			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_15,GPIO_PIN_RESET);
																			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12,GPIO_PIN_SET);
																			break;
																			
																			case 2:
																			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12,GPIO_PIN_RESET);
																			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_13,GPIO_PIN_SET);
																			break;
																			
																			case 3: 
																			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_13,GPIO_PIN_RESET);
																			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_14,GPIO_PIN_SET);
																			break;
																			}

																		counter_tim2++;		
																			
																		if(counter_tim2==4)	{
																									
																		counter_tim2=0;
																		}			


																	}																		
																				
																			

							}						
											
							
							
							
							
							
								if (htim->Instance == TIM1) {
									
									
										if (packet_arrived>packet_arrived_previous) {
											
												package_arriving=1;
										}
										else{
											package_arriving=0;
										}
									packet_arrived_previous=packet_arrived;
									
									
								}
																									
																											
																											
			
}			
				
				
				
				
				
		

void controller_attitude_identification( int joystick1_x,int joystick1_y, int joystick2_x,int joystick2_y ){  //function takes array as input


	int jyt1_a=0;int jyt1_b=0;  int jyt1_c=0; int jyt1_d=0;
	int jyt2_a=0;int jyt2_b=0;  int jyt2_c=0; int jyt2_d=0;
 
	
			joystick1_x=0;  joystick1_y=0;  joystick2_x=0;  joystick2_y =0;

			 jyt1_a=0; jyt1_b=0;   jyt1_c=0;  jyt1_d=0;
	     jyt2_a=0; jyt2_b=0;   jyt2_c=0;  jyt2_d=0;

     if (joystick1_x>512)      { jyt1_a=  joystick1_x-512;}
     else if(joystick1_x<512) {   jyt1_b=  joystick1_x;} 

      if (joystick1_y>512)      { jyt1_c=  joystick1_y-512;}
     else if(joystick1_y<512) {   jyt1_d=  joystick1_y;} 

     
     if (joystick2_x>512)      { jyt2_a=  joystick2_x-512;}
     else if(joystick2_x<512) {   jyt2_b=  joystick2_x;} 

      if (joystick2_y>512)      { jyt2_c=  joystick2_y-512;}
     else if(joystick2_y<512) {   jyt2_d=  joystick2_y;}
					 
		 
					 
					 
}		
				
//		void ccal( ){                         //Command control Abstraction Layer.
//			
//			//kontrol komut bilgilerini donanimdan soyutlamak için kullanilir
//			//2 kisimdan olusur. 1. kisimda aktif yön bilgileri boolen degiskenler içinde tututlur
//			//2. kisimda ise yön bilgilerine karsilik gelen hiz degerleri bulunur.
//			
//			int direction_forward=0;
//			int direction_backward=0;
//			int direction_right=0;
//			int direction_left=0;
//			int direction_asc=0;
//			int direction_desc=0;
//			int direction_yaw_l=0;
//			int direction_yaw_r=0;
//			int on=0;
//			int stand_by=0;
//			
//	   	int value_forward=0;
//			int value_backward=0;
//			int value_right=0;
//			int value_left=0;
//			int value_asc=0;
//			int value_desc=0;
//			int value_yaw_l=0;
//			int value_yaw_r=0;
//		
//			
//			
//       int16_t ccal_active_attitudes[11];
//			 int16_t ccal_corresponding_values[11];

//			
//			if(jyt1_a>0) {   direction_forward=1; value_forward= jyt1_a;  }
//				if(jyt1_b>0) {   direction_backward=1; value_backward= jyt1_b;  }
//					if(jyt1_c>0) {   direction_yaw_l=1; value_yaw_l= jyt1_c;  }
//						if(jyt1_d>0) {   direction_yaw_r=1; value_yaw_r= jyt1_d;  }
//							if(jyt2_a>0) {   direction_asc=1; value_asc= jyt2_a;  }
//								if(jyt2_b>0) {   direction_desc=1; value_desc= jyt2_b;  }
//									if(jyt2_c>0) {   direction_left=1; value_left= jyt2_c;  }
//										if(jyt2_d>0) {   direction_right=1; value_right= jyt2_d;  }
//			
//			


//		
//					 
//}				
//				
//				
//				void quaternion_control_theory(char ptr)            
//{   
//	
//	hvalandirdik. dengesiz bir biçimde dönüyor.dengeli hale getirmek istiyoruz. dengeli halin q degerleri belli. simdiki halin
//	q degerlerini bno055 ten aliyoruz.. burdan difference q yu bulduk.
//	
//	daha sonra axis i bulmak için  x y z kismini normalize ettik.
//	bu axis açisal iveminin etki ettigi axis oldu.
//	pd döngüsünün error u difference quaternionunun  axis of rotation yönünde ki angle of rotationu oldu.
//	
//	pd nin derivativesi için açi farki alindi.
//	
//	çikis olarak verilecek açisal ivmenin  3d olmasi gerekli. bu yüzden difference quaternion axisini döndürmeden önce  
//	current q ile çarparak worldkordinatlarina döndürürüz.
//	
//	
//	
//	Simply normalize the 'purely imaginary' (XYZ) part of the quaternion and that will return the axis. 
//	
//	
//  difference quaternion =desired orientation*	current orientation-1
//	
//	difference quaternion*current orientation=desired orientation
//	
//	axis of rotation of desired quat.
//	that will be the direction of the outputted angular acc..
//	
//	The error of this PD loop, is then the angle of rotation the difference quaternion described about the axis of rotation. 
//		
//	 A large angle indicates that we are far from our desired orientation, while a small angle indicates that we are close.
//		 
//	  Derivative action is easily implemented by saving the previous angle and subtracting it from the current angle.
//			
//		The outputted angular acceleration needs to be in world coordinates so before returning the difference quaternion axis,
//		
//		we transform it into world coordinates by multiplying it by the current orientation quaternion.
//	
////				
////				5.3 Quaternion PID
////With the aim of smooth transitions from one orientation to any other, a
////quaternion PD loop was implemented. This loop first creates two quaternions, one for the current orientation, and one for the desired orientation.
////The difference quaternion is then found by multiplying the desired quaternion by the conjugate (inverse) of the current quaternion. The resultant
////quaternion has the property that when multiplied by the current quaternion, will produce the desired quaternion. We can find the axis of rotation
////of this quaternion and that will be the direction of the outputted angular
////acceleration. The error of this PD loop, is then the angle of rotation the
////difference quaternion described about the axis of rotation. A large angle
////indicates that we are far from our desired orientation, while a small angle
////indicates that we are close. Derivative action is easily implemented by saving the previous angle and subtracting it from the current angle.
////The outputted angular acceleration needs to be in world coordinates so before returning the difference quaternion axis, we transform it into world
////coordinates by multiplying it by the current orientation quaternion.
////Integral action is not implemented in this control loop as there should not be
////any need for it (we are modeling passive forces) and will probably complicate
////things.
//				
//} 

				

		
		void Multisensor_Attitude_Estimation(char ptr)            
{   

	
} 
		
		
		
		
		
		
		
void Serial_write(char ptr)            
{   
     // char a=
HAL_UART_Transmit_IT(&huart1, (uint8_t*) &ptr,1);
	HAL_Delay(10);
	
} 




void Serial_print(char *ptr, size_t length)            
{   
    size_t i = 0;
//    int8_t  temp_array[length];
//		int8_t  c=47;
	
	
	for( int i=0; i < length; i++ ){
	
			Serial_write(  *( ptr + i )  );
	}
	
}
	
	




     
void UnStuffData(const unsigned char *ptr, unsigned long length,unsigned char *dst) 
{ 
	
	
  const unsigned char *end = ptr + length; 
  while (ptr < end) 
  { 
  int i, code = *ptr++; for (i=1; i<code; i++) *dst++ = *ptr++; if (code < 0xFF) *dst++ = 0; } 

}


Quaternion  quaternion_multiply(Quaternion q1,Quaternion q2)            
{   
	Quaternion q3;
         q3.w=      q1.w*q2.w - q1.x*q2.x - q1.y*q2.y - q1.z*q2.z ;// new w
	       q3.x=      q1.w*q2.x - q1.x*q2.w - q1.y*q2.z - q1.z*q2.y ;// new x
	       q3.y=      q1.w*q2.y - q1.x*q2.z - q1.y*q2.w - q1.z*q2.x ;// new w
	       q3.z=      q1.w*q2.z - q1.x*q2.y - q1.y*q2.x - q1.z*q2.w ;// new x
	 return q3;

} 


Quaternion getConjugate(Quaternion q1) {
	  q1.w=q1.w;
		q1.x=(q1.x)*-1;
		q1.y=(q1.y)*-1;
		q1.z=(q1.z)*-1;
	
            return q1;
        }
        
  float getMagnitude(Quaternion q1) {
            return sqrt( q1.w*q1.w  + q1.x*q1.x  + q1.y*q1.y  + q1.z*q1.z);
		       
		 
        }
        
        void normalize(Quaternion q1) {
            float m = getMagnitude(q1);
            q1.w /= m;
            q1. x /= m;
            q1. y /= m;
            q1.z /= m;
        }
        
//        Quaternion getNormalized() {
//            Quaternion r(w, x, y, z);
//            r.normalize();
//            return r;
//        }



