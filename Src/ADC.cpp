#include "ADC.hpp"
#include <cstdlib>

#ifdef TAL_ADC

ADC::ADC(ADC_HandleTypeDef* hadcx, uint8_t numero_sensores){
	this->hadc = hadcx;
	this->qtd_sensores = numero_sensores;
	this->buffer = (uint32_t*) malloc(numero_sensores * sizeof(uint32_t));
	this->valores = (uint32_t*) malloc(numero_sensores * sizeof(uint32_t));
	// TODO Auto-generated constructor stub
}

ADC::~ADC() {
	free(buffer);
	// TODO Auto-generated destructor stub
}

ADC_HandleTypeDef* ADC::retornar_canal() {
	return this->hadc;
}

uint32_t* ADC::retornar_valores() {
	return this->valores;
}

uint32_t* ADC::retornar_buffer() {
	return this->buffer;
}

uint8_t ADC::retornar_qtd_sensores() {
	return this->qtd_sensores;
}



void ADC::ler_DMA() {
	HAL_ADC_Start_DMA(this->hadc, this->buffer, this->qtd_sensores);
}

void ADC::parar_DMA() {
	HAL_ADC_Stop_DMA(this->hadc);
	free(this->buffer);
	free(this->valores);
}


#endif
