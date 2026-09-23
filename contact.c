#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    // Sort contacts based on the chosen criteria
    
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    //loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
    // ---------------------- NAME VALIDATION ----------------------
	int attempts = 0;
    char name[50];

    while(attempts < 3)
    {
        printf("Enter the name for the contact: ");
        scanf(" %[^\n]",name);

        // Validation for atleast 3 character.
        int i = 0;
        int char_count = 0;
        while(name[i] != '\0')
        {
            while(name[i] == ' ')
            {
                i++;
            }
            if(name[i] == '\0')
            {
                break;
            }
            if(name[i] != ' ')
            {
                char_count++;
            }
                i++;
        }

        if(char_count < 3)
        {
            printf("Invalid name! Name must have atleast 3 character.\n");
            attempts++;
            continue;
        }

        // Validation to check if all the character are alphabates.
        int isalpha_count = 0;
        for(int i = 0; name[i] != '\0'; i++)
        {
            while(name[i] == ' ')
            {
                i++;
            }
            if(name[i] == '\0')
            {
                break;
            }
            if(isalpha(name[i]))
            {
                isalpha_count++;
            }
        }

        if(isalpha_count != char_count)
        {
            printf("Invalid name! Name should only contain characters.\n");
            attempts++;
            continue;
        }

        // Validation to check if the space between words is valid or not.
       int space_ok = 1;
       int j = 0;
        while(name[j] != '\0')
        {
            if(name[j] != ' ')
            {
                j++;
            }
            else if(name[j] == ' ' && name[j + 1] != ' ')
            {
                j++;
            }
            else
            {
                space_ok = 0;
                break;
            }
        }

        if(space_ok != 1)
        {
            printf("Invalid name! Name must have proper spacing between them.\n");
            attempts++;
            continue;
        }

    
    }

    if(attempts == 3)
    {
        printf("Maximum attempts reached. Program terminated.\n");
        return;
    }
}

void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
   
}
