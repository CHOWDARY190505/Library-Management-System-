#include "lms.h"
#include <string.h>
#include <ctype.h>

static int contains_case_insensitive(const char *text, const char *query)
{
    size_t i, j;
    if (query[0] == '\0') return 1;
    for (i = 0; text[i] != '\0'; i++) {
        for (j = 0; query[j] != '\0' &&
                    tolower((unsigned char)text[i + j]) ==
                    tolower((unsigned char)query[j]); j++) { }
        if (query[j] == '\0') return 1;
    }
    return 0;
}

static void print_book(Book *b)
{
    printf("%-8d %-30s %-25s %8d\n", b->id, b->title, b->author, b->quantity);
}

void book_search(void)
{
    char choice, query[TITLE_LEN];
    int id, found = 0;
    Book *b;

    printf("\nA/a : By Book ID\nB/b : By Book Name\nC/c : By Author Name\nD/d : Back to Main Menu\n");
    choice = read_choice("Enter your choice: ");
    if (choice == 'a') {
        id = read_int("Enter Book ID: ");
        b = find_book_by_id(id);
        if (b != NULL) {
            printf("%-8s %-30s %-25s %8s\n", "Book ID", "Title", "Author", "Quantity");
            print_book(b);
        } else printf("Book not found.\n");
        return;
    }

    if (choice == 'b' || choice == 'c') {
        read_line(choice == 'b' ? "Enter book name or part of it: " :
                                  "Enter author name or part of it: ",
                  query, sizeof(query));
        printf("%-8s %-30s %-25s %8s\n", "Book ID", "Title", "Author", "Quantity");
        for (b = books_head; b != NULL; b = b->next) {
            const char *field = choice == 'b' ? b->title : b->author;
            if (contains_case_insensitive(field, query)) {
                print_book(b);
                found++;
            }
        }
        if (found == 0) printf("No matching books found.\n");
    } else if (choice != 'd') {
        printf("Invalid choice.\n");
    }
}
