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


#define _GLIBCXX_DEBUG_PEDANTIC 1
#include "nakladka.h"
#include "engine.h"

using namespace std;
typedef unsigned short int ushort;
extern string* Error::DescriptionOfErrors;

int main() {
	Error::setDescriptionOfErrors();
	ServiceOfTasks *serviceOfTasks = new ServiceOfTasks;
	serviceOfTasks->askWord = &(Interface::askWord);
	serviceOfTasks->printWords = &Interface::printWords;
	serviceOfTasks->dialogWindow = &Interface::dialogWindow;
	serviceOfTasks->Yes_No_Cancel = &Interface::Yes_No_Cancel;
	serviceOfTasks->printMessage = &Interface::printMessage;
	serviceOfTasks->infoWindow = &Interface::infoWindow;
	serviceOfTasks->optionWindow = &Interface::optionWindow;
	serviceOfTasks->radioWindow = &Interface::radioWindow;
	ushort numberOptionsM1 = 14;
	short int *numberOfActionsM1 = new short int[numberOptionsM1];
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
	string *describesOptionsM1 = new string[numberOptionsM1];
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
	Menu *menu1 = new Menu(numberOptionsM1, numberOfActionsM1, describesOptionsM1, NULL, 0, serviceOfTasks, false);
	ushort numberOptionsM2 = 8;
	short int *numberOfActionsM2 = new short int[numberOptionsM2];
	numberOfActionsM2[0] = 3;
	numberOfActionsM2[1] = 10;
	numberOfActionsM2[2] = 11;
	numberOfActionsM2[3] = 14;
	numberOfActionsM2[4] = 15;
	numberOfActionsM2[5] = 17;
  	numberOfActionsM2[6] = -1;
	numberOfActionsM2[7] = 0;
	string *describesOptionsM2 = new string[numberOptionsM2];
	describesOptionsM2[0] = "Zamknij kurs";
	describesOptionsM2[1] = "Nowy kurs";
	describesOptionsM2[2] = "Otwórz kurs";
	describesOptionsM2[3] = "Zapisz kurs";
	describesOptionsM2[4] = "Zapisz jako...";
	describesOptionsM2[5] = "Przełącz kurs";
	describesOptionsM2[6] = "Podmenu Kurs->";
	describesOptionsM2[7] = "Zamknij program";
	Menu *menu2 = new Menu(numberOptionsM2, numberOfActionsM2, describesOptionsM2, menu1, 1, serviceOfTasks, true);
	menu2->open();
	delete menu2;
	delete [] numberOfActionsM2;
	delete [] describesOptionsM2;
	delete menu1;
	delete [] numberOfActionsM1;
	delete [] describesOptionsM1;
	delete serviceOfTasks;
	Error::eraseDerscriptionOfErros();
}
