#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"

#define PRINT_INTERVAL pdMS_TO_TICKS(1000) // 1 second
#define LOOP_DURATION pdMS_TO_TICKS(20000)  // 20 seconds

void helloWorldTask(void *pvParameters) {
    TickType_t xStartTime = xTaskGetTickCount(); // Get current tick count
    TickType_t xElapsedTime = 0;

    while (xElapsedTime < LOOP_DURATION) {
        printf("Hello, World!\n"); // Print message

        // Delay for 1 second
        vTaskDelay(PRINT_INTERVAL);

        // Update elapsed time
        xElapsedTime = xTaskGetTickCount() - xStartTime;
    }

    // Optionally, cleanup or notify that the task has finished
    printf("Loop finished after 20 seconds.\n");

    // Delete the task if not needed anymore
    vTaskDelete(NULL);
}

void app_main(void) {
    // Create the hello world task
    xTaskCreate(helloWorldTask, "HelloWorldTask", 2048, NULL, 1, NULL);
}
