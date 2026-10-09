#include "lms.h"

void issue_show_all(void)
{
    Issue *i = issues_head;
    int count = 0;
    char issue_text[32], due_text[32], return_text[32];
    if (i == NULL) {
        printf("No issue records available.\n");
        return;
    }

    printf("\n%-8s %-8s %-8s %-20s %-12s %-12s %-14s %8s\n",
           "IssueID", "BookID", "UserID", "User Name", "Issue Date",
           "Due Date", "Return Date", "Fine");
    printf("------------------------------------------------------------------------------------------------------\n");
    while (i != NULL) {
        print_date(i->issue_date, issue_text, sizeof(issue_text));
        print_date(i->due_date, due_text, sizeof(due_text));
        print_date(i->return_date, return_text, sizeof(return_text));
        printf("%-8d %-8d %-8d %-20s %-12s %-12s %-14s %8.2f\n",
               i->issue_id, i->book_id, i->user_id, i->user_name,
               issue_text, due_text, return_text, i->fine);
        i = i->next;
        count++;
    }
    printf("Total issue records: %d\n", count);
}
