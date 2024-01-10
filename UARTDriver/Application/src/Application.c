#include "Application.h"

extern TIM_HandleTypeDef htim6;

extern SemaphoreHandle_t xSemaphore;
extern SemaphoreHandle_t xTimerSemaphor;
extern SemaphoreHandle_t xUartSemaphore;
extern UART_HandleTypeDef huart2;


static volatile uint8_t pData;



void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if(&huart2 == huart)
  {
    if(pData == 'a')
    {
        uint8_t x[] = "Hihi";
        HAL_GPIO_TogglePin(BLUE_LED_GPIO_Port, BLUE_LED_Pin);
        HAL_UART_Transmit_IT(&huart2, x, sizeof(x));
    }
  }
  
}

void Application_Init(void* params)
{
    TickType_t start = 0, stop = 0;
    TickType_t delay = pdMS_TO_TICKS(*(uint64_t*)params);
    for(;;)
    {
        start = xTaskGetTickCount();
        HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin); 
        stop = xTaskGetTickCount();  
        vTaskDelay(delay - (stop - start));
    }
    vTaskDelete(NULL);
}

void Application_IntHandler(void* params)
{
    HAL_TIM_Base_Start_IT(&htim6);
    for(;;)
    {
        if(xSemaphoreTake(xSemaphore, (TickType_t)10) == pdTRUE)
        {
            HAL_GPIO_TogglePin(BTN_EVENT_GPIO_Port, BTN_EVENT_Pin); 
        }

        if(xSemaphoreTake(xTimerSemaphor, (TickType_t)10) == pdTRUE)
        {
            HAL_GPIO_TogglePin(TIM_EVENT_GPIO_Port, TIM_EVENT_Pin); 
        }
    }
    vTaskDelete(NULL);
}

void Application_UARTHandler(void* params)
{
    for(;;)
    {
        if(xSemaphoreTake(xUartSemaphore, (TickType_t)10) == pdTRUE)
        {
            HAL_UART_Receive_IT(&huart2, &pData, 1);
        }
    }
    vTaskDelete(NULL);
}