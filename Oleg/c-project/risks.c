#include "security_system.h"

// Functions for risk registry
void add_risk() {
    if (risk_count >= MAX_ITEMS) {
        printf("Maximum number of risks reached!\n");
        return;
    }

    Risk risk;
    risk.id = risk_count + 1;

    printf("\n=== Adding New Risk for %s ===\n", COMPANY_NAME);
    printf("Enter risk name: ");
    scanf(" %[^\n]", risk.name);

    printf("Enter risk description: ");
    scanf(" %[^\n]", risk.description);

    printf("Choose risk level (0-Low, 1-Medium, 2-High, 3-Critical): ");
    int level;
    scanf("%d", &level);
    risk.level = (RiskLevel)level;

    printf("Enter risk owner (responsible employee): ");
    scanf(" %[^\n]", risk.owner);

    // Get restaurant location
    int location_choice;
    get_location_options();
    printf("Select location: ");
    scanf("%d", &location_choice);
    get_location_name(location_choice, risk.location);

    risk.is_mitigated = 0;
    strcpy(risk.mitigation_plan, "Plan not defined");
    strcpy(risk.identification_date, get_current_date());

    risks[risk_count++] = risk;
    printf("\nRisk successfully added with ID: %d\n", risk.id);
}

void list_risks() {
    if (risk_count == 0) {
        printf("\nNo risks available in %s system\n", COMPANY_NAME);
        return;
    }

    printf("\n=== %s Risk Registry ===\n", COMPANY_NAME);
    printf("ID\tName\t\t\tLevel\t\tLocation\t\tStatus\n");
    printf("----------------------------------------------------------------------------------\n");

    for (int i = 0; i < risk_count; i++) {
        printf("%d\t%-20s\t%-10s\t%-20s\t%s\n",
               risks[i].id,
               risks[i].name,
               risk_level_to_string(risks[i].level),
               risks[i].location,
               risks[i].is_mitigated ? "Mitigated" : "Active");
    }
}

void view_risk(int id) {
    for (int i = 0; i < risk_count; i++) {
        if (risks[i].id == id) {
            printf("\n=== Risk ID: %d ===\n", id);
            printf("Name: %s\n", risks[i].name);
            printf("Description: %s\n", risks[i].description);
            printf("Level: %s\n", risk_level_to_string(risks[i].level));
            printf("Location: %s\n", risks[i].location);
            printf("Owner: %s\n", risks[i].owner);
            printf("Identification date: %s\n", risks[i].identification_date);
            printf("Status: %s\n", risks[i].is_mitigated ? "Mitigated" : "Active");
            printf("Mitigation plan: %s\n", risks[i].mitigation_plan);
            return;
        }
    }
    printf("Risk with ID %d not found in %s system\n", id, COMPANY_NAME);
}

void update_risk(int id) {
    for (int i = 0; i < risk_count; i++) {
        if (risks[i].id == id) {
            printf("\n=== Updating Risk ID: %d ===\n", id);

            int choice;
            printf("What would you like to update?\n");
            printf("1. Risk level\n");
            printf("2. Mitigation plan\n");
            printf("3. Mark as mitigated\n");
            printf("4. Update location\n");
            printf("0. Cancel\n");
            printf("Select option: ");
            scanf("%d", &choice);

            switch(choice) {
                case 1:
                    printf("Choose new risk level (0-Low, 1-Medium, 2-High, 3-Critical): ");
                    int level;
                    scanf("%d", &level);
                    risks[i].level = (RiskLevel)level;
                    printf("Risk level updated to %s\n", risk_level_to_string(risks[i].level));
                    break;

                case 2:
                    printf("Enter new mitigation plan: ");
                    getchar(); // Clear buffer
                    scanf(" %[^\n]", risks[i].mitigation_plan);
                    printf("Mitigation plan updated\n");
                    break;

                case 3:
                    risks[i].is_mitigated = 1;
                    printf("Risk marked as mitigated\n");
                    break;

                case 4:
                    get_location_options();
                    printf("Select new location: ");
                    int location_choice;
                    scanf("%d", &location_choice);
                    get_location_name(location_choice, risks[i].location);
                    printf("Location updated to %s\n", risks[i].location);
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
    printf("Risk with ID %d not found in %s system\n", id, COMPANY_NAME);
}

void export_risks_to_file(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error opening file for writing!\n");
        return;
    }

    write_header_to_file(file, "Risk Register");

    fprintf(file, "Total risks: %d\n\n", risk_count);

    int active = 0, mitigated = 0;
    int critical = 0, high = 0, medium = 0, low = 0;

    for (int i = 0; i < risk_count; i++) {
        if (risks[i].is_mitigated) {
            mitigated++;
        } else {
            active++;
            switch (risks[i].level) {
                case CRITICAL: critical++; break;
                case HIGH: high++; break;
                case MEDIUM: medium++; break;
                case LOW: low++; break;
            }
        }
    }

    fprintf(file, "Risk Summary:\n");
    fprintf(file, "  Active risks: %d\n", active);
    fprintf(file, "  Mitigated risks: %d\n\n", mitigated);

    fprintf(file, "Active Risk Distribution:\n");
    fprintf(file, "  Critical: %d\n", critical);
    fprintf(file, "  High: %d\n", high);
    fprintf(file, "  Medium: %d\n", medium);
    fprintf(file, "  Low: %d\n\n", low);

    fprintf(file, "Detailed Risk Register:\n");
    fprintf(file, "------------------------------------------------\n\n");

    for (int i = 0; i < risk_count; i++) {
        fprintf(file, "Risk ID: %d\n", risks[i].id);
        fprintf(file, "Name: %s\n", risks[i].name);
        fprintf(file, "Description: %s\n", risks[i].description);
        fprintf(file, "Level: %s\n", risk_level_to_string(risks[i].level));
        fprintf(file, "Location: %s\n", risks[i].location);
        fprintf(file, "Owner: %s\n", risks[i].owner);
        fprintf(file, "Identification date: %s\n", risks[i].identification_date);
        fprintf(file, "Status: %s\n", risks[i].is_mitigated ? "Mitigated" : "Active");
        fprintf(file, "Mitigation plan: %s\n", risks[i].mitigation_plan);
        fprintf(file, "------------------------------------------------\n\n");
    }

    fclose(file);
    printf("Risks successfully exported to %s\n", filename);
}