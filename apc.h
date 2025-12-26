#ifndef APC_H
#define APC_H
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include<stdlib.h>
#define SUCCESS 0
#define FAILURE -1

typedef int data_t;
typedef struct node
{
	struct node *prev;
	data_t data;
	struct node *next;
}Dlist;

extern Dlist *head1, *tail1, *head2, *tail2, *headR, *tailR;

//global signs
extern int sign1;
extern int sign2;
extern int signR;

/* Include the prototypes here */

int validate_CLA(int argc, char *argv[]);

int convert_str_argv1_to_list(char *argv[]);

int convert_str_argv3_to_list(char *argv[]);

int insert_last_in_dll(Dlist **head, Dlist **tail, int data);

int insert_first_dll(Dlist **headR, Dlist **tailR, int data);

void print_list(Dlist *head, int sign);

int copy_dll(Dlist **signRc_head, Dlist **signRc_tail, Dlist **dest_head, Dlist **dest_tail);

int delete_dll(Dlist **headR, Dlist **tailR);

int compare_list(Dlist *head1, Dlist *head2);

//for unsigned function prototype
int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);

int subtraction(char *argv[],Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);

int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);

int division(char*argv[], Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);

//for signed functions prototpe

int add_signed(Dlist **head1, Dlist **tail1,int sign1, Dlist **head2, Dlist **tail2,int sign2, Dlist **headR, Dlist **tailR, int *signR);

int sub_signed(Dlist **head1, Dlist **tail1,int sign1, Dlist **head2, Dlist **tail2,int sign2, Dlist **headR, Dlist **tailR, int *signR);

int mul_signed(Dlist **head1, Dlist **tail1,int sign1, Dlist **head2, Dlist **tail2,int sign2, Dlist **headR, Dlist **tailR, int *signR);

int div_signed(Dlist **head1, Dlist **tail1,int sign1, Dlist **head2, Dlist **tail2,int sign2, Dlist **headR, Dlist **tailR, int *signR);

#endif
