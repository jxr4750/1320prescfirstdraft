/* Questions, Comments, Concerns

*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//List of functions used
void firstTime(); //Used for the first time setup
void inputData();
void displayPatient();
void displayMeds();
void displayContacts();

enum Week{
    Sunday,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday
};

typedef struct Address{
    char streetName[10];
    int streetNumber;
}Address;

typedef struct Medication{
    char name[10];
    int dosage_amount;
    char dosage_unit[10];
}Medication;

typedef struct Patient{
    char firstName[10]; //Full Name
    char lastName[10];
    char middleName[10];
    int birthMonth; //DOB
    int birthDay;
    int birthYear;
    Address patientAddress;
}Patient;

typedef struct Emergency{
    char firstName[10];
    char lastName[10];
    char relation[10];
    int phoneNumber1, phoneNumber2, phoneNumber3;
    Address emergencyAddress;
}Emergency;

typedef struct Pharmacy{
    char storeName[10]; //Pharmacy Name
    Address pharmacyAddress; //Pharmacy Address
}Pharmacy;

void main()
{
    int decision;
    char choice;

    //checking for file, and if it doesnt exist then program will create it and run first time setup
    FILE* fptr;
    fptr = fopen("patientInfo.txt","r");

    if (fptr == NULL){
        printf("\nWould you like to run the first time setup?(y/n)");
        scanf("%c", &choice);
        if(choice == 'y')firstTime();
        else exit(0);
    }
    else printf("Data Loaded...\n");


    while(decision!= 10)
    {
        printf("\nMain Menu:\n\nWhat would you like to do?\n1.Input Data(First time reset)\n2.Display Reminders\n3.Refill Reminders\n4.Notes\n5.Display Pharmacy Info");
        printf("\n6.Display Emergency Contacts\n7.List all Current Medications\n8.Contact us(credits)\n9.Display Profile\n10.Exit\n\n");
        scanf("%d",&decision);

        switch(decision){
    case 1:
        printf("Inputing Data...\n"); //Put towards the bottom?
        inputData();
        break;
    case 2:
        printf("Displaying Reminders...\n");
        displayPatient(); //beta test
        break;
    case 3:
        printf("Refill Reminders...");
        break;
    case 4:
        printf("Reminder Notes...");
        break;
    case 5:
        printf("Displaying Pharmacy info...");
        break;
    case 6:
        printf("Displaying Emergency Contacts...\n");
        displayContacts();
        break;
    case 7:
        printf("Current Medications:\n");
        displayMeds();
        break;
    case 8:
        printf("\nVer. 1.0\nTimely Prescription Reminders TM: a time based prescription reminder system.\n\nMade by Joseph Ramsay, Saish Gondkar, Krishna Valkambe, and Soham Panchal\n\n");
        break;
    case 9:
        printf("Displaying Current Profile...\n"); //swap case 8/9 at some point
        displayPatient();
        break;
    case 10:
        printf("Have a nice day!");
        break;
    default:
        printf("Command not recognized, please select again");
        break;
        }//closes main menu

    } //closes while loop for main menu

} //closes main

void firstTime(){
    printf("\nFirst time setup placeholder text");
    FILE* fptr;
    fptr = fopen("patientInfo.txt","w");
    if (fptr == NULL) {
        printf("\n\nThe file is not opened. The program will exit now");
        exit(0);
    }
    else {
        printf("\n\nThe file is created Successfully.\n");
        inputData();
    }
    printf("\nYou are now ready to use the app, your profile has been set up.\nTo access more features, add more medicine, or contact us, please use the main menu.");
    fclose(fptr);
    return;
}

void inputData(){
    Patient temp;
    Emergency primary;
    Medication first;

    FILE *fptr;

    //Section 1: Establish patient full name
    fptr = fopen("patientInfo.txt","w");
    printf("Enter first name: ");
    scanf("%s", temp.firstName);
    printf("Enter middle name or initial: ");
    scanf("%s", temp.middleName);
    printf("Enter last name: ");
    scanf("%s", temp.lastName);
    fprintf(fptr, "Patient Name: %s %s %s", temp.firstName,temp.middleName,temp.lastName);


    //Section 2: Establish patient DOB
    printf("Enter Patient DOB (MM/DD/YYYY): ");
    scanf("%d %d %d", &temp.birthMonth, &temp.birthDay, &temp.birthYear);
    fprintf(fptr, "\nPatient DOB: %d %d %d", temp.birthMonth,temp.birthDay,temp.birthYear);
    fclose(fptr);

    //Section 3: Emergency contact (primary)
    fptr = fopen("emergencyContact.txt","w");
    printf("\nPlease enter your primary emergency contact (You may add more or switch them out at any time, for the first time set up we need at least one.");
    printf("It is recommended to be filling out the first time set up with them at your side)");
    printf("\nPlease input first name:");
    scanf("%s", primary.firstName);
    printf("Please input last name:");
    scanf("%s", primary.lastName);
    printf("Please input relation:");
    scanf("%s", primary.relation);
    printf("Please input phone number [format: +1 (XXX) XXX-XXXX]: ");
    scanf("%d %d %d", &primary.phoneNumber1, &primary.phoneNumber2, &primary.phoneNumber3);
    fprintf(fptr, "Emergency Contact (primary): %s %s %s (%d) %d-%d", primary.firstName, primary.lastName, primary.relation, primary.phoneNumber1, primary.phoneNumber2, primary.phoneNumber3);
    fclose(fptr);

    //section 4: Input first Medication
    fptr = fopen("medication.txt","w");
    printf("\nPlease enter your first prescription (You may add more or switch them out at any time, for the first time set up we need at least one.");
    printf("It is recommended to be filling out the first time set up with your primary emergency contact at your side)");
    printf("\nPlease input medication name:");
    scanf("%s", first.name);
    printf("Please input dosage amount followed by the unit (ex: 10 ml, 1 tablet)");
    scanf("%d %s", &first.dosage_amount, first.dosage_unit);
    fprintf(fptr, "Medications:\n1.%s %d %s", first.name, first.dosage_amount, first.dosage_unit);
    fclose(fptr);


}

void displayPatient(){
    FILE* fptr;
    char str[100];
    fptr = fopen("patientInfo.txt","r");
    while(fgets(str, 100, fptr)!= NULL){
    printf("%s", str);
    }
    fclose(fptr);
}

void displayMeds(){
    FILE* fptr;
    char str[100];
    fptr = fopen("medication.txt","r");
    while(fgets(str, 100, fptr)!= NULL){
    printf("%s", str);
    }
    fclose(fptr);
}

void displayContacts(){
    FILE* fptr;
    char str[100];
    fptr = fopen("emergencyContact.txt","r");
    while(fgets(str, 100, fptr)!= NULL){
    printf("%s", str);
    }
    fclose(fptr);
}



