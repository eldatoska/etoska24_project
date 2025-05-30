#include <stdio.h>
#include <stdlib.h>

// Define a node in the linked list
typedef struct Node {
    int bookID;
    struct Node* next;
} Node;

// Function to add book to the end of the list
void addEnd(Node** head, int bookID) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->bookID = bookID;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
    } else {
        Node* temp = *head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
    }
}

// Function to remove books from the end
void removeLastK(Node** head, int k) {
    int count = 0;
    Node* temp = *head;

    // Count total nodes
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }

    // If k >= count, delete all nodes
    if (k >= count) {
        while (*head != NULL) {
            Node* toDelete = *head;
            *head = (*head)->next;
            free(toDelete);
        }
        return;
    }

    // Find (count - k)th node
    temp = *head;
    for (int i = 1; i < count - k; i++) {
        temp = temp->next;
    }

    // Delete the rest
    Node* toDelete = temp->next;
    temp->next = NULL;
    while (toDelete != NULL) {
        Node* next = toDelete->next;
        free(toDelete);
        toDelete = next;
    }
}

// Function to print the list
void printList(Node* head) {
    if (head == NULL) {
        printf("0\n");
        return;
    }

    while (head != NULL) {
        printf("%d", head->bookID);
        if (head->next != NULL)
            printf(" ");
        head = head->next;
    }
    printf("\n");
}

int main() {
    int n;
    scanf("%d", &n);

    Node* desktop = NULL;

    for (int i = 0; i < n; i++) {
        char op;
        scanf(" %c", &op);

        if (op == 'P') {
            int m, id;
            scanf("%d", &m);
            for (int j = 0; j < m; j++) {
                scanf("%d", &id);
                addEnd(&desktop, id);
            }
        } else if (op == 'R') {
            int k;
            scanf("%d", &k);
            removeLastK(&desktop, k);
        }
    }

    printList(desktop);

    // Free memory
    while (desktop != NULL) {
        Node* next = desktop->next;
        free(desktop);
        desktop = next;
    }

    return 0;
}

