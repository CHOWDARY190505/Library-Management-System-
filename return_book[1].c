#include "lms.h"

void return_book(void)
{
    int book_id, user_id;
    Issue *i;
    Book *b;
    time_t now = time(NULL);
    int late_days;
    char due_text[32], return_text[32];

    book_id = read_int("Enter Book ID: ");
    user_id = read_int("Enter User ID: ");

    for (i = issues_head; i != NULL; i = i->next) {
        if (i->book_id == book_id && i->user_id == user_id &&
            i->return_date == (time_t)0) {
            i->return_date = now;
            late_days = days_late(i->due_date, now);
            i->fine = late_days * FINE_PER_DAY;

            b = find_book_by_id(book_id);
            if (b != NULL) b->quantity++;

            print_date(i->due_date, due_text, sizeof(due_text));
            print_date(i->return_date, return_text, sizeof(return_text));
            printf("Book returned successfully.\n");
            printf("Due date: %s | Return date: %s\n", due_text, return_text);
            printf("Late days: %d | Fine: Rs. %.2f\n", late_days, i->fine);
            return;
        }
    }
    printf("No active issue found for that Book ID and User ID.\n");
}
