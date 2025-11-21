#include <stdio.h>
#include <stdlib.h>
#include "../include/student.h"

#define FILENAME "student_data.txt"

void displayMenu() {
    printf("\n=== Student Record Management System ===\n");
    printf("1. Add New Student\n");
    printf("2. Display All Students\n");
    printf("3. Search Student\n");
    printf("4. Update Student\n");
    printf("5. Delete Student\n");
    printf("6. Save to File\n");
    printf("7. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    Student students[MAX_STUDENTS];
    int count = 0;
    int choice, id;
    
    // Load existing data from file
    count = loadFromFile(students, FILENAME);
    
    do {
        displayMenu();
        scanf("%d", &choice);
        
        // Clear input buffer
        while (getchar() != '\n');
        
        switch (choice) {
            case 1:
                addStudent(students, &count);
                break;
                
            case 2:
                displayStudents(students, count);
                break;
                
            case 3:
                printf("Enter Student ID to search: ");
                scanf("%d", &id);
                searchStudent(students, count, id);
                break;
                
            case 4:
                printf("Enter Student ID to update: ");
                scanf("%d", &id);
                updateStudent(students, count, id);
                break;
                
            case 5:
                printf("Enter Student ID to delete: ");
                scanf("%d", &id);
                deleteStudent(students, &count, id);
                break;
                
            case 6:
                saveToFile(students, count, FILENAME);
                break;
                
            case 7:
                // Save data before exiting
                saveToFile(students, count, FILENAME);
                printf("Data saved. Exiting...\n");
                break;
                
            default:
                printf("Invalid choice! Please try again.\n");
        }
        
        // Clear input buffer in case of any remaining characters
        while (getchar() != '\n');
        
    } while (choice != 7);
    
    return 0;
}
