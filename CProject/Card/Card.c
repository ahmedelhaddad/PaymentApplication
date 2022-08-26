/* file Card.c*/
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Card.h"
#define MaxName 24
#define MinName 20
#define MaxDate 6
#define MaxPAN 19
#define MinPAN 16


EN_cardError_t getCardHolderName(ST_cardData_t* cardData) {
	EN_cardError_t getCardHolderName_checker;
	printf("Enter Card holder name [20-24 characters]: ");

	//scanf_s("%[^\n]s", cardData->cardHolderName, MaxName);
	gets(cardData->cardHolderName);

	size_t len = strlen(cardData->cardHolderName);

	if (cardData->cardHolderName == NULL || len > MaxName || len <MinName) {
		printf("WRONG NAME\n");
		getCardHolderName_checker = WRONG_NAME;
	}
	else{
		printf("Hello %s\n", cardData->cardHolderName);
		getCardHolderName_checker  = CARD_OK;
	}
	return getCardHolderName_checker;
	
}
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) {

	EN_cardError_t getCardExpiryDate_checker;
	printf("Enter Expiry date (MM/YY format): ");
	
	//scanf_s("%[^\n]s", cardData->cardExpirationDate, MaxDate);
	gets(cardData->cardExpirationDate);
	
		if (cardData->cardExpirationDate == NULL) {
				printf("DATE IS EXPIRED\n");
				getCardExpiryDate_checker = WRONG_EXP_DATE;
		}

		else if (!(isdigit(cardData->cardExpirationDate[0])) || !(isdigit(cardData->cardExpirationDate[1])) )
		{
				printf("DATE IS EXPIRED\n");
				getCardExpiryDate_checker = WRONG_EXP_DATE;
		}


		else if (!(isdigit(cardData->cardExpirationDate[3])) || !(isdigit(cardData->cardExpirationDate[4])))
		{
				printf("DATE IS EXPIRED\n");
				getCardExpiryDate_checker = WRONG_EXP_DATE;
		}
		else if (cardData->cardExpirationDate[2] != '/') {
				printf("DATE IS EXPIRED\n");
				getCardExpiryDate_checker = WRONG_EXP_DATE;
		}
		else {
				printf("The card expiry date is %s \n", cardData->cardExpirationDate);
				getCardExpiryDate_checker = CARD_OK;
		}
		return getCardExpiryDate_checker;
}

EN_cardError_t getCardPAN(ST_cardData_t* cardData) {
	EN_cardError_t getCardPAN_checker;
	printf("Please enter PAN: ");

	//scanf_s("%[^\n]s",cardData->primaryAccountNumber , MaxPAN);
	gets(cardData->primaryAccountNumber);

	if (cardData->primaryAccountNumber == NULL) 
	{
			printf("WRONG PAN\n");
			getCardPAN_checker = WRONG_PAN;
	}
	else if ((strlen(cardData->primaryAccountNumber) > MaxPAN) || (strlen(cardData->primaryAccountNumber) < MinPAN)) 
	{
			printf("WRONG PAN\n");
			getCardPAN_checker = WRONG_PAN;
	}
	else 
	{
			printf("The PAN %s is valid\n", cardData->primaryAccountNumber);
			getCardPAN_checker = CARD_OK;
	}
	return getCardPAN_checker;


}
