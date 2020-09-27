#include<stdio.h>
#include<stdlib.h>

struct list{
	int count;
	struct node *head;
};

struct node{
	char *command;
	struct node *next;
};

struct list history;

void insert (char *cmd);
void show ();

int main (){

	history.count = 0;
	history.head = NULL;

	char *cmd = (char *)malloc(100);
	scanf(" %[^\n]", cmd);

	insert(cmd);
	// insert("1. ls");
	// insert("2. cat");
	// insert("3. grep");
	// insert("4. cd");
	// insert("5. ls");
	// insert("6. cat");
	// insert("7. grep");
	// insert("8. cd");
	// insert("9. ls");
	// insert("10. cat");
	// insert("11. grep");
	// insert("12. cd");

	show();

	return 0;
}

void insert (char *cmd){
	
	struct node* temp = (struct node*)malloc(sizeof(struct node));
	temp->command = cmd;
	
	if(history.head == NULL){
		temp->next = NULL;
		history.head = temp;
		history.count = 1;
		return;
	}

	temp->next = history.head;
	history.head = temp;

	if(history.count == 10){
		// printf("\n%s:\n", cmd);
		struct node* temp = history.head, temp1;
		
		for(int i=0; i<9; i++){
			temp = temp->next;
			// printf("test\n");
		}
		temp->next = NULL;
		// show();
	}
	else{
		history.count += 1;
	}
	
}

void show (){

	struct node* temp = history.head;
	while(temp != NULL){

		printf("%s\n", temp->command);
		temp = temp->next;
	}
}