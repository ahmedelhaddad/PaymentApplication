#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Card/Card.h"
#include "Terminal/Terminal.h"
#include "Server/Server.h"
#include "Application/App.h"


//int main() {
	//ST_cardData_t x;
	//getCardHolderName(&x);
	//getCardExpiryDate(&x);
	//getCardPAN(&x);
	//ST_terminalData_t y;
	////getTransactionDate(&y);
	////isCardExpired(x, y);
	//getTransactionAmount(&y);
	////setMaxAmount(&y);
	////isBelowMaxAmount(&y);
	//ST_transaction_t z;
	////isValidAccount(&x);
	////isAmountAvailable(&y);
	//recieveTransactionData(&z);

//	ST_transaction_t transactionData = { 0 };
//	getCardHolderName(&transactionData.cardHolderData);
//	getCardExpiryDate(&transactionData.cardHolderData);
//	getCardPAN(&transactionData.cardHolderData);
//	//getTransactionDate(&transactionData.terminalData.transactionDate);
//	//isCardExpired(&transactionData.cardHolderData.cardExpirationDate, &transactionData.terminalData.transactionDate);
//	getTransactionAmount(&transactionData.terminalData.transAmount);
//	setMaxAmount(&transactionData.terminalData.maxTransAmount);
//	isBelowMaxAmount((&transactionData.terminalData.maxTransAmount));
//	//isValidAccount(&transactionData.cardHolderData);
//	//isAmountAvailable(&transactionData.terminalData);
//	//recieveTransactionData(&transactionData);
//	//void appStart(void);
//}