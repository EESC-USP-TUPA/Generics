#ifndef SRC_CAN_H_
#define SRC_CAN_H_

#include "main.h"
#include <stdlib.h>

class Can {
private:
    CAN_HandleTypeDef *handler;
    CAN_FilterTypeDef filtro;

    CAN_TxHeaderTypeDef tx_header;
    CAN_RxHeaderTypeDef rx_header;
    uint32_t mailbox;

    uint32_t interrupt;
    bool lock;

public:
    Can(CAN_HandleTypeDef *handler, uint32_t interrupt, uint32_t id);
    void iniciar(uint32_t interrupt, uint32_t id);

    void setup(uint32_t interrupt, uint32_t id_high, uint32_t id_low, uint32_t mask_high, uint32_t mask_low);

    uint8_t *ler();
    bool enviar(uint8_t *dados, uint8_t tamanho);

    void esperar();
    virtual ~Can();
};

#endif /* SRC_CAN_H_ */
