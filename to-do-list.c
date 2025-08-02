#include <stdio.h>
#include <string.h>

#define MAX_TASKS 100
#define MAX_LENGTH 100

typedef struct {
    char description[MAX_LENGTH];
    int completed; // 0 = pending, 1 = completed
} Task;

// Global task list and counter
Task taskList[MAX_TASKS];
int taskCount = 0;

// Function declarations
void addTask();
void viewTasks();
void markCompleted();
void removeTask();
void displayMenu();

int main() {
    int choice;

    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // Clear newline from input buffer

        switch (choice) {
            case 1: addTask(); break;
            case 2: viewTasks(); break;
            case 3: markCompleted(); break;
            case 4: removeTask(); break;
            case 5: printf("Exiting To-Do List Manager. Goodbye!\n"); break;
            default: printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 5);

    return 0;
}

// Display menu
void displayMenu() {
    printf("\n==== TO-DO LIST MANAGER ====\n");
    printf("1. Add Task\n");
    printf("2. View Tasks\n");
    printf("3. Mark Task as Completed\n");
    printf("4. Remove Task\n");
    printf("5. Exit\n");
}

// Add a task
void addTask() {
    if (taskCount >= MAX_TASKS) {
        printf("Task list full. Cannot add more tasks.\n");
        return;
    }

    printf("Enter task description: ");
    fgets(taskList[taskCount].description, MAX_LENGTH, stdin);
    taskList[taskCount].description[strcspn(taskList[taskCount].description, "\n")] = 0; // Remove newline

    taskList[taskCount].completed = 0;
    taskCount++;

    printf("Task added successfully!\n");
}

// View all tasks
void viewTasks() {
    if (taskCount == 0) {
        printf("No tasks to show.\n");
        return;
    }

    printf("\n--- TASK LIST ---\n");
    for (int i = 0; i < taskCount; i++) {
        printf("%d. [%s] %s\n", i + 1,
               taskList[i].completed ? "Completed" : "Pending",
               taskList[i].description);
    }
}

// Mark task as completed
void markCompleted() {
    if (taskCount == 0) {
        printf("No tasks available to mark.\n");
        return;
    }

    int index;
    viewTasks();
    printf("Enter task number to mark as completed: ");
    scanf("%d", &index);

    if (index < 1 || index > taskCount) {
        printf("Invalid task number.\n");
        return;
    }

    taskList[index - 1].completed = 1;
    printf("Task marked as completed.\n");
}

// Remove a task
void removeTask() {
    if (taskCount == 0) {
        printf("No tasks to remove.\n");
        return;
    }

    int index;
    viewTasks();
    printf("Enter task number to remove: ");
    scanf("%d", &index);

    if (index < 1 || index > taskCount) {
        printf("Invalid task number.\n");
        return;
    }

    for (int i = index - 1; i < taskCount - 1; i++) {
        taskList[i] = taskList[i + 1];
    }

    taskCount--;
    printf("Task removed successfully.\n");
}
