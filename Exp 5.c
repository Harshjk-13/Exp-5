#include <stdio.h>
#include <stdlib.h>

// Node structure definition
struct Node {
    int data;
    struct Node* next;
};

// Circular Queue structure definition
struct CircularQueue {
    struct Node* front;
    struct Node* rear;
};

// Function to initialize the circular queue
void initQueue(struct CircularQueue* q) {
    q->front = NULL;
    q->rear = NULL;
}

// Function to check if the queue is empty
int isEmpty(struct CircularQueue* q) {
    return q->front == NULL;
}

// Function to add an element to the circular queue (enqueue operation)
void enqueue(struct CircularQueue* q, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Memory allocation error! Cannot enqueue %d.\n", value);
        return;
    }
    newNode->data = value;
    newNode->next = NULL;

    if (isEmpty(q)) {
        q->front = newNode;
        q->rear = newNode;
        newNode->next = newNode;  // Circular link
    } else {
        newNode->next = q->front;  // Point the new node to the front node
        q->rear->next = newNode;   // Point the old rear node to the new node
        q->rear = newNode;         // Update the rear to the new node
    }
    printf("Enqueued %d to queue.\n", value);
}

// Function to remove and return an element from the circular queue (dequeue operation)
int dequeue(struct CircularQueue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty! Cannot dequeue element.\n");
        return -1;  // Return -1 as an error code for underflow
    }

    int dequeued_value;
    struct Node* temp = q->front;

    if (q->front == q->rear) {  // Queue has only one element
        dequeued_value = temp->data;
        q->front = NULL;
        q->rear = NULL;
    } else {
        dequeued_value = temp->data;
        q->front = q->front->next;  // Move the front to the next node
        q->rear->next = q->front;   // Maintain the circular link
    }

    free(temp);  // Free the memory of the dequeued node
    printf("Dequeued %d from queue.\n", dequeued_value);
    return dequeued_value;
}

// Function to return the front element of the circular queue without removing it
int peek(struct CircularQueue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty! Cannot peek.\n");
        return -1;
    } else {
        return q->front->data;
    }
}

// Function to display the elements of the circular queue
void display(struct CircularQueue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }

    struct Node* temp = q->front;
    printf("Queue elements: ");
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != q->front);
    printf("\n");
}

// Main function to demonstrate circular queue operations using linked list
int main() {
    struct CircularQueue q;
    initQueue(&q);  // Initialize the queue

    // Demonstrate enqueue operation
    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    enqueue(&q, 40);
    enqueue(&q, 50);

    // Display queue elements
    display(&q);

    // Demonstrate dequeue operation
    dequeue(&q);
    dequeue(&q);

    // Display queue elements after dequeuing
    display(&q);

    // Peek at the front element
    printf("Front element: %d\n", peek(&q));

    // Enqueue more elements to test circular behavior
    enqueue(&q, 60);
    enqueue(&q, 70);

    // Display queue elements again
    display(&q);

    return 0;
}
