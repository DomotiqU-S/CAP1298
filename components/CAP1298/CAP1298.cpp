#include "CAP1298.hpp"


CAP1298::CAP1298(const gpio_num_t sda, const gpio_num_t scl, const uint32_t freq, const uint8_t address)
{
    if(sda == scl) {
        ESP_LOGE(TAG, "SDA and SCL pins must be different");
        m_invalid_constructor = ESP_ERR_INVALID_ARG;
        return;
    }
    this->m_address = address;
    
    this->busController = I2CController::getInstance(); // new I2CController(address, sda, scl, freq);
}

CAP1298::~CAP1298()
{
}

esp_err_t CAP1298::begin() const
{
    esp_err_t ret;
    uint8_t tx_buffer[1];
    ret = this->busController->begin();

    if (ret == ESP_OK)
    {
        tx_buffer[0] = 0x8C;
        ret |= this->busController->writeByte(this->m_address, tx_buffer, CAP1298_MULTIPLE_TOUCH_CONFIG);
        tx_buffer[0] = 0x5F;
        ret |= this->busController->writeByte(this->m_address, tx_buffer, CAP1298_SENSITIVITY_CONTROL);
        tx_buffer[0] = 0x00;
        ret |= this->busController->writeByte(this->m_address, tx_buffer, CAP1298_REPEAT_RATE_ENABLE);
    }
    return ret;
}

bool CAP1298::touchStatusChanged() const
{
    uint8_t rx_buffer[1];
    uint8_t tx_buffer[1];
    this->busController->readByte(this->m_address,rx_buffer, CAP1298_MAIN_CONTROL);
    bool touchStatus = rx_buffer[0] & CAP1298_INT_MASK;
    
    // reset the interrupt
    tx_buffer[0] = 0x00;
    this->busController->writeByte(this->m_address, tx_buffer, CAP1298_MAIN_CONTROL);
    return touchStatus;
}

void CAP1298::updateTouchStatus()
{
    uint8_t rx_buffer[1];

    this->busController->readByte(this->m_address, rx_buffer, CAP1298_INPUT_STATUS);

    m_newTouches = (m_touchData ^ rx_buffer[0]) & rx_buffer[0];
	m_newReleases = (m_touchData ^ rx_buffer[0]) & m_touchData;
	m_touchData=rx_buffer[0];
}