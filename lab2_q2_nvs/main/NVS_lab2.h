
//816030798 Non Volatile Storage
#include <stdio.h>
#include <string.h>
#include <sys/unistd.h>
#include <sys/stat.h>
#include "esp_err.h"
#include "esp_log.h"
#include "esp_spiffs.h"



#ifndef NVS_LAB2_H
#define NVS_LAB2_H



bool init_nvs();
void write_to_nvs(const char* words_to_write,const char* file_name);

void rename_file(const char* oldname,const char* newname);

bool read_from_file(const char* file_name,int target_line);

void disable();
#endif

