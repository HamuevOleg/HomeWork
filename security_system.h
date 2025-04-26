#ifndef SECURITY_SYSTEM_H
#define SECURITY_SYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h> // Для функции usleep()

#define MAX_NAME_LENGTH 100
#define MAX_DESC_LENGTH 500
#define MAX_ITEMS 100
#define MAX_PATH_LENGTH 256
#define MAX_DATE_LENGTH 20
#define COMPANY_NAME "La Placinte"
#define MAX_DOCUMENTS 100
#define PASSWORD_LENGTH 16
#define MAX_ATTEMPTS 3

// Уровни доступа пользователей
typedef enum {
    EMPLOYEE = 1,
    MANAGER = 2,
    ADMIN = 3
} AccessLevel;

// Уровни риска
typedef enum {
    LOW,
    MEDIUM,
    HIGH,
    CRITICAL
} RiskLevel;

// Структура для управления документами
typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    char path[MAX_PATH_LENGTH];
    char description[MAX_DESC_LENGTH];
    char creation_date[MAX_DATE_LENGTH];
    char last_modified[MAX_DATE_LENGTH];
    char owner[MAX_NAME_LENGTH];
    int version;
} Document;

// Структура для реестра рисков
typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESC_LENGTH];
    RiskLevel level;
    char identification_date[MAX_DATE_LENGTH];
    char owner[MAX_NAME_LENGTH];
    int is_mitigated;
    char mitigation_plan[MAX_DESC_LENGTH];
    char location[MAX_NAME_LENGTH]; // Добавлено для местоположения ресторана (филиала)
} Risk;

// Структура для элементов контроля
typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESC_LENGTH];
    int risk_id;  // Связь с риском
    char implementation_date[MAX_DATE_LENGTH];
    char last_review_date[MAX_DATE_LENGTH];
    char responsible_person[MAX_NAME_LENGTH];
    int is_effective;
    char location[MAX_NAME_LENGTH]; // Добавлено для местоположения ресторана
} Control;

// Структура для аудитов
typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESC_LENGTH];
    char start_date[MAX_DATE_LENGTH];
    char end_date[MAX_DATE_LENGTH];
    char auditor[MAX_NAME_LENGTH];
    int is_completed;
    char findings[MAX_DESC_LENGTH];
    char location[MAX_NAME_LENGTH]; // Добавлено для местоположения ресторана
} Audit;

// Структура для инцидентов
typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESC_LENGTH];
    char detection_date[MAX_DATE_LENGTH];
    RiskLevel severity;
    char reporter[MAX_NAME_LENGTH];
    int is_resolved;
    char resolution[MAX_DESC_LENGTH];
    char location[MAX_NAME_LENGTH]; // Добавлено для местоположения ресторана
} Incident;

// Структура для пользователя
typedef struct {
    char username[MAX_NAME_LENGTH];
    char password[PASSWORD_LENGTH + 1];
    AccessLevel access_level;
} User;

extern Document documents[MAX_ITEMS];
extern int doc_count;

extern Incident incidents[MAX_ITEMS];
extern int incident_count;

extern Risk risks[MAX_ITEMS];
extern int risk_count;

extern Control controls[MAX_ITEMS];
extern int control_count;

extern Audit audits[MAX_ITEMS];
extern int audit_count;

// Функции аутентификации
AccessLevel login();
int validate_password(const char* input, const char* correct_password);
void get_access_level_name(AccessLevel level, char* level_name);
void loading_animation(const char* message);
void display_boxed_message(const char* message);

// Служебные функции
char* get_current_date();
void clear_screen();
char* risk_level_to_string(RiskLevel level);
void write_header_to_file(FILE* file, const char* title);
void get_location_options();
void get_location_name(int location_number, char* location_name);

// Функции для работы с документами
void add_document();
void list_documents();
void view_document(int id);
void update_document(int id);
void export_documents_to_file(const char* filename);

// Функции для работы с рисками
void add_risk();
void list_risks();
void view_risk(int id);
void update_risk(int id);
void export_risks_to_file(const char* filename);

// Функции для работы с контролями
void add_control();
void list_controls();
void view_control(int id);
void update_control(int id);

// Функции для работы с отчетами
void generate_risk_report();
void generate_incident_report();
void generate_full_system_report(const char* filename);

// Функции меню
void document_menu();
void risk_menu();
void control_menu();
void audit_menu();
void incident_menu();
void report_menu();
void show_main_menu();
void show_menu_based_on_access(AccessLevel level);

#endif // SECURITY_SYSTEM_H