#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int division(int quotient);

int main() // 
{
	int divisor, quotient, dividend, answer, counter, i;
	srand((int) time(NULL));
	for(i=0;i<10;i++) // Loops 10 times 
	{
		divisor = (rand()%12)+1; // Generate divisor
		quotient = rand()%13; // Generate quotient
		dividend = divisor*quotient; 
		printf("%d / %d? \n", dividend, divisor); // Prints the problem
		answer=division(quotient);
		if(answer==1) // Uses value recevied from div function and counts the amount of correct answers
		{
			counter++;
			printf("Correct! \n");
		}
		else
			printf("Incorrect. The answer is %d \n", quotient);
	}
	printf("You got %d answers correct \n", counter); // Prints the amount of correct
}

int division(int quotient) // Checks if the inputted guess is correct and returns 1 if correct or 0 if incorrect to the main function
{
	int guess;
	scanf("%d", &guess);
	if(guess==quotient)
		return 1;
	else
		return 0;
	
}

