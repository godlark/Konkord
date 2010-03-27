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

#ifndef _SINGLEWORD_H
#define	_SINGLEWORD_H

#include <string>
#include <vector>
#include <ctime>
#include <cmath>
#include "RegisterOfErrors.h"

using namespace std;
typedef unsigned short int ushort;

class SingleWord {
	private:
		bool known;
		string sound;
		string spelling;
		vector<SingleWord*> meanings;
		vector<ushort*> repetitionsOfMeanings;
		vector<time_t*> lastRepetitionsOfM;
		time_t time_lastud; //data ostatniego użycia
		ushort hralev;//poziom trudności
		ushort oplev;//poziom opanowania
		ushort q_meanings;
	public:
		ushort id;
		bool isConnectedWith(SingleWord* meaning) const;
		bool isEmpty() const; 
		bool isKnown() const;
		int findMeaning(SingleWord* meaning) const;
		void deleteAllMeanings();
		void joinOtherSingleWord(SingleWord* sword); //zakładamy, że sound, spelling są takie same
		
		string getSound() const;
		string getSpelling() const;
		time_t getTime_lastud() const;
		ushort getHralev() const;
		ushort getOplev() const;
		SingleWord * getMeaning(ushort number) const;
		ushort getNumberMeanings() const;
		time_t getTimeLastRepetition(ushort number_meaning) const;
		time_t getTimeNextRepetition(ushort number_meaning, vector<time_t> repetitionsTime) const;
		ushort getWhichRepetition(ushort number_meaning) const;
		void setWhichRepetition(ushort number_meaning, ushort which_repetition) const;
		void setTimeLastRepetition(ushort number_meaning, time_t lasttime);
		
		void setSound(string Asound);
		void setSpelling(string Aspelling);
		void setTime_lastud(time_t time_lastud);
		void setHralev(int hralev);
		void setOplev(ushort oplev);
		void setOplev(time_t nowTime);
		
		SingleWord(const string Aspelling, const string Asound);
		static SingleWord newSingleWord(string spelling, string sound);
		SingleWord() {
			spelling = "";
			sound = "";
			oplev = MIN_OPLEV;
			hralev = MAX_HRALEV;
			q_meanings = 0;
			time_lastud = 0;
			known = false;
			meanings = vector<SingleWord *>(0);
			repetitionsOfMeanings = vector<ushort*>(0);
			lastRepetitionsOfM = vector<time_t*>(0);
		}
		SingleWord(SingleWord const *sw);
		
		static bool connectSingleWords(SingleWord *sw1, SingleWord *sw2, ushort which_repetition, time_t last_repetition);
		static bool disconnectSingleWords(SingleWord *sw1, SingleWord *sw2);//powiadamianie o pustych słowach
	static const ushort MAX_OPLEV = 1000;
	static const ushort MAX_HRALEV = 1000;
	static const ushort MIN_OPLEV = 0;
	static const ushort MIN_HRALEV = 1;
};

#endif	/* _SINGLEWORD_H */
