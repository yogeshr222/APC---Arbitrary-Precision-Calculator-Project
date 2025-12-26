#include "apc.h"

Dlist *head1 = NULL,  *tail1 = NULL;
Dlist *head2 = NULL,  *tail2 = NULL;
Dlist *headR = NULL, *tailR = NULL;

//signs
int sign1 = 1;
int sign2 = 1;
int signR = 1;

int validate_CLA(int argc, char *argv[]) {

	//chaeck if exactly 4 arguments from the CLA
	if(argc != 4){
		printf("ERROR : CLA argument count should be 4 not %d\n",argc);
		printf("Give input like this -> \n\t./apc.exe number1 operator(+ / - / * or /) number2\n");
		return FAILURE;
	}

	//for signs of num1 and num2
    for (int k = 1; k <= 3; k += 2) {
        char *s = argv[k];

        int i = 0;

        if (s[0] == '+' || s[0] == '-') 
			i++;
		
		if (s[i] == '\0') {
			printf("ERROR : Number argument empty\n");
			return FAILURE;
		}
			
        for (; s[i] != '\0'; i++) {

			//check if all are digits for num1 and num2
            if (!isdigit((unsigned char)s[i])) {

                printf("ERROR : Argument %d must be numbers (digits only after optional sign)\n", k);
                return FAILURE;
            }
        }
    	
	}
	
	//verify 3rd CLA is must be operator +,-,*,/
	if(( strcmp(argv[2],"+") !=0 ) && ( strcmp(argv[2],"-")!=0 ) &&
		( strcmp(argv[2],"*") !=0 )  && ( strcmp(argv[2],"/") !=0 ) ){

		printf("ERROR : Invalid Operator\nOperator must be '+' or '-' or '*' or '/'\n");
		return FAILURE;
	}
	return SUCCESS;
}

//convert num1 from CLA (string to int)
int convert_str_argv1_to_list(char *argv[]) { 
	int  i = 0;
	sign1 = 1;

	if(argv[1][0] == '+' || argv[1][0] == '-') {
		if(argv[1][0] == '-')
			sign1 = -1;
		i++;
	}
	//fetch char by char
	for(; argv[1][i] != '\0'; i++) {

		//convert char to int
		int var = argv[1][i] - '0';

		//insert into the list -> using insert last operation
		int result = insert_last_in_dll(&head1, &tail1, var);
		
		if(result == FAILURE) {
			printf("Failed insert last operation for argv[1] at %d\n",i+1);
			return FAILURE;
		}
	}
	
	print_list(head1,sign1);

	return SUCCESS;
}

int convert_str_argv3_to_list(char *argv[]) {
	int  i = 0;
	sign2 = 1;

	if(argv[3][0] == '+' || argv[3][0] == '-') {
		if(argv[3][0] == '-')
			sign2 = -1;
		i++;
	}
	//fetch char by char
	for(; argv[3][i] != '\0'; i++) {

		//convert char to int
		int var = argv[3][i] - '0';

		//insert into the list -> using insert last operation
		int result = insert_last_in_dll(&head2, &tail2, var);
		
		if(result == FAILURE) {
			printf("Failed insert last operation for argv[3] at %d\n",i+1);
			return FAILURE;
		}
	}
    //print the list
	print_list(head2, sign2);
	return SUCCESS;
}

int insert_last_in_dll(Dlist **head, Dlist **tail, int data) {
	
    //create node
    Dlist *newnode = malloc(sizeof(Dlist));
    if(!newnode){
        printf("Memory allocation failed\n");
        return FAILURE;
    }
    newnode->data = data;
    newnode->next = NULL;
    newnode->prev = NULL;
    
    //check if the list is empty or not
    if(*head == NULL){
        *head = *tail = newnode;
    }
    
    else{
        Dlist *temp = *tail;
        temp->next = newnode;
        newnode->prev = temp;
        *tail = newnode;
    }
    return SUCCESS;

}

int insert_first_dll(Dlist **headR, Dlist **tailR, int data) {
	//create a node
	Dlist *newnode = (Dlist*)malloc(sizeof(Dlist));

	if(!newnode){
		printf("Memory allocation failed\n");
		return FAILURE;
	}
	newnode->data = data;
	newnode->next = newnode->prev = NULL;

	//check if the list is empty or not
	if(*headR == NULL) {
		*tailR = *headR = newnode;

	} else {
		Dlist *temp = *headR;
		newnode->next = *headR;
		temp->prev = newnode;
		*headR = newnode;
	}
	return SUCCESS;
}

void print_list(Dlist *head, int sign)
{
    //printf("Head -> ");

    if (head == NULL) {
        //printf("NULL <- Tail\n");
		printf("0\n");
        return;
    }

    // print minus sign ONCE at the beginning if negative 
    if (sign == -1)
        printf("-");

    Dlist *temp = head;
    while (temp != NULL)
    {
        printf("%d", temp->data);

        temp = temp->next;
    }

    //printf(" <- Tail\n");
	printf("\n");
}


int copy_dll(Dlist **src_head, Dlist **src_tail, Dlist **dest_head, Dlist **dest_tail) 
{
	//first clear the destination list
	delete_dll(dest_head, dest_tail);

	if(*src_head == NULL) {
		return FAILURE;   //list is empty
	}

	Dlist *temp = *src_head;
	while(temp != NULL) {
		insert_last_in_dll(dest_head, dest_tail, temp->data);
		temp = temp->next;
	}
	return SUCCESS;
}

int delete_dll(Dlist **headR, Dlist **tailR) {

	if(*headR == NULL) {
		return FAILURE;
	}

	Dlist *temp = *headR, *next;

	while(temp != NULL) {
		next = temp->next;
		free(temp);
		temp = next;
	}

	*headR = *tailR = NULL;
	return SUCCESS;
}

int compare_list(Dlist *head1, Dlist *head2) {

	int len1 = 0, len2 = 0;
	Dlist *temp1 = head1, *temp2 = head2;

	while(temp1){
		len1++;
		temp1 = temp1->next;
	}
	while(temp2) {
		len2++;
		temp2 = temp2->next;
	}

	//compare the lens
	if(len1 > len2)
		return 1;
	if(len2 > len1)
		return -1;

	//if len1 == len2 compare digit by digit from MSB
	temp1 = head1;
	temp2 = head2;

	while(temp1 && temp2){
		if(temp1->data > temp2->data)
			 return 1;
		if(temp2->data > temp1->data) 
			return -1;

		temp1 = temp1->next;
		temp2 = temp2->next;
	}

	//if num1 = num2
	return 0;

}