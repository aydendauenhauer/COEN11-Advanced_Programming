#include <stdio.h>

int main()
{
	int x, y, z, i, guess, score;
	srand((int)time(NULL));

	for (i = 0; i < 10; i++)
	{
		x = rand()%12 + 1;
		y = rand()%13;

		z = x * y;

		printf("%d / %d is equal to?", z, x);

		scanf("%d", &guess);

		if (guess == y)
		{
			printf("Correct\n");
			score++;
		}

		else
		{
			printf("Incorrect\n");
			printf("The correct answer was %d\n", y);
		}

	}
	printf("Your score is: %d\n", score);
}
