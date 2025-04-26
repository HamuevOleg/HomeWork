#include "security_system.h"

// Functions for document management
void add_document() {
    if (doc_count >= MAX_ITEMS) {
        printf("Maximum number of documents reached!\n");
        return;
    }

    Document doc;
    doc.id = doc_count + 1;

    printf("\n=== Adding New Document for %s ===\n", COMPANY_NAME);
    printf("Enter document name: ");
    scanf(" %[^\n]", doc.name);

    printf("Enter document file path: ");
    scanf(" %[^\n]", doc.path);

    printf("Enter document description: ");
    scanf(" %[^\n]", doc.description);

    printf("Enter document owner (responsible employee): ");
    scanf(" %[^\n]", doc.owner);

    doc.version = 1;
    strcpy(doc.creation_date, get_current_date());
    strcpy(doc.last_modified, doc.creation_date);

    documents[doc_count++] = doc;
    printf("\nDocument successfully added with ID: %d\n", doc.id);
}

void list_documents() {
    if (doc_count == 0) {
        printf("\nNo documents available in %s system\n", COMPANY_NAME);
        return;
    }

    printf("\n=== %s Document List ===\n", COMPANY_NAME);
    printf("ID\tName\t\t\tOwner\t\t\tCreation Date\n");
    printf("----------------------------------------------------------------\n");

    for (int i = 0; i < doc_count; i++) {
        printf("%d\t%-20s\t%-20s\t%s\n",
               documents[i].id,
               documents[i].name,
               documents[i].owner,
               documents[i].creation_date);
    }
}

void view_document(int id) {
    for (int i = 0; i < doc_count; i++) {
        if (documents[i].id == id) {
            printf("\n=== Document ID: %d ===\n", id);
            printf("Name: %s\n", documents[i].name);
            printf("Description: %s\n", documents[i].description);
            printf("Path: %s\n", documents[i].path);
            printf("Owner: %s\n", documents[i].owner);
            printf("Version: %d\n", documents[i].version);
            printf("Creation date: %s\n", documents[i].creation_date);
            printf("Last modified: %s\n", documents[i].last_modified);
            return;
        }
    }
    printf("Document with ID %d not found in %s system\n", id, COMPANY_NAME);
}

void update_document(int id) {
    for (int i = 0; i < doc_count; i++) {
        if (documents[i].id == id) {
            printf("\n=== Updating Document ID: %d ===\n", id);

            printf("Current name: %s\n", documents[i].name);
            printf("Enter new name (or press Enter to keep current): ");
            char buffer[MAX_NAME_LENGTH];
            getchar(); // Clear buffer
            fgets(buffer, MAX_NAME_LENGTH, stdin);
            if (buffer[0] != '\n') {
                buffer[strcspn(buffer, "\n")] = 0; // Remove newline
                strcpy(documents[i].name, buffer);
            }

            printf("Current description: %s\n", documents[i].description);
            printf("Enter new description (or press Enter to keep current): ");
            fgets(buffer, MAX_DESC_LENGTH, stdin);
            if (buffer[0] != '\n') {
                buffer[strcspn(buffer, "\n")] = 0;
                strcpy(documents[i].description, buffer);
            }

            printf("Current file path: %s\n", documents[i].path);
            printf("Enter new file path (or press Enter to keep current): ");
            fgets(buffer, MAX_PATH_LENGTH, stdin);
            if (buffer[0] != '\n') {
                buffer[strcspn(buffer, "\n")] = 0;
                strcpy(documents[i].path, buffer);
            }

            // Increment version and update modification date
            documents[i].version++;
            strcpy(documents[i].last_modified, get_current_date());

            printf("\nDocument successfully updated. New version: %d\n", documents[i].version);
            return;
        }
    }
    printf("Document with ID %d not found in %s system\n", id, COMPANY_NAME);
}

void export_documents_to_file(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error opening file for writing!\n");
        return;
    }

    write_header_to_file(file, "Document Register");

    fprintf(file, "Total documents: %d\n\n", doc_count);

    for (int i = 0; i < doc_count; i++) {
        fprintf(file, "Document ID: %d\n", documents[i].id);
        fprintf(file, "Name: %s\n", documents[i].name);
        fprintf(file, "Description: %s\n", documents[i].description);
        fprintf(file, "File path: %s\n", documents[i].path);
        fprintf(file, "Owner: %s\n", documents[i].owner);
        fprintf(file, "Version: %d\n", documents[i].version);
        fprintf(file, "Created: %s\n", documents[i].creation_date);
        fprintf(file, "Last modified: %s\n", documents[i].last_modified);
        fprintf(file, "------------------------------------------------\n\n");
    }

    fclose(file);
    printf("Documents successfully exported to %s\n", filename);
}