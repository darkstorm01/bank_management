#include<bits/stdc++.h>
#define clear() printf("\033[H\033[J")
using namespace std;

typedef struct val{
	string str="";
	long int accno;
}val;
class acc{
	private:
		string name;
		long int acc_no;
		long int mobile_no;
		int bal;
	public:
		void show_details();
		void create_account();
		val getdetails();
};

void acc::create_account(){
	cout<<"\nEnter the 10-digit account number: ";
	cin>>acc_no;
	while(acc_no<1000000000 || acc_no>9999999999){
		cout<<"\nRe-enter a valid account Number: ";
		cin>>acc_no;
	}
	cin.ignore();
	cout<<"\nEnter the name: ";
	getline(cin,name);
	cout<<"\nEnter mobile number: ";
	cin>>mobile_no;
	while(mobile_no<1000000000 || mobile_no>9999999999){
		cout<<"\nRe-enter a valid mobile Number: ";
		cin>>mobile_no;
	}
	cout<<"\nEnter the balance: ";
	cin>>bal;
}

void acc::show_details(){
	cout<<"Name: "<<name<<"\n";
	cout<<"Account number: "<<acc_no<<"\n";
	cout<<"Mobile number: "<<mobile_no<<"\n";
	cout<<"Balance: "<<bal<<"\n";
}

val acc::getdetails(){
	val res;
	res.str=res.str+to_string(acc_no)+"  "+name+"  "+to_string(mobile_no)+"  "+to_string(bal)+"\n";
	res.accno=acc_no;
	return res;
}

int search(long int key){
	ifstream file1;
	file1.open("a.dat");
	string a;
	while(getline(file1,a))
	{
		long int account_no=0;
		for(int i=0;a[i]!=' ';i++)
			account_no=account_no*10+(int)a[i]-48;
		if(key==account_no){
			int bal=0,i;
			for(i=a.size()-1;a[i]!=' ';i--);
			for(int k=i+1;k<a.size();k++)
				bal=bal*10+(int)a[k]-48;
			return bal;
		}
	}
	return -1;
}

void create_account(){
	acc data;
	ofstream file;
	file.open("a.dat",ios::app);
	data.create_account();
	val s=data.getdetails();
	if(search(s.accno)==-1){
		file<<s.str;
		cout<<"Account created successfully!";
	}
	else
		cout<<"An account already exists with this account number!\n";
	file.close();
}

void balance_enquiry(){
	long int num;
	cout<<"Enter the account number :";
	cin>>num;
	int k=search(num);
	if(k>=0)
		cout<<"Balance:"<<k<<"\n";
	else
		cout<<"Account does not exist\n";
}

void update(long int acc_no,int bal){
	ifstream file1;
	file1.open("a.dat");
	ofstream tempfile;
	tempfile.open("temp_file.dat",ios::app);
	string a;
	while(getline(file1,a))
	{
		long int account_no=0;
		for(int i=0;a[i]!=' ';i++)
			account_no=account_no*10+(int)a[i]-48;
		if(acc_no==account_no){
			int n=a.length();
			char arr[n+1];
			strcpy(arr,a.c_str());
			string new_entry="";
			char *temp;
			const char delim[2]={' ',' '};
			temp=strtok(arr,delim);
			int count=1;
			while(count<4)
			{	
				string temp1(temp);
				new_entry+=temp1+"  ";
				temp=strtok(NULL,delim);
				count++;
			}
			new_entry+=to_string(bal)+"\n";
			tempfile<<new_entry;
		}
		else{
			//push it into temp_file
			a=a+"\n";
			tempfile<<a;
		}
	}
	file1.close();
	tempfile.close();
	remove("a.dat");
	rename("temp_file.dat","a.dat");
}

void withdraw(){
	long int acc_no;
	int w_amnt;
	cout<<"Enter the account number :";
	cin>>acc_no;
	cout<<"Enter amount to withdraw :";
	cin>>w_amnt;
	while(w_amnt<0){
		cout<<"Enter valid amount :";
		cin>>w_amnt;
	}
	int bal=search(acc_no);
	if(bal==-1)
		cout<<"Account does not exist\n";
	else if(w_amnt>bal)
		cout<<"Insufficient balance\n";
	else{
		bal-=w_amnt;
		update(acc_no,bal);
		cout<<"Do you want to see the current balance(Y/N):";
		char a;
		cin>>a;
		if(a=='Y' || a=='y')
		cout<<"Current balance :"<<bal<<"\n";
	}	
}

void deposit(){
	long int acc_no;
	int d_amnt;
	cout<<"Enter the account number :";
	cin>>acc_no;
	cout<<"Enter amount to deposit :";
	cin>>d_amnt;
	while(d_amnt<0){
		cout<<"Enter valid amount :";
		cin>>d_amnt;
	}
	int bal=search(acc_no);
	if(bal==-1)
	cout<<"Account does not exist\n";
	else{
		bal+=d_amnt;
		update(acc_no,bal);
		cout<<"Do you want to see the current balance(Y/N):";
		char a;
		cin>>a;
		if(a=='Y' || a=='y')
		cout<<"Current balance :"<<bal<<"\n";
	}	
}

int main(){
	char a;
	clear();
	while(1)
	{
		cout<<"\n\n===========**===========\n";
		cout<<" BANK MANAGEMENT SYSTEM\n";
		cout<<"===========**===========\n";
		cout<<"1:Create Account\n";
		cout<<"2:Balance enquiry\n";
		cout<<"3:Withdraw\n";
		cout<<"4:Deposit\n";
		cout<<"5:Exit\n";
		cout<<"Enter Your choice: ";
		hello:
		cin>>a;
		switch(a){
			case '1': 	create_account();
						break;
			case '2': 	balance_enquiry();
						break;
			case '3':	withdraw();
						break;
			case '4':	deposit();
						break;
			case '5':	cout<<"Thank You!😇️\n";
						exit(0);
						break;
			default: 	cout<<"Enter the appropriate choice :";
					 	goto hello;
					 	break;
		}
	}
	return 0;
}
