/*******************************************************************************************************************************************************************
*Title			: Addition
*Description		: This function performs addition of two given large numbers and store the result in the resultant list.
*Prototype		: int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
*Input Parameters	: head1: Pointer to the first node of the first double linked list.
			: tail1: Pointer to the last node of the first double linked list.
			: head2: Pointer to the first node of the second double linked list.
			: tail2: Pointer to the last node of the second double linked list.
			: headR: Pointer to the first node of the resultant double linked list.
*Output			: Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/
#include "apc.h"

//add function definition if the numbers contains sign
int add_signed(Dlist **head1, Dlist **tail1, int sign1, Dlist **head2, Dlist **tail2, int sign2, Dlist **headR, Dlist **tailR, int *signR) {
    //signs equal -> magnitude add 
    if (sign1 == sign2) {
        addition(head1, tail1, head2, tail2, headR, tailR);

        *signR = sign1;

        if (*headR && (*headR)->data == 0 && (*headR)->next == NULL) 
			*signR = +1;

        return SUCCESS;
    }
    // signs differ -> subtract larger - smaller 
    int cmp = compare_list(*head1, *head2);
    if (cmp == 0) {

        delete_dll(headR, tailR);

        insert_first_dll(headR, tailR, 0);

        *signR = +1;

        return SUCCESS;

    } else if (cmp > 0) {

        subtraction(NULL, head1, tail1, head2, tail2, headR, tailR);

        *signR = sign1;
		
    } else {
        subtraction(NULL, head2, tail2, head1, tail1, headR, tailR);
        *signR = sign2;
	}
    if (*headR && (*headR)->data == 0 && (*headR)->next == NULL) 
		*signR = +1;
    return SUCCESS;
}

int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
	/* Definition goes here */
	
	//take two pointers temp1 for tail1, temp2 for tail2
	//printf("\nAdd function called\n");

	Dlist *temp1 = *tail1;
	Dlist *temp2 = *tail2;
	int carry = 0;

	while (temp1 != NULL || temp2 != NULL) {

		int val1 = 0, val2 = 0;

		if (temp1 != NULL) {
			val1 = temp1->data;
			temp1 = temp1->prev;
		}

		if (temp2 != NULL) {
			val2 = temp2->data;
			temp2 = temp2->prev;
		}

		int sum = 0;
		sum = val1 + val2 + carry;
		carry = sum/10;
		int digit = sum % 10;

		//perform insert first operation
		insert_first_dll(headR, tailR, digit);
	}
	if(carry == 1) {
		insert_first_dll(headR, tailR, carry);
	}
	return SUCCESS;
}


