/*******************************************************************************************************************************************************************
*Title			: Division
*Description		: This function performs division of two given large numbers and store the result in the resultant list.
*Prototype		: int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
*Input Parameters	: head1: Pointer to the first node of the first double linked list.
			: tail1: Pointer to the last node of the first double linked list.
			: head2: Pointer to the first node of the second double linked list.
			: tail2: Pointer to the last node of the second double linked list.
			: headR: Pointer to the first node of the resultant double linked list.
*Output			: Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/
#include "apc.h"

//function call for division if numbers contains sign
int div_signed(Dlist **head1, Dlist **tail1, int sign1, Dlist **head2, Dlist **tail2, int sign2, Dlist **headR, Dlist **tailR, int *signR) 
{
    if (*head2 == NULL) {
        printf("ERROR : division by 0 is not possible\n");
        return FAILURE;
    }
    division(NULL, head1, tail1, head2, tail2, headR, tailR);

    *signR = (sign1 == sign2) ? +1 : -1;

    if (*headR && (*headR)->data == 0 && (*headR)->next == NULL) 
		*signR = +1;

    return SUCCESS;
}

int division(char*argv[], Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    // using repeated subtraction -> division  
    if (*head2 == NULL) {
        printf("ERROR : division by 0 is not possible\n");
        return FAILURE;
    }

    delete_dll(headR, tailR);

    // if head1 < head2 -> quotient 0 
    if (compare_list(*head1, *head2) < 0) {
        insert_first_dll(headR, tailR, 0);
        return SUCCESS;
    }

    Dlist *countHead = NULL, *countTail = NULL;
    insert_first_dll(&countHead, &countTail, 0);

    Dlist *oneHead = NULL, *oneTail = NULL;
    insert_first_dll(&oneHead, &oneTail , 1);

    Dlist *tempResH = NULL, *tempResT = NULL;
    Dlist *countResH = NULL, *countResT = NULL;

    // make a copy to avoid corruption 
    Dlist *remH = NULL, *remT = NULL;
    copy_dll(head1, tail1, &remH, &remT);

    while (compare_list(remH, *head2) >= 0) {
        //subtract rem - head2 -> tempResH 
        subtraction(NULL, &remH, &remT, head2, tail2, &tempResH, &tempResT);

        // move tempRes to rem 
        delete_dll(&remH, &remT);

        remH = tempResH; 
        remT = tempResT;

        tempResH = tempResT = NULL;

        // count = count + 1 
        addition(&countHead, &countTail, &oneHead, &oneTail, &countResH, &countResT);

        delete_dll(&countHead, &countTail);

        countHead = countResH; 
        countTail = countResT;

        countResH = countResT = NULL;
    }

    *headR = countHead; *tailR = countTail;

    delete_dll(&remH, &remT);
    delete_dll(&oneHead, &oneTail);

    return SUCCESS;
}


