/*******************************************************************************************************************************************************************
*Title			: Subtraction
*Description		: This function performs subtraction of two given large numbers and store the result in the resultant list.
*Prototype		: int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
*Input Parameters	: head1: Pointer to the first node of the first double linked list.
			: tail1: Pointer to the last node of the first double linked list.
			: head2: Pointer to the first node of the second double linked list.
			: tail2: Pointer to the last node of the second double linked list.
			: headR: Pointer to the first node of the resultant double linked list.
*Output			: Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/
#include "apc.h"

int sub_signed(Dlist **head1, Dlist **tail1, int sign1, Dlist **head2, Dlist **tail2, int sign2, Dlist **headR, Dlist **tailR, int *signR) {
    // a - b = a + (-b) 
    return add_signed(head1, tail1, sign1, head2, tail2, -sign2, headR, tailR, signR);
}

int subtraction(char *argv[],Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
	//Definition goes here 
	//take two pointers t1 for tail1, t2 for tail2
	//printf("Subtraction function called\n");

	Dlist *temp1 = *tail1;
	Dlist *temp2 = *tail2;
	int borrow = 0;
	
	delete_dll(headR, tailR);

	while(temp1 != NULL || temp2 != NULL) {

		int val1 = 0, val2 = 0;

		if(temp1 != NULL) {
			val1 = temp1->data;
			temp1 = temp1->prev;
		}

		if(temp2 != NULL) {
			val2 = temp2->data;
			temp2 = temp2->prev;
		}

		int diff = val1 - val2 - borrow;

		if(diff < 0) {
			diff = diff + 10;
			borrow = 1;
		}
		else {
			borrow = 0;
		}

		insert_first_dll(headR, tailR, diff);

	}

	//to remove extra zeros
	while ((*headR != NULL) && (*headR)->data == 0 && (*headR)->next != NULL)
    {
        Dlist *temp = *headR;
        *headR = (*headR)->next;
        (*headR)->prev = NULL;
        free(temp);
    }

	return SUCCESS;
}








