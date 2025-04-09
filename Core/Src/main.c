/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <math.h>
#define LED_PORT GPIOC
#define LED_PIN_0  GPIO_PIN_0
#define LED_PIN_1  GPIO_PIN_1
#define LED_PIN_2  GPIO_PIN_2
#define LED_PIN_3  GPIO_PIN_3
typedef int32_t var_type;
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
var_type TestFunction(var_type num);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
Byte_t BinaryCount(Byte_t count) {
  //
	const unsigned long int clockIterBuffer = 20000000;
	/* 0xFFFFFFFF is maximum value for an unsigned long int
		 acts as a large value to count to, to spend time on execution cycles
		 such that a human can see the led light up
		 0x00FFFFFF was chosen as clock is at 80MHz, so for loop approx 0.2 secs
	*/
  for(unsigned long int i = 0; i < clockIterBuffer; i++) { // wait delayed time
		; // nop
	}
	
	const Byte_t countTo = 15; // To binary count through 4 LEDs, 16 states are needed (15 + 0 = 16)
	if (count == countTo) {
		count = 0; // cycle back to 0 after reaching maximum value to count to
	}
	else {
		count+=1; // count up until maximum value is reached
	}
	return count;
}

void LedAssign(Byte_t count) {
	/*
		if any bits of count are a 0, reset the bit by complementing it and shifting it by 16
		set all bits in the first 16 if value is 1
	*/
	LED_PORT->BRR = (LED_PIN_0 | LED_PIN_1 | LED_PIN_2 | LED_PIN_3);
	if(count & 0x1) LED_PORT->BSRR = (LED_PIN_0);
	if(count & 0x2) LED_PORT->BSRR = (LED_PIN_1);
	if(count & 0x4) LED_PORT->BSRR = (LED_PIN_2);
	if(count & 0x8) LED_PORT->BSRR = (LED_PIN_3);
	//	GPIOC->BSRR = ((~count >> 16) | count);
}

var_type TestFunction(var_type num) {
	var_type test_var;  				// local variable
 
  GPIOC->BSRR = (GPIO_PIN_1);             // turn on PC1
  /* USER insert test function here e.g. test_var = num; */

	test_var = num;

	
	GPIOC->BRR = (GPIO_PIN_1);              // turn off PC1
	//test_var = num;
  
  
  return test_var;
}


int main(void) {
	var_type main_var;
	/* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */


	RCC->AHB2ENR   |=  (RCC_AHB2ENR_GPIOCEN);
  GPIOC->MODER   &= ~(GPIO_MODER_MODE0 | GPIO_MODER_MODE1 | GPIO_MODER_MODE2 | GPIO_MODER_MODE3);
  GPIOC->MODER   |=  (GPIO_MODER_MODE0_0 | GPIO_MODER_MODE1_0 | GPIO_MODER_MODE2_0 | GPIO_MODER_MODE3_0);
  GPIOC->OTYPER  &= ~(GPIO_OTYPER_OT0 | GPIO_OTYPER_OT1 | GPIO_OTYPER_OT2 | GPIO_OTYPER_OT3);
  GPIOC->PUPDR   &= ~(GPIO_PUPDR_PUPD0 | GPIO_PUPDR_PUPD1 | GPIO_PUPDR_PUPD2 | GPIO_PUPDR_PUPD3);
  GPIOC->OSPEEDR |=  ((3 << GPIO_OSPEEDR_OSPEED0_Pos) |
                      (3 << GPIO_OSPEEDR_OSPEED1_Pos) |
											(3 << GPIO_OSPEEDR_OSPEED2_Pos) |
											(3 << GPIO_OSPEEDR_OSPEED3_Pos));
  GPIOC->BRR = (GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3); // preset PC0, PC1, PC2, PC3 to 0
	
	/* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  /* USER CODE END 3 */
	//Byte_t count = 0; // start counting from 0;
	for (Byte_t loopsCounted = 0; loopsCounted < 4; loopsCounted++) {
		for (Byte_t count = 0; count < 16; count++) {
			LED_PORT->BRR = (LED_PIN_0 | LED_PIN_1 | LED_PIN_2 | LED_PIN_3);
			if(count & 0x1) LED_PORT->BSRR = (LED_PIN_0);
			if(count & 0x2) LED_PORT->BSRR = (LED_PIN_1);
			if(count & 0x4) LED_PORT->BSRR = (LED_PIN_2);
			if(count & 0x8) LED_PORT->BSRR = (LED_PIN_3);
			for(long int i =0; i < 40000; i++) {
				;
			}
		}
	}

	while(1) {
		
		/*
			counts in binary using 4 LEDs
		*/
		GPIOC->BSRR = (GPIO_PIN_0);             // turn on PC0
		main_var = TestFunction(15);            // call test function
		GPIOC->BRR = (GPIO_PIN_0);             // turn on PC0
		main_var++;
		//	LedAssign(count); // turns on and off appropriate LEDs
		//count = BinaryCount(count); // jump to next count with a time delay in between
	}
	return 0;
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follows :
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 80000000
  *            HCLK(Hz)                       = 80000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 1
  *            APB2 Prescaler                 = 1
  *            HSE Frequency(Hz)              = 8000000
  *            PLL_M                          = 1
  *            PLL_N                          = 20
  *            PLL_P                          = 7
  *            PLL_Q                          = 4
  *            PLL_R                          = 2
  *            Flash Latency(WS)              = 4
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {}
}
#endif

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
