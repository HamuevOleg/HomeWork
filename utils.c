#include "security_system.h"

char* get_current_date() {
    static char date_str[MAX_DATE_LENGTH];
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(date_str, MAX_DATE_LENGTH, "%Y-%m-%d %H:%M:%S", t);
    return date_str;
}

void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

char* risk_level_to_string(RiskLevel level) {
    switch(level) {
        case LOW: return "Low";
        case MEDIUM: return "Medium";
        case HIGH: return "High";
        case CRITICAL: return "Critical";
        default: return "Unknown";
    }
}

void write_header_to_file(FILE* file, const char* title) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char date_str[MAX_DATE_LENGTH];

    strftime(date_str, MAX_DATE_LENGTH, "%Y-%m-%d %H:%M:%S", t);

    fprintf(file, "=== %s ===\n", COMPANY_NAME);
    fprintf(file, "%s\n", title);
    fprintf(file, "Generated: %s\n\n", date_str);
}

void get_location_options() {
    printf("\nAvailable Locations:\n");
    printf("1. La Placinte - Central\n");
    printf("2. La Placinte - North Branch\n");
    printf("3. La Placinte - East Branch\n");
    printf("4. La Placinte - South Branch\n");
    printf("5. La Placinte - West Branch\n");
}

void get_location_name(int location_number, char* location_name) {
    switch(location_number) {
        case 1:
            strcpy(location_name, "La Placinte - Central");
            break;
        case 2:
            strcpy(location_name, "La Placinte - North Branch");
            break;
        case 3:
            strcpy(location_name, "La Placinte - East Branch");
            break;
        case 4:
            strcpy(location_name, "La Placinte - South Branch");
            break;
        case 5:
            strcpy(location_name, "La Placinte - West Branch");
            break;
        default:
            strcpy(location_name, "Unknown Location");
    }
}