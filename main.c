
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_hal.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */

//xbee gönderici üzerinde xbee shieldin rx yazan kismi rx e gidicek
//xbee alici üstünde tx pb6 ya gidiyor.



/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/


float x=0;
uint16_t a[4];
uint16_t tamsayi=0;
float duty_cycle=0;
uint16_t thr=0;


float x2=0;

uint16_t tamsayi2=0;
float duty_cycle2=0;
uint16_t thr2=0;

float x3=0;

uint16_t tamsayi3=0;
float duty_cycle3=0;
uint16_t thr3=0;


float x4=0;

uint16_t tamsayi4=0;
float duty_cycle4=0;
uint16_t thr4=0;

uint8_t x5=0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
    int16_t wgodizi[11],wgodizi2[11],wgodizi3[11];
   uint8_t wgodizi4[11];

void resolve_package( unsigned char *ptr);

volatile int16_t decoded_data[13];
 uint8_t un_decoded_data[13];
  uint8_t un_decoded_data2[13];
		    int16_t destination[13];
	 unsigned char  destination2[13];

	
uint8_t paket[11] ,paket2[11] ,counter ,wgo;
volatile uint8_t buffrec[13];

	


uint8_t example_data[11]={2,32,2,140,3,168,100,3,1,16,0} ;
	




volatile uint8_t Rx_indx, Rx_data[2],TBuffer[150],dma_value[2];
 volatile uint8_t		Transfer_cplt, Rx_Buffer[30];
 uint8_t  cout_doku;
uint8_t surfaced_dma_value;


//Interrupt callback routine


/**paketi olustu. paket olustuktan sonra direk denge robotu degererlini güncellemesi gerekiyorç 
* bunu interrupt rütininde yapacak.
*
*degeri aldi . güncelleme yapti.
*sen adam gibi paketi rx ten topla. 
*daha sonra  interrupt içinde bu paketi aç . 
*paketi açtiktan sonra  resolve_package çalistir
*daha sonra return degeri üzerinden unstuff datayi çalistir
*buldugun degerleri balance roboto yükle .
**/
	
	void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim); //

	
	
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */


	
		uint8_t increment = 0;
		uint8_t increment2 = 0;
		uint8_t increment3 = 0;
		uint8_t increment4 = 0;

	
Drone_control  drone_control;
Quaternion attitude_estimation_quaternion;
Quaternion desired_position;
Quaternion error_quaternion;


desired_position = (Quaternion) { .w = 1.0, .x = 0.0, .y = 0.0 , .z = 0.0 };
	
drone_control.engine_1=0;
drone_control.engine_2=0;
drone_control.engine_3=0;
drone_control.engine_4=0;
drone_control.wake_up=0;
  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART1_UART_Init();
  MX_TIM3_Init();
  MX_TIM2_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
HAL_TIM_PWM_Start (&htim3, TIM_CHANNEL_1);
HAL_TIM_PWM_Start (&htim3, TIM_CHANNEL_2);
HAL_TIM_PWM_Start (&htim3, TIM_CHANNEL_3);
HAL_TIM_PWM_Start (&htim3, TIM_CHANNEL_4);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	
		__HAL_UART_ENABLE_IT(&huart1,UART_IT_TC);
    HAL_UART_Receive_DMA(&huart1,(uint8_t*)Rx_data,1);

//	HAL_TIM_Base_Start_IT(&htim2);
HAL_TIM_Base_Start_IT(&htim1);

  while (1)
  {

  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
		
		
		error_quaternion=  quaternion_multiply(desired_position  ,getConjugate(attitude_estimation_quaternion) );
		
		
		
HAL_Delay(20);
		    for( int i=0; i < 13; i++ ){
				un_decoded_data2[i]=	 		un_decoded_data[i] ;  }
												
					UnStuffData(un_decoded_data2, 11,destination2) ;
          resolve_package(destination2);
				

			
drone_control.engine_1=destination[0];
drone_control.engine_2=destination[1];
drone_control.engine_3=destination[2];
drone_control.engine_4=destination[3];
drone_control.wake_up=destination[4];			
											
				
//				drone_control.engine_1=1000;
//drone_control.engine_2=1000;
////drone_control.engine_3=1000;
////drone_control.engine_4=1000;
////drone_control.wake_up=1000;	
		
		x=drone_control.engine_1;
	duty_cycle=(x/1023)*100 ; //		duty_cycle=(x/4095)*100 ;  //gelen verinin doluluk orani hesalandi , 500 geldiyse yüzde 50 oranini elde ettik
	//	thr= 0;
		thr= (duty_cycle/100*1000)+1000 ;  // elde edilen doluluk oranini stmde pwm olarak ifade edicez. 
		increment = x;
		thr=thr-50;
		
		 TIM3->CCR1=thr;    //  PA6
		
		
		x2=drone_control.engine_2;
		duty_cycle2=(x2/1023)*100 ;//	duty_cycle2=(x2/4095)*100 ;
		thr2= (duty_cycle2/100*1000)+1000 ;
    increment2 = x2;
		
     TIM3->CCR2=thr;    //PA7
		
		
		x3=drone_control.engine_3;
	  duty_cycle3=(x3/1023)*100 ; //  duty_cycle3=(x3/4095)*100 ;
		thr3= (duty_cycle3/100*1000)+1000 ;
		increment3 = x3;
		
		 TIM3->CCR3=thr;   //PB0
		 
		 
		 	x4=drone_control.engine_4;
		  duty_cycle4=(x4/1023)*100 ;//  duty_cycle4=(x4/4095)*100 ;
		thr4= (duty_cycle4/100*1000)+1000 ;
		increment3 = x4;
		
		 TIM3->CCR4=thr;     //PB1
		
		x5=	drone_control.wake_up;
				
//		if (x5==1) 
//            {
//							
//							 TIM3->CCR1=1300;
//							 TIM3->CCR2=1300;
//							 TIM3->CCR3=1300;
//							 TIM3->CCR4=1300;
//							
//							
//							
//							
//							
//						}
				
				
				
				
		
		

		
  }
  /* USER CODE END 3 */

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
