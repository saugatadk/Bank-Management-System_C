#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>

#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define BLUE "\x1B[34m"
#define CYAN "\x1B[36m"
#define RESET "\x1B[0m"

struct bankaccount{
    int account_number;
    char account_holder[50];
    char password[50];
    int pin;
    float balance;
}acc[100];

int count =0;

//Function declaration
void create(struct bankaccount acc[], int *num);//num= number of accounts
void deposit(struct bankaccount acc[],  int num);
void withdraw(struct bankaccount acc[], int num);
void transfer(struct bankaccount acc[], int num);
void display(struct bankaccount acc[], int num);
void transaction_detail(struct bankaccount acc[], int num);
void confidential(struct bankaccount acc[], int num);//access password= 404
void deleteAccount(struct bankaccount acc[], int *num);


void divider(){
    for(int i=0; i<40; i++){
        printf("-");
    }
}

void clearAccountData() {
    FILE *ptr = fopen("bank.txt", "w");
    fclose(ptr);
    FILE *ptr1 = fopen("account.txt","w");
    fclose(ptr1);
}

//main function
int main(){
    int choice;
    int num=0;
    clearAccountData();//clears previous operating data
    while(1){
    system("cls");
    printf(CYAN"\n BANK MANAGEMENT SYSTEM \n"RESET);
    divider();
    printf(GREEN"\n1. Create an Account\n");
    printf("2. Deposit Funds\n");
    printf("3. Withdraw Funds\n");
    printf("4. Transfer Funds\n");
    printf(BLUE"5. Display Account Details\n");
    printf("6. Transaction Details\n"RESET);
    printf("7.*Confidential Data*\n");
    printf(RED"8. Delete Account\n");
    printf("9. Exit\n"RESET);

    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch(choice){
        case 1: system("cls");
                create(acc, &num);
            break;
        case 2: system("cls");
                deposit(acc, num);
            break;
        case 3: system("cls");
                withdraw(acc, num);
            break;
        case 4: system("cls");
                transfer(acc, num);
            break;
        case 5: system("cls");
                display(acc, num);
            break;
        case 6: system("cls");
                transaction_detail(acc, num);
            break;
        case 7: system("cls");
                confidential(acc, num);
            break;
        case 8:
                system("cls");
                deleteAccount(acc, &num);
                break;
        case 9: system("cls");
                printf(CYAN"Exiting the program..."RESET);
                exit(0);
            break;
        default: 
        printf(RED"INVALID INPUT.\n PLEASE TRY AGAIN\n"RESET);
    }
    } 
    return 0;
}

void create(struct bankaccount acc[], int *num){
    struct bankaccount newaccount;
    if (*num>= 100) {
        printf(RED"Cannot create more accounts. The maximum limit has been reached.\n"RESET);
        return;
    }
    FILE *ptr,*ptr1;
    ptr =fopen("bank.txt","a");
    ptr1 =fopen("account.txt","a");

    system("cls");
    printf(CYAN"\nACCOUNT CREATION\n"RESET);
    divider();
    printf("\nEnter Account Number: ");
    scanf("%d",&newaccount.account_number);
    printf("Enter Account Holder's Name: ");
    scanf(" %[^\n]", newaccount.account_holder);
    printf("Enter Account Password: ");
    scanf(" %[^\n]", newaccount.password);
    printf("Enter 4-digit Pin For Transaction: ");
    scanf("%d", &newaccount.pin);
    printf("Enter Initial Balance: ");
    scanf("%f",&newaccount.balance);
    
    acc[*num] = newaccount;
    (*num)++;

    fprintf(ptr1,"Account Number: %d\nAccount Holder's Name: %s\nAccount Password: %s\n4-digit Pin:%d\nInitialbalance:%0.2f\n\n",newaccount.account_number,newaccount.account_holder,newaccount.password,newaccount.pin,newaccount.balance);
    fprintf(ptr,"Initial balance for Account %d has been set to NPR %0.2f\n\n",newaccount.account_number,newaccount.balance);
    fclose(ptr1);
    fclose(ptr);

    printf(GREEN"\nAccount created successfully!\n"RESET);
    printf("\n");
    printf("Press any key...");
    getch();
}

void deposit(struct bankaccount acc[], int num){
    system("cls");
    printf(CYAN"\nDEPOSITING AMOUNT\n"RESET);
    divider();
    time_t tm;
    time(&tm);
    FILE *ptr= fopen("bank.txt","a");
    int acc_num;
    float amt;
    int found = 0; //(0=false, 1=true)

    printf("\nEnter account number: ");
    scanf("%d", &acc_num);

    for(int i=0; i<num; i++){
        if(acc[i].account_number == acc_num){
            found=1;
            printf("Enter the amount to deposit: ");
            scanf("%f",&amt);

            acc[i].balance +=amt;
            printf(GREEN"Deposit Successful.\nUpdated balance: %0.2f\n"RESET,acc[i].balance);
            fprintf(ptr,"Your %d## has been Credited by NPR %0.2f on %s",acc_num,amt,ctime(&tm));
            fprintf(ptr,"Remarks:Deposit. Download MoBank - http://bit.ly/MoBank4.\nADHIKARI BANK\n\n");
            fclose(ptr);
            count++;
            break;
        }
        if(found==0){
            printf(RED"Account is not Found.Please check account number and password.\n"RESET);
        }
    }
    printf("\n");
    printf("Press any key...");
    getch();
}

void withdraw(struct bankaccount acc[], int num){
    int acc_num;
    char acc_pass[50];
    float amt;
    int pin;
    int found =0;
    time_t tm;
    time(&tm);
    FILE *ptr= fopen("bank.txt","a");
   
    system("cls");
    printf(CYAN"\nWITHDRAWING AMOUNT\n"RESET);
    divider();
    printf("\nEnter your account number: ");
    scanf("%d",&acc_num);
    printf("Enter your password: ");
    scanf(" %[^\n]", acc_pass);
    
    for(int i=0; i<num; i++){
        if(acc[i].account_number == acc_num && strcmp(acc[i].password, acc_pass)==0){
            found=1;
            printf("Enter amount to withdraw: ");
            scanf("%f", &amt);
            printf("Enter your 4-digit pin: ");
            scanf("%d", &pin);
            if(acc[i].pin==pin){
                if (amt>acc[i].balance){
                    printf("Insufficient Balance.");
                }else{
                    acc[i].balance-=amt;
                    printf(GREEN"Withdrawal Successful!\n");
                    printf("Updated balance is: %0.2f\n"RESET,acc[i].balance);
                    }
                }
            else{
                    printf(RED"INVALID PIN!\n"RESET);
                }
                fprintf(ptr,"Your %d## has been Debited by NPR %0.2f on %s",acc_num,amt,ctime(&tm));
                fprintf(ptr,"Remarks:Withdraw. Download MoBank - http://bit.ly/MoBank4.\nADHIKARI BANK\n\n");
                fclose(ptr);
                count++;
                break;
            }
        if(found==0){
            printf(RED"Account Not Found! Please Check Your account number and password\n"RESET);
        }
        
        }
        printf("\n");
        printf("Press any key...");
        getch();
        
    }
    
    void display(struct bankaccount acc[], int num) {
    int acc_num;
    char acc_pass[50];
    int found =0;
    
    system("cls");
    printf(CYAN"\nDiplaying Account Details\n"RESET);
    divider();
    printf("\nEnter account number: ");
    scanf("%d", &acc_num);
    printf("Enter account passsword: ");
    scanf(" %[^\n]", &acc_pass);

    for (int i = 0; i < num; i++) {
        if (acc[i].account_number == acc_num && strcmp(acc[i].password,acc_pass)==0) {
            found = 1;
            printf("\n");
            printf(GREEN"Account Number: %d\n", acc[i].account_number);
            printf("Account Holder: %s\n", acc[i].account_holder);
            printf("Account Balance: %.2f\n"RESET, acc[i].balance);
           
            break;
        }
    }
    printf("\n");
    if (found==0) {
        printf(RED"Account not found. Please check the account number and password.\n"RESET);
    }
    printf("\n");
    printf("Press any key...");
    getch();
}

void transfer(struct bankaccount acc[], int num){
    int acc_num;
    int acc_rec;
    char acc_pass[50];
    float amt;
    int pin;
    int found =0;
    
    time_t tm;
    time(&tm);
    FILE *ptr= fopen("bank.txt","a");

    system("cls");
    printf(CYAN"\nTRANSFERING MONEY\n"RESET);
    divider();
    printf("\nEnter your account number: ");
    scanf("%d",&acc_num);
    printf("Enter your password: ");
    scanf(" %[^\n]", acc_pass);
    //update sender's account balance
    for(int i=0; i<num; i++){
        if(acc[i].account_number == acc_num && strcmp(acc[i].password, acc_pass)==0){
            found=1;
            printf("Enter the account number of receiver: ");
            scanf(" %d", &acc_rec);
            printf("Enter amount to transfer: ");
            scanf("%f", &amt);
            printf("Enter your 4-digit pin: ");
            scanf("%d", &pin);
            if(acc[i].pin==pin){
                if (amt>acc[i].balance){
                    printf(RED"Insufficient Balance."RESET);
                }else{
                    acc[i].balance-=amt;
                    printf(GREEN"Transfer Successful to Account number %d.\n",acc_rec);
                    printf("Updated balance is: %0.2f\n"RESET,acc[i].balance);
                    }
                }
            else{
                    printf(RED"INVALID PIN!\n"RESET);
                }
                fprintf(ptr,"Your %d## has been Debited by NPR %0.2f on %s",acc_num,amt,ctime(&tm));
                fprintf(ptr,"Remarks:Transfer to acc %d##. Download MoBank - http://bit.ly/MoBank4.\nADHIKARI BANK\n\n",acc_rec);
                count ++;
                break;
            }
        if(found!=0){
            printf(RED"Account Not Found! Please Check Your account number and password\n"RESET);
        }
        
    }
    //updating the reciever's account balance
    for (int i = 0; i < num; i++) {
        if (acc[i].account_number == acc_rec) {
            acc[i].balance += amt;
            fprintf(ptr, "Your %d## has been Credited by NPR %.2f on %s", acc_rec, amt, ctime(&tm));
            fprintf(ptr,"Remarks:Transfer from acc %d##. Download MoBank - http://bit.ly/MoBank4.\nADHIKARI BANK\n\n",acc_num);
            fclose(ptr);
            break;
        }
    }
        printf("\n");
        printf("Press any key...");
        getch();
}

void transaction_detail(struct bankaccount acc[], int num){
    FILE *ptr;
    ptr = fopen("bank.txt", "r");

    system("cls");
    printf(CYAN"\nTRANSACTION DETAILS\n"RESET);
    divider();
    
    printf("\nTOTAL TRANSACTIONS DONE: %d\n\n",count);
    char ch= fgetc(ptr);
    if (ch == EOF){
        printf(RED"No recent transactions\n"RESET);

    }else{
        while( ch!= EOF){
            printf("%c",ch);
            ch=fgetc(ptr);
        }
    }
    fclose(ptr);
    printf("Press any key...");
    getch();
}

void confidential(struct bankaccount acc[], int num){
    FILE *ptr1;
    ptr1 = fopen("account.txt", "r");

    system("cls");
    printf(CYAN"\nCONFIDENTIAL DATA\n"RESET);
    divider();
    
    int pass;
    printf("\nEnter password for ACCESS: ");
    scanf("%d", &pass);
    if(pass==404){

    char ch= fgetc(ptr1);
    
    if (ch == EOF){
        printf(RED"No data available\n"RESET);

    }else{
        while( ch!= EOF){
            printf("%c",ch);
            ch=fgetc(ptr1);
        }
    }
    fclose(ptr1);
    }
    else{
        printf(RED"ACCESS DENIED!\n"RESET);
    }
    printf("Press any key...");
    getch();
}

void deleteAccount(struct bankaccount acc[], int *num) {
    int acc_num;
    printf(CYAN"Enter account number to delete: "RESET);
    scanf("%d", &acc_num);
    int found= 0;

    // Search for the account with the given account number
    for (int i = 0; i < *num; i++) {
        if (acc[i].account_number == acc_num) {
            found = i + 1; // Store the index of the found account
            break;
        }
    }
    if (found != 0) {
        // Shift the accounts to remove the deleted account
        for (int i = found - 1; i < (*num - 1); i++) {
            acc[i] = acc[i + 1];
        }

        (*num)--;

        printf("Account %d deleted successfully!\n", acc_num);
    } 
    else {
        printf(RED"Account not found. Please check the account number.\n"RESET);
    }
    printf("\n");
    printf("Press any key...");
    getch(); 
}
