#include<stdio.h>
#include<string.h>
#include "duy.h"
#include "bt-5.0.0/inc/btree.h"


#define EXIT '5'
#define TITLE()(printf("%-20s%-20s%-20s\n", "Name", "Number", "Email"))

typedef struct {
  char name[100];
  char email[100];
} Contact;


void insertNewNode(BTA *btfile, char tokens[][200])
{
  char number[15];
  Contact data;
  
  strcpy(data.name, tokens[0]);
  strcpy(number, tokens[1]);
  strcpy(data.email, tokens[2]);
  
  btins(btfile, number, (char *)&data, sizeof(data));
}


int loadData(BTA *btfile, char *text_file)
{
  FILE *f;
  int i;
  char buffer[500];
  char tokens[3][200];
  /* count the number of lines in the file */
  int nline = countLine(text_file);

  f = fopen(text_file, "r");
  for(i = 0; i < nline; i++){
    fgets(buffer, 500, f);
    getTokens(buffer, tokens, '-');
    insertNewNode(btfile, tokens);
  }
  
  
  fclose(f);
  
  return nline;
}


void displayContact(char *key, Contact data)
{
  printf("%-20s%-20s%-20s\n", data.name, key, data.email);
}


void traverse_bt(BTA *btfile)
{
  char number[15];
  Contact data;
  int rsize;

  btpos(btfile, ZSTART);
  TITLE();
  while(btseln(btfile, number, (char *)&data, sizeof(Contact), &rsize) != QNOKEY){
    displayContact(number, data);
  }

}


char getMenu()
{
  char choice;
  printf("+===============================================+\n");
  printf("| 1. Import phonebook from text                 |\n");
  printf("| 2. Open phonebook                             |\n");
  printf("| 3. Find a contact                             |\n");
  printf("| 4. Modify a contact                           |\n");
  printf("| 5. Exit                                       |\n");
  printf("+===============================================+\n");
  printf("Your choice: ");
  scanf("%c", &choice);
  myfflush();
  return choice;
}


int main()
{
  BTA *btfile;
  btinit();
  int opened = 0;
  char text_file[100];
  char bt_file[100];
  char number[15];
  //char name[100];
  //char email[100];
  char choice;
  int len;
  int rsize;
  int found;
  Contact data;
  Contact *pdata;

  do{
    choice = getMenu();

    switch(choice){

    case '1':
      
      if(opened){
	printf("The phonebook is already loaded\n");
	break;
      }

      opened = 1;
      printf("Enter the text file to import: ");
      scanf("%[^\n]", text_file);
      myfflush();

      printf("Enter the file to save: ");
      scanf("%[^\n]", bt_file);
      myfflush();

      btfile = btcrt(bt_file, 0, 0);
      len = loadData(btfile, text_file);
      traverse_bt(btfile);
      break;

    case '2':

      if(opened){
	printf("The phonebook is already opened\n");
	break;
      }

      opened = 1;
      printf("Enter the phonebook file: ");
      scanf("%[^\n]", bt_file);
      myfflush();

      btfile = btopn(bt_file, 0, 0);
      if(btfile == NULL){
	printf("%s does not exist\n", bt_file);
	opened = 0;
	break;
      }
      traverse_bt(btfile);
      break;

    case '3':
      printf("Enter the number you want to find: ");
      scanf("%[^\n^ ]", number);
      printf("%s\n", number);
      myfflush();
      
      found = btsel(btfile, number, (char *)&data, sizeof(Contact), &rsize);
      if(found != 0){
	printf("%s not found\n", number);
      } else if(found == 0){
	TITLE();
	displayContact(number, data);
      }
      break;

    case '4':
      printf("Enter the number you want to modify: ");
      scanf("%[^\n^ ]", number);
      myfflush();

      printf("Enter name: ");
      scanf("%[^\n]", data.name);
      myfflush();
      
      printf("Enter email: ");
      scanf("%[^\n^ ]", data.email);
      myfflush();
      
      if(btupd(btfile, number, (char *)&data, sizeof(Contact)) != 0){
	printf("Error: cannot update\n");
      }
      break;

    case '5':
      btcls(btfile);
      break;

    }//end switch

  }while(choice != EXIT);
  return 0;
}
