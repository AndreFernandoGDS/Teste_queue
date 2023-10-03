#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

// Defina o tamanho da fila
#define QUEUE_LENGTH 5

// Crie uma fila
QueueHandle_t xQueue;

void sender_task(void *pvParameters) {
    int count = 0;

    while (1) {
        // Envia dados para a fila
        if (xQueueSend(xQueue, &count, portMAX_DELAY) == pdPASS) {
            printf("Enviado: %d\n", count);
            count++;
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void receiver_task(void *pvParameters) {
    int received_data;

    while (1) {
        // Recebe dados da fila
        if (xQueueReceive(xQueue, &received_data, portMAX_DELAY) == pdPASS) {
            printf("Recebido: %d\n", received_data);
        }
    }
}

void app_main() {
    // Crie a fila
    xQueue = xQueueCreate(QUEUE_LENGTH, sizeof(int));

    // Crie as tarefas produtora e consumidora
    xTaskCreate(sender_task, "sender", 2048, NULL, 1, NULL);
    xTaskCreate(receiver_task, "receiver", 2048, NULL, 2, NULL);
}
