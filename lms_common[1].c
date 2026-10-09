#include "lms.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

Book *books_head = NULL;
Issue *issues_head = NULL;

void read_line(const char *prompt, char *buffer, size_t size)
{
    size_t len;
    int ch;

    if (prompt != NULL) printf("%s", prompt);
    if (fgets(buffer, (int)size, stdin) == NULL) {
        buffer[0] = '\0';
        return;
    }
    len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else {
        while ((ch = getchar()) != '\n' && ch != EOF) { }
    }
}

int read_int(const char *prompt)
{
    char line[128], *end;
    long value;

    for (;;) {
        read_line(prompt, line, sizeof(line));
        errno = 0;
        value = strtol(line, &end, 10);
        while (isspace((unsigned char)*end)) end++;
        if (line[0] != '\0' && *end == '\0' && errno == 0 &&
            value >= INT_MIN && value <= INT_MAX) {
            return (int)value;
        }
        printf("Invalid integer. Please try again.\n");
    }
}

char read_choice(const char *prompt)
{
    char line[32];
    read_line(prompt, line, sizeof(line));
    return line[0] == '\0' ? '\0' : (char)tolower((unsigned char)line[0]);
}

Book *find_book_by_id(int id)
{
    Book *p = books_head;
    while (p != NULL) {
        if (p->id == id) return p;
        p = p->next;
    }
    return NULL;
}

Issue *find_issue_by_id(int issue_id)
{
    Issue *p = issues_head;
    while (p != NULL) {
        if (p->issue_id == issue_id) return p;
        p = p->next;
    }
    return NULL;
}

int book_id_exists(int id)
{
    return find_book_by_id(id) != NULL;
}

int smallest_book_id(void)
{
    int id = 1;
    while (book_id_exists(id) && id < INT_MAX) id++;
    return id;
}

int smallest_issue_id(void)
{
    int id = 1;
    while (find_issue_by_id(id) != NULL && id < INT_MAX) id++;
    return id;
}

void print_date(time_t value, char *buffer, size_t size)
{
    struct tm *tm_info;
    if (value == (time_t)0) {
        snprintf(buffer, size, "Not returned");
        return;
    }
    tm_info = localtime(&value);
    if (tm_info == NULL) {
        snprintf(buffer, size, "Unknown");
        return;
    }
    strftime(buffer, size, "%Y-%m-%d", tm_info);
}

time_t add_days(time_t date, int days)
{
    struct tm tm_info;
    struct tm *ptr = localtime(&date);
    if (ptr == NULL) return date;
    tm_info = *ptr;
    tm_info.tm_mday += days;
    tm_info.tm_isdst = -1;
    return mktime(&tm_info);
}

int days_late(time_t due_date, time_t return_date)
{
    struct tm due_tm, return_tm;
    struct tm *p_due = localtime(&due_date);
    struct tm *p_return = localtime(&return_date);
    time_t due_midnight, return_midnight;
    double seconds;

    if (p_due == NULL || p_return == NULL) return 0;
    due_tm = *p_due;
    return_tm = *p_return;
    due_tm.tm_hour = due_tm.tm_min = due_tm.tm_sec = 0;
    return_tm.tm_hour = return_tm.tm_min = return_tm.tm_sec = 0;
    due_tm.tm_isdst = return_tm.tm_isdst = -1;
    due_midnight = mktime(&due_tm);
    return_midnight = mktime(&return_tm);
    seconds = difftime(return_midnight, due_midnight);
    if (seconds <= 0) return 0;
    return (int)(seconds / 86400.0 + 0.5);
}

void free_all(void)
{
    Book *b = books_head;
    Issue *i = issues_head;
    while (b != NULL) {
        Book *next = b->next;
        free(b);
        b = next;
    }
    while (i != NULL) {
        Issue *next = i->next;
        free(i);
        i = next;
    }
    books_head = NULL;
    issues_head = NULL;
}
