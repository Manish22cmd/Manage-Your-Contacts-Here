#include<iostream>
#include<fstream>
#include<math.h>
#include<iomanip>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

using namespace std;

// create all the neccessary functions
int mainmenu();
void delete_contact();
void list_of_contacts();
void edit_contact();
void exit();

// create a class which will add/create a contact and tell the compiler that how to display that
class your_contacts
{
	/*
	long int mobile;
	char name[100],nickname[100], email[100], comp[100], job_title[100], relation[100], address[100];
	*/
	// make the add contact public
	public:
		long int mobile;
		char name[100],nickname[100], email[100], comp[100], job_title[100], relation[100], address[100] ;
		void add_contact()
		{
			// there can be repetition of char. so we would be using cin.ignore()
			cout << "\n Mobile no.: " ;
			cin.ignore() ;
			cin >> mobile ;
			cout << "\n Name: " ;
			cin.ignore() ;
			cin >> name ;
			cout << "\n Nickname/Phonetic name: " ;
			cin.ignore();
			cin >> nickname ;
			cout << "\n Email: " ;
			cin.ignore();
			cin >> email ;
			cout << "\n Job Title: " ;
			cin.ignore() ;
			cin >> job_title ;
			cout << "\n Comapany/College: " ;
			cin.ignore() ;
			cin >> comp ;
			cout << "\n Relationship: " ;
			cin.ignore();
			cin >> relation ;
			cout << "\n Address: " ;
			cin.ignore() ;
			cin >> address ;
		}
		
		// now tell the compiler how to display/show the contacts list
		void view_contacts()
		{
			cout << "\n --------------------------------------" ;
			cout << "\n Mobile Number: " << mobile ;
			cout << "\n Name: " << name ;
			cout << "\n Nickname/Phonetic name: " << nickname ;
			cout << "\n Email ID: " << email ;
			cout << "\n Job Title: " << job_title ;
			cout << "\n Company/College: " << comp ;
			cout << "\n Relationship: " << relation ;
			cout << "\n Address: " << address ;
			cout << "\n --------------------------------------" << endl ;
			// Note:- here extra borders are used to separate two contacts
			// otherwise it will be hectic to understand which is next
		}
		
		// get all the details that will be used further
		// to call or get the specified detail
		long int getmob()
		{
			return mobile ;
		}
		char* getPersonName()
		{
			return name ;
		}
		char* getNickname() {
			return nickname ;
		}
		char* getEmailId() {
			return email ;
		}
		char* getWorkInfo() {
			return job_title ;
		}
		char* getComapny() {
			return comp ;
		}
		char* getRelationship() {
			return relation ;
		}
		char* getAddress() {
			return address ;
		}
};

// create obj for the class your_contacts()
your_contacts yc ;
// also create the obj for the file
fstream file ; // we have globally declared so that we don't need to declare again and again
fstream file1 ; // will be used in delete module to create a new file

// create a function that will call add_contact()
void create_your_contact()
{
	system("CLS");
	cout << endl;
	cout << "                 -------------------------------- " ;
	cout << "\n \t\t    Add/Create Contact Module " <<endl;
	cout << "                 -------------------------------- " ;
	// open/create a txt file
	file.open("contacts.txt", ios::out|ios::app|ios::binary) ;
	// call the add_contact() via yc
	yc.add_contact() ;
	// now write in contacts.txt file
	file.write((char*)&yc,sizeof(your_contacts)) ;
	/*
	file << "\n Mobile No.: " << mob ;
	file << "\n Name: " << name ;
	file << "\n Nickname/Phonetic name: " << nickname ;
	file << "\n Email ID: " << email ;
	file << "\n Job title: " << job_title ;
	file << "\n Comapany/College: " << comp ;
	file << "\n Relationship: " << relation ;
	file << "\n Address: " << address ;
	*/
	// close the opened file
	file.close() ;
	
	cout << "\n This contact has been successfully added to your contact list" ;
	getchar();
}

// now to delete any contact that user want
void delete_contact()
{
	int flag = 0 ;
	system("CLS");
	cout << endl;
	cout << "               ----------------------------- " ;
	cout << "\n \t\t    Delete Contact Module " <<endl;
	cout << "               ----------------------------- " ;
	// first search for the req.contact via mobile no.
	int mob ;
	cout << "\n Enter the mobile number of the contact you want to delete: " ;
	cin >> mob ;
	
	// open the file and search there for the req. mob no.
	file.open("contacts.txt",ios::in|ios::out|ios::binary) ;
	
	// create a new file pointer and file 
	// where we will store all the other details
	file1.open("another_contacts_file.txt",ios::out|ios::binary) ;
	file.seekg(0,ios::beg) ;
	while(file.read((char*)&yc,sizeof(your_contacts))) {
		if(yc.getmob()==mob) { flag = 1 ; cout << "\n Record found and is deleted successfully." << endl ;
		}
		else if(yc.getmob()!=mob) {
			file1.write((char*)&yc,sizeof(your_contacts)) ;
		}
	}
	if (flag == 0) { cout << "\n Requested record not found!!!" ;
			cout << "\n Hence, Deletion operation can't be performed." ;
	}
	file1.close() ;
	file.close() ;
	// remove the contacts.txt file
	remove("contacts.txt") ;
	// rename the second file created to the primary file ie contacts.txt
	rename("another_contacts_file.txt", "contacts.txt") ;
}

// now to search for a particular contact that is in the file or not
void search_contact(int key) // here, key will be used to search based on the mobile number
{
	bool found = 0 ; // it will return 0 or 1
	// 0 = false and 1 = true
	
	file.open("contacts.txt",ios::in) ;
	while(file.read((char*)&yc,sizeof(your_contacts))) {
		if (yc.getmob() == key) {
			cout << "\n Your requested contact is found." << endl ;
			yc.view_contacts();
			found = 1 ;
		}
	}
	file.close() ;
	if (found == 0) {
		cout << "\n No record found or have been deleted!!!" ;
	}
	getchar();
}

// this func will show all the contacts
void list_of_contacts()
{
	system("CLS");
	cout << endl;
	cout << "                 ----------------------------- " ;
	cout << "\n \t\t       Your Contact List " <<endl;
	cout << "                 ----------------------------- " ;
	cout << endl << endl ;
	
	file.open("contacts.txt", ios::in) ;
	while(file.read((char*)&yc, sizeof(your_contacts))) {
		yc.view_contacts() ;
	}
	file.close() ;
}

// to modify/edit any contact 
void edit_contact()
{
	system("CLS");
	cout << endl;
	cout << "               ----------------------------- " ;
	cout << "\n \t\t    Modify any Contact " <<endl;
	cout << "               ----------------------------- " ;
	cout << endl ;
	
	bool found = 0 ;
	int key ;
	cout << "\n Enter the mobile number of the person to edit: " ;
	cin >> key ;
	// open the file to search for the contact
	file.open("contacts.txt", ios::in|ios::out) ;
	while(file.read((char*)&yc, sizeof(your_contacts)) && found == 0 ) {
		if (yc.getmob() == key) {
			cout << "\n Details of the requested person as per the previous record updated." << endl ;
			yc.view_contacts() ;
			cout << "\n Modify the details below." << endl ;
			
			// call the add_contact() func so that you can edit in the same way
			yc.add_contact() ;
			int pos=-1*sizeof(yc);
			file.seekp(pos,ios::cur) ;
			file.write((char*)&yc,sizeof(yc)) ;
			cout << "\n This contact is successfully modified/updated." ;
			// increase the value of found to 1 otherwise it will be still 0
			// and will show contact not found always
			found = 1 ;
		}
	}
	file.close() ;
	if (found == 0) {
		cout << "\n Requested Contact Not Found or it may have been deleted!!!" ;
	}
}

// mainmenu()
int mainmenu()
{
	int ch;
	char chs;
	cout << "\n \n \t\t ********** Contact Book Management System **********" ;
	cout << "\n \t\t               Manage your contacts here" ;
	
	// now display the mainmenu
	cout << " \n \n\n \t ************ MAINMENU ************ " << endl ;
	cout << "\t 1. Add/Create Contact" << endl ;
	cout << "\t 2. Delete any Contact" << endl ;
	cout << "\t 3. View your Contact List" << endl ;
	cout << "\t 4. Modify Contact" << endl ;
	cout << "\t 5. Search for a Contact" << endl ;
	cout << "\t 6. Exit the module" << endl ;
	
	// get the choice of the user
	cout << "\n Your Choice: " ;
	cin >> ch;
	
	// now use the switch case to traverse all modules based on the choice that user made
	switch(ch)
	{
		case 1:
			
			// call the function
			create_your_contact();
			break;
		
		case 2:
			
			// call the function
			delete_contact();
			break;
			
		case 3:
			
			// call the function
			list_of_contacts();
			break;
			
		case 4:
			
			// call the function
			edit_contact();
			break;
			
		case 5:
			system("CLS");
			cout << endl;
			cout << "               ----------------------------- " ;
			cout << "\n \t\t    Search any Contact " <<endl;
			cout << "               ----------------------------- " ;
			int key ;
			cout << "\n Mobile No. of the person to be searched for: " ;
			cin >> key ;
			// call the function
			search_contact(key);
			break;
			
		case 6:
			exit(0);
			break;
		
		default:
			cout << "\n Invalid Choice!!" << endl ;
	}
	
	// ask the user whether he will perform the actions more or not
	cout << "\n\n Do you want to perform more actions? " ;
	cin >> chs ;
	if (chs == 'Y' || chs == 'y'|| chs == 'yes' || chs == 'YES' || chs == 'Yes' || chs == '1' ) {
		system("CLS") ;
		mainmenu();
	} 
	 else if ( chs == 'n' || chs == 'N' || chs == 'no' || chs == 'NO' || chs == 'No' || chs == '0' ) { exit(0) ; }
	 else { cout << "Invalid choice!!!" ; cout << "\n Exiting the module...... " ; exit(0); }
}

int main()
{
	mainmenu();
	
    return 0;
}
