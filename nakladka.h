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

#ifndef _NAKLADKA2_H
#define	_NAKLADKA2_H

#include "engine.h"
#include <iostream>

typedef unsigned short int ushort;

class Interface
{
	public:
		static string askWord(SingleWord const *sword, ushort nr_word);//nr_lang = 0 lub = 1
		static void printWords(string description, SingleWord const **swords, ushort const *numbersWords, vector<ushort> numbersConnections, short time);
		static Variable dialogWindow(string text, ushort type);
		static void infoWindow(string const *descriptions, Variable *values, ushort number);
		static ushort radioWindow(string description, string const *values, ushort defaultOption, ushort number);
		static char Yes_No_Cancel(string description);
		static Variables optionWindow(string const *descriptions, Variable *values, ushort number);
		static void printMessage(string title, string something);
};
class Menu
{
	private: 
		ServiceOfTasks* serviceOfTasks;
		Menu* submenus;
		const ushort numberSubmenus;
		
		string const* const describesOptions;
		short int const* const numbersOfActions; 
		/*numberOfAction[n] is for n-option in menu
		*number > 0 points to use function "bool ServiceOfTask::doAction(USI numberAction);"
		*number == 0 points to close menu
		*number < 0 points to open submenu
		**/
		const ushort numberOptions;
		bool exitMenuISexitProgram;
		
	public:
		Menu(ushort numberO, short int* numbersOA, string * describesO, Menu* asubmenus, ushort numberS, ServiceOfTasks *aSOT, bool emiep) : numberOptions(numberO), serviceOfTasks(aSOT), submenus(asubmenus), numbersOfActions(numbersOA), describesOptions(describesO), numberSubmenus(numberS), exitMenuISexitProgram(emiep) {}
		void open();
		void printOptions() const;
		short int scanfOption() const; //get 'n' number of option (from 0 to 'numberOptions') from user and return 'numberOfActions[n]' and 'n' is not correct return 'serviceOfTaks->freeNumber'
		//~Menu();
};
#endif	/* _NAKLADKA2_H */

