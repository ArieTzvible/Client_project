
#include "HeaderProject.h"
#include "HeaderStruct.h"
#include "HeaderPrint.h"

void printTableHead(char* print) {//Creating a printable table header
	printf("\n\n\t##################################################################################################\n");
	printf("\t#                                                                                                #\n");
	printf("\t#    ****************************************************************************************    #\n\t#");
	//creating a header in the middle of the table *****
	for (int i = 0; i < (47 - (strlen(print) / 2)); i++)
		printf(" ");
	printf("%s", print);
	if (strlen(print) % 2 == 0)
		for (int i = 0; i < (49 - (strlen(print) / 2)); i++)
			printf(" ");
	else
		for (int i = 0; i < (48 - (strlen(print) / 2)); i++)
			printf(" ");
	printf("#\n\t#    ****************************************************************************************    #\n");
	printf("\t# ============================================================================================== #\n");//printing subheadings
	printf("\t# | %-16s | %-15s | %-12s | %-13s | %-10s | %-9s | #\n", " First name:", " Last name:", " ID:",
		" Phon:", " Date:", " Debt:");
	printf("\t# |============================================================================================| #\n");
}

void printCell(PClient cell) {//printing a single cell
	printf("\t# | %-16s | %-15s | %-12s | %-13s | %02d/%02d/%04d | %-9.2f | #\n",
		cell->firstName, cell->lastName, cell->id, cell->phone, cell->date.day,
		cell->date.month, cell->date.year, cell->debt);
}

void printingDebtorsOnly(PClient head) {//printing a list of debtors
	if (!head) {
		printf("\tThere are no debts in the current list;\n");//print error
		return;
	}
	printListDebtsFromTheSmallestToTheLargest(head, "List of Debtors  ");//Sending to the function that prints the debt from the largest to the smallest
}

void printListDebtsFromTheSmallestToTheLargest(PClient head, char* mainTitle) {//print the debt from the largest to the smallest
	PClient temp = head;//Creating a variable that will contain the head of the list
	int flag = 0;
	while (temp != NULL) {//Check that the cell is not empty
		if (temp->debt < 0) {
			if (!flag) {
				printTableHead(mainTitle);
				flag = 1;
			}
			printCell(temp);//Send to cell print function
			printf("\t# |--------------------------------------------------------------------------------------------| #\n");
		}
		temp = temp->next;//Move the pointer to the next cell
	}
	printf("\t# ============================================================================================== #\n");
	printf("\t#                                                                                                #\n");
	printf("\t##################################################################################################\n\n\n");
}


void printingCellsWithErrors(PClient head) {//print the cells with errors
	if (head) {
		printTableHead("ERRORS!!  ");//Send to create a table with a header
		PClient temp = head;//creating a pointer to the top of the list
		while (temp) {
			int printsThatWere = 0;//Creating a variable to maintain the integrity of the table
			printCell(temp);//Cell printing
			if (temp->error.comparisonFirstName || temp->error.comparisonLastName) {
				if (temp->error.comparisonFirstName)
					printf("\t# |  The first name does not match the ID number -> %s != %-16s              | #", temp->id, temp->firstName);// print error
				if (temp->error.comparisonFirstName && temp->error.comparisonLastName)
					printf("\n");
				if (temp->error.comparisonLastName)
					printf("\t# |  The last name does not match the ID number -> %s != %-15s                | #", temp->id, temp->lastName);// print error
			}
			else {
				if (temp->error.lacksValues)
					printErrors("lacks values", &printsThatWere);//Send to error print function
				if (temp->error.id)
					printErrors("I.D.", &printsThatWere);//Send to error print function 
				if (temp->error.firstName)
					printErrors("first name", &printsThatWere);//Send to error print function
				if (temp->error.lastName)
					printErrors("last name", &printsThatWere);//Send to error print function 
				if (temp->error.phone)
					printErrors("phone", &printsThatWere);//Send to error print function
				if (temp->error.date)
					printErrors("date", &printsThatWere);//Send to error print function
				if (temp->error.debt)
					printErrors("debt", &printsThatWere);//Send to error print function			
				if (printsThatWere > 0) {
					for (int i = printsThatWere; i < 91; i++)
						printf(" ");//print spaces until the end of the row in the table
					printf("| #");//closing the row in the table
				}
			}
			printf("\n\t# |--------------------------------------------------------------------------------------------| #\n");

			temp = temp->next;//Move the pointer to the next cell
		}
		printf("\t# ============================================================================================== #\n");
	}

	else if (!head) {//Print when there are no errors
		printf("\n\t##################################################################################################\n");
		printf("\t#                                                                                                #\n");
		printf("\t#    ****************************************************************************************    #\n");
		printf("\t#                                                                                                #\n");
		printf("\t#     $$$$$$$$$$$$$$$$$$$$$$  There are no errors in the client list  $$$$$$$$$$$$$$$$$$$$$$     #\n");
		printf("\t#                                                                                                #\n");
		printf("\t#    ****************************************************************************************    #\n");
	}
	printf("\t#                                                                                                #\n");
	printf("\t##################################################################################################\n\n\n");
}

void printErrors(char* error, int* printsThatWere) {//print the error
	if (*printsThatWere == 0) {//print the beginning of the first line of the error notes
		printf("\t# | ERROR! ");
		*printsThatWere += 7;//added to the number of characters printed
	}
	if (*printsThatWere + (strlen(error) + 16) >= 85) {// check that it will not exceed the size of the row in the table
		for (int i = *printsThatWere; i < 85; i++)
			printf(" ");// print spaces until the end of the row in the table
		printf("      | #\n\t# | ");//creating a new row in the table
		*printsThatWere = 0;// Setting the number of printed characters to 0
	}
	if (*printsThatWere != 7) {// checking that it is not a first print
		printf(" and ");
		*printsThatWere += 5;//added to the number of characters printed
	}
	printf("uncorect %s,", error);
	*printsThatWere += ((int)strlen(error) + 10);//added to the number of characters printed
}

void printASortedCell(PClient previousList, int flag) {//Getting for print the sort cell and checking if the flag is raised
	if (!flag)//Checking if this is the first time
		printTableHead("Sorted List As Per Your Request");//Sending for printing the table header
	if (previousList->debt < 0) {//	Checking if there is a debt
		printCell(previousList);//Send to cell print function
		printf("\t# |--------------------------------------------------------------------------------------------| #\n");
	}
}

