#ifndef LMS_H
#define LMS_H

#include <stdio.h>
#include <time.h>

#define TITLE_LEN 120
#define AUTHOR_LEN 100
#define USER_NAME_LEN 100
#define BOOKS_FILE "books.dat"
#define ISSUES_FILE "issues.dat"
#define FINE_PER_DAY 5.0

typedef struct Book {
    int id;
    char title[TITLE_LEN];
    char author[AUTHOR_LEN];
    int quantity;
    struct Book *next;
} Book;

typedef struct Issue {
    int issue_id;
    int book_id;
    int user_id;
    char user_name[USER_NAME_LEN];
    time_t issue_date;
    time_t due_date;
    time_t return_date; /* 0 means not returned */
    double fine;
    struct Issue *next;
} Issue;

extern Book *books_head;
extern Issue *issues_head;

void read_line(const char *prompt, char *buffer, size_t size);
int read_int(const char *prompt);
char read_choice(const char *prompt);
void free_all(void);

Book *find_book_by_id(int id);
Issue *find_issue_by_id(int issue_id);
int book_id_exists(int id);
int smallest_book_id(void);
int smallest_issue_id(void);

void book_add(void);
void book_update(void);
void book_remove(void);
void book_search(void);
void book_show_all(void);
void issue_book(void);
void return_book(void);
void issue_show_all(void);
void save_all(void);
void load_all(void);

void print_date(time_t value, char *buffer, size_t size);
time_t add_days(time_t date, int days);
int days_late(time_t due_date, time_t return_date);

#endif
