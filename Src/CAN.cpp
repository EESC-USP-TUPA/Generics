#include "CAN.hpp"

#ifdef HAL_CAN_MODULE_ENABLED

Can::Can(CAN_HandleTypeDef *handler, uint32_t interrupt)
{
    this->handler = handler;
    this->tx_header.ExtId = 0;
    this->tx_header.IDE = CAN_ID_STD;
    this->tx_header.RTR = CAN_RTR_DATA;
    this->tx_header.TransmitGlobalTime = DISABLE;
    this->tx_header.StdId = 0;

    HAL_CAN_Start(this->handler);
    HAL_CAN_ActivateNotification(this->handler, interrupt);
}

Can::~Can()
{
    HAL_CAN_DeInit(this->handler);
}

bool Can::enviar(uint32_t id_mensagem, uint8_t *dados, uint8_t tamanho)
{
	this->tx_header.StdId = id_mensagem;
    this->tx_header.DLC = tamanho;
    return (HAL_CAN_AddTxMessage(this->handler, &(this->tx_header), dados, &(this->mailbox)) == HAL_OK);
}

void Can::guardar_dados(uint8_t* alvo)
{
    this->lock = false;
    HAL_CAN_GetRxMessage(this->handler, this->interrupt, &(this->rx_header), dados_recebidos);
    memcpy(alvo, dados_recebidos, 8);
}

void Can::definir_filtro(uint32_t interrupt, uint32_t id_filtro, uint32_t mascara_filtro)
{
    this->filtro.FilterActivation = CAN_FILTER_ENABLE;  // Ativa o uso de filtro
    this->filtro.FilterBank = 10;                       // Seleciona o FilterBank a ser utilizado (0 - 13)
    this->filtro.FilterFIFOAssignment = interrupt;      // Canal de interrupção
    this->interrupt = interrupt;

    this->filtro.FilterMode = CAN_FILTERMODE_IDMASK;    // Modo de filtragem (filtro e máscara)
    this->filtro.FilterScale = CAN_FILTERSCALE_32BIT;   // Tamanho do filtro

    // Configuração Filtro e Máscara
    this->filtro.FilterIdHigh = ((id_filtro << 5)  | (id_filtro >> (32 - 5))) & 0xFFFF;
    this->filtro.FilterIdLow = (id_filtro >> (11 - 3)) & 0xFFF8;
    this->filtro.FilterMaskIdHigh = ((mascara_filtro << 5)  | (mascara_filtro >> (32 - 5))) & 0xFFFF;
    this->filtro.FilterMaskIdLow = (mascara_filtro >> (11 - 3)) & 0xFFF8;

    HAL_CAN_ConfigFilter(this->handler, &(this->filtro));
}

void Can::esperar(uint32_t timeout)
{
	this->lock = true;
	uint32_t inicio = HAL_GetTick();
    while(this->lock)
    {
    	if (HAL_GetTick() - inicio > timeout)
    	{
    		this->lock = false;
    	}
    };
}

#endif /* HAL_CAN_MODULE_ENABLED */
