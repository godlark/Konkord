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

#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include "SingleWord.hpp"

typedef unsigned short int ushort;

struct Variable {
	ushort type; //0- string, ushort - 1
	union {
		ushort _ushort;
		std::string *_string;
	};
};

struct Variables {
	Variable *v;
	ushort number;
};

class Interface {
	public:
		virtual std::string askWord(SingleWord const *sword, ushort nr_word) = 0;//nr_lang = 0 lub = 1
		virtual void printWords(std::string description, SingleWord const **swords, ushort const *numbersWords, std::vector<ushort> numbersConnections, short time) = 0;
		virtual Variable dialogWindow(std::string text, ushort type) = 0;
		virtual void infoWindow(std::string const *descriptions, Variable *values, ushort number) = 0;
		virtual ushort radioWindow(std::string description, std::string const *values, ushort defaultOption, ushort number) = 0;
		virtual char Yes_No_Cancel(std::string description) = 0;
		virtual Variables optionWindow(std::string const *descriptions, Variable *values, ushort number) = 0;
		virtual void printMessage(std::string title, std::string something) = 0;
		virtual void run() = 0;
	protected:
		Interface() {}
};

#endif //_INTERFACE_H_
