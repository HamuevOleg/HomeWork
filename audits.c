#include "security_system.h"

// Functions for audits
void add_audit() {
    if (audit_count >= MAX_ITEMS) {
        printf("Maximum number of audits reached!\n");
        return;
    }

    Audit audit;
    audit.id = audit_count + 1;

    printf("\n=== Adding New Audit for %s ===\n", COMPANY_NAME);
    printf("Enter audit name: ");
    scanf(" %[^\n]", audit.name);

    printf("Enter audit description: ");
    scanf(" %[^\n]", audit.description);

    printf("Enter auditor name: ");
    scanf(" %[^\n]", audit.auditor);

    // Get restaurant location
    int location_choice;
    get_location_options();
    printf("Select location to audit: ");
    scanf("%d", &location_choice);
    get_location_name(location_choice, audit.location);

    strcpy(audit.start_date, get_current_date());
    strcpy(audit.end_date, "Not completed");

    audit.is_completed = 0;
    strcpy(audit.findings, "No findings yet");

    audits[audit_count++] = audit;
    printf("\nAudit successfully added with ID: %d\n", audit.id);
}

void list_audits() {
    if (audit_count == 0) {
        printf("\nNo audits available in %s system\n", COMPANY_NAME);
        return;
    }

    printf("\n=== %s Audit List ===\n", COMPANY_NAME);
    printf("ID\tName\t\t\tLocation\t\tStart Date\t\tStatus\n");
    printf("----------------------------------------------------------------------------------\n");

    for (int i = 0; i < audit_count; i++) {
        printf("%d\t%-20s\t%-20s\t%-20s\t%s\n",
               audits[i].id,
               audits[i].name,
               audits[i].location,
               audits[i].start_date,
               audits[i].is_completed ? "Completed" : "In progress");
    }
}

void view_audit(int id) {
    for (int i = 0; i < audit_count; i++) {
        if (audits[i].id == id) {
            printf("\n=== Audit ID: %d ===\n", id);
            printf("Name: %s\n", audits[i].name);
            printf("Description: %s\n", audits[i].description);
            printf("Location: %s\n", audits[i].location);
            printf("Auditor: %s\n", audits[i].auditor);
            printf("Start Date: %s\n", audits[i].start_date);
            printf("End Date: %s\n", audits[i].end_date);
            printf("Status: %s\n", audits[i].is_completed ? "Completed" : "In progress");
            printf("Findings: %s\n", audits[i].findings);
            return;
        }
    }
    printf("Audit with ID %d not found in %s system\n", id, COMPANY_NAME);
}

void complete_audit(int id) {
    for (int i = 0; i < audit_count; i++) {
        if (audits[i].id == id) {
            if (audits[i].is_completed) {
                printf("This audit is already completed!\n");
                return;
            }

            printf("\n=== Completing Audit ID: %d ===\n", id);
            printf("Enter audit findings: ");
            getchar(); // Clear buffer
            scanf(" %[^\n]", audits);
            printf("\n=== Completing Audit ID: %d ===\n", id);
            printf("Enter audit findings: ");
            getchar(); // Clear buffer
            scanf(" %[^\n]", audits[i].findings);

            audits[i].is_completed = 1;
            strcpy(audits[i].end_date, get_current_date());

            printf("Audit marked as completed on %s\n", audits[i].end_date);
            return;
        }
    }
    printf("Audit with ID %d not found in %s system\n", id, COMPANY_NAME);
}