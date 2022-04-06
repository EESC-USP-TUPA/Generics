#include "Comum.hpp"

#ifdef HAL_ADC_MODULE_ENABLED

#ifndef TAL_ADC
#define TAL_ADC

#include "stm32f1xx_hal.h"

#define qtd_sensores 10

class ADC {
private:
	ADC_HandleTypeDef *hadc;
	uint32_t valores[qtd_sensores];
	uint32_t buffer[5];

public:
	ADC( ADC_HandleTypeDef *hadcx);
	~ADC();
	ADC_HandleTypeDef* Get_chanel();
	uint32_t *Get_valores();
	uint32_t* Get_buffer();
	void Ler_DMA();
	void Parar_DMA();

};

#endif /* TAL_ADC */

#endif /* HAL_ADC_MODULE_ENABLED */
