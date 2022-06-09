#include "GPIO.hpp"
#ifdef HAL_GPIO_MODULE_ENABLED


void GPIO::ligar()
{
	ligado = true;
	HAL_GPIO_WritePin(this->porta, this->pino, GPIO_PIN_SET);
}

void GPIO::desligar()
{
	ligado = false;
	HAL_GPIO_WritePin(this->porta, this->pino, GPIO_PIN_RESET);
}

void GPIO::inverter()
{
	if (ligado)
	{
		HAL_GPIO_WritePin(this->porta, this->pino, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(this->porta, this->pino, GPIO_PIN_RESET);
	}
}

bool GPIO::ler()
{
	return HAL_GPIO_ReadPin(this->porta, this->pino) == GPIO_PIN_SET;
}

void GPIO::escrever(bool estado)
{
	if (estado)
	{
		HAL_GPIO_WritePin(this->porta, this->pino, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(this->porta, this->pino, GPIO_PIN_RESET);
	}
}

#endif /* HAL_GPIO_MODULE_ENABLED */
