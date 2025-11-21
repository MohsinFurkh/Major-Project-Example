#ifndef STUDENT_H
#define STUDENT_H

#define MAX_NAME_LENGTH 50
#define MAX_STUDENTS 100

typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    int age;
    float gpa;
    char course[50];
} Student;

// Function declarations
void addStudent(Student students[], int *count);
void displayStudents(Student students[], int count);
void searchStudent(Student students[], int count, int id);
void updateStudent(Student students[], int count, int id);
void deleteStudent(Student students[], int *count, int id);
void saveToFile(Student students[], int count, const char *filename);
int loadFromFile(Student students[], const char *filename);

#endif // STUDENT_H
