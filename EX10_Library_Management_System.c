#include <stdio.h>
#include <string.h>

struct Book
{
    int id;
    char name[50];
    char author[50];
    int issued;
};

struct Book b[100];
int count = 0;

void loadBooks()
{
    FILE *fp;
    fp = fopen("library.dat", "rb");

    if (fp != NULL)
    {
        count = fread(b, sizeof(struct Book), 100, fp);
        fclose(fp);
    }
}

void saveBooks()
{
    FILE *fp;
    fp = fopen("library.dat", "wb");

    if (fp != NULL)
    {
        fwrite(b, sizeof(struct Book), count, fp);
        fclose(fp);
    }
}

void addBook()
{
    if (count >= 100)
    {
        printf("Library is full!\n");
        return;
    }

    printf("Enter Book ID: ");
    scanf("%d", &b[count].id);

    printf("Enter Book Name: ");
    scanf(" %[^\n]", b[count].name);

    printf("Enter Author Name: ");
    scanf(" %[^\n]", b[count].author);

    b[count].issued = 0;
    count++;

    saveBooks();

    printf("Book Added Successfully!\n");
}

void displayBooks()
{
    int i;

    if (count == 0)
    {
        printf("No Books Available!\n");
        return;
    }

    printf("\n----- BOOK DETAILS -----\n");

    for (i = 0; i < count; i++)
    {
        printf("\nBook ID: %d", b[i].id);
        printf("\nBook Name: %s", b[i].name);
        printf("\nAuthor Name: %s", b[i].author);

        if (b[i].issued == 1)
            printf("\nStatus: Issued\n");
        else
            printf("\nStatus: Available\n");
    }
}

void searchBook()
{
    int id, i, found = 0;

    printf("Enter Book ID to Search: ");
    scanf("%d", &id);

    for (i = 0; i < count; i++)
    {
        if (b[i].id == id)
        {
            printf("\nBook Found!");
            printf("\nBook Name: %s", b[i].name);
            printf("\nAuthor Name: %s", b[i].author);

            if (b[i].issued == 1)
                printf("\nStatus: Issued\n");
            else
                printf("\nStatus: Available\n");

            found = 1;
            break;
        }
    }

    if (found == 0)
        printf("Book Not Found!\n");
}

void issueBook()
{
    int id, i;

    printf("Enter Book ID to Issue: ");
    scanf("%d", &id);

    for (i = 0; i < count; i++)
    {
        if (b[i].id == id)
        {
            if (b[i].issued == 0)
            {
                b[i].issued = 1;
                saveBooks();
                printf("Book Issued Successfully!\n");
            }
            else
            {
                printf("Book Already Issued!\n");
            }
            return;
        }
    }

    printf("Book Not Found!\n");
}

void returnBook()
{
    int id, i;

    printf("Enter Book ID to Return: ");
    scanf("%d", &id);

    for (i = 0; i < count; i++)
    {
        if (b[i].id == id)
        {
            if (b[i].issued == 1)
            {
                b[i].issued = 0;
                saveBooks();
                printf("Book Returned Successfully!\n");
            }
            else
            {
                printf("Book Was Not Issued!\n");
            }
            return;
        }
    }

    printf("Book Not Found!\n");
}

int main()
{
    int choice;

    loadBooks();

    do
    {
        printf("\n\n===== LIBRARY MANAGEMENT SYSTEM =====\n");
        printf("1. Add Book\n");
        printf("2. Display Books\n");
        printf("3. Search Book\n");
        printf("4. Issue Book\n");
        printf("5. Return Book\n");
        printf("6. Exit\n");

        printf("\nEnter Your Choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                addBook();
                break;

            case 2:
                displayBooks();
                break;

            case 3:
                searchBook();
                break;

            case 4:
                issueBook();
                break;

            case 5:
                returnBook();
                break;

            case 6:
                printf("Thank You!\n");
                break;

            default:
                printf("Invalid Choice!\n");
        }

    } while (choice != 6);

    return 0;
}