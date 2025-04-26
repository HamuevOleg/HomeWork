#include "security_system.h"

// Functions for incident management
void add_incident() {
    if (incident_count >= MAX_ITEMS) {
        printf("Maximum number of incidents reached!\n");
        return;
    }

    Incident incident;
    incident.id = incident_count + 1;

    printf("\n=== Adding New Incident for %s ===\n", COMPANY_NAME);
    printf("Enter incident name: ");
    scanf(" %[^\n]", incident.name);

    printf("Enter incident description: ");
    scanf(" %[^\n]", incident.description);

    printf("Choose incident severity (0-Low, 1-Medium, 2-High, 3-Critical): ");
    int level;
    scanf("%d", &level);
    incident.severity = (RiskLevel)level;

    printf("Enter incident reporter (employee): ");
    scanf(" %[^\n]", incident.reporter);

    // Get restaurant location
    int location_choice;
    get_location_options();
    printf("Select location: ");
    scanf("%d", &location_choice);
    get_location_name(location_choice, incident.location);

    incident.is_resolved = 0;
    strcpy(incident.resolution, "Not resolved");
    strcpy(incident.detection_date, get_current_date());

    incidents[incident_count++] = incident;
    printf("\nIncident successfully added with ID: %d\n", incident.id);
}

void list_incidents() {
    if (incident_count == 0) {
        printf("\nNo incidents recorded in %s system\n", COMPANY_NAME);
        return;
    }

    printf("\n=== %s Incident Register ===\n", COMPANY_NAME);
    printf("ID\tName\t\t\tSeverity\tLocation\t\tStatus\n");
    printf("----------------------------------------------------------------------------------\n");

    for (int i = 0; i < incident_count; i++) {
        printf("%d\t%-20s\t%-10s\t%-20s\t%s\n",
               incidents[i].id,
               incidents[i].name,
               risk_level_to_string(incidents[i].severity),
               incidents[i].location,
               incidents[i].is_resolved ? "Resolved" : "Open");
    }
}

void view_incident(int id) {
    for (int i = 0; i < incident_count; i++) {
        if (incidents[i].id == id) {
            printf("\n=== Incident ID: %d ===\n", id);
            printf("Name: %s\n", incidents[i].name);
            printf("Description: %s\n", incidents[i].description);
            printf("Severity: %s\n", risk_level_to_string(incidents[i].severity));
            printf("Location: %s\n", incidents[i].location);
            printf("Reporter: %s\n", incidents[i].reporter);
            printf("Detection date: %s\n", incidents[i].detection_date);
            printf("Status: %s\n", incidents[i].is_resolved ? "Resolved" : "Open");
            if (incidents[i].is_resolved) {
                printf("Resolution: %s\n", incidents[i].resolution);
            }
            return;
        }
    }
    printf("Incident with ID %d not found in %s system\n", id, COMPANY_NAME);
}

void resolve_incident(int id) {
    for (int i = 0; i < incident_count; i++) {
        if (incidents[i].id == id) {
            if (incidents[i].is_resolved) {
                printf("This incident is already resolved.\n");
                return;
            }

            printf("\n=== Resolving Incident ID: %d ===\n", id);
            printf("Enter resolution details: ");
            getchar(); // Clear buffer
            scanf(" %[^\n]", incidents[i].resolution);

            incidents[i].is_resolved = 1;
            printf("Incident marked as resolved\n");
            return;
        }
    }
    printf("Incident with ID %d not found in %s system\n", id, COMPANY_NAME);
}