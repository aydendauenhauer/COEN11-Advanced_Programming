#include <stdio.h>
#include <string.h>
#define NROWS 10
#define NCOLS 20

int counter = 0;
char first_names[NROWS][NCOLS];
char last_names[NROWS][NCOLS];
int ages[NROWS];

void insert()
{
	char first[NROWS];
	char last[NROWS];
	int age;
	int i;
	int first_check;
	int last_check;

	if (counter < 10)
	{
		printf("Enter a first name \n");
		scanf("%s", first);
		printf("Enter a last name \n");
		scanf("%s", last);
		printf("Enter an age \n");
		scanf("%d", &age);
		
		for (i = 0; i < NROWS; i++)
		{
			first_check = strcmp(first, first_names[i]);
			last_check = strcmp(last, last_names[i]);

			if (first_check == 0 && last_check == 0)
			{
				break;
			}
		}
		
		if (first_check == 0 && last_check == 0)
		{
			printf("You have already entered that person. \n");
		}

		else
		{
			strcpy(first_names[counter], first);
			strcpy(last_names[counter], last);
			ages[counter] = age;
			counter++;

		}

	}

	else
	{
		printf("You have reached the maximum limit \n");
	}
}

int list()
{
	int i;
	for (i = 0; i < counter; i++)
	{
		printf("%s %s %d \n", first_names[i], last_names[i], ages[i]);
	}
}

int list_ages()
{
	int i;
	int input2;
	printf("What age would you like to search? \n");
	scanf("%d", &input2);

	for (i = 0; i < NROWS; i++)
	{
		if (input2 == ages[i])
		{
			printf("%s %s, %d \n", first_names[i], last_names[i], ages[i]);
		}
	}
}

int main()
{
        int input = 1;

        while (input != 0)
        {
                printf("Enter '1' to add to the spreadsheet. \n");
                printf("Enter '2' to show the list from oldest to newest. \n");
                printf("Enter '3' to show the list of people at a given age. \n");
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
        }
}

