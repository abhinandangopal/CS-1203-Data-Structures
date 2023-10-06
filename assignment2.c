#include <stdio.h>
#include <stdlib.h>

struct Node {
  int data;
  struct Node *left;
  struct Node *right;
};

struct Stack {
  struct Node *data[100];
  int top;
};

void initStack(struct Stack *s) {
  s->top = -1;
}

int isEmptyStack(struct Stack *s) {
  return s->top == -1;
}

void pushStack(struct Stack *s, struct Node *node) {
  s->top++;
  s->data[s->top] = node;
}

struct Node *popStack(struct Stack *s) {
  if (isEmptyStack(s)) {
    return NULL;
  }

  struct Node *node = s->data[s->top];
  s->top--;
  return node;
}

struct Node *newNode(int data) {
  struct Node *node = malloc(sizeof(struct Node));
  node->data = data;
  node->left = NULL;
  node->right = NULL;
  return node;
}

void inorderTraversal(struct Node *root) {
  struct Stack s;
  initStack(&s);

  struct Node *current = root;
  while (current != NULL || !isEmptyStack(&s)) {
    if (current != NULL) {
      pushStack(&s, current);
      current = current->left;
    } else {
      current = popStack(&s);
      printf("%d ", current->data);
      current = current->right;
    }
  }
}

int main() {
  struct Node *root = newNode(1);
  root->left = newNode(2);
  root->right = newNode(3);

  inorderTraversal(root);

  return 0;
}
