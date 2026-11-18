#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Définition d'un nœud de la liste chaînée
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Fonction pour ajouter un élément en fin de liste
void append(Node** head_ref, int new_data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    Node* last = *head_ref;
    
    new_node->data = new_data;
    new_node->next = NULL;

    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }

    while (last->next != NULL) {
        last = last->next;
    }

    last->next = new_node;
}

// Fonction pour afficher la liste
void printList(Node* node) {
    printf("[ ");
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("]\n");
}

// Tri à bulles sur la liste chaînée
void sortList(Node* head) {
    if (head == NULL) return;
    int swapped;
    Node* ptr1;
    Node* lptr = NULL;

    do {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (ptr1->data > ptr1->next->data) {
                int temp = ptr1->data;
                ptr1->data = ptr1->next->data;
                ptr1->next->data = temp;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

// Libération de la mémoire (crucial pour éviter les fuites)
void freeList(Node* head) {
    Node* tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

int main() {
    Node* head = NULL;
    srand((unsigned int)time(NULL));

    printf("--- Test Avance : Listes chainees et Allocation Dynamique ---\n");
    printf("Generation de 10 nombres aleatoires...\n");

    for (int i = 0; i < 10; i++) {
        int val = rand() % 100;
        append(&head, val);
    }

    printf("Liste initiale non triee :\n");
    printList(head);

    printf("Tri de la liste en cours...\n");
    sortList(head);

    printf("Liste finale triee par ordre croissant :\n");
    printList(head);

    // Nettoyage de la mémoire
    freeList(head);
    printf("Memoire liberee avec succes. Test reussi !\n");

    return 0;
}