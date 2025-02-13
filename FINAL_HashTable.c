#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 10

struct node{
    int ID;
    char name[20];
    char date[20];
    int price;
    float weight;
    struct node *next;
};

struct node *hashTable[SIZE];

int i;
struct node *head = NULL;
struct node *newNode = NULL;
struct node *curr = NULL;

int hash(int key){
    return (key * 31) % SIZE;
}

void insert(){
    int hashIndex = hash(newNode->ID);
    curr = hashTable[hashIndex];
    if (curr == NULL){
        hashTable[hashIndex] = newNode;
        return;
    }
    while(curr->next != NULL){
        curr = curr->next;
    }
    curr->next = newNode;
}

void deletee(int key){
    int hashIndex = hash(key);
    curr = hashTable[hashIndex];
    if(curr == NULL){
        printf("List is empty, nothing to delete.\n");
        return;
    }
    if(curr->ID == key){
        hashTable[hashIndex] = curr->next;
        free(curr);
        return;
    }
    while(curr->next != NULL && curr->next->ID != key){
        curr = curr->next;
    }
    if(curr->next != NULL){
        struct node *del = curr->next;
        curr->next = curr->next->next;
        free(del);
    } 
	else{
        printf("Item not found\n");
    }
}

void display(){
    int checkEmpty = 1;
    for(i = 0; i < SIZE; i++){
        curr = hashTable[i];
        while (curr != NULL){
            printf("%-10d%-10s%-10d%-10.3f%-10s\n", curr->ID, curr->name, curr->price, curr->weight, curr->date);
            curr = curr->next;
            checkEmpty = 0;
        }
    }
    if(checkEmpty == 1){
        printf("List is empty\n");
    }
}

void search(int key){
    int hashIndex = hash(key);
    curr = hashTable[hashIndex];
    while(curr != NULL){
        if (curr->ID == key){
            printf("Data found !!!\n");
            printf("ID : %d\n", curr->ID);
            printf("Name : %s\n", curr->name);
            printf("Price : %d\n", curr->price);
            printf("Weight : %.3f\n", curr->weight);
            printf("Date item : %s\n\n", curr->date);

            printf("Insert new item name: ");
            scanf(" %[^\n]", curr->name);

            printf("Insert new item price: ");
            scanf("%d", &curr->price);

            printf("Insert new item weight: ");
            scanf("%f", &curr->weight);

            printf("Insert new date item added (dd/mm/yy): ");
            scanf(" %[^\n]", curr->date);

            printf("\nData successfully updated with details:\n");
            printf("ID : %d\n", curr->ID);
            printf("Name : %s\n", curr->name);
            printf("Price : %d\n", curr->price);
            printf("Weight : %.3f\n", curr->weight);
            printf("Date item : %s\n\n", curr->date);
            return;
        }
        curr = curr->next;
    }
    printf("Data not found. Returning...\n");
}

int main(){
    // Baca file
    FILE *fp;
    fp = fopen("data", "r");

    while(1){
        newNode = (struct node*) malloc(sizeof(struct node));
        newNode->next = NULL;
        if(fscanf(fp, "%d,%[^,],%[^,],%f,%d", &newNode->ID, newNode->name, newNode->date, &newNode->weight, &newNode->price) == 5){
            insert();
        } 
		else{
            free(newNode);
            break;
        }
    }
    fclose(fp);

    // Menu
    while (1) {
        int ID, opt, key;
        printf("Warehouse\n");
        printf("===============\n");
        printf("1. Insert\n2. Delete\n3. Update\n4. Display\n5. Save\n");
        printf(">> ");
        scanf("%d", &opt);
        system("cls");

        switch (opt){
            case 1:
                newNode = (struct node*) malloc(sizeof(struct node));
                newNode->next = NULL;

                printf("Masukkan ID barang: ");
                scanf("%d", &newNode->ID);
                getchar();  

                printf("Masukkan nama barang: ");
                scanf(" %[^\n]", newNode->name);
                getchar();  

                while (1) {
                    int isValid = 1;

                    printf("Masukkan tanggal item ditambahkan [dd/mm/yy]: ");
                    scanf("%s", newNode->date);
                    getchar();  

                    if(strlen(newNode->date) != 8 || newNode->date[2] != '/' || newNode->date[5] != '/'){
                        isValid = 0;
                    } 
					else{
                        for (i = 0; i < 8; i++){
                            if((i != 2 && i != 5) && (newNode->date[i] < '0' || newNode->date[i] > '9')){
                                isValid = 0;
                                break;
                            }
                        }
                    }

                    if(isValid){
                        break;
                    }
					else{
                        printf("Tanggal tidak sesuai format, harap ulangi\n");
                    }
                }

                printf("Masukkan harga barang: ");
                scanf("%d", &newNode->price);

                printf("Masukkan berat barang (dalam gram): ");
                scanf("%f", &newNode->weight);
                getchar();  

                insert();
                break;

            case 2:
                printf("Masukkan ID item untuk dihapus: ");
                scanf("%d", &key);
                deletee(key);
                break;

            case 3:
                printf("Masukkan ID barang yang ingin diupdate: ");
                scanf("%d", &key);
                search(key);
                break;

            case 4:
                display();
                break;

            case 5:
                fp = fopen("data", "w");
                for(i = 0; i < SIZE; i++) {
                    curr = hashTable[i];
                    while (curr != NULL) {
                        fprintf(fp, "%d,%s,%s,%.3f,%d\n", curr->ID, curr->name, curr->date, curr->weight, curr->price);
                        curr = curr->next;
                    }
                }
                fclose(fp);
                printf("Saved successfully\n");
                break;

            default:
                printf("Invalid input\n");
                break;
        }
    }

    return 0;
}

