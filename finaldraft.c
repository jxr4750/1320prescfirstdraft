#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define ver 1.010
// List of functions used
void firstTime(); // Used for the first time setup
void inputData();
void displayPatient();
void displayMeds();
void displayContacts();
void displayPharmacy();
void samedayReminders();
void stateToday(int day);
void stateMonth(int month);
void addMedicine();
void removeMedicine();

typedef struct Address
{
    char streetName[10];
    int streetNumber;
} Address;

typedef struct Medication
{
    char name[10];
    int dosage_amount;
    char dosage_unit[10];
    int schedule[7];
} Medication;

typedef struct Patient
{
    char firstName[10]; // Full Name
    char lastName[10];
    char middleName[10];
    int birthMonth; // DOB
    int birthDay;
    int birthYear;
    Address patientAddress;
} Patient;

typedef struct Emergency
{
    char firstName[10];
    char lastName[10];
    char relation[10];
    int phoneNumber1, phoneNumber2, phoneNumber3;
    Address emergencyAddress;
} Emergency;

typedef struct Pharmacy
{
    char storeName[10];      // Pharmacy Name
    Address pharmacyAddress; // Pharmacy Address
} Pharmacy;

int main()
{
    int decision, mod2;
    char choice, mod;

    time_t now = time(NULL);
    struct tm *local = localtime(&now); // for time functions

    // checking for file, and if it doesnt exist then program will create it and run first time setup
    FILE *fptr;
    fptr = fopen("patientInfo.txt", "r");

    if (fptr == NULL)
    {
        printf("\nWould you like to run the first time setup?(y/n)");
        scanf("%c", &choice);
        if (choice == 'y')
            firstTime();
        else
            exit(0);
    }
    else
        printf("Data Loaded...\n");

    printf("\nTimely Prescription Reminders\n");

    while (decision != 8)
    {
        printf("\nMain Menu:\n\nWhat would you like to do?\n1. Input Data(First time reset)\n2. Display Reminders\n3. Display Pharmacy Info");
        printf("\n4. Display Emergency Contacts\n5. List all Current Medications\n6. Display Patient Profile\n7. Contact us(credits)\n8. Exit\n\n");
        scanf("%d", &decision);

        switch (decision)
        {
        case 1:
            printf("Inputing Data...\n");
            inputData();
            break;
        case 2:
            printf("Displaying Reminders...\n");
            samedayReminders();
            break;
        case 3:
            printf("Displaying Pharmacy info...\n");
            displayPharmacy();
            break;
        case 4:
            printf("Displaying Emergency Contacts...\n");
            displayContacts();
            break;
        case 5:
            printf("Current Medications:\n");
            displayMeds();
            printf("\nWould you like to modify this list?(y/n)\n");
            scanf(" %c", &mod);
            if (mod == 'y')
            {
                printf("would you like to 1. Add a medication 2. Remove a medication 3. Cancel\n");
                scanf(" %d", &mod2);
                switch (mod2)
                {
                case 1:
                    addMedicine();
                    break;
                case 2:
                    removeMedicine();
                    break;
                case 3:
                    printf("\nReturning...");
                    break;
                default:
                    printf("\nUnknown Answer");
                    break;
                }
            }
            break;
        case 6:
            printf("Displaying Current Profile...\n");
            displayPatient();
            break;
        case 7:
            printf("\nVer.%.2f \nTimely Prescription Reminders TM: a time based prescription reminder system.\n\nMade by Joseph Ramsay, Saish Gondkar, Krishna Valkambe, and Soham Panchal\n", ver);
            printf("\nCoded entirely AI free\n");
            break;
        case 8:
            printf("Have a nice day!");
            break;




        default:
            printf("Command not recognized, please select again");
            break;
        } // closes the switch case

    } // closes while loop for main menu
    return 0;
} // closes main

void addMedicine()
{
    FILE *fptr;
    fptr = fopen("medication.txt", "a");
    Medication *mptr, temp;
    mptr = &temp;
    char choice;
    printf("\nAdding a new medication...");
    printf("\nIt is recommended to be filling out the form with your primary emergency contact at your side");
    printf("\nPlease input medication name:");
    scanf("%s", temp.name);
    printf("Please input dosage amount followed by the unit (ex: 10 ml, 1 tablet)");
    scanf("%d %s", &temp.dosage_amount, temp.dosage_unit);
    fprintf(fptr, "\n%s  %d / %s ", temp.name, temp.dosage_amount, temp.dosage_unit);

    for (int i = 0; i < 7; i++)
    {
        mptr->schedule[i] = 1; // make schedule {1,1,1,1,1,1,1}
    }
    printf("\nHow often is this medication prescribed?\n1. Everyday\n2. Every other day\n3. Every 3 days\n4. Weekdays\n5. Weekends\n");
    scanf(" %d", &choice);
    switch (choice)
    {
    case 1:
        printf("\nSchedule for this medication is compiled");
        break;
    case 2:
        for (int i = 1; i < 7; i++)
        {
            if (mptr->schedule[i - 1] == 1)
                mptr->schedule[i] = 0; // make schedule {1,0,1,0,1,0,1}
        }
        break;
    case 3:
        mptr->schedule[1] = 0;
        mptr->schedule[2] = 0;
        mptr->schedule[4] = 0;
        mptr->schedule[5] = 0;
        break;
    case 4:
        mptr->schedule[0] = 0;
        mptr->schedule[6] = 0;
        break;
    case 5:
        for (int i = 1; i < 6; i++)
        {
            mptr->schedule[i] = 0;
        }
        break;
    }

    printf("\nSchedule is: ");
    for (int j = 0; j < 7; j++)
    {
        printf("%d, ", mptr->schedule[j]);
    }
    fclose(fptr);

    fptr = fopen("schedule.txt", "a");
    fprintf(fptr, "\n");
    for (int k = 0; k < 7; k++)
    {
        fprintf(fptr, "%d", mptr->schedule[k]);
    }

    printf("Prescription Added...\n ");
    fclose(fptr);
}

void removeMedicine()
{
    /*
    First open the medication file and copy all of the medications to an array.have the user input a number (n) to
    indicate which medicine to skip in the rewrite (i.e. the medication that is 'removed') and then rewrite all of
    the medications to the same file (minus the skipped one). (dont forget to also modify the schedule text)
    */
    FILE *fptr;
    fptr = fopen("medication.txt", "r");
    Medication *mptr, temp;
    mptr = &temp;
    int i = 0, s = 0;
    char str[100], str2[100];
    char x[100][100];
    char y[100][100];
    int remove;

    printf("\nRemoving a medication...\n");

    if (fptr == NULL)
    {
        printf("\nMedication failed to load line 228");
        exit(1);
    }

    while (fgets(str, 100, fptr) != NULL)
    {
        strcpy(x[i], str);
        if(i == 0)printf("%s", x[i]);
        else printf("%d. %s", i, x[i]);
        i++;
    }

    fclose(fptr); // first file pointer closed

    fptr = fopen("medication.txt", "w");
    if (fptr == NULL)
    {
        printf("\nMedication failed to load line 277");
        exit(1);
    }

    printf("\nWhich medication would you like to remove?(Please select the corresponding number)\n");
    scanf(" %d", &remove);

    for (int j = 0; j < i; j++)
    {
        if (j != remove)
        {
            fprintf(fptr, "%s", x[j]);
        }
    }

    fclose(fptr);

    // read and store the schedule in an array y
    fptr = fopen("schedule.txt", "r");

    if (fptr == NULL)
    {
        printf("\nSchedule failed to load line 277");
        exit(1);
    }

    while (fgets(str2, 100, fptr) != NULL)
    {
        strcpy(y[s], str2);
        s++;
    }
    fclose(fptr);

    // rewrite the schedule
    fptr = fopen("schedule.txt", "w");
    if (fptr == NULL)
    {
        printf("\nSchedule failed to load line 293");
        exit(1);
    }
    for (int k = 0; k < i - 1; k++)
    {
        if (k != remove - 1)
        {
            fprintf(fptr, "%s", y[k]);
        }
    }
    fclose(fptr);
    printf("Prescription removed... \n");
}

void stateToday(int day)
{
    switch (day)
    {
    case 0:
        printf("Sunday");
        break;
    case 1:
        printf("Monday");
        break;
    case 2:
        printf("Tuesday");
        break;
    case 3:
        printf("Wednesday");
        break;
    case 4:
        printf("Thursday");
        break;
    case 5:
        printf("Friday");
        break;
    case 6:
        printf("Saturday");
        break;
    }
}

void stateMonth(int month)
{
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

void inputData()
{
    Patient temp;
    Emergency primary;
    Medication *mptr, first;
    mptr = &first;
    int choice;

    FILE *fptr;

    // Section 1: Establish patient full name
    fptr = fopen("patientInfo.txt", "w");
    printf("Enter first name: ");
    scanf("%s", temp.firstName);
    printf("Enter middle name or initial: ");
    scanf("%s", temp.middleName);
    printf("Enter last name: ");
    scanf("%s", temp.lastName);
    fprintf(fptr, "Patient Name: %s %s %s", temp.firstName, temp.middleName, temp.lastName);

    // Section 2: Establish patient DOB
    printf("Enter Patient DOB (MM DD YYYY): ");
    scanf("%d %d %d", &temp.birthMonth, &temp.birthDay, &temp.birthYear);
    fprintf(fptr, "\nPatient DOB: %d/%d/%d", temp.birthMonth, temp.birthDay, temp.birthYear);
    fclose(fptr);

    // Section 3: Emergency contact (primary)
    fptr = fopen("emergencyContact.txt", "w");
    printf("\nPlease enter your primary emergency contact (You may add more or switch them out at any time, for the first time set up we need at least one.");
    printf("It is recommended to be filling out the first time set up with them at your side)");
    printf("\nInput first name : ");
    scanf("%s", primary.firstName);
    printf("Input last name : ");
    scanf("%s", primary.lastName);
    printf("Input relation : ");
    scanf("%s", primary.relation);
    printf("Input phone number [format: XXX XXX XXXX]: ");
    scanf("%d %d %d", &primary.phoneNumber1, &primary.phoneNumber2, &primary.phoneNumber3);
    fprintf(fptr, "Emergency Contact (primary): %s %s %s +1(%d) %d-%d", primary.firstName, primary.lastName, primary.relation, primary.phoneNumber1, primary.phoneNumber2, primary.phoneNumber3);
    fclose(fptr);

    // section 4: Input first Medication
    fptr = fopen("medication.txt", "w");
    printf("\nPlease enter your first prescription (You may add more or switch them out at any time, for the first time set up we need at least one.");
    printf("It is recommended to be filling out the first time set up with your primary emergency contact at your side)");
    printf("\nPlease input medication name:");
    scanf("%s", first.name);
    printf("Please input dosage amount followed by the unit (ex: 10 ml, 1 tablet)");
    scanf("%d %s", &first.dosage_amount, first.dosage_unit);
    fprintf(fptr, "Medications | Dosage Amount\n%s  %d / %s ", first.name, first.dosage_amount, first.dosage_unit);

    for (int i = 0; i < 7; i++)
    {
        mptr->schedule[i] = 1; // make schedule {1,1,1,1,1,1,1}
    }

    // section 5: make schedule
    printf("\nHow often is this medication prescribed?\n1.Everyday\n2.Every other day\n3.Every 3 days\n4.Weekdays\n5.Weekends\n");
    scanf(" %d", &choice);
    switch (choice)
    {
    case 1:
        printf("\nSchedule for this medication is compiled");
        break;
    case 2:
        for (int i = 1; i < 7; i++)
        {
            if (mptr->schedule[i - 1] == 1)
                mptr->schedule[i] = 0; // make schedule {1,0,1,0,1,0,1}
        }
        break;
    case 3:
        mptr->schedule[1] = 0;
        mptr->schedule[2] = 0;
        mptr->schedule[4] = 0;
        mptr->schedule[5] = 0;
        break;
    case 4:
        mptr->schedule[0] = 1;
        mptr->schedule[6] = 1;
        break;
    case 5:
        for (int i = 1; i < 6; i++)
        {
            mptr->schedule[i] = 0;
        }
        break;
    }

    // section 5.5: document schedule
    printf("\nSchedule is: ");
    for (int j = 0; j < 7; j++)
    {
        printf("%d, ", mptr->schedule[j]);
    }
    fclose(fptr);
    // create new schedule.txt, and assign a schedule to a medicine based on order of medications
    fptr = fopen("schedule.txt", "w");
    for (int k = 0; k < 7; k++) // Indented the first bracket
    {
        fprintf(fptr, "%d", mptr->schedule[k]);
    }
    fclose(fptr);
    printf(" Schedule created Successfully!");
}

void displayPatient()
{
    FILE *fptr;
    char str[100];
    fptr = fopen("patientInfo.txt", "r");
    while (fgets(str, 100, fptr) != NULL)
    {
        printf("%s", str);
    }
    fclose(fptr);
}

void displayMeds()
{
    FILE *fptr;
    char str[100];
    fptr = fopen("medication.txt", "r");
    while (fgets(str, 100, fptr) != NULL)
    {
        printf("%s", str);
    }
    fclose(fptr);
}

void displayContacts()
{
    FILE *fptr;
    char str[100];
    fptr = fopen("emergencyContact.txt", "r");
    while (fgets(str, 100, fptr) != NULL)
    {
        printf("%s", str);
    }
    fclose(fptr);
}

void inputPharmacy()
{
    FILE *fptr;
    char doctor[20];
    char hospital[100];
    char physician[100];
    getchar();

    fptr = fopen("pharmacyInfo.txt", "w");

    printf("Enter pharmacy name: ");
    fgets(hospital, sizeof(hospital), stdin);
    fprintf(fptr, "Pharmacy: ");
    fputs(hospital, fptr);

    printf("Enter primary physician's name: ");
    fgets(physician, sizeof(physician), stdin);
    fprintf(fptr, "Primary Physician: ");
    fputs(physician, fptr);

    fclose(fptr);
}

void displayPharmacy()
{
    char choice;
    FILE *fptr;
    char str[100];
    fptr = fopen("pharmacyInfo.txt", "r");

    if (fptr == NULL)
    {
        printf("\nWould you like to setup your local physician and pharmacy information?(y/n)\n");
        scanf(" %c", &choice);
        if (choice == 'y')
            inputPharmacy();
        else
            return;
    }
    else
    {
        while (fgets(str, 100, fptr) != NULL)
        {
            printf("%s", str);
        }
        fclose(fptr);
    }
}

void samedayReminders()
{
    int counter = 0, check = 0; // count how many medications to take today.
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    FILE *fptr;
    char str[100];
    int med[10];

    printf("Today is ");
    stateToday(local->tm_wday);
    printf(", ");
    stateMonth(local->tm_mon);
    printf(" %d", local->tm_mday);
    printf(",%d.", local->tm_year + 1900);

    fptr = fopen("schedule.txt", "r");
    if (fptr == NULL)
    {
        printf("\nSchedule failed to load line 606");
        exit(0);
    }
    else
        printf("\nSchedule Loaded...\n");
    printf("\nThe medications to take are:");

    while (fgets(str, 10, fptr) != NULL)
    {
        counter++;
        if (str[local->tm_wday] == '1')
        {
            med[counter] = 1;
            printf("\nMed#%d", counter);
            check++;
        }
        else
            med[counter] = 0;
    }
    fclose(fptr); // closes the schedule, since binary operation is complete
    fptr = fopen("medication.txt", "r"); // opens the medications document, to log what is needed to be taken
    if (fptr == NULL)
    {
        printf("\nPrescription list failed to load line 554");
        exit(0);
    }
    else
        printf("\n\n");
    int j = 0;
    while (fgets(str, 100, fptr)) // checks value of medicine array, and if its 1/true value, prints the line from the document.
    {
        if (med[j] == 1)
        {
            printf("%s", str);
        }
        j++;
    }
    fclose(fptr);
    printf("\nThere are %d medications scheduled for today.\n", check);
}

void firstTime()
{
    printf("\nThank you for choosing Timely Prescription reminders, we are pleased to have your company.");
    FILE *fptr;
    fptr = fopen("patientInfo.txt", "w");
    if (fptr == NULL)
    {
        printf("\n\nThe file is not opened. The program will exit now");
        exit(0);
    }
    else
    {
        printf("\n\nThe file is created Successfully.\n");
        inputData();
    }
    printf("\nYou are now ready to use the app, your profile has been set up.\nTo access more features, add more medicine, or contact us, please use the main menu.");
    fclose(fptr);
    return;
}
