#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 100
#define MAX_BORROWERS 100
#define MAX_LEN 100
#define FINE_PER_DAY 5  // INR 5 per overdue day

typedef struct {
    char title[MAX_LEN];
    char author[MAX_LEN];
    char isbn[MAX_LEN];
    int available; // 1 = Available, 0 = Checked out
} Book;

typedef struct {
    char name[MAX_LEN];
    char isbn[MAX_LEN]; // Which book is borrowed
    int dueDays; // Number of days till return
    int overdueDays; // If any
} Transaction;

// Global arrays
Book books[MAX_BOOKS];
Transaction transactions[MAX_BORROWERS];
int bookCount = 0, transCount = 0;

// Function prototypes
void addBook();
void viewBooks();
void searchBooks();
void checkoutBook();
void returnBook();
void calculateFine();
void displayMenu();

int main() {
    int choice;
    do {
        displayMenu();
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar(); // flush newline

        switch (choice) {
            case 1: addBook(); break;
            case 2: viewBooks(); break;
            case 3: searchBooks(); break;
            case 4: checkoutBook(); break;
            case 5: returnBook(); break;
            case 6: calculateFine(); break;
            case 7: printf("Exiting Library Management System. Bye!\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 7);

    return 0;
}

void displayMenu() {
    printf("\n====== LIBRARY MANAGEMENT SYSTEM ======\n");
    printf("1. Add Book\n");
    printf("2. View All Books\n");
    printf("3. Search Book\n");
    printf("4. Checkout Book\n");
    printf("5. Return Book\n");
    printf("6. Calculate Fine\n");
    printf("7. Exit\n");
}

// Add a book to the library
void addBook() {
    if (bookCount >= MAX_BOOKS) {
        printf("Book database full.\n");
        return;
    }

    printf("Enter book title: ");
    fgets(books[bookCount].title, MAX_LEN, stdin);
    books[bookCount].title[strcspn(books[bookCount].title, "\n")] = '\0';

    printf("Enter author name: ");
    fgets(books[bookCount].author, MAX_LEN, stdin);
    books[bookCount].author[strcspn(books[bookCount].author, "\n")] = '\0';

    printf("Enter ISBN: ");
    fgets(books[bookCount].isbn, MAX_LEN, stdin);
    books[bookCount].isbn[strcspn(books[bookCount].isbn, "\n")] = '\0';

    books[bookCount].available = 1;
    bookCount++;

    printf("Book added successfully.\n");
}

// View all books
void viewBooks() {
    printf("\n--- Book List ---\n");
    for (int i = 0; i < bookCount; i++) {
        printf("%d. %s | %s | ISBN: %s | %s\n", i + 1,
               books[i].title,
               books[i].author,
               books[i].isbn,
               books[i].available ? "Available" : "Checked Out");
    }
}

// Search by title, author, or ISBN
void searchBooks() {
    char query[MAX_LEN];
    int found = 0;

    printf("Enter title/author/ISBN to search: ");
    fgets(query, MAX_LEN, stdin);
    query[strcspn(query, "\n")] = '\0';

    for (int i = 0; i < bookCount; i++) {
        if (strstr(books[i].title, query) || strstr(books[i].author, query) || strstr(books[i].isbn, query)) {
            printf("Found: %s | %s | ISBN: %s | %s\n",
                   books[i].title, books[i].author, books[i].isbn,
                   books[i].available ? "Available" : "Checked Out");
            found = 1;
        }
    }

    if (!found) printf("No matching books found.\n");
}

// Checkout book to a borrower
void checkoutBook() {
    if (transCount >= MAX_BORROWERS) {
        printf("Borrower list full.\n");
        return;
    }

    char isbn[MAX_LEN];
    int found = -1;

    printf("Enter ISBN of book to checkout: ");
    fgets(isbn, MAX_LEN, stdin);
    isbn[strcspn(isbn, "\n")] = '\0';

    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].isbn, isbn) == 0 && books[i].available) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Book not found or already checked out.\n");
        return;
    }

    printf("Enter borrower name: ");
    fgets(transactions[transCount].name, MAX_LEN, stdin);
    transactions[transCount].name[strcspn(transactions[transCount].name, "\n")] = '\0';

    strcpy(transactions[transCount].isbn, isbn);

    printf("Enter due in how many days: ");
    scanf("%d", &transactions[transCount].dueDays);
    getchar(); // flush

    transactions[transCount].overdueDays = 0;
    books[found].available = 0;
    transCount++;

    printf("Book checked out successfully.\n");
}

// Return book
void returnBook() {
    char isbn[MAX_LEN];
    int found = -1;

    printf("Enter ISBN of book to return: ");
    fgets(isbn, MAX_LEN, stdin);
    isbn[strcspn(isbn, "\n")] = '\0';

    for (int i = 0; i < transCount; i++) {
        if (strcmp(transactions[i].isbn, isbn) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("No such transaction found.\n");
        return;
    }

    printf("How many days overdue (0 if returned on time)? ");
    scanf("%d", &transactions[found].overdueDays);
    getchar();

    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].isbn, isbn) == 0) {
            books[i].available = 1;
            break;
        }
    }

    printf("Book returned. ");
    if (transactions[found].overdueDays > 0) {
        int fine = transactions[found].overdueDays * FINE_PER_DAY;
        printf("Fine due: ₹%d\n", fine);
    } else {
        printf("No fine.\n");
    }

    // Remove transaction by shifting
    for (int i = found; i < transCount - 1; i++) {
        transactions[i] = transactions[i + 1];
    }
    transCount--;
}

// Fine calculation report
void calculateFine() {
    printf("\n--- Fine Report ---\n");
    int totalFine = 0;

    for (int i = 0; i < transCount; i++) {
        if (transactions[i].overdueDays > 0) {
            int fine = transactions[i].overdueDays * FINE_PER_DAY;
            printf("%s owes ₹%d for book ISBN %s\n",
                   transactions[i].name, fine, transactions[i].isbn);
            totalFine += fine;
        }
    }

    printf("Total fine to collect: ₹%d\n", totalFine);
}