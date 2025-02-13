#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
	int id;
	char name[20];
	int price;
	float weight;
	char date[20];
	struct node *next;
	struct node *prev;
};

struct node *head, *tail, *curr;

void insertNode(){
	
	struct node *newNode = (struct node*)malloc(sizeof(struct node));

	printf("Insert ID: ");
	scanf("%d", &newNode->id);
	
	printf("Insert item name : ");
	scanf(" %[^\n]", newNode->name);
	
	printf("Insert item price : ");
	scanf("%d", &newNode->price);
	
	printf("Insert item weight : ");
	scanf("%f", &newNode->weight);
	
	printf("Insert date item added (MM/DD/YY): ");
	scanf(" %[^\n]", newNode->date);
	
	printf("\n\n");

	if(head == NULL){
		printf("List does'nt exist, creating first list...\n");
		newNode->next = NULL;
		newNode->prev = NULL;
		curr = head = tail = newNode;
		printf("first list added !!!\n\n");
	}else{
		int opt;
		char opt2,opt3;
		printf("Choose insert option :\n");
		printf("1. Head list\n");
		printf("2. Position based\n");
		printf("3. Tail list\n>> ");
		scanf("%d", &opt);
			if(opt == 1){
				newNode->next = head;
				newNode->prev = NULL;
				head->prev = newNode;
				head = newNode;
			}else if(opt == 2){
				int temp_id;
				printf("Masukkan ID sebagai posisi: ");
				scanf("%d", &temp_id);
				
				curr = head;
				while(curr != NULL){
					if(curr->id == temp_id){
						printf("\nInsert data after :\n");
						printf("ID: %d\n", curr->id);
						printf("Name : %s\n", curr->name);
						printf("Price : %d\n", curr->price);
						printf("Weight : %.3f\n", curr->weight);
						printf("Date item : %s\n", curr->date);
						printf("Continue ?(y/n)\n>> ");
						scanf(" %c", &opt2);
						if(opt2 == 'y'){
							newNode->next = curr->next;
							newNode->prev = curr;
							curr->next = newNode;
							if(newNode->next != NULL){
								curr = newNode->next;
								curr->prev = newNode;
							}else{
								tail = newNode;
							}
							printf("Added Successfully !!!\n\n");
							break;
						}else if(opt2 == 'n'){
							printf("Back to menu : ...\n");
							free(newNode);
							break;
						}else{
							printf("Wrong input, returning...\n\n");
							free(newNode);
							break;
						}
					}
					curr = curr->next;
				}
				if(curr == NULL){
					printf("Data not found!!!\n\n");
					free(newNode);
				}
			}else if(opt == 3){
				newNode->next = NULL;
				newNode->prev = tail;
				tail->next = newNode;
				curr = tail = newNode;
				printf("Added Successfully !!!\n\n");
			}else{
				printf("Wrong input, returning...\n\n");
				free(newNode);
			}
	}

}

void printList(){
	if(head == NULL){
		printf("List doesn't exist.\n\n");
		return;
	}
	
	curr = head;
	printf("Linked List:\n");
	while(curr != NULL){
		printf("ID : %d\n", curr->id);
		printf("Name : %s\n", curr->name);
		printf("Price : %d\n", curr->price);
		printf("Weight : %.3f\n", curr->weight);
		printf("Date item : %s\n\n", curr->date);
		curr = curr->next;
	}
	printf("\n");
}

void delete_node(int id){
	if(head == NULL){
		printf("List doesn't exist\n\n");
		return;
	}
	
	struct node *del = head;
	char opt,opt2;
	while(del != NULL){
		if(del->id == id){
			printf("\nData details :\n");
			printf("ID : %d\n", del->id);
			printf("Name : %s\n", del->name);
			printf("Price : %d\n", del->price);
			printf("Weight : %.3f\n", del->weight);
			printf("Date item : %s\n", del->date);
			printf("Continue ? (y/n)\n>> ");
			scanf(" %c", &opt);
			if(opt == 'y'){
				if(head == tail){
					free(del);
					head = tail = curr = NULL;
				}else if(del == tail){
					curr = del->prev;
					curr->next = NULL;
					del->prev = NULL;
					tail = curr;
					free(del);
				}else if(del == head){
					curr = del->next;
					curr->prev = NULL;
					del->next = NULL;
					head = curr;
					free(del);
				}else{
					curr = del->prev;
					curr->next = del->next;
					curr = del->next;
					curr->prev = del->prev;
					del->next = del->prev = NULL;
					free(del);
				}
				printf("Data deleted succesfully !!!\n\n");
				break;
			}else if(opt == 'n'){
				printf("Back to menu...\n");
			}else{
				printf("Wrong input, returning...\n\n");
				break;
			}
		}
		del = del->next;
	}
	if(del == NULL){
		printf("Data's not found !!!\n");
	}
}

void search_data(int id){
	curr = head;
	while(curr != NULL){
		if(curr->id == id){
			printf("Data found !!!\n");
			printf("ID : %d\n", curr->id);
			printf("Name : %s\n", curr->name);
			printf("Price : %d\n", curr->price);
			printf("Weight : %.3f\n", curr->weight);
			printf("Date item : %s\n\n", curr->date);
			return;
		}
		curr = curr->next;
	}
	if(curr == NULL){
		printf("Data not found. Returning...\n");
		return;
	}
}

void update_data(int id){
	curr = head;
	while(curr != NULL){
		if(curr->id == id){
			printf("Data found !!!\n");
			printf("ID : %d\n", curr->id);
			printf("Name : %s\n", curr->name);
			printf("Price : %d\n", curr->price);
			printf("Weight : %.3f\n", curr->weight);
			printf("Date item : %s\n\n", curr->date);
			break;
		}
		curr = curr->next;
	}
	
	if(curr == NULL){
		printf("Data not found. Returning...\n");
		return;
	}
	
	printf("Insert new item name : ");
	scanf(" %[^\n]", curr->name);
	
	printf("Insert new item price : ");
	scanf("%d", &curr->price);
	
	printf("Insert new item weight : ");
	scanf("%f", &curr->weight);
	
	printf("Insert new date item added (MM/DD/YY): ");
	scanf(" %[^\n]", curr->date);
	
	printf("\nData successfully updated with details :\n");
	printf("ID : %d\n", curr->id);
	printf("Name : %s\n", curr->name);
	printf("Price : %d\n", curr->price);
	printf("Weight : %.3f\n", curr->weight);
	printf("Date item : %s\n\n", curr->date);
	
}

void save_data(){
	FILE *fp;
	fp = fopen("data.txt", "w");
	
	curr = head;
	while(curr != NULL){
		fprintf(fp, "%d %s, %d %.5f %s\n", curr->id, curr->name, curr->price, curr->weight, curr->date);
		curr = curr->next;
	}
	fclose(fp);
}

void load_data(){
	FILE *fp;
	fp = fopen("data.txt", "r");
	if(fp == NULL){
		fclose(fp);
		return;
	}

	int temp_id, temp_price;
	char temp_name[20], temp_date[20];
	float temp_weight;
	
	head = tail = NULL;
	
	while(fscanf(fp, "%d %[^,], %d %f %[^\n]\n", &temp_id, temp_name, &temp_price, &temp_weight, temp_date) != EOF){
		struct node *newNode = malloc(sizeof(struct node));
		newNode->next = NULL;
		newNode->prev = NULL;
		
		newNode->id = temp_id;
		newNode->price = temp_price;
		newNode->weight = temp_weight;
		strcpy(newNode->name, temp_name);
		strcpy(newNode->date, temp_date);

		if(head == NULL){
			head = tail = newNode;
		}else{
			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;
		}
	}
	fclose(fp);
}

int menu_option(){
	int opt;
	printf("Warehouse\n");
	printf("===============\n");
	printf("1. Insert data\n");
	printf("2. Delete data\n");
	printf("3. Display all data\n");
	printf("4. Search data\n");
	printf("5. Update data\n");
	printf("6. Exit\n");
	printf(">> ");
	scanf("%d", &opt);
	
	return opt;
}

int main(){
	load_data();
	int opt, id;
	while(1){
		opt = menu_option();
		if(opt == 1){
			insertNode();
		}else if(opt == 2){
			printf("Type item's ID :\n");
			scanf("%d", &id);
			delete_node(id);
		}else if(opt == 3){
			printList();
		}else if(opt == 4){
			printf("Type item's ID :\n");
			scanf("%d", &id);
			search_data(id);
		}else if(opt == 5){
			printf("Type item's ID :\n");
			scanf("%d", &id);
			update_data(id);
		}else if(opt == 6){
			save_data();
			return 0;
		}else{
			printf("Please choose the right option !!!\n");
		}
	}

return 0;
}

