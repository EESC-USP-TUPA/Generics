#include "ADC.hpp"

#ifdef HAL_ADC_MODULE_ENABLED

ADC::ADC(uint8_t sens_number, ADC_HandleTypeDef* hadcx) {
	this->hadc = hadcx;
	// TODO Auto-generated constructor stub

}

ADC::~ADC() {
	// TODO Auto-generated destructor stub
}

uint8_t ADC::Get_sens_num() {
	return this->sens_num;
}

void ADC::Set_sens_num(uint8_t sens_number) {
	this->sens_num = sens_number;
}


ADC_HandleTypeDef* ADC::Get_chanel() {
	return this->hadc;
}

uint32_t* ADC::Get_sens_vec_val() {
	return this->sens_vec_val;
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
	free(this->sens_vec_val);
}


#endif
