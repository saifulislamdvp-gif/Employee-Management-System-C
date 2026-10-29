#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "employee.dat"

struct Employee {
    int id;
    char name[50];
    char position[30];
    float salary;
};

void addEmployee();
void displayEmployees();
void searchEmployee();
void deleteEmployee();
void updateEmployee();

int main() {
    int choice;
    while(1) {
        printf("\n====================================\n");
        printf("   EMPLOYEE DATA MANAGEMENT SYSTEM   \n");
        printf("====================================\n");
        printf("1. Add Employee\n2. Display All Employees\n3. Search Employee by ID\n4. Update Employee\n5. Delete Employee\n6. Exit\nEnter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: addEmployee(); break;
            case 2: displayEmployees(); break;
            case 3: searchEmployee(); break;
            case 4: updateEmployee(); break;
            case 5: deleteEmployee(); break;
            case 6: exit(0);
            default: printf("Invalid Choice!\n");
        }
    }
    return 0;
}

void addEmployee() {
    FILE *fp;
    struct Employee emp;
    fp = fopen(FILENAME, "ab");
    printf("\nEnter Employee ID: ");
    scanf("%d", &emp.id);
    printf("Enter Name: ");
    fflush(stdin);
    gets(emp.name);
    printf("Enter Position: ");
    gets(emp.position);
    printf("Enter Salary: ");
    scanf("%f", &emp.salary);
    fwrite(&emp, sizeof(emp), 1, fp);
    fclose(fp);
    printf("Employee Added Successfully!\n");
}

void displayEmployees() {
    FILE *fp;
    struct Employee emp;
    fp = fopen(FILENAME, "rb");
    if(fp == NULL) { printf("No data found!\n"); return; }
    printf("\n%-5s %-20s %-15s %-10s\n", "ID", "Name", "Position", "Salary");
    printf("--------------------------------------------------\n");
    while(fread(&emp, sizeof(emp), 1, fp)) {
        printf("%-5d %-20s %-15s %.2f\n", emp.id, emp.name, emp.position, emp.salary);
    }
    fclose(fp);
}

void searchEmployee() {
    FILE *fp;
    struct Employee emp;
    int id, found = 0;
    printf("Enter Employee ID to search: ");
    scanf("%d", &id);
    fp = fopen(FILENAME, "rb");
    while(fread(&emp, sizeof(emp), 1, fp)) {
        if(emp.id == id) {
            printf("\nEmployee Found!\nID: %d\nName: %s\nPosition: %s\nSalary: %.2f\n", emp.id, emp.name, emp.position, emp.salary);
            found = 1;
            break;
        }
    }
    if(!found) printf("Employee Not Found!\n");
    fclose(fp);
}

void deleteEmployee() {
    FILE *fp, *temp;
    struct Employee emp;
    int id, found = 0;
    printf("Enter Employee ID to delete: ");
    scanf("%d", &id);
    fp = fopen(FILENAME, "rb");
    temp = fopen("temp.dat", "wb");
    while(fread(&emp, sizeof(emp), 1, fp)) {
        if(emp.id != id) fwrite(&emp, sizeof(emp), 1, temp);
        else found = 1;
    }
    fclose(fp);
    fclose(temp);
    remove(FILENAME);
    rename("temp.dat", FILENAME);
    if(found) printf("Employee Deleted Successfully!\n");
    else printf("Employee Not Found!\n");
}

void updateEmployee() {
    FILE *fp;
    struct Employee emp;
    int id, found = 0;
    printf("Enter Employee ID to update: ");
    scanf("%d", &id);
    fp = fopen(FILENAME, "rb+");
    while(fread(&emp, sizeof(emp), 1, fp)) {
        if(emp.id == id) {
            printf("Enter New Name: ");
            fflush(stdin);
            gets(emp.name);
            printf("Enter New Position: ");
            gets(emp.position);
            printf("Enter New Salary: ");
            scanf("%f", &emp.salary);
            fseek(fp, -sizeof(emp), SEEK_CUR);
            fwrite(&emp, sizeof(emp), 1, fp);
            found = 1;
            break;
        }
    }
    fclose(fp);
    if(found) printf("Employee Updated Successfully!\n");
    else printf("Employee Not Found!\n");
}
