#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct book{
    char title[50];
    char author[70];
    char isbn[14];
    struct book* left;
    struct book* right;
};


struct book* create_node(char* title,char* author,char* isbn){
    struct book* books=(struct book*)malloc(sizeof(struct book));
    strcpy(books->title,title);
    strcpy(books->author,author);
    strcpy(books->isbn,isbn);
    books->left=NULL;
    books->right=NULL;
    return books;
}

void insert(struct book** root,char* title,char* author, char* isbn){
    if(*root==NULL){
        *root=create_node(title,author,isbn);
        return;
    }
    if(strcmp(isbn,(*root)->isbn)<0){
        insert(&((*root)->left), title, author, isbn);
    }else if(strcmp(isbn, (*root)->isbn) > 0) {
        insert(&((*root)->right), title, author, isbn);
    }
}

struct book* remove_node(struct book** root,const char* isbn){
    if(*root==NULL) return NULL;
    
    if(strcmp(isbn,(*root)->isbn)<0){
            (*root)->left = remove_node(&((*root)->left), isbn);
    }else if(strcmp(isbn,(*root)->isbn)>0){
        (*root)->right = remove_node(&((*root)->right), isbn);
    }else{
         struct book* temp = NULL;
        if ((*root)->left == NULL && (*root)->right == NULL) {
		    free(*root); 
		    return NULL;  
		}
        else if ((*root)->left == NULL) {
            temp = (*root)->right;
            free(*root);
            return temp;
        } else if ((*root)->right == NULL) {
            temp = (*root)->left;
            free(*root);
            return temp;
        } else {
            struct book* successor = (*root)->right;
            while (successor->left != NULL) successor = successor->left;
            strcpy((*root)->isbn, successor->isbn);
            strcpy((*root)->title, successor->title);
            strcpy((*root)->author, successor->author);
            (*root)->right = remove_node(&((*root)->right), successor->isbn);
        }
    }
    return *root;
}

void search(struct book* root, const char* isbn){
    if(root==NULL){
    	printf("\n\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ");
        printf("\n\t\t\t\t\t     BOOK NOT FOUND!");
        printf("\n\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ");
        return;
    }
    if(strcasecmp(isbn, root->isbn) == 0) {
		printf("\n\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ");
        printf("\n\t\t\t\tISBN: %s ",root->isbn);
		printf("\n\t\t\t\tTitle: %s ", root->title);
		printf("\n\t\t\t\tAuthor: %s ",root->author);
        printf("\n\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ");
        return;
    }
    if (strcasecmp(isbn, root->isbn) < 0) {
        search(root->left, isbn);
    } else {
        search(root->right, isbn);
    }
}

void printing_books(struct book* root){
    if(root){
        printing_books(root->left);
        printf("\n\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ");
        printf("\n\t\t\t\tISBN: %s ",root->isbn);
		printf("\n\t\t\t\tTITLE: %s ", root->title);
		printf("\n\t\t\t\tAUTHOR: %s ",root->author);
        printf("\n\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ");
        printing_books(root->right);
    }
}

int main()
{
    struct book* library = NULL;
    int ch;
    char title[100];
    char author[100];
    char isbn[20];
    char str1[6],str2[6];
    char un[] = "admin";
    char pswd[] = "admin";
    printf("Enter Username: ");
    scanf("%s", str1);
    printf("Enter Password: ");
    scanf("%s", str2);

    if (strcmp(un, str1) == 0 && strcmp(pswd, str2) == 0)
    {
        printf("WELCOME TO LIBRARY MANAGEMENT SYSTEM!");
        while (1) {
            printf("\n\n\n\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ");
            printf("\n\t\t\t|                                                         | ");
            printf("\n\t\t\t|                LIBRARY MANAGEMENT SYSTEM                | ");
            printf("\n\t\t\t|                                                         | ");
            printf("\n\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ");
            printf("\n\t\t\t|   1. Add new book                                       |");
            printf("\n\t\t\t|   2. Remove book                                        |");
            printf("\n\t\t\t|   3. Search for book                                    |");
            printf("\n\t\t\t|   4. Print all books                                    |");
            printf("\n\t\t\t|   5. Exit                                               |");
            printf("\n\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ");
            
            printf("\nEnter your choice: ");
            scanf("%d", &ch);
            getchar(); 
            
            switch (ch) {
                case 1:
                	printf("\n\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ");
			    	printf("\n\t\t\t|                                                         | ");
			        printf("\n\t\t\t|                     ADD THE BOOK                        | ");
			        printf("\n\t\t\t|                                                         | ");
			        printf("\n\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ");
                    printf("\n\t\t\t\tEnter Title: ");
                    fgets(title, sizeof(title), stdin);
                    title[strcspn(title, "\n")] = '\0';  
    
                    printf("\n\t\t\t\tEnter Author: ");
                    fgets(author, sizeof(author), stdin);
                    author[strcspn(author, "\n")] = '\0';
    
                    printf("\n\t\t\t\tEnter ISBN: ");
                    fgets(isbn, sizeof(isbn), stdin);
                    isbn[strcspn(isbn, "\n")] = '\0'; 
					printf("\n\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "); 
                    
                    insert(&library, title, author, isbn);
                    break;
                case 2:
                	printf("\n\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ");
			    	printf("\n\t\t\t|                                                         | ");
			        printf("\n\t\t\t|                  DELETE THE BOOK                        | ");
			        printf("\n\t\t\t|                                                         | ");
			        printf("\n\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ");
                    printf("\n\t\t\t\tEnter ISBN Of The Book To Remove: ");
                    fgets(isbn, sizeof(isbn), stdin);
                    isbn[strcspn(isbn, "\n")] = '\0';  
                    printf("\n\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ");
                    
                    library = remove_node(&library, isbn);
                    break;
                case 3:
                	printf("\n\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ");
			    	printf("\n\t\t\t|                                                         | ");
			        printf("\n\t\t\t|               SEARCH FOR THE BOOK                       | ");
			        printf("\n\t\t\t|                                                         | ");
			        printf("\n\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ");
                    printf("\n\t\t\t\tEnter ISBN To Search For: ");
                    fgets(isbn, sizeof(isbn), stdin);
                    isbn[strcspn(isbn, "\n")] = '\0'; 
                    
                    search(library, isbn);
                    break;
                case 4:
                	printf("\n\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ");
			    	printf("\n\t\t\t|                                                         | ");
			        printf("\n\t\t\t|                LIST OF THE BOOKS                        | ");
			        printf("\n\t\t\t|                                                         | ");
			        printf("\n\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ");
                    printing_books(library);
                    break;
                case 5:
                    exit(0);
                default:
                    printf("Invalid choice selected!\n");
                }
        }
    }
    else
    {
        printf("Enter Valid Username and Password!");
    }
}
