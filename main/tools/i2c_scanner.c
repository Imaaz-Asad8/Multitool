#include "i2c_scanner.h"
#include "esp_err.h"
#include "esp_log.h"

int scanner(i2c_master_bus_handle_t bus, uint8_t *addresses) {
  esp_err_t result;
  int count = 0;

  for (uint8_t addr = 0x08; addr <= 0x77; addr++) {
    result = i2c_master_probe(bus, addr, 50);

    if (result == ESP_OK) {
      addresses[count] = addr;
      count++;
      ESP_LOGI("I2C", "Device found at 0x%02X", addr);

    } else if (result == ESP_ERR_TIMEOUT) {

      ESP_LOGI("I2C", "Timeout at 0x%02X", addr);
    }
  }
  ESP_LOGI("I2C", "Scan Complete");

  return count;
}