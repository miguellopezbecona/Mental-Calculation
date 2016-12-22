#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DEFAULT_NUMBER_QUESTIONS 10

// Maps operator code to operator character and returns result
int calculate(int op, char* c, int num1, int num2){
    switch(op){
        case 0: *c = '+'; return num1 + num2;
        case 1: *c = '-'; return num1 - num2;
        case 2: *c = '*'; return num1 * num2;
        case 3: *c = '/'; return num1 / num2;
		default: *c = '?'; return 0; // Should never happen
    }
}

// The core function: generates stuff, checks your answer and returns the score
int ask(){
    // Generates first number and operator code
    int num1 = (rand() % 99) + 1;
    int op = rand() % 4;
	
    int num2;
    char c;
    int answer;

    // Generates the second number, depending on the operator
    switch(op){
        case 0:
        case 1:
            num2 = (rand() % 99) + 1;

            // The first number will be always the greater one to make subtractions less annoying
            if(num2 > num1) {
                int aux = num2;
                num2 = num1;
                num1 = aux;
            }
            break;
        case 2:
        case 3: // No huge multiplications/divisions
            num2 = (rand() % 7) + 2;
            break;
    }

    int result = calculate(op, &c, num1, num2);
    printf("%d %c %d = ", num1, c, num2);
    scanf("%d", &answer);

    printf("The correct answer was: %d\n\n", result);
	
	 // Increments score if the answer was correct (could be done in a more sophisticated way, like counting the time spent, but meh...)
    return answer == result;
}

int main(int argc, char** argv){
    srand(time(NULL));
	
	int score = 0;
	int number_questions = DEFAULT_NUMBER_QUESTIONS;
	
	// Number of questions can be set through console parameter
	if(argc > 1 && atoi(argv[1]) > 0)
		number_questions = atoi(argv[1]);
	
	printf("Welcome to Mental Calculation! %d operations will appear to you and you must answer each one. You will get your score in the end. Good luck! :)\n\n", number_questions);

    int i;
    for(i = 0; i < number_questions; i++)
        score += ask();

    printf("Your score: %d out of %d.\n", score, number_questions);
    system("pause"); // So you can view your score without executing from a shell
    return 0;
}
