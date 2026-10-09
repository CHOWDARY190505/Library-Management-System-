#include "lms.h"
#include <string.h>

static void update_one(Book *book)
{
    char choice;
    char text[TITLE_LEN > AUTHOR_LEN ? TITLE_LEN : AUTHOR_LEN];
    int quantity;

    printf("\nA/a : Update title\nB/b : Update author\nC/c : Update quantity\n");
    choice = read_choice("Choose field: ");
    if (choice == 'a') {
        read_line("Enter new title: ", text, sizeof(text));
        if (text[0] == '\0') { printf("Title cannot be empty.\n"); return; }
        strcpy(book->title, text);
        printf("Title updated.\n");
    } else if (choice == 'b') {
        read_line("Enter new author: ", text, sizeof(text));
        if (text[0] == '\0') { printf("Author cannot be empty.\n"); return; }
        strcpy(book->author, text);
        printf("Author updated.\n");
    } else if (choice == 'c') {
        quantity = read_int("Enter new quantity (0 or more): ");
        if (quantity < 0) { printf("Quantity cannot be negative.\n"); return; }
        book->quantity = quantity;
        printf("Quantity updated.\n");
    } else {
        printf("Invalid choice.\n");
    }
}

static void print_book(Book *b)
{
    printf("ID: %d | Title: %s | Author: %s | Quantity: %d\n",
           b->id, b->title, b->author, b->quantity);
}

void book_update(void)
{
    char choice, name[TITLE_LEN];
    int id, found = 0;
    Book *b;

    printf("\nA/a : By Book ID\nB/b : By Book Name\nC/c : Back to Main Menu\n");
    choice = read_choice("Enter your choice: ");
    if (choice == 'a') {
        id = read_int("Enter Book ID: ");
        b = find_book_by_id(id);
        if (b == NULL) { printf("Book not found.\n"); return; }
        update_one(b);
    } else if (choice == 'b') {
        read_line("Enter exact book name: ", name, sizeof(name));
        for (b = books_head; b != NULL; b = b->next) {
            if (strcmp(b->title, name) == 0) {
                print_book(b);
                found++;
            }
        }
        if (found == 0) { printf("Book not found.\n"); return; }
        id = read_int("Enter Book ID of the record to update: ");
        b = find_book_by_id(id);
        if (b == NULL || strcmp(b->title, name) != 0) {
            printf("Book ID does not match the searched title.\n");
            return;
        }
        update_one(b);
    } else if (choice != 'c') {
        printf("Invalid choice.\n");
    }
}
