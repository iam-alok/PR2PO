#include <iostream> 
#include<conio.h> 
#include<string> 
#include<stdlib.h>
#include<fstream>
#include<ctime>
#include<windows.h> 

using namespace std; 
 //function definition for cursor definition and position in the concole window
 
 void gotoxy(int x,int y){
 	COORD coord; 
 	coord.X=x; 
 	coord.Y=y;
 	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord); 	
 } 
 
 //price list of items 
 //each array index value is used as an identifier for item codes 
 float price_list[20]={865,2.25,44,10,20,7710,33.33,48.97,8,0.5,0.01,88,999,25000,87,4,22,200,20,150};
 
 class po; //forward declaration for using friend function 
 //class definitio
 class requisition
 {
 	//defining data members 
 	static int req_no; 
 	int item_code; 
 	int qty; 
 	string delivery_date; 
 	
 	public:
 		//class function declaration 
 		void get_data();
 		void display(); 
 		friend void generate(requisition ,po ); //friend function 
 		
 }; 
 
 //function for receiving requisition details 
 void requisition::get_data()
{
	system("cls"); 
	req_no++; 
	cout<<"Product Item Code: "; 
	cin>>item_code; 
	cout<<"Quantity: "; 
	cin>>qty; 
	cout<<"Delivery Date: "; 
	cin.clear(); 
	cin.ignore(1000,'\n'); 
	getline(cin,delivery_date);
 }  
 //defining static data member 
 int requisition::req_no;
 
 //function for displaying requistion details 
 void requisition::display()
 {
 	system("cls"); 
 	cout<<"Requisition Number: "<<req_no; 
 	cout<<"\nProduct Item Code: "<<item_code; 
 	cout<<"\nQuantity: "<<qty; 
 	cout<<"\nDelivery Date: "<<delivery_date; 
 	getch();
 } 
 
 class po
 {
 	static int po_no; 
 	public:
 		//constructor  used for static variable po_no
 		po(){
 			po_no++;
		 } 
		 
		 friend void generate(requisition ,po );
		 
 }; 
 //defining satic member 
 int po::po_no; 
 //defining friend function generate 
 void generate(requisition r,po p){
 	ofstream fout; 
 	//retreiving system date and time
    time_t current =time(0); 
    char*dt =ctime(&current); 
    //opening the current_po.txt file in which po possible deatails are stored 
    fout.open("Current_PO.txt");  
    //generating the po and storing it in the current po box file in a formatted manner 
    fout<<"\t\t\t Purchase Order#: "<<p.po_no<<"\n"; 
    fout<<"\t\t\t___________________\n\n"; 
    fout<<"Requisition#: "<<r.req_no<<"\t\t\t\tIssue Date: "<<dt<<"\n\n"; 
    if(r.item_code >=1 && r.item_code <=10)
    fout<<"Supplier: "<<"SKS Inc\n\n"; 
    else if(r.item_code >=11 && r.item_code <=20)
    fout<<"Supplier: "<<"KC Spare Parts Ltd.\n\n";  
    else 
    fout<<"Supplier: "<<"Other(_________________________)\n\n"; 
    fout<<"Delivery Date: "<<r.delivery_date<<"\n\n";
    fout<<"-----------------------------------------------------------------------------------------------------\n";
    fout<<"                                               **Line Items**                                        \n";
    fout<<"-----------------------------------------------------------------------------------------------------\n";
    fout<<"Item Code \t\tQuantity\t\tPrice\t\t\tTotal\n";; 
    fout<<"__________\t\t________\t\t_____\t\t\t_____\n\n"; 
    fout<<" "<<r.item_code<<"\t\t\t "<<r.qty<<"\t\t\t";
    if(r.item_code>=1 && r.item_code<=20)
    fout<<" "<<price_list[r.item_code-1]<<"\t\t\t "<<price_list[r.item_code-1]*r.qty<<"\n\n\n"; 
    else 
    fout<<"---\t\t\t___\n\n\n"; 
    ifstream fin; 
    char line[80]; 
    //opening the terms.txt file from where standars items terms and conditions are copied intoo the po 
    fin.open("terms.txt"); 
    while(fin){
    	fin.getline(line,80); 
    	fout<<line<<"\n"; 
	} 
	fin.close();
  } 
  //main function 
  int main(){
  	requisition r; 
  	char flag='f'; 
  	char ch; 
  	//Dispalying a menu to accept user commands  

  	while(1){
  		system("cls"); 
  		gotoxy(35,8); 
  		cout<<" PR2PO "; 
  		gotoxy(35,9); 
  		cout<<"_______"; 
  		gotoxy(22,12); 
  		cout<<" 1- Create new Requisition"; 
  		gotoxy(22,13); 
  		cout<<" 2- Display Requisition"; 
  		gotoxy(22,14); 
  		cout<<" 3- Generate PO"; 
		gotoxy(22,15);
		cout<<" 4- Exit"; 
		gotoxy(22,18); 
		cout<<"Select an option by typing the numeric code: "; 
		ch=getch(); 
		switch(ch){
			case('1'): 
			{
				r.get_data(); 
				flag='t'; 
				break; 
			} 
			case('2'):
				{
					if(flag=='f'){
						gotoxy(22,20);
						cout<<"Requisition details not yet entered ! Press any key to continue...."; 
						getch();
					} 
					else
					r.display(); 
					break;
				} 
			case('3'):
				{
					po p; 
					generate(r,p); 
					gotoxy(22,20);
					cout<<"PR has been converted into a  PO. \n\t\t    You can view the Current_po.txt file to generated PO \n\t\t    Take its print out";
					getch(); 
					break; 
					
				} 
			case('4'):
				{
					exit(1); 
					break;
				} 
			default: 
			{
				gotoxy(22,20); 
				cout<<"Invalid choice! Press any key to Continue...."; 
				getch();
			}
		    }		
	  } return 0;
  }
 
 
 
 
 
 
 
 
 
 
 
 
 
 
