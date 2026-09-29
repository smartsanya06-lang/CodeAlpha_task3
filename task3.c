#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int rollNo;
    char name[50];
    int age;
    float marks;
};

// Function declarations
void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();

int main() {
    int choice;

    while (1) {
        printf("\n========== STUDENT MANAGEMENT SYSTEM ==========\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("===============================================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;

            case 6:
                printf("Program exited successfully.\n");
                exit(0);

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

// Add Student
void addStudent() {
    struct Student s;
    FILE *fp;

    fp = fopen("students.dat", "ab");

    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\nEnter Roll Number: ");
    scanf("%d", &s.rollNo);

    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);

    printf("Enter Age: ");
    scanf("%d", &s.age);

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(struct Student), 1, fp);

    fclose(fp);

    printf("Student record added successfully!\n");
}

// Display Students
void displayStudents() {
    struct Student s;
    FILE *fp;

    fp = fopen("students.dat", "rb");

    if (fp == NULL) {
        printf("No student records found.\n");
        return;
    }

    printf("\n------------- STUDENT RECORDS -------------\n");
    printf("%-10s %-20s %-10s %-10s\n",
           "Roll No", "Name", "Age", "Marks");
    printf("--------------------------------------------\n");

    while (fread(&s, sizeof(struct Student), 1, fp)) {
        printf("%-10d %-20s %-10d %.2f\n",
               s.rollNo, s.name, s.age, s.marks);
    }

    fclose(fp);
}

// Search Student
void searchStudent() {
    struct Student s;
    FILE *fp;
    int roll, found = 0;

    fp = fopen("students.dat", "rb");

    if (fp == NULL) {
        printf("No student records found.\n");
        return;
    }

    printf("\nEnter Roll Number to search: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(struct Student), 1, fp)) {
        if (s.rollNo == roll) {
            printf("\nStudent Found!\n");
            printf("Roll Number : %d\n", s.rollNo);
            printf("Name        : %s\n", s.name);
            printf("Age         : %d\n", s.age);
            printf("Marks       : %.2f\n", s.marks);

            found = 1;
            break;
        }
    }

    fclose(fp);

    if (!found) {
        printf("Student with Roll Number %d not found.\n", roll);
    }
}

// Update Student
void updateStudent() {
    struct Student s;
    FILE *fp;
    int roll, found = 0;

    fp = fopen("students.dat", "rb+");

    if (fp == NULL) {
        printf("No student records found.\n");
        return;
    }

    printf("\nEnter Roll Number to update: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(struct Student), 1, fp)) {
        if (s.rollNo == roll) {

            printf("Enter New Name: ");
            scanf(" %[^\n]", s.name);

            printf("Enter New Age: ");
            scanf("%d", &s.age);

            printf("Enter New Marks: ");
            scanf("%f", &s.marks);

            fseek(fp, -sizeof(struct Student), SEEK_CUR);

            fwrite(&s, sizeof(struct Student), 1, fp);

            found = 1;
            printf("Student record updated successfully!\n");
            break;
        }
    }

    fclose(fp);

    if (!found) {
        printf("Student with Roll Number %d not found.\n", roll);
    }
}

// Delete Student
void deleteStudent() {
    struct Student s;
    FILE *fp, *temp;
    int roll, found = 0;

    fp = fopen("students.dat", "rb");
    temp = fopen("temp.dat", "wb");

    if (fp == NULL) {
        printf("No student records found.\n");
        return;
    }

    if (temp == NULL) {
        printf("Error creating temporary file!\n");
        fclose(fp);
        return;
    }

    printf("\nEnter Roll Number to delete: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(struct Student), 1, fp)) {

        if (s.rollNo == roll) {
            found = 1;
            continue;
        }

        fwrite(&s, sizeof(struct Student), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found) {
        printf("Student record deleted successfully!\n");
    } else {
        printf("Student with Roll Number %d not found.\n", roll);
    }
}