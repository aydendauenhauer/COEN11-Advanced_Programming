#include <stdio.h>
#include <string.h>
#define NROWS 10
#define NCOLS 20

int counter = 0;

union Data
{
        char school[30];
        int retirement;
        float salary;
};

struct person
{
	char first_name[NCOLS];
	char last_name[NCOLS];
	int age;
	union Data data;
};

struct person info[NROWS];

void insert()
{
	struct person *p;
	p = info;
	char first[NCOLS];
	char last[NCOLS];
	int age;
	int i;
	int first_check;
	int last_check;

	if (counter < 10)
	{
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

		for (i = 0; i < counter; i++, p++);

		for (i = 0; i < counter; i++)
		{
			if (strcmp((p-1) -> last_name, last) > 0)
			{
                               	strcpy(p -> last_name, (p-1) -> last_name);
				strcpy(p -> first_name, (p-1) -> first_name);
				p -> age = (p-1) -> age;
                              	p--;
			}
		}
		strcpy(p -> first_name, first);
                strcpy(p -> last_name, last);
                p -> age = age;

		if (age <= 18)
                {
                        printf("What school do you go to? \n");
                        scanf("%s", p -> data.school);
                }

                if (age > 18 && age < 65)
                {
                        printf("What is your salary? \n");
                        scanf("%f", &p -> data.salary);
                }

                if (age >= 65)
                {
                        printf("How many years have you been retired? \n");
                        scanf("%d", &p -> data.retirement);
                }

                counter++;
	}

	else
	{
		printf("You have reached the maximum limit. \n");
	}
}

int list()
{
	struct person *p;
	p = info;
	int i;

	for (i = 0; i < counter; i++, p++)
	{
		if (p -> age <= 18)
		{
			printf("%s %s, age %d, goes to %s \n", p -> first_name, p -> last_name, p -> age, p -> data.school);
		}

		if ((p -> age > 18) && (p -> age < 65))
		{
			printf("%s %s, age %d, has a salary of %f \n", p -> first_name, p -> last_name, p -> age, p -> data.salary);
		}

		if (p -> age >= 65)
		{
			printf("%s %s, age %d, has been retired for %d years \n", p -> first_name, p -> last_name, p -> age, p -> data.retirement);
		}
	}
}

int list_ages()
{
	struct person *p;
	p = info;
	int i;
	int input2;

	printf("What age would you like to search? \n");
	scanf("%d", &input2);

	for (i = 0; i < counter; i++, p++)
	{
		if (input2 == p -> age)
		{
			if (p -> age <= 18)
                	{
                        	printf("%s %s, age %d, goes to %s \n", p -> first_name, p -> last_name, p -> age, p -> data.school);
                	}

                	if ((p -> age > 18) && (p -> age < 65))
                	{
                        	printf("%s %s, age %d, has a salary of %f \n", p -> first_name, p -> last_name, p -> age, p -> data.salary);
                	}

                	if (p -> age >= 65)
                	{
                        	printf("%s %s, age %d, has been retired for %d years \n", p -> first_name, p -> last_name, p -> age, p -> data.retirement);
                	}
		}
	}
}

int remove_name()
{
	struct person *p;
	int i;
	int j;
	int first_check;
	int last_check;
	char first[NCOLS];
	char last[NCOLS];

	printf("Enter the first name of the person you'd like to remove. \n");
	scanf("%s", first);
	printf("Enter the last name of the person you'd like to remove. \n");
	scanf("%s", last);
	p = info;

	for (i = 0; i < NROWS; i++, p++)
	{
		first_check = strcmp(first, p -> first_name);
		last_check = strcmp(last, p -> last_name);

		if (first_check == 0 && last_check == 0)
                {
			j = i;
                        for (; j < counter; j++, p++) 
			{
				info[j] = info[j + 1];
			}
			counter--;
			break;
                }
	}
}

int remove_age()
{
        struct person *p;
        int i = 0;
	int j;
        int age_remove;

        printf("Enter the age of the people you'd like to remove. \n");
        scanf("%d", &age_remove);
        p = info;

        while (i < counter)
        {
                if (age_remove == p -> age)
                {
			j = i;
                        for (; j < counter; j++, p++)
                        {
				info[j] = info[j + 1];
                        }
			i = 0;
			p = info;
                        counter--;
			printf("%d\n", counter);
                }

		else
		{
			i++;
			p++;
		}
        }
}

int check_duplicate(char *first, char *last)
{
	struct person *p;
	p = info;
	int i;

	for (i = 0; i < counter; i++, p++)
	{
		int first_check = strcmp(first, p -> first_name);
		int last_check = strcmp(last, p -> last_name);

		if (first_check == 0 && last_check == 0)
		{
			printf("You have already entered that person. \n");
			return 0;
		}
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
		printf("Enter '4' to remove someone from the spreadsheet by name. \n");
		printf("Enter '5' to remove someone from the spreadsheet by age. \n");
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
			remove_name();
		}
		if (input == 5)
		{
			remove_age();
		}
        }
}

