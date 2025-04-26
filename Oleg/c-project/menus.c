#include "security_system.h"

// Menu functions
void document_menu() {
    int choice;
    do {
        clear_screen();
        printf("\n=== %s DOCUMENT MANAGEMENT ===\n", COMPANY_NAME);
        printf("1. Add new document\n");
        printf("2. View document list\n");
        printf("3. View document details\n");
        printf("4. Update document\n");
        printf("5. Export documents to file\n");
        printf("0. Return to main menu\n");
        printf("Select option: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                add_document();
                break;
            case 2:
                list_documents();
                break;
            case 3: {
                int id;
                list_documents();
                printf("\nEnter document ID to view: ");
                scanf("%d", &id);
                view_document(id);
                break;
            }
            case 4: {
                int id;
                list_documents();
                printf("\nEnter document ID to update: ");
                scanf("%d", &id);
                update_document(id);
                break;
            }
            case 5: {
                char filename[MAX_PATH_LENGTH];
                printf("\nEnter filename for export (e.g., documents.txt): ");
                scanf(" %[^\n]", filename);
                export_documents_to_file(filename);
                break;
            }
            case 0:
                break;
            default:
                printf("Invalid choice!\n");
        }

        if (choice != 0) {
            printf("\nPress Enter to continue...");
            getchar(); // Clear buffer
            getchar(); // Wait for keypress
        }
    } while (choice != 0);
}

void risk_menu() {
    int choice;
    do {
        clear_screen();
        printf("\n=== %s RISK REGISTRY ===\n", COMPANY_NAME);
        printf("1. Add new risk\n");
        printf("2. View risk list\n");
        printf("3. View risk details\n");
        printf("4. Update risk\n");
        printf("5. Export risks to file\n");
        printf("0. Return to main menu\n");
        printf("Select option: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                add_risk();
                break;
            case 2:
                list_risks();
                break;
            case 3: {
                int id;
                list_risks();
                printf("\nEnter risk ID to view: ");
                scanf("%d", &id);
                view_risk(id);
                break;
            }
            case 4: {
                int id;
                list_risks();
                printf("\nEnter risk ID to update: ");
                scanf("%d", &id);
                update_risk(id);
                break;
            }
            case 5: {
                char filename[MAX_PATH_LENGTH];
                printf("\nEnter filename for export (e.g., risks.txt): ");
                scanf(" %[^\n]", filename);
                export_risks_to_file(filename);
                break;
            }
            case 0:
                break;
            default:
                printf("Invalid choice!\n");
        }

        if (choice != 0) {
            printf("\nPress Enter to continue...");
            getchar(); // Clear buffer
            getchar(); // Wait for keypress
        }
    } while (choice != 0);
}

void control_menu() {
    int choice;
    do {
        clear_screen();
        printf("\n=== %s CONTROLS ===\n", COMPANY_NAME);
        printf("1. Add new control\n");
        printf("2. View control list\n");
        printf("3. View control details\n");
        printf("4. Update control\n");
        printf("0. Return to main menu\n");
        printf("Select option: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                add_control();
                break;
            case 2:
                list_controls();
                break;
            case 3: {
                int id;
                list_controls();
                printf("\nEnter control ID to view: ");
                scanf("%d", &id);
                view_control(id);
                break;
            }
            case 4: {
                int id;
                list_controls();
                printf("\nEnter control ID to update: ");
                scanf("%d", &id);
                update_control(id);
                break;
            }
            case 0:
                break;
            default:
                printf("Invalid choice!\n");
        }

        if (choice != 0) {
            printf("\nPress Enter to continue...");
            getchar(); // Clear buffer
            getchar(); // Wait for keypress
        }
    } while (choice != 0);
}

void audit_menu() {
    int choice;
    do {
        clear_screen();
        printf("\n=== %s AUDIT MANAGEMENT ===\n", COMPANY_NAME);
        printf("1. Add new audit\n");
        printf("2. View audit list\n");
        printf("3. View audit details\n");
        printf("4. Complete audit\n");
        printf("0. Return to main menu\n");
        printf("Select option: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                add_audit();
                break;
            case 2:
                list_audits();
                break;
            case 3: {
                int id;
                list_audits();
                printf("\nEnter audit ID to view: ");
                scanf("%d", &id);
                view_audit(id);
                break;
            }
            case 4: {
                int id;
                list_audits();
                printf("\nEnter audit ID to complete: ");
                scanf("%d", &id);
                complete_audit(id);
                break;
            }
            case 0:
                break;
            default:
                printf("Invalid choice!\n");
        }

        if (choice != 0) {
            printf("\nPress Enter to continue...");
            getchar(); // Clear buffer
            getchar(); // Wait for keypress
        }
    } while (choice != 0);
}

void incident_menu() {
    int choice;
    do {
        clear_screen();
        printf("\n=== %s INCIDENT MANAGEMENT ===\n", COMPANY_NAME);
        printf("1. Add new incident\n");
        printf("2. View incident list\n");
        printf("3. View incident details\n");
        printf("4. Resolve incident\n");
        printf("0. Return to main menu\n");
        printf("Select option: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                add_incident();
                break;
            case 2:
                list_incidents();
                break;
            case 3: {
                int id;
                list_incidents();
                printf("\nEnter incident ID to view: ");
                scanf("%d", &id);
                view_incident(id);
                break;
            }
            case 4: {
                int id;
                list_incidents();
                printf("\nEnter incident ID to resolve: ");
                scanf("%d", &id);
                resolve_incident(id);
                break;
            }
            case 0:
                break;
            default:
                printf("Invalid choice!\n");
        }

        if (choice != 0) {
            printf("\nPress Enter to continue...");
            getchar(); // Clear buffer
            getchar(); // Wait for keypress
        }
    } while (choice != 0);
}

void report_menu() {
    int choice;
    do {
        clear_screen();
        printf("\n=== %s REPORTS ===\n", COMPANY_NAME);
        printf("1. Risk report\n");
        printf("2. Incident report\n");
        printf("3. Generate comprehensive system report\n");
        printf("0. Return to main menu\n");
        printf("Select option: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                generate_risk_report();
                break;
            case 2:
                generate_incident_report();
                break;
            case 3: {
                char filename[MAX_PATH_LENGTH];
                printf("\nEnter filename for comprehensive report (e.g., system_report.txt): ");
                scanf(" %[^\n]", filename);
                generate_full_system_report(filename);
                break;
            }
            case 0:
                break;
            default:
                printf("Invalid choice!\n");
        }

        if (choice != 0) {
            printf("\nPress Enter to continue...");
            getchar(); // Clear buffer
            getchar(); // Wait for keypress
        }
    } while (choice != 0);
}

void show_main_menu() {
    printf("\n=== %s SECURITY MANAGEMENT SYSTEM ===\n", COMPANY_NAME);
    printf("1. Document Management\n");
    printf("2. Risk Registry\n");
    printf("3. Controls\n");
    printf("4. Audit Management\n");
    printf("5. Incident Management\n");
    printf("6. Reports\n");
    printf("0. Exit\n");
    printf("Select option: ");
}