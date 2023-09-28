#include <stdio.h>
#include <stdlib.h>
// A structure to represent a node in the linked list
typedef struct node {
  int data;
  struct node *next;
} NODE;

// A structure to represent a queue
typedef struct queue {
  NODE *front;
  NODE *rear;
} QUEUE;

// Insert an element to the queue
void insert(QUEUE *q, int elm) {
  // Create a new node
  NODE *new_node = (NODE *)malloc(sizeof(NODE));
  new_node->data = elm;
  new_node->next = NULL;

  // If the queue is empty, set the front and rear pointers to the new node
  if (q->front == NULL) {
    q->front = new_node;
    q->rear = new_node;
  } else {
    // Add the new node to the end of the queue
    q->rear->next = new_node;
    q->rear = new_node;
  }
}

// Delete an element from the queue
int delete(QUEUE *q) {
  // If the queue is empty, return -1
  if (q->front == NULL) {
    return -1;
  }

  // Get the element at the front of the queue
  int dequeued_element = q->front->data;

  // Remove the front node from the queue
  q->front = q->front->next;

  // If the queue is now empty, set the rear pointer to NULL
  if (q->front == NULL) {
    q->rear = NULL;
  }

  return dequeued_element;
}

// Check if the queue is empty
int is_empty(QUEUE *q) {
  return q->front == NULL;
}

// Print the queue
void printQueue(QUEUE *q) {
  NODE *temp = q->front;
  while (temp != NULL) {
    printf("%d ", temp->data);
    temp = temp->next;
  }
  printf("\n");
}

// Main function
int main() {
  // Include the header file <stddef.h>, which defines the NULL constant
  #include <stddef.h>

  // Declare the variables element and dequeued_element outside of the loops
  int element;
  int dequeued_element;

  // Create a queue
  QUEUE q;
  q.front = NULL;
  q.rear = NULL;

  // Display the menu
  printf("Queue operations:\n");
  printf("1. Insert\n");
  printf("2. Delete\n");
  printf("3. Print queue\n");
  printf("4. Exit\n");

  // Get the user's choice
  int choice;
  printf("Enter your choice: ");
  scanf("%d", &choice);

  // Perform the selected operation
  while (choice != 4) {
    switch (choice) {
      case 1:
        // Insert an element
        printf("Enter the element to insert: ");
        scanf("%d", &element);
        insert(&q, element);
        break;

      case 2:
        // Delete an element
        dequeued_element = delete(&q);
        if (dequeued_element == -1) {
          printf("Queue is empty.\n");
        } else {
          printf("Deleted element: %d\n", dequeued_element);
        }
        break;

      case 3:
        // Print the queue
        printQueue(&q);
        break;

      default:
        printf("Invalid choice.\n");
    }

    // Get the user's choice again
    printf("Enter your choice: ");
    scanf("%d", &choice);
  }

  // Free the memory allocated to the queue
