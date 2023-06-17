#include "mesh_light.h"

static const char *MESH_TAG = "ROOT_TX";
int i;
esp_err_t err;
int send_count = 0;
mesh_addr_t route_table[CONFIG_MESH_ROUTE_TABLE_SIZE];
int route_table_size = 0;
mesh_data_t data;

uint8_t Address[6];

extern char RunTime[1024];
float cpu = 0;
bool HaveSend = 0;
mesh_addr_t route_table[CONFIG_MESH_ROUTE_TABLE_SIZE];
char msg1[CONFIG_MESH_ROUTE_TABLE_SIZE * 10] = "";
mesh_data_t data;
float temp = 0;
float humid = 0;

uint8_t * _jpg_buf;
size_t _jpg_buf_len;


void esp_mesh_p2p_tx_main()
{
    char ms[1000];
    data.data = (uint8_t *)ms;
    data.size = sizeof(ms);
    data.proto = MESH_PROTO_BIN;
    data.tos = MESH_TOS_P2P;
    TakePicture(_jpg_buf, _jpg_buf_len);
    sht30_measure(&temp, &humid);
    sprintf(ms,"%d:%.2f", NodeID, temp);
    data_synthesis(msg1);
    if(strlen(msg1) != 0)
    {
        strcat(ms,",");
        strcat(ms,msg1);
        // strcat(ms,",");
        // strcat(ms, (char *)_jpg_buf);
    }
    esp_mesh_send(NULL, &data, MESH_DATA_P2P , NULL, 0);
    printf("Send data: %s\r\n", data.data);
    HaveSend = 1;
    vTaskDelay(500);
}
void DelaySendData(void)
{
    err = init_camera();
    if (err != ESP_OK)
    {
        printf("err: %s\n", esp_err_to_name(err));
        return;
    }
    sht30_init();
    while(1)
    {
        if(HaveSend == 0)
        {
            esp_mesh_p2p_tx_main();
        }
        HaveSend = 0;
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}
void tx_mesh_init(void)
{
    // xTaskCreatePinnedToCore(esp_mesh_p2p_tx_main, "MPTX", 8192, NULL, 5, NULL, 0);
    xTaskCreatePinnedToCore(DelaySendData, "DelaySendData", 8192, NULL, 5, NULL, 0);
}