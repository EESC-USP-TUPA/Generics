#include "ADC.hpp"

#ifdef TAL_ADC

ADC::ADC(ADC_HandleTypeDef* hadcx) {
	this->hadc = hadcx;
	// TODO Auto-generated constructor stub
}

ADC::~ADC() {
	// TODO Auto-generated destructor stub
}

ADC_HandleTypeDef* ADC::Get_chanel() {
	return this->hadc;
}

uint32_t* ADC::Get_valores() {
	return this->valores;
}

uint32_t* ADC::Get_buffer() {
	return this->buffer;
}


void ADC::Ler_DMA() {
	HAL_ADC_Start_DMA(this->hadc, this->buffer, 10);
}

void ADC::Parar_DMA() {
	HAL_ADC_Stop_DMA(this->hadc);
	free(this->buffer);
	free(this->valores);
}


#endif
