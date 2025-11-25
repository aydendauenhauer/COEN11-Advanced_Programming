#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define NODE struct node
#define LIST struct list

struct list
{
	NODE *head;
	NODE *tail;
};

struct node
{
	char first_name[20];
	char last_name[20];
	int age;
	NODE *next;
	NODE *prev;
};

LIST List[3] = {{NULL,NULL},{NULL,NULL},{NULL,NULL}};

pthread_mutex_t mutex;

void insert(char first[20], char last[20], int age)
{
	NODE *p;
	p = (NODE *)malloc(sizeof(NODE));

	if (check_duplicate(first, last) == 0)
	{
		return;
	}

	strcpy(p -> first_name, first);
	strcpy(p -> last_name, last);
	p -> age = age;
	p -> next = NULL;	

	if (age <= 18)
	{
		if (List[0].head == NULL)
		{
			pthread_mutex_lock(&mutex);
			List[0].head = List[0].tail = p;
			pthread_mutex_unlock(&mutex);
		}

		else
		{
			pthread_mutex_lock(&mutex);
			List[0].tail -> next = p;
			p -> prev = List[0].tail;
			List[0].tail = List[0].tail -> next;
			pthread_mutex_unlock(&mutex);
		}
	}

	if (age > 18 && age < 65)
	{
		if (List[1].head == NULL)
		{
			pthread_mutex_lock(&mutex);
			List[1].head = List[1].tail = p;
			pthread_mutex_unlock(&mutex);
		}

		else
		{
			pthread_mutex_lock(&mutex);
			List[1].tail -> next = p;
			p -> prev = List[1].tail;
			List[1].tail = List[1].tail -> next;
			pthread_mutex_unlock(&mutex);
		}
	}

	if (age >= 65)
	{
		if (List[2].head == NULL)
		{
			pthread_mutex_lock(&mutex);
			List[2].head = List[2].tail = p;
			pthread_mutex_unlock(&mutex);
		}

		else
		{
			pthread_mutex_lock(&mutex);
			List[2].tail -> next = p;
			p -> prev = List[2].tail;
			List[2].tail = List[2].tail -> next;
			pthread_mutex_unlock(&mutex);
		}
	}
}

void list()
{
	int i;
	NODE *p;

	for (i = 0; i < 3; i++)
        {
                p = List[i].head;
                while (p != NULL)
                {
                        printf("%s %s, %d \n", p -> first_name, p -> last_name, p -> age);
                        p = p -> next;
                }
        }
}

void list_ages()
{
	NODE *p;
	int input2;

	printf("What age would you like to search? \n");
	scanf("%d", &input2);

	if (input2 <= 18)
	{
		p = List[0].head;
		while (p != NULL)
        	{
                	if (input2 == p -> age)
                	{
                        	printf("%s %s, %d \n", p -> first_name, p -> last_name, p -> age);
                	}
                	p = p -> next;
        	}
	}

	if (input2 > 18 && input2 < 65)
	{
		p = List[1].head;
	        while (p != NULL)
        	{
                	if (input2 == p -> age)
                	{
                        	printf("%s %s, %d \n", p -> first_name, p -> last_name, p -> age);
                	}
                	p = p -> next;
        	}
	}

	if (input2 >= 65)
	{
		p = List[2].head;
	        while (p != NULL)
        	{
	                if (input2 == p -> age)
        	        {
                        	printf("%s %s, %d \n", p -> first_name, p -> last_name, p -> age);
                	}
                	p = p -> next;
        	}
	}
}

void remove_input(char *first, char *last)
{
	NODE *p;
	NODE *q;
	int i;
	int first_check;
	int last_check;

	for (i = 0; i < 3; i++)
	{
		p = List[i].head;
		q = List[i].head;
		while (p != NULL)
		{
			first_check = strcmp(first, p -> first_name);
			last_check = strcmp(last, p -> last_name);

			if (first_check == 0 && last_check == 0)
			{
				if (List[i].head == List[i].tail)
				{
					pthread_mutex_lock(&mutex);
					List[i].head = List[i].tail = NULL;
					pthread_mutex_unlock(&mutex);
				}

				else if (p == List[i].head)
				{
					pthread_mutex_lock(&mutex);
					List[i].head = p -> next;
					pthread_mutex_unlock(&mutex);
				}

				else if (p == List[i].tail)
				{
					pthread_mutex_lock(&mutex);
					List[i].tail = q;
					pthread_mutex_unlock(&mutex);
				}

				else
				{
					q -> next = p -> next;
				}

				free(p);
				return;
                	}
		q = p;
		p = p -> next;
		}
	}
	printf("There was no person with that name. \n");
}


int check_duplicate(char *first, char *last)
{
	int i;
	NODE *p;

	for (i = 0; i < 3; i++)
	{
		p = List[i].head;

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
	}
	return 1;
}


void read_all(char *file_name)
{
	char temp_first[20];
	char temp_last[20];
	int temp_age;
	FILE *outfp;

	if ((outfp = fopen(file_name, "r")) == NULL)
	{
		printf("The file could not be opened. \n");
		return;
	}

	while (fscanf(outfp, "%s %s %d", temp_first, temp_last, &temp_age) == 3)
	{
		insert(temp_first, temp_last, temp_age);
	}

	fclose(outfp);
}


void save_all(char *file_name)
{
	int i = 0;
	NODE *p;
	FILE *fp;

	if ((fp = fopen(file_name, "w")) == NULL)
	{
		printf("File 1 (text file) could not be opened. \n");
		return;
	}

	for (i = 0; i < 3; i++)
	{
		p = List[i].head;
		while (p != NULL)
		{
			fprintf(fp, "%s %s %d \n", p -> first_name, p -> last_name, p -> age);
			p = p -> next;
		}
	}
	fclose(fp);
}

void delete_all(NODE *p)
{
	if (p == NULL)
	{
		return;
	}

	delete_all(p -> next);
	free(p);
}


void change_age(char *first, char *last)
{
	int new_age;
	int i;
	NODE *p;

        for (i = 0; i < 3; i++)
        {
                p = List[i].head;

                while (p != NULL)
                {
                        int first_check = strcmp(first, p -> first_name);
                        int last_check = strcmp(last, p -> last_name);

                        if (first_check == 0 && last_check == 0)
                        {
                                printf("What is their new age? \n");
				scanf("%d", &new_age);
				remove_input(first, last);
                                insert(first, last, new_age);
				return;
                        }
                        p = p -> next;
                }
        }
	printf("The person you entered could not be found. \n");
}

void *loopThread(void *arg)
{
        int i = 0;
        int counter = 0;
        NODE *p;
        FILE *fp;
	char *file_name = (char *) arg;

        while (counter != -1)
        {
                pthread_mutex_lock(&mutex);
		if ((fp = fopen(file_name, "wb")) == NULL)
                {
                        printf("File 2 (binary file) could not be opened. \n");
                        return;
                }

                for (i = 0; i < 3; i++)
                {
                        p = List[i].head;
                        while (p != NULL)
                        {
                                fwrite(p, sizeof(NODE), 1, fp);
                                p = p -> next;
                        }
                }
                fclose(fp);
                pthread_mutex_unlock(&mutex);
                sleep(15);
        }
}

void readThread(char *file_name)
{
        char *temp_first;
        char *temp_last;
        int temp_age;
        NODE p;
        FILE *fp;

        if ((fp = fopen(file_name, "rb")) == NULL)
        {
                printf("File 2 (binary file) could not be opened. \n");
                return;
        }

        while (fread(&p, sizeof(NODE), 1, fp) == 1)
        {
                printf("%s %s, %d \n", p.first_name, p.last_name, p.age);
        }

        fclose(fp);
}

void doublyLinked_show()
{
	int i;
	NODE *p;

        for (i = 0; i < 3; i++)
        {
                p = List[i].tail;
                while (p != NULL)
                {
                        printf("%s %s, %d \n", p -> first_name, p -> last_name, p -> age);
                        p = p -> prev;
                }
        }
}

void recursion_show(NODE *p)
{
        int i;

	if (p -> next != NULL)
	{
		recursion_show(p -> next);
	}
	printf("%s %s, %d \n", p -> first_name, p -> last_name, p -> age);
}

int main(int argc, char *argv[])
{
	char first[20];
	char last[20];
	int age;
	int input = 0;
	int i;
	NODE *p;
	pthread_t thr;
	pthread_mutex_init(&mutex, NULL);

	if (argc < 3)
	{
		printf("Please enter 2 file names when running the code. \n");
		input = -1;
	}

	read_all(argv[1]);
	pthread_create(&thr, NULL, loopThread, (void *) argv[2]);
	
	while (input != -1)
	{
		printf("Enter '1' to add to the spreadsheet. \n");
		printf("Enter '2' to show the list alphabetically by last name. \n");
		printf("Enter '3' to show the list of people at a given age. \n");
		printf("Enter '4' to remove someone from the spreadsheet. \n");
		printf("Enter '5' to change the age of someone. \n");
		printf("Enter '6' to show the list from the auto-saved (binary) file. \n");
		printf("Enter '7' to show the list using a doubly linked list. \n");
		printf("Enter '8' to show the list using a doubly linked list recursively. \n");
		printf("Enter '0' to save all information to a text file and quit. \n");
		scanf("%d", &input);

                if (input == 1)
		{
			printf("Enter a first name. \n");
			scanf("%s", first);
			printf("Enter a last name. \n");
			scanf("%s", last);			
			printf("Enter an age. \n");
			scanf("%d", &age);
			printf("%s %s %d \n", first, last, age);
                        insert(first, last, age);
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
        		printf("Enter the first name of the person you'd like to remove. \n");
	        	scanf("%s", first);
        		printf("Enter the last name of the person you'd like to remove. \n");
	        	scanf("%s", last);
			remove_input(first, last);
		}

		if (input == 5)
		{
			printf("Enter the first name of the person whose age you wish to change. \n");
			scanf("%s", first);
			printf("Enter the last name of the person whose age you wish to change. \n");
			scanf("%s", last);
			change_age(first, last);
		}

		if (input == 6)
		{
			readThread(argv[2]);
		}

		if (input == 7)
		{
			doublyLinked_show();
		}

		if (input == 8)
		{
			for (i = 0; i < 3; i++)
			{
				p = List[i].head;
				recursion_show(p);
			}
		}

		if (input == 0)
		{
			save_all(argv[1]);
			for (i = 0; i < 3; i++)
			{
				p = List[i].head;
				delete_all(p);
			}
			input = -1;
		}
        }
}

