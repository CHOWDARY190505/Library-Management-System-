#include "lms.h"
#include <string.h>
#include <stdlib.h>

static int has_active_issue(int book_id)
{
    Issue *i;
    for (i = issues_head; i != NULL; i = i->next) {
        if (i->book_id == book_id && i->return_date == (time_t)0) return 1;
    }
    return 0;
}

static void delete_book(int id)
{
    Book *current = books_head, *previous = NULL;
    while (current != NULL) {
        if (current->id == id) {
            if (has_active_issue(id)) {
                printf("Cannot remove: this book has an active issue.\n");
                return;
            }
            if (previous == NULL) books_head = current->next;
            else previous->next = current->next;
            free(current);
            printf("Book removed.\n");
            return;
        }
        previous = current;
        current = current->next;
    }
    printf("Book ID not found.\n");
}

void book_remove(void)
{
    char choice, title[TITLE_LEN];
    int id, found = 0;
    Book *b;

    printf("\nA/a : By Book ID\nB/b : By Book Name\nC/c : Back to Main Menu\n");
    choice = read_choice("Enter your choice: ");
    if (choice == 'a') {
        id = read_int("Enter Book ID to remove: ");
        delete_book(id);
    } else if (choice == 'b') {
        read_line("Enter exact book name: ", title, sizeof(title));
        for (b = books_head; b != NULL; b = b->next) {
            if (strcmp(b->title, title) == 0) {
                printf("ID: %d | Title: %s | Author: %s | Quantity: %d\n",
                       b->id, b->title, b->author, b->quantity);
                found++;
            }
        }
        if (found == 0) { printf("Book not found.\n"); return; }
        id = read_int("Enter Book ID of the record to remove: ");
        b = find_book_by_id(id);
        if (b == NULL || strcmp(b->title, title) != 0) {
            printf("Book ID does not match the searched title.\n");
            return;
        }
        delete_book(id);
    } else if (choice != 'c') {
        printf("Invalid choice.\n");
    }
}
