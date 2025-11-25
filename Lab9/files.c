#include "proj.h"

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

