// MENU DRIVEN SINGLY LINKED LIST PROGRAM
// A-62, Muhammad Shahnawaz Khan, 21070461

#include <stdio.h>
#include <stdlib.h>

struct node{
    int value;
    struct node *next;
};typedef struct node node;

void printlist(node *head);
void even_odd(node *head);
void middle(node *head);
void last_second(node *head);
void sum(node *head);
void reverse(node **head);

void printMenu() {
  printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ");
  printf("\nLinked List Operations\n");
  printf("1. Print the current Linked List\n");
  printf("2. Print the Odd and Even items separately\n");
  printf("3. Find the Middle Item\n");
  printf("4. Find the Last Second Item\n");
  printf("5. Find the Sum of all elements\n");
  printf("6. Reverse the Linked List and print\n");
  printf("7. Exit\n");
}

int main()
{
    int i, n;
    printf("Enter the number of nodes: ");
    scanf("%d",&n);
    node linkedlist[n];
    for(i=0;i<n;i++){
        printf("Enter value for node [%d]: ",i+1);
        scanf("%d",&linkedlist[i].value);
        linkedlist[i-1].next=&linkedlist[i];
    }
    node *head=&linkedlist[0];
    linkedlist[n-1].next=NULL;
    int choice;
    while (1) {
    printMenu();
    printf("\nEnter your choice: ");
    scanf("%d", &choice);
    switch (choice) {
      case 1: printlist(head); break;
      case 2: even_odd(head); break;
      case 3: middle(head); break;
      case 4: last_second(head); break;
      case 5: sum(head); break;
      case 6: reverse(&head); break;
      case 7: printf("\nThanks for using our program ^^ Goodbye! \n"); return 0;
      default: printf("Invalid choice. Please try again.\n"); break;
    }
  }
}

void printlist(node *head){
    printf("\nLinked List: ");
    while (head != NULL){
        printf("%d - ", head->value);
        head = head->next;
    }
}

void even_odd(node *head){
    printf("\t EVEN \t\t ODD \n");
    while (head != NULL){
        if (head->value % 2 == 0) printf("\t %d\n", head->value);
        else printf("\t\t\t%d\n", head->value);
        head = head->next;
    }
}

void middle(node *head){
    node *a = head, *b = head;
    while (b->next != NULL){
        b = b->next->next;
        if (b != NULL) a = a->next;
    }
    printf("\nThe Value at the exact middle is: %d",a->value);
}

void last_second(node *head){
    node *a = head, *b = head->next;
    while (b->next != NULL){
        b = b->next;
        a = a->next;
    }
    printf("\nThe Last Second value is: %d",a->value);
}

void sum(node *head){
    int sum = 0;
    while (head != NULL){
        sum += head->value;
        head = head->next;
    }
    printf("\nSum of all values of in the Linked List: %d",sum);
}

void reverse(node **head){
    node *prev = NULL;
    node *curr = *head;
    node *next;
    while (curr != NULL){
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    *head = prev;
    printlist(*head);
}