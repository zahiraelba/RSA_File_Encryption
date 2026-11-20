#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Include all teammate modules
#include "rsa.h"
#include "keys.h"
#include "file_handler.h"

// Function prototypes as requested in the image
void display_menu();
void generate_option();
void encrypt_option();
void decrypt_option();

int main() {
    int choice = 0;

    printf("===== RSA PROJECT =====\n");

    // Loop until user chooses Exit
    while (choice != 4) {
        display_menu();
        printf("Your choice: ");
        
        // Read user choice
        if (scanf("%d", &choice) != 1) {
            // Clear the input buffer if a letter is typed
            while (getchar() != '\n'); 
            printf("Invalid choice. Please enter a number.\n\n");
            continue;
        }

        switch (choice) {
            case 1:
                generate_option();
                break;
            case 2:
                encrypt_option();
                break;
            case 3:
                decrypt_option();
                break;
            case 4:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please select 1, 2, 3, or 4.\n\n");
        }
    }

    return 0;
}

// 1. Display Menu
void display_menu() {
    printf("\n--- MENU ---\n");
    printf("1. Generate RSA keys\n");
    printf("2. Encrypt a file\n");
    printf("3. Decrypt a file\n");
    printf("4. Exit\n");
}

// 2. Generate Option
void generate_option() {
    int p, q, n, e, d;

    printf("\n[INFO] Generating RSA keys...\n");
    
    // Call Personne 2's function to generate keys
    if (generer_cles(&p, &q, &n, &e, &d) == 1) {
        // Call Personne 2's function to save them
        if (sauvegarder_cles(n, e, d) == 1) {
            printf("[SUCCESS] Keys generated and saved to public.key and private.key\n");
        } else {
            printf("[ERROR] Failed to save keys to files.\n");
        }
    } else {
        printf("[ERROR] Failed to generate keys.\n");
    }
    printf("\n");
}

// 3. Encrypt Option
void encrypt_option() {
    char source[256];
    char destination[256];
    
    // Variables to hold the keys loaded from the file
    int n, e, d;
    FILE *file;

    printf("\n[INFO] --- Encryption ---\n");
    
    // Load the public key
    file = fopen("public.key", "r");
    if (file == NULL) {
        printf("[ERROR] public.key not found. Please generate keys first (Option 1).\n\n");
        return;
    }
    // Read n and e from the file
    if (fscanf(file, "%d %d", &n, &e) != 2) {
        printf("[ERROR] Invalid public.key format.\n\n");
        fclose(file);
        return;
    }
    fclose(file);

    // Ask for the files
    printf("Enter source file to encrypt: ");
    scanf("%255s", source); // Read a string without spaces
    printf("Enter destination file (e.g., secret.enc): ");
    scanf("%255s", destination);

    // Call Personne 3's function
    printf("\n[INFO] Encrypting...\n");
    if (chiffrer_fichier(source, destination, e, n) == 1) {
        printf("[SUCCESS] File encrypted successfully.\n\n");
    } else {
        printf("[ERROR] Encryption failed.\n\n");
    }
}

// 4. Decrypt Option
void decrypt_option() {
    char source[256];
    char destination[256];
    
    // Variables to hold the keys loaded from the file
    int n, e, d;
    FILE *file;

    printf("\n[INFO] --- Decryption ---\n");
    
    // Load the private key
    file = fopen("private.key", "r");
    if (file == NULL) {
        printf("[ERROR] private.key not found. Please generate keys first (Option 1).\n\n");
        return;
    }
    // Read n and d from the file
    if (fscanf(file, "%d %d", &n, &d) != 2) {
        printf("[ERROR] Invalid private.key format.\n\n");
        fclose(file);
        return;
    }
    fclose(file);

    // Ask for the files
    printf("Enter source file to decrypt (e.g., secret.enc): ");
    scanf("%255s", source);
    printf("Enter destination file (e.g., secret.txt): ");
    scanf("%255s", destination);

    // Call Personne 3's function
    printf("\n[INFO] Decrypting...\n");
    if (dechiffrer_fichier(source, destination, d, n) == 1) {
        printf("[SUCCESS] File decrypted successfully.\n\n");
    } else {
        printf("[ERROR] Decryption failed.\n\n");
    }
}