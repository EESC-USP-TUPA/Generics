#include "Comum.hpp"

#ifdef HAL_CAN_MODULE_ENABLED
#include "stm32f1xx_hal_can.h"


#ifndef TAL_CAN
#define TAL_CAN

#include "stm32f1xx_hal.h"
#include <stdlib.h>
#include <stdint.h>
#include <cstring>

class Can {
private:
    CAN_HandleTypeDef *handler;
    CAN_FilterTypeDef filtro;

    CAN_TxHeaderTypeDef tx_header;
    CAN_RxHeaderTypeDef rx_header;
    uint32_t mailbox;

    uint32_t interrupt;
    uint8_t dados_recebidos[8];
    bool lock;

public:
    Can(CAN_HandleTypeDef *handler, uint32_t interrupt, uint32_t id);

    void definir_filtro(uint32_t interrupt, uint32_t id_filtro, uint32_t mascara_filtro);

    void guardar_dados(uint8_t* alvo);
    bool enviar(uint32_t id_mensagem, uint8_t *dados, uint8_t tamanho);

    void esperar(uint32_t timeout);
    virtual ~Can();
};

#endif /* TAL_CAN */

#endif /* HAL_CAN_MODULE_ENABLED */
