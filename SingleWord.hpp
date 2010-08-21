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

#ifndef _SINGLEWORD_H
#define	_SINGLEWORD_H

#include "RegisterOfErrors.hpp"

#include <string>
#include <vector>

typedef unsigned short int ushort;

class SingleWord {
	private:
		bool known;
		std::string sound;
		std::string spelling;
		std::vector<SingleWord*> meanings;
		std::vector<ushort*> repetitionsOfMeanings;
		std::vector<time_t*> lastRepetitionsOfM;
		ushort q_meanings;
		std::vector<std::string> flag_names;
		std::vector<std::string> flags;
	public:
		ushort id;
		bool isConnectedWith(SingleWord* meaning) const;
		bool isEmpty() const; 
		bool isKnown() const;
		int findMeaning(SingleWord* meaning) const;
		void deleteAllMeanings();
		void joinOtherSingleWord(SingleWord* sword); //zakładamy, że sound, spelling są takie same
		
		std::string getSound() const;
		std::string getSpelling() const;
		SingleWord * getMeaning(const ushort &number) const;
		ushort getNumberMeanings() const;
		time_t getTimeLastRepetition(const ushort &number_meaning) const;
		time_t getTimeNextRepetition(const ushort &number_meaning, const std::vector<time_t> &repetitionsTime) const;
		ushort getWhichRepetition(const ushort &number_meaning) const;
		void setWhichRepetition(const ushort &number_meaning, const ushort &which_repetition) const;
		void setTimeLastRepetition(const ushort &number_meaning, const time_t &lasttime);
		
		void setSound(const std::string &Asound);
		void setSpelling(const std::string &Aspelling);

		void setFlag(const std::string &flag_name,const  std::string &flag);
		std::string getFlag(const std::string &flag_name) const;

		SingleWord(const std::string &Aspelling, const std::string &Asound);
		static SingleWord newSingleWord(const std::string &spelling, const std::string &sound);
		SingleWord() {
			spelling = "";
			sound = "";
			q_meanings = 0;
			known = false;
			meanings = std::vector<SingleWord *>(0);
			repetitionsOfMeanings = std::vector<ushort*>(0);
			lastRepetitionsOfM = std::vector<time_t*>(0);
			flag_names = std::vector<std::string>(0);
			flags = std::vector<std::string>(0);
		}
		SingleWord(SingleWord const *sw);
		~SingleWord();
		
		static bool connectSingleWords(SingleWord *sw1, SingleWord *sw2, const ushort &which_repetition, const time_t &last_repetition, int which_repetition2 = -1);
		static bool disconnectSingleWords(SingleWord *sw1, SingleWord *sw2);//powiadamianie o pustych słowach
};

#endif	/* _SINGLEWORD_H */
