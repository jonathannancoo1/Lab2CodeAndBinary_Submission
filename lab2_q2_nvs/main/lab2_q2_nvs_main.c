//816030798
#include "NVS_lab2.h"


void app_main(){
init_nvs();
write_to_nvs("this is a test","test_file.txt");
rename_file("test_file.txt","file_under_test.txt");

read_from_file("file_under_test.txt",1);

    
}