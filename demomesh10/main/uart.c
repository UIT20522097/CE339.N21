esp_err_t esp_mesh_comm_p2p_start(void)
// {
//     static bool is_comm_p2p_started = false;
//     if (!is_comm_p2p_started) {
//         is_comm_p2p_started = true;
//         // command_send_init();
//         receive_data_init();
//         // mqtt_init();
//         mqtt_app_start();
//         // client_post_init();
//         // xTaskCreate(msg_synthetic, "msg_synthetic", 3072, NULL, 5, NULL);
//         // array_loop_init();
//     }
//     return ESP_OK;
// }