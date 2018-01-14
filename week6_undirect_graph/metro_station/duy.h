#include<stdio.h>
#include<string.h>
#include<time.h>
#include<ctype.h>
#include<stdlib.h>

/*
  prototype
 */
void trimLeft(char s[]);	//eliminate the spaces at the beginning.
void trimRight(char s[]); 	//eliminate the spaces at the end
void trimMiddle(char s[]);	//eliminate the spaces at the middle of the string
void shiftString(char s[], int n1, int n2);	//shift a string at index n2 to n1
void standardName(char s[]);	//standard name
void increaseInt(int A[], int len);   //sorting an array of int increasingly
void decreaseInt(int A[], int len);   //sorting an array of int decreasingly
void swapInt(int *a, int *b);    //swap two integers
void myfflush();                 //clear redundant
FILE *myfopen(char *name, char *mode);
void changeExtend(char *name, char *extend, char *newName);   //change the extend of file: luong.h -> luong.txt
void generateData(int *A, char *name, int low, int high, int n);    //generate n random integers in range low - high
                                                                    //then store it in array A and file name
int getTokens(char *buffer, char tokens[][200], char ch);           //break buffer into tokens separated by ch character
char inputChoice(char lowBound, char highBound, char *message);
int inputInt(char *prompt, int lowBound, int highBound, char *message);
void toString(int a, char buffer[]);  //not checked
void swap(int *a, int *b);  //not checked
int countLine(char *fileName);  //count the number of line in a file named by fileName
void toLower(char *buffer);  //convert a string to lower case
void toUpper(char *buffer);  //convert a string to upper case


/***************************************
*
* shiftString
*
***************************************/
void shiftString(char s[], int n1, int n2)
{

	int i;

	for(i = n2; i < strlen(s)+1; i++)
	{
		s[i+n1-n2] = s[i];
	}//end for

}//end shiftString


/****************************************
*
* trimLeft
*
*****************************************/
void trimLeft(char s[])
{

	int len = strlen(s);
	int i = 0;

	if(s[i] != ' ') return;
	else
	{
		while(s[i] == ' ') i++;

		shiftString(s, 0, i);
	}

}//end trimLeft


/*****************************************
*
* trimRight
*
******************************************/
void trimRight(char s[])
{
	int len = strlen(s);
	int i = len - 1;

	if(s[i] != ' ') return;
	else
	{
		while(s[i] == ' ') i--;
		s[i+1] = s[len];
	}//end else

}//end trimRight


/***************************************
*
* trimMiddle
*
****************************************/
void trimMiddle(char s[])
{

	int len = strlen(s);
	int i;
	int count;

	for(i = 1; i < len; i++)
	{

		if(s[i] == ' ')
		{
			count = 0;
			while(s[i] == ' '){
				i++;
				count++;
			};

			if(count > 1) shiftString(s, i+1 - count, i);
			i = i + 1 - count;	//update i
		}//end if

	}//end for

}//end trimMiddle


/**********************************************************
*
* standardName
*
***********************************************************/
void standardName(char s[])
{
	int i;

	//eliminate redundant space bars
	trimLeft(s);
	trimRight(s);
	trimMiddle(s);

	//Capitalize the first Character
	if(!isupper(s[0])) s[0] -= 32;
	for(i = 1; i < strlen(s); i++)
	{
		//printf("%d ", i);
		if(s[i] == ' '){
			if(!isupper(s[i+1]))
			{
				s[i+1] -= 32;
				i++;
			}//end nested if
		}//end if

	}//end for
}//end standardName


void swapInt(int *a, int *b)
{
  int tmp;

  tmp = *a;
  *a = *b;
  *b = tmp;
}

void decreaseInt(int A[], int len)
{
  int i, j;

  for(i = 0; i < len - 1; i++)
    for(j = 1; j < len; j++)
      {
	if(A[j-1] < A[j])
	  {
	    swapInt(&A[j-1], &A[j]);
	  }//end if

      }//end nested for
}//end decreaseInt


void increaseInt(int A[], int len)
{
  int i, j;

  for(i = 0; i < len - 1; i++)
    for(j = 1; j < len; j++)
      {
	if(A[j-1] > A[j])
	  {
	    swapInt(&A[j-1], &A[j]);
	  }//end if

      }//end nested for
}//end increaseInt


// my fflush
void myfflush() {
  int ch;
  while((ch = getchar()) && ch != '\n' && ch != EOF);
}



/**
 * Function: myfopen
 * Open file and handle file error
 */
FILE *myfopen(char *name, char *mode)
{
  FILE *f;

  //open file
  f = fopen(name, mode);
  
  //handle
  if(f == NULL){
    printf("File %s does not exist.\n", name);
    exit(1);
  }//end if

  return f;

}//end myfopen


/**
 * changeExtend
 * change the extend of a file name
 * nokia.txt, dat -> nokia.dat
 */
void changeExtend(char *name, char *extend, char *newName)
{
  int i = 0;

  do{
    newName[i] = name[i];
    i++;
  }while(name[i] != '.');
  newName[i] = '.';
  strcat(newName, extend);
    
}//end changeExtend


void generateData(int *A, char *name, int low, int high, int n)
{
  
  int i;
  FILE *f;
  int range = high - low + 1;

  //open file to write
  f = myfopen(name, "w");

  for(i = 0; i < n; i++){
    A[i] = rand()%range + low;
    fprintf(f, "%d ", A[i]);
  }

  fclose(f);

}


int getTokens(char *buffer, char tokens[][200], char ch)
{
  
  int i = 0;
  int j = 0;
  int index = 0;

  while(buffer[i] != '\n' && buffer[i] != '\0'){

    if(buffer[i] == ch){
      tokens[index][j] = '\0';
      index++;
      i++;
      j = 0;
      continue;
    }

    tokens[index][j] = buffer[i];
    i++;
    j++;

  }//end while

  tokens[index][j] = '\0';

  return index+1;

}


char inputChoice(char lowBound, char highBound, char *message)
{

  char choice;
  do{
    scanf("%c", &choice);
    myfflush();
    if((choice < lowBound) || (choice > highBound)) printf("%s\n", message);
  }while((choice < lowBound) || (choice > highBound));

  return choice;

}//end inputChoice

int inputInt(char *prompt, int lowBound, int highBound, char *message)
{

  int choice;
  do{
    printf("%s", prompt);
    scanf("%d", &choice);
    myfflush();
    if((choice < lowBound) || (choice > highBound)) printf("%s\n", message);
  }while((choice < lowBound) || (choice > highBound));

  return choice;

}//end inputInt


void toString(int a, char* buffer)
{
  int num = 1;
  int i=0;
  int mod;
  int k = 10;
  while(k <= a){
    k*=10;
    num++;
  }

  do{
    mod = a/(k/10);
    buffer[i] = (char) mod+'0';
    i++;
    a = a%(k/10);
    k /= 10;
  }while(k > 1);

  buffer[i] = '\0';
  
}


void swap(int *a, int *b)
{
  int tmp;
  tmp = *a;
  *a = *b;
  *b = tmp;
}

int countLine(char *fileName)
{

  int count = 0;
  int ch;

  FILE *f;
  
  f = myfopen(fileName, "r");
  while((ch = fgetc(f)) != EOF)
    if(ch == '\n') count++;
  fclose(f);

  return count;

}//end count


void toLower(char *buffer)
{

  int i;
  int len = strlen(buffer);

  for(i = 0; i < len; i++){
    if(isupper(buffer[i])) buffer[i] += 32;
  }

}

void toUpper(char *buffer)
{

  int i;
  int len = strlen(buffer);

  for(i = 0; i < len; i++){
    if(islower(buffer[i])) buffer[i] -= 32;
  }

}
