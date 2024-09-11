#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <Windows.h>
using namespace std;

class Validations // class for input validations
{
public:
    bool idValidation(const string &idString)
    {
        if (idString.empty() || idString.find(' ') != string::npos)
        {
            return false;
        }

        for (char ch : idString)
        {
            if (!isdigit(ch))
            {
                return false;
            }
        }
        return true;
    }

    bool stringValidation(const string &str)
    {
        if (str.empty())
        {
            return false;
        }

        for (char ch : str)
        {
            if (!isspace(ch))
            {
                return true;
            }
        }
        return false;
    }

    bool phoneNumberValidation(const string &number)
    {
        if (number.size() !=8)
        {
            return false;
        }

        for (char ch : number)
        {
            if (!isdigit(ch))
            {
                return false;
            }
        }
        return true;
    }

    bool emailValidation(const string &email)
    {
        const string gmailSuffix = "@gmail.com";
        if (email.empty())
        {
            return false;
        }

        for (char ch : email)
        {
            if (isspace(ch))
            {
                return false;
            }
        }
        if (email.size() < gmailSuffix.size() + 5)
        {
            return false;
        }

        string prefix = email.substr(0, email.size() - gmailSuffix.size());
        for (char ch : prefix)
        {
            if (!islower(ch) && !isdigit(ch) && ch != '.' && ch != '_' && ch != '-')
            {
                return false;
            }
        }

        string suffix = email.substr(email.size() - gmailSuffix.size());
        return suffix == gmailSuffix;
    }
};

class Contact
{
protected:
    string name;
    string number;
    string email;
    string type;

public:
    Contact() {}

    Contact(const string &name, const string &number, const string &email, const string &type)
        : name(name), number(number), email(email), type(type) {}

    // Getters
    string getName() const { return name; }
    string getNumber() const { return number; }
    string getEmail() const { return email; }
    string getType() const { return type; }

    // Setters
    void setName(const string &name) { this->name = name; }
    void setNumber(const string &number) { this->number = number; }
    void setEmail(const string &email) { this->email = email; }
    void setType(const string &type) { this->type = type; }
};
class AddContact : public Validations
{
public:
    void addContact(Contact ptclContacts[], int &ptclCount, Contact localContacts[], int &localCount, Contact emergencyContacts[], int &emergencyCount)
    {
        system("cls");
        bool main_page = false;
        while (!main_page)
        {
            cout << "\n\n\t ____________________________________________\n";
            cout << "\t|\t   Choose Contact Type\t\t     |\n";
            cout << "\t|____________________________________________|\n";
            cout << "\t|   |" << setw(42) << "|\n";
            cout << "\t| 1 |  PTCL Number" << setw(29) << "|\n";
            cout << "\t| 2 |  Emergency Number" << setw(24) << "|\n";
            cout << "\t| 3 |  Local Number" << setw(28) << "|\n";
            cout << "\t| 0 |  Back to Main Menu" << setw(23) << "|\n";
            cout << "\t|___|________________________________________|\n\n";
            string choice;
            while (true)
            {
                cout << "\tEnter your choice: ";
                getline(cin, choice);
                if (stringValidation(choice) && (choice == "1" || choice == "2" || choice == "3" || choice == "0"))
                {
                    break;
                }
                cout << "\n\tInvalid input. Please enter a valid choice (0, 1, 2, or 3).\n";
            }

            if (choice == "0")
            {
                main_page = true;
                continue;
            }
            else if (choice == "1" && ptclCount < 100)
            {
                addSpecificContact(ptclContacts, ptclCount, "PTCL", ptclContacts, ptclCount, localContacts, localCount, emergencyContacts, emergencyCount);
            }
            else if (choice == "2" && emergencyCount < 100)
            {
                addSpecificContact(emergencyContacts, emergencyCount, "Emergency", ptclContacts, ptclCount, localContacts, localCount, emergencyContacts, emergencyCount);
            }
            else if (choice == "3" && localCount < 100)
            {
                addSpecificContact(localContacts, localCount, "Local", ptclContacts, ptclCount, localContacts, localCount, emergencyContacts, emergencyCount);
            }
            else
            {
                cout << "\n\tInvalid choice or maximum contacts reached for this type.\n";
            }
            string addMore;
            while (true)
            {
                cout << "\n\n\tDo you want to add another contact? (y/n): ";
                getline(cin, addMore);
                if (stringValidation(addMore) && (addMore == "y" || addMore == "Y" || addMore == "n" || addMore == "N"))
                {
                    if (addMore == "n" || addMore == "N")
                    {
                        main_page = true;
                    }
                    break;
                }
                cout << "\n\tInvalid input. Please enter 'y' or 'n'.\n";
            }
        }
    }

// protected:
    void addSpecificContact(Contact contacts[], int &count, const string &type, Contact ptclContacts[], int ptclCount, Contact localContacts[], int localCount, Contact emergencyContacts[], int emergencyCount)
    {
        system("cls");
        while (true)
        {
            string name, number, email;
            cout << "\n\n\tEnter details for the new " << type << " contact:\n";

            // Get name
            while (true)
            {
                cout << "\tName : \t\t";
                getline(cin, name);
                if (stringValidation(name))
                {
                    break;
                }
                cout << "\n\tInvalid input. Please enter a valid name.\n";
            }

            // Get number
            while (true)
            {
                cout << "\tNumber :\t";
                getline(cin, number);

                if (type == "Emergency" && idValidation(number))
                {
                    if (isUniqueNumber(number, ptclContacts, ptclCount, localContacts, localCount, emergencyContacts, emergencyCount))
                    {
                        break;
                    }
                    else
                    {
                        cout << "\n\tThis number is already registered. Please enter a different number.\n";
                    }
                }
                else if ((type == "Local" && localPhoneNumberValidation(number)) ||
                         (type != "Local" && type != "Emergency" && phoneNumberValidation(number)))
                {
                    if (isUniqueNumber(number, ptclContacts, ptclCount, localContacts, localCount, emergencyContacts, emergencyCount))
                    {
                        break;
                    }
                    else
                    {
                        cout << "\n\tThis number is already registered. Please enter a different number.\n";
                    }
                }
                else
                {
                    cout << "\n\tInvalid input. Please enter a valid phone number.\n";
                }
            }

            // Get email if not emergency
            if (type != "Emergency")
            {
                while (true)
                {
                    cout << "\tEmail : \t";
                    getline(cin, email);
                    if (emailValidation(email))
                    {
                        if (isUniqueEmail(email, ptclContacts, ptclCount, localContacts, localCount))
                        {
                            break;
                        }
                        else
                        {
                            cout << "\n\tThis email is already registered. Please enter a different email.\n";
                        }
                    }
                    else
                    {
                        cout << "\n\tInvalid input. Please enter a valid email ending with @gmail.com.\n";
                    }
                }
            }

            // Add contact
            contacts[count++] = Contact(name, number, email, type);
            cout << "\n\n\tContact added successfully!\n";
            break;
        }
    }

    bool localPhoneNumberValidation(const string &number)
    {
        if (((number.substr(0, 4) == "+923") && (number.size() == 13)) || ((number.substr(0, 2) == "03") && (number.size() == 11)))
        {
            for (int i = 1; i< number.size();i++ )
            {
                if (!isdigit(number[i]))
                {
                    return false;
                }
            }
            return true;
        }
        return false;
    }

    bool isUniqueNumber(const string &number, Contact ptclContacts[], int ptclCount, Contact localContacts[], int localCount, Contact emergencyContacts[], int emergencyCount)
    {
        for (int i = 0; i < ptclCount; ++i)
        {
            if (ptclContacts[i].getNumber() == number)
            {
                return false;
            }
        }
        for (int i = 0; i < localCount; ++i)
        {
            if (localContacts[i].getNumber() == number)
            {
                return false;
            }
        }
        for (int i = 0; i < emergencyCount; ++i)
        {
            if (emergencyContacts[i].getNumber() == number)
            {
                return false;
            }
        }
        return true;
    }

    bool isUniqueEmail(const string &email, Contact ptclContacts[], int ptclCount, Contact localContacts[], int localCount)
    {
        for (int i = 0; i < ptclCount; ++i)
        {
            if (ptclContacts[i].getEmail() == email)
            {
                return false;
            }
        }
        for (int i = 0; i < localCount; ++i)
        {
            if (localContacts[i].getEmail() == email)
            {
                return false;
            }
        }
        return true;
    }
};

class SearchContact : public Validations
{
public:
    void searchContacts(Contact ptclContacts[], int ptclCount, Contact localContacts[], int localCount, Contact emergencyContacts[], int emergencyCount)
    {
        string keyword;
        while (true)
        {
            cout << "\n\tEnter search keyword (name, number, or email): \t";
            getline(cin, keyword);
            if (stringValidation(keyword))
            {
                break;
            }
            cout << "\n\tInvalid input. Please enter a valid keyword.";
        }

        system("cls");
        bool found = false;
        cout << "\n\n\tSearch Results:\n";

        // Convert keyword to lowercase for case-insensitive name search
        string keywordLower = toLower(keyword);

        // Search in PTCL contacts
        for (int i = 0; i < ptclCount; i++)
        {
            if (toLower(ptclContacts[i].getName()).find(keywordLower) != string::npos ||
                ptclContacts[i].getNumber().find(keyword) != string::npos ||
                ptclContacts[i].getEmail().find(keyword) != string::npos)
            {
                displayContact(ptclContacts[i]);
                found = true;
            }
        }

        // Search in Local contacts
        for (int i = 0; i < localCount; i++)
        {
            if (toLower(localContacts[i].getName()).find(keywordLower) != string::npos ||
                localContacts[i].getNumber().find(keyword) != string::npos ||
                localContacts[i].getEmail().find(keyword) != string::npos)
            {
                displayContact(localContacts[i]);
                found = true;
            }
        }

        // Search in Emergency contacts
        for (int i = 0; i < emergencyCount; i++)
        {
            if (toLower(emergencyContacts[i].getName()).find(keywordLower) != string::npos ||
                emergencyContacts[i].getNumber().find(keyword) != string::npos)
            {
                displayContact(emergencyContacts[i]);
                found = true;
            }
        }

        if (!found)
        {
            cout << "\n\n\tNo contact found matching the keyword!\n";
        }
    }
private:
    void displayContact(const Contact &contact)
    {
        cout << "\n\tName : \t\t" << contact.getName();
        cout << "\n\tNumber :\t" << contact.getNumber();
        if (contact.getType() != "Emergency")
        {
            cout << "\n\tEmail : \t" << contact.getEmail();
        }
        cout << "\n\tType : \t\t" << contact.getType();
        cout << "\n";
    }

    string toLower(const string &str)
    {
        string lowerStr = str;
        transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
        return lowerStr;
    }
};
class EditContact : public Validations
{
public:
    void editContact(Contact ptclContacts[], int &ptclCount, Contact localContacts[], int &localCount, Contact emergencyContacts[], int &emergencyCount)
    {
        AddContact addContactHelper;
        while (true)
        {
            string keyword;
            while (true)
            {
                cout << "\n\n\tEnter search keyword (name, number, or email) for editing: \t";
                getline(cin, keyword);
                if (stringValidation(keyword))
                {
                    break;
                }
                cout << "\n\tInvalid input. Please enter a valid keyword.\n";
            }

            Contact *results[100];
            int resultsCount = 0;

            findContacts(ptclContacts, ptclCount, keyword, results, resultsCount);
            findContacts(localContacts, localCount, keyword, results, resultsCount);
            findContacts(emergencyContacts, emergencyCount, keyword, results, resultsCount);

            if (resultsCount == 0)
            {
                cout << "\n\n\tNo contact found!\n";
                break;
            }
            else if (resultsCount == 1)
            {
                displayContact(*results[0]);
                if (confirmEdit())
                {
                    editSpecificContact(*results[0], ptclContacts, ptclCount, localContacts, localCount, emergencyContacts, emergencyCount, addContactHelper);
                }
                break;
            }
            else
            {
                cout << "\n\n\tMultiple contacts found. Enter more specific keyword to narrow down:\n";
                for (int i = 0; i < resultsCount; ++i)
                {
                    displayContact(*results[i]);
                }
            }
        }
    }

private:
    void findContacts(Contact contacts[], int count, const string &keyword, Contact *results[], int &resultsCount)
    {
        string keywordLower = toLower(keyword);
        for (int i = 0; i < count; ++i)
        {
            if (toLower(contacts[i].getName()).find(keywordLower) != string::npos ||
                contacts[i].getNumber().find(keyword) != string::npos ||
                contacts[i].getEmail().find(keyword) != string::npos)
            {
                results[resultsCount++] = &contacts[i];
            }
        }
    }

    void displayContact(const Contact &contact)
    {
        cout << "\n\tName : \t\t" << contact.getName();
        cout << "\n\tNumber :\t" << contact.getNumber();
        if (contact.getType() != "Emergency")
        {
            cout << "\n\tEmail : \t" << contact.getEmail();
        }
        cout << "\n\tType : \t\t" << contact.getType();
        cout << "\n";
    }

    bool confirmEdit()
    {
        string choice;
        while (true)
        {
            cout << "\n\tDo you want to edit this contact? (y/n): ";
            getline(cin, choice);
            if (stringValidation(choice) && (choice == "y" || choice == "Y" || choice == "n" || choice == "N"))
            {
                return (choice == "y" || choice == "Y");
            }
            cout << "\n\tInvalid input. Please enter 'y' or 'n'.\n";
        }
    }

    void editSpecificContact(Contact &contact, Contact ptclContacts[], int ptclCount, Contact localContacts[], int localCount, Contact emergencyContacts[], int emergencyCount, AddContact &addContactHelper)
    {
        cout << "\n\nEditing contact. Press Enter to skip an attribute.\n";

        string input;
        cout << "\n\tNew name (current: " << contact.getName() << ") : \t";
        getline(cin, input);
        if (!input.empty())
        {
            contact.setName(input);
        }

        while (true)
        {
            cout << "\n\tNew number (current: " << contact.getNumber() << ") : \t";
            getline(cin, input);
            if (input.empty())
            {
                break;
            }
            if ((contact.getType() == "Local" && addContactHelper.localPhoneNumberValidation(input)) ||
                (contact.getType() != "Local" && addContactHelper.phoneNumberValidation(input)))
            {
                if (addContactHelper.isUniqueNumber(input, ptclContacts, ptclCount, localContacts, localCount, emergencyContacts, emergencyCount))
                {
                    contact.setNumber(input);
                    break;
                }
                else
                {
                    cout << "\n\tThis number is already registered. Please enter a different number.\n";
                }
            }
            else
            {
                cout << "\n\tInvalid input. Please enter a valid phone number.\n";
            }
        }

        if (contact.getType() != "Emergency")
        {
            while (true)
            {
                cout << "\n\tNew email (current: " << contact.getEmail() << ") : \t";
                getline(cin, input);
                if (input.empty())
                {
                    break;
                }
                if (addContactHelper.emailValidation(input))
                {
                    if (addContactHelper.isUniqueEmail(input, ptclContacts, ptclCount, localContacts, localCount))
                    {
                        contact.setEmail(input);
                        break;
                    }
                    else
                    {
                        cout << "\n\tThis email is already registered. Please enter a different email.\n";
                    }
                }
                else
                {
                    cout << "\n\tInvalid input. Please enter a valid email ending with @gmail.com.\n";
                }
            }
        }

        cout << "\n\tUpdated Successfully!\n";
    }

    string toLower(const string &str)
    {
        string lowerStr = str;
        transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
        return lowerStr;
    }
};
class DeleteContact : public Validations
{
public:
    void deleteContact(Contact ptclContacts[], int &ptclCount, Contact localContacts[], int &localCount, Contact emergencyContacts[], int &emergencyCount)
    {
        while (true)
        {
            string keyword;
            while (true)
            {
                cout << "\n\n\tEnter search keyword (name, number, or email) for deleting: \t";
                getline(cin, keyword);
                if (stringValidation(keyword))
                {
                    break;
                }
                cout << "\n\tInvalid input. Please enter a valid keyword.\n";
            }

            Contact *results[100];
            int resultsCount = 0;

            findContacts(ptclContacts, ptclCount, keyword, results, resultsCount);
            findContacts(localContacts, localCount, keyword, results, resultsCount);
            findContacts(emergencyContacts, emergencyCount, keyword, results, resultsCount);

            if (resultsCount == 0)
            {
                cout << "\n\n\tNo contact found!\n";
                break;
            }
            else if (resultsCount == 1)
            {
                displayContact(*results[0]);
                if (confirmDeletion())
                {
                    deleteSpecificContact(results[0], ptclContacts, ptclCount, localContacts, localCount, emergencyContacts, emergencyCount);
                    cout << "\n\n\tContact Deleted Successfully!\n";
                }
                break;
            }
            else
            {
                cout << "\n\n\tMultiple contacts found. Enter more specific keyword to narrow down:\n";
                for (int i = 0; i < resultsCount; ++i)
                {
                    displayContact(*results[i]);
                }
            }
        }
    }

private:
    void findContacts(Contact contacts[], int count, const string &keyword, Contact *results[], int &resultsCount)
    {
        string keywordLower = toLower(keyword);
        for (int i = 0; i < count; ++i)
        {
            if (toLower(contacts[i].getName()).find(keywordLower) != string::npos ||
                contacts[i].getNumber().find(keyword) != string::npos ||
                contacts[i].getEmail().find(keyword) != string::npos)
            {
                results[resultsCount++] = &contacts[i];
            }
        }
    }

    void displayContact(const Contact &contact)
    {
        cout << "\n\tName : \t\t" << contact.getName();
        cout << "\n\tNumber :\t" << contact.getNumber();
        if (contact.getType() != "Emergency")
        {
            cout << "\n\tEmail : \t" << contact.getEmail();
        }
        cout << "\n\tType : \t\t" << contact.getType();
        cout << "\n";
    }

    bool confirmDeletion()
    {
        string choice;
        while (true)
        {
            cout << "\n\tAre you sure you want to delete this contact? (y/n): ";
            getline(cin, choice);
            if (stringValidation(choice) && (choice == "y" || choice == "Y" || choice == "n" || choice == "N"))
            {
                return (choice == "y" || choice == "Y");
            }
            cout << "\n\tInvalid input. Please enter 'y' or 'n'.\n";
        }
    }

    void deleteSpecificContact(Contact *contact, Contact ptclContacts[], int &ptclCount, Contact localContacts[], int &localCount, Contact emergencyContacts[], int &emergencyCount)
    {
        if (contact->getType() == "PTCL")
        {
            removeContact(contact, ptclContacts, ptclCount);
        }
        else if (contact->getType() == "Local")
        {
            removeContact(contact, localContacts, localCount);
        }
        else if (contact->getType() == "Emergency")
        {
            removeContact(contact, emergencyContacts, emergencyCount);
        }
    }

    void removeContact(Contact *contact, Contact contacts[], int &count)
    {
        for (int i = 0; i < count; ++i)
        {
            if (&contacts[i] == contact)
            {
                for (int j = i; j < count - 1; ++j)
                {
                    contacts[j] = contacts[j + 1];
                }
                --count;
                break;
            }
        }
    }

    string toLower(const string &str)
    {
        string lowerStr = str;
        transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
        return lowerStr;
    }
};
class FavoriteContact : public Validations
{
public:
    void manageFavorites(Contact ptclContacts[], int ptclCount, Contact localContacts[], int localCount, Contact emergencyContacts[], int emergencyCount, Contact favorites[], int &favCount)
    {
        bool back = false;
        while (!back)
        {
            cout << "\n\n\t ____________________________________________\n";
            cout << "\t|\t   Favorite Contacts\t\t     |\n";
            cout << "\t|____________________________________________|\n";
            cout << "\t|   |" << setw(42) << "|\n";
            cout << "\t| 1 |  Add Favorite " << setw(27) << "|\n";
            cout << "\t| 2 |  Remove Favorite " << setw(24) << "|\n";
            cout << "\t| 3 |  Display Favorites " << setw(22) << "|\n";
            cout << "\t| 0 |  Main page " << setw(30) << "|\n";
            cout << "\t|___|________________________________________|\n\n";
            string choice;
            while (true)
            {
                cout << "\tEnter your choice: ";
                getline(cin, choice);
                if (stringValidation(choice) && (choice == "1" || choice == "2" || choice == "3" || choice == "0"))
                {
                    break;
                }
                cout << "\n\tInvalid input. Please enter a valid choice (0, 1, 2, or 3).\n";
            }

            if (choice == "1")
            {
                addFavorite(ptclContacts, ptclCount, localContacts, localCount, emergencyContacts, emergencyCount, favorites, favCount);
            }
            else if (choice == "2")
            {
                removeFavorite(favorites, favCount);
            }
            else if (choice == "3")
            {
                displayFavorites(favorites, favCount);
            }
            else if (choice == "0")
            {
                back = true;
            }
            else
            {
                cout << "\n\n\tInvalid choice. Please try again.\n";
            }
        }
    }

private:
    void addFavorite(Contact ptclContacts[], int ptclCount, Contact localContacts[], int localCount, Contact emergencyContacts[], int emergencyCount, Contact favorites[], int &favCount)
    {
        while (true)
        {
            string keyword;
            while (true)
            {
                cout << "\n\n\tEnter search keyword (name, number, or email) to add to favorites: \t";
                getline(cin, keyword);
                if (stringValidation(keyword))
                {
                    break;
                }
                cout << "\n\tInvalid input. Please enter a valid keyword.\n";
            }

            Contact *results[100];
            int resultsCount = 0;

            findContacts(ptclContacts, ptclCount, keyword, results, resultsCount);
            findContacts(localContacts, localCount, keyword, results, resultsCount);
            findContacts(emergencyContacts, emergencyCount, keyword, results, resultsCount);

            if (resultsCount == 0)
            {
                cout << "\n\n\tNo contact found!\n";
                break;
            }
            else if (resultsCount == 1)
            {
                if (isFavorite(*results[0], favorites, favCount))
                {
                    cout << "\n\n\tThis contact is already in your favorites.\n";
                }
                else
                {
                    displayContact(*results[0]);
                    if (confirmAddition())
                    {
                        favorites[favCount++] = *results[0];
                        cout << "\n\n\tContact added to favorites successfully!\n";
                    }
                }
                break;
            }
            else
            {
                cout << "\n\n\tMultiple contacts found. Enter more specific keyword to narrow down:\n";
                for (int i = 0; i < resultsCount; ++i)
                {
                    displayContact(*results[i]);
                }
            }
        }
    }

    void removeFavorite(Contact favorites[], int &favCount)
    {
        while (true)
        {
            string keyword;
            while (true)
            {
                cout << "\n\n\tEnter search keyword (name, number, or email) to remove from favorites: \t";
                getline(cin, keyword);
                if (stringValidation(keyword))
                {
                    break;
                }
                cout << "\n\tInvalid input. Please enter a valid keyword.\n";
            }

            Contact *results[100];
            int resultsCount = 0;

            findContacts(favorites, favCount, keyword, results, resultsCount);

            if (resultsCount == 0)
            {
                cout << "\n\n\tNo contact found!\n";
                break;
            }
            else if (resultsCount == 1)
            {
                displayContact(*results[0]);
                if (confirmRemoval())
                {
                    removeContact(results[0], favorites, favCount);
                    cout << "\n\n\tContact removed from favorites successfully!\n";
                }
                break;
            }
            else
            {
                cout << "\n\n\tMultiple contacts found. Enter more specific keyword to narrow down:\n";
                for (int i = 0; i < resultsCount; ++i)
                {
                    displayContact(*results[i]);
                }
            }
        }
    }

    void displayFavorites(Contact favorites[], int favCount)
    {
        if (favCount == 0)
        {
            cout << "\n\n\n\tNo favorite contact found.\n\n";
        }
        else
        {
            for (int i = 0; i < favCount; i++)
            {
                displayContact(favorites[i]);
            }
        }
    }

    void findContacts(Contact contacts[], int count, const string &keyword, Contact *results[], int &resultsCount)
    {
        string keywordLower = toLower(keyword);
        for (int i = 0; i < count; ++i)
        {
            if (toLower(contacts[i].getName()).find(keywordLower) != string::npos ||
                contacts[i].getNumber().find(keyword) != string::npos ||
                contacts[i].getEmail().find(keyword) != string::npos)
            {
                results[resultsCount++] = &contacts[i];
            }
        }
    }

    void displayContact(const Contact &contact)
    {
        cout << "\n\tName : \t\t" << contact.getName();
        cout << "\n\tNumber :\t" << contact.getNumber();
        if (contact.getType() != "Emergency")
        {
            cout << "\n\tEmail : \t" << contact.getEmail();
        }
        cout << "\n\tType : \t\t" << contact.getType();
        cout << "\n";
    }

    bool confirmAddition()
    {
        string choice;
        while (true)
        {
            cout << "\n\tAre you sure you want to add this contact to favorites? (y/n): ";
            getline(cin, choice);
            if (stringValidation(choice) && (choice == "y" || choice == "Y" || choice == "n" || choice == "N"))
            {
                return (choice == "y" || choice == "Y");
            }
            cout << "\n\tInvalid input. Please enter 'y' or 'n'.\n";
        }
    }

    bool confirmRemoval()
    {
        string choice;
        while (true)
        {
            cout << "\n\tAre you sure you want to remove this contact from favorites? (y/n): ";
            getline(cin, choice);
            if (stringValidation(choice) && (choice == "y" || choice == "Y" || choice == "n" || choice == "N"))
            {
                return (choice == "y" || choice == "Y");
            }
            cout << "\n\tInvalid input. Please enter 'y' or 'n'.\n";
        }
    }

    void removeContact(Contact *contact, Contact contacts[], int &count)
    {
        for (int i = 0; i < count; ++i)
        {
            if (&contacts[i] == contact)
            {
                for (int j = i; j < count - 1; ++j)
                {
                    contacts[j] = contacts[j + 1];
                }
                --count;
                break;
            }
        }
    }

    bool isFavorite(const Contact &contact, Contact favorites[], int favCount)
    {
        for (int i = 0; i < favCount; ++i)
        {
            if (favorites[i].getName() == contact.getName() &&
                favorites[i].getNumber() == contact.getNumber() &&
                favorites[i].getEmail() == contact.getEmail())
            {
                return true;
            }
        }
        return false;
    }

    string toLower(const string &str)
    {
        string lowerStr = str;
        transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
        return lowerStr;
    }
};
class AllContacts
{
public:
    void displayAllContacts(Contact ptclContacts[], int ptclCount, Contact localContacts[], int localCount, Contact emergencyContacts[], int emergencyCount)
    {
        bool hasLocal = false;
        bool hasPTCL = false;
        bool hasEmergency = false;

        cout << "\n\n\tLocal Contacts:\n";
        for (int i = 0; i < localCount; i++)
        {
            displayContact(localContacts[i]);
            hasLocal = true;
        }

        if (!hasLocal)
        {
            cout << "\n\tNo Local contacts found.\n";
        }

        cout << "\n\n\tPTCL Contacts:\n";
        for (int i = 0; i < ptclCount; i++)
        {
            displayContact(ptclContacts[i]);
            hasPTCL = true;
        }

        if (!hasPTCL)
        {
            cout << "\n\tNo PTCL contacts found.\n";
        }

        cout << "\n\n\tEmergency Contacts:\n";
        for (int i = 0; i < emergencyCount; i++)
        {
            displayContact(emergencyContacts[i]);
            hasEmergency = true;
        }

        if (!hasEmergency)
        {
            cout << "\n\tNo Emergency contacts found.\n";
        }
    }

private:
    void displayContact(const Contact &contact)
    {
        cout << "\n\tName : \t\t" << contact.getName();
        cout << "\n\tNumber :\t" << contact.getNumber();
        if (contact.getType() != "Emergency")
        {
            cout << "\n\tEmail : \t" << contact.getEmail();
        }
        cout << "\n\tType : \t\t" << contact.getType();
        cout << "\n";
    }
};
class Login : public Validations
{
public:
    bool authenticate()
    {
        int attempts = 0;
        string password;
        cout << "\n\n\t****** Login *****\n";
        while (true)
        {
            cout << "\n\tEnter your Password :  ";
            getline(cin, password);
            if (stringValidation(password))
            {
                if (attempts >= 3)
                {
                    showEmergencyContacts();
                    string choice;
                    while (true)
                    {
                        cout << "\n\tDo you want to continue logging in or exit? (login/exit): ";
                        getline(cin, choice);
                        if (stringValidation(choice) && (choice == "login" || choice == "exit"))
                        {
                            break;
                        }
                        cout << "\n\tInvalid input. Please enter 'login' or 'exit'.\n";
                    }
                    if (choice == "exit")
                    {
                        return false;
                    }
                    else
                    {
                        attempts = 0;
                        continue;
                    }
                }
                if (password == storedPassword)
                {
                    cout << "\n\tPlease wait ";
                    for (int i = 0; i < 5; i++)
                    {
                        cout << ".";
                        Sleep(300);
                    }
                    cout << "\n\n\tPassword matched!";
                    Sleep(1000);
                    system("cls");
                    cout << "\n\n\n\t ******* Welcome to Phone-book Project ******\n";
                    return true;
                }
                else
                {
                    system("cls");
                    cout << "\n\n\tWrong Password!";
                    attempts++;
                }
            }
            cout << "\n\tInvalid input. Please enter a valid password.\n";
        }
    }

    void changePassword()
    {
        string oldPassword, newPassword;
        while (true)
        {
            cout << "\n\tEnter your old password: ";
            getline(cin, oldPassword);
            if (stringValidation(oldPassword))
            {
                if (oldPassword == storedPassword)
                {
                    while (true)
                    {
                        cout << "\n\tEnter your new password: ";
                        getline(cin, newPassword);
                        if (stringValidation(newPassword))
                        {
                            storedPassword = newPassword;
                            cout << "\n\tPassword changed successfully!\n";
                            return;
                        }
                        cout << "\n\tInvalid input!";
                    }
                }
                else
                {
                    cout << "\n\tIncorrect old password!\n";
                    return;
                }
            }
            else
            {
                cout << "\n\tInvalid input!";
            }
        }
    }

private:
    void showEmergencyContacts()
    {
        cout << "\n\n\tEmergency Contacts:\n";
        cout << "\t1. Police - 911\n";
        cout << "\t2. Fire Department - 911\n";
        cout << "\t3. Ambulance - 911\n";
        cout << "\t4. Poison Control - 911\n";
        cout << "\t5. Disaster Relief - 911\n";
        cout << "\t6. Animal Control - 911\n";
        cout << "\t7. Coast Guard - 911\n";
        cout << "\t8. Mountain Rescue - 911\n";
        cout << "\t9. Suicide Hotline - 911\n";
        cout << "\t10. Gas Leak - 911\n";
    }

    string storedPassword = "123";
};
class PhoneBookApp : public AddContact, public DeleteContact, public SearchContact, public EditContact, public AllContacts, public FavoriteContact
{
protected:
    Contact ptclContacts[100];
    Contact localContacts[100];
    Contact emergencyContacts[100];
    Contact favorites[100];

    int ptclCount = 0;
    int localCount = 0;
    int emergencyCount = 0;
    int favCount = 0;

    Login login;

public:
    PhoneBookApp(Login &loginObj) : login(loginObj)
    {
        cout << "\n\n\t ********** Welcome to Phone Book **********\n";
        initializeEmergencyContacts();
    }

    void displayMenu()
    {
        cout << "\n\n\t ____________________________________________\n";
        cout << "\t|\t\t   Phone Book\t\t     |\n";
        cout << "\t|____________________________________________|\n";
        cout << "\t|   |" << setw(42) << "|\n";
        cout << "\t| 1 |  New Contact " << setw(28) << "|\n";
        cout << "\t| 2 |  Edit a contact " << setw(25) << "|\n";
        cout << "\t| 3 |  Search Contact " << setw(25) << "|\n";
        cout << "\t| 4 |  Delete Contact " << setw(25) << "|\n";
        cout << "\t| 5 |  List all Contacts " << setw(22) << "|\n";
        cout << "\t| 6 |  Favorite Contacts " << setw(22) << "|\n";
        cout << "\t| 7 |  Change Password " << setw(24) << "|\n";
        cout << "\t| 0 |  Exit " << setw(35) << "|\n";
        cout << "\t|___|________________________________________|\n\n";
        cout << "\tPress a key to continue ... ";
    }

    void startApp()
    {
        while (true)
        {
            displayMenu();
            string choice;
            getline(cin, choice);
            if (choice == "1")
            {
                system("cls");
                addContact(ptclContacts, ptclCount, localContacts, localCount, emergencyContacts, emergencyCount);
            }
            else if (choice == "2")
            {
                system("cls");
                editContact(ptclContacts, ptclCount, localContacts, localCount, emergencyContacts, emergencyCount);
            }
            else if (choice == "3")
            {
                system("cls");
                searchContacts(ptclContacts, ptclCount, localContacts, localCount, emergencyContacts, emergencyCount);
            }
            else if (choice == "4")
            {
                system("cls");
                deleteContact(ptclContacts, ptclCount, localContacts, localCount, emergencyContacts, emergencyCount);
            }
            else if (choice == "5")
            {
                system("cls");
                displayAllContacts(ptclContacts, ptclCount, localContacts, localCount, emergencyContacts, emergencyCount);
            }
            else if (choice == "6")
            {
                system("cls");
                manageFavorites(ptclContacts, ptclCount, localContacts, localCount, emergencyContacts, emergencyCount, favorites, favCount);
            }
            else if (choice == "7")
            {
                system("cls");
                login.changePassword();
            }
            else if (choice == "0")
            {
                cout << "\n\n\tThank you for using Phone Book. Goodbye!\n";
                break;
            }
            else
            {
                cout << "\n\n\tInvalid choice. Please try again.\n";
            }
        }
    }

private:
    void initializeEmergencyContacts()
    {
        emergencyContacts[emergencyCount++] = Contact("Police", "911", "", "Emergency");
        emergencyContacts[emergencyCount++] = Contact("Fire Department", "911", "", "Emergency");
        emergencyContacts[emergencyCount++] = Contact("Ambulance", "911", "", "Emergency");
        emergencyContacts[emergencyCount++] = Contact("Poison Control", "911", "", "Emergency");
        emergencyContacts[emergencyCount++] = Contact("Disaster Relief", "911", "", "Emergency");
        emergencyContacts[emergencyCount++] = Contact("Animal Control", "911", "", "Emergency");
        emergencyContacts[emergencyCount++] = Contact("Coast Guard", "911", "", "Emergency");
        emergencyContacts[emergencyCount++] = Contact("Mountain Rescue", "911", "", "Emergency");
        emergencyContacts[emergencyCount++] = Contact("Suicide Hotline", "911", "", "Emergency");
        emergencyContacts[emergencyCount++] = Contact("Gas Leak", "911", "", "Emergency");
    }
};
int main()
{
    Login login;
    if (login.authenticate())
    {
        PhoneBookApp app(login);
        app.startApp();
    }
    return 0;
}


