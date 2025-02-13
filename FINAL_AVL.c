#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tnode{
	int id;
	char name[20];
	int price;
	float weight;
	char date[20];
	struct tnode *left;
	struct tnode *right;
	int height;
};

int max(int a, int b){
	if(a > b){
		return a;
	}else{
		return b;
	}
}

int height(struct tnode *N){
	if(N == NULL){
		return 0;
	}
	
return N->height;
}

struct tnode *newtnode(int id, char name[], int price, float weight, char date[]){
	struct tnode *tnode = (struct tnode *)malloc(sizeof(struct tnode));
	tnode->id = id;
	tnode->price = price;
	tnode->weight = weight;
	strcpy(tnode->name, name);
	strcpy(tnode->date, date);
	
	tnode->left = NULL;
	tnode->right = NULL;
	tnode->height = 1;
	
return(tnode);
}

struct tnode *rightRotate(struct tnode *y){
  struct tnode *x = y->left;
  struct tnode *T2 = x->right;

  x->right = y;
  y->left = T2;

  y->height = max(height(y->left), height(y->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;

  return x;
}

struct tnode *leftRotate(struct tnode *x){
	struct tnode *y = x->right;
	struct tnode *T2 = y->left;
	
	y->left = x;
	x->right = T2;
	
	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;
	
return y;
}

int getBalance(struct tnode *N){
	if(N == NULL){
		return 0;
	}
	
return height(N->left) - height(N->right);
}

struct tnode *inserttnode(struct tnode *tnode, int id, char name[], int price, float weight, char date[]){
	if(tnode == NULL){
		return(newtnode(id, name, price, weight, date));
	} 

	if(id < tnode->id){
		tnode->left = inserttnode(tnode->left, id, name, price, weight, date);
	}

	else if(id > tnode->id){
		tnode->right = inserttnode(tnode->right, id, name, price, weight, date);
	}
	else{
		return tnode;
	}

	tnode->height = 1 + max(height(tnode->left), height(tnode->right));

	int balance = getBalance(tnode);
	if(balance > 1 && id < tnode->left->id){
		return rightRotate(tnode);
	}
		
	if(balance < -1 && id > tnode->right->id){
		return leftRotate(tnode);
	}

	if(balance > 1 && id > tnode->left->id){
		tnode->left = leftRotate(tnode->left);
		return rightRotate(tnode);
	}

	if(balance < -1 && id < tnode->right->id){
		tnode->right = rightRotate(tnode->right);
		return leftRotate(tnode);
	}

return tnode;
}

struct tnode *minValuetnode(struct tnode *node){
	struct tnode *current = node;

	while(current->left != NULL){
		current = current->left;
	}

return current;
}

struct tnode *delete_tnode(struct tnode *root, int id, int *found){
  if(root == NULL){
  	return root;
  }
  
  if(id < root->id){
  	root->left = delete_tnode(root->left, id, found);
  }else if(id > root->id){
  	root->right = delete_tnode(root->right, id, found);
  }else{
  	*found = 1;
    if((root->left == NULL) || (root->right == NULL)){
      struct tnode *temp;
      
	  if(root->left != NULL){
	  	temp = root->left;
	  }else{
	  	temp = root->right;
	  }

      if(temp == NULL){
        temp = root;
        root = NULL;
      }else{
      	*root = *temp;
      	free(temp);
	  }
        
    }else{
      struct tnode *temp = minValuetnode(root->right);
      root->id = temp->id;
      root->weight = temp->weight;
      root->price = temp->price;
      strcpy(root->name, temp->name);
      strcpy(root->date, temp->date);
      
      root->right = delete_tnode(root->right, temp->id, found);
    }
  }

  if(root == NULL){
  	return root;
  }
    
  root->height = 1 + max(height(root->left), height(root->right));

  int balance = getBalance(root);
  
  if(balance > 1 && getBalance(root->left) >= 0){
  	return rightRotate(root);
  }
    
  if(balance > 1 && getBalance(root->left) < 0){
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }
	
  if(balance < -1 && getBalance(root->right) <= 0){
  	return leftRotate(root);
  }
    
  if(balance < -1 && getBalance(root->right) > 0){
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }

  return root;
}

void printPreOrder(struct tnode *root){
	if(root != NULL){
		printf("ID item: %d\n", root->id);
		printf("Item name: %s\n", root->name);
		printf("Item price : %d\n", root->price);
		printf("Item weight : %.3f\n", root->weight);
		printf("Item date: %s\n\n", root->date);
		printPreOrder(root->left);
		printPreOrder(root->right);
	}
}

void search_tnode(struct tnode *root, int id, int *found){
	if(root != NULL){
		if(id == root->id){
			printf("Data found !!!\n");
			printf("ID item: %d\n", root->id);
			printf("Item name: %s\n", root->name);
			printf("Item price : %d\n", root->price);
			printf("Item weight : %.3f\n", root->weight);
			printf("Item date: %s\n\n", root->date);
			*found = 1;
			return;
		}
		search_tnode(root->left, id, found);
		search_tnode(root->right, id, found);
	}
}

struct tnode *update_tnode(struct tnode *root, int id, int *found){
    if(root != NULL){
        if(id == root->id){
        	printf("Data found !!!\n");
			printf("ID item: %d\n", root->id);
			printf("Item name: %s\n", root->name);
			printf("Item price : %d\n", root->price);
			printf("Item weight : %.3f\n", root->weight);
			printf("Item date : %s\n\n", root->date);

            printf("New Item name: "); scanf(" %[^\n]", root->name);
            printf("New Item price : "); scanf("%d", &root->price);
            printf("New Item weight : "); scanf("%f", &root->weight);
            printf("New Item date: "); scanf(" %[^\n]", root->date);

            *found = 1;
            return root;
        }
        root->left = update_tnode(root->left, id, found);
        root->right = update_tnode(root->right, id, found);
    }
    return root;
}

struct tnode *load_data_avl(struct tnode *root, FILE *fp){
	int temp_id, temp_price;
	char temp_name[20], temp_date[20];
	float temp_weight;
	
	while(fscanf(fp, "%d %[^,], %d %f %[^\n]\n", &temp_id, temp_name, &temp_price, &temp_weight, temp_date) != EOF){
		root = inserttnode(root, temp_id, temp_name, temp_price, temp_weight, temp_date);
	}
	return root;
}

void save_data_avl(struct tnode *root, FILE *fp){
	if(root == NULL){
		return;
	}
	save_data_avl(root->left, fp);
	fprintf(fp, "%d %s, %d %.5f %s\n", root->id, root->name, root->price, root->weight, root->date);
	save_data_avl(root->right, fp);
}


int menu_opt(){
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
	struct tnode *root = NULL;
	int id, price, opt;
	char name[20], date[20];
	float weight;
	
	FILE *fp;
	fp = fopen("data.txt", "r");
	if(fp != NULL){
		root = load_data_avl(root, fp);
		fclose(fp);
	}else{
		fclose(fp);
	}

	while(1){
		opt = menu_opt();
			switch(opt){
				int found = 0;
				case 1:
					printf("ID item: "); scanf("%d", &id);
					printf("Item name: "); scanf(" %[^\n]", name);
					printf("Item price : "); scanf("%d", &price);
					printf("Item weight : "); scanf("%f", &weight);
					printf("Date added (MM/DD/YY): "); scanf(" %[^\n]", &date);
					printf("\n");
					root = inserttnode(root, id, name, price, weight, date);
					break;
				case 2:
					printf("Type item's ID : "); scanf("%d", &id);
					found = 0;
					root = delete_tnode(root, id, &found);
					if(found == 0){
						printf("Data not found !!!\n");
					}else{
						printf("Data deleted successfully !!!\n");
					}
					break;
				case 3:
					printPreOrder(root);
					break;
				case 4:
					printf("Type item's ID : "); scanf("%d", &id);
					found = 0;
					search_tnode(root, id, &found);
					if(found == 0){
						printf("Data not found !!!\n");
					}
					break;
				case 5:
					printf("Insert item's ID: "); scanf("%d", &id);
					found = 0;
					root = update_tnode(root, id, &found);
					if(found == 0){
						printf("Data not found !!!\n");
					}
					break;
				case 6:
					fp = fopen("data.txt", "w");
					save_data_avl(root, fp);
					fclose(fp);
					return 0;
				default:
					printf("Wrong input !!!\n");
			}
	}

}
