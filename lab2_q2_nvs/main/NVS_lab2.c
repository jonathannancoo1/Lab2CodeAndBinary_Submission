// 8166030798 Non-Volatile Storage
#include "NVS_lab2.h"  // Include custom header file for non-volatile storage (NVS) functions


static const char *TAG = "example";

// Function to initialize SPIFFS (SPI Flash File System)
bool init_nvs() {
    // Log the start of the SPIFFS initialization process
    ESP_LOGI(TAG, "Initializing SPIFFS");
    
    // Define the configuration for SPIFFS
    esp_vfs_spiffs_conf_t conf = {
        .base_path = "/spiffs",               // Mount point of the filesystem
        .partition_label = NULL,              // Use default SPIFFS partition
        .max_files = 5,                       // Maximum number of open files at a time
        .format_if_mount_failed = true        // Format partition if mount fails
    };

    // Register the SPIFFS filesystem with the provided configuration
    esp_err_t ret = esp_vfs_spiffs_register(&conf);

    // Check if SPIFFS was successfully initialized
    if (ret != ESP_OK) {
        // Log errors based on the type of failure
        if (ret == ESP_FAIL) {
            ESP_LOGE(TAG, "Failed to mount or format filesystem");
        } else if (ret == ESP_ERR_NOT_FOUND) {
            ESP_LOGE(TAG, "Failed to find SPIFFS partition");
        } else {
            ESP_LOGE(TAG, "Failed to initialize SPIFFS (%s)", esp_err_to_name(ret));
        }
        return true;  // Exit if initialization failed
    }

    // Variables to hold total and used space in the SPIFFS partition
    size_t total = 0, used = 0;
    ret = esp_spiffs_info(NULL, &total, &used);
    
    // Check if SPIFFS partition information was successfully retrieved
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to get SPIFFS partition information (%s)", esp_err_to_name(ret));
    } else {
        // Log the partition size and amount of used space
        ESP_LOGI(TAG, "Partition size: total: %d, used: %d", total, used);
        }
         return true;
}
// Function to write a string to a specified file in SPIFFS
void write_to_nvs(const char* words_to_write, const char* file_name) {
    // Log the start of the file opening process
    ESP_LOGI(TAG, "Opening file");

    // Construct the full file path with the specified file name
    char file_path[32]; // Adjust size as needed
    snprintf(file_path, sizeof(file_path), "/spiffs/%s", file_name);

    // Open the file in write mode
    FILE* f = fopen(file_path, "w");
    if (f == NULL) {
        // Log an error if the file fails to open
        ESP_LOGE(TAG, "Failed to open file for writing");
        return;
    }

    // Write the provided string to the file
    fprintf(f, "%s\n", words_to_write);
    
    // Close the file after writing
    fclose(f);
    ESP_LOGI(TAG, "File written");  // Log a success message
}


void rename_file(const char* oldname, const char* newname) {    
    
    // Check if destination file exists before renaming
    struct stat st;
    if (stat("/spiffs/file_under_test.txt", &st) == 0) {
        // Delete it if it exists
        unlink("/spiffs/file_under_test.txt");
    }

    // Rename original file
    ESP_LOGI(TAG, "Renaming file");
    if (rename("/spiffs/test_file.txt", "/spiffs/file_under_test.txt") != 0) {
        ESP_LOGE(TAG, "Rename failed");
    }
}
bool read_from_file(const char* file_name, int target_line) {
    // Open the specified file for reading
    ESP_LOGI(TAG, "Reading file");
    FILE* f = fopen("/spiffs/file_under_test.txt", "r");
    if (f == NULL) {
        ESP_LOGE(TAG, "Failed to open file for reading");
        return false;
    }

    char line[32];
    int current_line = 0;

    // Read through the file line by line
    while (fgets(line, sizeof(line), f) != NULL) {
        current_line++;
        // Check if the current line matches the target line
        if (current_line == target_line) {
            // Strip newline
            char* pos = strchr(line, '\n');
            if (pos) {
                *pos = '\0';
            }
            ESP_LOGI(TAG, "Read from line %d: '%s'", target_line, line);
            fclose(f);
            return true;
        }
    }

    // If we reach here, the target line was not found
    ESP_LOGE(TAG, "Line %d does not exist in the file", target_line);
    fclose(f);
    return false;

}




void disable(){

    // All done, unmount partition and disable SPIFFS
    esp_vfs_spiffs_unregister(NULL);
    ESP_LOGI(TAG, "SPIFFS unmounted");
}