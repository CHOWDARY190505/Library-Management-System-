# Library Management System (LMS) in C

A console-based Library Management System implemented in C using structures, singly linked lists, dynamic memory allocation, date/time functions, and file handling.

## Features

1. Add a book (automatically assigns the smallest available positive ID)
2. Update title, author, or quantity by book ID or book name
3. Remove a book by ID or name (blocked while an active issue exists)
4. Search by ID, partial title, or partial author name (case-insensitive for text)
5. View all books
6. Issue a book to a user; records issue date and due date (7 days later)
7. Return a book; records return date and calculates a fine of Rs. 5 per late day
8. List issue and return history
9. Save data to `books.dat` and `issues.dat`
10. Load data automatically at startup

## Source files

- `main.c` — menu and program flow
- `lms.h` — structures and function declarations
- `lms_common.c` — shared input, lookup, date, and memory helpers
- `book_add.c` — add books
- `book_update.c` — update book details
- `book_remove.c` — remove books
- `book_search.c` — search books
- `book_show.c` — list all books
- `issue_book.c` — issue books
- `return_book.c` — return books and calculate fines
- `issue_show.c` — list issue history
- `lms_save.c` — save and load files

## Compile (GCC)

```bash
gcc -std=c99 -Wall -Wextra -pedantic main.c lms_common.c book_add.c book_update.c book_remove.c book_search.c book_show.c issue_book.c return_book.c issue_show.c lms_save.c -o lms
```

Run on Linux/macOS:

```bash
./lms
```

On Windows with MinGW:

```bash
lms.exe
```

## Data files

The program creates `books.dat` and `issues.dat` in its current working directory after saving. Do not manually edit these files while the program is running.

## Rules and assumptions

- Issue period: 7 calendar days.
- Fine: Rs. 5 per late calendar day.
- User IDs must be positive integers.
- Book quantities cannot be negative.
- Text search is partial and case-insensitive; update/remove by book name use exact, case-sensitive matching.
- The project stores issue history but does not maintain a separate user directory; user ID and name are entered at issue time.
- Choosing Exit saves current data automatically.
