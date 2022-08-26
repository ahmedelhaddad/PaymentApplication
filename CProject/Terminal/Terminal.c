/* file Terminal.c*/
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "Terminal.h"
#include "../Card/Card.h"

#define TransDate 10
#define MaxAmount 5000
EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) {

	EN_terminalError_t getTransactionDate_checker;
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	sprintf(termData->transactionDate, "%02d/%02d/%02d\n", tm.tm_mday, (tm.tm_mon + 1), (tm.tm_year + 1900));
	//printf("The Transaction date is %s\n", termData->transactionDate);

	//printf("%c",termData->transactionDate[2]);
	//printf("Enter Transaction date (DD/MM/YYYY format): ");
	////scanf_s("%[^\n]s", termData->transactionDate, TransDate);
	//fgets(termData->transactionDate,TransDate,stdin);
	//puts(termData->transactionDate);
	////printf("%d", termData->transactionDate[1]);

	if (termData == NULL) {
		printf("WRONG DATE\n");
		getTransactionDate_checker = WRONG_DATE;
	}
	else if (!(isdigit(termData->transactionDate[0])) || !(isdigit(termData->transactionDate[1])))
	{
		printf("WRONG DATE\n");
		getTransactionDate_checker = WRONG_DATE;
	}

	else if (!(isdigit(termData->transactionDate[3])) || !(isdigit(termData->transactionDate[4])))
	{
		printf("WRONG DATE\n");
		getTransactionDate_checker = WRONG_DATE;
	}

	else if (!(isdigit(termData->transactionDate[6])) || !(isdigit(termData->transactionDate[7])))
	{
		printf("WRONG DATE\n");
		getTransactionDate_checker = WRONG_DATE;
	}
	else if (!(isdigit(termData->transactionDate[8])) || !(isdigit(termData->transactionDate[9])))
	{
		printf("WRONG DATE\n");
		getTransactionDate_checker = WRONG_DATE;
	}

	else if ((termData->transactionDate[2]) != '/') {
		printf("/ is missing\n");
		getTransactionDate_checker = WRONG_DATE;
	}

	else if ((termData->transactionDate[5]) != '/') {
		printf("/ is missing\n");
		getTransactionDate_checker = WRONG_DATE;
	}
	else {
		printf("The transaction date is %s\n", termData->transactionDate);
		getTransactionDate_checker = TERMINAL_OK;
	}
	return getTransactionDate_checker;
}

EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData)
{
	//expiry date of format MM/YY
	//Trans date of format DD/MM/YYYY
	EN_terminalError_t isCardExpired_checker;
	if (cardData->cardExpirationDate[3] < termData->transactionDate[8]) {
		printf("Card is expired\n");
		isCardExpired_checker = EXPIRED_CARD;
	}
	else if (cardData->cardExpirationDate[3] == termData->transactionDate[8]) {

		if (cardData->cardExpirationDate[4] < termData->transactionDate[9]) {
			printf("Card is expired\n");
			isCardExpired_checker = EXPIRED_CARD;
		}
		else if (cardData->cardExpirationDate[4] == termData->transactionDate[9]) {

			if (cardData->cardExpirationDate[0] < termData->transactionDate[3]) {
				printf("Card is expired\n");
				isCardExpired_checker = EXPIRED_CARD;
			}
			else if (cardData->cardExpirationDate[0] == termData->transactionDate[3]) {

				if (cardData->cardExpirationDate[1] < termData->transactionDate[4]) {
					printf("Card is expired\n");
					isCardExpired_checker = EXPIRED_CARD;
				}
				else {
					printf("Card is accepted\n");
					isCardExpired_checker = TERMINAL_OK;
				}
			}
			else {
				printf("Card is accepted\n");
				isCardExpired_checker = TERMINAL_OK;
			}
		}
		else {
			printf("Card is not expired\n");
			isCardExpired_checker = TERMINAL_OK;
		}
	}
	else {
		printf("Card is not expired\n");
		isCardExpired_checker = TERMINAL_OK;
	}
	return isCardExpired_checker;
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData) {

	EN_terminalError_t getTransactionAmount_checker;
	//If the transaction amount is less than or equal to 0 will return INVALID_AMOUNT, else return OK.
	printf("Enter the transaction amount:");
	scanf_s("%f", &termData->transAmount);
	//printf("Your transaction amount is: %f\n", termData->transAmount);

	if (termData->transAmount <= 0.0) {
		printf("INVALID AMOUNT");
		getTransactionAmount_checker = INVALID_AMOUNT;
	}
	else {
		//printf("The transaction amount is %f \n", termData->transAmount);
		getTransactionAmount_checker = TERMINAL_OK;
	}
	return getTransactionAmount_checker;
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData) {
	EN_terminalError_t isBelowMaxAmount_checker;
	if (termData->transAmount > termData->maxTransAmount) {
		printf("Max amount is exceeded \n");
		isBelowMaxAmount_checker =  EXCEED_MAX_AMOUNT;
	}
	else {
		isBelowMaxAmount_checker = TERMINAL_OK;
	}
	return isBelowMaxAmount_checker;
}

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData) {
	//If transaction max amount less than or equal to 0 will return INVALID_MAX_AMOUNT error, else return TERMINAL_OK.
	/*printf("Max transaction amount is: ");
	scanf_s("%f", &termData->maxTransAmount);
	if (termData->maxTransAmount <= 0 || (termData->transAmount > termData->maxTransAmount)) {
		printf("Invalid Max Amount \n");
		return INVALID_MAX_AMOUNT;
	}
	else {
		printf("Transaction amount %f is not exceeded, safe to proceed \n", termData->maxTransAmount);
		return TERMINAL_OK;
	}*/
	termData->maxTransAmount = MaxAmount;
	printf("Max transaction amount is %f\n", termData->maxTransAmount);
	if (termData->maxTransAmount <= 0) {
		return INVALID_MAX_AMOUNT;
	}
	else {
		return TERMINAL_OK;
	}

}
