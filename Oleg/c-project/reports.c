#include "security_system.h"

// Reporting functions
void generate_risk_report() {
    printf("\n=== %s RISK REPORT ===\n", COMPANY_NAME);
    printf("Report date: %s\n\n", get_current_date());

    int active_risks = 0;
    int mitigated_risks = 0;

    for (int i = 0; i < risk_count; i++) {
        if (risks[i].is_mitigated) {
            mitigated_risks++;
        } else {
            active_risks++;
        }
    }

    printf("Total number of risks: %d\n", risk_count);
    printf("Active risks: %d\n", active_risks);
    printf("Mitigated risks: %d\n\n", mitigated_risks);

    int critical = 0, high = 0, medium = 0, low = 0;

    for (int i = 0; i < risk_count; i++) {
        if (!risks[i].is_mitigated) {  // Count only active risks
            switch (risks[i].level) {
                case CRITICAL: critical++; break;
                case HIGH: high++; break;
                case MEDIUM: medium++; break;
                case LOW: low++; break;
            }
        }
    }

    printf("Active risk distribution by level:\n");
    printf("Critical: %d\n", critical);
    printf("High: %d\n", high);
    printf("Medium: %d\n", medium);
    printf("Low: %d\n\n", low);

    // Location distribution
    printf("Active risks by location:\n");
    printf("Location\t\t\tNumber of Active Risks\n");
    printf("-----------------------------------------------\n");

    char locations[MAX_ITEMS][MAX_NAME_LENGTH];
    int location_count = 0;
    int location_risks[MAX_ITEMS] = {0};

    // Collect unique locations and count risks per location
    for (int i = 0; i < risk_count; i++) {
        if (!risks[i].is_mitigated) {
            int found = 0;
            for (int j = 0; j < location_count; j++) {
                if (strcmp(locations[j], risks[i].location) == 0) {
                    location_risks[j]++;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                strcpy(locations[location_count], risks[i].location);
                location_risks[location_count] = 1;
                location_count++;
            }
        }
    }

    // Print location distribution
    for (int i = 0; i < location_count; i++) {
        printf("%-30s\t%d\n", locations[i], location_risks[i]);
    }
    printf("\n");

    if (critical > 0) {
        printf("WARNING: There are critical risks requiring immediate attention!\n\n");

        printf("List of critical risks:\n");
        printf("ID\tName\t\t\tLocation\t\tOwner\n");
        printf("----------------------------------------------------------------\n");

        for (int i = 0; i < risk_count; i++) {
            if (risks[i].level == CRITICAL && !risks[i].is_mitigated) {
                printf("%d\t%-20s\t%-20s\t%-20s\n",
                       risks[i].id,
                       risks[i].name,
                       risks[i].location,
                       risks[i].owner);
            }
        }
    }
}

void generate_incident_report() {
    printf("\n=== %s INCIDENT REPORT ===\n", COMPANY_NAME);
    printf("Report date: %s\n\n", get_current_date());

    int open_incidents = 0;
    int resolved_incidents = 0;

    for (int i = 0; i < incident_count; i++) {
        if (incidents[i].is_resolved) {
            resolved_incidents++;
        } else {
            open_incidents++;
        }
    }

    printf("Total number of incidents: %d\n", incident_count);
    printf("Open incidents: %d\n", open_incidents);
    printf("Resolved incidents: %d\n\n", resolved_incidents);

    int critical = 0, high = 0, medium = 0, low = 0;

    for (int i = 0; i < incident_count; i++) {
        if (!incidents[i].is_resolved) {  // Count only open incidents
            switch (incidents[i].severity) {
                case CRITICAL: critical++; break;
                case HIGH: high++; break;
                case MEDIUM: medium++; break;
                case LOW: low++; break;
            }
        }
    }

    printf("Open incident distribution by severity:\n");
    printf("Critical: %d\n", critical);
    printf("High: %d\n", high);
    printf("Medium: %d\n", medium);
    printf("Low: %d\n\n", low);

    // Location distribution
    printf("Open incidents by location:\n");
    printf("Location\t\t\tNumber of Open Incidents\n");
    printf("-----------------------------------------------\n");

    char locations[MAX_ITEMS][MAX_NAME_LENGTH];
    int location_count = 0;
    int location_incidents[MAX_ITEMS] = {0};

    // Collect unique locations and count incidents per location
    for (int i = 0; i < incident_count; i++) {
        if (!incidents[i].is_resolved) {
            int found = 0;
            for (int j = 0; j < location_count; j++) {
                if (strcmp(locations[j], incidents[i].location) == 0) {
                    location_incidents[j]++;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                strcpy(locations[location_count], incidents[i].location);
                location_incidents[location_count] = 1;
                location_count++;
            }
        }
    }

    // Print location distribution
    for (int i = 0; i < location_count; i++) {
        printf("%-30s\t%d\n", locations[i], location_incidents[i]);
    }
    printf("\n");

    if (critical > 0) {
        printf("WARNING: There are critical incidents requiring immediate attention!\n\n");

        printf("List of critical incidents:\n");
        printf("ID\tName\t\t\tLocation\t\tDetection Date\n");
        printf("----------------------------------------------------------------\n");

        for (int i = 0; i < incident_count; i++) {
            if (incidents[i].severity == CRITICAL && !incidents[i].is_resolved) {
                printf("%d\t%-20s\t%-20s\t%-20s\n",
                       incidents[i].id,
                       incidents[i].name,
                       incidents[i].location,
                       incidents[i].detection_date);
            }
        }
    }
}

void generate_full_system_report(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error opening file for writing!\n");
        return;
    }

    fprintf(file, "==========================================================\n");
    fprintf(file, "             %s SECURITY MANAGEMENT SYSTEM\n", COMPANY_NAME);
    fprintf(file, "                COMPREHENSIVE SYSTEM REPORT\n");
    fprintf(file, "                 Generated: %s\n", get_current_date());
    fprintf(file, "==========================================================\n\n");

    // System overview
    fprintf(file, "SYSTEM OVERVIEW\n");
    fprintf(file, "----------------------------------------------------------\n");
    fprintf(file, "Documents registered: %d\n", doc_count);
    fprintf(file, "Risks identified: %d\n", risk_count);
    fprintf(file, "Controls implemented: %d\n", control_count);
    fprintf(file, "Audits conducted: %d\n", audit_count);
    fprintf(file, "Incidents reported: %d\n\n", incident_count);

    // Risk summary
    int active_risks = 0, mitigated_risks = 0;
    int critical = 0, high = 0, medium = 0, low = 0;

    for (int i = 0; i < risk_count; i++) {
        if (risks[i].is_mitigated) {
            mitigated_risks++;
        } else {
            active_risks++;
            switch (risks[i].level) {
                case CRITICAL: critical++; break;
                case HIGH: high++; break;
                case MEDIUM: medium++; break;
                case LOW: low++; break;
            }
        }
    }

    fprintf(file, "RISK SUMMARY\n");
    fprintf(file, "----------------------------------------------------------\n");
    fprintf(file, "Active risks: %d\n", active_risks);
    fprintf(file, "Mitigated risks: %d\n", mitigated_risks);
    fprintf(file, "Risk breakdown by severity:\n");
    fprintf(file, "  Critical: %d\n", critical);
    fprintf(file, "  High: %d\n", high);
    fprintf(file, "  Medium: %d\n", medium);
    fprintf(file, "  Low: %d\n\n", low);

    // Incident summary
    int open_incidents = 0, resolved_incidents = 0;
    critical = 0; high = 0; medium = 0; low = 0;

    for (int i = 0; i < incident_count; i++) {
        if (incidents[i].is_resolved) {
            resolved_incidents++;
        } else {
            open_incidents++;
            switch (incidents[i].severity) {
                case CRITICAL: critical++; break;
                case HIGH: high++; break;
                case MEDIUM: medium++; break;
                case LOW: low++; break;
            }
        }
    }

    fprintf(file, "INCIDENT SUMMARY\n");
    fprintf(file, "----------------------------------------------------------\n");
    fprintf(file, "Open incidents: %d\n", open_incidents);
    fprintf(file, "Resolved incidents: %d\n", resolved_incidents);
    fprintf(file, "Open incident breakdown by severity:\n");
    fprintf(file, "  Critical: %d\n", critical);
    fprintf(file, "  High: %d\n", high);
    fprintf(file, "  Medium: %d\n", medium);
    fprintf(file, "  Low: %d\n\n", low);

    // Location summary
    fprintf(file, "LOCATION RISK PROFILE\n");
    fprintf(file, "----------------------------------------------------------\n");

    char locations[MAX_ITEMS][MAX_NAME_LENGTH];
    int location_count = 0;
    int location_risks[MAX_ITEMS] = {0};
    int location_incidents[MAX_ITEMS] = {0};

    // Collect unique locations
    for (int i = 0; i < risk_count; i++) {
        if (!risks[i].is_mitigated) {
            int found = 0;
            for (int j = 0; j < location_count; j++) {
                if (strcmp(locations[j], risks[i].location) == 0) {
                    location_risks[j]++;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                strcpy(locations[location_count], risks[i].location);
                location_risks[location_count] = 1;
                location_count++;
            }
        }
    }

    // Count incidents per location
    for (int i = 0; i < incident_count; i++) {
        if (!incidents[i].is_resolved) {
            for (int j = 0; j < location_count; j++) {
                if (strcmp(locations[j], incidents[i].location) == 0) {
                    location_incidents[j]++;
                    break;
                }
            }
        }
    }

    // Print location risk profile
    fprintf(file, "Location                      Active Risks    Open Incidents\n");
    fprintf(file, "----------------------------------------------------------\n");
    for (int i = 0; i < location_count; i++) {
        fprintf(file, "%-30s %-15d %-15d\n",
                locations[i], location_risks[i], location_incidents[i]);
    }
    fprintf(file, "\n");

    // Critical items that need attention
    fprintf(file, "CRITICAL ITEMS REQUIRING ATTENTION\n");
    fprintf(file, "----------------------------------------------------------\n");

    int has_critical_items = 0;

    // Critical risks
    for (int i = 0; i < risk_count; i++) {
        if (risks[i].level == CRITICAL && !risks[i].is_mitigated) {
            if (!has_critical_items) {
                fprintf(file, "Critical Risks:\n");
                has_critical_items = 1;
            }
            fprintf(file, "  - [Risk ID: %d] %s (Location: %s)\n",
                    risks[i].id, risks[i].name, risks[i].location);
        }
    }

    // Critical incidents
    int has_critical_incidents = 0;
    for (int i = 0; i < incident_count; i++) {
        if (incidents[i].severity == CRITICAL && !incidents[i].is_resolved) {
            if (!has_critical_incidents) {
                fprintf(file, "\nCritical Incidents:\n");
                has_critical_incidents = 1;
            }
            fprintf(file, "  - [Incident ID: %d] %s (Location: %s)\n",
                    incidents[i].id, incidents[i].name, incidents[i].location);
        }
    }

    if (!has_critical_items && !has_critical_incidents) {
        fprintf(file, "No critical items requiring immediate attention.\n");
    }

    fprintf(file, "\n--- End of Report ---\n");

    fclose(file);
    printf("\nComprehensive system report successfully generated and saved to %s\n", filename);
}