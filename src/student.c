#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/student.h"

// Add a new student
void addStudent(Student students[], int *count) {
    if (*count >= MAX_STUDENTS) {
        printf("Maximum number of students reached!\n");
        return;
    }
    
    Student newStudent;
    printf("\nEnter Student ID: ");
    scanf("%d", &newStudent.id);
    
    // Clear input buffer
    while (getchar() != '\n');
    
    printf("Enter Name: ");
    fgets(newStudent.name, MAX_NAME_LENGTH, stdin);
    newStudent.name[strcspn(newStudent.name, "\n")] = 0; // Remove newline
    
    printf("Enter Age: ");
    scanf("%d", &newStudent.age);
    
    printf("Enter GPA: ");
    scanf("%f", &newStudent.gpa);
    
    // Clear input buffer
    while (getchar() != '\n');
    
    printf("Enter Course: ");
    fgets(newStudent.course, 50, stdin);
    newStudent.course[strcspn(newStudent.course, "\n")] = 0; // Remove newline
    
    students[(*count)++] = newStudent;
    printf("Student added successfully!\n");
}

// Display all students
void displayStudents(Student students[], int count) {
    if (count == 0) {
        printf("No students to display.\n");
        return;
    }
    
    printf("\n%-10s %-20s %-10s %-10s %s\n", 
           "ID", "Name", "Age", "GPA", "Course");
    printf("--------------------------------------------------\n");
    
    for (int i = 0; i < count; i++) {
        printf("%-10d %-20s %-10d %-10.2f %s\n", 
               students[i].id, students[i].name, 
               students[i].age, students[i].gpa, students[i].course);
    }
}

// Search for a student by ID
void searchStudent(Student students[], int count, int id) {
    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            printf("\nStudent Found!\n");
            printf("ID: %d\nName: %s\nAge: %d\nGPA: %.2f\nCourse: %s\n",
                   students[i].id, students[i].name, 
                   students[i].age, students[i].gpa, students[i].course);
            return;
        }
    }
    printf("Student with ID %d not found.\n", id);
}

// Update student information
void updateStudent(Student students[], int count, int id) {
    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            printf("\nEnter new details for student ID %d\n", id);
            
            printf("Name (%s): ", students[i].name);
            char name[50];
            fgets(name, 50, stdin);
            if (strlen(name) > 1) { // If user entered something
                strcpy(students[i].name, strtok(name, "\n"));
            }
            
            printf("Age (%d): ", students[i].age);
            char ageStr[10];
            fgets(ageStr, 10, stdin);
            if (strlen(ageStr) > 1) {
                students[i].age = atoi(ageStr);
            }
            
            printf("GPA (%.2f): ", students[i].gpa);
            char gpaStr[10];
            fgets(gpaStr, 10, stdin);
            if (strlen(gpaStr) > 1) {
                students[i].gpa = atof(gpaStr);
            }
            
            printf("Course (%s): ", students[i].course);
            char course[50];
            fgets(course, 50, stdin);
            if (strlen(course) > 1) {
                strcpy(students[i].course, strtok(course, "\n"));
            }
            
            printf("Student information updated successfully!\n");
            return;
        }
    }
    printf("Student with ID %d not found.\n", id);
}

// Delete a student by ID
void deleteStudent(Student students[], int *count, int id) {
    for (int i = 0; i < *count; i++) {
        if (students[i].id == id) {
            // Shift all elements after the found student one position left
            for (int j = i; j < *count - 1; j++) {
                students[j] = students[j + 1];
            }
            (*count)--;
            printf("Student with ID %d deleted successfully!\n", id);
            return;
        }
    }
    printf("Student with ID %d not found.\n", id);
}

// Save students to a file
void saveToFile(Student students[], int count, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }
    
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d,%s,%d,%.2f,%s\n", 
                students[i].id, students[i].name, 
                students[i].age, students[i].gpa, students[i].course);
    }
    
    fclose(file);
    printf("Data saved to %s successfully!\n", filename);
}

// Load students from a file
int loadFromFile(Student students[], const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("No existing data file found. Starting with empty database.\n");
        return 0;
    }
    
    int count = 0;
    char line[256];
    
    while (fgets(line, sizeof(line), file) && count < MAX_STUDENTS) {
        // Remove newline character if present
        line[strcspn(line, "\n")] = 0;
        
        // Parse the line
        char *token = strtok(line, ",");
        if (token == NULL) continue;
        
        students[count].id = atoi(token);
        
        token = strtok(NULL, ",");
        if (token) strncpy(students[count].name, token, MAX_NAME_LENGTH - 1);
        
        token = strtok(NULL, ",");
        if (token) students[count].age = atoi(token);
        
        token = strtok(NULL, ",");
        if (token) students[count].gpa = atof(token);
        
        token = strtok(NULL, ",");
        if (token) strncpy(students[count].course, token, 49);
        
        count++;
    }
    
    fclose(file);
    printf("Loaded %d students from %s\n", count, filename);
    return count;
}
