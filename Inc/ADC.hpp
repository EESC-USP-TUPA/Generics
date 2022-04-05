#include "Comum.hpp"

#ifdef HAL_ADC_MODULE_ENABLED

#ifndef TAL_ADC
#define TAL_ADC

#include "stm32f1xx_hal.h"
#include <stdio.h>
#include <stdlib.h>

#define sens_num 10

class ADC {
private:
	ADC_HandleTypeDef *hadc;
	uint32_t valores[sens_num];
	uint32_t buffer[10];

public:
	ADC( ADC_HandleTypeDef *hadcx);
	~ADC();
	ADC_HandleTypeDef* Get_chanel();
	uint32_t *Get_valores();
	uint32_t* Get_buffer();
	void Set_buffer();
	void Ler_DMA();
	void Parar_DMA();



};

#endif /* TAL_ADC */

#endif /* HAL_ADC_MODULE_ENABLED */
