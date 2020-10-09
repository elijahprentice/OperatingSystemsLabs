#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h> 

/* IMPLEMENT ME: Declare your functions here */
int add (int a, int b);
int subtract (int a, int b);
int multiply (int a, int b);
int divide (int a, int b);

int main (void)
{
	/* IMPLEMENT ME: Insert your algorithm here */
  int operator;
	int result;
  int operands[2];
  srand(getpid());
  
  int stillRunning = 1;
  
  while(stillRunning) {
    
    operands[0] = rand() % 10;
    operands[1] = rand() % 10;
    
    printf("Operand ‘a’ : %d Operand ‘b’ : %d\n", operands[0], operands[1]);
    printf("Specify the operation to perform");
    printf("(0 : add | 1 : subtract | 2 : Multiply | 3 : divide | 4 : exit): ");
    scanf("%d", &operator);
    
    result = operator == 0 ? add(operands[0], operands[1]) :
      operator == 1 ? subtract(operands[0], operands[1]) :
      operator == 2 ? multiply(operands[0], operands[1]) :
      operator == 3 ? divide(operands[0], operands[1]) :
      operator == 4 ? -100 : -1;
    
		printf((result > -100) ? "x = %d\n" : "\n", result);
		
		stillRunning = result >= 0 ? 1 : result == -100 ? 0 : 1;
  }

	return 0;
}

/* IMPLEMENT ME: Define your functions here */
int add (int a, int b) { printf ("Adding 'a' and 'b'\n"); return a + b; }
int subtract (int a, int b) { printf ("Subtracting 'b' from 'a'\n"); return a - b; }
int multiply (int a, int b) { printf ("Multiplying 'a' and 'b'\n"); return a * b; }
int divide (int a, int b) { printf ("Dividing 'a' by 'b'\n"); return a / b; }