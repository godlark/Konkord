/*
#################################################################################
#				Konkord 														#
#			Version 0.0.2009.04.19												#
#	This program was created for learning words									#
#	 		from different languages.											#
#																				#
#    Copyright(C) 2009 Sławomir Domagała										#
#																				#
#    This program is free software: you can redistribute it and/or modify		#
#    it under the terms of the GNU General Public License as published by		#
#    the Free Software Foundation, either version 3 of the License, or			#
#    (at your option) any later version.										#
#																				#
#    This program is distributed in the hope that it will be useful,			#
#    but WITHOUT ANY WARRANTY; without even the implied warranty of				#
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the				#
#    GNU General Public License for more details.								#
#																				#
#    You should have received a copy of the GNU General Public License			#
#    along with this program.  If not, see <http://www.gnu.org/licenses/>		#
#																				#
#    E-mail: godlark@gmail.com													#
#################################################################################		
*/
#ifndef RegisterOfErrors_hpp
#define REgisterOfErrors_hpp

#include <iostream>
#include "silnik.hpp"

using namespace std;

class Menu
{
	public:
		RegisterOfErrors globalROE;

		vector<Kurs*> kursy;
		Kurs *activ_kurs;
		short int nr_activ_kurs;
		USI QOK; //ilosc otwartych kursów

		USI ilosc_opcji_0; //ilość opcji w głównym menu
		string *tekst_opcji_0;
		bool *activ_opcji_0;
		USI ilosc_opcji_3; //ilość opcji w podmenu 3
		string *tekst_opcji_3;
		bool *activ_opcji_3;
		
		Menu();
		void at_error(Error &errorek, bool &local_variable_error, short int &local_variable_wybor);
		bool closeKurs(USI nr_kurs);
		void menu_3();
		void naucz_nowych();
		void newKurs();
		void openKurs();
		void printInfoKurs();
		void printOptions(string *&tekst_opcji, bool *&activ_opcji, USI ilosc_opcji);
		void przepytaj_ze_starych();
		void saveKurs(USI nr_kurs);
		void saveKursAs(USI nr_kurs);
		USI scanfOption(bool *&activ_opcji, USI ilosc_opcji);
		void settingsKurs();
		void switchKurs();
		void zaktualizuj_menu_3();
		void zaktualizuj_menu_0();
	private:
		void simple_closeKurs(USI nr_kurs);
};
#endif