#include <stdio.h>
#include <string.h>

typedef struct {
    int id;
    float weight;
    char name[100];
    char date[100];
    int price;
} Node;

int size = 0;

void swap(Node *a, Node *b) {
    Node temp = *b;
    *b = *a;
    *a = temp;
}
void heapify(Node array[], int size, int i) {
    if (size == 1) {
        printf("Single element in the heap\n");
    } else {
        int largest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        if (l < size && array[l].weight > array[largest].weight) 
            largest = l;
        if (r < size && array[r].weight > array[largest].weight)
            largest = r;
        if (largest != i) {
            swap(&array[i], &array[largest]);
            heapify(array, size, largest);
        }
    }
}

void insert(Node array[], Node newNum) {
    if (size == 0) {
        array[0] = newNum;
        size += 1;
    } else {
        array[size] = newNum;
        size += 1;
        for (int i = size / 2 - 1; i >= 0; i--) {
            heapify(array, size, i);
        }
    }
}

void deleteRoot(Node array[], int id) {
    int i;
    for (i = 0; i < size; i++) {
        if (id == array[i].id)
            break;
    }
    if (i == size) {
        printf("Node with ID %d not found.\n", id);
        return;
    }
    swap(&array[i], &array[size - 1]);
    size -= 1;
    for (i = size / 2 - 1; i >= 0; i--) {
        heapify(array, size, i);
    }
}


void printArray(Node array[], int size) {
    for (int i = 0; i < size; ++i){
    	printf("Data Barang ke-%d\n",i+1);
        printf("Name: %s\n", array[i].name);
        printf("ID: %d\n", array[i].id);
        printf("Date of arrival: %s\n", array[i].date);
        printf("Price: %d\n", array[i].price);
        printf("Weight: %.2f\n\n", array[i].weight);
    }
    printf("\n");
}

void findMax(Node array[]) {
    printf("The maximum node in the heap is ID: %d, Weight: %.2f, Name: %s, Date: %s, Price: %d\n", array[0].id, array[0].weight, array[0].name, array[0].date, array[0].price);
}

void file(Node array[], int size) {

    FILE *file = fopen("file.txt", "w");
    if (file == NULL) {
        printf("File not found.\n");
        return;
    }
    for (int i = 0; i < size; ++i){
        fprintf(file,"Name: %s\n", array[i].name);
        fprintf(file,"ID: %d\n", array[i].id);
        fprintf(file,"Date of arrival: %s\n", array[i].date);
        fprintf(file,"Price: %d\n", array[i].price);
        fprintf(file,"Weight: %.2f\n\n", array[i].weight);
    }
    
    fclose(file);
    printf("Data saved.\n");
}

void displayFile(Node array[], int *size) {
    FILE *file = fopen("file.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    Node newNum;
    while (fscanf(file, "Name: %[^\n]\n", newNum.name) != EOF) {
        fscanf(file, "ID: %d\n", &newNum.id);
        fscanf(file, "Date of arrival: %[^\n]\n", newNum.date);
        fscanf(file, "Price: %d\n", &newNum.price);
        fscanf(file, "Weight: %f\n\n", &newNum.weight);
        insert(array, newNum);
    }
    fclose(file);

    printArray(array, *size);
}

int search(Node array[],int size,int target ){
	int i;  
    for (i = 0; i< size; i++) {  
        if (array[i].id == target) {  
            return i;   
        }  
    }  
    return -1;  
}

int main() {
	Node array[100];
	int num,id,target;;
	Node newNum;
	while (num != 8) {
        printf("1. Insert\n");
        printf("2. Display\n");
        printf("3. Delete\n");
        printf("4. Search\n");
        printf("5. Update to database\n");
        printf("6. Read database\n");
        printf("7. Update a product\n");
        printf("8. Quit\n");
        printf("Input your choice\n");
        scanf("%d", &num);
        switch (num){
        	case 1:
        		printf("Masukan nama product\n");
                scanf("%s", newNum.name);
                printf("Masukan ID product\n");
                scanf("%d", &newNum.id);
                printf("Masukan tanggal kedatangan product(MM/DD/YY)\n");
                scanf("%s", newNum.date);
                printf("Masukan harga product\n");
                scanf("%d", &newNum.price);
                printf("Masukan berat prodcut\n");
                scanf("%f", &newNum.weight);
                insert(array,newNum);
                break;
        	case 2:
        		printArray(array, size);
        		break;
			case 3:
				printf("Masukan ID product yang ingin didelete\n");
				scanf("%d",&id);
				deleteRoot(array,id);
				break;
			case 4:
				printf("Masukan ID product yang ingin dicari\n");
				scanf("%d",&target);
				 int result = search(array, size, target);  
    				if (result == -1) {  
						printf("Data tidak dapat ditemukan.\n");  
 				   }
					 else {  
					printf("Data dengan ID:%d dapat ditemukan\n", target);  
    				}  
				break;
			case 5:
				file(array,size);
				break;
			case 6:
				size=0;
				displayFile(array,&size);
				break;
			case 7:
				break;
			case 8:
				printf("Quit\n");
				break;
			default:
				printf("Invalid choice. Please try again.\n");					
		}
	}
    


    return 0;
}

