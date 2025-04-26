#include "security_system.h"

// Functions for controls
void add_control() {
    if (control_count >= MAX_ITEMS) {
        printf("Maximum number of controls reached!\n");
        return;
    }

    if (risk_count == 0) {
        printf("You need to add at least one risk first!\n");
        return;
    }

    Control control;
    control.id = control_count + 1;

    printf("\n=== Adding New Control for %s ===\n", COMPANY_NAME);
    printf("Enter control name: ");
    scanf(" %[^\n]", control.name);

    printf("Enter control description: ");
    scanf(" %[^\n]", control.description);

    list_risks();
    printf("Select risk ID to link: ");
    scanf("%d", &control.risk_id);

    // Check if risk exists
    int risk_exists = 0;
    int risk_index = -1;
    for (int i = 0; i < risk_count; i++) {
        if (risks[i].id == control.risk_id) {
            risk_exists = 1;
            risk_index = i;
            break;
        }
    }

    if (!risk_exists) {
        printf("Risk with ID %d does not exist!\n", control.risk_id);
        return;
    }

    printf("Enter responsible person: ");
    scanf(" %[^\n]", control.responsible_person);

    // Use the same location as the linked risk
    strcpy(control.location, risks[risk_index].location);
    printf("Control location set to: %s (same as linked risk)\n", control.location);

    control.is_effective = 1;  // Effective by default
    strcpy(control.implementation_date, get_current_date());
    strcpy(control.last_review_date, control.implementation_date);

    controls[control_count++] = control;
    printf("\nControl successfully added with ID: %d\n", control.id);
}

void list_controls() {
    if (control_count == 0) {
        printf("\nNo controls available in %s system\n", COMPANY_NAME);
        return;
    }

    printf("\n=== %s Control List ===\n", COMPANY_NAME);
    printf("ID\tName\t\t\tLinked Risk\tLocation\t\tStatus\n");
    printf("----------------------------------------------------------------------------------\n");

    for (int i = 0; i < control_count; i++) {
        printf("%d\t%-20s\t%-10d\t%-20s\t%s\n",
               controls[i].id,
               controls[i].name,
               controls[i].risk_id,
               controls[i].location,
               controls[i].is_effective ? "Effective" : "Ineffective");
    }
}

void view_control(int id) {
    for (int i = 0; i < control_count; i++) {
        if (controls[i].id == id) {
            printf("\n=== Control ID: %d ===\n", id);
            printf("Name: %s\n", controls[i].name);
            printf("Description: %s\n", controls[i].description);
            printf("Linked Risk ID: %d\n", controls[i].risk_id);
            printf("Location: %s\n", controls[i].location);
            printf("Responsible Person: %s\n", controls[i].responsible_person);
            printf("Implementation Date: %s\n", controls[i].implementation_date);
            printf("Last Review Date: %s\n", controls[i].last_review_date);
            printf("Status: %s\n", controls[i].is_effective ? "Effective" : "Ineffective");
            return;
        }
    }
    printf("Control with ID %d not found in %s system\n", id, COMPANY_NAME);
}

void update_control(int id) {
    for (int i = 0; i < control_count; i++) {
        if (controls[i].id == id) {
            printf("\n=== Updating Control ID: %d ===\n", id);

            int choice;
            printf("What would you like to update?\n");
            printf("1. Mark as ineffective\n");
            printf("2. Mark as effective\n");
            printf("3. Update responsible person\n");
            printf("4. Update review date (to today)\n");
            printf("0. Cancel\n");
            printf("Select option: ");
            scanf("%d", &choice);

            switch(choice) {
                case 1:
                    controls[i].is_effective = 0;
                    printf("Control marked as ineffective\n");
                    break;

                case 2:
                    controls[i].is_effective = 1;
                    printf("Control marked as effective\n");
                    break;

                case 3:
                    printf("Enter new responsible person: ");
                    getchar(); // Clear buffer
                    scanf(" %[^\n]", controls[i].responsible_person);
                    printf("Responsible person updated\n");
                    break;

                case 4:
                    strcpy(controls[i].last_review_date, get_current_date());
                    printf("Review date updated to %s\n", controls[i].last_review_date);
                    break;

                case 0:
                    printf("Update canceled\n");
                    break;

                default:
                    printf("Invalid choice\n");
            }
            return;
        }
    }
    printf("Control with ID %d not found in %s system\n", id, COMPANY_NAME);
}