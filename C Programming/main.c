#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

static const char FILEPATH[] = "C:\\Users\\lfesc\\Documents\\GitHub\\Contact-book\\C Programming\\contacts.dat";

int count = 0;

typedef struct {
    unsigned int ddd;
    unsigned int number;
} Telephone;

typedef struct {
 unsigned short day;
 unsigned short month;
 unsigned short year;
} Date;

typedef struct {
    unsigned short id;
    unsigned char name[128];
    Telephone tNumber;
    Date birthday;
    int save;
} Contact;


Contact* AddContact(Contact contact, Contact* contacts)
{
    if (count == 0) {
        contacts = (Contact*)malloc(1 * sizeof(Contact));
        contacts[0] = contact;
    }
    else
    {
        contacts = (Contact*)realloc(contacts, (count + 1) * sizeof(Contact));
        contacts[count] = contact;
    }

    count++;

    system("CLS");

    return contacts;
}

void PrintContact(Contact contact)
{
    printf("Name: %s \n", contact.name);
    printf("Date of birth: %d/%d/%d \n", contact.birthday.day, contact.birthday.month, contact.birthday.year);
    printf("Telephone: (%d) %d \n", contact.tNumber.ddd, contact.tNumber.number);
    printf("\r\n \r\n");
}

Contact* InitializeContants(Contact* contacts)
{
    int num;
    FILE* f;

    Contact contact;

    f = fopen(FILEPATH, "rb");

    if (f == NULL)
    {
        printf("Error! opening file");
        exit(0);
    }


    while (fread(&contact, sizeof(Contact), 1, f))
    {
        contacts = AddContact(contact, contacts);
    }

    fclose(f);

    return contacts;
}

Contact* CreateNewContact(Contact* oldContacts)
{
    Contact contact;
    int size;

    contact.id = count;

    printf("Insert the name of the new contact: ");
    scanf("%s", &contact.name);
    fflush(stdin);

    printf("Insert the day of birth: ");
    fflush(stdin);
    scanf("%i", &contact.birthday.day);

    printf("Insert the month of birth: ");
    fflush(stdin);
    scanf("%i", &contact.birthday.month);

    printf("Insert the year of birth: ");
    fflush(stdin);
    scanf("%i", &contact.birthday.year);

    printf("Insert the telephone DDD: ");
    fflush(stdin);
    scanf("%i", &contact.tNumber.ddd);

    printf("Insert the telephone number: ");
    fflush(stdin);
    scanf("%i", &contact.tNumber.number);

    contact.save = 1;

    printf("\r\n");

    return AddContact(contact, oldContacts);
}

void PrintAllContacts(Contact* contacts)
{
    system("CLS");
    printf("------------------- CONTACTS -------------------");
    printf("\r\n \r\n");
    for (int i = 0; i < count; i++)
    {
        PrintContact(contacts[i]);
    }
    printf("------------------------------------------------");
}

void PrintContactsByBirth(Contact* contacts)
{
    int month;

    system("CLS");
    printf("Insert the month to search: \r\n");
    scanf("%d", &month);

    printf("\r\n \r\n");
    for (int i = 0; i < count; i++)
    {
        if (contacts[i].birthday.month == month) {
            PrintContact(contacts[i]);
        }
    }
    printf("------------------------------------------------");
}

void PrintContactsByName(Contact* contacts)
{
    char name[380];

    system("CLS");
    printf("Insert the name to search: \r\n");
    scanf("%s", &name);

    printf("\r\n \r\n");
    for (int i = 0; i < count; i++)
    {
        if (strcmp(contacts[i].name, name) == 0) {
            PrintContact(contacts[i]);
        }
    }
    printf("------------------------------------------------");
}

void PrintContactsByLetter(Contact* contacts)
{
    char letter[10];
    system("CLS");
    printf("Insert the letter to search: \r\n");
    scanf("%s", &letter);

    printf("\r\n \r\n");
    for (int i = 0; i < count; i++)
    {
        if (contacts[i].name[0] == letter[0]) {
            PrintContact(contacts[i]);
        }
    }
    printf("------------------------------------------------");
}

Contact* DeleteContact(Contact* contacts)
{
    char name[380];

    system("CLS");
    printf("Insert the name to delete: \r\n");
    scanf("%s", &name);


    for (int i = 0; i < count; i++)
    {
        if (strcmp(contacts[i].name, name) == 0) {

            contacts[i].save = 0;

            printf("Contact will be deleted in the next save...");
          
            break;
        }
    }

    return contacts;
}

void SaveContacts(Contact* contacts)
{
    FILE* fptr;

    if ((fptr = fopen(FILEPATH, "wb")) == NULL)
    {
        printf("Error! opening file");

        exit(0);
    }

    for (int n = 0; n < count; ++n)
    {
        if(contacts[n].save)
            fwrite(&contacts[n], sizeof(Contact), 1, fptr);
    }

    fclose(fptr);

}

Contact* UpdateContact(Contact* contacts)
{
    char name[128];
    char option[10];

    system("CLS");
    printf("Insert the name of the contact to update: \r\n");
    scanf("%s", &name);

    for (int i = 0; i < count; i++)
    {
        if (strcmp(contacts[i].name, name) == 0) {

            printf("Do you want to update the contact name? y/n: \r\n");
            fflush(stdin);
            scanf("%s", &option);

            if (option[0] == 'y')
            {
                printf("Insert the contact name: ");
                fflush(stdin);
                scanf("%s", &contacts[i].name);
            }

            printf("Do you want to update the contact birthday? y/n: \r\n");
            scanf("%s", &option);

            if (option[0] == 'y')
            {
                printf("Insert the day of birth: ");
                fflush(stdin);
                scanf("%i", &contacts[i].birthday.day);

                printf("Insert the month of birth: ");
                fflush(stdin);
                scanf("%i", &contacts[i].birthday.month);

                printf("Insert the year of birth: ");
                fflush(stdin);
                scanf("%i", &contacts[i].birthday.year);
            }


            printf("Do you want to update the contact telephone? y/n: \r\n");
            fflush(stdin);
            scanf("%s", &option);

            if (option[0] == 'y')
            {
                printf("Insert the telephone DDD: ");
                fflush(stdin);
                scanf("%i", &contacts[i].tNumber.ddd);

                printf("Insert the telephone number: ");
                fflush(stdin);
                scanf("%i", &contacts[i].tNumber.number);
            }

            break;
        }
    }

    return contacts;
}



int main()
{
    int option = 0;

    Contact* contacts = NULL;
    contacts = InitializeContants(contacts);

    while (option != 8) {
        printf("\n------------------- SCHEDULE -------------------\n");
        printf("Choose an action: \n1- Update contact.\n2- Create new contact.\n3- Remove contact\n4- Search contact by name\n5- List all contacts.\n6- List all contacts that starts with a specific letter.\n7- List the contacts who are birthdays of the month.\n8- Exit.\n");
        scanf("%d", &option);
        fflush(stdin);
        switch (option)
        {
        case 1:
            UpdateContact(contacts);
            break;
        case 2:
            contacts = CreateNewContact(contacts);
            break;
        case 3:
            DeleteContact(contacts);
            break;
        case 4:
            PrintContactsByName(contacts);
            break;
        case 5:
            PrintAllContacts(contacts);
            break;
        case 6:
            PrintContactsByLetter(contacts);
            break;
        case 7:
            PrintContactsByBirth(contacts);
            break;
        case 8:
            SaveContacts(contacts);
            exit(0);
            break;
        }

    }

    return 0;
}