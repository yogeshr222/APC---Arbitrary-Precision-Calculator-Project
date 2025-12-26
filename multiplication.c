/*******************************************************************************************************************************************************************
*Title			: Multiplication
*Description		: This function performs multiplication of two given large numbers and store the result in the resultant list.
*Prototype		: int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
*Input Parameters	: head1: Pointer to the first node of the first double linked list.
			: tail1: Pointer to the last node of the first double linked list.
			: head2: Pointer to the first node of the second double linked list.
			: tail2: Pointer to the last node of the second double linked list.
			: headR: Pointer to the first node of the resultant double linked list.
*Output			: Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/
#include "apc.h"

//function call for multiplication if numbers contains sign
int mul_signed(Dlist **head1, Dlist **tail1, int sign1, Dlist **head2, Dlist **tail2, int sign2, Dlist **headR, Dlist **tailR, int *signR) {

    multiplication(head1, tail1, head2, tail2, headR, tailR);

    *signR = (sign1 == sign2) ? +1 : -1;

    if (*headR && (*headR)->data == 0 && (*headR)->next == NULL) 
		*signR = +1;

    return SUCCESS;
}

int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
	/* Definition goes here */
	//printf("Multiplication function is called\n");

	//declare ptrs for traversal
	//to start from tail -> lsb
	Dlist *temp2 = *tail2;
	Dlist *temp1 = NULL;

	//take two temporary result list and 1 final result list
	Dlist *tempHead1 = NULL, *tempTail1 = NULL;   //to store res1
	Dlist *tempHead2 = NULL, *tempTail2 = NULL;   //to store res2

	//take final result list as headR and tailR
	*headR = NULL , *tailR = NULL;
	
	int carry , count=0;  //count is to add extra zero's


	//1. traverse through each digits of num2 from lsb
	while (temp2 != NULL) 
	{
		carry = 0;

		//step 2 : Multiply each digit of num1 from tail side with current digit of num2
		temp1 = *tail1;

		//clear the previous temporary  result1
		delete_dll(&tempHead1, &tempTail1);

		while(temp1 != NULL) 
		{
			int product = (temp1->data * temp2->data) + carry;
			insert_first_dll(&tempHead1, &tempTail1, product % 10);
			carry = product / 10;
			
			temp1 = temp1->prev;
		}

		if(carry)
			insert_first_dll(&tempHead1, &tempTail1, carry);

		//step3 : to add extra zeros 
		for(int i = 0; i < count ; i++){
			insert_last_in_dll(&tempHead1, &tempTail1, 0);
		}

		//step4 : add temp result to final result
		addition(&tempHead1, &tempTail1, headR, tailR, &tempHead2, &tempTail2);

		//step5 : copy temp2Head to final list
		delete_dll(headR, tailR);
		*headR = tempHead2;
		*tailR = tempTail2;

		tempHead2 = tempTail2 = NULL;


		//step6 :goto next digit of num2
		temp2 = temp2->prev;
		count++;

	}

	return SUCCESS;
	
}


