/* Questions, Comments, Concerns
To Do:
-Pickup for next time:Start: Line 318, write schedule down on its own custom text file. create functions to create/display schedule
-fix the casing order (low priority)
-link reminder to schedule(days of the week?)
-reorganize inputdata function into 3 distinct input functions(if time allows)
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
void displayPharmacy();
void samedayReminders();
void stateToday(int day);
void stateMonth(int month);

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
    int schedule[7];
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

    time_t now = time(NULL);
    struct tm *local = localtime(&now); //for time functions

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
        samedayReminders();
        break;
    case 3:
        printf("Refill Reminders..."); //extra QOL
        break;
    case 4:
        printf("Reminder Notes..."); //extra QOL
        break;
    case 5:
        printf("Displaying Pharmacy info...");
        displayPharmacy();
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
        printf("\nVer. 1.01\nTimely Prescription Reminders TM: a time based prescription reminder system.\n\nMade by Joseph Ramsay, Saish Gondkar, Krishna Valkambe, and Soham Panchal\n\n");
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

void stateToday(int day){

    switch (day){
    case 0:
        printf("Today is Sunday");
        break;
    case 1:
        printf("Today is Monday");
        break;
    case 2:
        printf("Today is Tuesday");
        break;
    case 3:
        printf("Today is Wednesday");
        break;
    case 4:
        printf("Today is Thursday");
        break;
    case 5:
        printf("Today is Friday");
        break;
    case 6:
        printf("Today is Saturday");
        break;
    }
}

void stateMonth(int month){
    switch (month)
    {
    case 0:
        printf("January");
        break;
    case 1:
        printf("February");
        break;
    case 2:
        printf("March");
        break;
    case 3:
        printf("April");
        break;
    case 4:
        printf("May");
        break;
    case 5:
        printf("June");
        break;
    case 6:
        printf("July");
        break;
    case 7:
        printf("August");
        break;
    case 8:
        printf("September");
        break;
    case 9:
        printf("October");
        break;
    case 10:
        printf("November");
        break;
    case 11:
        printf("December");
        break;
    }
}

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
    Medication *mptr, first;
    mptr = &first;
    int choice;

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

    for(int i = 0; i<7; i++){
        mptr->schedule[i] = 1; //make schedule {1,1,1,1,1,1,1}
    }

    printf("\nHow often is this medication prescribed?\n1.Everyday\n2.Every other day\n3.Every 3 days\n4.Weekdays\n5.Weekends\n6.Custom...\n");
    scanf(" %d",&choice);
    switch (choice){
    case 1:
        printf("\nSchedule for this medication is compiled");
        break;
    case 2:
        for(int i = 1; i<7; i++){
        if(mptr->schedule[i-1] == 1)mptr->schedule[i] = 0; //make schedule {1,0,1,0,1,0,1}
        }
        break;
    case 3:
        mptr->schedule[1] = 0;
        mptr->schedule[2] = 0;
        mptr->schedule[4] = 0;
        mptr->schedule[5] = 0; //NOT DONE(kinda, patch job.redo when 14 day schedule gets implemented): make schedule {1,0,0,1,0,0,1}
        break;
    case 4:
        mptr->schedule[0] = 1;
        mptr->schedule[6] = 1; //NOT DONE(kinda, patch job.redo when 14 day schedule gets implemented): make schedule {0,1,1,1,1,1,0}
        break;
    case 5:
        for(int i = 1; i<6; i++){
        mptr->schedule[i] = 0; //NOT DONE(same as above): make schedule {1,0,0,0,0,0,1}
        }
        break;
    case 6:
        for(int i = 0; i<7; i++){
        mptr->schedule[i] = 1; //NOT DONE: make schedule custom
        }
        break;
    }
    printf("\nSchedule is: ");
    for(int j = 0; j<7; j++){
        printf("%d, ",mptr->schedule[j]);
    }

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

void displayPharmacy(){
    char choice;
    FILE* fptr;
    char str[100];
    fptr = fopen("pharmacyInfo.txt","r");

    if (fptr == NULL){
        printf("\nWould you like to setup your local physician and pharmacy information?(y/n)\n");
        scanf(" %c", &choice);
        if(choice == 'y')inputPharmacy();
        else return;
    }
    else{
    while(fgets(str, 100, fptr)!= NULL){
        printf("%s", str);
    }
    fclose(fptr);
    }
}

void inputPharmacy(){

    Pharmacy temp;
    FILE *fptr;
    char doctor[20];

    fptr = fopen("pharmacyInfo.txt","w"); //add option to input address?
    printf("Enter pharmacy name: ");
    scanf("%s", temp.storeName);

    printf("Enter primary physician's name: ");
    scanf("%s", doctor);
    fprintf(fptr, "Pharmacy: %s \nPrimary Physcian:%s", temp.storeName,doctor);

    fclose(fptr);
}

void samedayReminders(){
    time_t now = time(NULL);
    struct tm *local = localtime(&now);

    stateToday(local->tm_wday);
    printf(", ");
    stateMonth(local->tm_mon);
    printf(" %d", local->tm_mday);
    printf(",%d.", local->tm_year + 1900); //Years since 1900

    //perform check

    printf("\nThere are # medications scheduled for today.\n"); //replace number sign with actual int, create loop below

}




