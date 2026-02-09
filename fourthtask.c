#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "accounts.dat"
#define MAX 100

typedef struct {
    int accNo;
    char name[50];
    float balance;
} Account;

Account accounts[MAX];
int count = 0;

void load() {
    FILE *f = fopen(FILENAME, "rb");
    if(f) {
        fread(&count, sizeof(int), 1, f);
        fread(accounts, sizeof(Account), count, f);
        fclose(f);
    }
}

void save() {
    FILE *f = fopen(FILENAME, "wb");
    fwrite(&count, sizeof(int), 1, f);
    fwrite(accounts, sizeof(Account), count, f);
    fclose(f);
}

int find(int accNo) {
    for(int i=0; i<count; i++)
        if(accounts[i].accNo == accNo)
            return i;
    return -1;
}

void create() {
    if(count >= MAX) {
        printf("Max accounts reached!\n");
        return;
    }
    
    printf("Enter account number: ");
    scanf("%d", &accounts[count].accNo);
    
    if(find(accounts[count].accNo) != -1) {
        printf("Account already exists!\n");
        return;
    }
    
    printf("Enter name: ");
    scanf("%s", accounts[count].name);
    
    printf("Enter initial deposit: ");
    scanf("%f", &accounts[count].balance);
    
    count++;
    save();
    printf("Account created!\n");
}

void deposit() {
    int accNo;
    float amount;
    
    printf("Enter account number: ");
    scanf("%d", &accNo);
    
    int idx = find(accNo);
    if(idx == -1) {
        printf("Account not found!\n");
        return;
    }
    
    printf("Enter amount to deposit: ");
    scanf("%f", &amount);
    
    accounts[idx].balance += amount;
    save();
    printf("Deposit successful! New balance: %.2f\n", accounts[idx].balance);
}

void withdraw() {
    int accNo;
    float amount;
    
    printf("Enter account number: ");
    scanf("%d", &accNo);
    
    int idx = find(accNo);
    if(idx == -1) {
        printf("Account not found!\n");
        return;
    }
    
    printf("Enter amount to withdraw: ");
    scanf("%f", &amount);
    
    if(amount > accounts[idx].balance) {
        printf("Insufficient balance!\n");
        return;
    }
    
    accounts[idx].balance -= amount;
    save();
    printf("Withdrawal successful! New balance: %.2f\n", accounts[idx].balance);
}

void balance() {
    int accNo;
    
    printf("Enter account number: ");
    scanf("%d", &accNo);
    
    int idx = find(accNo);
    if(idx == -1) {
        printf("Account not found!\n");
        return;
    }
    
    printf("\nAccount Number: %d\n", accounts[idx].accNo);
    printf("Account Holder: %s\n", accounts[idx].name);
    printf("Balance: %.2f\n", accounts[idx].balance);
}

void display() {
    if(count == 0) {
        printf("No accounts!\n");
        return;
    }
    
    printf("\n%-10s %-20s %-10s\n", "Acc No", "Name", "Balance");
    printf("----------------------------------------\n");
    for(int i=0; i<count; i++)
        printf("%-10d %-20s %-10.2f\n", 
               accounts[i].accNo, 
               accounts[i].name, 
               accounts[i].balance);
}

int main() {
    int choice;
    load();
    
    do {
        printf("\n=== BANK SYSTEM ===\n");
        printf("1. Create Account\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Balance Enquiry\n");
        printf("5. Display All\n");
        printf("6. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: create(); break;
            case 2: deposit(); break;
            case 3: withdraw(); break;
            case 4: balance(); break;
            case 5: display(); break;
            case 6: save(); printf("Goodbye!\n"); break;
            default: printf("Invalid!\n");
        }
    } while(choice != 6);
    
    return 0;
}