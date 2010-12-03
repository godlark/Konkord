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

#ifndef _ENGINE_H
#define	_ENGINE_H

#include "RegisterOfErrors.hpp"
#include "kurs.hpp"
#include "interface.hpp"

#include <string>
#include <vector>
#include <iostream>

typedef unsigned short int ushort;

class ServiceOfTasks
{
	private:
		void simpleCloseCourse(ushort nr_course);
		short int activ_course;
		ushort QOK; //number opened courses
		std::vector<Kurs*> courses;
		std::vector<bool> saved_courses;
		static const ushort numberActions = 19;
		bool* actionActive;
		Interface *main_interface;
	public:
		static const ushort freeNumber = 4619;
		
		RegisterOfErrors globalROE;
		
		void repaskWords();//1
		void askUnknownWords();//2
		void closeKurs();//3
		void editWord();//4
		void deleteWord();//5
		void doAction(ushort number, std::string options = "");
		void connectWords();//6
		void disconnectWords();//7
		void addWord();//8
		void addWords();//9
		void newCourse();//10
		void openCourse(std::string filename);//11
		void printInfoCourse() const;//12
		void printWordss() const; //13
		void saveCourse();//14
		void saveCourseAs();//15
		void settingsCourse();//16
		void switchCourse();//17
		void readWordsFromFile();//18
		void findWords() const;//19
		bool isActionActive(ushort numberOfAction) const; //isn't done
		void setStateActions();
		ushort getNumberOpenedCourses() const;
		bool closeProgram();
		ServiceOfTasks(Interface *Amain_interface);
		~ServiceOfTasks() {
			delete [] actionActive;
		}
};

#endif	/* _ENGINE_H */

