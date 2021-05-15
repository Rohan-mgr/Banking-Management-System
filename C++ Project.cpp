// C++ project second semester
// Banking Management System
#include<iostream>
#include<conio.h>
#include<string.h>
#include<fstream>
#include<iomanip>
using namespace std; 
class account
{
	private: 
	char name[30], account_type[7];
	int deposit, account_number;
	unsigned long int withdraw;
	public: 
	void new_account();
	void modify();
	void display_account();
	void show_account();
	int return_acc_no();
	void modify_deposit_amount();
	void modify_withdraw_amount();
	int return_withdraw_amount();
	int return_deposit_amount();
};
void account::new_account()				// creating a account for the customer
{
	system("cls");
	cout<<"\n================ New Account Entry Form =================\n"<<endl;
	cout<<"Enter Account Number: ";
	cin>>account_number;
	cout<<"Enter your Name: ";
	cin.ignore();
	cin.getline(name, 29);
	cout<<"Enter Account Type(current/saving): ";
	cin>>account_type;
	cout<<"Enter your Deposit Balance: ";
	cin>>deposit;
}
void account::modify()
{
	cout<<"\nModify Account Holder Name: ";
	cin.ignore();
	cin.getline(name, 30);
	cout<<"Modify Account Type: ";
	cin>>account_type;
	cout<<"Modify Deposit Balance: ";
	cin>>deposit;
}
void account::display_account()			// showing an account
{
	cout<<left<<setw(15)<<account_number<<left<<setw(30)<<name<<left<<setw(19)<<account_type<<left<<setw(10)<<deposit<<endl;
}
void account::show_account()
{
	cout<<"\n---------------Account Details----------------"<<endl;
	cout<<"A/C No: "<<account_number<<endl;
	cout<<"Account Holder Name: "<<name<<endl;
	cout<<"Account Type: "<<account_type<<endl;
	cout<<"Deposit: "<<deposit<<endl;	
}
int account::return_acc_no()
{
	return account_number;
}
void account::modify_deposit_amount()
{
	int new_deposit;
	cout<<"\nEnter Amount to be deposited: ";
	cin>>new_deposit;
	deposit = deposit + new_deposit;
}
void account::modify_withdraw_amount()
{
	cout<<"\nEnter Amount to be withdrawn: ";
	cin>>withdraw;
	if(withdraw <= deposit)
	{
		deposit = deposit - withdraw;
		cout<<"\n************* Withdraw Updated Successfully ****************"<<endl;	
	}
	else
	{
		cout<<"\nSorry! Withdraw is not possible!"<<endl;
	}
	
}
int account::return_withdraw_amount()
{
	return withdraw;
}
int account::return_deposit_amount()
{
	return deposit;
}
// End of a class 


// declaration and definition of main functions
void create_account()							// main function to create an account
{
	account a; 
	ofstream fout;
	fout.open("bank.dat", ios::binary | ios::out | ios::app);
	a.new_account();
	fout.write((char*)&a, sizeof(account));
	fout.close();
	cout<<"\n*************Records Updated Successfully***************"<<endl;
	getch();
}

void modify_account()							// main function to modify account
{
	account a;
	fstream file;
	int temp_acc_no;
	cout<<"Enter Account Number Which is to be modified: ";
	cin>>temp_acc_no;
	file.open("bank.dat", ios::in | ios::binary | ios::out);
	file.seekg(0, ios::beg);
	while(file.read((char*)&a, sizeof(account)))
	{
		if(temp_acc_no == a.return_acc_no())
		{
			a.show_account();
			cout<<"\nEnter new details of account: ";
			int position = sizeof(account);
			file.seekp(-position, ios::cur);
			a.modify();
			file.write((char*)&a, sizeof(account));
			cout<<"\n-------------Records Updated Successfully---------------"<<endl;
			getch();
		}
	}
	if(temp_acc_no != a.return_acc_no())
	{
		cout<<"\nAccount not found!!!!"<<endl;
		getch();
	}
	file.close();
}

void delete_account()							// main function to delete an account
{
	bool found = false;
	account a;
	ifstream fin;
	ofstream fout;
	int temp_acc_no;
	cout<<"Enter Account Number which you want to delete: ";
	cin>>temp_acc_no;
	fin.open("bank.dat", ios::in | ios::binary);
	int flength;
	fin.seekg(0, ios::end);
	flength = fin.tellg();
	if(flength == 0)
	{
		cout<<"\nFile is Empty!!!!"<<endl;
		getch();
	}
	else
	{
		fout.open("tempfile.dat", ios::binary | ios::out);
		fin.seekg(0, ios::beg);
		while(fin.read((char*)&a, sizeof(account)))
		{
			if(temp_acc_no != a.return_acc_no())
			{
				fout.write((char*)&a, sizeof(account));
				
			}
			else 
			{
				a.show_account();
				found = true;
			}
		}
	fin.close();
	fout.close();
	if(found == true)
	{
		remove("bank.dat");
		rename("tempfile.dat", "bank.dat");
		cout<<"\n***************Account Deleted Successfully****************"<<endl;
		getch();
	}
	else
	{
		cout<<"\n************Account not found!!!***************"<<endl;
		getch();
	}
    }
}

void account_details()				// main function to display the details of all account holders
{
	system("cls");
	int file_length;
	account a;
	ifstream fin;
	fin.open("bank.dat", ios::in | ios::binary);
	fin.seekg(0, ios::end);
	file_length = fin.tellg();
	if(file_length == 0)
	{
		cout<<"\n*************File is Empty!!! No Any Account has been created!***************"<<endl;
	}
	else
	{
		cout<<"======================================================================================"<<endl;
		cout<<"A/C NO            Name                      A/C Type        Deposit Balance(Rs)"<<endl;
		fin.seekg(0, ios::beg);
		while(fin.read((char*)&a, sizeof(account)))
		{	
			a.display_account();	
		}
		cout<<"======================================================================================"<<endl;
	}
	fin.close();
	getch();
}
// End of declaration of main functions of admin panel

// declaration and definition of main functions of customer panel
void deposit_amount()
{
	bool found = false;
	account a; 
	fstream file;
	int temp_acc_no;
	cout<<"\nEnter Your A/C No: ";
	cin>>temp_acc_no;
	file.open("bank.dat", ios::in | ios::out | ios::binary);
	file.seekg(0, ios::beg);
	while(file.read((char*)&a, sizeof(account)))
	{
		if(temp_acc_no == a.return_acc_no())
		{
			a.show_account();
			found = true;
			int position;
			position = sizeof(account);
			file.seekp(-position, ios::cur);
			a.modify_deposit_amount();
			file.write((char*)&a, sizeof(account));
			cout<<"\n************Deposit Updated Successfully***************"<<endl;
			getch();
		}
	}
	if(found == false)
	{
		cout<<"\nAccount not found!!! Create an accont first"<<endl;
		getch();
	}
	file.close();
}

void withdraw_amount()
{
	account a; 
	bool found = false; 
	int acc_no;
	fstream file; 
	cout<<"\nEnter your A/C number: ";
	cin>>acc_no;
	file.open("bank.dat", ios::in | ios::out | ios::binary);
	file.seekg(0, ios::beg);
	while(file.read((char*)&a, sizeof(account)))
	{
		if(acc_no == a.return_acc_no())
		{
			a.show_account();
			found = true;
			a.modify_withdraw_amount();
			int position; 
			position = sizeof(account);
			file.seekp(-position, ios::cur);
			file.write((char*)&a, sizeof(account));
			getch();
			
		}
	}
	if(found == false)
	{
		cout<<"\nAccount not found!!! Create an accont first"<<endl;
		getch();
	}
	file.close();
}

void balance_query()
{
	bool found = false;
	account a; 
	ifstream fin;
	int acc_no;
	cout<<"\nEnter your A/C NO: ";
	cin>>acc_no;
	fin.open("bank.dat", ios::in | ios::binary);
	fin.seekg(0, ios::beg);
	while(fin.read((char*)&a, sizeof(account)))
	{
		if(acc_no == a.return_acc_no())
		{
			a.show_account();
			found = true;
		}
	}
	if(found == false)
	{
		cout<<"\nAccount not found!!! Create an accont first"<<endl;
	}
	fin.close();
	getch();
}


// End of declaration of main functions of customer panel

void intro()
{
    cout<<"\n\n\n\n\n\t\t\t///***********************************************************///\n";
    cout<<"\t\t\t\t   Welcome To The Banking Management System\n";
    cout<<"\t\t\t\t\t     Kamalpokhari,Kathmandu\n";
    cout<<"\t\t\t///***********************************************************///\n";
    cout<<"\n\n\n\t\t\t\t\t Press any key to continue..........";
    getch();
}
int main()
{
	int choice;
	intro();
	main_menu:
	while(1)
	{
		system("cls");
		cout<<"\n\n";
		cout<<"1. Customer Panel"<<endl;
		cout<<"2. Admin Panle"<<endl;
		cout<<"3. Exit"<<endl;
		cout<<"Select Your Option: ";
		cin>>choice;
		customer_menu:
		switch(choice)
		{
			case 1: 
				int customer_choice;
				while(1)
				{
					system("cls");
					cout<<"\n\n";
					cout<<"1. Deposit Amount"<<endl;
					cout<<"2. Withdraw Amount"<<endl;
					cout<<"3. Balance Query"<<endl;
					cout<<"4. Back To Main Menu"<<endl;
					cout<<"5. Exit"<<endl;
					cout<<"Select Options(1-5): ";
					cin>>customer_choice;
					switch(customer_choice)
					{
						case 1: 
							deposit_amount();
							break;
						case 2:
							withdraw_amount(); 
							break;
						case 3: 
							balance_query();
							break;
						case 4: 
							goto main_menu;
							break;
						case 5: 
							goto main_exit;
							break;
						default: 
							cout<<"Invalid Choice!!"<<endl;
							getch();
					}	
				}
				break;
			case 2: 
				char password[4], ch;
				int i; 
				cout<<"\nEnter your Password: "<<endl;
				for(i=0; i<4; i++)
				{
					ch = getch();
					ch = tolower(ch);
					password[i] = ch;
					cout<<"*";
				}
				password[i] = '\0';
				getch();
				if(strcmp(password, "park")==0)
				{
					int admin_choice;
					while(1)
					{
						system("cls");
						cout<<"1. Create Account"<<endl;
						cout<<"2. Modify Account"<<endl;
						cout<<"3. Delete Account"<<endl;
						cout<<"4. All Account Holder List"<<endl;
						cout<<"5. Back To Main Menu"<<endl;
						cout<<"6. Exit"<<endl;
						cout<<"Select Your Choice: ";
						cin>>admin_choice; 
						switch(admin_choice)
						{
							case 1: 
								create_account();
								break;
							case 2: 
								modify_account();
								break;
							case 3: 
								delete_account();
								break;
							case 4: 
								account_details();				
								break;
							case 5: 
								goto main_menu;
								break;
							case 6: 
								goto main_exit;
							default: 
								cout<<"Invalid choice!"<<endl;
								getch();
								break;
						}
					}
				}
				else
				{
					cout<<"\nIncorrect password."<<endl;
				}
				break;
			case 3: 
				main_exit:
				cout<<"\n*************Thanks For Your Visit***********"<<endl;
				exit(0);
			default: 
				cout<<"Invalid Choice!"<<endl;
				break;
		}
		getch();
	}
	return 0;	
}
