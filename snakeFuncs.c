
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define ROWS 25
#define COLS 75
#define SPEED_DIFFERENCE 0.03
#define MAKE_CHANGE 5

typedef struct snake //the struct of the snake
{
	int row; // current row of stract
	int col; // current col of stract
	struct snake* next; // address of next orgen in the list
}snake;

// Turn escape codes ON.
void init(void);

// Moves the cursor to position (x,y) on screen.
// Parameters:
//     x: the row of the position.
//     y: the column of the position.
void gotoxy(int x, int y);

// Delays the execution of the program.
// Parameters:
//     secs: the length of the delay in seconds. 
void sleep(float secs);

void printBoard();
snake* headOfSnake();
snake* addToHeadOfSnake(snake* head);
bool gameOver(snake* head);
void deleteLast(snake* head);
char moveInDirection(char c, snake* head);
void moveBody(snake* head);
void freeSnake(snake* head);
void printSnake(snake* head);

int main() {

	init();
	//printf("Press a to move left, d to move right, w to move up and s to move down\n");
	printBoard();
	int steps = 0;
	float speed = 1;
	snake* head = headOfSnake(); //starts the snake
	char c='d', prevC='d';

	while (!gameOver(head))
	{
		if (_kbhit()) //if user entered input
			c = _getch();

		if (c != 'd' && c != 'w' && c != 'a' && c != 's') //if incorrect input
			c = prevC;
		else
			prevC = c;

		if (steps == MAKE_CHANGE)
		{
			speed = speed - SPEED_DIFFERENCE;
			head = addToHeadOfSnake(head);
			printSnake(head);
			steps = 0;
		}
		else
		{
			moveInDirection(c, head);
			printSnake(head);
		}
			
		steps++;
	}
	freeSnake(head);

	system("pause");
}
	// Turn escape codes ON.
	void init(void) {
		system("cls");
	}

	// Moves the cursor to position (x,y) on screen.
	// Parameters:
	//     x: the row of the posiiton.
	//     y: the column of the posiiton.
	void gotoxy(int x, int y) {
		printf("\x1b[%d;%df", x, y);
	}

	// Delays the execution of the program.
	// Parameters:
	//     secs: the length of the delay in seconds. 
	void sleep(float secs) {
		clock_t clocks_start = clock();

		while (clock() - clocks_start < secs*CLOCKS_PER_SEC)
			;
	}
	void printBoard() //print the frame of the board
	{
		int i, row, col;

		for (i = 2; i <= COLS; i++)
		{
			printf("#");
			if (i == COLS)
			{
				row = 1;
				col = COLS;
			}
		}
		for (i = 1; i <= ROWS; i++)
		{
			printf("#");
			printf("\n");
		}
		for (i = 1; i <= ROWS; i++)
		{
			gotoxy(row, col);
			printf("#");
			printf("\n");
			row = i;
		}
		for (i = 1; i <= COLS; i++)
		{
			gotoxy(row, i);
			printf("#");
		}
	}
snake* headOfSnake() //sets the head of the snake at the begining of the game
{
	snake* head;
	head = (snake*)malloc(sizeof(snake));
	head->col = COLS / 2;
	head->row = ROWS / 2;
	head->next = NULL;

	return head;
}
snake* addToHeadOfSnake(snake* head) //creates new node and adds to the head of the snake
{
	snake* newHead;
	newHead = (snake*)malloc(sizeof(snake));

	newHead->next=head;
	newHead = head;
	
	return newHead;
}
char moveInDirection(char c, snake* head) // moves the snake at the direction
{
	moveBody(head);

	deleteLast(head);

	switch (c)
	{
	case 'd':
	{
		(head->col)++;
		break;
	}
	case 'a':
	{
		(head->col)--;
		break;
	}
	case 'w':
	{
		(head->row)--;
		break;
	}
	case 's':
	{
		(head->row)++;
		break;
	}
	}

	return c;
}
bool gameOver(snake* head) // checkes whether the snake bumped into the frame or itself and the game over
{
	snake* temp = head;
	bool isStuck = false, stuckInC = false, stuckInR = false;
	while (temp->next != NULL && isStuck == false) //Checks whether the snake bumped into itself
	{
			temp = temp->next;
			if (head->col == temp->col)
				isStuck = true;
	}
	if (head->col == 1 || head->col == COLS) // Checks whether the snake bumped into the frame
		stuckInC = true;
	if (head->row == 1 || head->row == ROWS) // Checks whether the snake bumped into the frame
		stuckInR = true;

	if (isStuck || stuckInC || stuckInR)
		return true;
	else
		return false;
}
void deleteLast(snake* head) // deletes the last apperance of the last node because the snake moved
{
	snake* temp = head;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	if (temp->next == NULL)
	{
		gotoxy(temp->row, temp->col);
		printf(" ");
	}
}
void moveBody(snake* head) // Promotes each organ to the location of the preceding organ
{
	if (head == NULL || head->next == NULL)
		return;
	else
	{
		moveBody(head->next);
		head->next->col = head->col;
		head->next->row = head->row;
	}
}
void printSnake(snake* head) // prints the snake
{
	snake* temp = head;
	while (temp!=NULL)
	{
		gotoxy(temp->row, temp->col);
		printf("@");
		temp = temp->next;
	}
}
void freeSnake(snake* head) // deletes the snake, free the list and prints game over
{
	snake* next;

	while (head != NULL)
	{
		gotoxy(head->row, head->col);
		printf(" ");
		next = head->next;
		free(head);
		head = next;
	}
	gotoxy(ROWS / 2, COLS / 2);
	printf("GAME OVER");
	gotoxy(26, 0);
	}
