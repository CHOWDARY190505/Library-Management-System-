#include "lms.h"
#include <stdlib.h>
#include <string.h>

void save_all(void)
{
    FILE *fp = fopen(BOOKS_FILE, "w");
    Book *b;
    if (fp == NULL) { perror("Cannot save books.dat"); return; }

    for (b = books_head; b != NULL; b = b->next) {
        if (fprintf(fp, "%d|%d|%s|%s\n", b->id, b->quantity, b->title, b->author) < 0) {
            printf("Error writing book records.\n");
            fclose(fp);
            return;
        }
    }
    if (fclose(fp) != 0) { perror("Error closing books.dat"); return; }

    fp = fopen(ISSUES_FILE, "w");
    if (fp == NULL) { perror("Cannot save issues.dat"); return; }

    {
        Issue *i;
        for (i = issues_head; i != NULL; i = i->next) {
            if (fprintf(fp, "%d|%d|%d|%lld|%lld|%lld|%.2f|%s\n",
                        i->issue_id, i->book_id, i->user_id,
                        (long long)i->issue_date, (long long)i->due_date,
                        (long long)i->return_date, i->fine, i->user_name) < 0) {
                printf("Error writing issue records.\n");
                fclose(fp);
                return;
            }
        }
    }
    if (fclose(fp) != 0) { perror("Error closing issues.dat"); return; }
    printf("Book and issue records saved successfully.\n");
}

void load_all(void)
{
    FILE *fp;
    char line[512];

    fp = fopen(BOOKS_FILE, "r");
    if (fp != NULL) {
        while (fgets(line, sizeof(line), fp) != NULL) {
            char *p1 = strchr(line, '|'), *p2, *p3, *nl;
            char *end;
            long id, quantity;
            Book *b, *tail;
            if (p1 == NULL) continue;
            *p1 = '\0';
            p2 = strchr(p1 + 1, '|');
            if (p2 == NULL) continue;
            *p2 = '\0';
            p3 = strchr(p2 + 1, '|');
            if (p3 == NULL) continue;
            *p3 = '\0';

            id = strtol(line, &end, 10);
            if (*line == '\0' || *end != '\0' || id <= 0) continue;
            quantity = strtol(p1 + 1, &end, 10);
            if (*(p1 + 1) == '\0' || *end != '\0' || quantity < 0 || quantity > 2147483647L) continue;

            nl = strchr(p3 + 1, '\n');
            if (nl != NULL) *nl = '\0';
            nl = strchr(p3 + 1, '\r');
            if (nl != NULL) *nl = '\0';
            if (p2[1] == '\0' || p3[1] == '\0' || book_id_exists((int)id)) continue;

            b = (Book *)malloc(sizeof(Book));
            if (b == NULL) { printf("Not enough memory to load books.\n"); break; }
            b->id = (int)id;
            b->quantity = (int)quantity;
            strncpy(b->title, p2 + 1, TITLE_LEN - 1);
            b->title[TITLE_LEN - 1] = '\0';
            strncpy(b->author, p3 + 1, AUTHOR_LEN - 1);
            b->author[AUTHOR_LEN - 1] = '\0';
            b->next = NULL;

            if (books_head == NULL) books_head = b;
            else {
                tail = books_head;
                while (tail->next != NULL) tail = tail->next;
                tail->next = b;
            }
        }
        fclose(fp);
    }

    fp = fopen(ISSUES_FILE, "r");
    if (fp != NULL) {
        while (fgets(line, sizeof(line), fp) != NULL) {
            int issue_id, book_id, user_id;
            long long issue_date, due_date, return_date;
            double fine;
            char user_name[USER_NAME_LEN];
            Issue *i, *tail;
            int matched = sscanf(line, "%d|%d|%d|%lld|%lld|%lld|%lf|%99[^\n]",
                                 &issue_id, &book_id, &user_id, &issue_date,
                                 &due_date, &return_date, &fine, user_name);
            if (matched != 8 || issue_id <= 0 || book_id <= 0 || user_id <= 0 ||
                find_issue_by_id(issue_id) != NULL) continue;

            i = (Issue *)malloc(sizeof(Issue));
            if (i == NULL) { printf("Not enough memory to load issue records.\n"); break; }
            i->issue_id = issue_id;
            i->book_id = book_id;
            i->user_id = user_id;
            i->issue_date = (time_t)issue_date;
            i->due_date = (time_t)due_date;
            i->return_date = (time_t)return_date;
            i->fine = fine;
            strncpy(i->user_name, user_name, USER_NAME_LEN - 1);
            i->user_name[USER_NAME_LEN - 1] = '\0';
            i->next = NULL;

            if (issues_head == NULL) issues_head = i;
            else {
                tail = issues_head;
                while (tail->next != NULL) tail = tail->next;
                tail->next = i;
            }
        }
        fclose(fp);
    }
}
