/*
Divya Jagadeesh
CMPSC 121 - Spring 2015
Sec 004

Purpose:	Create a program that mimics a savings account based on monthly interest, deposits, and withdrawals.

Input:		interest (interest added on monthly)
			initialDeposit (initial user inputted deposit)
			deposit (user inputted deposit)
			withdrawal (user inputted withdrawal)
			answerD (user prompted yes/no that determines whether they want a deposit that month)
			answerW (user prompted yes/no that determines whether they want a withdrawal that month)
			year (user prompted yes/no that determines whether they'd like to keep using the savings bank for another year)

Output:		interestAmt (calculated interest amount based on original interest rate, after deposit/withdrawal for 
			month has been made)
			balance (amount user has at the end of each month after deposit/withdrawal and interest)	

Processing:	A do-while loop keeps executing as long as the user wants to use the savings bank for a year.
			A for loop executes the calculations for 12 months. Then the user will be prompted to respond
			whether they'd like to continue using the bank for another year.
			Calculations in for loop:
			balance = balance +/- deposit/withdrawal
			interestAmt = (balance * interest) / 12
			balance = balance + interestAmt
			There are 3 while loops. The first while loop confirms the user put in an initial deposit greater
			than or equal to $250.00. The second while loop confirms that the user inputs a positive deposit
			amount. The third while loop confirms that the user inputs a positive withdrawal amount and that
			the withdrawal amount does not make the balance go below $250.00.

Test Cases:	interest: 5%						deposit: no
			initial deposit: 1000				withdrawal: yes
			Initial balance: $1005.00			amount: $100
												Month 7 balance: $1223.00
			deposit: yes						
			withdrawal: no						deposit: no
			Month 1 balance: $1010.03			withdrawal: yes
												amount: $500
			deposit: yes						Month 8 balance: $726.61
			amount: $150						
			Month 2 balance: $1165.83			deposit: no
												withdrawal: no
			deposit: no							Month 9 balance: $730.24
			withdrawal: yes
			amount: $865						deposit: no
			Month 3 balance: $302.33			withdrawal: no
												Month 10 balance: $733.90
			deposit: no
			withdrawal: no						deposit: no
			Month 4 balance: $303.84			withdrawal: no
												Month 12 balance: $737.57
			deposit: yes				
			amount: $1000						another year?: no
			Month 5 balance: $1310.36

			deposit: no
			withdrawal: no
			Month 6 balance: $1316.91
*/

#include <iostream>
#include <iomanip>
using namespace std;

int main() {

	double	interest, // user inputted interest
			initialDeposit, // user inputted initial deposit
			interestAmt, // calculated interest (changes monthly)
			balance, // new monthly balance
			withdrawal, // user inputted withdrawal money
			deposit, // user inputted deposit money
			monthCounter; // counts the months throughout the year
	char	answerD, // yes/no to whether user wants to deposit money that month
			answerW, // yes/no to whether user wants to withdraw money that month
			year = 'y'; // yes/no to whether user wants to use bank for another year

	cout << "Thanks for using JR Bank for your savings" << endl
		<< "What is the yearly interest rate for this account? ";
	cin >> interest; // asks user for interest

	interest /= 100; 

	cout << "How much money will you initially deposit? ";
	cin >> initialDeposit; // asks user for initial deposit

	// make sure initial deposit is at least $250
	while (initialDeposit < 250) {
		cout << "Your inital deposit must be at least $250.00." << endl;
		cout << "How much money will you initially deposit? ";
		cin >> initialDeposit;
	}

	// calculate first interest amount
	interestAmt = (initialDeposit * interest) / 12;
	
	// calculates first balance
	balance = initialDeposit + interestAmt;
	cout << "\nYou currently have $" << setprecision(2) << fixed << showpoint << balance << " in your account." << endl;

	do {

		for (monthCounter = 1; monthCounter < 13; monthCounter++) {

			cout << "Would you like to deposit more money into this account (y/n)? ";
			cin >> answerD; // asks user whether they'd like to deposit money

			if (answerD == 'n') {
				cout << "Would you like to withdraw any money from this account (y/n)? ";
				cin >> answerW; // asks the user whether they'd like to withdraw money
				if (answerW == 'y') {
					cout << "How much money would you like to withdraw? ";
					cin >> withdrawal; 
					if (withdrawal < 0) {
						withdrawal *= -1;
						balance -= withdrawal;
						withdrawal *= -1;
					}
					else {
						balance -= withdrawal;
					}
					while (withdrawal < 0 || balance < 250) { // makes sure withdrawal is not negative and it doesn't make the balance less that $250
						if (withdrawal < 0) {
							withdrawal *= -1;
						}
						balance += withdrawal;
						// prompts user for correct withdrawal
						cout << "A withdrawal must be greater than zero (0.00) and\n"
							<< "cannot cause the balance to fall below $250.00!\n";
						cout << "How much money would you like to withdraw? ";
						cin >> withdrawal;
						balance -= withdrawal;
					}
					interestAmt = (balance * interest) / 12;
					balance += interestAmt;
				}
				else { // calculates new balance when the user selects no for deposit and withdrawal
					interestAmt = (balance * interest) / 12;
					balance += interestAmt;
				}
			}
			else if (answerD == 'y') {
				cout << "How much money would you like to deposit? ";
				cin >> deposit;
				while (deposit < 0) { // makes sure deposit is greater than 0
					cout << "A deposit must be greater than zero (0.00)!" << endl;
					cout << "How much money would you like to deposit? ";
					cin >> deposit;
				}
				balance += deposit;
				interestAmt = (balance * interest) / 12;
				balance += interestAmt;
			}

			// outputs current balance every month
			cout << "\nYou currently have $" << setprecision(2) << fixed << showpoint << balance << " in your account." << endl;
		}

		// asks user if they'd like to continue another year
		cout << "Would you like to keep the account for another year (y/n)? ";
		cin >> year;
		
		if (year == 'y') {
			monthCounter = 1;
		}

	} while (year == 'y');

	return 0;
}