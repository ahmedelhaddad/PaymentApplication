/* file App.c*/
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include "App.h"
#include "../Server/Server.h"
#include "../Card/Card.h"
#include "../Terminal/Terminal.h"

#define appStart main

void appStart(void) {

	//ST_transaction_t transactionData = { 0 };
	//getCardHolderName(&transactionData.cardHolderData);
	//getCardExpiryDate(&transactionData.cardHolderData);
	//getCardPAN(&transactionData.cardHolderData);
	////getTransactionDate(&transactionData.terminalData.transactionDate);
	////isCardExpired(&transactionData.cardHolderData.cardExpirationDate, &transactionData.terminalData.transactionDate);
	//getTransactionAmount(&transactionData.terminalData.transAmount);
	////setMaxAmount(&transactionData.terminalData.maxTransAmount);
	////isBelowMaxAmount((&transactionData.terminalData.maxTransAmount));
	////isValidAccount(&transactionData.cardHolderData);
	////isAmountAvailable(&transactionData.terminalData);
	//recieveTransactionData(&transactionData);


	/////////// DATABASE///////////
	ST_accountsDB_t accountsDB[255] = { {1000.0,RUNNING,"8989374615436851"}, {2000.0,BLOCKED,"5807007076043875"}, {500.0,RUNNING,"7347576842345124"},{4000,RUNNING,"6584597822761234"}, {9000,BLOCKED,"9374658671523487"} };
	ST_transaction_t transDB[255] = { 0 }; //fill array with zeros

	///////////CARD///////////
	ST_transaction_t transactionData = { 0 };
		if (getCardHolderName(&transactionData.cardHolderData) == WRONG_NAME) {
			//printf("You have 1 more try. Please re-enter as specified below\n");
			//getCardHolderName(&transactionData.cardHolderData);
			return;
		}
		if (getCardExpiryDate(&transactionData.cardHolderData) == WRONG_EXP_DATE) {
			//printf("You have 1 more try. Please re-enter as specified below\n");
			//getCardExpiryDate(&transactionData.cardHolderData);
			return;
		}
		if (getCardPAN(&transactionData.cardHolderData) == WRONG_PAN) {
			//printf("You have 1 more try. Please re-enter as specified below\n");
			//getCardPAN(&transactionData.cardHolderData);
			return;
		}
	
	
	///////////TERMINAL///////////
	if (getTransactionDate(&transactionData.terminalData) == WRONG_DATE) {
		return;
	}
	if (isCardExpired(&transactionData.cardHolderData, &transactionData.terminalData) == EXPIRED_CARD) {
		return;
	}
	setMaxAmount(&transactionData.terminalData);


	if (getTransactionAmount(&transactionData.terminalData) == INVALID_AMOUNT) {
		return;
	}

	if (isBelowMaxAmount((&transactionData.terminalData)) == EXCEED_MAX_AMOUNT) {
		return;
	}

	///////////SERVER///////////
	recieveTransactionData(&transactionData);

}