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

#ifndef _NAKLADKA2_H
#define	_NAKLADKA2_H

#include "engine.hpp"
#include "interface.hpp"
#include <string>
#include <vector>

typedef unsigned int uint;

class Menu
{
	private: 
		ServiceOfTasks* serviceOfTasks;
		Menu* submenus;
		const uint numberSubmenus;
		
		const std::vector<std::string> describesOptions;
		const std::vector<short int> numbersOfActions;
		/*numberOfAction[n] is for n-option in menu
		*number > 0 points to use function "bool ServiceOfTask::doAction(USI numberAction);"
		*number == 0 points to close menu
		*number < 0 points to open submenu
		**/
		const uint numberOptions;
		bool exitMenuISexitProgram;	
	public:
		Menu(uint numberO, std::vector<short int> numbersOA, std::vector<std::string> describesO, Menu* asubmenus, uint numberS, ServiceOfTasks *aSOT, bool emisp) : numberOptions(numberO), serviceOfTasks(aSOT), submenus(asubmenus), numbersOfActions(numbersOA), describesOptions(describesO), numberSubmenus(numberS), exitMenuISexitProgram(emisp) {}
		void open();
		void printOptions() const;
		short int scanfOption() const; //get 'n' number of option (from 0 to 'numberOptions') from user and return 'numberOfActions[n]' and 'n' is not correct return 'serviceOfTaks->freeNumber'
		//~Menu();
};

class Text_Interface : public Interface
{
	private:
		Menu *menu2;
		Menu *menu1;
		ServiceOfTasks *serviceOfTasks;
		
		std::vector<short int> numberOfActionsM1;
		std::vector<std::string> describesOptionsM1;
		std::vector<short int> numberOfActionsM2;
		std::vector<std::string> describesOptionsM2;
	public:
		Text_Interface();
		~Text_Interface();
		void run();
		std::string askWord(SingleWord const *sword, uint nr_word);//nr_lang = 0 lub = 1
		void printWords(std::string description, SingleWord const **swords, uint const *numbersWords, std::vector<uint> numbersConnections, short time);
		Variable dialogWindow(std::string text, uint type);
		void infoWindow(std::string const *descriptions, Variable *values, uint number);
		uint radioWindow(std::string description, std::string const *values, uint defaultOption, uint number);
		char Yes_No_Cancel(std::string description);
		Variables optionWindow(std::string const *descriptions, Variable *values, uint number);
		void printMessage(std::string title, std::string something);
};
#endif	/* _NAKLADKA2_H */

