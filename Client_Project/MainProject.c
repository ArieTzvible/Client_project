// 


//   Built by Arie Tzvible
//***********************************************
// Managing debts in a business from a portfolio
//***********************************************
// 
// The program reading a CSV file.That in every row, the data appears in the following section:
//First name, last name, social security number, telephone, amount dueand date.
//Any customer can receivemore than one line, first nameand last name must match ID otherwise
//will be printed Error.
// 
// The program builds a linked list where each customer has one cell that is updated with all
//debts or the payments and also updates the date to the most recent date, the customer's phone
//is also updated according to the most recent date.
//In addition, the system checks whether there is an error in each lineand updates it in the error list.
//
// The program then print the list of customers who have a debt.
//In addition, the program will be printing list with the errorsand notes where the errors are,
//if there are no errors the system will notify.
//
//***********************************
//
//At this point the system will issue a request to the user to enter a request.
// The user can request a to wiil print of of all debtors.
// The user must log in "print".
// 
// 
//Another option is printing according to a certain value with 4 ( = / != / < / > ) sorting options
// big small equal and different,
//     For example: "Select First name != Arie".
// 
// 
//You can also add a new line to the customer list.
// All customer fields must be filled in:
// - first name,
// - last name,
// - ID,
// - phone number,
// - amount of debt / payment,
// - date.
// For example : "set first name = Arie, ID = 123456789,..."
// 
// -- There is no obligation to enter the values in a particular order.
// -- All details must be entered(otherwise the system will print an error).
//
// The system will print a new line in the file with all the customer's details.
// If the customer exists, we will add the debt, if necessary we will update the details(date and phone).
// If the client does not exist we will add the client to the list.
// 
// 
//In order to exit the program and finish, enter "Quit".
// The program will release the list and close the program.
//


#include "HeaderProject.h"
//*********
#include "HeaderPrint.h"
#include "HeaderSpecific.h"
#include "HeaderDelet.h"
#include "HeaderTest.h"
#include "HeaderUser.h"

//*********

//�������� �������� 
int testingFirstName(PClient cell, void* value) {//First name check (specific)
	return strcmp(cell->firstName, (char*)value);//Comparison of the strings
}
int testingLastName(PClient cell, void* value) {//Last name check (specific)
	return strcmp(cell->lastName, (char*)value);//Comparison of the strings
}
int testingID(PClient cell, void* value) {//ID check (specific)
	return strcmp(cell->id, (char*)value);//Comparison of the strings
}
int testingPhone(PClient cell, void* value) {//Phone check (specific)
	return strcmp(cell->phone, (char*)value);//Comparison of the strings
}
int testingDebt(PClient cell, void* value) {//Debt check (specific)
	if (cell->debt < *(float*)value) return 1;
	if (cell->debt > *(float*)value) return -1;
	return 0;
}
int testingDate(PClient cell, void* value) {//Date check (specific)
	return comparingDates(cell->date, *(Date*)value);//Debt comparison
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//Memory release test

	char* selection = { 0 };//Create a pointer to receive the user's selection.
	char strUse[7] = { 0 };//Create a variable to receive the user's selection. 
	FILE* debtFile;//Create a pointer to the file.
	char* fileName = { 0 };//Create a pointer to get the file name
	char* tempFileName = "f.csv";//Declaration of a variable containing the file name.
	int fileNameDynamic = 0;//Creating a variable to test whether the pointer to the file is dynamic�
	fileName = tempFileName;//Getting the filename for the pointer


	while (!(debtFile = fopen(fileName, "r"))) {//Opening for reading only. 
		if (fileNameDynamic) free(fileName);
		//Sending to the function of receiving a name from the user (it is not necessary to insert CSV).
		fileName = getNewFileName();
		fileNameDynamic = 1;//Checking whether we received a dynamic string
	}

	ListManager managerClientList = createANewListManager();//Creating a new manageme� structure.
	creatingListOfClientsFromAFile(managerClientList, debtFile);//Building a list from a file.

	fclose(debtFile);//Closing a folder.

	printingDebtorsOnly(managerClientList->head);//Debtors printing.
	printingCellsWithErrors(managerClientList->headError);//Printing the cells with errors
	//Printing of instructions.      ********
	printf("\t\tWELCOME!");
	printf("\n\tThis program displays the debts from the file.");
	printf("\n\tAbove in the table are all the debtors that exist in the file.");
	printf("\n\n\tYou can add a debt or payment by adding a line to the file.");
	printf("\n\tIn order to add, all the details of the customer must be entered First name, Last name, ID,");
	printf("\n\tPhone, Debt and date(two digits for the day, two digits for the month, four digits for the year).");
	printf("\n\tFor example : \"Set First name = Arie, Last name = Tzvible, ID = 123456789, Phone = 0548484848,");
	printf("\n\tDate = 05/07/2022, Debt = -250.36\".");
	printf("\n\n\tYou can also sort by any existing parameter and the system will print according to the request:");
	printf("\n\tFirst name, Last name, ID, Phone number, Debt and Date(two digits for the day,");
	printf("\n\ttwo digits for the month, four digits for the year)");
	printf("\n\tThe sorting options are : greater: > , less: < , equal : =, and different : !=.");
	printf("\n\tand then enter the value to sort.");
	printf("\n\tFor example : \"Select ID = 123456789\".");
	printf("\n\n\tIn addition, in order to print the list of debtors one more time, you must enter \"Print\".");
	printf("\n\n\tIn addition, in order to print the list of errors one more time, you must enter \"Error\".");
	printf("\n\n\tTo exit, enter \"Quit\".");
	//                   ********
	do {
		printf("\n\n\t--> ");
		while (!scanf("%s", strUse)) {//Receive request from user
			printf("\n\n\t--> ");
		}
		selection = strUse;//Getting the string into a pointer.
		if (!(checkingIfTheNameIsProper(selection))) {//Checking the correctness of the letters and changing uppercase letters to lowercase.
			if (!(strcmp(selection, "select")))//Checks if he asked to sort
				sortingByRequest(managerClientList);//Sending to a sort function
			else if (!(strcmp(selection, "set"))) {//Checking whether he asked to add a new customer
				while (!(debtFile = fopen(fileName, "a"))) {//Opening the file for writing.
					//Sending to the function of receiving a name from the user (it is not necessary to insert CSV).
					if (fileNameDynamic) free(fileName);
					fileName = getNewFileName();
					fileNameDynamic;//Checking whether we received a dynamic string
				}
				addingClientFromUser(&managerClientList, debtFile);//Sending to the function of adding a new client.
				fclose(debtFile);//close file.
			}
			else if (!(strcmp(selection, "print")))//Checking whether printing was requested.
				printingDebtorsOnly(managerClientList->head);//Debtors printing.
			else if (!(strcmp(selection, "error")))//Checking whether printing was errors.
				printingCellsWithErrors(managerClientList->headError);//Printing the cells with errors
			else if ((strcmp(selection, "quit")))//A test that does not want to leave the program.
				printf("\tERROR! The category you requested was not found;\n");//Error printing.
		}
		else
			printf("\tERROR! Probably characters other than letters appear in the request category;\n");//Error printing.
	} while ((strcmp(selection, "quit")));//Loop exit conditions

	deletingTheEntireList(managerClientList);//Deleting the list.
	if (fileNameDynamic)//Checking if the string is dynamic.
		free(fileName);//Release the string.
	printf("\n\tBye Bye!!\n");

	return 0;
}