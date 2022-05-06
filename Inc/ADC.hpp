#include "Comum.hpp"

#ifdef HAL_ADC_MODULE_ENABLED

#ifndef TAL_ADC
#define TAL_ADC

#include "stm32f1xx_hal.h"

class ADC {
private:
	ADC_HandleTypeDef *hadc;
	uint8_t qtd_sensores;
	uint32_t* valores;
	uint32_t* buffer;

public:
	ADC( ADC_HandleTypeDef *hadcx, uint8_t numero_sensores);
	~ADC();
	ADC_HandleTypeDef* retornar_canal();
	uint32_t * retornar_valores();
	uint32_t* retornar_buffer();
	void ler_DMA();
	void parar_DMA();
	uint8_t retornar_qtd_sensores();

};

#endif /* TAL_ADC */

#endif /* HAL_ADC_MODULE_ENABLED */
