#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_ACCOUNTS 100
#define MAX_NAME_LENGTH 50
#define MAX_ADDRESS_LENGTH 100
#define PIN_LENGTH 4
#define FILENAME "bank_data.txt"
#define MIN_AGE 18

// Account status enumeration
typedef enum {
    ACTIVE,
    CLOSED,
    FROZEN
} AccountStatus;

// Account type enumeration
typedef enum {
    SAVINGS,
    CURRENT,
    INVESTMENT_ACCOUNT
} AccountType;

// User role enumeration
typedef enum {
    ADMIN,
    CUSTOMER
} UserRole;

// Account structure
typedef struct {
    int accountNumber;
    char holderName[MAX_NAME_LENGTH];
    int age;
    char address[MAX_ADDRESS_LENGTH];
    char phone[15];
    AccountType accountType;
    double balance;
    AccountStatus status;
    double loanBalance;
    double investmentBalance;
    char pin[PIN_LENGTH + 1];
    UserRole role;
} Account;

// Transaction structure
typedef struct {
    int accountNumber;
    char date[11];
    char time[6];
    char description[50];
    double amount;
    double balanceAfter;
} Transaction;

// Global variables
Account accounts[MAX_ACCOUNTS];
Transaction transactions[MAX_ACCOUNTS * 10]; // Allow 10 transactions per account
int accountCount = 0;
int transactionCount = 0;
Account* currentUser = NULL;

// Function prototypes
void initializeSystem();
void mainMenu();
void adminMenu();
void customerMenu();
void registerAccount();
void createAccount();
void viewAllAccounts();
void searchByAccountNumber();
void updateAccountStatus();
void depositMoney();
void withdrawMoney();
void transferMoney();
void applyForLoan();
void repayLoan();
void viewLoanStatus();
void investMoney();
void withdrawInvestment();
void viewInvestmentPortfolio();
void calculateTotalBankBalance();
void calculateTotalLoans();
void calculateTotalInvestments();
void viewTransactionHistory();
void changePIN();
void saveToFile();
void loadFromFile();
void exitProgram();

// Helper functions
int isAccountNumberUnique(int accountNumber);
int findAccountIndex(int accountNumber);
void printAccountDetails(Account account);
const char* getAccountTypeName(AccountType type);
const char* getAccountStatusName(AccountStatus status);
void generateAccountNumber(char* pin);
int verifyPIN(int accountNumber, const char* pin);
void addTransaction(int accountNumber, const char* description, double amount, double balanceAfter);
void displayWelcomeMessage();
int getCurrentYear();
int isValidDate(int day, int month, int year);
int calculateAge(int day, int month, int year);

int main() {
    displayWelcomeMessage();
    initializeSystem();
    mainMenu();
    return 0;
}

void displayWelcomeMessage() {
    printf("=============================================\n");
    printf("    WELCOME TO FINANCE HUB BANKING SYSTEM    \n");
    printf("=============================================\n");
    printf("    Secure • Reliable • Innovative Banking   \n");
    printf("=============================================\n\n");
}

void initializeSystem() {
    loadFromFile();
    printf("System Initialized Successfully\n");
    printf("Loaded %d accounts and %d transactions\n", accountCount, transactionCount);
}

void mainMenu() {
    int choice;
    
    do {
        printf("\n=== MAIN MENU ===\n");
        printf("1. Register New Account\n");
        printf("2. Login as Customer\n");
        printf("3. Login as Administrator\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }
        
        switch(choice) {
            case 1: registerAccount(); break;
            case 2: {
                int accountNumber;
                char pin[PIN_LENGTH + 1];
                
                printf("Enter your account number: ");
                scanf("%d", &accountNumber);
                
                printf("Enter your PIN: ");
                scanf("%s", pin);
                
                if (verifyPIN(accountNumber, pin)) {
                    int index = findAccountIndex(accountNumber);
                    if (index != -1) {
                        currentUser = &accounts[index];
                        customerMenu();
                    }
                } else {
                    printf("Invalid account number or PIN.\n");
                }
                break;
            }
            case 3: {
                char adminPin[PIN_LENGTH + 1];
                printf("Enter Administrator PIN: ");
                scanf("%s", adminPin);
                
                // Default admin PIN is "admin" but should be changed in production
                if (strcmp(adminPin, "admin") == 0) {
                    adminMenu();
                } else {
                    printf("Invalid Administrator PIN.\n");
                }
                break;
            }
            case 0: exitProgram(); break;
            default: printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 0);
}

void adminMenu() {
    int choice;
    
    do {
        printf("\n=== ADMINISTRATOR MENU ===\n");
        printf("1. View All Accounts\n");
        printf("2. Search Account by Number\n");
        printf("3. Update Account Status\n");
        printf("4. Total Bank Balance\n");
        printf("5. Total Outstanding Loans\n");
        printf("6. Total Investments\n");
        printf("7. View Transaction History\n");
        printf("0. Logout\n");
        printf("Enter your choice: ");
        
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: viewAllAccounts(); break;
            case 2: searchByAccountNumber(); break;
            case 3: updateAccountStatus(); break;
            case 4: calculateTotalBankBalance(); break;
            case 5: calculateTotalLoans(); break;
            case 6: calculateTotalInvestments(); break;
            case 7: viewTransactionHistory(); break;
            case 0: 
                printf("Logging out from administrator account.\n");
                currentUser = NULL;
                break;
            default: printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 0);
}

void customerMenu() {
    int choice;
    
    do {
        printf("\n=== CUSTOMER MENU ===\n");
        printf("Welcome, %s!\n", currentUser->holderName);
        printf("1. View Account Details\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Transfer Money\n");
        printf("5. Apply for Loan\n");
        printf("6. Repay Loan\n");
        printf("7. View Loan Status\n");
        printf("8. Invest Money\n");
        printf("9. Withdraw Investment\n");
        printf("10. View Investment Portfolio\n");
        printf("11. View Transaction History\n");
        printf("12. Change PIN\n");
        printf("0. Logout\n");
        printf("Enter your choice: ");
        
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: printAccountDetails(*currentUser); break;
            case 2: depositMoney(); break;
            case 3: withdrawMoney(); break;
            case 4: transferMoney(); break;
            case 5: applyForLoan(); break;
            case 6: repayLoan(); break;
            case 7: viewLoanStatus(); break;
            case 8: investMoney(); break;
            case 9: withdrawInvestment(); break;
            case 10: viewInvestmentPortfolio(); break;
            case 11: viewTransactionHistory(); break;
            case 12: changePIN(); break;
            case 0: 
                printf("Logging out. Thank you for banking with us!\n");
                currentUser = NULL;
                break;
            default: printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 0 && currentUser != NULL);
}

void registerAccount() {
    if (accountCount >= MAX_ACCOUNTS) {
        printf("Maximum account limit reached. Cannot create new account.\n");
        return;
    }
    
    Account newAccount;
    int typeChoice, day, month, year;
    double initialDeposit;
    char pin[PIN_LENGTH + 1], confirmPin[PIN_LENGTH + 1];
    
    printf("\n--- REGISTER NEW ACCOUNT ---\n");
    
    // Get personal information
    printf("Enter your full name: ");
    getchar(); // Clear input buffer
    fgets(newAccount.holderName, MAX_NAME_LENGTH, stdin);
    newAccount.holderName[strcspn(newAccount.holderName, "\n")] = 0; // Remove newline
    
    printf("Enter your date of birth (DD MM YYYY): ");
    scanf("%d %d %d", &day, &month, &year);
    
    // Validate date
    if (!isValidDate(day, month, year)) {
        printf("Invalid date of birth.\n");
        return;
    }
    
    // Calculate age
    newAccount.age = calculateAge(day, month, year);
    
    // Check if user is old enough
    if (newAccount.age < MIN_AGE) {
        printf("You must be at least %d years old to open an account.\n", MIN_AGE);
        return;
    }
    
    printf("Enter your address: ");
    getchar(); // Clear input buffer
    fgets(newAccount.address, MAX_ADDRESS_LENGTH, stdin);
    newAccount.address[strcspn(newAccount.address, "\n")] = 0; // Remove newline
    
    printf("Enter your phone number: ");
    scanf("%s", newAccount.phone);
    
    // Get account type
    printf("Select account type:\n");
    printf("1. Savings Account\n");
    printf("2. Current Account\n");
    printf("3. Investment Account\n");
    printf("Enter choice (1-3): ");
    scanf("%d", &typeChoice);
    
    switch(typeChoice) {
        case 1: newAccount.accountType = SAVINGS; break;
        case 2: newAccount.accountType = CURRENT; break;
        case 3: newAccount.accountType = INVESTMENT_ACCOUNT; break;
        default: 
            printf("Invalid choice. Setting to Savings by default.\n");
            newAccount.accountType = SAVINGS;
    }
    
    // Get initial deposit
    printf("Enter initial deposit: ");
    scanf("%lf", &initialDeposit);
    
    if (initialDeposit < 0) {
        printf("Initial deposit cannot be negative. Setting to 0.\n");
        initialDeposit = 0;
    }
    
    // Set up PIN
    printf("Set your 4-digit PIN: ");
    scanf("%s", pin);
    
    if (strlen(pin) != PIN_LENGTH) {
        printf("PIN must be exactly 4 digits.\n");
        return;
    }
    
    printf("Confirm your PIN: ");
    scanf("%s", confirmPin);
    
    if (strcmp(pin, confirmPin) != 0) {
        printf("PINs do not match. Account creation failed.\n");
        return;
    }
    
    strcpy(newAccount.pin, pin);
    
    // Generate account number (simple implementation)
    srand(time(NULL));
    newAccount.accountNumber = 100000 + rand() % 900000; // 6-digit account number
    
    // Initialize account
    newAccount.balance = initialDeposit;
    newAccount.loanBalance = 0.0;
    newAccount.investmentBalance = 0.0;
    newAccount.status = ACTIVE;
    newAccount.role = CUSTOMER;
    
    accounts[accountCount] = newAccount;
    accountCount++;
    
    printf("\nAccount created successfully!\n");
    printf("Your account number is: %d\n", newAccount.accountNumber);
    printf("Please remember this number for future logins.\n");
    
    // Add initial deposit transaction
    if (initialDeposit > 0) {
        addTransaction(newAccount.accountNumber, "Initial Deposit", initialDeposit, newAccount.balance);
    }
    
    printAccountDetails(newAccount);
}

void viewAllAccounts() {
    if (accountCount == 0) {
        printf("No accounts found.\n");
        return;
    }
    
    printf("\n--- All Accounts ---\n");
    printf("------------------------------------------------------------------------------------------------------------------------\n");
    printf("| %-12s | %-20s | %-10s | %-10s | %-10s | %-10s | %-8s | %-6s |\n", 
           "Account No", "Holder Name", "Type", "Balance", "Loan", "Investment", "Status", "Age");
    printf("------------------------------------------------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < accountCount; i++) {
        printf("| %-12d | %-20s | %-10s | %-10.2f | %-10.2f | %-10.2f | %-8s | %-6d |\n",
               accounts[i].accountNumber,
               accounts[i].holderName,
               getAccountTypeName(accounts[i].accountType),
               accounts[i].balance,
               accounts[i].loanBalance,
               accounts[i].investmentBalance,
               getAccountStatusName(accounts[i].status),
               accounts[i].age);
    }
    printf("------------------------------------------------------------------------------------------------------------------------\n");
}

void searchByAccountNumber() {
    int accountNumber;
    printf("Enter account number to search: ");
    scanf("%d", &accountNumber);
    
    int index = findAccountIndex(accountNumber);
    if (index == -1) {
        printf("Account not found.\n");
        return;
    }
    
    printf("\n--- Account Details ---\n");
    printAccountDetails(accounts[index]);
}

void updateAccountStatus() {
    int accountNumber, statusChoice;
    printf("Enter account number: ");
    scanf("%d", &accountNumber);
    
    int index = findAccountIndex(accountNumber);
    if (index == -1) {
        printf("Account not found.\n");
        return;
    }
    
    printf("Current status: %s\n", getAccountStatusName(accounts[index].status));
    printf("Select new status:\n");
    printf("1. Active\n");
    printf("2. Closed\n");
    printf("3. Frozen\n");
    printf("Enter choice (1-3): ");
    scanf("%d", &statusChoice);
    
    switch(statusChoice) {
        case 1: accounts[index].status = ACTIVE; break;
        case 2: accounts[index].status = CLOSED; break;
        case 3: accounts[index].status = FROZEN; break;
        default: 
            printf("Invalid choice. Status unchanged.\n");
            return;
    }
    
    printf("Account status updated successfully.\n");
    printAccountDetails(accounts[index]);
}

void depositMoney() {
    if (currentUser == NULL) {
        printf("You must be logged in to perform this operation.\n");
        return;
    }
    
    double amount;
    char pin[PIN_LENGTH + 1];
    
    printf("Enter amount to deposit: ");
    scanf("%lf", &amount);
    
    if (amount <= 0) {
        printf("Deposit amount must be positive.\n");
        return;
    }
    
    printf("Enter your PIN to confirm: ");
    scanf("%s", pin);
    
    if (strcmp(currentUser->pin, pin) != 0) {
        printf("Invalid PIN. Transaction cancelled.\n");
        return;
    }
    
    if (currentUser->status != ACTIVE) {
        printf("Cannot deposit to a %s account.\n", getAccountStatusName(currentUser->status));
        return;
    }
    
    currentUser->balance += amount;
    
    printf("Deposit successful. New balance: %.2f\n", currentUser->balance);
    addTransaction(currentUser->accountNumber, "Deposit", amount, currentUser->balance);
}

void withdrawMoney() {
    if (currentUser == NULL) {
        printf("You must be logged in to perform this operation.\n");
        return;
    }
    
    double amount;
    char pin[PIN_LENGTH + 1];
    
    printf("Enter amount to withdraw: ");
    scanf("%lf", &amount);
    
    if (amount <= 0) {
        printf("Withdrawal amount must be positive.\n");
        return;
    }
    
    printf("Enter your PIN to confirm: ");
    scanf("%s", pin);
    
    if (strcmp(currentUser->pin, pin) != 0) {
        printf("Invalid PIN. Transaction cancelled.\n");
        return;
    }
    
    if (currentUser->status != ACTIVE) {
        printf("Cannot withdraw from a %s account.\n", getAccountStatusName(currentUser->status));
        return;
    }
    
    if (amount > currentUser->balance) {
        printf("Insufficient funds. Current balance: %.2f\n", currentUser->balance);
        return;
    }
    
    currentUser->balance -= amount;
    printf("Withdrawal successful. New balance: %.2f\n", currentUser->balance);
    addTransaction(currentUser->accountNumber, "Withdrawal", -amount, currentUser->balance);
}

void transferMoney() {
    if (currentUser == NULL) {
        printf("You must be logged in to perform this operation.\n");
        return;
    }
    
    int toAccount;
    double amount;
    char pin[PIN_LENGTH + 1];
    
    printf("Enter destination account number: ");
    scanf("%d", &toAccount);
    
    int toIndex = findAccountIndex(toAccount);
    if (toIndex == -1) {
        printf("Destination account not found.\n");
        return;
    }
    
    printf("Enter amount to transfer: ");
    scanf("%lf", &amount);
    
    if (amount <= 0) {
        printf("Transfer amount must be positive.\n");
        return;
    }
    
    printf("Enter your PIN to confirm: ");
    scanf("%s", pin);
    
    if (strcmp(currentUser->pin, pin) != 0) {
        printf("Invalid PIN. Transaction cancelled.\n");
        return;
    }
    
    if (currentUser->status != ACTIVE) {
        printf("Cannot transfer from a %s account.\n", getAccountStatusName(currentUser->status));
        return;
    }
    
    if (accounts[toIndex].status != ACTIVE) {
        printf("Cannot transfer to a %s account.\n", getAccountStatusName(accounts[toIndex].status));
        return;
    }
    
    if (amount > currentUser->balance) {
        printf("Insufficient funds. Current balance: %.2f\n", currentUser->balance);
        return;
    }
    
    currentUser->balance -= amount;
    accounts[toIndex].balance += amount;
    
    printf("Transfer successful.\n");
    printf("Your new balance: %.2f\n", currentUser->balance);
    printf("Destination account new balance: %.2f\n", accounts[toIndex].balance);
    
    addTransaction(currentUser->accountNumber, "Transfer Out", -amount, currentUser->balance);
    addTransaction(toAccount, "Transfer In", amount, accounts[toIndex].balance);
}

void applyForLoan() {
    if (currentUser == NULL) {
        printf("You must be logged in to perform this operation.\n");
        return;
    }
    
    double amount;
    char pin[PIN_LENGTH + 1];
    
    printf("Enter loan amount: ");
    scanf("%lf", &amount);
    
    if (amount <= 0) {
        printf("Loan amount must be positive.\n");
        return;
    }
    
    printf("Enter your PIN to confirm: ");
    scanf("%s", pin);
    
    if (strcmp(currentUser->pin, pin) != 0) {
        printf("Invalid PIN. Transaction cancelled.\n");
        return;
    }
    
    if (currentUser->status != ACTIVE) {
        printf("Cannot apply for loan with a %s account.\n", getAccountStatusName(currentUser->status));
        return;
    }
    
    currentUser->balance += amount;
    currentUser->loanBalance += amount;
    
    printf("Loan approved and disbursed successfully.\n");
    printf("New balance: %.2f\n", currentUser->balance);
    printf("Loan balance: %.2f\n", currentUser->loanBalance);
    
    addTransaction(currentUser->accountNumber, "Loan Disbursement", amount, currentUser->balance);
}

void repayLoan() {
    if (currentUser == NULL) {
        printf("You must be logged in to perform this operation.\n");
        return;
    }
    
    double amount;
    char pin[PIN_LENGTH + 1];
    
    if (currentUser->loanBalance <= 0) {
        printf("No outstanding loan for this account.\n");
        return;
    }
    
    printf("Current loan balance: %.2f\n", currentUser->loanBalance);
    printf("Enter repayment amount: ");
    scanf("%lf", &amount);
    
    if (amount <= 0) {
        printf("Repayment amount must be positive.\n");
        return;
    }
    
    printf("Enter your PIN to confirm: ");
    scanf("%s", pin);
    
    if (strcmp(currentUser->pin, pin) != 0) {
        printf("Invalid PIN. Transaction cancelled.\n");
        return;
    }
    
    if (amount > currentUser->balance) {
        printf("Insufficient funds. Current balance: %.2f\n", currentUser->balance);
        return;
    }
    
    if (amount > currentUser->loanBalance) {
        printf("Repayment amount exceeds loan balance. Adjusting to full loan amount: %.2f\n", 
               currentUser->loanBalance);
        amount = currentUser->loanBalance;
    }
    
    currentUser->balance -= amount;
    currentUser->loanBalance -= amount;
    
    printf("Loan repayment successful.\n");
    printf("New balance: %.2f\n", currentUser->balance);
    printf("Remaining loan balance: %.2f\n", currentUser->loanBalance);
    
    addTransaction(currentUser->accountNumber, "Loan Repayment", -amount, currentUser->balance);
}

void viewLoanStatus() {
    if (currentUser == NULL) {
        printf("You must be logged in to perform this operation.\n");
        return;
    }
    
    printf("\n--- Loan Status ---\n");
    printf("Account Holder: %s\n", currentUser->holderName);
    printf("Account Number: %d\n", currentUser->accountNumber);
    printf("Outstanding Loan Balance: %.2f\n", currentUser->loanBalance);
}

void investMoney() {
    if (currentUser == NULL) {
        printf("You must be logged in to perform this operation.\n");
        return;
    }
    
    double amount;
    char pin[PIN_LENGTH + 1];
    
    printf("Current balance: %.2f\n", currentUser->balance);
    printf("Enter investment amount: ");
    scanf("%lf", &amount);
    
    if (amount <= 0) {
        printf("Investment amount must be positive.\n");
        return;
    }
    
    printf("Enter your PIN to confirm: ");
    scanf("%s", pin);
    
    if (strcmp(currentUser->pin, pin) != 0) {
        printf("Invalid PIN. Transaction cancelled.\n");
        return;
    }
    
    if (currentUser->status != ACTIVE) {
        printf("Cannot invest with a %s account.\n", getAccountStatusName(currentUser->status));
        return;
    }
    
    if (amount > currentUser->balance) {
        printf("Insufficient funds. Current balance: %.2f\n", currentUser->balance);
        return;
    }
    
    currentUser->balance -= amount;
    currentUser->investmentBalance += amount;
    
    printf("Investment successful.\n");
    printf("New balance: %.2f\n", currentUser->balance);
    printf("Investment balance: %.2f\n", currentUser->investmentBalance);
    
    addTransaction(currentUser->accountNumber, "Investment", -amount, currentUser->balance);
}

void withdrawInvestment() {
    if (currentUser == NULL) {
        printf("You must be logged in to perform this operation.\n");
        return;
    }
    
    double amount;
    char pin[PIN_LENGTH + 1];
    
    if (currentUser->investmentBalance <= 0) {
        printf("No investments to withdraw from this account.\n");
        return;
    }
    
    printf("Current investment balance: %.2f\n", currentUser->investmentBalance);
    printf("Enter withdrawal amount: ");
    scanf("%lf", &amount);
    
    if (amount <= 0) {
        printf("Withdrawal amount must be positive.\n");
        return;
    }
    
    printf("Enter your PIN to confirm: ");
    scanf("%s", pin);
    
    if (strcmp(currentUser->pin, pin) != 0) {
        printf("Invalid PIN. Transaction cancelled.\n");
        return;
    }
    
    if (amount > currentUser->investmentBalance) {
        printf("Insufficient investment funds. Current investment balance: %.2f\n", 
               currentUser->investmentBalance);
        return;
    }
    
    currentUser->balance += amount;
    currentUser->investmentBalance -= amount;
    
    printf("Investment withdrawal successful.\n");
    printf("New balance: %.2f\n", currentUser->balance);
    printf("Remaining investment balance: %.2f\n", currentUser->investmentBalance);
    
    addTransaction(currentUser->accountNumber, "Investment Withdrawal", amount, currentUser->balance);
}

void viewInvestmentPortfolio() {
    if (currentUser == NULL) {
        printf("You must be logged in to perform this operation.\n");
        return;
    }
    
    printf("\n--- Investment Portfolio ---\n");
    printf("Account Holder: %s\n", currentUser->holderName);
    printf("Account Number: %d\n", currentUser->accountNumber);
    printf("Investment Balance: %.2f\n", currentUser->investmentBalance);
    printf("Total Account Balance: %.2f\n", currentUser->balance);
}

void calculateTotalBankBalance() {
    double total = 0;
    
    for (int i = 0; i < accountCount; i++) {
        total += accounts[i].balance;
    }
    
    printf("\n--- Total Bank Balance ---\n");
    printf("Total balance across all accounts: %.2f\n", total);
}

void calculateTotalLoans() {
    double total = 0;
    
    for (int i = 0; i < accountCount; i++) {
        total += accounts[i].loanBalance;
    }
    
    printf("\n--- Total Outstanding Loans ---\n");
    printf("Total loans across all accounts: %.2f\n", total);
}

void calculateTotalInvestments() {
    double total = 0;
    
    for (int i = 0; i < accountCount; i++) {
        total += accounts[i].investmentBalance;
    }
    
    printf("\n--- Total Investments ---\n");
    printf("Total investments across all accounts: %.2f\n", total);
}

void viewTransactionHistory() {
    int accountNumber;
    
    if (currentUser != NULL && currentUser->role == CUSTOMER) {
        accountNumber = currentUser->accountNumber;
    } else {
        printf("Enter account number: ");
        scanf("%d", &accountNumber);
        
        int index = findAccountIndex(accountNumber);
        if (index == -1) {
            printf("Account not found.\n");
            return;
        }
    }
    
    printf("\n--- Transaction History for Account: %d ---\n", accountNumber);
    printf("Date       Time   Description                    Amount     Balance After\n");
    printf("------------------------------------------------------------------------\n");
    
    int found = 0;
    for (int i = 0; i < transactionCount; i++) {
        if (transactions[i].accountNumber == accountNumber) {
            printf("%s %s %-30s %9.2f %13.2f\n", 
                   transactions[i].date,
                   transactions[i].time,
                   transactions[i].description,
                   transactions[i].amount,
                   transactions[i].balanceAfter);
            found = 1;
        }
    }
    
    if (!found) {
        printf("No transactions found for this account.\n");
    }
    printf("------------------------------------------------------------------------\n");
}

void changePIN() {
    if (currentUser == NULL) {
        printf("You must be logged in to perform this operation.\n");
        return;
    }
    
    char oldPin[PIN_LENGTH + 1], newPin[PIN_LENGTH + 1], confirmPin[PIN_LENGTH + 1];
    
    printf("Enter your current PIN: ");
    scanf("%s", oldPin);
    
    if (strcmp(currentUser->pin, oldPin) != 0) {
        printf("Incorrect current PIN.\n");
        return;
    }
    
    printf("Enter your new 4-digit PIN: ");
    scanf("%s", newPin);
    
    if (strlen(newPin) != PIN_LENGTH) {
        printf("PIN must be exactly 4 digits.\n");
        return;
    }
    
    printf("Confirm your new PIN: ");
    scanf("%s", confirmPin);
    
    if (strcmp(newPin, confirmPin) != 0) {
        printf("PINs do not match.\n");
        return;
    }
    
    strcpy(currentUser->pin, newPin);
    printf("PIN changed successfully.\n");
}

void saveToFile() {
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    
    // Write account count first
    fprintf(file, "%d\n", accountCount);
    fprintf(file, "%d\n", transactionCount);
    
    // Write each account
    for (int i = 0; i < accountCount; i++) {
        fprintf(file, "%d\n", accounts[i].accountNumber);
        fprintf(file, "%s\n", accounts[i].holderName);
        fprintf(file, "%d\n", accounts[i].age);
        fprintf(file, "%s\n", accounts[i].address);
        fprintf(file, "%s\n", accounts[i].phone);
        fprintf(file, "%d\n", accounts[i].accountType);
        fprintf(file, "%.2f\n", accounts[i].balance);
        fprintf(file, "%d\n", accounts[i].status);
        fprintf(file, "%.2f\n", accounts[i].loanBalance);
        fprintf(file, "%.2f\n", accounts[i].investmentBalance);
        fprintf(file, "%s\n", accounts[i].pin);
        fprintf(file, "%d\n", accounts[i].role);
    }
    
    // Write each transaction
    for (int i = 0; i < transactionCount; i++) {
        fprintf(file, "%d\n", transactions[i].accountNumber);
        fprintf(file, "%s\n", transactions[i].date);
        fprintf(file, "%s\n", transactions[i].time);
        fprintf(file, "%s\n", transactions[i].description);
        fprintf(file, "%.2f\n", transactions[i].amount);
        fprintf(file, "%.2f\n", transactions[i].balanceAfter);
    }
    
    fclose(file);
    printf("Data saved to file successfully.\n");
}

void loadFromFile() {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("No existing data file found. Starting with empty database.\n");
        return;
    }
    
    // Read account count and transaction count
    fscanf(file, "%d", &accountCount);
    fscanf(file, "%d", &transactionCount);
    
    // Read each account
    for (int i = 0; i < accountCount; i++) {
        fscanf(file, "%d", &accounts[i].accountNumber);
        fscanf(file, " %[^\n]", accounts[i].holderName);
        fscanf(file, "%d", &accounts[i].age);
        fscanf(file, " %[^\n]", accounts[i].address);
        fscanf(file, "%s", accounts[i].phone);
        
        int type, status, role;
        fscanf(file, "%d", &type);
        accounts[i].accountType = (AccountType)type;
        
        fscanf(file, "%lf", &accounts[i].balance);
        
        fscanf(file, "%d", &status);
        accounts[i].status = (AccountStatus)status;
        
        fscanf(file, "%lf", &accounts[i].loanBalance);
        fscanf(file, "%lf", &accounts[i].investmentBalance);
        
        fscanf(file, "%s", accounts[i].pin);
        
        fscanf(file, "%d", &role);
        accounts[i].role = (UserRole)role;
    }
    
    // Read each transaction
    for (int i = 0; i < transactionCount; i++) {
        fscanf(file, "%d", &transactions[i].accountNumber);
        fscanf(file, "%s", transactions[i].date);
        fscanf(file, "%s", transactions[i].time);
        fscanf(file, " %[^\n]", transactions[i].description);
        fscanf(file, "%lf", &transactions[i].amount);
        fscanf(file, "%lf", &transactions[i].balanceAfter);
    }
    
    fclose(file);
    printf("Data loaded from file successfully.\n");
}

void exitProgram() {
    saveToFile();
    printf("Thank you for using the Banking & FinTech Management System. Goodbye!\n");
}

// Helper function implementations
int isAccountNumberUnique(int accountNumber) {
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            return 0;
        }
    }
    return 1;
}

int findAccountIndex(int accountNumber) {
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            return i;
        }
    }
    return -1;
}

void printAccountDetails(Account account) {
    printf("Account Number: %d\n", account.accountNumber);
    printf("Holder Name: %s\n", account.holderName);
    printf("Age: %d\n", account.age);
    printf("Address: %s\n", account.address);
    printf("Phone: %s\n", account.phone);
    printf("Account Type: %s\n", getAccountTypeName(account.accountType));
    printf("Balance: %.2f\n", account.balance);
    printf("Status: %s\n", getAccountStatusName(account.status));
    printf("Loan Balance: %.2f\n", account.loanBalance);
    printf("Investment Balance: %.2f\n", account.investmentBalance);
}

const char* getAccountTypeName(AccountType type) {
    switch(type) {
        case SAVINGS: return "Savings";
        case CURRENT: return "Current";
        case INVESTMENT_ACCOUNT: return "Investment";
        default: return "Unknown";
    }
}

const char* getAccountStatusName(AccountStatus status) {
    switch(status) {
        case ACTIVE: return "Active";
        case CLOSED: return "Closed";
        case FROZEN: return "Frozen";
        default: return "Unknown";
    }
}

void generateAccountNumber(char* pin) {
    srand(time(NULL));
    for (int i = 0; i < PIN_LENGTH; i++) {
        pin[i] = '0' + (rand() % 10);
    }
    pin[PIN_LENGTH] = '\0';
}

int verifyPIN(int accountNumber, const char* pin) {
    int index = findAccountIndex(accountNumber);
    if (index == -1) return 0;
    
    return (strcmp(accounts[index].pin, pin) == 0);
}

void addTransaction(int accountNumber, const char* description, double amount, double balanceAfter) {
    if (transactionCount >= MAX_ACCOUNTS * 10) {
        printf("Transaction history full. Oldest transactions will be overwritten.\n");
        // Simple implementation: shift all transactions left
        for (int i = 0; i < transactionCount - 1; i++) {
            transactions[i] = transactions[i + 1];
        }
        transactionCount--;
    }
    
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    
    Transaction newTransaction;
    newTransaction.accountNumber = accountNumber;
    strftime(newTransaction.date, 11, "%Y-%m-%d", tm_info);
    strftime(newTransaction.time, 6, "%H:%M", tm_info);
    strncpy(newTransaction.description, description, 50);
    newTransaction.amount = amount;
    newTransaction.balanceAfter = balanceAfter;
    
    transactions[transactionCount++] = newTransaction;
}

int getCurrentYear() {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    return tm_info->tm_year + 1900;
}

int isValidDate(int day, int month, int year) {
    if (year < 1900 || year > getCurrentYear()) return 0;
    if (month < 1 || month > 12) return 0;
    if (day < 1 || day > 31) return 0;
    
    // Check for months with 30 days
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
        return 0;
    
    // Check for February
    if (month == 2) {
        // Leap year check
        int isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (day > (28 + isLeap)) return 0;
    }
    
    return 1;
}

int calculateAge(int day, int month, int year) {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    
    int currentYear = tm_info->tm_year + 1900;
    int currentMonth = tm_info->tm_mon + 1;
    int currentDay = tm_info->tm_mday;
    
    int age = currentYear - year;
    
    // Adjust age if birthday hasn't occurred yet this year
    if (currentMonth < month || (currentMonth == month && currentDay < day)) {
        age--;
    }
    
    return age;
}