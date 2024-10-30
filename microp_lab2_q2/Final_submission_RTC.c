//816030907 RTC

#include "Final_Submission_RTC.h"


bool init_RTC(){


    i2c_config_t pinconfig;


    //Installing driver
    //i2c_driver_install(I2C_NUM_0,I2C_MODE_MASTER);
    //master mode
    pinconfig.mode=I2C_MODE_MASTER;

    //disabling pullups
    pinconfig.sda_pullup_en=GPIO_PULLUP_DISABLE;
    pinconfig.scl_pullup_en=GPIO_PULLUP_DISABLE;


    //Setting SCL as IO 0
    pinconfig.scl_io_num=GPIO_NUM_0;

    //Setting SDA as IO2
    pinconfig.sda_io_num=GPIO_NUM_2;

    //wait for 1000 tics
    pinconfig.clk_stretch_tick = 1000;


    i2c_dev_t dev;
    memset(&dev, 0, sizeof(i2c_dev_t));
    dev.addr=DS3231_ADDR;
    dev.cfg=pinconfig;
    dev.port=I2C_NUM_0;

    esp_err_t status =ds3231_init_desc(&dev,0,GPIO_NUM_2,GPIO_NUM_0);
    
    if (status==ESP_OK){

        return true;
    }
    

        return false;
    
    }

bool write_time_to_RTC(struct tm time){


i2c_config_t pinconfig;



//Installing driver
//i2c_driver_install(I2C_NUM_0,I2C_MODE_MASTER);
 //master mode
pinconfig.mode=I2C_MODE_MASTER;

//disabling pullups
pinconfig.sda_pullup_en=GPIO_PULLUP_DISABLE;
pinconfig.scl_pullup_en=GPIO_PULLUP_DISABLE;


//Setting SCL as IO 0
pinconfig.scl_io_num=GPIO_NUM_0;

//Setting SDA as IO2
pinconfig.sda_io_num=GPIO_NUM_2;

//wait for 1000 tics
pinconfig.clk_stretch_tick = 1000;


    i2c_dev_t dev;
    memset(&dev, 0, sizeof(i2c_dev_t));
    dev.addr=DS3231_ADDR;
    dev.cfg=pinconfig;
    dev.port=I2C_NUM_0;


    if (ds3231_set_time(&dev, &time) == ESP_OK)
        {
            printf("Time has been set\n");
            
            return true;
        }

    return false;

    
  
}


struct tm read_time_from_RTC(){



    
i2c_config_t pinconfig;



//Installing driver
//i2c_driver_install(I2C_NUM_0,I2C_MODE_MASTER);
 //master mode
pinconfig.mode=I2C_MODE_MASTER;

//disabling pullups
pinconfig.sda_pullup_en=GPIO_PULLUP_DISABLE;
pinconfig.scl_pullup_en=GPIO_PULLUP_DISABLE;


//Setting SCL as IO 0
pinconfig.scl_io_num=GPIO_NUM_0;

//Setting SDA as IO2
pinconfig.sda_io_num=GPIO_NUM_2;

//wait for 1000 tics
pinconfig.clk_stretch_tick = 1000;
   
   
    struct tm time;
    i2c_dev_t dev;
    memset(&dev, 0, sizeof(i2c_dev_t));
    dev.addr=DS3231_ADDR;
    dev.cfg=pinconfig;
    dev.port=I2C_NUM_0;

if (ds3231_get_time(&dev, &time) != ESP_OK)
{
    printf("Year: %d\n", time.year+1900);
    printf("Month: %d\n", time.month);
    printf("Day: %d\n", time.day);
    printf("Hour: %d\n", time.hour);
    printf("Minute: %d\n", time.min);
    printf("Second: %d\n", time.sec);

    return time;
}
printf("Fail \n");
return time;

}


