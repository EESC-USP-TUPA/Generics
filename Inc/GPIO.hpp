#include "Comum.hpp"

#ifdef HAL_GPIO_MODULE_ENABLED
#include "stm32f1xx_hal_gpio.h"

#ifndef TAL_GPIO
#define TAL_GPIO

#include <stdint.h>
#include <vector>


class GPIO
{
		private:
			GPIO_TypeDef *porta;
			uint16_t pino;

			bool ligado;

		public:
			GPIO(){};
			GPIO(GPIO_TypeDef *endereco_porta, uint16_t endereco_pino) : porta(endereco_porta), pino(endereco_pino) {}

			void ligar();
			void desligar();
			void inverter();
			bool ler();

			void escrever(bool estado);
};


#endif /* TAL_GPIO */

#endif /* HAL_GPIO_MODULE_ENABLED */
