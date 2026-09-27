#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"

void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    // Sort contacts based on the chosen criteria
    
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    loadContactsFromFile(addressBook); // Load contacts from file
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

        break;
    }

    if(attempts == 3)
    {
        printf("Maximum attempts reached. Program terminated.\n");
        return;
    }
    
    // After validation copy the name into the structure.
    strcpy(addressBook->contacts[addressBook->contactCount].name, name);



    // ---------------------- PHONE NUMBER VALIDATION ----------------------

    char phone[20];
    int phone_attempts = 0;

    while (phone_attempts < 3)
    {
        printf("Enter the phone number: ");
        scanf("%s", phone);

        // Check phone number length
        int len = strlen(phone);

        if (len != 10)
        {
            printf("Invalid Phone number! Enter exactly 10 digits.\n");
            phone_attempts++;
            continue;
        }

        // Check first digit
        if (phone[0] != '6' && phone[0] != '9')
        {
            printf("Invalid Phone number! Phone number must start from 6 or 9.\n");
            phone_attempts++;
            continue;
        }

        // Check whether all characters are digits
        int valid = 1;

        for (int i = 0; phone[i] != '\0'; i++)
        {
            if (!isdigit(phone[i]))
            {
                valid = 0;
                break;
            }
        }

        if (!valid)
        {
            printf("Invalid Phone number! Number must contain only digits.\n");
            phone_attempts++;
            continue;
        }

        // Find the duplicate number exists or not
        int isduplicate = 0;
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(phone, addressBook->contacts[i].phone) == 0)
            {
                isduplicate = 1;  
                break; 
            }
        }

        if(isduplicate)
        {
            printf("Invalid Phone number! There is a duplicate.\n");
            phone_attempts++;
            continue;
        }

        break;
    }

    if (phone_attempts == 3)
    {
        printf("Maximum attempts reached. Program terminated.\n");
        return;
    }

    // After validation copy the name into the structure.
    strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);


    // ---------------------- EMAIL ID VALIDATION ----------------------
    char email[20];
    int email_attempts = 0;

    while(email_attempts < 3)
    {

        printf("Enter the email: ");
        scanf(" %s", email);

        // Only one @ and . validation.
        int symbol_count = 0;
        int dot_count = 0;

        for(int i = 0; email[i] != '\0'; i++)
        {
            if(email[i] == '@')
            {
                symbol_count++;
            }

            if(email[i] == '.')
            {
                dot_count++;
            }
        }

        if(symbol_count != 1 || dot_count != 1)
        {
            printf("Invalid email! Check the symbols.\n");
            email_attempts++;
            continue;
        }

        // Only lowercase and digits.
        int invalid_char = 0;

        for(int i = 0; email[i] != '\0'; i++)
        {
            if((islower(email[i]) == 0) &&
               (isdigit(email[i]) == 0) &&
               email[i] != '@' &&
               email[i] != '.')
            {
                invalid_char = 1;
                break;
            }
        }

        if(invalid_char)
        {
            printf("Invalid email! Check if you have entered invalid character.\n");
            email_attempts++;
            continue;
        }

        // Find @ and . positions.
        int symbol_index = 0;
        int dot_index = 0;

        for(int i = 0; email[i] != '\0'; i++)
        {
            if(email[i] == '@')
            {
                symbol_index = i;
            }

            if(email[i] == '.')
            {
                dot_index = i;
            }
        }

        // @ must come before .
        if(dot_index < symbol_index)
        {
            printf("Invalid email! Check the placement of @ and . and re-enter.\n");
            email_attempts++;
            continue;
        }

        // At least one character between @ and .
        int no_char = 0;

        if(dot_index - symbol_index <= 1)
        {
            no_char = 1;
        }
        else
        {
            for(int i = symbol_index + 1; i < dot_index; i++)
            {
                if(islower(email[i]) == 0)
                {
                    no_char = 1;
                    break;
                }
            }
        }

        if(no_char)
        {
            printf("Invalid email! Check if you have entered character between symbols.\n");
            email_attempts++;
            continue;
        }

        // After .com no character should be entered.
        char temp_str[] = "moc.";

        int len = strlen(email);
        int j = len - 1;
        int i = 0;
        int invalid = 0;

        while(temp_str[i] != '\0')
        {
            if(j < 0 || temp_str[i] != email[j])
            {
                invalid = 1;
                break;
            }

            j--;
            i++;
        }

        if(invalid)
        {
            printf("Invalid email! After .com no character should be present.\n");
            email_attempts++;
            continue;
        }

        // Find the duplicate email exists or not
        int isduplicate_email = 0;
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(email, addressBook->contacts[i].email) == 0)
            {
                isduplicate_email = 1;  
                break; 
            }
        }

        if(isduplicate_email)
        {
            printf("Invalid Phone number! There is a duplicate.\n");
            phone_attempts++;
            continue;
        }

        break;
    }

    if(email_attempts == 3)
    {
        printf("Maximum attempts. Program terminated.\n");
        return;
    }

    strcpy(addressBook -> contacts[addressBook -> contactCount].email, email);
    addressBook -> contactCount++;
}

void searchContact(AddressBook *addressBook) 
{
    //-------------------SEARCH BY NAME--------------------
    int choice;

    printf("\n");
    printf("========================================\n");
    printf("             SEARCH CONTACT             \n");
    printf("========================================\n");
    printf("1. Search by Name\n");
    printf("2. Search by Phone Number\n");
    printf("3. Search by Email\n");
    printf("4. Exit\n");
    printf("========================================\n");

    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 4)
    {
        return;
    }

    if (choice == 1)
    {
        char search_name[50];
        int matching_indices[100];
        int match_count = 0;

        printf("\nEnter the name to search: ");
        scanf(" %[^\n]", search_name);

        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(search_name, addressBook->contacts[i].name) == 0)
            {
                matching_indices[match_count] = i;
                match_count++;
            }
        }

        if (match_count == 0)
        {
            printf("\n----------------------------------------\n");
            printf("       No matching contact found.\n");
            printf("----------------------------------------\n");
        }
        else if (match_count == 1)
        {
            int index = matching_indices[0];

            printf("\n========================================\n");
            printf("           CONTACT FOUND                \n");
            printf("========================================\n");
            printf("Name  : %s\n", addressBook->contacts[index].name);
            printf("Phone : %s\n", addressBook->contacts[index].phone);
            printf("Email : %s\n", addressBook->contacts[index].email);
            printf("========================================\n");
        }
        else
        {
            char phone[20];
            int found = 0;

            printf("\nMultiple contacts found with the name \"%s\".\n", search_name);
            printf("Enter the phone number to identify the contact: ");
            scanf("%s", phone);

            for (int i = 0; i < match_count; i++)
            {
                int index = matching_indices[i];

                if (strcmp(phone, addressBook->contacts[index].phone) == 0)
                {
                    printf("\n========================================\n");
                    printf("           CONTACT FOUND                \n");
                    printf("========================================\n");
                    printf("Name  : %s\n", addressBook->contacts[index].name);
                    printf("Phone : %s\n", addressBook->contacts[index].phone);
                    printf("Email : %s\n", addressBook->contacts[index].email);
                    printf("========================================\n");

                    found = 1;
                    break;
                }
            }

            if (!found)
            {
                printf("\n----------------------------------------\n");
                printf("        Invalid phone number.\n");
                printf("----------------------------------------\n");
            }
        }
    }
    //--------------------------SEARCH BY NAME------------------------
    else if (choice == 2)
    {
        char phone[20];
        int found = 0;

        printf("\nEnter the phone number to search: ");
        scanf("%s", phone);

        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(phone, addressBook->contacts[i].phone) == 0)
            {
                printf("\n========================================\n");
                printf("           CONTACT FOUND                \n");
                printf("========================================\n");
                printf("Name  : %s\n", addressBook->contacts[i].name);
                printf("Phone : %s\n", addressBook->contacts[i].phone);
                printf("Email : %s\n", addressBook->contacts[i].email);
                printf("========================================\n");

                found = 1;
                break;
            }
        }

        if (!found)
        {
            printf("\n----------------------------------------\n");
            printf("       No matching contact found.\n");
            printf("----------------------------------------\n");
        }
    }
    //---------------------------SERACH BY EMAIL---------------------
    else if (choice == 3)
    {
        char email[50];
        int found = 0;

        printf("\nEnter the email to search: ");
        scanf("%s", email);

        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(email, addressBook->contacts[i].email) == 0)
            {
                printf("\n========================================\n");
                printf("           CONTACT FOUND                \n");
                printf("========================================\n");
                printf("Name  : %s\n", addressBook->contacts[i].name);
                printf("Phone : %s\n", addressBook->contacts[i].phone);
                printf("Email : %s\n", addressBook->contacts[i].email);
                printf("========================================\n");

                found = 1;
                break;
            }
        }

        if (!found)
        {
            printf("\n----------------------------------------\n");
            printf("       No matching contact found.\n");
            printf("----------------------------------------\n");
        }
    }
    else
    {
        printf("\nInvalid choice!\n");
    }
}

void editContact(AddressBook *addressBook)
{
    char search_name[50];
    char phone[20];
    int matching_indices[100];
    int match_count = 0;
    int index = -1;

    printf("\n========================================\n");
    printf("             EDIT CONTACT\n");
    printf("========================================\n");

    printf("Enter the name of the contact: ");
    scanf(" %[^\n]", search_name);

    // Find all contacts with matching name
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(search_name, addressBook->contacts[i].name) == 0)
        {
            matching_indices[match_count] = i;
            match_count++;
        }
    }

    // No contact found
    if (match_count == 0)
    {
        printf("\nContact not found.\n");
        return;
    }

    // Only one contact found
    if (match_count == 1)
    {
        index = matching_indices[0];
    }

    // Multiple contacts found
    else
    {
        printf("\nMultiple contacts found with this name.\n");

        printf("Enter the phone number to identify the contact: ");
        scanf("%s", phone);

        for (int i = 0; i < match_count; i++)
        {
            int current_index = matching_indices[i];

            if (strcmp(phone, addressBook->contacts[current_index].phone) == 0)
            {
                index = current_index;
                break;
            }
        }

        if (index == -1)
        {
            printf("\nInvalid phone number.\n");
            return;
        }
    }

    // Display selected contact
    printf("\n========================================\n");
    printf("           CONTACT SELECTED\n");
    printf("========================================\n");
    printf("Name  : %s\n", addressBook->contacts[index].name);
    printf("Phone : %s\n", addressBook->contacts[index].phone);
    printf("Email : %s\n", addressBook->contacts[index].email);
    printf("========================================\n");

    int choice;

    printf("\n1. Edit Name\n");
    printf("2. Edit Phone\n");
    printf("3. Edit Email\n");
    printf("4. Cancel\n");

    printf("Enter your choice: ");
    scanf("%d", &choice);


    // -------------------- EDIT NAME --------------------

    if (choice == 1)
    {
        char name[50];
        int valid = 0;

        while (!valid)
        {
            printf("Enter the new name: ");
            scanf(" %[^\n]", name);

            int char_count = 0;

            for (int i = 0; name[i] != '\0'; i++)
            {
                if (name[i] != ' ')
                {
                    char_count++;
                }
            }

            if (char_count < 3)
            {
                printf("Invalid name! Name must have atleast 3 characters.\n");
                continue;
            }

            if (name[0] == ' ' || name[strlen(name) - 1] == ' ')
            {
                printf("Invalid name! Name must have proper spacing between them.\n");
                continue;
            }

            valid = 1;

            for (int i = 0; name[i] != '\0'; i++)
            {
                if (name[i] != ' ' && !isalpha(name[i]))
                {
                    printf("Invalid name! Name should only contain characters.\n");
                    valid = 0;
                    break;
                }

                if (name[i] == ' ' && name[i + 1] == ' ')
                {
                    printf("Invalid name! Name must have proper spacing between them.\n");
                    valid = 0;
                    break;
                }
            }
        }

        strcpy(addressBook->contacts[index].name, name);
    }


    // -------------------- EDIT PHONE --------------------

    else if (choice == 2)
    {
        char new_phone[20];
        int valid = 0;

        while (!valid)
        {
            printf("Enter the new phone number: ");
            scanf("%s", new_phone);

            if (strlen(new_phone) != 10)
            {
                printf("Invalid Phone number! Enter exactly 10 digits.\n");
                continue;
            }

            if (new_phone[0] != '6' && new_phone[0] != '9')
            {
                printf("Invalid Phone number! Phone number must start from 6 or 9.\n");
                continue;
            }

            valid = 1;

            for (int i = 0; new_phone[i] != '\0'; i++)
            {
                if (!isdigit(new_phone[i]))
                {
                    printf("Invalid Phone number! Number must contain only digits.\n");
                    valid = 0;
                    break;
                }
            }

            if (!valid)
            {
                continue;
            }

            // Check duplicate phone number
            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (i == index)
                {
                    continue;
                }

                if (strcmp(new_phone, addressBook->contacts[i].phone) == 0)
                {
                    printf("Invalid Phone number! There is a duplicate.\n");
                    valid = 0;
                    break;
                }
            }
        }

        strcpy(addressBook->contacts[index].phone, new_phone);
    }


    // -------------------- EDIT EMAIL --------------------

    else if (choice == 3)
    {
        char email[50];
        int valid = 0;

        while (!valid)
        {
            printf("Enter the new email: ");
            scanf("%s", email);

            int at_count = 0;
            int dot_count = 0;
            int at_position = -1;
            int dot_position = -1;

            for (int i = 0; email[i] != '\0'; i++)
            {
                if (email[i] == '@')
                {
                    at_count++;
                    at_position = i;
                }

                if (email[i] == '.')
                {
                    dot_count++;
                    dot_position = i;
                }
            }

            if (at_count != 1)
            {
                printf("Invalid email! Email must contain exactly one @.\n");
                continue;
            }

            if (dot_count < 1)
            {
                printf("Invalid email! Email must contain a dot.\n");
                continue;
            }

            if (at_position == 0 || dot_position <= at_position + 1)
            {
                printf("Invalid email format.\n");
                continue;
            }

            valid = 1;
        }

        strcpy(addressBook->contacts[index].email, email);
    }


    // -------------------- CANCEL --------------------

    else if (choice == 4)
    {
        return;
    }

    else
    {
        printf("\nInvalid choice.\n");
        return;
    }

    // Save changes to file
    saveContactsToFile(addressBook);

    printf("\n========================================\n");
    printf("       Contact updated successfully!\n");
    printf("========================================\n");
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
   
}
