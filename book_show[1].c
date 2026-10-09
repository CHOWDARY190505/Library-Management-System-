#include "lms.h"

void book_show_all(void)
{
    Book *b = books_head;
    if (b == NULL) {
        printf("No books in the catalogue.\n");
        return;
    }
    printf("\n%-8s %-30s %-25s %8s\n", "Book ID", "Title", "Author", "Quantity");
    printf("-------------------------------------------------------------------------\n");
    while (b != NULL) {
        printf("%-8d %-30s %-25s %8d\n",
               b->id, b->title, b->author, b->quantity);
        b = b->next;
    }
}
