//#include<conio>
#include<stdio.h>
//#include<process>
#include<fstream>
#include<string>
#include<stdlib.h>
#include<iostream>
#include<iomanip>
#include <termios.h>
#include <unistd.h>

using namespace std;
/************************************************************************************************/
class product
{
public :	int pr_no;
			char name[60];
			float price,qty,dis;
public:		void get()
			{
				cout<<"\nEnter Product Number : ";
				cin>>pr_no;
				cout<<"\nEnter Name of Product : ";
				cin.ignore();
				cin>>name;
				cout<<"\nEnter Price : ";
				cin>>price;
				cout<<"\nEnter Discount :  ";
				cin>>dis;
			}
			void show_product()
			{
				cout<<"\nProduct Number : "<<pr_no;
				cout<<"\nName : ";
				puts(name);
				cout<<"\nPrice : "<<price;
				cout<<"\nDiscount : "<<dis;
			}
			int retpr_no()
			{
				return pr_no;
			}
			float retprice()
			{
				return price;
			}
			char* retname()
			{
				return name;
			}
			int retdis()
			{
				return dis;
			}
};


fstream f;
product pr;

void write_product()
{
	f.open("Shop.dat",ios::out|ios::app);
	pr.get();
	f.write((char*)&pr,sizeof(product));
	f.close();
	cout<<"\n\n\tProduct Added ";
}
/********************************************************************************************/
void modify_product()
{
	int no,found=0;
	system("clear");
	cout<<"\n\n\tEnter Product Number you want to edit : ";
	cin>>no;
	f.open("Shop.dat",ios::in|ios::out);
	while(f.read((char*)&pr,sizeof(product)) && found==0)
	{
		if(pr.retpr_no()==no)
		{
			pr.show_product();
			cout<<"\nEnter New Info. of Product : "<<endl;
			pr.get();
			int pos=-1*sizeof(pr);
			f.seekp(pos,ios::cur);
			f.write((char*)&pr,sizeof(product));
			cout<<"\n\n\t Record Updated";
			found=1;
		}
	}
	f.close();
	if(found==0)
	cout<<"\n\n Record Not Found ";
}

/******************************************************************************************/
void delete_product()
{
	int no;
	system("clear");
	cout<<"\n\nEnter Product Number you want to delete";
	cin>>no;
	f.open("Shop.dat",ios::in|ios::out);
	fstream f2;
	f2.open("Temp.dat",ios::out);
	f.seekg(0,ios::beg);
	while(f.read((char*)&pr,sizeof(product)))
	{
		if(pr.retpr_no()!=no)
		{
			f2.write((char*)&pr,sizeof(product));
		}
	}
	f2.close();
	f.close();
	remove("Shop.dat");
	rename("Temp.dat","Shop.dat");
	cout<<"\n\n\tRecord Deleted ..";
	getchar();
}
/******************************************************************************************************/
void menu()
{
	system("clear");
	f.open("Shop.dat",ios::in);
	if(!f)
	{
		cout<<"\n\n\tFile Not Found\n\n\n Go To Admin Menu to create File";
		exit(0);
	}
	cout<<"\n\n\t\tProduct List\n\n";
	cout<<"====================================================\n";
	cout<<"\n";
	cout<<left<<setw(12)<<setfill(' ')<<"Pr_No";
	cout<<left<<setw(30)<<setfill(' ')<<"Pr_Name";
	cout<<left<<setw(12)<<setfill(' ')<<"Price";
	cout<<"\n====================================================\n";
	while(f.read((char*)&pr,sizeof(product)))
	{
			cout<<"\n";
			cout<<left<<setw(12)<<setfill(' ')<<pr.retpr_no();
			cout<<left<<setw(30)<<setfill(' ')<<pr.retname();
			cout<<left<<setw(12)<<setfill(' ')<<pr.retprice();
	}
	f.close();
}

/*************************************************************************************************/

void place_order()
{
	int order_arr[50],quan[50],i=0;
	float amt,damt,total=0;
	char ch='Y';
	menu();
	do
	{
		cout<<"\n\nEnter Product Number : ";
		cin>>order_arr[i];
		cout<<"\nEnter Quantity : ";
		cin>>quan[i];
		i++;
		cout<<"\nAdd Another Product?(y/n)";
		cin>>ch;
	}while(ch=='y' ||ch=='Y');
	cout<<"\n\nOrder Placed";
	getchar();
	system("clear");
	cout<<"\n\n****************************************BILL****************************************************\n\n";
	cout<<left<<setw(12)<<setfill(' ')<<"Pr_No";
	cout<<left<<setw(30)<<setfill(' ')<<"Pr_Name";
	cout<<left<<setw(12)<<setfill(' ')<<"Quantity";
	cout<<left<<setw(12)<<setfill(' ')<<"Price";
	cout<<left<<setw(12)<<setfill(' ')<<"Amount";
	cout<<left<<setw(12)<<setfill(' ')<<"Discounted Amount\n\n";
	for(int x=0;x<=i;x++)
	{
		f.open("Shop.dat",ios::in);
		f.read((char*)&pr,sizeof(product));
		while(!f.eof())
		{
			if(pr.retpr_no()==order_arr[x])
		{
			cout<<"\n";
			amt=pr.retprice()*quan[x];
			damt=amt-(amt*pr.retdis()/100);
			cout<<left<<setw(12)<<setfill(' ')<<order_arr[x];
			cout<<left<<setw(30)<<setfill(' ')<<pr.retname();
			cout<<left<<setw(12)<<setfill(' ')<<quan[x];
			cout<<left<<setw(12)<<setfill(' ')<<pr.retprice();
			cout<<left<<setw(12)<<setfill(' ')<<amt;
			cout<<left<<setw(12)<<setfill(' ')<<damt;
			total+=damt;
		}
		f.read((char*)&pr,sizeof(product));
	}
	f.close();
}
	cout<<"\n\n\n\t\t\t\t\t\t\t\t\t\tTotal = "<<total;
	getchar();
}
/************************************************************************************************/
void admin_menu()
{
	system("clear");
	char ch2;
	cout<<"\n\n\n\tADMIN MENU";
	cout<<"\n\n\t1.Add Product";
	cout<<"\n\n\t2.Edit Product";
	cout<<"\n\n\t3.Delete Product";
	cout<<"\n\n\t4.Main Menu";
	cout<<"\n\n\tEnter Choice : ";
	cin>>ch2;
	switch(ch2)
	{
		case '1' :  system("clear");
					write_product();
					break;
		case '2' :  modify_product();
					break;
		case '3' :  delete_product();
					break;
		case '4': 	break;
		default :	admin_menu();
}
}

int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}
int main()
{
	string pass;
	char ch;
	do
	{
		system("clear");
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t1.Customer";
		cout<<"\n\n\t2.Admin";
		cout<<"\n\n\t3.Exit";
		cout<<"\n\n\tEnter Choice : ";
		cin>>ch;
		switch(ch)
		{
			case '1' :  system("clear");
						place_order();
						break;
			case '2' :
				        cout<<"\n ENTER PASSWORD:";
			            cin>>pass;
			            if(pass=="****")
			            {
				        admin_menu();
			            }else
			            	cout<<"\n !!!INVALID PASSWORD!!!";
			            break;
			case '3' :  exit(0);
			default  :	cout<<"\a";
		}
	}while(ch!='3');
return 0;
}
