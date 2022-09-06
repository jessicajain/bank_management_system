#include<bits/stdc++.h>
using namespace std;

class account
{
    int acc_No;
	char name[50];
	int balance;
	char type;
    double phn;
    public:
	    void add_account() // to create or add new accounts 
        {   
            cout << endl <<"Enter the account number: ";
            cin>>acc_No;
            cout << endl << endl << "Enter the name of the account holder: ";
			cin.ignore();
            cin.getline(name,50);
            cout << endl << endl << "Enter the phone number: ";
            cin >> phn;
            cout<<endl << endl <<"Enter the type of account you wish to create: \n S for Savings \n C for current: ";
            cin>>type;
            type=toupper(type);
            if(type=='S')
            {
                cout << endl << endl <<"Enter the amount you wish to deposit: " << endl;
                cout <<"Minimum amount 1000 ";
                cin >> balance;
                if(balance >= 1000)
                {   
                    cout <<endl << endl<< "\t---Account Created---" << endl;
                    display_account();
                }
                else
                   {
                       cout << "Minimum amount is 1000. \n Please enter amount >= 1000" << endl;
                       cin >> balance ;
                       cout <<endl << endl << "\t---Account Created---" << endl;
                       display_account();
                   } 
           } 
            else if(type=='C')   
            {
                cout << endl << endl <<"Enter the amount you wish to deposit: " << endl;
                cout <<"Minimum amount 3000 ";
                cin >> balance;
                if(balance >= 3000)
                    {
                        cout <<endl << endl << "\t---Account Created---" << endl;
                        display_account();
                    }
                else
                   {
                       cout << "Minimum amount is 3000. \n Please enter amount >= 3000" << endl;
                       cin >> balance ;
                       cout <<endl << endl << "\t---Account Created---" << endl;
                       display_account();
                   } 
            }
            else
            {
                cout << "Invalid option" << endl << endl ;
            }
        }
        void display_account() // to display the details of the account holder
        {
            cout<<"---------------------------------------------------------------------------\n";
	        cout<<"Account no.         Name           Phone No         Type         Balance\n";
            cout<<"---------------------------------------------------------------------------\n";
            cout<<acc_No<<setw(20);
            cout<<name<<setw(17);
            cout<<phn<<setw(14);
            cout<<type<<setw(17);
            cout<<balance<<endl;
        }
        void acc_modify() // to update or modify the details 
        {
            int choice;
            do
            {
                cout<<"What details do you wish to modify? "<<endl;
                cout<<"\t1. Name" << endl << "\t2. Type" << endl << "\t3. Phone Number" << endl << "\t4. Exit" << endl;
                cin >> choice;
                switch(choice)
                {
                    case 1:
                        cout<<"Enter the new name: ";
                        cin.ignore();
	                    cin.getline(name,50);
                        break;
                    case 2:
                        cout<<"Enter the type: ";
                        cin >> type;
                        type=toupper(type);
                        break;
                    case 3:
                        cout<<"Enter the new phone number: ";
                        cin >> phn;
                        break;
                    default:
                        cout << "Invalid choice";
                        break;
                }
            } while(choice!=4);
        }
        void display_acc() // to display the details of the account holder
        {
            cout<<acc_No<<setw(20);
            cout<<name<<setw(17);
            cout<<phn<<setw(14);
            cout<<type<<setw(17);
            cout<<balance<<endl;
        }
        int account_number() // to return the acc number 
        {
            return acc_No;
        }
        void deposit(int amount) // to add money to balance when amount is deposited 
        {
            balance+=amount;
        }
        void withdraw(int amount) // to subtract money from balance when amount is debited 
        {
            balance-=amount;
        }
        int return_balance()  // to return the cutter balance of an account
        {
            return balance;
        }
};

void put_account() // to add the details into a file 
{
    account obj;
	ofstream file;
	file.open("account_details.txt",ios::binary|ios::out|ios::app);
	obj.add_account();
	file.write(reinterpret_cast<char *> (&obj), sizeof(account));
	file.close();
}
void modify_account(int no) // to modify the deatils in the file 
{
    bool check=false;
	account obj;
	fstream file;
    file.open("account_details.txt",ios::binary|ios::in|ios::out);
	while(!file.eof() and check==false)
	{
		file.read(reinterpret_cast<char *> (&obj), sizeof(account));
		if(obj.account_number()==no)
		{
			obj.display_account();
			obj.acc_modify();
			int pos=(-1)*static_cast<int>(sizeof(account));
			file.seekp(pos,ios::cur); 
		    file.write(reinterpret_cast<char *> (&obj), sizeof(account));
		    cout<< endl <<"\t---Account details updated---" << endl;
            obj.display_account();
		    check=true;
		  }
	}
	file.close();
	if(check==false)
		cout<<"\t---Account does not exist---" << endl;
}
void close_account(int no)// to deleted records of the file 
{
    account obj;
	ifstream i_file;
	ofstream o_file;
	i_file.open("account_details.txt",ios::binary);
	o_file.open("temp_file.txt",ios::binary);
	i_file.seekg(0,ios::beg);
	while(i_file.read(reinterpret_cast<char *> (&obj), sizeof(account)))
	{
		if(obj.account_number()!=no)
		{
			o_file.write(reinterpret_cast<char *> (&obj), sizeof(account));
		}
	}
    i_file.close();
	o_file.close();
	remove("account_details.txt");
	rename("temp_file.txt","account_details.txt");
	cout<<"\t---Record Deleted---"<< endl;
}


void deposit_amount(int no) // modifiy details of file
{
	int amt;
	bool check=false;
	account obj;
	fstream file;
    file.open("account_details.txt", ios::binary|ios::in|ios::out);
	while(!file.eof() && check==false)
	{
		file.read(reinterpret_cast<char *> (&obj), sizeof(account));
		if(obj.account_number()==no)
		{
			obj.display_account();
			cout<<"TO DEPOSITSS AMOUNT" << endl;
			cout<<"Enter The amount to be deposited: ";
			cin>>amt;
			obj.deposit(amt);
			int pos=(-1)*static_cast<int>(sizeof(obj));
			file.seekp(pos,ios::cur);
			file.write(reinterpret_cast<char *> (&obj), sizeof(account));
			cout<< endl <<"\t---Record Updated---" << endl;
			obj.display_account();
            check=true;
	       }
         }
    file.close();
	if(check==false)
		cout<< endl <<"\t---Record Not Found---" << endl;
}
void withdraw_amount(int no) // modify details of the file 
{
	int amt;
	bool check=false;
	account obj;
	fstream file;
    file.open("account_details.txt", ios::binary|ios::in|ios::out);
	while(!file.eof() && check==false)
	{
		file.read(reinterpret_cast<char *> (&obj), sizeof(account));
		if(obj.account_number()==no)
		{
			obj.display_account();
			cout<<"TO WITHDRAW AMOUNT" << endl;
			cout<<"Enter The amount to be withdraw: ";
			cin>>amt;
			int bal=obj.return_balance()-amt;
			if(bal<0)
				cout<< endl <<"Insufficience balance" << endl;
    		else
				obj.withdraw(amt);
		    int pos=(-1)*static_cast<int>(sizeof(obj));
		    file.seekp(pos,ios::cur);
		    file.write(reinterpret_cast<char *> (&obj), sizeof(account));
		    cout<<"\t---Record Updated---" << endl;
            obj.display_account();
			check=true;
	       }
         }
    file.close();
	if(check==false)
	cout<<"\t---Record Not Found---" << endl;
}
void display_Oneacc(int no) // display the details of a particulat account 
{
	account obj;
	bool check=false;
	ifstream file;
	file.open("account_details.txt",ios::binary);
	cout<<"\t---BALANCE DETAILS---"<<endl;
    while(file.read(reinterpret_cast<char *> (&obj), sizeof(account)))
	{
		if(obj.account_number()==no)
		{
			obj.display_account();
			check=true;
		}
	}
    file.close();
	if(check==false)
		cout<<"---\tAccount number does not exist----"<< endl;
}
void display_accdet() // display all the contents of the file 
{
	account obj;
	ifstream file;
	file.open("account_details.txt",ios::binary);
    cout<<"---------------------------------------------------------------------------\n";
    cout<<"Account no.         Name           Phone No         Type         Balance\n";
    cout<<"---------------------------------------------------------------------------\n";
	while(file.read(reinterpret_cast<char *> (&obj), sizeof(account)))
	{
		obj.display_acc();
	}
	file.close();
}
void last_entry() // to display the last line of the file 
{
    account obj;
    int count=0;
	ifstream file;
	file.open("account_details.txt",ios::binary);
	while(file.read(reinterpret_cast<char *> (&obj), sizeof(account)))
	{
		count = obj.account_number();
	}
    file.close();
    file.open("account_details.txt",ios::binary);
    while(file.read(reinterpret_cast<char *> (&obj), sizeof(account)))
	{
		if(obj.account_number()==count)
		{
			obj.display_account();
		}
	}
	file.close();
	
}
void check_account(int no) // to checl if an account exists 
{
    account obj;
	bool check=false;
	ifstream file;
	file.open("account_details.txt",ios::binary);
    while(file.read(reinterpret_cast<char *> (&obj), sizeof(account)))
	{
		if(obj.account_number()==no)
		{
            cout<<"\t---Account Exists---" << endl;
			obj.display_account();
			check=true;
		}
	}
    file.close();
	if(check==false)
		cout<<"---\tAccount does not exist----"<< endl;
}
int main()
{
    int option;
    int accNo;
    account obj;
    do
    {
        system("CLS");
        cout << "=========================================" << endl << endl;
        cout << " \t Welcome to xyz Bank" << endl << endl;
        cout << "=========================================" << endl << endl;
        cout<<"\t \t MAIN MENU"<< endl << endl;
        cout<<"\t 1. ADD NEW ACCOUNT"<< endl<< endl;
        cout<<"\t 2. MODIFY AN ACCOUNT"<< endl<< endl;
        cout<<"\t 3. CLOSE AN ACCOUNT"<< endl<< endl;
        cout<<"\t 4. DEPOSIT AMOUNT"<< endl<< endl;
        cout<<"\t 5. WITHDRAW AMOUNT"<< endl<< endl;
        cout<<"\t 6. BALANCE ENQUIRY"<< endl<< endl;
        cout<<"\t 7. LIST OF ALL ACCOUNT HOLDER"<< endl<< endl;
        cout<<"\t 8. LAST ENTRY"<< endl << endl;
        cout<<"\t 9. CHECK IF AN ACCOUNT EXISTS"<< endl << endl;
        cout<<"\t 10. EXIT"<< endl << endl;
        cout<<"\tSelect Your Option <1-10>";
        cin >> option;
        system("cls");
        switch(option)
        {
            case 1:
                put_account();
                break;
            case 2:
                cout<<"Enter the Account number you wish to update/modify: ";
                cin >> accNo;
                modify_account(accNo);
                break;
            case 3:
                cout<<"Enter the Account number you wish to close/delete: ";
                cin >> accNo;
                close_account(accNo);
                break;
            case 4:
                cout<<"Enter the Account number to deposit: ";
                cin >> accNo;
                deposit_amount(accNo);
                break;
            case 5:
                cout<<"Enter the Account number to withdraw money: ";
                cin >> accNo;
                withdraw_amount(accNo);
                break;
            case 6:
                cout<<"Enter the Account Number: ";
                cin >> accNo;
                display_Oneacc(accNo);
                break;
            case 7:
                cout<<"\tList of all Accounts "<< endl;
                display_accdet();
                break;
            case 8:
                last_entry();
                break;
            case 9:
                cout<<"Enter the account number: " << endl;
                cin >> accNo;
                check_account(accNo);
                break;
            case 10:
                cout<<"\tThank you for using bank managemnet system" << endl;
                break;
            default:
                cout << "Invalid option";
        }
        cin.ignore();
        cin.get();
    } while (option!=10);
    return 0;
}
