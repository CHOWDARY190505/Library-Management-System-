#include "lms.h"
#include <stdlib.h>
#include <string.h>

void book_add(void)
{
    Book *node, *tail;
    char title[TITLE_LEN], author[AUTHOR_LEN];
    int quantity;

    read_line("Enter book title: ", title, sizeof(title));
    read_line("Enter author name: ", author, sizeof(author));
    if (title[0] == '\0' || author[0] == '\0') {
        printf("Title and author cannot be empty.\n");
        return;
    }
    quantity = read_int("Enter quantity (0 or more): ");
    if (quantity < 0) {
        printf("Quantity cannot be negative.\n");
        return;
    }

    node = (Book *)malloc(sizeof(Book));
    if (node == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    node->id = smallest_book_id();
    strcpy(node->title, title);
    strcpy(node->author, author);
    node->quantity = quantity;
    node->next = NULL;

    if (books_head == NULL) {
        books_head = node;
    } else {
        tail = books_head;
        while (tail->next != NULL) tail = tail->next;
        tail->next = node;
    }
    printf("Book added. Assigned Book ID: %d\n", node->id);
}
