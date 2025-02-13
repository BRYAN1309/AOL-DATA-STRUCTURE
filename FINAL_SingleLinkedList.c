#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    int id;
    float weight;
    char name[100];
    char date[100];
    int price;
    struct node *next;
} *head, *newNode, *temp;

struct node *head = NULL;

void insert(char name[100], int id, char date[100], int price, float weight) {
    newNode = (struct node*) malloc(sizeof(struct node));
    newNode->id = id;
    newNode->weight = weight;
    strcpy(newNode->name, name);
    strcpy(newNode->date, date);
    newNode->price = price;
    newNode->next = NULL;
    if (head == NULL)
        head = newNode;
    else {
        temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void print() {
    temp = head;
    while (temp != NULL) {
        printf("Data Barang\n");
        printf("Name: %s\n", temp->name);
        printf("ID: %d\n", temp->id);
        printf("Date of arrival: %s\n", temp->date);
        printf("Price: %d\n", temp->price);
        printf("Weight: %f\n", temp->weight);
        temp = temp->next;
    }
}

void del(int del1) {
    temp = head;
    if (head->id == del1) {
        head = head->next;
        free(temp);
    } else {
        while (temp->next != NULL && temp->next->id != del1)
            temp = temp->next;
        if (temp->next != NULL) {
            struct node *ptr = temp->next;
            temp->next = ptr->next;
            free(ptr);
        }
    }
}

void search(int num1) {
    temp = head;
    while (temp != NULL && temp->id != num1)
        temp = temp->next;
    if (temp != NULL) {
        printf("Data ditemukan.\n");
        printf("Name: %s\n", temp->name);
        printf("ID: %d\n", temp->id);
        printf("Date of arrival: %s\n", temp->date);
        printf("Price: %d\n", temp->price);
        printf("Weight: %.2f\n", temp->weight);
    } else {
        printf("Data tidak ditemukan.\n");
    }
}

void sort() {
    if (head == NULL)
        return;
    
    struct node *i, *j;
    int tempID;
    int tempPrice;
    char tempName[100];
    char tempDate[100];
    float tempWeight;
    
    for (i = head; i->next != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->id > j->id) {
                tempID = i->id;
                i->id = j->id;
                j->id = tempID;
                
                strcpy(tempName, i->name);
                strcpy(i->name, j->name);
                strcpy(j->name, tempName);
                
                strcpy(tempDate, i->date);
                strcpy(i->date, j->date);
                strcpy(j->date, tempDate);
                
                tempPrice = i->price;
                i->price = j->price;
                j->price = tempPrice;
                
                tempWeight = i->weight;
                i->weight = j->weight;
                j->weight = tempWeight;
            }
        }
    }
}

void file() {
    FILE *file = fopen("file.txt", "w");
    if (file == NULL) {
        printf("File not found.\n");
        return;
    }
    temp = head;
    while (temp != NULL) {
        fprintf(file, "Name: %s\n", temp->name);
        fprintf(file, "ID: %d\n", temp->id);
        fprintf(file, "Date of arrival: %s\n", temp->date);
        fprintf(file, "Price: %d\n", temp->price);
        fprintf(file, "Weight: %f\n", temp->weight);
        temp = temp->next;
    }
    fclose(file);
    printf("Data saved.\n");
}

void displayFile() {
    int id;
    float weight;
    char name[100];
    char date[100];
    int price;
    FILE *file = fopen("file.txt", "r");
    if (file == NULL) {
        printf("File does not exist \n");
        return;
    }
    
    while (fscanf(file, "Name: %s\n", name) != EOF) {
        fscanf(file, "ID: %d\n", &id);
        fscanf(file, "Date of arrival: %s\n", date);
        fscanf(file, "Price: %d\n", &price);
        fscanf(file, "Weight: %f\n", &weight);
        insert(name, id, date, price, weight);
    }
    temp = head;
    while (temp != NULL) {
        printf("Data Barang\n");
        printf("Name: %s\n", temp->name);
        printf("ID: %d\n", temp->id);
        printf("Date of arrival: %s\n", temp->date);
        printf("Price: %d\n", temp->price);
        printf("Weight: %f\n", temp->weight);
        temp = temp->next;
    }
    fclose(file);
}

void update(int id) {
    temp = head;
    while (temp != NULL&& temp->id != id)
        temp = temp->next;
    if (temp != NULL) {
        printf("Updating product with ID %d\n", id);
        printf("Input the new product name\n");
        scanf("%s", temp->name);
        printf("Input the new product Date of arrival (MM/DD/YY)\n");
        scanf("%s", temp->date);
        printf("Input the new product price\n");
        scanf("%d", &temp->price);
        printf("Input the new product weight\n");
        scanf("%f", &temp->weight);
    } else {
        printf("Product with ID %d not found.\n", id);
    }
}

int main() {
    int num, num1;
    int id;
    float weight;
    char name[100];
    char date[100];
    int price;
    int del1;
    
    while (num != 9) {
        printf("1. Insert\n");
        printf("2. Display\n");
        printf("3. Delete\n");
        printf("4. Search\n");
        printf("5. Sort\n");
        printf("6. Update to database\n");
        printf("7. Read database\n");
        printf("8. Update a product\n");
        printf("9. Quit\n");
        printf("Input your choice\n");
        scanf("%d", &num);
        switch (num) {
            case 1:
                printf("Input the product name\n");
                scanf("%s", name);
                printf("Input the product ID\n");
                scanf("%d", &id);
                printf("Input the product Date of arrival (MM/DD/YY)\n");
                scanf("%s", date);
                printf("Input the product price\n");
                scanf("%d", &price);
                printf("Input the product weight\n");
                scanf("%f", &weight);
                insert(name, id, date, price, weight);
                break;
            case 2:
                print();
                break;
            case 3:
                printf("Masukan barang dengan id yang ingin di delete\n");
                scanf("%d", &del1);
                del(del1);
                break;
            case 4:
                printf("Masukan ID barang yang ingin dicari\n");
                scanf("%d", &num1);
                search(num1);
                break;
            case 5:
                sort();
                printf("Sorted Data:\n");
                print();
                break;
            case 6:
                file();
                break;
            case 7:
                displayFile();
                break;
            case 8:
                printf("Masukan ID barang yang ingin diupdate\n");
                scanf("%d", &id);
                update(id);
                break;
            case 9:
                printf("Exit\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

