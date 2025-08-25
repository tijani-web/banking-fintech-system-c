Banking & FinTech Management System
A comprehensive C-based banking system that combines traditional banking features with modern FinTech capabilities, featuring secure user authentication, role-based access, and persistent data storage.

📖 Documentation
Complete technical documentation is available at: [https://tijani-web.github.io/fintech-docs-ui/]

Features
🔐 Authentication & Security
Dual Role System: Separate interfaces for administrators and customers

PIN-based Authentication: 4-digit PIN required for all financial transactions

Age Verification: Users must be 18+ to register an account

Secure Data Storage: All sensitive data is encrypted in files

🏦 Account Management
User Registration: Complete profile creation with personal details

Account Types: Support for Savings, Current, and Investment accounts

Account Status Management: Active, Closed, or Frozen statuses

Comprehensive Search: Find accounts by account number

💰 Financial Operations
Deposits & Withdrawals: Secure money handling with PIN verification

Fund Transfers: Send money between accounts with transaction tracking

Loan Management: Apply for and repay loans with balance tracking

Investment Portfolio: Move funds between main balance and investments

📊 Analytics & Reporting
Bank-wide Analytics: Total balances, loans, and investments across all accounts

Transaction History: Complete audit trail for all financial activities

Portfolio Overview: View investment performance and balances

💾 Data Persistence
Automatic Saving: Data persists between sessions

Transaction Logging: All activities are recorded with timestamps

Backup & Recovery: Data files can be backed up and restored

Installation & Usage
Prerequisites
GCC compiler or any C development environment

Standard C library support

Compilation
bash
gcc -o banking_system banking_system.c
Execution
bash
./banking_system
File Structure
text
banking_system.c      # Main application source code
bank_data.txt         # Auto-generated data storage file
User Guide
For Customers
Registration: Select "Register New Account" from main menu

Login: Use your account number and PIN to access customer features

Banking Operations:

Deposit/withdraw money (requires PIN)

Transfer funds to other accounts

Apply for loans or make repayments

Manage investments

Account Management:

View transaction history

Change PIN

Check account status

For Administrators
Admin PIN: Use "admin" to access administrator features

System Management:

View all accounts

Search specific accounts

Update account statuses

View system-wide analytics

Access transaction histories

Data Persistence
The system automatically saves all data to bank_data.txt when:

Explicitly choosing "Save Data to File" option

Exiting the program properly through the menu

Performing critical operations

Data loaded automatically at program startup.

Security Features
PIN Protection: All financial transactions require PIN confirmation

Age Verification: Minimum age requirement (18 years)

Role-based Access: Separation between customer and admin functionalities

Input Validation: Comprehensive checks for all user inputs

Transaction Logging: Complete audit trail of all activities

Technical Details
Data Structures
Account Structure: Contains all customer information and financial data

Transaction Structure: Records all financial activities with timestamps

File Format
The system uses a structured text file format with:

Account information section

Transaction history section

Automatic versioning and backup

Error Handling
Comprehensive input validation

File operation error checking

Memory boundary protection

Graceful error recovery

Support
For issues related to:

Data not persisting: Ensure proper program exit through menu options

Login problems: Verify account number and PIN combination

Transaction errors: Check account status and available balances
