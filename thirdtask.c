#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STUDENTS 100
#define FILENAME "student_records.dat"
#define NAME_LEN 50
#define COURSE_LEN 30

// Structure definition for Student
typedef struct {
    int rollNo;
    char name[NAME_LEN];
    int age;
    char course[COURSE_LEN];
    float marks;
    char grade;
} Student;

// Global array to hold student records
Student students[MAX_STUDENTS];
int studentCount = 0;

// Function prototypes
void loadRecordsFromFile();
void saveRecordsToFile();
void addStudent();
void deleteStudent();
void updateStudent();
void searchStudent();
void displayAllStudents();
void displayStudent(Student s);
void clearInputBuffer();
char calculateGrade(float marks);
void printHeader();
void printMenu();
int findStudentByRollNo(int rollNo);

int main() {
    int choice;
    
    // Load existing records from file
    loadRecordsFromFile();
    
    do {
        system("clear || cls"); // Clear screen
        printHeader();
        printMenu();
        
        printf("Enter your choice (1-7): ");
        scanf("%d", &choice);
        clearInputBuffer();
        
        switch(choice) {
            case 1:
                addStudent();
                break;
            case 2:
                deleteStudent();
                break;
            case 3:
                updateStudent();
                break;
            case 4:
                searchStudent();
                break;
            case 5:
                displayAllStudents();
                break;
            case 6:
                // Save and exit
                saveRecordsToFile();
                printf("\nRecords saved successfully!\n");
                printf("Exiting program. Goodbye!\n");
                break;
            case 7:
                // Exit without saving (emergency exit)
                printf("\nExiting without saving changes!\n");
                break;
            default:
                printf("\nInvalid choice! Please enter 1-7.\n");
        }
        
        if(choice != 6 && choice != 7) {
            printf("\nPress Enter to continue...");
            clearInputBuffer();
        }
        
    } while(choice != 6 && choice != 7);
    
    return 0;
}

// Function to load records from file
void loadRecordsFromFile() {
    FILE *file = fopen(FILENAME, "rb");
    
    if(file == NULL) {
        printf("No existing records found. Starting fresh.\n");
        return;
    }
    
    // Read student count
    fread(&studentCount, sizeof(int), 1, file);
    
    // Read all student records
    fread(students, sizeof(Student), studentCount, file);
    
    fclose(file);
    printf("Loaded %d student records from file.\n", studentCount);
}

// Function to save records to file
void saveRecordsToFile() {
    FILE *file = fopen(FILENAME, "wb");
    
    if(file == NULL) {
        printf("Error: Could not save records!\n");
        return;
    }
    
    // Save student count
    fwrite(&studentCount, sizeof(int), 1, file);
    
    // Save all student records
    fwrite(students, sizeof(Student), studentCount, file);
    
    fclose(file);
}

// Function to add a new student
void addStudent() {
    system("clear || cls");
    printHeader();
    printf("=== ADD NEW STUDENT ===\n\n");
    
    if(studentCount >= MAX_STUDENTS) {
        printf("Error: Maximum student capacity reached!\n");
        return;
    }
    
    Student newStudent;
    
    printf("Enter Roll Number: ");
    scanf("%d", &newStudent.rollNo);
    clearInputBuffer();
    
    // Check if roll number already exists
    if(findStudentByRollNo(newStudent.rollNo) != -1) {
        printf("Error: Student with Roll Number %d already exists!\n", newStudent.rollNo);
        return;
    }
    
    printf("Enter Name: ");
    fgets(newStudent.name, NAME_LEN, stdin);
    newStudent.name[strcspn(newStudent.name, "\n")] = 0; // Remove newline
    
    printf("Enter Age: ");
    scanf("%d", &newStudent.age);
    clearInputBuffer();
    
    printf("Enter Course: ");
    fgets(newStudent.course, COURSE_LEN, stdin);
    newStudent.course[strcspn(newStudent.course, "\n")] = 0;
    
    printf("Enter Marks (0-100): ");
    scanf("%f", &newStudent.marks);
    clearInputBuffer();
    
    // Validate marks
    if(newStudent.marks < 0 || newStudent.marks > 100) {
        printf("Error: Marks must be between 0 and 100!\n");
        return;
    }
    
    // Calculate grade
    newStudent.grade = calculateGrade(newStudent.marks);
    
    // Add to array
    students[studentCount] = newStudent;
    studentCount++;
    
    // Save to file immediately
    saveRecordsToFile();
    
    printf("\nStudent added successfully!\n");
    printf("\n--- Added Student Details ---\n");
    displayStudent(newStudent);
}

// Function to delete a student
void deleteStudent() {
    system("clear || cls");
    printHeader();
    printf("=== DELETE STUDENT ===\n\n");
    
    if(studentCount == 0) {
        printf("No students in the database!\n");
        return;
    }
    
    int rollNo;
    printf("Enter Roll Number to delete: ");
    scanf("%d", &rollNo);
    clearInputBuffer();
    
    int index = findStudentByRollNo(rollNo);
    
    if(index == -1) {
        printf("Error: Student with Roll Number %d not found!\n", rollNo);
        return;
    }
    
    printf("\n--- Student to be Deleted ---\n");
    displayStudent(students[index]);
    
    char confirm;
    printf("\nAre you sure you want to delete this student? (y/n): ");
    scanf("%c", &confirm);
    clearInputBuffer();
    
    if(tolower(confirm) == 'y') {
        // Shift all elements after index one position left
        for(int i = index; i < studentCount - 1; i++) {
            students[i] = students[i + 1];
        }
        studentCount--;
        
        saveRecordsToFile();
        printf("\nStudent deleted successfully!\n");
    } else {
        printf("\nDeletion cancelled.\n");
    }
}

// Function to update student information
void updateStudent() {
    system("clear || cls");
    printHeader();
    printf("=== UPDATE STUDENT ===\n\n");
    
    if(studentCount == 0) {
        printf("No students in the database!\n");
        return;
    }
    
    int rollNo;
    printf("Enter Roll Number to update: ");
    scanf("%d", &rollNo);
    clearInputBuffer();
    
    int index = findStudentByRollNo(rollNo);
    
    if(index == -1) {
        printf("Error: Student with Roll Number %d not found!\n", rollNo);
        return;
    }
    
    printf("\n--- Current Student Details ---\n");
    displayStudent(students[index]);
    
    printf("\n--- Enter New Details ---\n");
    
    // Update name
    printf("Name [%s] (Press Enter to keep current): ", students[index].name);
    char newName[NAME_LEN];
    fgets(newName, NAME_LEN, stdin);
    if(strlen(newName) > 1) {
        newName[strcspn(newName, "\n")] = 0;
        strcpy(students[index].name, newName);
    }
    
    // Update age
    printf("Age [%d] (Enter new age or -1 to keep current): ", students[index].age);
    int newAge;
    scanf("%d", &newAge);
    clearInputBuffer();
    if(newAge != -1) {
        students[index].age = newAge;
    }
    
    // Update course
    printf("Course [%s] (Press Enter to keep current): ", students[index].course);
    char newCourse[COURSE_LEN];
    fgets(newCourse, COURSE_LEN, stdin);
    if(strlen(newCourse) > 1) {
        newCourse[strcspn(newCourse, "\n")] = 0;
        strcpy(students[index].course, newCourse);
    }
    
    // Update marks
    printf("Marks [%.2f] (Enter new marks or -1 to keep current): ", students[index].marks);
    float newMarks;
    scanf("%f", &newMarks);
    clearInputBuffer();
    if(newMarks != -1) {
        if(newMarks >= 0 && newMarks <= 100) {
            students[index].marks = newMarks;
            students[index].grade = calculateGrade(newMarks);
        } else {
            printf("Invalid marks! Keeping previous value.\n");
        }
    }
    
    saveRecordsToFile();
    printf("\nStudent updated successfully!\n");
    printf("\n--- Updated Student Details ---\n");
    displayStudent(students[index]);
}

// Function to search for a student
void searchStudent() {
    system("clear || cls");
    printHeader();
    printf("=== SEARCH STUDENT ===\n\n");
    
    if(studentCount == 0) {
        printf("No students in the database!\n");
        return;
    }
    
    int choice;
    printf("Search by:\n");
    printf("1. Roll Number\n");
    printf("2. Name\n");
    printf("3. Course\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    clearInputBuffer();
    
    switch(choice) {
        case 1: {
            int rollNo;
            printf("Enter Roll Number: ");
            scanf("%d", &rollNo);
            clearInputBuffer();
            
            int index = findStudentByRollNo(rollNo);
            if(index != -1) {
                printf("\n--- Student Found ---\n");
                displayStudent(students[index]);
            } else {
                printf("\nStudent with Roll Number %d not found!\n", rollNo);
            }
            break;
        }
        
        case 2: {
            char searchName[NAME_LEN];
            printf("Enter Name (or part of name): ");
            fgets(searchName, NAME_LEN, stdin);
            searchName[strcspn(searchName, "\n")] = 0;
            
            int found = 0;
            printf("\n--- Search Results ---\n");
            for(int i = 0; i < studentCount; i++) {
                if(strstr(students[i].name, searchName) != NULL) {
                    displayStudent(students[i]);
                    printf("--------------------\n");
                    found = 1;
                }
            }
            if(!found) {
                printf("No students found with name containing: %s\n", searchName);
            }
            break;
        }
        
        case 3: {
            char searchCourse[COURSE_LEN];
            printf("Enter Course: ");
            fgets(searchCourse, COURSE_LEN, stdin);
            searchCourse[strcspn(searchCourse, "\n")] = 0;
            
            int found = 0;
            printf("\n--- Search Results ---\n");
            for(int i = 0; i < studentCount; i++) {
                if(strcmp(students[i].course, searchCourse) == 0) {
                    displayStudent(students[i]);
                    printf("--------------------\n");
                    found = 1;
                }
            }
            if(!found) {
                printf("No students found in course: %s\n", searchCourse);
            }
            break;
        }
        
        default:
            printf("Invalid choice!\n");
    }
}

// Function to display all students
void displayAllStudents() {
    system("clear || cls");
    printHeader();
    printf("=== ALL STUDENT RECORDS ===\n\n");
    
    if(studentCount == 0) {
        printf("No students in the database!\n");
        return;
    }
    
    printf("Total Students: %d\n\n", studentCount);
    printf("===================================================================================\n");
    printf("Roll No | Name                     | Age | Course              | Marks  | Grade\n");
    printf("===================================================================================\n");
    
    for(int i = 0; i < studentCount; i++) {
        printf("%7d | %-24s | %3d | %-18s | %6.2f | %c\n",
               students[i].rollNo,
               students[i].name,
               students[i].age,
               students[i].course,
               students[i].marks,
               students[i].grade);
    }
    printf("===================================================================================\n");
    
    // Display statistics
    if(studentCount > 0) {
        float totalMarks = 0;
        for(int i = 0; i < studentCount; i++) {
            totalMarks += students[i].marks;
        }
        printf("\nStatistics:\n");
        printf("Average Marks: %.2f\n", totalMarks / studentCount);
        printf("Total Students: %d\n", studentCount);
    }
}

// Function to display a single student
void displayStudent(Student s) {
    printf("\nStudent Details:\n");
    printf("Roll Number: %d\n", s.rollNo);
    printf("Name: %s\n", s.name);
    printf("Age: %d\n", s.age);
    printf("Course: %s\n", s.course);
    printf("Marks: %.2f\n", s.marks);
    printf("Grade: %c\n", s.grade);
}

// Function to clear input buffer
void clearInputBuffer() {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

// Function to calculate grade based on marks
char calculateGrade(float marks) {
    if(marks >= 90) return 'A';
    if(marks >= 80) return 'B';
    if(marks >= 70) return 'C';
    if(marks >= 60) return 'D';
    if(marks >= 50) return 'E';
    return 'F';
}

// Function to find student by roll number
int findStudentByRollNo(int rollNo) {
    for(int i = 0; i < studentCount; i++) {
        if(students[i].rollNo == rollNo) {
            return i;
        }
    }
    return -1;
}

// Function to print header
void printHeader() {
    printf("========================================\n");
    printf("     STUDENT RECORD MANAGEMENT SYSTEM\n");
    printf("========================================\n\n");
}

// Function to print menu
void printMenu() {
    printf("MAIN MENU:\n");
    printf("1. Add New Student\n");
    printf("2. Delete Student\n");
    printf("3. Update Student Information\n");
    printf("4. Search Student\n");
    printf("5. Display All Students\n");
    printf("6. Save and Exit\n");
    printf("7. Exit Without Saving\n");
    printf("========================================\n");
}
