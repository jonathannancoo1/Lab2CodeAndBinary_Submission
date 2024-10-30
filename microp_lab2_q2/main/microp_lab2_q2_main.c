//816030907 RTC

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_sleep.h"
#include "driver/gpio.h"
#include "driver/hw_timer.h"
#include "driver/uart.h"
#include "driver/i2c.h"
#include "freertos/semphr.h"
#include "freertos/FreeRTOSConfig.h"
#include "ds3231.h"
#include <i2cdev.h>
#include <string.h>
#include "Final_submission_RTC.h"



void app_main(){

struct tm time  = {
        .tm_year = 124, //since 1900 (2016 - 1900)
        .tm_mon  = 10,  // 0-based
        .tm_mday = 30,
        .tm_hour = 13,
        .tm_min  = 50,
        .tm_sec  = 30
    };


init_RTC();
write_time_to_RTC(time);

while(1){
read_time_from_RTC();
const TickType_t xDelay = 500 / portTICK_PERIOD_MS;

vTaskDelay(xDelay);
}
}