/**************************************************************************************************************************************************************
*Title		: main function(Driver function)
*Description	: This function is used as the driver function for the all the functions
***************************************************************************************************************************************************************/
#include "apc.h"

int main(int argc, char *argv[])
{
	//function call for validating CLA
	int res = validate_CLA(argc, argv);
	if (res == FAILURE) {
		printf("ERROR : Failed to validate CLA\n");
		return FAILURE;
	} else {
		printf("Validation of CLA successful.\n\n");
	}
	
	/* Declare the pointers */
	//Dlist *head1, *tail1, *head2, *tail2, *headR;
	char option, operator;

	//extracting operator from argv[2]
	operator = argv[2][0];
	//printf("Operator is = %c\n\n",operator);

	printf("Number1 (LIST 1 ) ==>  ");
	//convert argv[1] str to list
	int ret = convert_str_argv1_to_list(argv); 

	if(ret == FAILURE) {
		printf("ERROR : Failed to convert str to list of argv[1]\n");
		return FAILURE;
	}
	//printf("Successfully converted str_argv1 to list successfully.\n\n");

	printf("Number 2 (LIST 2 )==>  ");
	//convert argv[3] str to list
	int val = convert_str_argv3_to_list(argv); 

	if(val == FAILURE) {
		printf("ERROR : Failed to convert str to list of argv[3]\n");
		return FAILURE;
	}

	int result = FAILURE;

	//printf("Successfully converted str_argv3 to list successfully.\n");
	
	/* Code for reading the inputs */

	/* Function for extracting the operator */

	switch (operator)
	{
		case '+':
			/* call the function to perform the addition operation */
			printf("ADDITION function is called\n");
			result = add_signed(&head1, &tail1, sign1, &head2, &tail2, sign2, &headR, &tailR, &signR);
			break;

		case '-':	
			/* call the function to perform the subtraction operation */

			printf("SUBTRACTION function is called\n");
			result = sub_signed(&head1, &tail1, sign1, &head2, &tail2, sign2, &headR, &tailR, &signR);
			break;

		case '*':	
			/* call the function to perform the multiplication operation */
			//for multiplication operator -> * we need to give "*" or \* in CLA of argv[2]
			printf("Multiplication function is called\n");
			result = mul_signed(&head1, &tail1, sign1, &head2, &tail2, sign2, &headR, &tailR, &signR);
			break;

		case '/':	
			/* call the function to perform the division operation */
			printf("Division function is called\n");
			if (head2 && head2->data == 0 && head2->next == NULL) {
                printf("ERROR : division by 0 is not possible\n");
                return FAILURE;
            }
            result = div_signed(&head1, &tail1, sign1, &head2, &tail2, sign2, &headR, &tailR, &signR);
			break;

		default:
			printf("Invalid Input:-> Try again...\n");
			return FAILURE;
	}

	if (result == FAILURE) {
        printf("ERROR : Operation failed\n");
        return FAILURE;
    }

    printf("RESULT ==> ");
    print_list(headR,signR);

    //clear
    delete_dll(&head1, &tail1);
    delete_dll(&head2, &tail2);
    delete_dll(&headR, &tailR);
	
	return 0;
}

