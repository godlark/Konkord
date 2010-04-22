/*
#################################################################################
#################################################################################
##	                 Konkord 												
##	          Version 0.0.2009.04.19																
##	This program was created for learning words						
##	         from different languages.											
##																				
##	Copyright(C) 2009 Sławomir Domagała											
##																				
##	This program is free software: you can redistribute it and/or modify		
##	it under the terms of the GNU General Public License as published by		
##	the Free Software Foundation, either version 3 of the License, or			
##	(at your option) any later version.											
##																				
##	This program is distributed in the hope that it will be useful,				
##	but WITHOUT ANY WARRANTY; without even the implied warranty of				
##	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the				
##	GNU General Public License for more details.								
##																				
##	You should have received a copy of the GNU General Public License			
##	along with this program.  If not, see <http://www.gnu.org/licenses/>
##																				
##	E-mail: E-mail: g_o_d_l_a_r_k / monkey / g_m_a_i_l / dot / c_o_m									
#################################################################################
#################################################################################	
*/
#include "nakladka.h"

typedef unsigned short int ushort;


string Interface::askWord(SingleWord const *sword, ushort nr_word) {
	system("clear");
	cout << "Numer słowa: " << nr_word << endl;
	cout << "Napisz znaczenia tego wyrażenia:\n\"" << sword->getSpelling() << "\"";
	string temp;
	getline(cin, temp);
	return temp;
}
void Interface::printMessage(string title, string something) {
	cout << "***" << title << "***" << endl;
	cout << something << endl;
}
void Interface::printWords(string description, SingleWord const *swords[], ushort const *numbersWords, vector<ushort> numbersConnections, short time) {
	cout << description << endl;
	SingleWord const *mean;
	ushort number_connections = numbersConnections.size()/2;
	for(ushort i = 0; i < number_connections; i++) {
		cout << "Numer słowa: " << numbersWords[numbersConnections[i*2]] << endl;
		mean = swords[numbersConnections[i*2]]->getMeaning(numbersConnections[(i*2)+1]);
		cout << swords[numbersConnections[i*2]]->getSpelling() << "\t\t" << mean->getSpelling() << endl;
		cout << "***" << endl;
	}
	if(time >= 0)sleep(time);
	else cin.get();
}

Variable Interface::dialogWindow(string text, ushort type) {
	Variable temp;
	temp.type = type;
	string teemp;
	cout << text << ": " << endl;
	bool repeat = true;
	while(repeat){
		switch(type) {
			case 0:
				getline(cin, teemp);
				temp._string = new string(teemp);
				break;
			case 1:
				cin >> temp._ushort;
				break;
		}
		if(cin.fail()) {
			cout << "\nNiepoprawne dane, wpisz jeszcze raz" << endl;
			cin.clear();
		}
		else repeat = false;
		if(type != 0)cin.ignore(INT_MAX, '\n');
	}
	return temp;
}

void Interface::infoWindow(string const *descriptions, Variable *values, ushort number) {
	for(ushort i = 0; i < number; i++) {
		cout << descriptions[i] << ": ";
		switch(values[i].type) {
			case 0:
				cout << *(values[i]._string) << endl;
				break;
			case 1:
				cout << values[i]._ushort << endl;
				break;
		}
	}
}

Variables Interface::optionWindow(string const *descriptions, Variable *values, ushort number) {
	ushort wybor = 0;
	Variables vs;
	vs.number = number;
	vs.v = values;
	do {
		string teemp;
		cout << "Opcje kursu to: " << endl;
		for(ushort i = 0; i < number; i++)
		{
			cout << i+1 << ". " << descriptions[i] << endl;
		}
		cout << "Aby zmienić opcję kursu, wpisz numer znajdujący się przy niej, jeśli nie chcesz zmienić już żadnej opcji wpisz '0'" << endl;
		cin >> wybor;
		cout << "Obecna wartość to: ";
		bool repeat = true;
		while(repeat){
			switch(values[wybor-1].type) {
				case 0:
					cout << *(values[wybor-1]._string) << endl;
					cout << "Podaj nową wartość: ";
					cin >> teemp;
					values[wybor-1]._string = new string(teemp);
					break;
				case 1:
					cout << values[wybor-1]._ushort << endl;
					cout << "Podaj nową wartość: ";
					cin >> values[wybor-1]._ushort;
					break;
			}
			if(cin.fail()) {
				cout << "\nNiepoprawne dane, wpisz jeszcze raz" << endl;
				cin.clear();
			}
			else repeat = false;
			if(values[wybor-1].type != 0)cin.ignore(INT_MAX, '\n');
		}
		
	}while(wybor != 0);
}

ushort Interface::radioWindow(string description, string const *values, ushort defaultOption, ushort number) {
	cout << description << endl;
	cout << "Kurs aktywny oznaczony jest gwiazdką" << endl;
	for(ushort i = 0; i < number; i++) {
		if(i == defaultOption)cout << "*";
		cout << i << ". " << values[i] << endl;
	}
	cout << "Wpisz numer opcji, którą wybierasz: ";
	ushort temp;
	bool repeat = true;
	while(repeat){
		cin >> temp;
		if(cin.fail()) {
		  cout << "\nNiepoprawne dane, wpisz jeszcze raz" << endl;
		  cin.clear();
		}
		else repeat = false;
		cin.ignore(INT_MAX, '\n');
	}
	return temp;
}

char Interface::Yes_No_Cancel(string description)
{
	char znak;
	cout << description << endl;
	cout << "Tak(T)" << endl;
	cout << "Nie(N)\tAnuluj(A)" << endl;
	bool repeat = true;
	while(repeat){
		cin >> znak;
		if(cin.fail()) {
		  cout << "\nNiepoprawne dane, wpisz jeszcze raz" << endl;
		  cin.clear();
		}
		else repeat = false;
		cin.ignore(INT_MAX, '\n');
	}
	if(znak == 'T')return 1;
	if(znak == 'N')return 0;
	else return 2;
}

/*Menu::Menu(ushort numberO, short int* numbersOA, string * describesO, Menu* asubmenus, ushort numberS, ServiceOfTasks *aSOT) {
	numberOptions = numberO;
	numberOfActions = numbersOA;
	describesOptions = describesO;
	submenus = asubmenus;
	numberSubmenus = numberS;
	serviceOfTasks = aSOT;
}*/
void Menu::printOptions() const
{
	printf("Aby wybrać opcję, wpisz numer, który znajduje się przy niej. Jeśli przed opcją jest \'#\' to opcja jest nieaktywna.\n");
	for(int i = 0; i < numberOptions; i++)
	{
		if(numbersOfActions[i] > 0 && !serviceOfTasks->isActionActive(numbersOfActions[i]))printf("%c ", '#');
		printf("%hu %s\n", i, describesOptions[i].c_str());
	}
}
short int Menu::scanfOption() const
{
	ushort wybor;
	bool repeat = true;
	while(repeat){
		cin >> wybor;
		if(cin.fail()) {
		  cout << "\nNiepoprawne dane, wpisz jeszcze raz" << endl;
		  cin.clear();
		}
		else repeat = false;
		cin.ignore(INT_MAX, '\n');
	}
	if(wybor >= numberOptions || (numbersOfActions[wybor] > 0 && !serviceOfTasks->isActionActive(numbersOfActions[wybor])))return serviceOfTasks->freeNumber; //oznacza, że nieprawidłowe
	else return numbersOfActions[wybor];
}
void Menu::open()
{
	short int temp;
	bool fix = false;
	do
	{
		system("clear");
		if(!fix) {
			printOptions();
			temp = scanfOption();
			if(temp == serviceOfTasks->freeNumber)printf("Zły numer opcji lub opcja w danej chwili jest nieaktywna.\n");
		}
		if(temp == 0) {
			if(exitMenuISexitProgram) {
				if(!serviceOfTasks->closeProgram())temp = serviceOfTasks->freeNumber;
			}
		}
		else if(temp > 0) {
			try {
				serviceOfTasks->doAction(temp);
			}
			catch(Error &errorek) {
				
			}
		}
		else if(temp < 0)submenus[(temp*(-1))-1].open();
	}while(temp != 0);
}
/*Menu::~Menu() {
	delete serviceOfTasks;
	delete [] submenus;
	delete [] describesOptions;
	delete [] numbersOfActions;
}*/
