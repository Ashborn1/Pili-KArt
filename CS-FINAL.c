#include <stdio.h> //Standard input/output (for printing and scanning)
#include <string.h> //String handling (copy, compare, length)
#include <unistd.h> //Sleep Function
#include <ctype.h> //Character conversions
#include <stdlib.h> //General utilities (for memory allocation, random, and exit)
#include <time.h> //Time/date functions (time, clock, timers)


// Structures
struct ATMAccount {
    char name[50];
    char pin[7]; //6-digit PIN
    float balance; //Store ATM balance in PHP
};


// Function prototypes
int isValidName(char name[]); //Check if name contains only letter and spaces
int isValidNum(char str[]); // Checks if string contains only digits
void displayApp(int cur, char App[][50], char symbol[], float APrices[], float rateValue);
void displayHb(int cur, char Hb[][50], char symbol[], float Hprices[], float rateValue);
void displayNp(int cur, char Np[][50], char symbol[], float Nprices[], float rateValue);
void displaypaso(int cur, char paso[][50], char symbol[], float Pprices[], float rateValue);
void waitForEnter();
void waitForCha();
void exitprog();
void printDivider();
void printSectionHeader(char title[]);
void printBoxHeader(char title[]);
void printSubtitle(char subtitle[]);


// ATM Functions
void atmMenu(float *walletAmount, char symbol[], float rateValue); //Main ATM menu
void createATMAccount(); //Creates ATM account
int atmLogin(char loggedInName[], float *balance); //ATM login
void depositMoney(float *balance, float *walletAmount, char symbol[], float rateValue);
void withdrawMoney(float *balance, float *walletAmount, char symbol[], float rateValue);
void checkBalance(float balance, char symbol[], float rateValue);
void transferToWallet(float *balance, float *walletAmount, char symbol[], float rateValue);
void viewAllAccounts(); //Displays all stored ATM account


int main(){
    // Menu Items with prices in arryas
    char APP[15][50] = {"USB Flash Drive (128GB)", "Wireless Mouse", "Mechanical Keyboard",
    "Bluetooth Earphones", "Power Bank (10,000mAh)", "Gaming Headset", "Smartwatch",
    "Phone Stand", "USB Type-C Cable", "HDMI Cable (2m)", "Webcam (1080p)", "LED Desk Lamp",
    "Portable Speaker", "External Hard Drive (1TB)", "Wireless Charger Pad"};
    float APrices[15] = {799, 420, 1750, 890, 1499, 1650, 2100, 250, 150, 300, 950, 600, 700, 3500, 980};


    char Hb[15][50] = {
    "1 pair bikini XL limited", "Fitted shirt S", "Cargo pants 2XL",
    "Crop top Gnarly limited", "Long sleeve Chenal", "Rip denim jeans M",
    "Lakers Hoodie L limited", "Corduroy jeans L", "Black & white tuxedo XL",
    "Polo shirt XL", "Jogging pants CCC exclusive all size",
    "PE shirt CCC exclusive all size", "Mini skirt XS",
    "Maong pants XL", "Leggings M"};
    float Hprices[15] = {3000, 499, 649, 2500, 500, 1250, 7500, 500, 5000, 350, 500, 500, 200, 3000, 250};


    char Np[10][50] = {
    "Bed Frame", "Dining table set", "Couch set", "Refrigerator",
    "Portable vacuum cleaner", "Cabinets", "Air conditioner",
    "Comforter", "Pillow", "Vanity table with chair"};
    float Nprices[10] = {5999.75, 9999.75, 8999.75, 11000.50, 4999.75, 1499.75, 12999.75, 699.75, 399.99, 4967.99};


    char paso[15][50] = {
    "Water", "Bread", "Sardines", "Eggs (12pcs)", "Cheddar Cheese (160g)",
    "Chips (100g)", "Milk Powder (150g)", "All purpose flour (400g)",
    "Soda Pop (320ml)", "Pancit Canton (Kasalo Pack)", "White Sugar (1kg)",
    "Chicken Noodles (100g)", "Keso de Bola", "Penne Pasta (500g)", "Tocino (250g)"};
    float Pprices[15] = {9.98, 20.25, 25.15, 118, 56.50, 45.75, 110.50, 52.25, 38.45, 20.50, 77.85, 12.50, 514.75, 97.65, 120};


    // Function variables
    char username[100], edcho = 'y', chcho, loop = 'y', loop2 = 'y', loop3 = 'y', loop4 = 'y', loop5 = 'y', loop6 = 'y', loop7 = 'y', loop8 = 'y', ageStr[10], pwd, symbol[4] = "₱", topup, moneyInput[50], curInput[10];
    int cur, mecho, choice, quantity, totalItems = 0, cartCount = 0, cartQuantity[50], cartItems[50], cartCategory[50], age = 0, valid = 1, valid2 = 1;
    float am, subtotal, totalAmount = 0, totalb4discount, cartSubtotal[50], rateValue = 1, insuf = 0, am_in_php = 0, minPHP = 9.98;
   
    // Defining color codes
    #define red       "\x1b[31m"
    #define yellow    "\x1b[33m"
    #define blue      "\x1b[34m"
    #define lblue     "\x1b[94m"  
    #define gray      "\x1b[90m"  
    #define black     "\x1b[30m"


    // font formatting
    #define bold      "\x1b[1m"
    #define italic    "\x1b[3m"
    #define underline "\x1b[4m"
    #define reset     "\x1b[0m"


    // Welcome message
    printf("%s%s", bold, yellow);
    printBoxHeader("🛒 MABUHAY! \n              Welcome to Pili KArt!");
    printf("%s%s", italic, yellow);
    printf("%s", reset);
    printf("- a digital e-commerce built in with a virtual atm.\nMade to make your digital shopping experience a pleasant one!\n\n");
    printf("A little insight on the shops' naming conventions:");
    printf("%s", bold);
    printf(" \n📱 1.APOLLO [Technologies Store]");
    printf("%s", reset);
    printf("\n- The Lunar Roving Vehicle used by the Apollo missions\n15, 16, 17 was allegedly designed by Eduardo San Juan,\na Filipino NASA engineer. ");
    printf("%s", bold);
    printf(" \n👗 2.HABI [Fashion Store]");
    printf("%s", reset);
    printf("\n- Tagalog term used to describe the act of weaving ");
    printf("%s", bold);
    printf(" \n🏠 3.NIPA [Home Appliances Store]");
    printf("%s", reset);
    printf("\n-  Derived from \"Bahay Kubo\" or Nipa Hut ");
    printf("%s", bold);
    printf(" \n🍲 4.PASO [Food Essentials Store]");
    printf("%s", reset);
    printf(" \n- Other term for 'banga' or a pot; this also represents \nCalamba. ");
    printf(" \n\nNow, unearth the treasures of Pili KArt.\nWill your journey begin at HABI or take flight with APOLLO?");
    printf(" \nYou can only do that here!");
    printf("%s%s",bold, italic);
    printf("\nWhere you can choose, to your heart's desire.\n");  
    printf("%s", reset);
   
    // Sign up
    do {
        printf("%s", reset);
        printf("%s", lblue);
        printSectionHeader("📝 SIGN UP");
        printf("%s", blue);
        printf("Please enter your sign up details.\n");
        printf("%s", reset);
        printf("Enter Name: ");
        fgets(username, sizeof(username), stdin);
        username[strcspn(username, "\n")] = '\0';
       
        //name validation
        if (strlen(username) == 0) {
            printf("%s%s", bold, red);
            printf("Name cannot be empty!\n");
            printf("%s", reset);
            printDivider();
            continue;
        }
        if (!isValidName(username)) {
            printf("%s%s", bold, red);
            printf("Invalid name! Please use letters and spaces only.\n");
            printf("%s", reset);
            printDivider();
            continue;
        }
        break;
    } while (1);
   
    //age validation
    do {
        printf("Enter your age: ");
        scanf("%s", ageStr);
       
        if (!isValidNum(ageStr)) {
            printf("%s%s", bold, red);
            printf("Invalid input! Please enter numbers only.\n");
            printf("%s", reset);
            printDivider();
            continue;
        }

        age = atoi(ageStr);

        if (age <= 0 || age > 120) {
            printf("%s%s", bold, red);
            printf("Invalid age! Please enter a realistic number (1-120).\n");
            printf("%s", reset);
            printDivider();
            continue;
        }
        break;
    } while (1);
   
    //PWD status
    do {
        printf("Are you a Person with Disability? (y/n): ");
        scanf(" %c", &pwd);
        if (pwd != 'y' && pwd != 'Y' && pwd != 'n' && pwd != 'N') {
            printf("%s%s", bold, red);
            printf("Invalid input! Please enter 'y' for yes or 'n' for no.\n");
            printf("%s", reset);
            printDivider();
            continue;
        }
    } while (pwd != 'y' && pwd != 'Y' && pwd != 'n' && pwd != 'N');
   
    printDivider();


    // Currency selection
    do {
        valid2 = 1;
        printSectionHeader("💱 CURRENCY SELECTION");
        printf("Select Currency\n");
        printf("1 - PHP 🇵🇭\n");
        printf("2 - USD 🇺🇸\n");
        printf("3 - EUR 🇪🇺\n");
        printf("4 - JPY 🇯🇵\n");
        printf("%s", blue);
        printf("Enter Choice: ");
        printf("%s", reset);
        scanf("%s", curInput);

        //numeric input validation
        for (int i = 0; curInput[i] != '\0'; i++) {
            if (!isdigit(curInput[i])) {
                valid2 = 0;
                break;
            }
        }

        if (!valid2) {
            printf("%s%s", bold, red);
            printf("Invalid input! Please enter numbers only (1-4).\n");
            printf("%s", reset);
            printDivider();
            continue;
        }

        cur = atoi(curInput);

        switch (cur) {
            case 1:
                rateValue = 1.0;
                strcpy(symbol, "₱");
                loop = 'n';
                break;
            case 2:
                rateValue = 0.017; //1 PHP = 0.017 USD
                strcpy(symbol, "$");
                loop = 'n';
                break;
            case 3:
                rateValue = 0.016; //1 PHP = 0.016 EUR
                strcpy(symbol, "€");
                loop = 'n';
                break;
            case 4:
                rateValue = 2.68; //1 PHP = 2.68 JPY
                strcpy(symbol, "¥");
                loop = 'n';
                break;
            default:
                printf("%s%s", bold, red);
                printf("You've entered an invalid choice. Please select 1-4.\n");
                printf("%s", reset);
                printDivider();
                continue;
        }
        break;
    } while (loop == 'y' || loop == 'Y');
   
    printDivider();

    // Wallet Money input
    do {
        printSectionHeader("💰 USER WALLET");
        printf("%s", blue);
        printf("Enter Money Amount (%s): ", symbol);
        printf("%s", reset);
        scanf("%s", moneyInput);

        //input validation
        valid = 1;
        for (int i = 0; moneyInput[i] != '\0'; i++) {
            if (!isdigit((unsigned char)moneyInput[i]) && moneyInput[i] != '.') {
                valid = 0;
                break;
            }
        }

        if (!valid) {
            printf("%s%s", bold, red);
            printf("Invalid input! Please enter numeric values only.\n");
            printf("%s", reset);
            printDivider();
            continue;
        }

        am = atof(moneyInput); //wallet money amount in selected currency
        am_in_php = am / rateValue; //wallet amount in PHP to selected currency

        if (am < 0.0f) {
            printf("%s%s", bold, red);
            printf("Amount cannot be negative.\n");
            printf("Please enter again.\n");
            printf("%s", reset);
            printDivider();
            continue;
        }

        if (am_in_php < minPHP) {
            printf("%s%s", bold, red);
            printf("You don't have enough money to shop.\n");
            printf("Minimum required: %s%.2f\n", symbol, minPHP * rateValue);
            printf("Please enter again.\n");
            printf("%s", reset);
            printDivider();
            continue;
        }
        break;
    } while (1);

    printf("You've entered: %s%.2f\n", symbol, am);
    printDivider();

    // Main Menu Loop
    do {
        printSectionHeader("🏠 MAIN MENU");
        time_t t;
        time(&t);
        printf("📅 Date & Time: %s", ctime(&t));
        printf("👋 Hello!, %s, Welcome to Pili KArt!\n", username);
        printf("💰 Your money is: %s%.2f\n", symbol, am);
       
        printf("\n1. 👁️ View Items");
        printf("\n2. 🛍️ Buy Products");    
        printf("\n3. 🛒 View Cart / Checkout");    
        printf("\n4. 🏧 ATM");
        printf("\n5. 🚪 Exit");
        printf("\n%s", blue);
        printf("Enter your choice (1-5): ");
        printf("%s", reset);
        scanf("%d", &mecho);
       
        switch (mecho) {
            case 1:
                do {
                    printSectionHeader("👁️ VIEW ITEMS");
                    printf("Select a Shop to View\n");
                    printf("\n1. 📱 APOLLO Technologies");
                    printf("\n2. 👗 HABI Fashion Store");
                    printf("\n3. 🏠 NIPA Home Essentials");
                    printf("\n4. 🍲 PASO Food Essentials");
                    printf("\n5. 🔙 Exit");
                    printf("\n%s", blue);
                    printf("Enter your choice (1-5): ");
                    printf("%s", reset);
                    scanf("%d", &choice);

                    switch (choice) {
                        case 1:
                            printSectionHeader("📱 APOLLO Technologies");
                            displayApp(cur, APP, symbol, APrices, rateValue);
                            waitForCha();
                            break;
                        case 2:
                            printSectionHeader("👗 HABI Fashion Store");
                            displayHb(cur, Hb, symbol, Hprices, rateValue);
                            waitForCha();
                            break;
                        case 3:
                            printSectionHeader("🏠 NIPA Home Essentials");
                            displayNp(cur, Np, symbol, Nprices, rateValue);
                            waitForCha();
                            break;
                        case 4:
                            printSectionHeader("🍲 PASO Food Essentials");
                            displaypaso(cur, paso, symbol, Pprices, rateValue);
                            waitForCha();
                            break;
                        case 5:
                            loop3 = 'n';
                            waitForEnter();
                            break;
                        default:
                            printf("%s%s", bold, red);
                            printf("Invalid choice!\n");
                            printf("%s", reset);
                            printDivider();
                            break;
                    }
                } while (loop3 == 'y' || loop3 == 'Y');
                break;

            case 2:
                printSectionHeader("🛍️ BUY PRODUCTS");
                do {
                    printf("Select a Shop to Buy\n");
                    printf("\n1. 📱 APOLLO Technologies");
                    printf("\n2. 👗 HABI Fashion Store");
                    printf("\n3. 🏠 NIPA Home Essentials");
                    printf("\n4. 🍲 PASO Food Essentials");
                    printf("\n5. 🔙 Exit");
                    printf("\n%s", blue);
                    printf("Enter your choice (1-5): ");
                    printf("%s", reset);
                    scanf("%d", &choice);

                    switch (choice) {
                        case 1:
                            printSectionHeader("📱 APOLLO Technologies");
                            do {
                                displayApp(cur, APP, symbol, APrices, rateValue);
                                printf("\n%s", blue);
                                printf("Enter your choice (1-15): ");
                                printf("%s", reset);
                                scanf("%d", &choice);
                                if (choice < 1 || choice > 15) {
                                    printf("%s%s", bold, red);
                                    printf("Invalid choice. Please select a valid item.\n");
                                    printf("%s", reset);
                                    printDivider();
                                    break;
                                }
                                printf("\nYou selected: %s - %s%.2f\n", APP[choice - 1], symbol, APrices[choice - 1] * rateValue);
                                printf("%s", blue);
                                printf("Enter quantity: ");
                                printf("%s", reset);
                                scanf("%d", &quantity);
                                if (quantity < 1) {
                                    printf("%s%s", bold, red);
                                    printf("Invalid quantity.\n");
                                    printf("%s", reset);
                                    printDivider();
                                    break;
                                }
                                subtotal = APrices[choice - 1] * rateValue * quantity;
                                printf("\nSubtotal: %s%.2f\n", symbol, subtotal);
                                int found = -1;
                                for (int i = 0; i < cartCount; i++) {
                                    if (cartItems[i] == choice - 1 && cartCategory[i] == 1) {
                                        found = i;
                                        break;
                                    }
                                }
                                if (found != -1) {
                                    cartQuantity[found] += quantity;
                                    cartSubtotal[found] += subtotal;
                                    printf("Item quantity updated in cart!\n");
                                } else {
                                    cartItems[cartCount] = choice - 1;
                                    cartCategory[cartCount] = 1;
                                    cartQuantity[cartCount] = quantity;
                                    cartSubtotal[cartCount] = subtotal;
                                    cartCount++;
                                    printf("Item added to cart!\n");
                                }
                                printf("%s", blue);
                                printf("Do you want to purchase another item in this store? (y/n): ");
                                printf("%s", reset);
                                scanf(" %c", &loop5);
                                printDivider();
                            } while (loop5 == 'y' || loop5 == 'Y');
                            waitForCha();
                            break;

                        case 2:
                            printSectionHeader("👗 HABI Fashion Store");
                            do {
                                displayHb(cur, Hb, symbol, Hprices, rateValue);
                                printf("\n%s", blue);
                                printf("Enter your choice (1-15): ");
                                printf("%s", reset);
                                scanf("%d", &choice);
                                if (choice < 1 || choice > 15) {
                                    printf("%s%s", bold, red);
                                    printf("Invalid choice. Please select a valid item.\n");
                                    printf("%s", reset);
                                    printDivider();
                                    break;
                                }
                                printf("\nYou selected: %s - %s%.2f\n", Hb[choice - 1], symbol, Hprices[choice - 1] * rateValue);
                                printf("%s", blue);
                                printf("Enter quantity: ");
                                printf("%s", reset);
                                scanf("%d", &quantity);
                                if (quantity < 1) {
                                    printf("%s%s", bold, red);
                                    printf("Invalid quantity.\n");
                                    printf("%s", reset);
                                    printDivider();
                                    break;
                                }
                                subtotal = Hprices[choice - 1] * rateValue * quantity;
                                printf("\nSubtotal: %s%.2f\n", symbol, subtotal);
                                int found = -1;
                                for (int i = 0; i < cartCount; i++) {
                                    if (cartItems[i] == choice - 1 && cartCategory[i] == 2) {
                                        found = i;
                                        break;
                                    }
                                }
                                if (found != -1) {
                                    cartQuantity[found] += quantity;
                                    cartSubtotal[found] += subtotal;
                                    printf("Item quantity updated in cart!\n");
                                } else {
                                    cartItems[cartCount] = choice - 1;
                                    cartCategory[cartCount] = 2;
                                    cartQuantity[cartCount] = quantity;
                                    cartSubtotal[cartCount] = subtotal;
                                    cartCount++;
                                    printf("Item added to cart!\n");
                                }
                                printf("%s", blue);
                                printf("Do you want to purchase another item in this store? (y/n): ");
                                printf("%s", reset);
                                scanf(" %c", &loop6);
                                printDivider();
                            } while (loop6 == 'y' || loop6 == 'Y');
                            waitForCha();
                            break;

                        case 3:
                            printSectionHeader("🏠 NIPA Home Essentials");
                            do {
                                displayNp(cur, Np, symbol, Nprices, rateValue);
                                printf("\n%s", blue);
                                printf("Enter your choice (1-10): ");
                                printf("%s", reset);
                                scanf("%d", &choice);
                                if (choice < 1 || choice > 10) {
                                    printf("%s%s", bold, red);
                                    printf("Invalid choice. Please select a valid item.\n");
                                    printf("%s", reset);
                                    printDivider();
                                    break;
                                }
                                printf("\nYou selected: %s - %s%.2f\n", Np[choice - 1], symbol, Nprices[choice - 1] * rateValue);
                                printf("%s", blue);
                                printf("Enter quantity: ");
                                printf("%s", reset);
                                scanf("%d", &quantity);
                                if (quantity < 1) {
                                    printf("%s%s", bold, red);
                                    printf("Invalid quantity.\n");
                                    printf("%s", reset);
                                    printDivider();
                                    break;
                                }
                                subtotal = Nprices[choice - 1] * rateValue * quantity;
                                printf("\nSubtotal: %s%.2f\n", symbol, subtotal);
                                int found = -1;
                                for (int i = 0; i < cartCount; i++) {
                                    if (cartItems[i] == choice - 1 && cartCategory[i] == 3) {
                                        found = i;
                                        break;
                                    }
                                }
                                if (found != -1) {
                                    cartQuantity[found] += quantity;
                                    cartSubtotal[found] += subtotal;
                                    printf("Item quantity updated in cart!\n");
                                } else {
                                    cartItems[cartCount] = choice - 1;
                                    cartCategory[cartCount] = 3;
                                    cartQuantity[cartCount] = quantity;
                                    cartSubtotal[cartCount] = subtotal;
                                    cartCount++;
                                    printf("Item added to cart!\n");
                                }
                                printf("%s", blue);
                                printf("Do you want to purchase another item in this store? (y/n): ");

                                printf("%s", reset);
                                scanf(" %c", &loop7);
                                printDivider();
                            } while (loop7 == 'y' || loop7 == 'Y');
                            waitForCha();
                            break;

                        case 4:
                            printSectionHeader("🍲 PASO Food Essentials");
                            do {
                                displaypaso(cur, paso, symbol, Pprices, rateValue);
                                printf("\n%s", blue);
                                printf("Enter your choice (1-15): ");
                                printf("%s", reset);
                                scanf("%d", &choice);
                                if (choice < 1 || choice > 15) {
                                    printf("%s%s", bold, red);
                                    printf("Invalid choice. Please select a valid item.\n");
                                    printf("%s", reset);
                                    printDivider();
                                    break;
                                }
                                printf("\nYou selected: %s - %s%.2f\n", paso[choice - 1], symbol, Pprices[choice - 1] * rateValue);
                                printf("%s", blue);
                                printf("Enter quantity: ");
                                printf("%s", reset);
                                scanf("%d", &quantity);
                                if (quantity < 1) {
                                    printf("%s%s", bold, red);
                                    printf("Invalid quantity.\n");
                                    printf("%s", reset);
                                    printDivider();
                                    break;
                                }
                                subtotal = Pprices[choice - 1] * rateValue * quantity;
                                printf("\nSubtotal: %s%.2f\n", symbol, subtotal);
                                int found = -1;
                                for (int i = 0; i < cartCount; i++) {
                                    if (cartItems[i] == choice - 1 && cartCategory[i] == 4) {
                                        found = i;
                                        break;
                                    }
                                }
                                if (found != -1) {
                                    cartQuantity[found] += quantity;
                                    cartSubtotal[found] += subtotal;
                                    printf("Item quantity updated in cart!\n");
                                } else {
                                    cartItems[cartCount] = choice - 1;
                                    cartCategory[cartCount] = 4;
                                    cartQuantity[cartCount] = quantity;
                                    cartSubtotal[cartCount] = subtotal;
                                    cartCount++;
                                    printf("Item added to cart!\n");
                                }
                                printf("%s", blue);
                                printf("Do you want to purchase another item in this store? (y/n): ");
                                printf("%s", reset);
                                scanf(" %c", &loop8);
                                printDivider();
                            } while (loop8 == 'y' || loop8 == 'Y');
                            waitForCha();
                            break;

                        case 5: //exit buy menu
                            loop4 = 'n';
                            waitForEnter();
                            break;
                        default:
                            printf("%s%s", bold, red);
                            printf("Invalid choice!\n");
                            printf("%s", reset);
                            printDivider();
                            break;
                    }
                } while (loop4 == 'y' || loop4 == 'Y');
                break;

            case 3: //view cart and checkout
                if (cartCount == 0) {
                    printf("🛒 Your cart is empty.\n");
                    printDivider();
                    waitForEnter();
                    break;
                }

                do {
                    totalAmount = 0;
                    printSectionHeader("🛒 YOUR CART");
                    printf("%-3s %-35s %-10s %-10s\n", "No.", "Product", "Qty", "Total");
                    printDivider();

                    for (int i = 0; i < cartCount; i++) {
                        char *productName;
                        int itemIndex = cartItems[i];
                        int category = cartCategory[i];
                       
                        if (category == 1) productName = APP[itemIndex];
                        else if (category == 2) productName = Hb[itemIndex];
                        else if (category == 3) productName = Np[itemIndex];
                        else if (category == 4) productName = paso[itemIndex];
                       
                        printf("%-3d %-35s %-10d %s%.2f\n", i + 1, productName, cartQuantity[i], symbol, cartSubtotal[i]);
                        totalAmount += cartSubtotal[i];
                    }
                    printDivider();
                    printf("💰 Your money is: %s%.2f\n", symbol, am);
                    printf("💳 Total Amount: %s%.2f\n", symbol, totalAmount);
               
                    printf("\n%s", blue);
                    printf("✏️ Do you want to edit your cart? (y/n): ");
                    printf("%s", reset);
                    scanf(" %c", &edcho);

                    if (edcho == 'y' || edcho == 'Y') {
                        int editChoice, newQty;
                        printf("\n%s", blue);
                        printf("Enter item number to edit (1-%d): ", cartCount);
                        printf("%s", reset);
                        scanf("%d", &editChoice);


                        if (editChoice < 1 || editChoice > cartCount) {
                            printf("%s%s", bold, red);
                            printf("Invalid item number.\n");
                            printf("%s", reset);
                            printDivider();
                            continue;
                        }

                        char *selectedProduct;
                        int itemIndex = cartItems[editChoice - 1];
                        int category = cartCategory[editChoice - 1];
                        float itemPrice;
                       
                        if (category == 1) {
                            selectedProduct = APP[itemIndex];
                            itemPrice = APrices[itemIndex];
                        } else if (category == 2) {
                            selectedProduct = Hb[itemIndex];
                            itemPrice = Hprices[itemIndex];
                        } else if (category == 3) {
                            selectedProduct = Np[itemIndex];
                            itemPrice = Nprices[itemIndex];
                        } else if (category == 4) {
                            selectedProduct = paso[itemIndex];
                            itemPrice = Pprices[itemIndex];
                        }

                        printf("You selected: %s (Current qty: %d)\n", selectedProduct, cartQuantity[editChoice - 1]);
                        printf("%s", blue);
                        printf("Enter new quantity (0 to remove): ");
                        printf("%s", reset);
                        scanf("%d", &newQty);

                        if (newQty == 0) {
                            for (int i = editChoice - 1; i < cartCount - 1; i++) {
                                cartItems[i] = cartItems[i + 1];
                                cartCategory[i] = cartCategory[i + 1];
                                cartQuantity[i] = cartQuantity[i + 1];
                                cartSubtotal[i] = cartSubtotal[i + 1];
                            }
                            cartCount--;
                            printf("❌ Item removed from cart.\n");
                        } else if (newQty > 0) {
                            cartQuantity[editChoice - 1] = newQty;
                            cartSubtotal[editChoice - 1] = itemPrice * rateValue * newQty;
                            printf("✅ Quantity updated.\n");
                        } else {
                            printf("%s%s", bold, red);
                            printf("Invalid quantity.\n");
                            printf("%s", reset);
                        }
                        printDivider();
                    }

                } while (edcho == 'y' || edcho == 'Y');
               
                //checkout confirmation
                printf("%s", blue);
                printf("💳 Do you want to check out? (y/n): ");
                printf("%s", reset);
                scanf(" %c", &chcho);
               
                if (chcho == 'y' || chcho == 'Y') {
                    if (cartCount > 0) {
                        totalAmount = 0;
                        for (int i = 0; i < cartCount; i++) {
                            totalAmount += cartSubtotal[i];
                        }

                        totalb4discount = totalAmount;

                        if (age > 60 && (pwd == 'y' || pwd == 'Y')) {
                            totalAmount *= 0.85; //15%
                        } else if (age > 60) {
                            totalAmount *= 0.90; //10%
                        } else if (totalb4discount >= 20000 * rateValue) {
                            totalAmount *= 0.90; //10%
                        } else if (totalb4discount >= 15000 * rateValue) {
                            totalAmount *= 0.925; //7.5%
                        } else if (pwd == 'y' || pwd == 'Y') {
                            totalAmount *= 0.95; //5%
                        } else if (totalb4discount >= 10000 * rateValue) {
                            totalAmount *= 0.95; //5%
                        } else if (totalb4discount >= 5000 * rateValue) {
                            totalAmount *= 0.975; //7.5%
                        }
                       
                        //display receipt
                        printSectionHeader("🧾 BILL RECEIPT");
                        time_t t;
                        time(&t);
                        printf("📅 Date & Time: %s", ctime(&t));
                        printf("👤 Customer Name: %s\n", username);

                        //display discount applied
                        if (age >= 60 && (pwd == 'y' || pwd == 'Y')) {
                            printf("🎁 A 15%% senior and PwD discount has been applied to your total.\n");
                        } else if (age > 60) {
                            printf("🎁 A 10%% age discount has been applied to your total.\n");
                            if (totalb4discount >= 5000 * rateValue) {
                                printf("💡 Note: Your age discount has overridden the promo discount\n");
                            }
                        } else if (totalb4discount >= 20000 * rateValue) {
                            printf("🎁 A 10%% promo discount for 20k+ has been applied to your total.\n");
                            if (pwd == 'y' || pwd == 'Y') {
                                printf("💡 Note: Your promo discount has overridden the PwD discount\n");
                            }
                        } else if (totalb4discount >= 15000 * rateValue) {
                            printf("🎁 A 7.5%% promo discount for 15k+ has been applied to your total.\n");
                            if (pwd == 'y' || pwd == 'Y') {
                                printf("💡 Note: Your promo discount has overridden the PwD discount.\n");
                            }
                        } else if (pwd == 'y' || pwd == 'Y') {
                            printf("🎁 A 5%% PwD discount has been applied to your total.\n");
                        } else if (totalb4discount >= 10000 * rateValue) {
                            printf("🎁 A 5%% promo discount for 10k+ has been applied to your total.\n");
                        } else if (totalb4discount >= 5000 * rateValue) {
                            printf("🎁 A 2.5%% promo discount for 5k+ has been applied to your total.\n");
                        }
                       
                        printDivider();
                        printf("💰 Wallet: %s%.2f\n\n", symbol, am);
                       
                        if (age >= 60 || pwd == 'y' || pwd == 'Y' || (totalb4discount >= 5000 * rateValue)) {
                            printf("📊 Initial Total: %s%.2f\n", symbol, totalb4discount);
                        }
                        printf("💳 Final Total: %s%.2f\n", symbol, totalAmount);
                       
                        if (am < totalAmount) {
                            insuf = totalAmount - am;
                            printf("❌ You need an additional %s%.2f to complete the purchase.\n", symbol, insuf);
                        } else {
                            float change = am - totalAmount;
                            printf("\n🪙 Change: %s%.2f\n", symbol, change);
                        }
                        printDivider();

                        //insufficient funds, offers ATM top-up
                        if (totalAmount > am) {
                            printf("\n%s", blue);
                            printf("🏧 Insufficient funds. Would you like to use ATM to top-up? (y/n): ");
                            printf("%s", reset);
                            scanf(" %c", &topup);
                            if (topup == 'y' || topup == 'Y') {
                                // Check if ATM accounts file exists
                                FILE *fp = fopen("atm_accounts.dat", "rb");
                                //ATM account do not exist
                                if (!fp) {
                                    printf("\n%s%s", bold, red);
                                    printf("❌ No ATM accounts found. Please create an ATM account first.\n");
                                    printf("🔙 Returning to main menu...\n");
                                    printf("💡 Note: You don't have enough money to complete this purchase.\n");
                                    printf("Please add money to your wallet or create an ATM account.\n");
                                    printf("%s", reset);
                                    printDivider();
                                    waitForEnter();
                                } else {
                                    fclose(fp);
                                    // Go to ATM system
                                    printf("\n🔄 Redirecting to ATM system...\n");
                                    printDivider();
                                    waitForEnter();
                                    atmMenu(&am, symbol, rateValue);
                                   
                                    // After returning from ATM, check if user now has enough money
                                    if (am >= totalAmount) {
                                        printSectionHeader("✅ COMPLETING TRANSACTION");
                                        float change = am - totalAmount;
                                        printSectionHeader("🎉 Transaction successful!\n");
                                        printf("🪙 Change: %s%.2f\n", symbol, change);
                                        printf("\n%s%s", bold, yellow);
                                        printf("\n🙏 Thank you for shopping with Pili KArt, %s!\n", username);
                                        printf("%s", reset);
                                        am -= totalAmount; //minus final total from wallet money
                                        cartCount = 0; //empty cart
                                        printf("💰 Remaining balance: %s%.2f\n", symbol, am);
                                    } else {
                                        printf("\n%s%s", bold, red);
                                        printf("❌ You still don't have enough money.\n");
                                        printf("🔙 Returning to main menu...\n");
                                        printf("💡 Note: Transaction cancelled. Your cart has been saved.\n");
                                        printf("%s", reset);
                                    }
                                }
                            } else {
                                printf("\n❌ Transaction cancelled.\n");
                                printf("🔙 Returning to main menu...\n");
                                printf("\n💡 Note: You don't have enough money to complete this purchase.\n");
                            }
                        } else {
                            printf("✅ Transaction successful!");
                            printf("\n🙏 Thank you for shopping at Pili KArt, %s!\n", username);
                            am -= totalAmount;
                            cartCount = 0;
                            printf("💰 Remaining balance: %s%.2f\n", symbol, am);
                        }
                    }
                }
               
                printDivider();
                waitForEnter();
                break;
            case 4:
                atmMenu(&am, symbol, rateValue);
                break;


            case 5:
                exitprog();
                return 0;


            default:
                printf("%s%s", bold, red);
                printf("❌ You've entered an invalid choice.\n");
                printf("%s", reset);
                printDivider();
                break;
        }
    } while (loop2 == 'y' || loop2 == 'Y');


    return 0;
}

void atmMenu(float *walletAmount, char symbol[], float rateValue) {
    int atmChoice;
    char atmLoop = 'y';
    char loggedInName[50];
    float atmBalance = 0;
    int isLoggedIn = 0;

    do {
        printf("%s%s", bold, yellow);
        printBoxHeader("🏧 Welcome to Pili KAhera!");
        printf("%s", reset);
        printf("1. 🆕 Create ATM Account\n");
        printf("2. 🔐 Login to ATM\n");
        printf("3. 👥 View All ATM Accounts\n");
        printf("4. 🔙 Exit ATM\n");
        printf("%s", blue);
        printf("Enter your choice (1-4): ");
        printf("%s", reset);
        scanf("%d", &atmChoice);

        switch (atmChoice) {
            case 1: //create account
                createATMAccount();
                break;
           
            case 2: //login
                if (atmLogin(loggedInName, &atmBalance)) {
                    isLoggedIn = 1;
                    char atmSubLoop = 'y';
                   
                    while (atmSubLoop == 'y' || atmSubLoop == 'Y') {
                        printSectionHeader("🏧 ATM MENU");
                        printf("👋 Welcome %s!\n", loggedInName);
                        printf("1. 💵 Deposit Money (from Wallet)\n");
                        printf("2. 💸 Transfer to Wallet\n");
                        printf("3. 📊 Check Balance\n");
                        printf("4. 🚪 Logout\n");
                        printf("%s", blue);
                        printf("Enter your choice (1-4): ");
                        printf("%s", reset);
                        scanf("%d", &atmChoice);

                        switch (atmChoice) {
                            case 1: //deposit money from wallet
                                depositMoney(&atmBalance, walletAmount, symbol, rateValue);
                                {
                                    //update file handling with new ATM balance
                                    struct ATMAccount acc;
                                    FILE *fp = fopen("atm_accounts.dat", "rb");
                                    FILE *temp = fopen("temp_atm.dat", "wb");
                                   
                                    if (fp && temp) {
                                        while (fread(&acc, sizeof(struct ATMAccount), 1, fp)) {
                                            if (strcmp(acc.name, loggedInName) == 0) {
                                                acc.balance = atmBalance;
                                            }
                                            fwrite(&acc, sizeof(struct ATMAccount), 1, temp);
                                        }
                                        fclose(fp);
                                        fclose(temp);
                                        remove("atm_accounts.dat");
                                        rename("temp_atm.dat", "atm_accounts.dat");
                                    }
                                }
                                break;
                           
                            case 2: //withdraw from ATM account to wallet money
                               transferToWallet(&atmBalance, walletAmount, symbol, rateValue);
                                {
                                    //update file handling
                                    struct ATMAccount acc;
                                    FILE *fp = fopen("atm_accounts.dat", "rb");
                                    FILE *temp = fopen("temp_atm.dat", "wb");
                                   
                                    if (fp && temp) {
                                        while (fread(&acc, sizeof(struct ATMAccount), 1, fp)) {
                                            if (strcmp(acc.name, loggedInName) == 0) {
                                                acc.balance = atmBalance;
                                            }
                                            fwrite(&acc, sizeof(struct ATMAccount), 1, temp);
                                        }
                                        fclose(fp);
                                        fclose(temp);
                                        remove("atm_accounts.dat");
                                        rename("temp_atm.dat", "atm_accounts.dat");
                                    }
                                }
                                break;
                           
                            case 3:
                                checkBalance(atmBalance, symbol, rateValue);
                                break;
                           
                            case 4:
                                printf("🚪 Logging out...\n");
                                atmSubLoop = 'n';
                                isLoggedIn = 0;
                                break;
                            default:
                                printf("%s%s", bold, red);
                                printf("❌ Invalid choice!\n");
                                printf("%s", reset);
                                break;
                        }
                       
                        if (atmChoice != 4) {
                            printDivider();
                            printf("%s", blue);
                            printf("🔄 Continue ATM operations? (y/n): ");
                            printf("%s", reset);
                            scanf(" %c", &atmSubLoop);
                        }
                    }
                } else {
                    printf("%s%s", bold, red);
                    printf("❌ Login failed!\n");
                    printf("%s", reset);
                }
                break;
           
            case 3:
                viewAllAccounts();
                break;
           
            case 4:
                printf("%s", gray);
                printf("🔙 Exiting ATM...\n");
                printf("%s", reset);
                atmLoop = 'n';
                break;
           
            default:
                printf("%s%s", bold, red);
                printf("❌ Invalid choice!\n");
                printf("%s", reset);
                break;
        }
       
        if (atmChoice != 4) {
            printDivider();
            printf("%s", blue);
            printf("🔄 Return to ATM main menu? (y/n): ");
            printf("%s", reset);
            scanf(" %c", &atmLoop);
        }
       
    } while (atmLoop == 'y' || atmLoop == 'Y');
}

void createATMAccount() {
    struct ATMAccount newAccount;
    FILE *fp;
   
    printSectionHeader("🆕 CREATE ATM ACCOUNT");
    printf("%s", blue);
    printf("Enter your name: ");
    printf("%s", reset);
    getchar();
    fgets(newAccount.name, sizeof(newAccount.name), stdin);
    newAccount.name[strcspn(newAccount.name, "\n")] = '\0';
   
    //account name already exist
    fp = fopen("atm_accounts.dat", "rb");
    if (fp) {
        struct ATMAccount temp;
        while (fread(&temp, sizeof(struct ATMAccount), 1, fp)) {
            if (strcmp(temp.name, newAccount.name) == 0) {
                printf("%s%s", bold, red);
                printf("❌ Account with this name already exists!\n");
                printf("%s", reset);
                fclose(fp);
                return;
            }
        }
        fclose(fp);
    }
   
    printf("%s", blue);
    printf("🔒 Create a 6-digit PIN: ");
    printf("%s", reset);
    scanf("%s", newAccount.pin);
   
    //6-digit PIN validation
    if (strlen(newAccount.pin) != 6) {
        printf("%s%s", bold, red);
        printf("❌ PIN must be exactly 6 digits!\n");
        printf("%s", reset);
        return;
    }
   
    for (int i = 0; i < 6; i++) {
        if (!isdigit(newAccount.pin[i])) {
            printf("%s%s", bold, red);
            printf("❌ PIN must contain only digits!\n");
            printf("%s", reset);
            return;
        }
    }
   
    printf("%s", blue);
    printf("💰 Enter initial deposit (PHP): ");
    printf("%s", reset);
    scanf("%f", &newAccount.balance);
   
    if (newAccount.balance < 0) {
        printf("%s%s", bold, red);
        printf("❌ Invalid deposit amount!\n");
        printf("%s", reset);
        return;
    }
   
    fp = fopen("atm_accounts.dat", "ab");//append binary
    if (!fp) {
        printf("%s%s", bold, red);
        printf("❌ Error creating account!\n");
        printf("%s", reset);
        return;
    }
   
    fwrite(&newAccount, sizeof(struct ATMAccount), 1, fp);
    fclose(fp);
   
    printSectionHeader("✅ ACCOUNT CREATED SUCCESSFULLY");
    printf("👤 Name: %s\n", newAccount.name);
    printf("💰 Initial Balance: ₱%.2f\n", newAccount.balance);
}

int atmLogin(char loggedInName[], float *balance) {
    struct ATMAccount acc;
    FILE *fp;
    char inputName[50];
    char inputPin[7];
   
    printSectionHeader("🔐 ATM LOGIN");
    printf("%s", blue);
    printf("Enter your name: ");
    printf("%s", reset);
    getchar();
    fgets(inputName, sizeof(inputName), stdin);
    inputName[strcspn(inputName, "\n")] = '\0';
   
    printf("%s", blue);
    printf("🔒 Enter your PIN: ");
    printf("%s", reset);
    scanf("%s", inputPin);
   
    fp = fopen("atm_accounts.dat", "rb");
    if (!fp) {
        printf("%s%s", bold, red);
        printf("❌ No ATM accounts found. Please create an account first.\n");
        printf("%s", reset);
        return 0;
    }
   
    while (fread(&acc, sizeof(struct ATMAccount), 1, fp)) {
        if (strcmp(acc.name, inputName) == 0 && strcmp(acc.pin, inputPin) == 0) {
            strcpy(loggedInName, acc.name);
            *balance = acc.balance;
            fclose(fp);
            printSectionHeader("✅ LOGIN SUCCESSFUL");
            printf("👋 Welcome, %s\n", loggedInName);
            return 1;
        }
    }
   
    fclose(fp);
    printf("%s%s", bold, red);
    printf("❌ Invalid name or PIN!\n");
    printf("%s", reset);
    return 0;
}

void depositMoney(float *balance, float *walletAmount, char symbol[], float rateValue) {
    float amount;
    printSectionHeader("💵 DEPOSIT MONEY");
    printf("💰 Current ATM Balance: ₱%.2f\n", *balance);
    printf("💼 Current Wallet Balance: %s%.2f\n", symbol, *walletAmount);
    printf("%s", blue);
    printf("Enter amount to deposit from wallet (in %s): ", symbol);
    printf("%s", reset);
    scanf("%f", &amount);
   
    if (amount <= 0) {
        printf("%s%s", bold, red);
        printf("❌ Invalid amount!\n");
        printf("%s", reset);
        return;
    }
   
    if (amount > *walletAmount) {
        printf("%s%s", bold, red);
        printf("❌ Insufficient wallet balance!\n");
        printf("💡 You only have %s%.2f in your wallet.\n", symbol, *walletAmount);
        printf("%s", reset);
        return;
    }
   
    // Convert wallet currency to PHP for ATM
    float amountInPHP = amount / rateValue;
   
    *walletAmount -= amount;
    *balance += amountInPHP;
   
    printSectionHeader("✅ DEPOSIT SUCCESSFUL");
    printf("💵 Deposited: ₱%.2f (from %s%.2f wallet)\n", amountInPHP, symbol, amount);
    printf("💰 New ATM Balance: ₱%.2f\n", *balance);
    printf("💼 Remaining Wallet Balance: %s%.2f\n", symbol, *walletAmount);
}
//ATM balance, both in PHP and selected currency
void checkBalance(float balance, char symbol[], float rateValue) {
    printSectionHeader("📊 ACCOUNT BALANCE");
    printf("💰 ATM Balance (PHP): ₱%.2f\n", balance);
    printf("💱 Equivalent in %s: %s%.2f\n", symbol, symbol, balance * rateValue);
}

//transfer from ATM to wallet
void transferToWallet(float *balance, float *walletAmount, char symbol[], float rateValue) {
    float amount;
   
    printSectionHeader("💸 TRANSFER TO WALLET");
    printf("💰 Current ATM Balance: ₱%.2f\n", *balance);
    printf("💼 Current Wallet Balance: %s%.2f\n", symbol, *walletAmount);
    printf("%s", blue);
    printf("Enter amount to transfer (PHP): ");
    printf("%s", reset);
    scanf("%f", &amount);
   
    if (amount <= 0) {
        printf("%s%s", bold, red);
        printf("❌ Invalid amount!\n");
        printf("%s", reset);
        return;
    }
   
    if (amount > *balance) {
        printf("%s%s", bold, red);
        printf("❌ Insufficient ATM balance!\n");
        printf("%s", reset);
        return;
    }
   
    *balance -= amount;
    *walletAmount += (amount * rateValue);
   
    printSectionHeader("✅ TRANSFER SUCCESSFUL");
    printf("💸 Transferred: ₱%.2f\n", amount);
    printf("💰 New ATM Balance: ₱%.2f\n", *balance);
    printf("💼 New Wallet Balance: %s%.2f\n", symbol, *walletAmount);
}

//display all accounts and balances
void viewAllAccounts() {
    struct ATMAccount acc;
    FILE *fp;
    int count = 0;
   
    printSectionHeader("👥 ALL ATM ACCOUNTS");
   
    fp = fopen("atm_accounts.dat", "rb");
    if (!fp) {
        printf("❌ No ATM accounts found.\n");
        return;
    }
   
    printf("\n%-5s %-30s %-15s\n", "No.", "Account Name", "Balance (PHP)");
    printDivider();
   
    while (fread(&acc, sizeof(struct ATMAccount), 1, fp)) {
        count++;
        printf("%-5d %-30s ₱%.2f\n", count, acc.name, acc.balance);
    }
   
    if (count == 0) {
        printf("📭 No accounts registered yet.\n");
    } else {
        printDivider();
        printf("📊 Total Accounts: %d\n", count);
    }
   
    fclose(fp);
}


// UI Helper Functions
//line dividers
void printDivider() {
    printf("%s", gray);
    printf("--------------------------------------------------------------\n");
    printf("%s", reset);
}

void printSectionHeader(char title[]) {
    printf("%s%s", bold, yellow);
    printf("\n==============================================================\n");
    printf("                    %s\n", title);
    printf("==============================================================\n");
    printf("%s", reset);
}

void printBoxHeader(char title[]) {
    printf("\n==============================================================\n");
    printf("                    %s\n", title);
    printf("==============================================================\n");
}

void printSubtitle(char subtitle[]) {
    printf("%s%s", italic, yellow);
    printf("%s\n", subtitle);
    printf("%s", reset);
}

int isValidName(char name[]) {
    for (int i = 0; name[i] != '\0'; i++) {
        if (!isalpha(name[i]) && name[i] != ' ') {
            return 0;
        }
    }
    return 1;
}

void displayApp(int cur, char App[][50], char symbol[], float APrices[], float rateValue) {
    printf("\n%-3s %-35s %10s\n", "No.", "Product", "Price");
    printDivider();
    for (int i = 0; i < 15; i++) {
        printf("%-3d %-35s %s%.2f\n", i + 1, App[i], symbol, APrices[i] * rateValue);
    }
}

void displayHb(int cur, char Hb[][50], char symbol[], float Hprices[], float rateValue) {
    printf("\n%-3s %-35s %10s\n", "No.", "Product", "Price");
    printDivider();
    for (int i = 0; i < 15; i++) {
        printf("%-3d %-35s %s%.2f\n", i + 1, Hb[i], symbol, Hprices[i] * rateValue);
    }
}

void displayNp(int cur, char Np[][50], char symbol[], float Nprices[], float rateValue) {
    printf("\n%-3s %-35s %10s\n", "No.", "Product", "Price");
    printDivider();
    for (int i = 0; i < 10; i++) {
        printf("%-3d %-35s %s%.2f\n", i + 1, Np[i], symbol, Nprices[i] * rateValue);
    }
}

void displaypaso(int cur, char paso[][50], char symbol[], float Pprices[], float rateValue) {
    printf("\n%-3s %-35s %10s\n", "No.", "Product", "Price");
    printDivider();
    for (int i = 0; i < 15; i++) {
        printf("%-3d %-35s %s%.2f\n", i + 1, paso[i], symbol, Pprices[i] * rateValue);
    }
}
//string validation
int isValidNum(char str[]) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return 0;
        }
    }
    return 1;
}

//wait for enter
//main menu
void waitForEnter() {
    printf("%s", blue);
    printf("\n⏎ Press ENTER to return to main menu...");
    printf("%s", reset);
    while (getchar() != '\n');
    getchar();
}

//category
void waitForCha() {
    printf("%s", blue);
    printf("\n⏎ Press ENTER to return to Category...");
    printf("%s", reset);
    while (getchar() != '\n');
    getchar();
}

//exit with countdown
void exitprog() {
    printf("%s", gray);
    printf("\n🚪 Exiting...");
    for (int i = 3; i > 0; i--) {
        printf("\n⏳ %d", i);
        sleep(1);
    }
    printf("%s", reset);
    printf("%s%s", yellow, bold);
    printf("\n🙏 Thank you for using Pili KArt!\n");
    printf("%s", reset);
}
