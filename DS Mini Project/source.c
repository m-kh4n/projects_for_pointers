/*
  IMPROVEMENTS REQUIRED:
    1. make admin pin **** while it is being entered
    2. make admin menu more branched
        2.a. a stock update function using purhcase code as core
        2.b. make see_stock function a seperate choice in admin menu
    3. make a code from make_bill which prints the same ascii receipt
       into a seperate txt file by the name of the receipt number
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define max_order 9

struct Comic {
  int id;
  char title[15];
  float price;
  int stock;
}; typedef struct Comic cdata;

int comic_count=0;
int last_id=100;
char reg_title[9][15];
float reg_price[9];
int reg_qtty[9];
int sr=0;

int purchased=0;

void show_shelf(){
	int n;
	FILE* base1;
  cdata s;
	if ((base1 = fopen("database.txt", "r")) == NULL) {
		printf("Error! opening file");
	}
  else{
    printf("\n\t\tID\tTITLE\t\tPRICE\n");
	  while(fscanf(base1, "%d\t%s\t%f\t%d\n",&s.id, s.title, &s.price, &s.stock)!=EOF) {
		  if(s.stock>0) printf("\t\t%d\t%s\t%.2f/-\n", s.id, s.title, s.price);
      last_id=s.id;
	  }
	  fclose(base1);
  }
}

void get_comic_count(){
    FILE* base=fopen("database.txt","r");
    cdata s;
    while(fscanf(base, "%d\t%s\t%f\t%d\n",&s.id, s.title, &s.price, &s.stock)!=EOF) {
		comic_count++;
        last_id=s.id;
	}
}

void add_to_bill(char title1[],float price1, int qtty1){
    for(int j=0; title1[j]!='\0';j++){
      reg_title[sr][j]=title1[j];
    }
    reg_price[sr]=price1;
    reg_qtty[sr]=qtty1;
    sr++;
}

void make_bill(){
    srand(time(0));
    int r_num = 1000 + rand() % (9999 - 1000 + 1);
    printf("\n _________________________________________________________________________________________________\n");
    printf("|                                                                                                 |\n");
    printf("|                              K H A N   C O M I C   B O O K   S T O R E                          |\n");
    printf("|                                                                                                 |\n");
    printf(" -------------------------------------------------------------------------------------------------\n");
    printf("|                                        - TAX INVOICE -                                          |\n");
    printf("|                                                                                                 |\n");
    printf("|  Receipt Number: %d                                                                           |\n",r_num);
    printf("|  _____________________________________________________________________________________________  |\n");
    printf("| | SR\t\tPARTICULARS\t\t\tPRICE\t\tUNITS\t\tTOTAL(GST +18%%)\t| |\n");
    printf("| |_____________________________________________________________________________________________| |\n");
    printf("| |                                                                                             | |\n");
    float grand_total=0.0;
    for(int i=0;i<sr;i++){
      float total=(1.18)*(reg_price[i])*(reg_qtty[i]);
      printf("| | %d\t\t %s\t\t\t %.2f\t\t\t %d\t\t%.2f\t| |\n",i+1,reg_title[i],reg_price[i],reg_qtty[i],total);
      grand_total=grand_total+total;
    }
    printf("| |                                                                                             | |\n");
    printf("| |                                                                                             | |\n");
    printf("| |                                                                                             | |\n");
    printf("| |                                                                                             | |\n");
    printf("| |   Thanks for visiting our store!                                GRAND TOTAL: %.2f Rupees \t| |\n",grand_total);
    printf("| |_____________________________________________________________________________________________| |\n");
    printf("|                                                                                                 |\n");
    printf("|_________________________________________________________________________________________________|\n");
}

void base_up(){
    FILE *clear_base=fopen("database.txt","w");
    fclose(clear_base);

    FILE *base=fopen("database.txt","w+");
    FILE *dup=fopen("temp.txt","r+");
    cdata temp;
    while(fscanf(dup, "%d\t%s\t%f\t%d\n", &temp.id, temp.title, &temp.price, &temp.stock)!=EOF){
        fprintf(base, "%d\t%s\t%.2f\t%d\n", temp.id, temp.title, temp.price, temp.stock);
    }
    fclose(dup);
    fclose(base);

    FILE *clear_dup=fopen("temp.txt","w+");
    fclose(clear_dup);
}

void purchase(){
    FILE *base=fopen("database.txt","r+");
    FILE *dup=fopen("temp.txt","w+");
    cdata s;

    int req_id, req_stock;
    printf("\nEnter the id of the the comic you wish to purchase: ");
    scanf("%d",&req_id);
    printf("How many units do you wish to purchase: ");
    scanf("%d",&req_stock);

    int found=0;
    while(fscanf(base, "%d\t%s\t%f\t%d\n", &s.id, s.title, &s.price, &s.stock)!=EOF){
        if(s.id==req_id){
            found=1;
            if(s.stock>=req_stock){
                add_to_bill(s.title,s.price,req_stock);
                ++purchased;
                fprintf(dup, "%d\t%s\t%f\t%d\n", s.id, s.title, s.price, (s.stock-req_stock));
            }
            else {
                printf("We dont have enough stock to make your puchase,\nWe only have %d units of this title available\n",s.stock);
                printf("Please retry purchase with smaller quantity\n");
                fprintf(dup, "%d\t%s\t%f\t%d\n", s.id, s.title, s.price, (s.stock-req_stock));
            }
        }
        else fprintf(dup, "%d\t%s\t%f\t%d\n", s.id, s.title, s.price, s.stock);
    }
    fclose(dup);
    fclose(base);
    base_up();
    if(found==0) {
        printf("We were unable to find the item you requested for, \n");
        printf("Here are the titles we currently have available: \n");
        show_shelf();
    }
}



void see_stock(){
  int n;
	FILE* base2=fopen("database.txt","r");
  cdata s;
	if (base2 == NULL) {
		printf("Error! opening file");
	}
  else{
    printf("\n\tID\tTITLE\t\tSTOCK\n");
	  while(fscanf(base2, "%d\t%s\t%f\t%d\n",&s.id, s.title, &s.price, &s.stock)!=EOF) {
		  if(s.stock==0) printf("\t%d\t%s\t%d  [OUT OF STOCK]\n", s.id, s.title, s.stock);
      else printf("\t%d\t%s\t%d\n", s.id, s.title, s.stock);
	  }
	  fclose(base2);
  }
}

void append_to_base() {
    int count;
    printf("\nEntries to be made: ");
    scanf("%d",&count);
    comic_count+=count;
    for(int i=1; i<=count; i++){
        cdata s;
        s.id=++last_id;
        printf("\n[%d]Title (comic_name): \t",i); scanf("%s",s.title);
        printf("[%d]Price : \t\t",i); scanf("%f",&s.price);
        printf("[%d]Stock Quantity: \t",i); scanf("%d",&s.stock);

        FILE *base = fopen("database.txt", "a+");
        if (base == NULL) {
            printf("Error opening file\n");
            return;
        }
        else{
        fprintf(base, "%d\t%s\t%.2f\t%d\n", s.id, s.title, s.price, s.stock);
        fclose(base);
        }
        see_stock();
    }
}



int main(){
    get_comic_count();
    int logch,ch1,ch2,pass;
    while(1){
      printf("\nWelcome  to the your comic book store: \n");
      printf("1. Login as a customer\n");
      printf("2. Login as the Admin \n");
      printf("3. Exit\n");
      printf("Enter a choice: ");
      scanf("%d",&logch);
      switch(logch)
      {
        case 1:
          printf("\tWelcome to KHAN COMIC BOOK STORE store! \n");
          printf("\tHere are all the fresh and classic titles available at our store today:\n");
          show_shelf();
          printf("\n\t Is there anything you'd like to buy..?\n");
          printf("Press 1 to continue and 0 to exit: ");
          scanf("%d",&ch1);
          while(ch1){
            purchase();
            printf("Do you want to add any more items in your cart...?\n");
            printf("Press 1 to continue and 0 to exit: ");
            scanf("%d",&ch1);
          }
          if(purchased!=0) {
            printf("\t Thanks for shopping with us! Here's your bill: \n");
            make_bill();
            sr=0;
          }
          break;
        case 2:
          printf("ENTER THE SIX DIGIT PIN: ");
          scanf("%d",&pass);
          if(pass==456789){
            printf("Do you wish to add new titles...? \n");
            printf("Press 1 to continue and 0 to exit: ");
            scanf("%d",&ch2);
            while(ch2){
              append_to_base();
              printf("Do you wish to append more titles...? \n");
              printf("Press 1 to continue and 0 to exit: ");
              scanf("%d",&ch2);
            }
          }
          else printf("You have entered the wrong pin! Try Again!");
          break;
      case 3:
        printf("Thanks for using our program! Goodbye! \n");
        return 0;
      default:
        printf("Please Enter a Valid Choice!\n");
        break;
      }
    }
}
