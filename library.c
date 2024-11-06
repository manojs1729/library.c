#include <stdio.h>
#include <string.h>

void admin();
void viewbook();
void mem();
void loadBooks();
void saveBooks();
void loadMembers();
void saveMembers();
void loadAdmins();
void saveAdmins();
int checkAdmin(char username[], char password[]);
void addAdmin();
void addBook();
void addMember();

struct books {
    char bname[100];
    int bid, prize, bkflag;
} book[100];

struct members {
    char mname[100], mpass[100];
    int mid, rbook;
} member[100];

struct admins {
    char username[100];
    char password[100];
} adminData[100];

int bcount = 0, bookid = 101, mcount = 1, memberid = 201, adminCount = 0;

void saveBooks() {
    FILE *fp = fopen("books.dat", "wb");
    if (fp == NULL) {
        printf("Error saving books data.\n");
        return;
    }
    fwrite(&bcount, sizeof(int), 1, fp);  // Save the book count
    fwrite(&bookid, sizeof(int), 1, fp);   // Save the book ID counter
    fwrite(book, sizeof(struct books), bcount, fp);  // Save the book details
    fclose(fp);
}

void loadBooks() {
    FILE *fp = fopen("books.dat", "rb");
    if (fp != NULL) {
        fread(&bcount, sizeof(int), 1, fp);  // Read the book count
        fread(&bookid, sizeof(int), 1, fp);  // Read the book ID counter
        fread(book, sizeof(struct books), bcount, fp);  // Read the book details
        printf("Loaded %d books.\n", bcount);
        fclose(fp);
    } else {
        printf("No books found. Please add at least one book.\n");
        addBook();
        saveBooks();
    }
}


void saveMembers() {
    FILE *fp = fopen("members.dat", "wb");
    if (fp == NULL) {
        printf("Error saving members data.\n");
        return;
    }
    fwrite(&mcount, sizeof(int), 1, fp);  // Save the member count
    fwrite(&memberid, sizeof(int), 1, fp);  // Save the member ID counter
    fwrite(member, sizeof(struct members), mcount, fp);  // Save the member details
    fclose(fp);
}

void loadMembers() {
    FILE *fp = fopen("members.dat", "rb");
    if (fp != NULL) {
        fread(&mcount, sizeof(int), 1, fp);  // Read the member count
        fread(&memberid, sizeof(int), 1, fp);  // Read the member ID counter
        fread(member, sizeof(struct members), mcount, fp);  // Read the member details
        printf("Loaded %d members.\n", mcount);
        fclose(fp);
    } else {
        printf("No members found. Please add at least one member.\n");
        addMember();
        saveMembers();
    }
}


void saveAdmins() {
    FILE *fp = fopen("admins.dat", "wb");
    if (fp == NULL) {
        printf("Error saving admins data.\n");
        return;
    }
    fwrite(&adminCount, sizeof(int), 1, fp);  // Save the admin count
    fwrite(adminData, sizeof(struct admins), adminCount, fp);  // Save the admin details
    fclose(fp);
}

void loadAdmins() {
    FILE *fp = fopen("admins.dat", "rb");
    if (fp != NULL) {
        fread(&adminCount, sizeof(int), 1, fp);  // Read the admin count
        fread(adminData, sizeof(struct admins), adminCount, fp);  // Read the admin details
        fclose(fp);
    } else {
        printf("No admins found. Please add an admin to access the system.\n");
        addAdmin();
        saveAdmins();
    }
}

int checkAdmin(char username[], char password[]) {
    for (int i = 0; i < adminCount; i++) {
        if (strcmp(adminData[i].username, username) == 0 && strcmp(adminData[i].password, password) == 0) {
            return i; // Return the index of the admin
        }
    }
    return -1; // Admin does not exist
}

void addAdmin() {
    printf("Enter new admin username: ");
    scanf("%s", adminData[adminCount].username);
    printf("Enter new admin password: ");
    scanf("%s", adminData[adminCount].password);
    adminCount++;
    saveAdmins();
    printf("New admin added successfully!\n");
}

void addBook() {
    printf("Enter Book name: ");
    scanf("%s", book[bcount].bname);
    printf("Enter Book Prize: ");
    scanf("%d", &book[bcount].prize);
    book[bcount].bkflag = 1;
    book[bcount].bid = bookid++;
    
    printf("Your Book id is: %d\n", book[bcount++].bid);
    saveBooks();
}

void addMember() {
    printf("Enter Member name: ");
    scanf("%s", member[mcount].mname);
    printf("Enter Password: ");
    scanf("%s", member[mcount].mpass);
    member[mcount].mid = memberid++;
    
    printf("Your Membership id is: %d\n", member[mcount].mid);
    member[mcount++].rbook = 0;
    saveMembers();
}

void viewbook() {
    int i;
    printf("\n");
    if (bcount == 0) {
        printf("No books found.\n");
        admin();
    } 
    else {
        for (i = 0; i < bcount; i++) {
            printf("Book name : %-10s\t", book[i].bname);
            printf("Book Id : %-10d\t", book[i].bid);
            printf("Prize : %-10d\t", book[i].prize);
            printf(book[i].bkflag == 1 ? "Available\n" : "Not Available\n");
        }
    }
}

void admin() {
    int n, index, f, i, m;
    char username[100], password[100];
    printf("Enter admin username: ");
    scanf("%s", username);
    printf("Enter admin password: ");
    scanf("%s", password);

    index = checkAdmin(username, password);
    if (index != -1) {
        printf("Welcome, %s!\n", adminData[index].username); // Display welcome message with admin name
        printf("%d\n",adminCount);
        while (1) {
            printf("\n----------> ADMIN <------------\n");
            printf("\t1. Add Book\n\t2. View Book\n\t3. Issued Book\n\t4. Add Admin\n\t5. Logout\nEnter your choice: ");
            scanf("%d", &n);
            if (n == 1) {
                if (bcount == 0) {
                    printf("No books found. Please add at least one book.\n");
                }
                printf("How many books to add: ");
                scanf("%d", &m);
                for (i = 0; i < m; i++) {
                    addBook();
                    saveBooks();
                }
                
            } else if (n == 2) {
                viewbook();
            } else if (n == 3) {
                f = 1;
                for (i = 1; i < bcount; i++) {
                    if (book[i].bkflag == 0) {
                        f = 0;
                        printf("Book name : %-10s\t", book[i].bname);
                        printf("Book Id : %-10d\t", book[i].bid);
                        printf("Book Prize : %-10d\t", book[i].prize);
                    }
                }
                if (f == 1) printf("No issued books\n");
            } else if (n == 4) {
                addAdmin();
            } else if (n == 5) {
                break;
            } else {
                printf("Invalid choice...\n");
            }
        }
    } else {
        printf("\nInvalid admin credentials...\n\n");
    }
}

void mem() {
    int n, index;
    char password[100];
    while (1) {
        printf("\n-------------> MEMBER LOGIN <--------------\n");
        printf("\t1. Sign In\n\t2. Sign Up\n\t3. Back\nEnter your choice: ");
        scanf("%d", &n);
        if (n == 1) {
            int memberId;
            printf("Enter user id: ");
            scanf("%d", &memberId);
            printf("Enter password: ");
            scanf("%s", password);
            index = memberId - 200;  // Calculate index based on id

            if (index >= 0 && index < mcount && strcmp(member[index].mpass, password) == 0) {
                printf("Welcome, %s!\n", member[index].mname);  // Display welcome message with member name
                while (1) {
                    printf("\t1. View Book\n\t2. Lend Book\n\t3. Return Book\n\t4. Log out\nEnter your choice: ");
                    int m;
                    scanf("%d", &m);
                    if (m == 1) {
                        viewbook();
                    } else if (m == 2) {
                        char d[100];
                        int c;
                        printf("Enter Book name: ");
                        scanf("%s", d);
                        printf("Enter Book id: ");
                        scanf("%d", &c);
                        if (member[index].rbook == 0 && book[c - 100].bkflag == 1) {
                            member[index].rbook = book[c - 100].bid;
                            book[c - 100].bkflag = 0;
                            printf("Book Lended Successfully!\n");
                            saveBooks();
                            saveMembers();
                        } else {
                            printf("Book is either already issued or you have already borrowed a book.\n");
                        }
                    } else if (m == 3) {
                        if (member[index].rbook != 0) {
                            book[member[index].rbook - 100].bkflag = 1;
                            member[index].rbook = 0;
                            printf("Book returned successfully!\n");
                            saveBooks();
                            saveMembers();
                        } else {
                            printf("No book to return.\n");
                        }
                    } else if (m == 4) {
                        break;
                    } else {
                        printf("Invalid choice.\n");
                    }
                }
            } else {
                printf("Invalid credentials.\n");
            }
        } else if (n == 2) {
            addMember();
            saveMembers();
        } else if (n == 3) {
            break;
        }
    }
}

int main() {
    
    
    loadAdmins();
    while (1) {
        int choice;
        printf("\n------------> WELCOME T4TEQ LIBRARY <-------------\n");
        printf("\t1. Admin\n\t2. Member\n\t3. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            admin();
            
        } else if (choice == 2) {
            loadMembers();
            mem();
        } else if (choice == 3) {
            printf("Exiting system...\n");
            break;
        } else {
            printf("Invalid choice...\n");
        }
    }
    return 0;
}
