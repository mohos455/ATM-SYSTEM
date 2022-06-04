#include <iostream>
#include <cstring>
#include <limits>

using namespace std;
int accounts_counter;

// this Function check if the input value have any non-numerical values
// if there is a non-numerical get input until the data is numerical
double get_numerical_value() {
    double value;
    cin >> value;
    //check if the input is numbers only
    while (cin.fail() || cin.peek() != '\n') {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "please enter numerical value: ";
        cin >> value;
    }
    return value;
}

// This function get the value and check if positive
double get_amount() {

    double amount = get_numerical_value();
    while (amount <= 0) {
        cout << "please enter positive amount: ";
        amount = get_amount();
    }
    return amount;
}
// the main class
class ATM {
private:
    char Account_Name[1000];
    double Amount = 0;
    char Card_Number[19];

    void set_card_number(char number[]) {
        // check card number
        bool Card = false;
        while (!Card) {
            bool Same_Numbers = true, Only_Numbers = true;
            int count = 0;
            cout << "Please Enter The Card Number:(10 numbers with no spaces)\n";
            cin >> number;
            // check if card number digits has the same value if true >>>>> count will equal 10
            for (int a = 0; number[a] != '\0'; a++) {
                count++;
                if (a > 1) {
                    if (number[a] != number[0])
                        Same_Numbers = false;
                }
                // check if card number has numbers only
                // isdigit return true if all digits are number
                if (!isdigit(number[a])) {
                    Only_Numbers = false;
                }
            }
            // check if there is an invalid condition if there return the operation and request another value
            if (Same_Numbers || count != 10 || !Only_Numbers) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Please Enter only Strong 10 Different Integer Numbers" << endl;
                Card = false;
                continue;

            }
            else {
                Card = true;
            }
        }
    }

public:

    void create_new_acc() {
        bool Name = false;
        cin.ignore();
        // check account name
        while (!Name) {
            cout << "Please Enter The account Name:\n";
            cin.getline(Account_Name, 1000);
            // check name length less than 100 letter
            if (strlen(Account_Name) > 100) {
                cout << "Enter a Valid Name less than 100 character" << endl;
                continue;
            }
            // check name length more than 1 letter
            if (strlen(Account_Name) == 0) {
                cout << "Enter a Valid Name 1 character at least";
            }
            // isspace function return true is the value is a space
            // isalpha return true if the value is char

            for (int i = 0; i < strlen(Account_Name); i++) {
                // check if name starts with space
                if (isspace(Account_Name[0])) {
                    cout << "name must start with letter" << endl;
                    Name = false;
                    break;
                    // check if name has letters and space only
                }
                else if (!isalpha(Account_Name[i]) && !isspace(Account_Name[i])) {
                    cout << "Enter Valid Name With only Characters" << endl;
                    Name = false;
                    break;
                    // check if name has 2 spaces in a row
                }
                else if (isspace(Account_Name[i]) && isspace(Account_Name[i + 1])) {
                    cout << "name can't have double spaces\n";
                    Name = false;
                    break;
                }
                    // if there is any un wanted case return to take new value from the user
                    // if there isn't , save the input
                else {
                    Name = true;
                }
            }

        }
        // then go to take the card number and check it with the function set_card_number if it is valid
        // check card number
        set_card_number(Card_Number);
        // if it is valid then check if it is

        // check if card number already registered already registered or not

        while (search(Card_Number, true) >= 0) {
            cout << "card number already registered\n";
            //if it already registered already registered request another value

            set_card_number(Card_Number);
        }
        // Prent all data
        Print_acc_data(*this);
        accounts_counter++;
    }


    //Declaration the main Function of the program
    void Deposit();

    void Transfer();

    void Withdrawal();

    void Print_acc_data(ATM acc) {
        cout << "Name: " << acc.Account_Name << "\nCard number: " << acc.Card_Number << "\nAmount: " << acc.Amount
             << '\n';
    }

    static int search(char card_number[], bool create);
};


ATM accounts[100]; // make array of the class

int ATM::search(char card_number[], bool create) {
    // search for card number in accounts if exist return index else return -1
    for (int i = 0; i < 100; ++i) {
        if (strcmp(accounts[i].Card_Number, card_number) == 0) {
            if (!create)
                return i;
            if (accounts_counter != i)
                return i;
        }
    }
    return -1;
}

void ATM::Deposit() {
    //Add Money to the account
    char number[19];
    set_card_number(number);
    double deposited_amount;
    // check if account exist by searching for the card number in all arrays of the class
    while (search(number, false) < 0) {
        cout << "account doesn't exist\n";
        return;
    }
    // if there is account
    // request the amount and check if it is positive integer or not with the get_amount fun if true then add the amount
    cout << "Please enter the amount to be deposited: ";
    deposited_amount = get_amount();
    accounts[search(number, false)].Amount += 1.01 * deposited_amount;
    Print_acc_data(accounts[search(number, false)]);


}

void ATM::Transfer() {
    char sending[19], receiving[19];
    cout << "Sending Account ";
    set_card_number(sending);
    // check if sending account exist by searching for the card number in all arrays of the class

    while (search(sending, false) < 0) {
        cout << "account doesn't exist";
        return;
    }
    // check if account have money on it or not
    if (accounts[search(sending, false)].Amount == 0) {
        cout << "can't send money from empty account\n";
        return;
    }
    cout << "Receiving Account ";
    set_card_number(receiving);
    // check if receiving account exist by searching for the card number in all arrays of the class
    while (search(receiving, false) < 0) {
        cout << "account doesn't exist\n";
        return;
    }
    // check if sending account and receiving account are the same
    if (strcmp(sending, receiving) == 0) {
        cout << "can't transfer money to the same account\n";
        return;
    }
    // if all Conditions is true
    // then take the amount want to transform and check if it is positive integer
    double transferred_amount;
    int s = search(sending, false), r = search(receiving, false);
    cout << "Please enter the amount to be transferred:";
    transferred_amount = get_amount();
    // check if sending account has enough money to transfer
    while (1.015 * transferred_amount >= accounts[s].Amount) {
        cout << "Can't transfer more money than your account have. Enter another amount: ";
        transferred_amount = get_amount();
    }
    accounts[s].Amount -= 1.015 * transferred_amount;
    accounts[r].Amount += 0.985 * transferred_amount;
    cout << "Sending Account ";
    Print_acc_data(accounts[s]);
    cout << "Receiving Account ";
    Print_acc_data(accounts[r]);

}

void ATM::Withdrawal() {
    char number[19];
    set_card_number(number);
    double withdrawn_amount;
    // check if  account exist
    while (search(number, false) < 0) {
        cout << "account doesn't exist";
        return;
    }
    if (accounts[search(number, false)].Amount == 0) {
        cout << "can't withdraw money from empty account\n";
        return;
    }
    int n = search(number, false);
    cout << "Please enter the amount to be withdrawn: ";
    withdrawn_amount = get_amount();
    // check if  account has enough money to withdraw
    while (1.03 * withdrawn_amount >= accounts[n].Amount) {
        cout << "Can't withdraw more money than your account have. Enter another amount: ";
        withdrawn_amount = get_amount();

    }
    accounts[n].Amount -= 1.03 * withdrawn_amount;
    Print_acc_data(accounts[n]);


}

int main() {
    bool exit = false;
    int operation;
    // the main window of our program
    while (!exit) {
        cout << "1----Create new account\n";
        cout << "2----Deposit\n";
        cout << "3----transfer to another account\n";
        cout << "4----withdrawal\n";
        cout << "5----exit\n";
        cout << "please enter the number of operation:";
        operation = (int)get_numerical_value();

        switch (operation) {
            case 1:
                if (accounts_counter <= 100) {
                    accounts[accounts_counter].create_new_acc();
                    break;
                }
                else {
                    cout << "There is 100 Account,You can not create more accounts" << endl;
                    break;
                }
            case 2:
                accounts[accounts_counter].Deposit();
                break;
            case 3:
                accounts[accounts_counter].Transfer();
                break;
            case 4:
                accounts[accounts_counter].Withdrawal();
                break;
            case 5:
                exit = true;
                break;
            default:
                cout << "please enter a number between 1 and 5\n";


        }


    }

}
