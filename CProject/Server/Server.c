/* file Server.c*/
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include "Server.h"
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "../Terminal/Terminal.h"
#include "../Card/Card.h"
#include "../Application/App.h"


ST_accountsDB_t accountsDB[255] = { {1000.0,RUNNING,"8989374615436851"}, {2000.0,BLOCKED,"5807007076043875"}, {500.0,RUNNING,"7347576842345124"},{4000,RUNNING,"6584597822761234"}, {9000,BLOCKED,"9374658671523487"} };
ST_transaction_t transDB[255] = { 0 }; //fill array with zeros
uint32_t accountNumber =0;
uint32_t sequence_number =0;

EN_serverError_t isValidAccount(ST_cardData_t* cardData) {

	EN_serverError_t isValidAccount_Checker;
	//bool flag = false;
	for (accountNumber = 0; accountNumber < 255; accountNumber++) {
		if (strcmp(cardData->primaryAccountNumber, accountsDB[accountNumber].primaryAccountNumber) == 0) { //if equal PAN
			//flag = true;
			isValidAccount_Checker = SERVER_OK;
			//accountNumber = 0 + accountNumber;
			printf("Account found\n");
			break;
		}
		//if (flag == false)
		else {
			//printf("Account not found\n");
			isValidAccount_Checker = ACCOUNT_NOT_FOUND;

		}
	}
	return isValidAccount_Checker;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData) {

	EN_serverError_t isAmountAvailable_Checker;

	if (termData->transAmount <= accountsDB[accountNumber].balance) {
		//printf("%d\t", accountNumber);
		printf("Balance is available\n");
		isAmountAvailable_Checker = SERVER_OK;
	}
	else {
		//printf("%d\t", accountNumber);
		printf("Account number %d has LOW BALANCE \n", accountNumber);
		isAmountAvailable_Checker = LOW_BALANCE;
	}

	return isAmountAvailable_Checker;

}


EN_serverError_t saveTransaction(ST_transaction_t* transData) {
	EN_serverError_t saveTransaction_checker;

	transData->transactionSequenceNumber = sequence_number;
	transDB[sequence_number] = *transData;

	if (transData->transactionSequenceNumber>255) {
		//transaction database is full
		saveTransaction_checker = SAVING_FAILED;
	}

	else {
		transDB[transData->transactionSequenceNumber].cardHolderData = transData->cardHolderData;
		transDB[transData->transactionSequenceNumber].terminalData = transData->terminalData;
		transDB[transData->transactionSequenceNumber].transactionSequenceNumber = transData->transactionSequenceNumber;
		sequence_number++;
		saveTransaction_checker = SERVER_OK;
	}
	return saveTransaction_checker;
}
//EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t* transData) {
//
//}



EN_transState_t recieveTransactionData(ST_transaction_t* transData) {


	EN_transState_t recieveTransactionData_Checker;

	//if ((saveTransaction(transData) == SAVING_FAILED)) {
	//	recieveTransactionData_Checker = INTERNAL_SERVER_ERROR;
	//	printf("Internal server error");
	//}
	//else{
	//	printf("%d", &transDB);
	//}
	if (isValidAccount(&transData->cardHolderData) == ACCOUNT_NOT_FOUND) {
		printf("fraud");
		recieveTransactionData_Checker = FRAUD_CARD;
	}

	else if (isAmountAvailable(&transData->terminalData) == LOW_BALANCE) {

		printf("DECLINED_INSUFFECIENT_FUND");
		recieveTransactionData_Checker = DECLINED_INSUFFECIENT_FUND;
	}

	else {
			printf("TRANSACTION APPROVED\n");

			printf("Balance before transaction = %f\n", accountsDB[accountNumber].balance);
			accountsDB[accountNumber].balance = (accountsDB[accountNumber].balance - transData->terminalData.transAmount);
			printf("Balance after transaction = %f", accountsDB[accountNumber].balance);
			recieveTransactionData_Checker = APPROVED;
		}
	
	return  recieveTransactionData_Checker;


}





