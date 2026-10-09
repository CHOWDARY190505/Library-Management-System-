#include "lms.h"
#include <stdio.h>

int main(void)
{
    int choice;
    load_all();

    for (;;) {
        printf("\n+----------------------------------------+\n");
        printf("|          Book Management Menu          |\n");
        printf("|----------------------------------------|\n");
        printf("| 1. Add New Book                        |\n");
        printf("| 2. Update Book Details                 |\n");
        printf("| 3. Remove Book                         |\n");
        printf("| 4. Search Book                         |\n");
        printf("| 5. View All Books                      |\n");
        printf("| 6. Issue Book                          |\n");
        printf("| 7. Return Book                         |\n");
        printf("| 8. List Issued Books                   |\n");
        printf("| 9. Save                                |\n");
        printf("| 10. Exit                               |\n");
        printf("+----------------------------------------+\n");

        choice = read_int("Enter your choice: ");
        switch (choice) {
            case 1: book_add(); break;
            case 2: book_update(); break;
            case 3: book_remove(); break;
            case 4: book_search(); break;
            case 5: book_show_all(); break;
            case 6: issue_book(); break;
            case 7: return_book(); break;
            case 8: issue_show_all(); break;
            case 9: save_all(); break;
            case 10:
                save_all();
                free_all();
                printf("Exiting Library Management System. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice. Enter a number from 1 to 10.\n");
        }
    }
}
