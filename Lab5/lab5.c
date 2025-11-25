#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define NODE struct node

int counter = 0;
NODE *head;

struct node
{
	char first_name[20];
	char last_name[20];
	int age;
	NODE *next;
};

void insert()
{
	char first[20];
	char last[20];
	int age;

	NODE *p;
	p = (NODE *)malloc(sizeof(NODE));

	printf("Enter a first name. \n");
	scanf("%s", first);
	printf("Enter a last name. \n");
	scanf("%s", last);
	printf("Enter an age. \n");
	scanf("%d", &age);

	if (check_duplicate(first, last) == 0)
	{
		return;
	}

	strcpy(p -> first_name, first);
	strcpy(p -> last_name, last);
	p -> age = age;
	p -> next = head;
	head = p;
	counter++;
}

int list()
{
	NODE *p;
	p = head;

	while (p != NULL)
	{
		printf("%s %s %d \n", p -> first_name, p -> last_name, p -> age);
		p = p -> next;
	}
}

int list_ages()
{
	NODE *p;
	p = head;
	int i;
	int input2;

	printf("What age would you like to search? \n");
	scanf("%d", &input2);

	while (p != NULL)
	{
		if (input2 == p -> age)
		{
			printf("%s %s, %d \n", p -> first_name, p -> last_name, p -> age);
		}
		p = p -> next;
	}
}

int remove_input()
{
	NODE *p;
	NODE *q;
	p = head;
	q = head;
	int first_check;
	int last_check;
	char first[20];
	char last[20];

	printf("Enter the first name of the person you'd like to remove. \n");
	scanf("%s", first);
	printf("Enter the last name of the person you'd like to remove. \n");
	scanf("%s", last);

	while (p != NULL)
	{
		first_check = strcmp(first, p -> first_name);
		last_check = strcmp(last, p -> last_name);

		if (first_check == 0 && last_check == 0)
                {
			if (p == head)
			{
				head = p -> next;
			}

			else
			{
				q -> next = p -> next;
			}

			free(p);
			counter--;
			break;
                }
		q = p;
		p = p -> next;
	}
}


int check_duplicate(char *first, char *last)
{
	NODE *p;
	p = head;
	int i;

	while (p != NULL)
	{
		int first_check = strcmp(first, p -> first_name);
		int last_check = strcmp(last, p -> last_name);

		if (first_check == 0 && last_check == 0)
		{
			printf("You have already entered that person. \n");
			return 0;
		}
		p = p -> next;
	}
	return 1;
}


int main()
{
        int input = 1;

        while (input != 0)
        {
                printf("Enter '1' to add to the spreadsheet. \n");
                printf("Enter '2' to show the list alphabetically by last name. \n");
                printf("Enter '3' to show the list of people at a given age. \n");
		printf("Enter '4' to remove someone from the spreadsheet. \n");
		printf("Enter '0' to quit. \n");
		scanf("%d", &input);

                if (input == 1)
		{
                        insert();
                }
                if (input == 2)
                {
                        list();
                }
                if (input == 3)
                {
                        list_ages();
                }
		if (input == 4)
		{
			remove_input();
		}
        }
}

