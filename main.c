#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <conio.h>
#include <pthread.h>

/* FUNCTION PROTOTYPES */

int add(int , int );
int subtract(int , int );
int multiply(int , int );
int divide(int , int );
int power(int , int );
int iCounter = 60;
int sum=0, score;
void fhighscore(int );

void *counter(void *threadid);

void *diff_easy(void *threadid);
void *diff_medium(void *threadid);
void *diff_hard(void *threadid);


int main()
{
	FILE *fp;
	fp=fopen("high_score.txt", "a+");
	fscanf(fp,"%d",&score);
	fclose(fp);
	char cont[10];
	int flag;
	
	char Difficulty_level[10];
	
	/*Opening Screen Messages*/
	
	do{
		flag=0;
		printf("\n\n\t\t\tWELCOME TO THE QUICK MATHS");
		printf("\n\n\n\n\t\tThis is a place where you test your mental maths!\n\n\t\tCan you WIN this race against TIME?");
		printf("\n\n\t---------------------------------------------------------------------------------------------");	
		printf("\n\n\n\t\tEnter the Difficulty level\n\nEasy, Medium or Hard:\n");
		fflush(stdin);
		gets(Difficulty_level);
		strlwr(Difficulty_level);
		if(score<500 && strcmp(Difficulty_level, "medium")==0){
			printf("\n\n\tYour skill rank should be at least PRO to play this mode.");
			printf("\n\n\tTry another Mode.");
			printf("\n\n\tPress a key to continue:");
			flag=1;
			getch();
			system("cls");

		}
		else if(score<1000 && strcmp(Difficulty_level, "hard")==0){
			printf("\n\n\tYour skill rank should be at least EXPERT to play this mode.");
			printf("\n\n\tTry another Mode.");
			printf("\n\n\tPress a key to continue.");
			flag=1;
			getch();
			system("cls");

		}
		else if(strcmp(Difficulty_level, "easy")>0 || strcmp(Difficulty_level, "medium")>0 || strcmp(Difficulty_level, "hard")>0){
			printf("\n\n\tDifficulty level is invalid");
			printf("\n\n\tPlease try again!");
			printf("\n\n\tPress any key to continue.");
			flag=1;
			getch();
			system("cls");
		}
	}while(flag==1);
	system("cls");
	printf("\n\n\tYou have Entered %s Mode\n\n", Difficulty_level);
		printf("\n\n\t-----------------------------------------------------------------------------------------");
	printf("\n\n\n\n");
	printf("\tRules:\n\n");
	printf("\t1) A counter of 60 seconds will start once your game starts.\n\n");
	printf("\t2) Keep solving until the counter reaches 0.\n\n");
	printf("\t3) +5 seconds for correct answer. -5 seconds for every wrong answer.\n\n");
	printf("\t4) Every correct answer will give +50 points.\n\n");
	printf("\t5) If you have a 3 win streak, you will be granted +70 score for every correct answer.\n\n");
	printf("\t6) If you have a 5 win streak, you will be granted +90 score for every correct answer.\n\n");
	printf("\t7) If you give any incorrect answer, your streak will be lost.\n\n");
	printf("\t8) In case of division, you have to give the value of quotient.\n\n");
		printf("\n\n\t-----------------------------------------------------------------------------------------");
	printf("\n\n\t\tPress any key to continue");
	getch();
	system("cls");
	
	/*
		Easy Mode
		Operators ['+' '-' '*']

	*/
	if (strcmp(Difficulty_level,"easy")==0)
	{
        pthread_t thread1;
        pthread_t thread2;
        int rc, pc;
        rc = pthread_create(&thread1, NULL, counter, (void *)1);
        if(rc){
            printf("Error:unable to create thread, %d\n", rc);
            exit(-1);
        }

        pc = pthread_create(&thread2, NULL, diff_easy, (void *)1);
        if(pc){
            printf("Error: unable to create thread, %d\n", pc);
            exit(-1);
        }
        pthread_exit(NULL);
	}
	/*
        Medium Mode
        Operators['+' '-' '*' '/']
	*/
    else if(strcmp(Difficulty_level, "medium")==0){
        pthread_t thread1;
        pthread_t thread2;
        int pc, rc;

        rc = pthread_create(&thread1, NULL, counter, (void *)1);
        if(rc){
            printf("Error:unable to create thread, %d\n", rc);
            exit(-1);
        }
        pc = pthread_create(&thread2, NULL, diff_medium, (void *)1);
        if(pc){
            printf("Error:unable to create thread, %d\n", rc);
            exit(-1);
        }
        pthread_exit(NULL);
    }


	/*
		Hard Mode
		Operators['+' '-' '*' '/' '^']
	*/
	else if(strcmp(Difficulty_level, "hard")==0){
        pthread_t thread1;
        pthread_t thread2;
        int pc, rc;

        rc = pthread_create(&thread1, NULL, counter, (void *)1);
        if(rc){
            printf("Error: unable to create thread, %d\n", rc);
            exit(-1);
        }

        pc = pthread_create(&thread2, NULL, diff_hard, (void *)1);
        if(pc){
            printf("Error: unable to create thread, %d\n", pc);
            exit(-1);
        }
        pthread_exit(NULL);
	}
	else{
		printf("Error!");
		exit(1);
	}
	return 0;
}

//Functions
int add(int a, int b)
{
	return a+b;
}

int subtract(int a, int b)
{
	return a-b;
}

int multiply(int a, int b)
{
	return a*b;
}

int divide(int a, int b)
{
	return a/b;
}

int power(int a , int b)
{
	return pow(a,b);
}

/*
	SAVE HIGH SCORE FUNCTIONS
*/

void fhighscore(int sum)
{
	FILE *ptr1, *ptr2;
	ptr2 = fopen("high_score.txt", "r+");
	fscanf(ptr2,"%d",&score);
	fclose(ptr2);

	if(sum>score)
	{
		ptr1 = fopen("high_score.txt", "w+");
		fprintf(ptr1, "%d", sum);
		fclose(ptr1);
	}
}

/*
	THREAD FUNCTIONS
*/

void *counter(void *threadid){
	while(iCounter > 0){
        sleep(1);
        iCounter--;
    }
    system("cls");
    printf("\n\n\n\t\t\tTIME'S UP");
    sleep(2);
    system("cls");
    printf("\n\n\t\t\tThe total score =  %d", sum);
    fhighscore(sum);
    if(score < sum){
        printf("\n\n\t\t\tCongratulations! Your new High Score is: %d\n\n\n", score);
    }
    else{
        printf("\n\n\t\t\tThe High score is: %d\n\n\n", score);
    }
    	printf("\n\t\t\t\tYOUR SKILL RANK IS");
	if(score<=100){
		printf("\n\n\t\t\t\tNOOB");
	}
	else if(score<=500){
		printf("\n\n\t\t\t\tSEMI PRO");
	}
	else if(score<=1000){
		printf("\n\n\t\t\t\tPRO");
	}
	else if(score>1000){
		printf("\n\n\t\t\t\tEXPERT");
	}
	

    getch();
    exit(0);
    pthread_exit(NULL);
}

void *diff_easy(void *threadid){
    char op[5] = {'+', '-', '*'};
    int n1, n2, n3, i, j=0, streak=0;
    int ans;
    while(iCounter > 0){
        j++;
        srand(time(0));
        n1 = ( rand()%89 ) + 10;
        n2 = ( rand()%89 ) + 10;
        n3 = ( rand()%9 ) + 1;
        i = rand()%3;
        printf("\n\n\t\t\tYou have %d seconds left", iCounter);
        if(i==2){
            printf("\n\n\t\t(%d)\n\t\t\t%d %c %d = ",j, n1, op[i], n3);
        }
        else{
            printf("\n\n\t\t(%d)\n\t\t\t%d %c %d = ",j, n1, op[i], n2);
        }
        fflush(stdin);
        scanf("%d", &ans);
        if(i == 0){
            int c = add(n1, n2);
            if(ans == c){
                printf("\n\n\t\t\tCorrect!");
                printf("\n\n\t\t\tTime: + 5 seconds!");
                streak++;
                iCounter += 5;
                if(streak>=3&&streak<5){
                    printf("\n\n\t\t\tCongratulations! You have %d WIN STREAK!", streak);
                    sum+=70;
                    printf("\n\n\t\t\tScore + 70\n");
                }
                else if(streak>=5){
                    printf("\n\n\t\t\tCongratulations! You have %d WIN STREAK", streak);
                    sum+=90;
                    printf("\n\n\t\t\tScore + 90");
                }
                else{
                    sum += 50;
                    printf("\n\n\t\t\tScore + 50");
                }
            }
            else{
                printf("\n\n\t\t\tWrong!\n\n\t\t\tScore +0");
                iCounter = iCounter - 5;
                printf("\n\n\t\t\tTime: -5 seconds");
                streak=0;
            }
            sleep(2);
            iCounter += 2;
            system("cls");
        }
        else if(i == 1){
            int c = subtract(n1, n2);
            if(ans == c){
                printf("\n\n\t\t\tCorrect!");
                printf("\n\n\t\t\tTime: + 5 seconds!");
                iCounter += 5;
                streak++;
                if(streak>=3&&streak<5){
                    printf("\n\n\t\t\tCongratulations! You have %d WIN STREAK!", streak);
                    sum+=70;
                    printf("\n\n\t\t\tScore + 70");
                }
                else if(streak>=5){
                    printf("\n\n\t\t\tCorrect!");
                    printf("\n\n\t\t\tCongratulations! You have %d WIN STREAK", streak);
                    sum+=90;
                    printf("\n\n\t\t\tScore + 90");
                }
                else{
                    sum += 50;
                    printf("\n\n\t\t\tScore + 50");
                }
            }
            else{
                printf("\n\n\t\t\tWrong!\n\n\t\t\tScore + 0");
                iCounter = iCounter - 5;
                printf("\n\n\t\t\tTime: -5 seconds");
                streak=0;
            }
            sleep(2);
            system("cls");
        }
        else if(i == 2){
            int c = multiply(n1, n3);
            if(ans == c){
                printf("\n\n\t\t\tCorrect!");
                printf("\n\n\t\t\tTime: + 5 seconds!");
                iCounter += 5;
                streak++;
                if(streak>=3&&streak<5){
                    printf("\n\n\t\t\tCongratulations! You have %d WIN STREAK!", streak);
                    sum+=70;
                    printf("\n\n\t\t\tScore + 70");
                }
                else if(streak>=5){
                    printf("\n\n\t\t\tCorrect!\n");
                    printf("\n\n\t\t\tCongratulations! You have %d WIN STREAK", streak);
                    sum+=90;
                    printf("\n\n\t\t\tScore + 90");
                }
                else{
                    sum += 50;
                    printf("\n\n\t\t\tScore + 50");
                }
            }
            else{
                printf("\n\n\t\t\tWrong!\n\n\t\t\tScore + 0");
                iCounter = iCounter - 5;
                printf("\n\n\t\t\tTime: -5 seconds");
                streak=0;
            }
            sleep(2);
            system("cls");
        }

    }
    getch();
    exit(0);
    pthread_exit(NULL);
}

void *diff_medium(void *threadid){
    char op[5] = {'+', '-', '*', '/'};
    int n1, n2, n3, n4, n5, i, j=0;
    int ans;
    int streak=0;

    while(iCounter > 0){
        srand(time(0));
        n1 = ( rand()%199 ) + 100;
        n2 = ( rand()%199 ) + 100;
        n3 = rand()%20 + 10;
        n4 = rand()%10 + 10;
        n5 = rand()%10 + 1;
        i = rand()%4;
        j++;
        printf("\n\n\t\t\tYou have %d seconds left", iCounter);
        if(i==0 || i==1){
        printf("\n\n\t\t(%d)\n\t\t\t%d %c %d = ",j, n1, op[i], n2);
        }
        else if(i==2){
        printf("\n\n\t\t(%d)\n\t\t\t%d %c %d = ",j, n3, op[i], n4);
        }
        else if(i==3){
            printf("\n\n\t\t(%d)\n\t\t\t%d %c %d = ",j, n3, op[i], n5);
        }
        fflush(stdin);
        scanf("%d", &ans);
        if(i == 0){
            int c = add(n1, n2);
            if(ans == c){
                printf("\n\n\t\t\tCorrect!");
                printf("\n\n\t\t\tTime: + 6 seconds!");
                iCounter += 6;
                streak++;
                if(streak>=3&&streak<5){
                    printf("\n\n\t\t\tCongratulations! You have %d WIN STREAK!", streak);
                    sum+=70;
                    printf("\n\n\t\t\tScore + 70\n");
                }
                else if(streak>=5){
                    printf("\n\n\t\t\tCongratulations! You have %d WIN STREAK", streak);
                    sum+=90;
                    printf("\n\n\t\t\tScore + 90");
                }
                else{
                    sum += 50;
                    printf("\n\n\t\t\tScore + 50");
                }
            }
            else{
                printf("\n\n\t\t\tWrong!\n\n\t\t\tScore + 0");
                iCounter = iCounter - 5;
                printf("\n\n\t\t\tTime: -5 seconds");
                streak=0;
            }
            sleep(2);
            system("cls");
        }
        else if(i == 1){
            int c = subtract(n1, n2);
            if(ans == c){
                printf("\n\n\t\t\tCorrect!");
                printf("\n\n\t\t\tTime: + 6 seconds!");
                iCounter += 6;
                streak++;
                if(streak>=3&&streak<5){
                    printf("\n\n\t\t\tCongratulations! You have %d WIN STREAK!", streak);
                    sum+=70;
                    printf("\n\n\t\t\tScore + 70\n");
                }
                else if(streak>=5){
                    printf("\n\n\t\t\tCongratulations! You have %d WIN STREAK", streak);
                    sum+=90;
                    printf("\n\n\t\t\tScore + 90");
                }
                else{
                    sum += 50;
                    printf("\n\n\t\t\tScore + 50");
                }
            }
            else{
                printf("\n\n\t\t\tWrong!\n\n\t\t\tScore + 0");
                iCounter = iCounter - 5;
                printf("\n\n\t\t\tTime: -5 seconds");
                streak=0;
            }
            sleep(2);
            system("cls");
        }
        else if(i == 2){
            int c = multiply(n3, n4);
            if(ans == c){
                printf("\n\n\t\t\tCorrect!");
                printf("\n\n\t\t\tTime: + 6 seconds!");
                iCounter += 6;
                streak++;
                if(streak>=3&&streak<5){
                    printf("\n\n\t\t\tCongratulations! You have %d WIN STREAK!", streak);
                    sum+=70;
                    printf("\n\n\t\t\tScore + 70\n");
                }
                else if(streak>=5){
                    printf("\n\n\t\t\tCongratulations! You have %d WIN STREAK", streak);
                    sum+=90;
                    printf("\n\n\t\t\tScore + 90");
                }
                else{
                    sum += 50;
                    printf("\n\n\t\t\tScore + 50");
                }
            }
            else{
                printf("\n\n\t\t\tWrong!\n\n\t\t\tScore + 0");
                iCounter = iCounter - 5;
                printf("\n\n\t\t\tTime: -5 seconds");
                streak=0;
            }
            sleep(2);
            system("cls");
        }
        else if(i == 3){
            int c = divide(n3, n5);
            if(ans == c){
                printf("\n\n\t\t\tCorrect!");
                printf("\n\n\t\t\tTime: + 6 seconds!");
                iCounter += 6;
                streak++;
                if(streak>=3&&streak<5){
                    printf("\n\n\t\t\tCongratulations! You have %d WIN STREAK!", streak);
                    sum+=70;
                    printf("\n\n\t\t\tScore + 70\n");
                }
                else if(streak>=5){
                    printf("\n\n\t\t\tCongratulations! You have %d WIN STREAK", streak);
                    sum+=90;
                    printf("\n\n\t\t\tScore + 90");
                }
                else{
                    sum += 50;
                    printf("\n\n\t\t\tScore + 50");
                }
            }
            else{
                printf("\n\n\t\t\tWrong!\n\n\t\t\tScore + 0");
                iCounter = iCounter - 5;
                printf("\n\n\t\t\tTime: -5 seconds");
                streak=0;
            }
            sleep(2);
            system("cls");
        }
    }
    getch();
    exit(0);
    pthread_exit(NULL);
}

void *diff_hard(void *threadid)
{
    char op[5] = {'+', '-', '*', '/', '^'};
    int n1, n2, n3, n4, n6, n7, i, j=0;
    int ans;
    int streak=0;

    while(iCounter > 0){
        srand(time(0));
        n1 = ( rand()%889 ) + 100;
        n2 = ( rand()%889 ) + 100;
        n6 = ( rand()%89 ) + 10;
        n7 = ( rand()%39 ) + 10;
        n3 = ( rand()%9 ) + 1;
        n4 = ( rand()%2 ) + 2;
        i = rand()%5;
        j++;
         printf("\n\n\t\t\tYou have %d seconds left", iCounter);
        if(i==2){
            printf("\n\n\t\t(%d)\n\t\t\t%d %c %d = ",j, n7, op[i], n6);
        }
        else if(i==0 || i==1){
            printf("\n\n\t\t(%d)\n\t\t\t%d %c %d = ",j, n1, op[i], n2);
        }
        else if(i==3){
            printf("\n\n\t\t(%d)\n\t\t\t%d %c %d = ",j, n6, op[i], n3);
        }
        else if(i==4){
            printf("\n\n\t\t(%d)\n\t\t\t%d %c %d = ",j, n3, op[i], n4);
        }
		fflush(stdin);
        scanf("%d", &ans);
        if(i == 0){
            int c = add(n1, n2);
            if(ans == c){
                printf("\n\n\t\t\tCorrect!");
                printf("\n\n\t\t\tTime: + 7 seconds!");
                iCounter += 7;
                streak++;
                if(streak>=3&&streak<5){
                    printf("\n\n\t\t\tCongratulations! You have %d WIN STREAK!", streak);
                    sum+=70;
                    printf("\n\n\t\t\tScore + 70");
                }
                else if(streak>=5){
                    printf("\n\n\t\t\tCongratulations! You have %d WIN STREAK", streak);
                    sum+=90;
                    printf("\n\n\t\t\tScore + 90");
                }
                else{
                    sum += 50;
                    printf("\n\n\t\t\tScore + 50");
                }
            }
            else{
                printf("\n\n\t\t\tWrong!\n\n\t\t\tScore + 0");
                iCounter = iCounter - 5;
                printf("\n\n\t\t\tTime: -5 seconds");
                streak=0;
            }
            sleep(2);
            system("cls");
        }
        else if(i == 1){
            int c = subtract(n1, n2);
            if(ans == c){
                printf("\n\n\t\t\tCorrect!");
                printf("\n\n\t\t\tTime: + 7 seconds!");
                iCounter += 7;
                streak++;
                if(streak>=3&&streak<5){
                    printf("\n\n\t\t\tCongratulations! You have %d WIN STREAK!", streak);
                    sum+=70;
                    printf("\n\n\t\t\tScore + 70");
                }
                else if(streak>=5){
                    printf("\n\n\t\t\tCongratulations! You have %d WIN STREAK", streak);
                    sum+=90;
                    printf("\n\n\t\t\tScore + 90");
                }
                else{
                    sum += 50;
                    printf("\n\n\t\t\tScore + 50");
                }
            }
            else{
                printf("\n\n\t\t\tWrong!\n\n\t\t\tScore + 0");
                iCounter = iCounter - 5;
                printf("\n\n\t\t\tTime: -5 seconds");
                streak=0;
            }
            sleep(2);
            system("cls");
        }
        else if(i == 2){
            int c = multiply(n6, n7);
            if(ans == c){
                printf("\n\n\t\t\tCorrect!");
                printf("\n\n\t\t\tTime: + 7 seconds!");
                iCounter += 7;
                streak++;
                if(streak>=3&&streak<5){
                    printf("\n\n\t\t\tCongratulations! You have %d WIN STREAK!", streak);
                    sum+=70;
                    printf("\n\n\t\t\tScore + 70");
                }
                else if(streak>=5){
                    printf("\n\n\t\t\tCongratulations! You have %d WIN STREAK", streak);
                    sum+=90;
                    printf("\n\n\t\t\tScore + 90");
                }
                else{
                    sum += 50;
                    printf("\n\n\t\t\tScore + 50");
                }
            }
            else{
                printf("\n\n\t\t\tWrong!\n\n\t\t\tScore + 0");
                iCounter = iCounter - 5;
                printf("\n\n\t\t\tTime: -5 seconds");
                streak=0;
            }
            sleep(2);
            system("cls");
        }
        else if(i == 3){
            int c = divide(n6, n3);
            if(ans == c){
                printf("\n\n\t\t\tCorrect!");
                printf("\n\n\t\t\tTime: + 7 seconds!");
                iCounter += 7;
                streak++;
                if(streak>=3&&streak<5){
                    printf("\n\n\t\t\tCongratulations! You have %d WIN STREAK!", streak);
                    sum+=70;
                    printf("\n\n\t\t\tScore + 70");
                }
                else if(streak>=5){
                    printf("\n\n\t\t\tCongratulations! You have %d WIN STREAK", streak);
                    sum+=90;
                    printf("\n\n\t\t\tScore + 90");
                }
                else{
                    sum += 50;
                    printf("\n\n\t\t\tScore + 50");
                }
            }
            else{
                printf("\n\n\t\t\tWrong!\n\n\t\t\tScore + 0");
                iCounter = iCounter - 5;
                printf("\n\n\t\t\tTime: -5 seconds");
                streak=0;
            }
            sleep(2);
            system("cls");
        }
        else if (i==4)
        {
            int c= power(n3, n4);
            if(ans == c)
            {
                printf("\n\n\t\t\tCorrect!");
                streak++;
                printf("\n\n\t\t\tTime: + 7 seconds!");
                iCounter += 7;
                if(streak>=3&&streak<5){
                    printf("\n\n\t\t\tCongratulations! You have %d WIN STREAK!", streak);
                    sum+=70;
                    printf("\n\n\t\t\tScore + 70");
                }
                else if(streak>=5){
                    printf("\n\n\t\t\tCongratulations! You have %d WIN STREAK", streak);
                    sum+=90;
                    printf("\n\n\t\t\tScore + 90");
                }
                else{
                    sum += 50;
                    printf("\n\n\t\t\tScore + 50");
                }
            }
            else{
                printf("\n\n\t\t\tWrong!\n\n\t\t\tScore+0");
                iCounter = iCounter - 5;
                printf("\n\n\t\t\tTime: -5 seconds");
                streak=0;
            }
            sleep(2);
            system("cls");
        }
    }
    pthread_exit(NULL);
}


