#include "CAN.hpp"

#ifdef HAL_CAN_MODULE_ENABLED

Can::Can(CAN_HandleTypeDef *handler, uint32_t interrupt, uint32_t id) {
    this->handler = handler;
    this->iniciar(interrupt, id);
}

Can::~Can() {
    HAL_CAN_DeInit(this->handler);
}

void Can::iniciar(uint32_t interrupt, uint32_t id) {
    this->tx_header.ExtId = 0;
    this->tx_header.IDE = CAN_ID_STD;
    this->tx_header.RTR = CAN_RTR_DATA;
    this->tx_header.TransmitGlobalTime = DISABLE;
    this->tx_header.StdId = id;

    HAL_CAN_Start(this->handler);
    HAL_CAN_ActivateNotification(this->handler, interrupt);
}

bool Can::enviar(uint8_t *dados, uint8_t tamanho) {
    this->tx_header.DLC = tamanho;
    return (HAL_CAN_AddTxMessage(this->handler, &(this->tx_header), dados, &(this->mailbox)) == HAL_OK);
}

void Can::guardar_dados(uint8_t* alvo) {
    this->lock = false;
    HAL_CAN_GetRxMessage(this->handler, this->interrupt, &(this->rx_header), dados_recebidos);
    memcpy(alvo, dados_recebidos, 8);
    return dados;
}

void Can::setup(uint32_t interrupt, uint32_t id_high, uint32_t id_low, uint32_t mask_high, uint32_t mask_low) {
    this->filtro.FilterActivation = CAN_FILTER_ENABLE;  // Ativa o uso de filtro
    this->filtro.FilterBank = 10;                       // Seleciona o FilterBank a ser utilizado (0 - 13)
    this->filtro.FilterFIFOAssignment = interrupt;      // Canal de interrupção
    this->interrupt = interrupt;

    this->filtro.FilterMode = CAN_FILTERMODE_IDMASK;    // Modo de filtragem (filtro e máscara)
    this->filtro.FilterScale = CAN_FILTERSCALE_32BIT;   // Tamanho do filtro

    // Configuração Filtro e Máscara
    this->filtro.FilterIdHigh = id_high;
    this->filtro.FilterIdLow = id_low;
    this->filtro.FilterMaskIdHigh = mask_high;
    this->filtro.FilterMaskIdLow = mask_low;

    HAL_CAN_ConfigFilter(this->handler, &(this->filtro));
}

void Can::esperar() {
    while(this->lock);
}

#endif /* HAL_CAN_MODULE_ENABLED */
