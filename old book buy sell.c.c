#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#ifndef STRUCTURE_H
#define STRUCTURE_H



struct User
{
    int userID;

    char name[50];
    char studentID[20];
    char email[50];
    char phone[20];

    char password[30];

    char userType[10];
};




struct Book
{
    int bookID;

    char title[100];
    char author[50];
    char edition[20];

    char category[30];
    char condition[30];

    float price;

    int sellerID;

    char sellerName[50];
    char sellerPhone[20];

    char status[20];
};



struct Transaction
{
    char transactionID[15];

    int bookID;

    int sellerID;
    int buyerID;

    char sellerName[50];
    char buyerName[50];

    float sellingPrice;

    char date[20];
    char time[20];
};

#endif


struct User currentUser;

void mainMenu();
void exitSystem();


void registration();
void login();


void sellerPanel();
void addBook();
void updateBook();
void deleteBook();
void viewMyBooks();


void buyerPanel();
void searchBook();
void viewAvailableBooks();
void buyBook();


void adminPanel();
void viewAllUsers();
void viewAllBooks();
void viewAvailableBooksAdmin();
void viewSoldBooks();
void viewAllTransactions();


void saveTransaction(struct Book book);



/* ===== registration.c ===== */

void registration()
{
    FILE *fp;
    FILE *temp;

    struct User user;
    struct User tempUser;

    int choice;

    system("cls");
    system("color 71");

    printf("\n");
    printf("\t=====================================\n");
    printf("\t         USER REGISTRATION\n");
    printf("\t=====================================\n\n");


    temp = fopen("user.dat","rb");

    if(temp == NULL)
    {
        user.userID = 1001;
    }
    else
    {
        user.userID = 1001;

        while(fread(&tempUser,sizeof(tempUser),1,temp))
        {
            user.userID = tempUser.userID + 1;
        }

        fclose(temp);
    }

    printf("User ID     : %d\n",user.userID);

    printf("Name        : ");
    scanf(" %[^\n]",user.name);

    printf("Student ID  : ");
    scanf(" %s",user.studentID);

    printf("Email       : ");
    scanf(" %s",user.email);

    printf("Phone       : ");
    scanf(" %s",user.phone);

    printf("Password    : ");
    scanf(" %s",user.password);

    printf("\nSelect User Type\n");
    printf("1. Seller\n");
    printf("2. Buyer\n");

    printf("\nEnter Choice : ");
    scanf("%d",&choice);

    if(choice==1)
    {
        strcpy(user.userType,"Seller");
    }
    else if(choice==2)
    {
        strcpy(user.userType,"Buyer");
    }
    else
    {
        printf("\nInvalid Choice!");

        getch();

        return;
    }

    fp = fopen("user.dat","ab");

    if(fp==NULL)
    {
        printf("\nFile Error!");

        getch();

        return;
    }

    fwrite(&user,sizeof(user),1,fp);

    fclose(fp);

    printf("\n=====================================\n");
    printf(" Registration Successful.\n");
    printf("=====================================\n");

    printf("\nPress Any Key To Continue...");

    getch();
}

/* ===== login.c ===== */

void login()
{
    FILE *fp;

    struct User user;

    char email[50];
    char password[30];
    char ch;
    int i = 0;
    int found = 0;

    system("cls");
    system("color 71");

    printf("\n");
    printf("\t=====================================\n");
    printf("\t             LOGIN\n");
    printf("\t=====================================\n\n");

    printf("Email    : ");
    scanf("%s", email);

    printf("Password : ");
    while(1)
{
    ch = getch();

    if(ch == 13)
        break;

    if(ch == 8)
    {
        if(i > 0)
        {
            i--;
            printf("\b \b");
        }
    }
    else
    {
        password[i++] = ch;
        printf("*");
    }
}

password[i] = '\0';

    if(strcmp(email,"admin@gmail.com")==0 &&
       strcmp(password,"admin123")==0)
    {
        printf("\nAdmin Login Successful.");

        getch();

        adminPanel();

        return;
    }

    fp = fopen("user.dat","rb");

    if(fp == NULL)
    {
        printf("\nUser File Not Found!");

        getch();

        return;
    }

    while(fread(&user,sizeof(user),1,fp))
    {
        if(strcmp(user.email,email)==0 &&
           strcmp(user.password,password)==0)
        {
            found = 1;

            currentUser = user;

            break;
        }
    }

    fclose(fp);

    if(found == 0)
    {
        printf("\nInvalid Email or Password!");

        getch();

        return;
    }

    printf("\nLogin Successful.");

    getch();

    if(strcmp(currentUser.userType,"Seller")==0)
    {
        sellerPanel();
    }
    else if(strcmp(currentUser.userType,"Buyer")==0)
    {
        buyerPanel();
    }
    else
    {
        printf("\nInvalid User Type!");

        getch();
    }
}

/* ===== seller.c ===== */

void sellerPanel()
{
    int choice;

    while(1)
    {
        system("cls");
        system("color 71");

        printf("\n");
        printf("\t=====================================\n");
        printf("\t          SELLER PANEL\n");
        printf("\t=====================================\n\n");

        printf("\t1. Add Old Book\n");
        printf("\t2. Update Book Detail\n");
        printf("\t3. Delete Book Listing\n");
        printf("\t4. View My Books\n");
        printf("\t5. Logout\n");

        printf("\nEnter Your Choice : ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                addBook();
                break;

            case 2:
                updateBook();
                break;

            case 3:
                deleteBook();
                break;

            case 4:
                viewMyBooks();
                break;

            case 5:
                return;

            default:
                printf("\nInvalid Choice!");
                getch();
        }
    }
}
void addBook()
{
    FILE *fp;
    FILE *temp;

    struct Book book;
    struct Book tempBook;

    system("cls");

    printf("\n");
    printf("\t=====================================\n");
    printf("\t          ADD OLD BOOK\n");
    printf("\t=====================================\n\n");



    temp = fopen("book.dat","rb");

    if(temp == NULL)
    {
        book.bookID = 101;
    }
    else
    {
        book.bookID = 101;

        while(fread(&tempBook,sizeof(tempBook),1,temp))
        {
            book.bookID = tempBook.bookID + 1;
        }

        fclose(temp);
    }

    printf("Book ID      : %d\n",book.bookID);

    printf("Book Title   : ");
    scanf(" %[^\n]",book.title);

    printf("Author Name  : ");
    scanf(" %[^\n]",book.author);

    printf("Edition      : ");
    scanf(" %[^\n]",book.edition);

    printf("Category     : ");
    scanf(" %[^\n]",book.category);

    printf("Condition    : ");
    scanf(" %[^\n]",book.condition);

    printf("Price        : ");
    scanf("%f",&book.price);



    book.sellerID = currentUser.userID;

    strcpy(book.sellerName,currentUser.name);

    strcpy(book.sellerPhone,currentUser.phone);

    strcpy(book.status,"Available");

    fp = fopen("book.dat","ab");

    if(fp == NULL)
    {
        printf("\nFile Error!");

        getch();

        return;
    }

    fwrite(&book,sizeof(book),1,fp);

    fclose(fp);

    printf("\nBook Added Successfully.");

    getch();
}
void updateBook()
{
    FILE *fp;

    struct Book book;

    int id;
    int found = 0;

    fp = fopen("book.dat","rb+");

    if(fp == NULL)
    {
        printf("\nBook File Not Found!");

        getch();

        return;
    }

    system("cls");

    printf("\n");
    printf("\t=====================================\n");
    printf("\t       UPDATE BOOK DETAIL\n");
    printf("\t=====================================\n\n");

    printf("Enter Book ID : ");
    scanf("%d",&id);

    while(fread(&book,sizeof(book),1,fp))
    {
        if(book.bookID == id && book.sellerID == currentUser.userID)
        {
            found = 1;

            printf("\nCurrent Information\n\n");

            printf("Title      : %s\n",book.title);
            printf("Author     : %s\n",book.author);
            printf("Edition    : %s\n",book.edition);
            printf("Category   : %s\n",book.category);
            printf("Condition  : %s\n",book.condition);
            printf("Price      : %.2f\n",book.price);

            printf("\nEnter New Information\n\n");

            printf("Book Title : ");
            scanf(" %[^\n]",book.title);

            printf("Author     : ");
            scanf(" %[^\n]",book.author);

            printf("Edition    : ");
            scanf(" %[^\n]",book.edition);

            printf("Category   : ");
            scanf(" %[^\n]",book.category);

            printf("Condition  : ");
            scanf(" %[^\n]",book.condition);

            printf("Price      : ");
            scanf("%f",&book.price);

            fseek(fp,-(long)sizeof(book),SEEK_CUR);

            fwrite(&book,sizeof(book),1,fp);

            printf("\nBook Updated Successfully.");

            break;
        }
    }

    if(found==0)
    {
        printf("\nBook Not Found!");

    }

    fclose(fp);

    getch();
}
void deleteBook()
{
    FILE *fp,*temp;

    struct Book book;

    int id;
    int found = 0;

    fp = fopen("book.dat","rb");

    if(fp==NULL)
    {
        printf("\nBook File Not Found!");

        getch();

        return;
    }

    temp = fopen("temp.dat","wb");

    system("cls");

    printf("\n");
    printf("\t=====================================\n");
    printf("\t      DELETE BOOK LISTING\n");
    printf("\t=====================================\n\n");

    printf("Enter Book ID : ");
    scanf("%d",&id);

    while(fread(&book,sizeof(book),1,fp))
    {
        if(book.bookID==id && book.sellerID==currentUser.userID)
        {
            found = 1;
        }
        else
        {
            fwrite(&book,sizeof(book),1,temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("book.dat");

    rename("temp.dat","book.dat");

    if(found)
    {
        printf("\nBook Deleted Successfully.");
    }
    else
    {
        printf("\nBook Not Found!");
    }

    getch();
}
void viewMyBooks()
{
    FILE *fp;

    struct Book book;

    int found = 0;

    fp = fopen("book.dat","rb");

    if(fp == NULL)
    {
        printf("\nBook File Not Found!");

        getch();

        return;
    }

    system("cls");

    printf("\n");
    printf("\t=====================================\n");
    printf("\t          MY BOOK LIST\n");
    printf("\t=====================================\n\n");

    while(fread(&book,sizeof(book),1,fp))
    {
        if(book.sellerID == currentUser.userID)
        {
            found = 1;

            printf("\n----------------------------------------\n");

            printf("Book ID      : %d\n",book.bookID);
            printf("Title        : %s\n",book.title);
            printf("Author       : %s\n",book.author);
            printf("Edition      : %s\n",book.edition);
            printf("Category     : %s\n",book.category);
            printf("Condition    : %s\n",book.condition);
            printf("Price        : %.2f\n",book.price);
            printf("Status       : %s\n",book.status);
        }
    }

    if(found == 0)
    {
        printf("\nNo Book Found.");
    }

    fclose(fp);

    printf("\n\nPress Any Key To Continue...");

    getch();
}

/* ===== buyer.c ===== */

void buyerPanel()
{
    int choice;

    while(1)
    {
        system("cls");
        system("color 71");

        printf("\n");
        printf("\t=====================================\n");
        printf("\t          BUYER PANEL\n");
        printf("\t=====================================\n\n");

        printf("\t1. Search Old Book\n");
        printf("\t2. View Available Books\n");
        printf("\t3. Buy Book\n");
        printf("\t4. Logout\n");

        printf("\nEnter Your Choice : ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                searchBook();
                break;

            case 2:
                viewAvailableBooks();
                break;

            case 3:
                buyBook();
                break;

            case 4:
                return;

            default:
                printf("\nInvalid Choice!");
                getch();
        }
    }
}


void searchBook()
{
    FILE *fp;

    struct Book book;

    int choice;
    int found = 0;

    char category[30];

    system("cls");

    printf("\n");
    printf("\t=====================================\n");
    printf("\t         SEARCH BOOK\n");
    printf("\t=====================================\n\n");

    printf("Select Category\n\n");

    printf("1. Academic\n");
    printf("2. Novel\n");
    printf("3. Fiction\n");
    printf("4. Programming\n");
    printf("5. Religious\n");
    printf("6. Others\n");

    printf("\nEnter Choice : ");
    scanf("%d",&choice);

    switch(choice)
    {
    case 1:
        strcpy(category,"Academic");
        break;

    case 2:
        strcpy(category,"Novel");
        break;

    case 3:
        strcpy(category,"Fiction");
        break;

    case 4:
        strcpy(category,"Programming");
        break;

    case 5:
        strcpy(category,"Religious");
        break;

    case 6:
        strcpy(category,"Others");
        break;

    default:
        printf("\nInvalid Choice!");
        getch();
        return;
    }

    fp = fopen("book.dat","rb");

    if(fp == NULL)
    {
        printf("\nBook File Not Found!");
        getch();
        return;
    }

    system("cls");
    system("color 71");

    printf("\n");
    printf("\t=====================================\n");
    printf("\t      %s BOOKS\n",category);
    printf("\t=====================================\n\n");

    while(fread(&book,sizeof(book),1,fp))
    {
        if(strcmp(book.category,category)==0 &&
           strcmp(book.status,"Available")==0)
        {
            found = 1;

            printf("--------------------------------------\n");
            printf("Book ID      : %d\n",book.bookID);
            printf("Title        : %s\n",book.title);
            printf("Author       : %s\n",book.author);
            printf("Edition      : %s\n",book.edition);
            printf("Condition    : %s\n",book.condition);
            printf("Price        : %.2f\n",book.price);
            printf("Seller Name  : %s\n",book.sellerName);
            printf("Seller Phone : %s\n",book.sellerPhone);
            printf("--------------------------------------\n\n");
        }
    }

    fclose(fp);

    if(found==0)
    {
        printf("\nNo Book Available In This Category.");
    }

    getch();
}


void viewAvailableBooks()
{
    FILE *fp;

    struct Book book;

    int found = 0;

    fp = fopen("book.dat","rb");

    if(fp==NULL)
    {
        printf("\nBook File Not Found!");

        getch();

        return;
    }

    system("cls");

    printf("\n");
    printf("\t=====================================\n");
    printf("\t      AVAILABLE BOOKS\n");
    printf("\t=====================================\n\n");

    while(fread(&book,sizeof(book),1,fp))
    {
        if(strcmp(book.status,"Available")==0)
        {
            found = 1;

            printf("\n-----------------------------------\n");

            printf("Book ID      : %d\n",book.bookID);
            printf("Title        : %s\n",book.title);
            printf("Author       : %s\n",book.author);
            printf("Category     : %s\n",book.category);
            printf("Price        : %.2f\n",book.price);
            printf("Seller Name  : %s\n",book.sellerName);
            printf("Seller Phone : %s\n",book.sellerPhone);
        }
    }

    if(found==0)
    {
        printf("\nNo Available Book Found.");
    }

    fclose(fp);

    getch();
}


void buyBook()
{
    FILE *fp;

    struct Book book;

    int id;
    int found = 0;
    char title[100];
    char confirm[30];

    fp = fopen("book.dat","rb+");

    if(fp==NULL)
    {
        printf("\nBook File Not Found!");

        getch();

        return;
    }

    system("cls");

    printf("\n");
    printf("\t=====================================\n");
    printf("\t            BUY BOOK\n");
    printf("\t=====================================\n\n");
printf("\nEnter Book Title : ");
scanf(" %[^\n]",title);

fp = fopen("book.dat","rb+");

while(fread(&book,sizeof(book),1,fp))
{
    if(strcmp(book.title,title)==0 &&
       strcmp(book.status,"Available")==0)
    {
        char confirm;

        printf("\nBook Found\n");
        printf("----------------------------\n");
        printf("Title        : %s\n",book.title);
        printf("Author       : %s\n",book.author);
        printf("Price        : %.2f\n",book.price);
        printf("Seller       : %s\n",book.sellerName);
        printf("Phone        : %s\n",book.sellerPhone);

        printf("\nAre You Sure You Want To Buy This Book? (Y/N): ");
        scanf(" %c",&confirm);

        if(confirm=='Y' || confirm=='y')
        {
            strcpy(book.status,"Sold");

            fseek(fp,-sizeof(book),SEEK_CUR);

            fwrite(&book,sizeof(book),1,fp);

            saveTransaction(book);

            printf("\nBook Purchased Successfully.");
        }
        else
        {
            printf("\nPurchase Cancelled.");
        }

        fclose(fp);

        getch();

        return;
    }
}

fclose(fp);

printf("\nBook Not Found or Already Sold.");

getch();
}

/* ===== transaction.c ===== */

void saveTransaction(struct Book book)
{
    FILE *fp;
    FILE *temp;

    struct Transaction transaction;
    struct Transaction tempTransaction;

    int id = 101;


    temp = fopen("transaction.dat","rb");

    if(temp != NULL)
    {
        while(fread(&tempTransaction,sizeof(tempTransaction),1,temp))
        {
            id = atoi(tempTransaction.transactionID + 2) + 1;
        }

        fclose(temp);
    }

    sprintf(transaction.transactionID,"TR%d",id);


    transaction.bookID = book.bookID;

    transaction.sellerID = book.sellerID;

    transaction.buyerID = currentUser.userID;

    strcpy(transaction.sellerName,book.sellerName);

    strcpy(transaction.buyerName,currentUser.name);

    transaction.sellingPrice = book.price;
    time_t now;
struct tm *t;

now = time(NULL);

t = localtime(&now);

strftime(transaction.date,sizeof(transaction.date),
"%d-%m-%Y",t);

strftime(transaction.time,sizeof(transaction.time),
"%I:%M %p",t);



    fp = fopen("transaction.dat","ab");

    if(fp == NULL)
    {
        printf("\nTransaction File Error!");

        getch();

        return;
    }

    fwrite(&transaction,sizeof(transaction),1,fp);

    fclose(fp);
}

/* ===== admin.c ===== */

void adminPanel()
{
    int choice;

    while(1)
    {
        system("cls");

        printf("\n");
        printf("\t=====================================\n");
        printf("\t          ADMIN PANEL\n");
        printf("\t=====================================\n\n");

        printf("\t1. View All Users\n");
        printf("\t2. View All Books\n");
        printf("\t3. View Available Books\n");
        printf("\t4. View Sold Books\n");
        printf("\t5. View All Transactions\n");
        printf("\t6. Logout\n");

        printf("\nEnter Your Choice : ");
        scanf("%d",&choice);

        switch(choice)
        {
        case 1:
            viewAllUsers();
            break;

        case 2:
            viewAllBooks();
            break;

        case 3:
            viewAvailableBooksAdmin();
            break;

        case 4:
            viewSoldBooks();
            break;

        case 5:
            viewAllTransactions();
            break;

        case 6:
            return;

        default:
            printf("\nInvalid Choice!");
            getch();
        }
    }
}


void viewAllUsers()
{
    FILE *fp;
    struct User user;

    int found=0;

    fp=fopen("user.dat","rb");

    if(fp==NULL)
    {
        printf("\nUser File Not Found!");
        getch();
        return;
    }

    system("cls");

    printf("\n=========== ALL USERS ===========\n");

    while(fread(&user,sizeof(user),1,fp))
    {
        found=1;

        printf("\n---------------------------------\n");

        printf("User ID     : %d\n",user.userID);
        printf("Name        : %s\n",user.name);
        printf("Student ID  : %s\n",user.studentID);
        printf("Email       : %s\n",user.email);
        printf("Phone       : %s\n",user.phone);
        printf("User Type   : %s\n",user.userType);
    }

    if(found==0)
    {
        printf("\nNo User Found.");
    }

    fclose(fp);

    getch();
}


void viewAllBooks()
{
    FILE *fp;
    struct Book book;

    int found=0;

    fp=fopen("book.dat","rb");

    if(fp==NULL)
    {
        printf("\nBook File Not Found!");
        getch();
        return;
    }

    system("cls");

    printf("\n=========== ALL BOOKS ===========\n");

    while(fread(&book,sizeof(book),1,fp))
    {
        found=1;

        printf("\n---------------------------------\n");

        printf("Book ID      : %d\n",book.bookID);
        printf("Title        : %s\n",book.title);
        printf("Author       : %s\n",book.author);
        printf("Category     : %s\n",book.category);
        printf("Price        : %.2f\n",book.price);
        printf("Seller Name  : %s\n",book.sellerName);
        printf("Status       : %s\n",book.status);
    }

    if(found==0)
    {
        printf("\nNo Book Found.");
    }

    fclose(fp);

    getch();
}


void viewAvailableBooksAdmin()
{
    FILE *fp;
    struct Book book;

    int found=0;

    fp=fopen("book.dat","rb");

    if(fp==NULL)
    {
        printf("\nBook File Not Found!");
        getch();
        return;
    }

    system("cls");

    printf("\n======= AVAILABLE BOOKS =======\n");

    while(fread(&book,sizeof(book),1,fp))
    {
        if(strcmp(book.status,"Available")==0)
        {
            found=1;

            printf("\n---------------------------------\n");

            printf("Book ID      : %d\n",book.bookID);
            printf("Title        : %s\n",book.title);
            printf("Author       : %s\n",book.author);
            printf("Price        : %.2f\n",book.price);
            printf("Seller Name  : %s\n",book.sellerName);
        }
    }

    if(found==0)
    {
        printf("\nNo Available Book Found.");
    }

    fclose(fp);

    getch();
}


void viewSoldBooks()
{
    FILE *fp;
    struct Book book;

    int found=0;

    fp=fopen("book.dat","rb");

    if(fp==NULL)
    {
        printf("\nBook File Not Found!");
        getch();
        return;
    }

    system("cls");

    printf("\n=========== SOLD BOOKS ===========\n");

    while(fread(&book,sizeof(book),1,fp))
    {
        if(strcmp(book.status,"Sold")==0)
        {
            found=1;

            printf("\n---------------------------------\n");

            printf("Book ID      : %d\n",book.bookID);
            printf("Title        : %s\n",book.title);
            printf("Author       : %s\n",book.author);
            printf("Price        : %.2f\n",book.price);
            printf("Seller Name  : %s\n",book.sellerName);
        }
    }

    if(found==0)
    {
        printf("\nNo Sold Book Found.");
    }

    fclose(fp);

    getch();
}


void viewAllTransactions()
{
    FILE *fp;
    struct Transaction transaction;

    int found=0;

    fp=fopen("transaction.dat","rb");

    if(fp==NULL)
    {
        printf("\nTransaction File Not Found!");
        getch();
        return;
    }

    system("cls");
    system("color 71");

    printf("\n======= ALL TRANSACTIONS =======\n");

    while(fread(&transaction,sizeof(transaction),1,fp))
    {
        found=1;

        printf("\n---------------------------------\n");

        printf("Transaction ID : %s\n",transaction.transactionID);
        printf("Book ID        : %d\n",transaction.bookID);
        printf("Seller ID      : %d\n",transaction.sellerID);
        printf("Buyer ID       : %d\n",transaction.buyerID);
        printf("Seller Name    : %s\n",transaction.sellerName);
        printf("Date           : %s\n",transaction.date);
        printf("Time           : %s\n",transaction.time);

    }

    if(found==0)
    {
        printf("\nNo Transaction Found.");
    }

    fclose(fp);

    getch();
}

/* ===== main.c ===== */

void mainMenu();

int main()
{
    mainMenu();

    return 0;
}

void mainMenu()
{
    int choice;

    while(1)
    {
        system("cls");
        system("color 71");

        printf("\n");
        printf("\t==============================================\n");
        printf("\t     OLD BOOK BUY & SELL MANAGEMENT SYSTEM\n");
        printf("\t==============================================\n\n");

        printf("\t1. Registration\n");
        printf("\t2. Login\n");
        printf("\t3. Exit\n");

        printf("\n\tEnter Your Choice : ");
        scanf("%d",&choice);

        switch(choice)
        {
        case 1:
            registration();
            break;

        case 2:
            login();
            break;

        case 3:
            exitSystem();
            break;

        default:
            printf("\nInvalid Choice!");
            getch();
        }
    }
}

void exitSystem()
{
    system("cls");
    system("color 71");

    printf("\n\n");
    printf("\t=====================================\n");
    printf("\t     THANK YOU FOR USING OUR\n");
    printf("\t OLD BOOK BUY & SELL MANAGEMENT SYSTEM\n");
    printf("\t=====================================\n");

    printf("\n\nPress Any Key To Exit...");

    getch();

    exit(0);
}

