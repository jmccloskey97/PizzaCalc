#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "string.h"
#include "stdbool.h"

#define PI 3.14159265358979323846

#Creates a struct for the node which includes a char array for the PizzaName and pizza-per-dollar
struct node
{
	char type[64];
	float fin;
	struct node* next;
};

#Bubble sort that sorts each pizza in descending order of pizza-per-dollar
void sort(struct node *head)
{
	int flag;
	int count;

	struct node *pointer;
	struct node *start = NULL;

	pointer = head;

	if(pointer == NULL)
	{
		return;
	}

	do
	{
		flag = 0;
		pointer = head;
	
		while(pointer->next != start)
		{
			if(pointer->fin < pointer->next->fin || (pointer->fin == pointer->next->fin && strcmp(pointer->type, pointer->next->type) > 0) && pointer->fin != 0)
			{
				float temval = pointer->fin;
				char temtype[64];
				strcpy(temtype, pointer->type);

				pointer->fin = pointer->next->fin;
				strcpy(pointer->type, pointer->next->type);

				pointer->next->fin = temval;
				strcpy(pointer->next->type,temtype);

				flag = 1;
			}
			pointer = pointer->next;
		}
		start = pointer;
	}
	while(flag);
	

}

int main(int argc, char *argv[])
{
	int c = 0;
	float d = 0;
	float co = 0;
	char read;

	struct node *head, *anchor;

	char line[64];
	FILE *fr;
	fr = fopen(argv[1], "r"); //error

	if(fscanf(fr, "%s", line) == EOF) //error
	{
		printf("PIZZA FILE IS EMPTY");
		return EXIT_SUCCESS;
	}

	if(strcmp(line, "DONE") == 0)
	{
		printf("PIZZA FILE IS EMPTY");
		return EXIT_SUCCESS;
	}
	else
	{

	head = (struct node*)malloc(sizeof(struct node));

	strcpy(head->type, line);
	fscanf(fr, "%f", &d);
	fscanf(fr, "%f", &co);
	head->fin = (((PI/4.0)*(d*d))/co);
	head->next = NULL;

	struct node *prev = head;

	fscanf(fr, "%s", line); //error

	while(strcmp(line, "DONE") != 0)
	{
		struct node *current = (struct node*)malloc(sizeof(struct node));

		fscanf(fr, "%f", &d);
		fscanf(fr, "%f", &co);
		strcpy(current->type, line);
		if(co != 0.0)
		{
			current->fin = (((PI/4.0)*(d*d))/co);
		}
		else
		{
			current->fin = 0.0;
		}
		current->next = NULL;
		prev->next = current;
		prev = current;
		fscanf(fr, "%s", line); //error
		
	}

	sort(head);

	prev = head;

	while(head != NULL)
	{
		printf("%s ", head->type);
		printf("%f\n",head->fin);
		head = head->next;
		free (prev);
		prev = head;
	} 
	}

	fclose(fr);
	return EXIT_SUCCESS;

}

