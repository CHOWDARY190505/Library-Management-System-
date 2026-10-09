#include "lms.h"
#include <stdlib.h>
#include <string.h>

void issue_book(void)
{
    int book_id, user_id;
    char user_name[USER_NAME_LEN];
    Book *b;
    Issue *node, *tail;
    time_t now = time(NULL);

    book_id = read_int("Enter Book ID: ");
    b = find_book_by_id(book_id);
    if (b == NULL) { printf("Book not found.\n"); return; }
    if (b->quantity <= 0) { printf("No copies available to issue.\n"); return; }

    user_id = read_int("Enter User ID: ");
    if (user_id <= 0) { printf("User ID must be positive.\n"); return; }
    read_line("Enter user name: ", user_name, sizeof(user_name));
    if (user_name[0] == '\0') { printf("User name cannot be empty.\n"); return; }

    node = (Issue *)malloc(sizeof(Issue));
    if (node == NULL) { printf("Memory allocation failed.\n"); return; }

    node->issue_id = smallest_issue_id();
    node->book_id = book_id;
    node->user_id = user_id;
    strcpy(node->user_name, user_name);
    node->issue_date = now;
    node->due_date = add_days(now, 7);
    node->return_date = (time_t)0;
    node->fine = 0.0;
    node->next = NULL;

    if (issues_head == NULL) issues_head = node;
    else {
        tail = issues_head;
        while (tail->next != NULL) tail = tail->next;
        tail->next = node;
    }
    b->quantity--;
    printf("Book issued. Issue ID: %d\n", node->issue_id);
    {
        char issue_text[32], due_text[32];
        print_date(node->issue_date, issue_text, sizeof(issue_text));
        print_date(node->due_date, due_text, sizeof(due_text));
        printf("Issue date: %s | Due date: %s\n", issue_text, due_text);
    }
}
