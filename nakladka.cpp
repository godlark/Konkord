/*				Konkord 
 *		    Version 0.0.2009.04.19
 *	This program was created for learning words
 *		    from different languages.
 *    Copyright(C) 2009 Sławomir Domagała	
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *																			
 * This program is distributed in the hope that it will be useful,				
 * but WITHOUT ANY WARRANTY; without even the implied warranty of				
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the				
 * GNU General Public License for more details.								
 *																			
 * You should have received a copy of the GNU General Public License			
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 *																				
 * E-mail: E-mail: g_o_d_l_a_r_k / monkey / g_m_a_i_l / dot / c_o_m									
 */
#include "nakladka.hpp"
#include <iostream>

using namespace std;
typedef unsigned short int ushort;

Text_Interface::~Text_Interface() {
	delete menu2;
	delete menu1;
}

Text_Interface::Text_Interface() {
	serviceOfTasks = new ServiceOfTasks(this);
	
	int numberOptionsM1 = 14;
	numberOfActionsM1 = vector<short int>(numberOptionsM1);
	numberOfActionsM1[0] = 1;
	numberOfActionsM1[1] = 2;
	numberOfActionsM1[2] = 4;
	numberOfActionsM1[3] = 5;
	numberOfActionsM1[4] = 6;
	numberOfActionsM1[5] = 7;
	numberOfActionsM1[6] = 8;
	numberOfActionsM1[7] = 9;
	numberOfActionsM1[8] = 12;
	numberOfActionsM1[9] = 13;
	numberOfActionsM1[10] = 16;
	numberOfActionsM1[11] = 18;
	numberOfActionsM1[12] = 19;
	numberOfActionsM1[13] = 0;
	describesOptionsM1 = vector<string>(numberOptionsM1);
	describesOptionsM1[0] = "Powtórz poznane słowa";
	describesOptionsM1[1] = "Naucz się nowych";
	describesOptionsM1[2] = "Edytuje słowo";
	describesOptionsM1[3] = "Usuń słowo";
	describesOptionsM1[4] = "Połącz słowa";
	describesOptionsM1[5] = "Rozłącz słowa";
	describesOptionsM1[6] = "Dodaj słowo";
	describesOptionsM1[7] = "Dodaj słowa";
	describesOptionsM1[8] = "Wyświetl informacje na temat kursu";
	describesOptionsM1[9] = "Wyświetl słowa";
	describesOptionsM1[10] = "Ustawienia kursu";
	describesOptionsM1[11] = "Wczytaj słowa z pliku";
	describesOptionsM1[12] = "Znajdź słowa";
	describesOptionsM1[13] = "Zamknij podmenu";
	menu1 = new Menu(numberOptionsM1, numberOfActionsM1, describesOptionsM1, NULL, 0, serviceOfTasks, false);
	int numberOptionsM2 = 8;
	numberOfActionsM2 = vector<short int>(numberOptionsM2);
	numberOfActionsM2[0] = 3;
	numberOfActionsM2[1] = 10;
	numberOfActionsM2[2] = 11;
	numberOfActionsM2[3] = 14;
	numberOfActionsM2[4] = 15;
	numberOfActionsM2[5] = 17;
  	numberOfActionsM2[6] = -1;
	numberOfActionsM2[7] = 0;
	describesOptionsM2 = vector<string>(numberOptionsM2);
	describesOptionsM2[0] = "Zamknij kurs";
	describesOptionsM2[1] = "Nowy kurs";
	describesOptionsM2[2] = "Otwórz kurs";
	describesOptionsM2[3] = "Zapisz kurs";
	describesOptionsM2[4] = "Zapisz jako...";
	describesOptionsM2[5] = "Przełącz kurs";
	describesOptionsM2[6] = "Podmenu Kurs->";
	describesOptionsM2[7] = "Zamknij program";
	menu2 = new Menu(numberOptionsM2, numberOfActionsM2, describesOptionsM2, menu1, 1, serviceOfTasks, true);
}

void Text_Interface::run() {
	menu2->open();
}

string Text_Interface::askWord(SingleWord const *sword, ushort nr_word) {
	system("clear");
	cout << "Numer słowa: " << nr_word << endl;
	cout << "Napisz znaczenia tego wyrażenia:\n\"" << sword->getSpelling() << "\"";
	string temp;
	getline(cin, temp);
	return temp;
}
void Text_Interface::printMessage(string title, string something) {
	cout << "***" << title << "***" << endl;
	cout << something << endl;
}
void Text_Interface::printWords(string description, SingleWord const *swords[], ushort const *numbersWords, vector<ushort> numbersConnections, short time) {
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

Variable Text_Interface::dialogWindow(string text, ushort type) {
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

void Text_Interface::infoWindow(string const *descriptions, Variable *values, ushort number) {
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

Variables Text_Interface::optionWindow(string const *descriptions, Variable *values, ushort number) {
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

ushort Text_Interface::radioWindow(string description, string const *values, ushort defaultOption, ushort number) {
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

char Text_Interface::Yes_No_Cancel(string description)
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

void Menu::printOptions() const
{
	cout << "Aby wybrać opcję, wpisz numer, który znajduje się przy niej. Jeśli przed opcją jest \'#\' to opcja jest nieaktywna." << endl;
	for(int i = 0; i < numberOptions; i++)
	{
		if(numbersOfActions[i] > 0 && !serviceOfTasks->isActionActive(numbersOfActions[i]))printf("%c ", '#');
		cout << i << " " << describesOptions[i] << endl;
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
			if(temp == serviceOfTasks->freeNumber)cout << "Zły numer opcji lub opcja w danej chwili jest nieaktywna." << endl;
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
