#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cmath>
#include <cctype>
#include <iomanip>
#include <Windows.h>
#include <string>
#include <time.h>
using namespace std;
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
SYSTEMTIME systemTime;


//function declaration
string upper(string);
void Main_Menu(string);
void CinemaManagement(int);
void AdministratorMenu(int);
//Cinema_Hall function
void CinemaHallManagement(int);
void ReadCinemaHallRecord(int&);
void CinemaSeatPrinting(int,int);
void HallSeatPrinting(int, int, int);
bool AddCinemaHall(bool);
void ModifyCinemaHall(int&);
void DeleteCinemaHall(int&);
void LoadCinemaHallRecord(int&);
void AddCinemaSeat(int&);
void DeleteCinemaSeat(int&);
void ConfirmAddCinemaSeat(int, int, int);
//movie function
void MovieManagement(int);
void AddMovie(int&);
void ReadMovieRecord(int&);
void LoadMovieRecord(int&);
void ModifyMovie(int&);
void DeleteMovie(int&);
void MoviePrinting(int&,int);
bool MovieStartDetection(string);
void MovieEndDetection(string,int,double,int&,int&,int);
void MovieIntoStruct(string, string, string, string, double, int,int&);
//employee function
void EmployeeManagement(int);
void ReadEmployeeRecord(int&);
void LoadEmployeeRecord(int&);
void AddEmployee(int&);
void DeleteEmployee(int&);
void ModifyEmployee(int&);
bool EmployeeID(string,int&);
//Movie details
void MovieDetails(int);
//Purchase now
void PurchaseNow(int);
void BookMovie(int);
void NumberTicket(int, int&, int&, int row[], int column[]);
void MemberChecking(string&, int&);
void TimeChecking(int, int, int, int, int, int,int&);
void DateRecord(int, int, int, int, int, int,int&);
void BookSeatPrinting(int, int, int);
//refresh the cinema hall
void CinemaRefresh(int);

void OpenMemberDetails(int& nomember);
void ReadTextRecord(int);

void OpenMemberDetails(int& nomember);

//structure declaration
struct mapping_seats
{//cinema hall	//a set of column and row = 1 data
	int hall, data, row[70], column[70];
}unavailable[50];
struct MemberDetails
{
	string Details_user, Details_name, Details_password, Details_join, Details_phone, Details_email, Details_status, Details_point;
}Member[100];
struct PurchaseHistory
{
	string Purchase_user, Purchase_name, Purchase_movie[5], Purchase_date[5], Purchase_pax[5], Purchase_food[5];
}Purchase[100];
struct PurchasedSeatType
{
	int data,purchased_row[50],purchased_column[50];
};
struct CinemaHallSeatType
{
	int data,row[70],column[70];
};
struct movie
{
	string movie_id,movie_name,description,movie_time;
	double movie_length;
	int movie_hall;
	PurchasedSeatType seats;
	CinemaHallSeatType backup;
	
}movie[100];
struct employee {
	string id,name,department,position;
	int password;
}employee[100];
string department[5] = { "INFORMATION TECHNOLOGY","HUMAN RESOURCES","FINANCE","MARKETING","BUSINESS" };
string text[40][7];
//Main Menu
int main()
{
	system("chcp 65001");
	bool decision = true;
	string selection;
	do{
		system("cls");
		Main_Menu("MAIN");
		cout << "\t\t\tPlease input your selection >>> ";
		getline(cin,selection);
		if (selection == "1")//Movie details
			MovieDetails(1);
		else if (selection == "2")//f&b
			cout << "HELLO" << endl;
		else if (selection == "3")//purchase now
			PurchaseNow(3);
		else if (selection == "4")//membership details
			cout << "hey" << endl;//MembershipDetails();
		else if(selection=="5")
			AdministratorMenu(5);
		else if(selection=="7")//exit
			decision = false;
		else
			cout << "\t\t\tInvalid input found" << endl;
		cin.clear();
	} while (decision);


	system("pause");
	return 0;
}
//change string to uppercase
string upper(string uppercase)
{
	for (int i = 0; i < uppercase.size(); i++)
		uppercase[i] = toupper(uppercase[i]);
	return uppercase;
}
//Administrator Menu (havent implement employee function)
void AdministratorMenu(int option)
{
	bool decision = true, access = true;
	do {
		cin.clear();
		system("cls");
		ReadTextRecord(0);
		cout << "\n\n" << endl;
		for (int i = 0; i < 7; i++)
		{
			cout << "\t\t\t\t\t\t\t\t" << text[14][i] << endl;
		}
		cout << "\n\n\t\t\t" << string(150, char(95)) << endl;
		cout << "\n\t\t\t\tDear Admin, kindly key in your Admin ID and password" << endl;
		cout << "\n\t\t\t" << string(150, char(95)) << endl;
		string id,pass_word;
		int record = 0,password=0, found = 0,number=0;
		ReadEmployeeRecord(record);
		cout << "\n\n\t\t\t\tid=ew001 and password=12345 for lecturer used only!!" << endl;
		cout << "\n\t\t\t\t\tADMIN ID <E>xit >>>";
		getline(cin, id);
		id = upper(id);
		if (id == "E")
		{
			decision = false;
			break;
		}
		cout << "\t\t\t\t\tPassword >>>";
		getline(cin, pass_word);
		for (int i = 0; i < pass_word.size(); i++)	//ensure pass_word only in numeric numbers
		{
			if (isdigit(pass_word[i]))
				number++;
		}
		if (pass_word.size() == number)			//comparing
			password = stoi(pass_word);			//string to integer
		if (id.length() == 5)
		{
			for (int i = 0; i < record; i++)	//checking correct password
			{
				if (password == employee[i].password && id == employee[i].id)
				{
					found++;
				}
			}
		}
		if (found == 0 || id.length() != 5)	
		{
			cout << "\t\t\tPlease reinput your id and password " << endl;
			Sleep(1000);
		}
		else if (found == 1)
			access = false;
	} while (access);
	while(decision)
	{
		system("cls");
		ReadTextRecord(0);
		for (int i = 0; i < 7; i++)
		{
			cout << "\t\t\t" << text[1][i] << endl;
		}
		string selection;
		cout << "\n\n\t\t\t" << string(150, char(95)) << endl;
		cout << "\n\t\t\t<1> Cinema Refreshing" << endl;
		cout << "\t\t\t<2> Cinema management" << endl;
		cout << "\t\t\t<3> Food & Beverages management" << endl;
		cout << "\t\t\t<4> Membership Management" << endl;
		cout << "\t\t\t<5> Employee management" << endl;
		cout << "\t\t\t<6> Exit " << endl;
		cout << "\t\t\t" << string(150, char(95)) << endl;
		cout << "\t\t\tPlease input your selection >>> ";
		getline(cin, selection);
		if (selection == "1")
			CinemaRefresh(1);
		if (selection == "2")//Cinema management
			CinemaManagement(2);
		if (selection == "3")//F&B management
			cout << "Hello";
		if (selection == "4")//Membership managements
			cout << "hello" << endl;
		if (selection == "5")//Employee management
			EmployeeManagement(5);
		if (selection == "6")
			decision = false;
		else//reinput
			cout << "\t\t\tInvalid input found" << endl;
	} 
}
//Cinema Management
void CinemaManagement(int option)
{
	string selection;
	bool decision = true;
	do{	
		cin.clear();
		system("cls");
		int notext = 0;
		ReadTextRecord(notext);
		for (int i = 0; i < 7; i++)
		{
			cout <<"\t\t\t"<< text[3][i] << endl;
		}
		cout << "\n\n\n\t\t\t<1> Movies management " << endl;
		cout << "\t\t\t<2> Cinema Hall management " << endl;
		cout << "\t\t\t<3> Exit " << endl;
		cout << "\t\t\tPlease input your selection >>> ";
		getline(cin, selection);
		if(selection=="1")//Movie management
			MovieManagement(1);
		if(selection=="2")//Cinema Hall Modification
			CinemaHallManagement(2);
		if(selection=="3")//exit
			decision = false;
		else//reinput
			cout << "\t\t\tInvalid input found" << endl;
	} while (decision);
}
//Cinema Hall Page
void CinemaHallManagement(int option)
{
	string selection;
	bool decision = true;
	do
	{
		system("cls");
		int record = 0;
		bool result = false;
		for (int i = 0; i < 7; i++)
		{
			cout << "\t\t\t\t\t\t\t\t" << text[5][i] << endl;
		}
		ReadCinemaHallRecord(record);
		cout << "\n\n\t\t\t" << string(150, char(95)) << endl;
		for (int w = 0; w < record; w++)
		{
			cout << "\n\n\t\t\t\t HALL " << unavailable[w].hall << "\n\n";
			CinemaSeatPrinting(w,99);
		}
		cin.clear();
		cout << "\t\t\t" << string(150, char(95)) << endl;
		cout << "\t\t\t<1> Add Cinema Hall" << endl;
		cout << "\t\t\t<2> Modify Cinema Hall space" << endl;
		cout << "\t\t\t<3> Delete Cinema Hall" << endl;
		cout << "\t\t\t<4> Exit" << endl;
		cout << "\t\t\t" << string(150, char(95)) << endl;
		cout << "\t\t\tInput your selection >>> ";
		getline(cin, selection);
		//Add cinema Hall
		if (selection == "1")
		{
			result = AddCinemaHall(result);
			if (result)
			{
				record++;
				unavailable[record - 1].hall = record;
				unavailable[record - 1].data = 0;
				unavailable[record - 1].row[0] = 0;
				unavailable[record - 1].column[0] = 0;
				LoadCinemaHallRecord(record);
			}
		}
		else if(selection=="2")//Modify Cinema Seat
			ModifyCinemaHall(record);
		else if(selection=="3")//Delete Cinema Hall
			DeleteCinemaHall(record);
		else if(selection=="4")//exit
			decision = false;
		else//reinput
			cout << "\t\t\tInvalid input detected." << endl;
	} while (decision);
}
void ReadCinemaHallRecord(int& record)
{
	int i = 0;
	ifstream infile;
	infile.open("seatcontrol.txt");
	if (infile.fail())
	{
		cout << "unable to open the file";
	}
	else
	{
		while (!infile.eof())
		{
			infile >> unavailable[i].hall;
			infile >> unavailable[i].data;
			infile.ignore();
			if (unavailable[i].data > 0)
			{
				for (int j = 0; j < unavailable[i].data; j++)
					infile >> unavailable[i].row[j];
				for (int j = 0; j < unavailable[i].data; j++)
					infile >> unavailable[i].column[j];
			}
			else
			{
				infile >> unavailable[i].row[0];
				infile >> unavailable[i].column[0];
			}
			
			infile.ignore();
			i++;
			record++;
		}
	}
	infile.close();
}
void LoadCinemaHallRecord(int& record)
{
	ofstream outfile;
	outfile.open("seatcontrol.txt");
	for (int i = 0; i < record; i++)
	{
		outfile << unavailable[i].hall << endl;
		outfile << unavailable[i].data << endl;
		if (unavailable[i].data > 0)
		{
			for (int j = 0; j < unavailable[i].data; j++)
			{
				if (j > 0)
					outfile << " ";
				outfile << unavailable[i].row[j];
			}
			outfile << endl;
			for (int j = 0; j < unavailable[i].data; j++)
			{
				if (j > 0)
					outfile << " ";
				outfile << unavailable[i].column[j];
			}

		}
		else
		{
			outfile << unavailable[i].row[0] << endl;
			outfile << unavailable[i].column[0];
		}
		if (i != record - 1)
			outfile << endl;
	}
	outfile.close();
}
//print selected cinema seat mapping
void CinemaSeatPrinting(int w,int f)
{
	for (int i = 0; i < 10; i++)
	{
		cout << "\t\t\t\t\t";
		cout << i;
		if (i == 0)
		{
			for (int j = 1; j < 15; j++)
			{
				if (j == 2 || j == 12)
					cout << setw(2) << j << " ";
				else
					cout << setw(2) << j;
			}
			cout << endl;
		}
		else
		{
			for (int j = 1; j < 3; j++)
			{
				if (f == 99)
					HallSeatPrinting(w, i, j);
				else
					BookSeatPrinting(w, i, j);

			}
			cout << " ";
			for (int j = 3; j < 13; j++)
			{
				if (f == 99)
					HallSeatPrinting(w, i, j);
				else
					BookSeatPrinting(w, i, j);
			}
			cout << " ";
			for (int j = 13; j < 15; j++)
			{
				if (f == 99)
					HallSeatPrinting(w, i, j);
				else
					BookSeatPrinting(w, i, j);;
			}
			cout << endl;
		}

	}
}
//check availability of seat
void HallSeatPrinting(int w, int i, int j)
{
	int checking = 1;
	if (unavailable[w].data != 0)
	{
		for (int z = 0; z < unavailable[w].data; z++)
		{
			if (i == unavailable[w].row[z] && j == unavailable[w].column[z])
			{
				cout << setw(2) << "X";
				checking = 0;
			}
		}
	}
	if (checking)
		cout << setw(2) << "A";
}
//add cinema hall
bool AddCinemaHall(bool result) 
{
	cin.clear();
	string confirms;
	bool decision = true;
	do
	{
		cout << "Do you want to add a new cinema hall <Y>es or <N>o >>> ";
		getline(cin, confirms);
		confirms = upper(confirms);
		if (confirms == "Y" || confirms == "N")
			decision = false;

	} while (decision);
	if (confirms == "Y")
		return true;
	else
		return false;
}
void ModifyCinemaHall(int& record)
{
	string selection;
	bool decision = true;
	do {
		cout << "\t\t\t<1> Add Cinema Unavailable Seat" << endl;
		cout << "\t\t\t<2> Delete Cinema Unavailable Seat" << endl;
		cout << "\t\t\t<3> Exit" << endl;
		cout << "\t\t\tInput your selection >>> ";
		getline(cin, selection);
		if(selection=="1")//	Add
			AddCinemaSeat(record);
		else if(selection=="4")//Delete
			DeleteCinemaSeat(record);
		else if(selection=="3")//Exit
			decision = false;
		else//reinput
			cout << "\t\t\tInvalid input found" << endl;
	} while (decision);


}
void DeleteCinemaHall(int& record)
{
	int number;
	cout << "Please input the cinema hall number >>>";
	cin >> number;

	if (number > 0 && number <= record)
	{
		for (int i = 0; i < record; i++)
		{
			if (unavailable[i].hall == number)
			{
				for (int j = i; j < record; j++)
				{
					unavailable[j].hall =j+1;
					unavailable[j].data = unavailable[j + 1].data;
					if (unavailable[j].data> 0)
					{
						for (int z = 0; z < unavailable[j].data; z++)
						{
							unavailable[j].row[z] = unavailable[j + 1].row[z];
							unavailable[j].column[z] = unavailable[j + 1].column[z];
						}
					}
					else
					{
						unavailable[j].row[0] = 0;
						unavailable[j].column[0] = 0;
					}
					number++;
				}
			}
		}
		record--;
		cout << "successfully deleted..." << endl;
		LoadCinemaHallRecord(record);
	}
	else
		cout << "no cinema hall found" << endl;
}
void AddCinemaSeat(int& record)
{//add unavailable seats
	int number;
	char continued;
	cout << "\t\t\tInput the number of cinema hall >>>";
	cin >> number;
	if (number > 0 && number <= record)
	{
		bool decision = true;
		do {
			int row, column;
			number -= 1;
			CinemaSeatPrinting(number,99);
			cout << "\t\t\tInput the row that you want to modify >>>";
			cin >> row;
			cout << "\t\t\tInput the column that you want to modify >>>";
			cin >> column;
			if (unavailable[number - 1].data > 0)
			{
				int found = 0;
				for (int i = 0; i < unavailable[number - 1].data; i++)
				{
					if (row > 10 || column > 14)
					{
						found++;
						cout << "\t\t\tplease ensure row and column within the range: 0 < row < 10 and 0 < column < 15" << endl;
						cout << "\t\t\tPlease reinput row and column" << endl;
						break;
					}
					else if (unavailable[number - 1].row[i] == row && unavailable[number - 1].column[i] == column)
					{
						found++;
						cout << "\t\t\tInput have found inside the system..." << endl;
						cout << "\t\t\tPlease reinput row and column" << endl;
						break;
					}
				}
				if (found == 0)
				{
					ConfirmAddCinemaSeat(number, row, column);
				}
			}
			else
				ConfirmAddCinemaSeat(number, row, column);
			LoadCinemaHallRecord(record);
			cout << "\t\t\tDo you want to continue <Y>es <N>o >>";
			cin >> continued;
			continued = toupper(continued);
			if (continued == 'N')
				decision = false;
		} while (decision);

	}
	else
		cout << "\t\t\tNo cinema hall found."<<endl;
}
void DeleteCinemaSeat(int& record)
{
	int number;
	cout << "\t\t\tPlease input the cinema hall number >>>";
	cin >> number;

	if (number > 0 && number <= record)
	{
		cout << "\n\n" << string(100, char(61)) << "\n\n";
		cout << "\t\t\tCinema hall " << number << endl;
		CinemaSeatPrinting(number - 1, 99);
		bool decision = true;
		do {
			char continued;
			int row, column;
			cout << "\t\t\tInput the row of the seat >> ";
			cin >> row;
			cout << "\t\t\tInput the column of the seat >> ";
			cin >> column;
			int found = 0;
			for (int i = 0; i < unavailable[number - 1].data; i++)
			{
				if (row > 10 || column > 14)
				{
					cout << "\t\t\tplease ensure row and column within the range: 0 < row < 10 and 0 < column < 15" << endl;
					break;
				}
				else if (unavailable[number - 1].row[i] == row && unavailable[number - 1].column[i] == column)
				{
					found++;
					char confirms;
					cout << "\t\t\tAre you confirm delete row " << row << " and " << "column " << column << " <Y>es <N>o  >>";
					cin >> confirms;
					confirms = toupper(confirms);					
					if (confirms == 'Y')
					{
						for (int j = i; j < unavailable[number - 1].data; j++)
						{
							unavailable[number - 1].row[j] = unavailable[number - 1].row[j + 1];
							unavailable[number - 1].column[j] = unavailable[number - 1].column[j + 1];
						}
						unavailable[number - 1].data -= 1;
						LoadCinemaHallRecord(record);
					}
					else
					{
						cout << "\t\t\tConfirmation Unsuccessful" << endl;
						cout << "\t\t\tPlease reinput the row and column" << endl;
					}
					break;
				}

			}
			if (found == 0)
				cout << "\t\t\tNo data found in system" << endl;
			cout << "\t\t\tDo you want to continue <Y>es <N>o >>";
			cin >> continued;
			continued = toupper(continued);
			if (continued == 'N')
				decision = false;
		} while (decision);
	}
	else
		cout << "\t\t\tno cinema hall seat found" << endl;
}
void ConfirmAddCinemaSeat(int number, int row, int column)
{
	char confirms;
	cout << "Are you confirm add row " << row << " and " << "column " << column << " <Y>es <N>o  >>";
	cin >> confirms;
	confirms = toupper(confirms);
	if (confirms == 'Y')
	{
		cout << "confirmation successful" << endl;
		unavailable[number - 1].data += 1;
		unavailable[number - 1].row[unavailable[number - 1].data - 1] = row;
		unavailable[number - 1].column[unavailable[number - 1].data - 1] = column;
		cout << "succesfully added" << endl;
	}
	else
	{
		cout << "Confirmation Unsuccessful" << endl;
		cout << "Please reinput the row and column" << endl;
	}
}

void MovieManagement(int option)
{
	bool decision = true;
	string selection;
	do {
		int record = 0;
		cin. clear();
		system("cls");
		for (int i = 0; i < 7; i++)
		{
			cout << "\t\t\t\t\t" << text[4][i] << endl;
		}
		cout << "\n\t\t\t" << string(150, char(95)) << endl;
		ReadMovieRecord(record);
		MoviePrinting(record,99);
		cout << "\n\t\t\t" << string(150, char(95)) << endl;
		cout << "\n\n\t\t\t\t<1> Add Movie " << endl;
		cout << "\t\t\t\t<2> Modify Movie " << endl;
		cout << "\t\t\t\t<3> Delete Movie " << endl;
		cout << "\t\t\t\t<4> exit " << endl;
		cout << "\t\t\t\tInput your selection >>> ";
		getline(cin, selection);
		if(selection=="1")
			AddMovie(record);
		else if(selection=="2")
			ModifyMovie(record);
		else if(selection=="3")
			DeleteMovie(record); 
		else if(selection=="4")
			decision = false;
		else
			cout << "\t\t\tInvalid input found" << endl; 
	} while (decision);
}
void ReadMovieRecord(int& record)
{
	ifstream infile;
	infile.open("movie.txt");
	if (infile.fail())
		cout << "unable to open the file";
	else
	{
		while (!infile.eof())
		{
			getline(infile,movie[record].movie_id);
			getline(infile, movie[record].movie_name);
			getline(infile, movie[record].description);
			getline(infile, movie[record].movie_time);
			infile >> movie[record].movie_length;
			infile >> movie[record].movie_hall;
			infile >> movie[record].seats.data;
			if (movie[record].seats.data > 0)
			{
				for (int i = 0; i < movie[record].seats.data; i++)
					infile >> movie[record].seats.purchased_row[i];
				for (int i = 0; i < movie[record].seats.data; i++)
					infile >> movie[record].seats.purchased_column[i];
			}
			else
			{
				infile >> movie[record].seats.purchased_row[0];
				infile >> movie[record].seats.purchased_column[0];

			}
			infile >> movie[record].backup.data;
			if (movie[record].backup.data > 0)
			{
				for (int i = 0; i < movie[record].backup.data; i++)
					infile >> movie[record].backup.row[i];
				for (int i = 0; i < movie[record].backup.data; i++)
					infile >> movie[record].backup.column[i];
			}
			else
			{
				infile >> movie[record].backup.row[0];
				infile >> movie[record].backup.column[0];

			}
			infile.ignore();
			record++;
		}
	}
	infile.close();

}
void LoadMovieRecord(int& record)
{
	ofstream outfile;
	outfile.open("movie.txt");
	for (int i = 0; i < record; i++)
	{
		outfile << movie[i].movie_id << endl << movie[i].movie_name << endl << movie[i].description << endl;
		outfile << movie[i].movie_time << endl << movie[i].movie_length << endl << movie[i].movie_hall << endl;
		outfile << movie[i].seats.data << endl;
		if (movie[i].seats.data > 0)
		{
			for (int j = 0; j < movie[i].seats.data; j++)
			{
				if (j > 0)
					outfile << " ";
				outfile << movie[i].seats.purchased_row[j];
			}
			outfile << endl;
			for (int j = 0; j < movie[i].seats.data; j++)
			{
				if (j > 0)
					outfile << " ";
				outfile << movie[i].seats.purchased_column[j];
			}
		}
		else
		{
			outfile << movie[i].seats.purchased_row[0] << endl;
			outfile << movie[i].seats.purchased_column[0] << endl;
		}
		outfile << movie[i].backup.data << endl;
		if (movie[i].backup.data > 0)
		{
			for (int j = 0; j < movie[i].backup.data; j++)
			{
				if (j > 0)
					outfile << " ";
				outfile << movie[i].backup.row[j];
			}
			outfile << endl;
			for (int j = 0; j < movie[i].backup.data; j++)
			{
				if (j > 0)
					outfile << " ";
				outfile << movie[i].backup.column[j];
			}
		}
		else
		{
			outfile << movie[i].backup.row[0]<<endl;
			outfile << movie[i].backup.column[0];
		}
		if (!(i == record - 1))
			outfile << endl;
	}
	outfile.close();
}
void AddMovie(int& record)
{
	bool decision = true;
	do {
		int movie_hall;
		string movie_name, movie_id, description, movie_time,confirms;
		double movie_length;
		bool checking = true;
		do {
			int found = 0;
			cout << "\t\t\t\tInput the movie id >>> ";
			cin >> movie_id;
			movie_id = upper(movie_id);
			for (int i = 0; i < record; i++)
			{
				if (movie_id == movie[i].movie_id)
					found++;
			}
			if (found == 0)
				checking = false;
			else
				cout << "\t\t\t\tMovie id detected." << endl;
		} while (checking);
		cin.ignore();
		cout << "\t\t\t\tInput the movie name >>> "; //same name allowed(same name,diff. movie
		getline(cin, movie_name);
		movie_name = upper(movie_name);
		
		cout << "\t\t\t\tInput the movie description >>> ";
		getline(cin, description);

		checking = true;
		do {
			cout << "\t\t\t\tInput the movie_time (24 Hours format XXXX) >>> ";
			cin >> movie_time;								
			bool result = MovieStartDetection(movie_time);
			if (result)
				checking = false;
			else
				cout << "\t\t\t\tinvalid input" << endl;
		} while (checking);

		checking = true;
		do {
			cout << "\t\t\t\tInput the movie_length in (Hours.minutes~~~ X.XX)>>> ";
			cin >> movie_length;							//2.60		2.50	(input)
			int hour = int(movie_length);					//2.00		2
			double minutes = (movie_length-hour) * 100;		//60		50
			if (minutes >= 60)
				cout << "\t\t\t\tinvalid input" << endl;
			else
				checking = false;
		} while (checking);
		checking = true;
		do {
			int found = 0,hall=0;
			cout << "\t\t\t\tInput the movie_hall >>>";
			cin >> movie_hall;
			if (movie_hall<=record||movie_hall>0)
			{
				MovieEndDetection(movie_time, movie_hall, movie_length, found, record,999);
				if (found == 0)
					checking = false;
			}
			else
				cout << "\t\t\t\tPlease input again the movie hall" << endl;
		} while (checking);
		checking = true;
		do{
			cout << "\t\t\t\tMovie ID: " << movie_id << endl;
			cout << "\t\t\t\tMovie Name: " << movie_name << endl;
			cout << "\t\t\t\tMovie description: " << description << endl;
			cout << "\t\t\t\tMovie time: " << movie_time << endl;
			cout << "\t\t\t\tMovie length H.MM: " << movie_length << endl;
			cout << "\t\t\t\tMovie hall: " << movie_hall << endl;
			cout << "\t\t\t\tAre you confirm? <Y>es <N>o >>> ";
			cin >> confirms;
			confirms = upper(confirms);
			if (confirms == "Y" || confirms == "N")
			{
				checking = false;
			}
		}while(checking);

		if (confirms == "Y")
		{
			MovieIntoStruct(movie_id, movie_name, description, movie_time, movie_length, movie_hall, record);
		}
		string cont;
		do{
			cout << "\t\t\t\tDO you want to continue <Y>es <N>o >>> ";
			cin >> cont;
			cont = upper(cont);
			if (!(cont == "Y" || cont == "N"))
				cout << "\t\t\tInvalid input" << endl;
		} while (!(cont == "Y" || cont == "N"));
		if (cont == "N")
			decision = false;
	} while (decision);

}
void ModifyMovie(int& record)
{
	bool decision = true;
	do {
		string movie_name, movie_id, description, movie_time;
		double movie_length;
		int movie_hall, trace = 0;
		int found = 0,selection,storage;
		cout << "\t\t\t\tInput the Movie ID <E>xit: ";
		cin >> movie_id;
		movie_id = upper(movie_id);
		for (int i = 0; i < record; i++)
		{
			if (movie_id == movie[i].movie_id)
			{
				found++;
				storage = i;
			}
		}
		if (found > 0)
		{
			cout << "\n\t\t\t\tWhich section you want to modify???" << endl;
			cout << "\t\t\t\t<1> Movie ID " << endl;
			cout << "\t\t\t\t<2> Movie Name" << endl;
			cout << "\t\t\t\t<3> Movie Description" << endl;
			cout << "\t\t\t\t<4> Movie Start time" << endl;
			cout << "\t\t\t\t<5> Movie length" << endl;
			cout << "\t\t\t\t<6> Cinema Hall of movie" << endl;
			cout << "\t\t\t\t<7> Exit" << endl;
			cout << "\t\t\t\tInput your selection";
			cin >> selection;
			switch (selection)
			{
			case(1):
			{
				int check = 0;
				cout << "\t\t\t\tInput new movie id >>> ";
				cin >> movie_id;
				for(int i = 0; i < record; i++)
				{
					if (movie_id == movie[i].movie_id)
					{
						cout << "\t\t\t\tMovie ID was found inside the system." << endl;
						check++;
					}
				}
				if (check == 0)
				{
					movie[storage].movie_id = movie_id;
				}
				break;
			}
			case(2):
			{
				//assume that movie can have the same name !!!
				cout << "\t\t\t\tInput new movie name >>> ";
				getline(cin, movie_name);
				movie[storage].movie_name = movie_name;
				break;
			}
			case(3):
			{
				//assume that description can have the same !!!
				cout << "\t\t\t\tInput new movie description >>> ";
				getline(cin, description);
				movie[storage].description = description;
				break;
			}
			case(4):
			{

				cout << "\t\t\t\tInput the new start time in 24 Hours format (XXXX)>>> ";
				cin >> movie_time;
				bool result = MovieStartDetection(movie_time);
				if (result)
				{
					MovieEndDetection(movie_time, movie[storage].movie_hall, movie[storage].movie_length, trace, record,storage);
					cout << trace << endl;
					if (trace == 0)
					{
						movie[storage].movie_time = movie_time;
					}
				}
				break;
			}
			case(5)://enter length (start time,movie hall)
			{
				cout << "\t\t\t\tEnter the new movie length in Hours.Minutes(X.XX) >>>";
				cin >> movie_length;
				MovieEndDetection(movie[storage].movie_time, movie[storage].movie_hall,movie_length, trace, record,storage);
				if (trace == 0)
				{
					movie[storage].movie_length = movie_length;
				}
				break;
			}
			case(6)://movie hall( start time, end time)
			{
				cout << "\t\t\t\tEnter the new movie hall >>>";
				cin >> movie_hall;
				MovieEndDetection(movie[storage].movie_time,movie_hall, movie[storage].movie_length, trace, record,storage);
				if (trace == 0)
				{
					movie[storage].movie_hall = movie_hall;
					movie[storage].seats.data = 0;
					movie[storage].seats.purchased_row[0] = 0;
					movie[storage].seats.purchased_column[0] = 0;
					movie[storage].backup.data = unavailable[storage].data;
					for (int i = 0; i < movie[storage].backup.data; i++)
					{
						movie[storage].backup.row[i] = unavailable[storage].row[i];
						movie[storage].backup.column[i] = unavailable[storage].column[i];
					}
				}
				break;
			}
			case(7):
			{
				decision = false;
				break;
			}
			default:
			{
				cout << "\t\t\t\tPlease reinput again!!!" << endl;
			}
			}
		
		}
		else if(movie_id=="E")
			decision = false;
		else
			cout << "\t\t\t\tinvalid input.Please input again" << endl;
			LoadMovieRecord(record);
	} while (decision);
}
void DeleteMovie(int& record) 
{
	int found=0,index;
	string movie_id;
	bool decision = true;
	do {
		char confirm = 'W';
		cout << "\t\t\t\tInput the movie id you want to delete <E>xit >>>>";
		cin >> movie_id;
		movie_id = upper(movie_id);
		if (!(movie_id == "E"))
		{
			for (int i = 0; i < record; i++)
			{
				if (movie_id == movie[i].movie_id)
				{
					found++;
					index = i;
				}

			}
			if (found==1)
			{
				cout << "\t\t\t\tMovie ID found in system" << endl;
				while (!(confirm == 'Y' || confirm == 'N'))
				{
					cout << "\t\t\t\tFinal confirmation <Y>es <N>o >>>";
					cin >> confirm;
					confirm = toupper(confirm);
					if (!(confirm == 'Y' || confirm == 'N'))
						cout << "\t\t\t\tInvalid input" << endl;
				}
				if (confirm == 'Y')
				{
					cout << "\t\t\t\tLoading..." << endl;
					Sleep(3500);
					for (int j = index; j < record; j++)
					{
						movie[j].movie_id = movie[j + 1].movie_id;
						movie[j].movie_name = movie[j + 1].movie_name;
						movie[j].description = movie[j + 1].description;
						movie[j].movie_time = movie[j + 1].movie_time;
						movie[j].movie_length = movie[j + 1].movie_length;
						movie[j].movie_hall = movie[j + 1].movie_hall;
						movie[j].seats.data = movie[j + 1].seats.data;
						if (movie[j].seats.data > 0) {
							for (int z = 0; z < movie[j].seats.data; z++)
							{
								movie[j].seats.purchased_row[z] = movie[j + 1].seats.purchased_row[z];
								movie[j].seats.purchased_column[z] = movie[j + 1].seats.purchased_column[z];
							}
						}
						else {
							movie[j].seats.purchased_row[0] = movie[j + 1].seats.purchased_row[0];
							movie[j].seats.purchased_column[0] = movie[j + 1].seats.purchased_column[0];
						}
						movie[j].backup.data = movie[j + 1].backup.data;
						if (movie[j].backup.data > 0)
						{
							for (int z = 0; z < movie[j].backup.data; z++)
							{
								movie[j].backup.row[z] = movie[j + 1].backup.row[z];
								movie[j].backup.column[z] = movie[j + 1].backup.column[z];
							}
						}
						else {
							movie[j].backup.row[0] = movie[j + 1].backup.row[0];
							movie[j].backup.column[0] = movie[j + 1].backup.column[0];

						}
						decision = false;
						record--;
						LoadMovieRecord(record);

					}
				}
				else if (found == 0)
					cout << "\t\t\tInvalid movie id" << endl;
			}
		}
		else
			decision = false;
		
	} while (decision);

}
void MoviePrinting(int& record,int w)
{
	for (int i = 0; i < record; i++)
	{
		cout << "\n\t\t\tNo. " << i + 1 << endl;
		if (w == 99) //only print for admin
			cout << "\t\t\tMovie Id: " << movie[i].movie_id << endl;
		cout << "\t\t\tMovie Name: " << movie[i].movie_name << endl;
		cout << "\t\t\tMovie Description: " << movie[i].description << endl;
		cout << "\t\t\tMovie Time: " << movie[i].movie_time << endl;
		cout << "\t\t\tMovie Length H.MM: " <<fixed<<setprecision(2)<< movie[i].movie_length << endl;
		cout << "\t\t\tMovie Hall: " << movie[i].movie_hall << endl;
	}
}
bool MovieStartDetection(string movie_time)   //detect start time of movie
{													//sample output

	int checking = stoi(movie_time);				//2401      2061
	int integer_hours = checking / 100 * 100;		//2400		2000
	int remain = checking%integer_hours;			//1			61
	int size=int (movie_time.length());
	if (size > 4 || size < 4)
		return false;
	else if (integer_hours > 2400)		//if more than 24 hours (a day)
		return false;
	else if (remain > 60)		//if minutes more than 60
		return false;
	else
		return true;
}
void MovieIntoStruct(string id,string name,string description,string time,double length,int hall,int &record)
{
	record++;
	movie[record - 1].movie_id = id;
	movie[record - 1].movie_name = name;
	movie[record - 1].description = description;
	movie[record - 1].movie_time = time;
	movie[record - 1].movie_length = length;
	movie[record - 1].movie_hall = hall;
	movie[record - 1].seats.data = 0;
	movie[record - 1].seats.purchased_row[0] = 0;
	movie[record - 1].seats.purchased_column[0] = 0;
	movie[record - 1].backup.data = unavailable[hall - 1].data;
	if (movie[record - 1].backup.data > 0)
	{
		for (int i = 0; i < movie[record - 1].backup.data; i++)
		{
			movie[record - 1].backup.row[i] = unavailable[hall - 1].row[i];
			movie[record - 1].backup.column[i] = unavailable[hall - 1].column[i];
		}
	}
	else
	{
		movie[record - 1].backup.row[0] = unavailable[hall - 1].row[0];
		movie[record - 1].backup.column[0] = unavailable[hall - 1].column[0];
	}
	LoadMovieRecord(record);
}
void MovieEndDetection(string movie_time, int movie_hall, double movie_length, int& found, int& record, int storage)
{//storage is i value from modication section
	double movie_end = stoi(movie_time) + (int(movie_length) * 100 + (movie_length - int(movie_length)) * 100);
	movie_end = int(movie_end);
	if (movie_end - movie_end / 100 * 100 > 60) {//minutes exist 60
		movie_end = movie_end - 60 + 100;
	}
	for (int i = 0; i < record; i++)
	{
		int detection = 0,timing,hour,minutes,ending,overflow;
		if (i == storage){
			detection++;
			continue;
		}
		else if (movie_hall == movie[i].movie_hall) {		//take other record than that movie hall(if 99)  ===
			string time = movie[i].movie_time;					//1200
			timing = stoi(time);
			detection++;
		}
		if(detection==1){
			hour = int(movie_length);						//2.40=2
			minutes = int((movie_length - hour) * 100);		//40
			ending = timing + hour * 100 + minutes;			//1200+2*100+40
			overflow = ending - int(ending / 100 * 100);
			if (overflow >= 60)
				ending = ending - 60 + 100;

			if (stoi(movie_time) >= timing && stoi(movie_time) <= ending)
			{
				found++;
			}
			else if (movie_end >= timing && movie_end <= ending)
			{
				found++;
			}
		}
	}
}

void EmployeeManagement(int)
{
	bool decision = true;
	do {
		system("cls");
		int record = 0,selection;
		ReadEmployeeRecord(record);
		cout << "\n\n\n\t\t\t" << string(161, char(61)) << endl;
		cout << "\t\t\t=" << setw(15) << "Employee ID" << setw(35) << "Employee Name" << setw(45) << "Department" << setw(40) << "Position" << setw(20) << "Password" << setw(5) << "=" << endl;
		cout << "\t\t\t" << string(161, char(61)) << endl;
		for (int i = 0; i < record; i++)
		{
			cout << "\t\t\t=" << setw(15) << employee[i].id << setw(35) << employee[i].name << setw(45) << employee[i].department << setw(40) << employee[i].position << setw(20) << employee[i].password << setw(5) << "=" << endl;
		}
		cout << "\t\t\t" << string(161, char(61)) << endl;		cout << "\t\t\t<1> Add Employee " << endl;
		cout << "\t\t\t<2> Modify Employee" << endl;
		cout << "\t\t\t<3> Delete Employee" << endl;
		cout << "\t\t\t<4> Exit" << endl;
		cout << "\t\t\tInput your selection >>>";
		cin >> selection;
		switch (selection)
		{
		case(1):
		{
			AddEmployee(record);
			break;
		}
		case(2):
		{
			ModifyEmployee(record);
			break;
		}
		case(3):
		{
			DeleteEmployee(record);
			break;
		}
		case(4):
		{
			decision = false;
			break;
		}
		default:
		{
			cout << "\n\t\t\tinvalid input" << endl;
		}
		}
	} while (decision);
}
void ReadEmployeeRecord(int& record)
{
	ifstream details;
	details.open("employee.txt");
	if (details.fail())
		cout << "unable to open the file" << endl;
	else
	{
		while (!details.eof())
		{
			getline(details, employee[record].id);
			getline(details,employee[record].name);
			getline(details,employee[record].department);
			getline(details,employee[record].position);
			details >> employee[record].password;
			details.ignore();
			record++;
		}
	}
	details.close();
}
void LoadEmployeeRecord(int& record)
{
	ofstream details;
	details.open("employee.txt");
	if (details.fail())
		cout << "unable to open the file" << endl;
	else
	{
		for (int i = 0; i < record; i++)
		{
			details << employee[i].id << endl;
			details << employee[i].name << endl;
			details << employee[i].department << endl;
			details << employee[i].position << endl;
			if (i == record - 1)
				details << employee[i].password;
			else
				details << employee[i].password << endl;
		}
	}
	details.close();
}
void AddEmployee(int& record)
{
	bool decision = true;
	do {
		char confirms;
		bool checking = true,result;
		int password;
		string employee_id, employee_department, employee_name, employee_position;
		do {
			cout << "\t\t\tInput employee id ('EW' and 3 numeric numbers)>>>";
			cin >> employee_id;
			employee_id = upper(employee_id);
			result = EmployeeID(employee_id, record);
			if (result)
				checking = false;
			else
				cout << "\t\t\tPlease reinput again employee id" << endl;
		} while (checking);
		char cont;
		do {
			cin.ignore();
			cout << "\t\t\tInput employee name >>>";
			getline(cin, employee_name);
			employee_name = upper(employee_name);
			cout << "\t\t\tEmployee name, "<<employee_name<<"\n\t\t\tIf confirms <Y>es >>> ";
			cin >> cont;
			cont = toupper(cont);
		} while (!(cont == 'Y'));
		
		char conts;
		do {
			int number;
			for (int i = 0; i < sizeof(department)/sizeof(string); i++)//display department
			{
				cout << "\t\t\t<"<<i+1<<"> " << department[i] << endl;
				
			}
			cout << "\t\t\tinput your selection >>>";
			cin >> number;
			employee_department = department[number - 1];
			cout << "\t\t\tThis employee under deparment of " << employee_department << endl;
			cout << "\t\t\tEmployee department confirmation <Y>es <N>o >>> ";
			cin >> conts;
			conts = toupper(conts);
		} while (!(conts=='Y'));

		char resume;
		do {
			cin.ignore();
			cout << "\t\t\tInput the position of employee >>> ";
			getline(cin,employee_position);
			employee_position = upper(employee_position);
			cout << "\t\t\tHer/His position is "<<employee_position<<endl;
			cout << "\t\t\tEmployee position confirmation <Y>es <N>o >>> ";
			cin >> resume;
			resume = toupper(resume);
		} while (!(resume == 'Y'));
		bool check = true;
		do {
			int found = 0;
			int number[4] = { 10000,20000,30000,40000 };
			int index = rand() % 4; //index=(0,1,2,3)
			int value = number[index] + rand() % 10000;//10000+XXXX
			for (int i = 0; i < record; i++)
			{
				if (value == employee[i].password)
					found++;
			}
			if (found == 0)
			{
				password = value;//password will be assigned automatically
				check = false;
			}
		} while (check);
		
		do {
			cout << "\t\t\tFinal confirmation <Y>es <N>o >>>";
			cin >> confirms;
			confirms = toupper(confirms);
			if (confirms == 'Y')
			{
				cout << "\t\t\tSuccessfully added employee named " << employee_name << "," << employee_id << endl;
				employee[record].id = employee_id;
				employee[record].name = employee_name;
				employee[record].department = employee_department;
				employee[record].position = employee_position;
				employee[record].password = password;
				record++;
				LoadEmployeeRecord(record);
				decision = false;
			}
			else if (confirms == 'N')
			{
				cout << "\t\t\tPending exit to employee page." << endl;
				Sleep(20);
				decision = false;
			}
		} while (!(confirms == 'Y' || confirms == 'N'));
	} while (decision);
}
void DeleteEmployee(int& record)
{
	string employee_id;
	char cont;
	do {
		int found = 0;
		cout << "\n\t\t\tInput the employee ID that want to delete >>>";
		cin >> employee_id;
		employee_id = upper(employee_id);
		for(int i=0;i<record;i++)
		{
			if (employee_id == employee[i].id)//must character by character
			{
				for (int j = i; j < record; j++)
				{
					found++;
					record--;
					employee[j].id = employee[j + 1].id;
					employee[j].name = employee[j + 1].name;
					employee[j].department = employee[j + 1].department;
					employee[j].position = employee[j + 1].position;
					employee[j].password = employee[j + 1].password;
					LoadEmployeeRecord(record);
				}
				break;
			}
		}
		if (found == 0)
			cout << "\t\t\tThe employee id did not found in the system" << endl;
		do {
			cout << "\t\t\tDo you want to continue <Y>es <N>o >> >";
			cin >> cont;
			cont = toupper(cont);
			if (!(cont == 'N' || cont == 'Y'))
				cout << "\t\t\tPlease input 'Y' or 'N' " << endl;
		} while (!(cont == 'N' || cont == 'Y'));
	} while (cont=='Y');
}
void ModifyEmployee(int& record)
{
	bool checking = true;
	do {
		bool result;
		int index, found=0,selection,number=0;
		string id,employee_id, employee_name, employee_position;
		cout << "\t\t\tInput the employee id to modify >>> ";
		cin >> id;
		id = upper(id);
		for (int i = 0; i < record; i++)
		{
			if (id == employee[i].id)
			{
				index = i;
				found++;
			}
		}
		if (found == 1)
		{
				cout << "\t\t\tEmployee id, "<<id<<" found in system " << endl;
				cout << "\t\t\t<1> Employee id" << endl;
				cout << "\t\t\t<2> Employee name" << endl;
				cout << "\t\t\t<3> employee department" << endl;
				cout << "\t\t\t<4> employee position" << endl;
				cout << "\t\t\t<5> Exit" << endl;
				cout << "\t\t\tinput your selection to modify >>> ";
				cin >> selection;
				switch (selection)
				{
				case(1):
				{
					cout << "\t\t\tinput new employee id ('EW' and 3 numerial numbers)>>>";
					cin >> employee_id;
					employee_id = upper(employee_id);
					result = EmployeeID(employee_id, record);
					if (result)
						employee[index].id = employee_id;
					else
						cout << "\t\t\tInvalid employee id" << endl;
					checking = false;
					break;
				case(2):
				{
					cin.ignore();
					cout << "\t\t\tInput new employee name: ";
					getline(cin, employee_name);
					employee_name = upper(employee_name);
					employee[index].name= employee_name;
					checking = false;
					break;
				}
				case(3):
				{
					for (int i = 0; i < 5; i++)
					{
						cout << "\t\t\t< " << i+1 << " > " << department[i] << endl;
					}
					cout << "\t\t\tInput the department number >>>";
					cin >> number;
					employee[index].department = department[number - 1];
					checking = false;
					break;
				}
				case(4):
				{
					cin.ignore();
					cout << "\t\t\tInput new position of employee >>> ";
					getline(cin, employee_position);
					employee_position = upper(employee_position);
					cout << "\t\t\tPosition is " << employee_position;
					employee[index].position= employee_position;
				}
				}case(5):
				{
					checking = false;
					break;
				}
				default:
				{
					cout << "\t\t\tInvalid input detected." << endl;
				}
				}
				LoadEmployeeRecord(record);
		}
		else
			cout << "\t\t\tInvalid input detected." << endl;
	} while (checking);
}
bool EmployeeID(string employee_id,int &record)
{//employee id must start with EW and end with three numeric numbers
	int found = 0,size;
	size = signed(employee_id.size());
	for (int i = 0; i < record; i++)
	{
		if (employee_id == employee[i].id)
			found++;
	}
	if (found == 0 && size == 5)
	{
		if ((employee_id[0] == 'E' && employee_id[1] == 'W') && (isdigit(employee_id[3]) && (isdigit(employee_id[3]) && isdigit(employee_id[3]))))
			return true;//&& is binary operator(only can compare two items)
		else
			return false;
	}
	else
		return false;
}
void MovieDetails(int option)
{
	system("cls");
	int record = 0;
	string leave;
	GetSystemTime(&systemTime);
	ReadMovieRecord(record);
	cout << "\n\n\n\n\t\t\t" << string(150, char(95)) << endl;
	cout << "\t\t\t" << setw(134) << systemTime.wDay << "/" <<systemTime.wMonth << "/" << systemTime.wYear << " " << systemTime.wHour << ":" << systemTime.wMinute << ":" << systemTime.wSecond << endl;
	cout << "\t\t\t" << string(150, char(95)) << endl;
	MoviePrinting(record, 0);
	cout << "\t\t\t" << string(150, char(95)) << endl;
	cout << "\t\t\t";
	system("pause");
}

void PurchaseNow(int option)
{
	int selection;
	bool decision=true;
	do {
		system("cls");
		cout << "\t\t\t<1> Book a movie UwU " << endl;
		cout << "\t\t\t<2> Food & Beverages " << endl;
		cout << "\t\t\t<3> Exit " << endl;
		cout << "\t\t\tInput your selection >>> ";
		cin >> selection;
		switch (selection)
		{
		case(1):
		{
			BookMovie(selection);
			break;
		}
		case(2):
		{

			break;
		}
		case(3):
		{
			decision = false;
			break;
		}
		default:
		{
			cout << "\t\t\tinvalid input" << endl;
		}
		}
	} while (decision);

}
void BookMovie(int option)
{
	bool decision=true,validated=true;
	do {
		int record = 0, result = 0, time_validate = 0, inner = 0, movie_hall[30] = {}, date = 0, month = 0, year = 0, dd, mm, yyyy;
		string keyword, movie_time,currentdate;
		system("cls");
		ReadMovieRecord(record);
		GetSystemTime(&systemTime);
		cout << "\n\n\n\n\t\t\t" << string(150, char(95)) << endl;
		cout << "\t\t\t" << setw(134) <<systemTime.wDay << "/" <<systemTime.wMonth << "/" << systemTime.wYear << " " << systemTime.wHour << ":" << systemTime.wMinute << ":" << systemTime.wSecond << endl;
		cout << "\t\t\t" << string(150, char(95)) << endl;
		MoviePrinting(record, 0);
		cout << "\t\t\t" << string(150, char(95)) << endl;
		do {
			cout << "\t\t\tDear customer, please input current date (refer to upper right)" << endl;
			cout << "\t\t\tcurrent date in DD MM YYYY form >>>";
			cin >> dd >> mm >> yyyy;
			TimeChecking(dd, mm, yyyy, date, month, year, time_validate);
			if (time_validate > 0)
			{
				validated = false;
				currentdate = to_string(dd) + " " + to_string(mm) + " " + to_string(yyyy);
			}
			else
				cout << "\t\t\tInvalid input detected." << endl;
		} while (validated);
		cin.ignore();
		cout << "\t\t\tInput the keyword to search the movie <E>xit >>>";
		getline(cin,keyword);
		keyword = upper(keyword);
		for (int i = 0; i < record; i++)
		{
			if (movie[i].movie_name.find(keyword) != string::npos)//keyword checking process
			{
				inner++;
				if (inner== 1){
					system("cls");
					cout << "\n\n\n\n\t\t\t" << string(150, char(95)) << endl;
					cout << "\t\t\t" << setw(135) <<systemTime.wDay << "/" <<systemTime.wMonth << "/" << systemTime.wYear << " " << systemTime.wHour << ":" << systemTime.wMinute << ":" << systemTime.wSecond << endl;
					cout << "\t\t\t" << string(150, char(95)) << endl;
				}
				cout << "\n\t\t\tNo. " << inner << endl;
				cout << "\t\t\tMovie Name: " << movie[i].movie_name << endl;
				cout << "\t\t\tMovie Description: " << movie[i].description << endl;
				cout << "\t\t\tMovie Time: " << movie[i].movie_time << endl;
				cout << "\t\t\tMovie Length H.MM: " << fixed << setprecision(2) << movie[i].movie_length << endl;
				cout << "\t\t\tMovie Hall: " << movie[i].movie_hall << endl;
			}
		}
		if (keyword == "E")
			decision = false;
		else if (inner == 0)
		{
			cout << "\t\t\tno result found...\n\t\t\tReturn to booking page" << endl;
			Sleep(1000);
			return BookMovie(0);
		}
		else {
			cout << "\t\t\t" << string(150, char(95)) << endl;
			bool confirms = true;
			int found = 0, adult, child, total_people=0;
			string people[25] = {};
			string booking="w";
			while (confirms)
			{
				cout << "\t\t\tInput the showtime of the movie <E>xit >>>";
				cin >> movie_time;
				if (movie_time == "E" || movie_time == "e")
				{
					confirms = false;
					decision = false;
				}
				else
				{
					int noMovie[10] = {}, index = 0, number = 0;
					bool result = MovieStartDetection(movie_time);

					for (int i = 0; i < record; i++)
					{
						if (movie_time == movie[i].movie_time)
						{
							noMovie[found] = i;
							found++;
						}
					}
					if (result&&found>0)
					{
						string booking;
						do {
							index = noMovie[number];
							number++;
							cout << "\t\t\tMovie Name: " << movie[index].movie_name << endl;
							cout << "\t\t\tMovie Description: " << movie[index].description << endl;
							cout << "\t\t\tMovie Time: " << movie[index].movie_time << endl;
							cout << "\t\t\tMovie Length H.MM: " << fixed << setprecision(2) << movie[index].movie_length << endl;
							cout << "\t\t\tMovie Hall: " << movie[index].movie_hall << endl;
							cout << "\t\t\tAre this movie you want to book <Y>es <N>o >> >";
							cin >> booking;
							booking = upper(booking);
							string final;
							int row[25];
							int column[25];
							bool payment = true;
							if (booking == "Y")
							{
								NumberTicket(index, child, adult, row, column);
								do {

									cout << "\t\t\tAre you confirms with this booking <Y>es <N>o <E>xit >>>";
									cin >> final;
									final = upper(final);
									if (final == "Y" || final == "E") {
										payment = false;
									}
									else if (final == "N")
									{
										cout << "\t\t\tPayment declined" << endl;
										payment = false;
										confirms = false;
										decision = false;
									}
								} while (payment);
							}

							if (final == "Y")
							{ 
								int nomember = 0, record = 0;
								OpenMemberDetails(nomember);
								ReadMovieRecord(record);
								string checking = "9999";
								MemberChecking(checking,nomember);
								
								cout << "\t\t\t" << string(60, char(32)) << " PAYMENT SUMMARY " << string(60, CHAR(32)) << endl;
								cout << "\n\n\t\t\t" << string(150, char(95)) << endl;
								cout << "\t\t\t" << setw(134) << systemTime.wDay << "/" << systemTime.wMonth << "/" << systemTime.wYear << " " << systemTime.wHour << ":" << systemTime.wMinute << ":" << systemTime.wSecond << endl;
								cout << "\t\t\t" << string(150, char(95)) << endl;
								cout << "\t\t\t\t" << movie[index].movie_name << endl;
								cout << "\t\t\t\t" << movie[index].movie_hall << endl;
								cout << "\t\t\t" << string(150, char(95)) << endl;
								if (checking != "9999" || checking != "9998")
									cout << "\t\t\t Member Name >>" << Member[stoi(checking)].Details_name << endl;
								cout << "\t\t\t" << string(150, char(95)) << endl;
								cout << "\t\t\tNumber of Child" << "\t\t\t\t\t\t" << child << endl;
								cout << "\t\t\tNumber of Adult" << "\t\t\t\t\t\t" << adult << endl;
								cout << "\t\t\t" << string(150, char(95)) << endl;
								cout << "\t\t\tSeat Number" << endl;
								for (int i = 0; i < child + adult; i++)
								{
									cout <<"\t\t\t  "<< row[i] <<" "<< column[i] << endl;
								}

							}
							else if (booking == "N")
							{
								if (number == found)
								{
									cout << "\t\t\tNo other movie found. Back to movie page" << endl;
									cout << "\t\t\t";
									system("pause");
									return BookMovie(0);
								}
							}
							else
								cout << "\t\t\tInvalid input detected." << endl;
						} while (booking == "N"||booking!="Y");
					}
				}
			}
		}
	} while (decision);
}
void NumberTicket(int index, int& child, int& adult,int row[],int column[])
{
	int input=0,rows,columns,detected;
	CinemaSeatPrinting(index, 0);
	cout << "\t\t\tInput the number of children you want to book for >>>";
	cin >> child;
	cout << "\t\t\tInput the number of adult you want to book for >>>";
	cin >> adult;

	for (int i = 0; i < child + adult; i++)
	{
		cout << "\t\t\tNo. " << i + 1 << endl;
		do {
			detected = 0;
			cout << "\t\t\tInput the row you want >>>>";
			cin >> rows;
			cout << "\t\t\tInput the colomn you want >>>>";
			cin >> columns;
			for (int j = 0; j < movie[index].seats.data; j++)
			{
				if (rows == movie[index].seats.purchased_row[i]&&columns == movie[index].seats.purchased_column[i])
					detected++;
			}
			for (int j = 0; j < movie[index].backup.data; j++)
			{
				if (rows == movie[index].backup.row[i]&&column[j] == movie[index].backup.column[i])
					detected++;
			}
			for (int i = 0; i < input; i++)
			{
				if (rows == row[i]&&columns==column[i])
					detected++;
			}
			if (detected > 0)
				cout << "\t\t\tcolumn of seat is not available." << endl;
		} while (detected != 0);
		if (detected == 0)
		{
			row[i] = rows;
			column[i] = columns;
			input++;
		}
	}
	cout << "\t\t\tSuccessfully booked the seats with " << endl;;
	for (int i = 0; i < child + adult; i++)
	{
		cout << "\t\t\tRow " << row[i] << "Column " << column[i] << endl;
	}
}
void MemberChecking(string &checking,int &nomember)
{
	string members, phone_number;
	do {
		cout << "\t\t\tAre you a member of our cinema <Y>es <N>o  >>";
		cin >> members;
		members = upper(members);
		if (members == "Y") {
			do {
				cout << "\t\t\tInput your phone number to record the points <E>xit >>>";
				cin >> phone_number;
				for (int i = 0; i < nomember; i++)
				{
					if (phone_number == Member[i].Details_phone)
					checking = to_string(i);
				}
				if (phone_number == "E")
					checking = "9998";
				else if (checking == "9999")
					cout << "\t\t\tInvalid input detected." << endl;
			} while (checking == "9999");
		}
		else if (members == "N")
			checking = "9999";
		else
			cout << "\t\t\tInvalid input detected." << endl;
	} while (members != "N" || members != "Y");
}

void TimeChecking(int dd, int mm, int yyyy, int date, int month, int year, int& result)
{
	if (mm >= 1 && mm <= 12)
	{
		if (to_string(yyyy).size() == 4)  //check year
		{
			if (mm >= 1 && mm <= 7)//check month
			{
				if (mm == 2)
				{
					if ((dd >= 1 && dd <= 29) && (yyyy % 4 == 0))
						DateRecord(dd, mm, yyyy, date, month, year, result);
					else if ((dd >= 1 && dd <= 28) && (yyyy % 4 != 0))
						DateRecord(dd, mm, yyyy, date, month, year, result);
				}
				else if (mm % 2 == 0)//check date
				{
					if (dd >= 1 && dd <= 30)
						DateRecord(dd, mm, yyyy, date, month, year, result);
				}
				else
				{
					if (dd >= 1 && dd <= 31)
						DateRecord(dd, mm, yyyy, date, month, year, result);
				}
			}
			else
			{
				if (mm % 2 == 1)
				{
					if (dd >= 1 || dd <= 30)
						DateRecord(dd, mm, yyyy, date, month, year, result);
				}
				else
				{
					if (dd >= 1 && dd <= 31)
						DateRecord(dd, mm, yyyy, date, month, year, result);
				}
			}
		}
	}
}
void DateRecord(int dd, int mm, int yyyy, int date, int month, int year, int& result)
{
	result++;
	date = dd, month = mm, year = yyyy;
}
void BookSeatPrinting(int w, int i, int j)
{
	int checking = 1;
	if (movie[w].backup.data != 0)
	{
		for (int z = 0; z < movie[w].backup.data; z++)
		{
			if (i == movie[w].seats.purchased_row[z] && j == movie[w].seats.purchased_column[z])
			{
				cout << setw(2) << "X";
				checking = 0;
			}
			else if (i == movie[w].backup.row[z] && j == movie[w].backup.column[z])
			{
				cout << setw(2) << " ";
				checking = 0;
			}
		}
	}
	if (checking)
		cout << setw(2) << "A";
}
void CinemaRefresh(int option)
{
	string confirms;
	bool decision=true;
	while (decision)
	{
		int movie_record = 0, hall_record = 0, notfound;
		system("cls");
		ReadTextRecord(0);
		cout << "\n\n" << endl;
		for (int i = 0; i < 7; i++)
			cout << "\t\t\t\t\t\t" << text[20][i] << endl;
		cout << "\n\n\t\t\t" << string(150, char(95)) << endl;
		cout << "\n\t\t\t\tRefresh Cinema terms and conditions!!!" << endl;
		cout << "\t\t\t\tOnce you confirm to refresh the cinema, the available seats and the cinema hall record of each movie will be refreshed " << endl;
		cout << "\t\t\t\tTo the latest updated from the cinema hall record" << endl;
		cout << "\t\t\t\tThe system is not reversable after confirmation have made" << endl;
		cout << "\t\t\t\tRefreshing Cinema Confirmation" << endl;
		cout << "\n\t\t\t" << string(150, char(95)) << endl;
		cout << "\n\t\t\t\t if Confirms <Y>es, else <N>o  >>>";
		getline(cin, confirms);
		confirms = upper(confirms);
		if (confirms == "Y")
		{
			ReadMovieRecord(movie_record);
			ReadCinemaHallRecord(hall_record);
			
			for (int i = 0; i < movie_record; i++)
			{			
				for (int j = 0; j < hall_record; j++)//check if cinema hall not in the seatcontrol.txt
				{
					notfound = 0;
					if (movie[i].movie_hall != unavailable[j].hall)
					{
						notfound++;
					}
				}
				if (notfound != hall_record)
				{
					for (int j = i; j < movie_record; j++)
					{
						movie[j].movie_id = movie[j + 1].movie_id;
						movie[j].movie_name = movie[j + 1].movie_name;
						movie[j].description = movie[j + 1].description;
						movie[j].movie_time = movie[j + 1].movie_time;
						movie[j].movie_length = movie[j + 1].movie_length;
						movie[j].movie_hall = movie[j + 1].movie_hall;
						movie[j].seats.data = movie[j + 1].seats.data;
					}
				}
				movie[i].seats.data = 0;				//update seats data
				movie[i].seats.purchased_row[0] = 0;
				movie[i].seats.purchased_column[0] = 0;
				if (movie[i].movie_hall <= hall_record || movie[i].movie_hall > 0)//refresh the data of cinema hall
				{
					movie[i].backup.data = unavailable[movie[i].movie_hall - 1].data;
					if (movie[i].backup.data > 0)
					{
						for (int j = 0; j < movie[i].backup.data; j++)
						{
							movie[i].backup.row[j] = unavailable[movie[i].movie_hall - 1].row[j];
							movie[i].backup.column[j] = unavailable[movie[i].movie_hall - 1].column[j];
						}
					}
					else
					{
						movie[i].backup.row[0] = 0;
						movie[i].backup.column[0] = 0;
					}
				}
			}
			LoadMovieRecord(movie_record);
			decision = false;
		}
		else if (confirms == "N")
			decision = false;
		else
			cout << "\t\t\tInvalid Input found" << endl;
	}
}

void Main_Menu(string Name)
{
	int i=143, j=143;
	system("Color 80");
	SetConsoleTextAttribute(console, i);
	cout << "\n\n\n\t\t\t" << string(121, char(61)) << "\n";
	cout << "\t\t\t=" << right << setw(121) << "=\n";
	cout << "\t\t\t=" << string(4, ' ') << string(20, char(126)) << string(20, ' ') << string(25, char(126)) << string(25, ' ') << string(19, char(126)) << string(5, ' ') << " = \n";
	cout << "\t\t\t=" << string(4, ' ') << "[";
	SetConsoleTextAttribute(console, i);
	cout << " 1. Movie Details ";
	SetConsoleTextAttribute(console, j);
	cout << "]" << string(20, ' ') << "[";
	SetConsoleTextAttribute(console, i);
	cout << " 2. Food and Beverages ";
	SetConsoleTextAttribute(console, j);
	cout << "]" << string(25, ' ') << "[";
	SetConsoleTextAttribute(console, i);
	cout << " 3. Purchase Now ";
	SetConsoleTextAttribute(console, j);
	cout << "]" << string(5, ' ') << " = \n";
	cout << "\t\t\t=" << string(4, ' ') << string(20, char(126)) << string(20, ' ') << string(25, char(126)) << string(25, ' ') << string(19, char(126)) << string(5, ' ') << " = \n";
	cout << "\t\t\t=" << right << setw(121) << "=\n";
	cout << "\t\t\t=" << string(24, ' ') << string(22, char(95)) << string(23, ' ') << string(25, char(95)) << string(24, ' ') << " = \n";
	cout << "\t\t\t=" << string(24, ' ') << "[";
	SetConsoleTextAttribute(console, i);
	cout << " 4. Membership Page ";
	SetConsoleTextAttribute(console, j);
	cout << "]" << string(23, ' ') << "[";
	SetConsoleTextAttribute(console, i);
	cout << " 5. Administrator Page ";
	SetConsoleTextAttribute(console, j);
	cout << "]" << string(24, ' ') << " = \n";
	cout << "\t\t\t=" << string(24, ' ') << string(20, char(126)) << string(25, ' ') << string(25, char(126)) << string(24, ' ') << " = \n";
	cout << "\t\t\t=" << right << setw(121) << "=\n";
	cout << "\t\t\t=" << string(50, ' ') << string(14, char(126)) << string(54, ' ') << " = \n";
	cout << "\t\t\t=" << string(50, ' ') << "[";
	SetConsoleTextAttribute(console, i);
	cout << " 5.   EXIT  ";
	SetConsoleTextAttribute(console, j);
	cout << "]" << string(54, ' ') << " = \n";
	cout << "\t\t\t=" << string(50, ' ') << string(14, char(126)) << string(54, ' ') << " = \n";
	cout << "\t\t\t" << string(121, char(61)) << "\n";
}

void ReadTextRecord(int record)
{
	ifstream infile;
	infile.open("Title.txt");
	if (infile.fail())
		cout << "unable to open the file" << endl;
	else
	{
		while (!infile.eof())
		{
			for (int i = 0; i < 21; i++)
			{
				for (int j = 0; j < 7; j++)
				{
					getline(infile, text[i][j]);
				}
			}
		}
	}
}


void OpenMemberDetails(int& nomember)
{
	int i = 0;
	ifstream Ad_memberlist;
	Ad_memberlist.open("Admin_memberlist.txt");
	if (Ad_memberlist.is_open())
	{
		while (!Ad_memberlist.eof())
		{
			getline(Ad_memberlist, Member[i].Details_user);
			getline(Ad_memberlist, Member[i].Details_password);
			getline(Ad_memberlist, Member[i].Details_name);
			getline(Ad_memberlist, Member[i].Details_status);
			getline(Ad_memberlist, Member[i].Details_join);
			getline(Ad_memberlist, Member[i].Details_point);
			getline(Ad_memberlist, Member[i].Details_phone);
			getline(Ad_memberlist, Member[i].Details_email);
			i++;
			nomember = i;
		}
	}
	else
		cout << "Please contact admin for further assistance..." << endl;
	Ad_memberlist.close();
	
}