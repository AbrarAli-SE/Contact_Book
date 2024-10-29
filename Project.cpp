#include <iostream>
#include <string>
#include <array>
#include <iomanip>
#include <windows.h>
using namespace std;
int id = 0;
bool startup = true;
struct contact
{
    string names,
        numbers,
        emails;
};
struct contact contacts[100];
void loginpage() // login
{
    string signuppassword;
    cout << "\n\n\t****** Sign-up *****\n";
    cout << "\n\tChoose a Password:  ";
    getline(cin, signuppassword);
    cout << "\n\tPlease wait ";
    for (int i = 0; i < 5; i++)
    {
        cout << ".";
        Sleep(400);
    }
    cout << "\n\n\tSign-up Done Successful!";
    Sleep(1000);
    system("cls");
    while (true)
    {
        string password;
        cout << "\n\n\t****** Login *****\n";
        cout << "\n\tEnter your Password :  ";
        getline(cin, password);
        cout << "\n\tPlease wait ";
        for (int i = 0; i < 5; i++)
        {
            cout << ".";
            Sleep(400);
        }
        if (password == signuppassword)
        {
            cout << "\n\n\tPassword matched!";
            Sleep(1000);
            system("cls");
            cout << "\n\n\n\t ******* Wellcome to Phone-book Project ******\n";
            startup = !(startup);
            break;
        }
        else
        {
            system("cls");
            cout << "\n\n\tWronge Password!";
        }
    }
}
void mainpage() // start choice options
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
    cout << "\t| 0 |  Exit " << setw(35) << "|\n";
    cout << "\t|   |" << setw(42) << "|\n";
    cout << "\t|___|________________________________________|\n\n";
    cout << "\tPress a key to continue ... ";
}
void newcontact() // for new numbers
{
    bool main_page = false;
    system("cls");
    for (id; id < 100; id++)
    {
        if (main_page == true)
        {
            break;
        }
        cin.ignore();
        cout << "\n\nPerson " << id + 1 << " :";
        cout << "\n\t Name : \t";
        getline(cin, contacts[id].names);
        cout << "\t Number :\t";
        getline(cin, contacts[id].numbers);
        cout << "\t Email : \t";
        getline(cin, contacts[id].emails);
        cout << "\n\n";
        while (true)
        {
            cout << "\tDo you want to add another (y/n): ";
            string a;
            cin >> a;
            if (a == "n" || a == "N")
            {
                system("cls");
                main_page = true;
                break;
            }
            else if (a == "Y" || a == "y")
            {
                break;
            }
            else
            {
                cout << "\n\tInvalid Choice!\n";
            }
        }
    }
}
void allcontacts() // All contacts
{
    if (id == 0)
    {
        cout << "\n\n\n\tNo contact found.Please add at least one!\n\n";
    }
    else
    {
        for (int i = 0; i < id; i++)
        {
            cout << "\n\nPerson " << i + 1 << " :";
            cout << "\n\t Name : \t" << contacts[i].names;
            cout << "\n\t Number :\t" << contacts[i].numbers;
            cout << "\n\t Email : \t" << contacts[i].emails;
            cout << "\n";
        }
    }
}
void deletecontacts() // Delete
{
    bool back = false; // for terminating main loop for main
    while (back == false)
    {
        cout << "\n\n\t ____________________________________________\n";
        cout << "\t|\t\t   Phone Book\t\t     |\n";
        cout << "\t|____________________________________________|\n";
        cout << "\t|   |" << setw(42) << "|\n";
        cout << "\t| 1 |  Delete All  " << setw(28) << "|\n";
        cout << "\t| 2 |  Delete Specific" << setw(25) << "|\n";
        cout << "\t| 0 |  Main page " << setw(30) << "|\n";
        cout << "\t|   |" << setw(42) << "|\n";
        cout << "\t|   |" << setw(42) << "|\n";
        cout << "\t|   |" << setw(42) << "|\n";
        cout << "\t|___|________________________________________|\n\n";
        cout << "\tPress a key to continue ... ";
        string dell;
        cin >> dell;
        bool option = false; // for terminating interior loop
        bool del = false;    // for else condition
        while (option == false)
        {
            if (dell == "1")
            {
                for (int i = 0; i < 100; i++)
                {
                    contacts[i].names.clear();
                    contacts[i].numbers.clear();
                    contacts[i].emails.clear();
                }
                id = 0;
                system("cls");
                cout << "\n\n\tAll contacts Deleted Successful!";
                break;
            }
            else if (dell == "2")
            {
                cin.ignore();
                cout << "\n\n\tEnter the Name of person : \t";
                string dellbyname;
                getline(cin, dellbyname);
                for (int i = 0; i < 100; i++)
                {
                    if (dellbyname == contacts[i].names)
                    {
                        contacts[i].names.clear();
                        contacts[i].numbers.clear();
                        contacts[i].emails.clear();
                        for (int j = i; j <= id; j++)
                        {
                            // for swap names
                            string *n1, *n2, tempn;
                            n1 = &contacts[j].names;
                            n2 = &contacts[j + 1].names;
                            tempn = *n1;
                            *n1 = *n2;
                            *n2 = tempn;
                            // for swap numbers
                            string *num1, *num2, tempnum;
                            num1 = &contacts[j].numbers;
                            num2 = &contacts[j + 1].numbers;
                            tempn = *num1;
                            *num1 = *num2;
                            *num2 = tempnum;
                            // for swap emails
                            string *e1, *e2, tempe;
                            e1 = &contacts[j].emails;
                            e2 = &contacts[j + 1].emails;
                            tempe = *e1;
                            *e1 = *e2;
                            *e2 = tempe;
                        }
                        --id;
                        system("cls");
                        cout << "\n\n\tContact Deleted Successful!";
                        del = true;
                        option = true;
                        break;
                    }
                }
                if (del == false)
                {
                    system("cls");
                    cout << "\n\n\n\tNo contact found! \n\n";
                    del = true;
                    break;
                }
            }
            else if (dell == "0")
            {
                system("cls");
                back = true;
                break;
            }
            else
            {
                system("cls");
                cout << "\n\n\tInvalid Choice!\n\n";
                break;
            }
        }
    }
}
void searchingcontacts() // searching contact
{
    bool back = false; // for terminating main loop for main
    while (back == false)
    {
        cout << "\n\n\t ____________________________________________\n";
        cout << "\t|\t\t   Phone Book\t\t     |\n";
        cout << "\t|____________________________________________|\n";
        cout << "\t|   |" << setw(42) << "|\n";
        cout << "\t| 1 |  Search By Name  " << setw(24) << "|\n";
        cout << "\t| 2 |  Search By Numbers" << setw(23) << "|\n";
        cout << "\t| 0 |  Main page " << setw(30) << "|\n";
        cout << "\t|   |" << setw(42) << "|\n";
        cout << "\t|   |" << setw(42) << "|\n";
        cout << "\t|   |" << setw(42) << "|\n";
        cout << "\t|___|________________________________________|\n\n";
        cout << "\tPress a key to continue ... ";
        string search;
        cin >> search;
        bool option = false; // for terminating interior loop
        bool srch = false;   // for else condition
        while (option == false)
        {
            if (search == "1")
            {
                string searchbyname;
                cin.ignore();
                cout << "\n\n\tEnter the name of person : \t";
                getline(cin, searchbyname);
                for (int i = 0; i < 100; i++)
                {
                    if (searchbyname == contacts[i].names)
                    {
                        system("cls");
                        cout << "\n\nPerson " << i + 1 << " :";
                        cout << "\n\t Name : \t" << contacts[i].names << endl;
                        cout << "\t Number :\t" << contacts[i].numbers << endl;
                        cout << "\t Email : \t" << contacts[i].emails << endl;
                        srch = true;
                        option = true;
                        break;
                    }
                }
                if (srch == false)
                {
                    system("cls");
                    cout << "\n\n\n\tNo contact found! \n\n";
                    break;
                }
            }
            else if (search == "2")
            {
                cin.ignore();
                cout << "\n\n\tEnter the Number of person : \t";
                string searchbynumber;
                getline(cin, searchbynumber);
                for (int i = 0; i < 100; i++)
                {
                    if (searchbynumber == contacts[i].numbers)
                    {
                        system("cls");
                        cout << "\n\nPerson " << i + 1 << " :";
                        cout << "\n\t Name : \t" << contacts[i].names << endl;
                        cout << "\t Number :\t" << contacts[i].numbers << endl;
                        cout << "\t Email : \t" << contacts[i].emails << endl;
                        srch = true;
                        option = true;
                        break;
                    }
                }
                if (srch == false)
                {
                    system("cls");
                    cout << "\n\n\n\tNo contact found! \n\n";
                    srch = true;
                    break;
                }
            }
            else if (search == "0")
            {
                system("cls");
                back = true;
                break;
            }
            else
            {
                system("cls");
                cout << "\n\n\tInvalid Choice!\n\n";
                break;
            }
        }
    }
}
void editcontact() // edit contact
{
    bool back = false; // for terminating main loop for main
    while (back == false)
    {
        cout << "\n\n\t ____________________________________________\n";
        cout << "\t|\t\t   Phone Book\t\t     |\n";
        cout << "\t|____________________________________________|\n";
        cout << "\t|   |" << setw(42) << "|\n";
        cout << "\t| 1 |  Edit by Number " << setw(25) << "|\n";
        cout << "\t| 2 |  Edit by Name " << setw(27) << "|\n";
        cout << "\t| 0 |  Main page " << setw(30) << "|\n";
        cout << "\t|   |" << setw(42) << "|\n";
        cout << "\t|   |" << setw(42) << "|\n";
        cout << "\t|   |" << setw(42) << "|\n";
        cout << "\t|___|________________________________________|\n\n";
        cout << "\tPress a key to continue ... ";
        string edit;
        cin >> edit;
        bool option = false; // for terminating interior loop
        bool edt = false;    // for else condition
        while (option == false)
        {
            if (edit == "1")
            {
                string editbynumber;
                cin.ignore();
                cout << "\n\n\tEnter Person number : \t";
                getline(cin, editbynumber);
                for (int i = 0; i < 100; i++)
                {
                    if (editbynumber == contacts[i].numbers)
                    {
                        system("cls");
                        cout << "\n\n Old contact Details:\n";
                        cout << "\n\nPerson " << i + 1 << " :";
                        cout << "\n\tName : \t" << contacts[i].names << endl;
                        cout << "\tNumber :\t" << contacts[i].numbers << endl;
                        cout << "\tEmail : \t" << contacts[i].emails << endl;
                        cout << "\n\n Enter new Details:\n";
                        // cin.ignore();
                        cout << "\n\tNew name : \t";
                        getline(cin, contacts[i].names);
                        cout << "\n\tNew Number :\t";
                        getline(cin, contacts[i].numbers);
                        cout << "\n\tNew Email :\t";
                        getline(cin, contacts[i].emails);
                        cout << "\n\tUpdated Successfull!\n";
                        edt = true;
                        option = true;
                        break;
                    }
                }
                if (edt == false)
                {
                    system("cls");
                    cout << "\n\n\n\tNo contact found! \n\n";
                    break;
                }
            }
            else if (edit == "2")
            {
                cin.ignore();
                cout << "\n\n\tEnter the Name of person : \t";
                string editbyname;
                getline(cin, editbyname);
                for (int i = 0; i < 100; i++)
                {
                    if (editbyname == contacts[i].names)
                    {
                        system("cls");
                        cout << "\n\n Old contact Details:\n";
                        cout << "\n\nPerson " << i + 1 << " :";
                        cout << "\n\tName : \t" << contacts[i].names << endl;
                        cout << "\tNumber :\t" << contacts[i].numbers << endl;
                        cout << "\tEmail : \t" << contacts[i].emails << endl;
                        cout << "\n\n Enter new Details:\n";
                        // cin.ignore();
                        cout << "\n\tNew name : \t";
                        getline(cin, contacts[i].names);
                        cout << "\n\tNew Number :\t";
                        getline(cin, contacts[i].numbers);
                        cout << "\n\tNew Email :\t";
                        getline(cin, contacts[i].emails);
                        cout << "\n\tUpdated Successfull!\n";
                        edt = true;
                        option = true;
                        break;
                    }
                }
                if (edt == false)
                {
                    system("cls");
                    cout << "\n\n\n\tNo contact found! \n\n";
                    edt = true;
                    break;
                }
            }
            else if (edit == "0")
            {
                system("cls");
                back = true;
                break;
            }
            else
            {
                system("cls");
                cout << "\n\n\tInvalid Choice!\n\n";
                break;
            }
        }
    }
}
int main()
{
    while (startup) // password
    {
        loginpage();
    }
    while (true)
    {
        mainpage();
        string startchoice;
        cin >> startchoice;
        if (startchoice == "1") // new contacts open
        {
            newcontact();
        }
        else if (startchoice == "2") // Edit a contect
        {
            system("cls");
            editcontact();
        }
        else if (startchoice == "3") // searching contacts
        {
            system("cls");
            searchingcontacts();
        }
        else if (startchoice == "4") // for delete
        {
            system("cls");
            deletecontacts();
        }
        else if (startchoice == "5") // all list options
        {
            system("cls");
            allcontacts();
        }
        else if (startchoice == "0") // exit option
        {
            cout << "\n\n\t Thanks for using\n\t Good bye ... \n\n\n";
            break;
        }
        else // wronge option
        {
            system("cls");
            cout << "\n\tWronge Option!\n";
        }
    }
    return 0;
}