#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <ctype.h>
#include <unistd.h> // For sleep function
#include "security_system.h"

Document documents[MAX_ITEMS];
int doc_count = 0;

Risk risks[MAX_ITEMS];
int risk_count = 0;

Control controls[MAX_ITEMS];
int control_count = 0;

Audit audits[MAX_ITEMS];
int audit_count = 0;

Incident incidents[MAX_ITEMS];
int incident_count = 0;

// Predefined users with access levels - using simple passwords as requested
User users[] = {
        {"admin", "admin123456", ADMIN},
        {"manager", "manager123456", MANAGER},
        {"employee", "employee123456", EMPLOYEE}
};

int num_users = sizeof(users) / sizeof(User);

// Function to convert access level enum to string
void get_access_level_name(AccessLevel level, char* level_name) {
    switch(level) {
        case ADMIN:
            strcpy(level_name, "Administrator");
            break;
        case MANAGER:
            strcpy(level_name, "Manager");
            break;
        case EMPLOYEE:
            strcpy(level_name, "Employee");
            break;
        default:
            strcpy(level_name, "Unknown");
    }
}

// Loading animation
void show_loading_animation() {
    printf("\n");
    printf("    Initializing system ");
    for (int i = 0; i < 5; i++) {
        printf("*");
        fflush(stdout);
        sleep(1);
    }
    printf("\n\n");
}

// Password validation function
int validate_password(const char* input, const char* correct_password) {
    return strcmp(input, correct_password) == 0;
}

// Authentication function with simple passwords
AccessLevel login() {
    char username[MAX_NAME_LENGTH];
    char password[PASSWORD_LENGTH + 1];
    int attempts = MAX_ATTEMPTS;

    while (attempts--) {
        clear_screen();
        printf("\n*********************************************************\n");
        printf("*                                                       *\n");
        printf("*         %s SECURITY MANAGEMENT SYSTEM        *\n", COMPANY_NAME);
        printf("*                         LOGIN                         *\n");
        printf("*                                                       *\n");
        printf("*********************************************************\n\n");

        printf("Enter username: ");
        scanf("%s", username);

        printf("Enter password: ");
        scanf("%16s", password);

        // Check each registered user
        for (int i = 0; i < num_users; i++) {
            if (strcmp(username, users[i].username) == 0) {
                if (validate_password(password, users[i].password)) {
                    printf("\nLogin successful!");
                    printf("\nPress Enter to continue...");
                    getchar(); // Clear buffer
                    getchar(); // Wait for Enter
                    return users[i].access_level;
                }
            }
        }

        printf("\nInvalid username or password. Attempts left: %d\n", attempts);
        printf("\nPress Enter to continue...");
        getchar(); // Clear buffer
        getchar(); // Wait for Enter
    }

    printf("\nToo many failed attempts. Exiting...\n");
    exit(1);
}

// Function to display menu based on access level
void show_menu_based_on_access(AccessLevel level) {
    clear_screen();
    printf("\n*********************************************************\n");
    printf("*                                                       *\n");
    printf("*         %s SECURITY MANAGEMENT SYSTEM        *\n", COMPANY_NAME);
    printf("*                                                       *\n");
    printf("*********************************************************\n");

    printf("\n1. Document Management");

    // Risk management - Only available to Manager and Admin
    if (level >= MANAGER) {
        printf("\n2. Risk Management");
    }

    // Control management - Only available to Manager and Admin
    if (level >= MANAGER) {
        printf("\n3. Controls Management");
    }

    // Audit management - Only available to Admin
    if (level >= ADMIN) {
        printf("\n4. Audit Management");
    }

    // Incident reporting - Available to all
    printf("\n5. Incident Reporting");

    // Reports - Managers and Admin only
    if (level >= MANAGER) {
        printf("\n6. Generate Reports");
    }

    printf("\n0. Exit");
    printf("\n\nEnter your choice: ");
}

int main() {
    int choice;
    AccessLevel current_access_level;
    char level_name[MAX_NAME_LENGTH];

    // Display initial loading animation
    clear_screen();
    printf("\n*********************************************************\n");
    printf("*                                                       *\n");
    printf("*         %s SECURITY MANAGEMENT SYSTEM        *\n", COMPANY_NAME);
    printf("*                                                       *\n");
    printf("*********************************************************\n");

    show_loading_animation();

    // Login and get access level
    current_access_level = login();

    // Display welcome banner with access level information
    clear_screen();
    get_access_level_name(current_access_level, level_name);

    printf("\n");
    printf("\n*********************************************************\n");
    printf("*                                                       *\n");
    printf("*         %s SECURITY MANAGEMENT SYSTEM        *\n", COMPANY_NAME);
    printf("*                                                       *\n");
    printf("*         Ensuring Safety and Security for All          *\n");
    printf("*              La Placinte Locations                    *\n");
    printf("*                                                       *\n");
    printf("*         Welcome, %-20s                 *\n", level_name);
    printf("*                                                       *\n");
    printf("*********************************************************\n");
    printf("\nSystem initialized: %s\n", get_current_date());
    printf("\nPress Enter to continue...");
    getchar();

    do {
        clear_screen();
        show_menu_based_on_access(current_access_level);
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                document_menu();
                break;
            case 2:
                if (current_access_level >= MANAGER) {
                    risk_menu();
                } else {
                    printf("\nAccess denied: You need Manager or Admin privileges for this function.");
                    printf("\nPress Enter to continue...");
                    getchar(); // Clear buffer
                    getchar(); // Pause
                }
                break;
            case 3:
                if (current_access_level >= MANAGER) {
                    control_menu();
                } else {
                    printf("\nAccess denied: You need Manager or Admin privileges for this function.");
                    printf("\nPress Enter to continue...");
                    getchar(); // Clear buffer
                    getchar(); // Pause
                }
                break;
            case 4:
                if (current_access_level >= ADMIN) {
                    audit_menu();
                } else {
                    printf("\nAccess denied: You need Admin privileges for this function.");
                    printf("\nPress Enter to continue...");
                    getchar(); // Clear buffer
                    getchar(); // Pause
                }
                break;
            case 5:
                incident_menu();
                break;
            case 6:
                if (current_access_level >= MANAGER) {
                    report_menu();
                } else {
                    printf("\nAccess denied: You need Manager or Admin privileges for this function.");
                    printf("\nPress Enter to continue...");
                    getchar(); // Clear buffer
                    getchar(); // Pause
                }
                break;
            case 0:
                clear_screen();
                printf("\n*********************************************************\n");
                printf("*                                                       *\n");
                printf("*  Thank you for using %s Security System       *\n", COMPANY_NAME);
                printf("*              Exiting Program                          *\n");
                printf("*                                                       *\n");
                printf("*********************************************************\n");
                break;
            default:
                printf("Invalid choice!\n");
                printf("\nPress Enter to continue...");
                getchar(); // Clear buffer
                getchar(); // Pause
        }

    } while (choice != 0);

    return 0;
}