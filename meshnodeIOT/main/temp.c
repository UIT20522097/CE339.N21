/* i2c - Simple example

   Simple I2C example that shows how to initialize I2C
   as well as reading and writing from and to registers for a sensor connected over I2C.

   The sensor used in this example is a MPU9250 inertial measurement unit.

   For other examples please check:
   https://github.com/espressif/esp-idf/tree/master/examples

   See README.md file to get detailed usage of this example.

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "esp_log.h"
#include "driver/i2c.h"

static const char *TAG = "SHT30";

#define I2C_MASTER_SCL_IO           13      /*!< GPIO number used for I2C master clock */
#define I2C_MASTER_SDA_IO           12      /*!< GPIO number used for I2C master data  */
#define I2C_MASTER_NUM              0                          /*!< I2C master i2c port number, the number of i2c peripheral interfaces available will depend on the chip */
#define I2C_MASTER_FREQ_HZ          400000                     /*!< I2C master clock frequency */
#define I2C_MASTER_TX_BUF_DISABLE   0                          /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE   0                          /*!< I2C master doesn't need buffer */
#define I2C_MASTER_TIMEOUT_MS       1000

#define SHT30_SENSOR_ADDR                 0x44        /*!< Slave address of the MPU9250 sensor */

/**
 * @brief Read a sequence of bytes from a MPU9250 sensor registers
 */
static esp_err_t mpu9250_register_read(uint8_t reg_addr, uint8_t *data, size_t len)
{
    return i2c_master_write_read_device(I2C_MASTER_NUM, SHT30_SENSOR_ADDR, &reg_addr, 1, data, len, I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS);
}

/**
 * @brief Write a byte to a MPU9250 sensor register
 */
static esp_err_t mpu9250_register_write_byte(uint8_t reg_addr)
{
    int ret;
    uint8_t write_buf[2] = { 0x24, 0x00};

    ret = i2c_master_write_to_device(I2C_MASTER_NUM, SHT30_SENSOR_ADDR, write_buf, sizeof(write_buf), I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS);

    return ret;
}

/**
 * @brief i2c master initialization
 */
static esp_err_t i2c_master_init(void)
{
    int i2c_master_port = I2C_MASTER_NUM;

    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ,
    };

    i2c_param_config(i2c_master_port, &conf);

    return i2c_driver_install(i2c_master_port, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
}
void sendreset()
{
    uint8_t command[2] = {0x30, 0xa2};
    i2c_master_write_to_device(I2C_MASTER_NUM, SHT30_SENSOR_ADDR, command, sizeof(command), I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS);
}

void sht30_init()
{
    (i2c_master_init());
    ESP_LOGI(TAG, "I2C initialized successfully");
}

void sht30_measure(float *cTemp, float *humidity)
{

uint8_t data[6] = {0};
    
    mpu9250_register_write_byte(SHT30_SENSOR_ADDR<<1);
    // vTaskDelay(1);
        for(int i = 0; i<6;i++)
    {
        data[i] = 0;
    }
    /* Read the MPU9250 WHO_AM_I register, on power up the register should have the value 0x71 */
    mpu9250_register_read(SHT30_SENSOR_ADDR<<1|1, data, 6);
    *cTemp = ((((data[0] * 256.0) + data[1]) * 175) / 65535.0) - 45;
    *humidity = ((((data[3] * 256.0) + data[4]) * 100) / 65535.0);
    printf("cTemp: %f\r\n", *cTemp);
    printf("humidity: %f\r\n", *humidity);
}
