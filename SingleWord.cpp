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

#include "SingleWord.hpp"

#include <cmath>
#include <ctime>

typedef unsigned short int ushort;
using namespace std;

SingleWord::~SingleWord() {
}
SingleWord::SingleWord(const string &Aspelling, const string &Asound) {
	spelling = Aspelling;
	sound = Asound;
	q_meanings = 0;
	known = false;
	meanings = vector<SingleWord *>(0);
	repetitionsOfMeanings = vector<ushort*>(0);
	lastRepetitionsOfM = vector<time_t*>(0);
	flag_names = vector<string>(0);
	flags = vector<string>(0);
}
SingleWord::SingleWord(SingleWord const *sw) {
	spelling = sw->spelling;
	sound = sw->sound;
	q_meanings = sw->q_meanings;
	meanings = vector<SingleWord*>(sw->meanings); // czy napewno skopiuje wektor
	lastRepetitionsOfM = vector<time_t*>(sw->lastRepetitionsOfM);
	repetitionsOfMeanings = vector<ushort*>(sw->repetitionsOfMeanings);
	flag_names = sw->flag_names;
	flags = sw->flags;
}
void SingleWord::setTimeLastRepetition(const ushort &number_meaning, const time_t &lasttime) {
	if(number_meaning >= q_meanings)throw Error::newError(Error::BAD_ARGUMENT, "", __LINE__, __FILE__);
	
	//veryfying correctness data
	const time_t nowTime = time(NULL);
	if(lasttime > nowTime)*lastRepetitionsOfM[number_meaning] = nowTime;
	else *lastRepetitionsOfM[number_meaning] = lasttime;
	
	known = (known || lasttime != 0);
	meanings[number_meaning]->known = (meanings[number_meaning]->known || lasttime != 0);
}
bool SingleWord::isKnown() const{
	return known;
}
ushort SingleWord::getWhichRepetition(const ushort &number_meaning) const {
	if(number_meaning >= q_meanings)throw Error::newError(Error::BAD_ARGUMENT, "", __LINE__, __FILE__);
	return *repetitionsOfMeanings[number_meaning];
}
void SingleWord::setWhichRepetition(const ushort &number_meaning, const ushort &which_repetition) const {
	if(number_meaning >= q_meanings)throw Error::newError(Error::BAD_ARGUMENT, "", __LINE__, __FILE__);
	*repetitionsOfMeanings[number_meaning] = which_repetition;
}
time_t SingleWord::getTimeLastRepetition(const ushort &number_meaning) const {
	if(number_meaning >= q_meanings)throw Error::newError(Error::BAD_ARGUMENT, "", __LINE__, __FILE__);
	return *lastRepetitionsOfM[number_meaning];
}
time_t SingleWord::getTimeNextRepetition(const ushort &number_meaning, const vector<time_t> &repetitionsTime) const {
	if(number_meaning >= q_meanings)throw Error::newError(Error::BAD_ARGUMENT, "", __LINE__, __FILE__);
	if(*repetitionsOfMeanings[number_meaning] >= repetitionsTime.size())throw Error::newError(Error::BAD_ARGUMENT, "", __LINE__, __FILE__);
	return *lastRepetitionsOfM[number_meaning] + repetitionsTime[*repetitionsOfMeanings[number_meaning]];
}
bool SingleWord::connectSingleWords(SingleWord *sw1, SingleWord *sw2, const ushort &which_repetition, const time_t &last_repetition, int which_repetition2) {//zmienić kolejność argumentów
	if(which_repetition2 == -1)which_repetition2 = which_repetition;
		
	if(!sw1->isConnectedWith(sw2)) {
		int temp1 = sw1->meanings.size();
		sw1->meanings.push_back(sw2);
		sw1->repetitionsOfMeanings.push_back(NULL);
		sw1->repetitionsOfMeanings[temp1] = new ushort;
		*(sw1->repetitionsOfMeanings[temp1]) = which_repetition;
		sw1->lastRepetitionsOfM.push_back(NULL);

		sw1->lastRepetitionsOfM[temp1] = new time_t;
		time_t nowTime = time(NULL);
		if(last_repetition >= nowTime) *(sw1->lastRepetitionsOfM[temp1]) = nowTime;
		else *(sw1->lastRepetitionsOfM[temp1]) =  last_repetition;

		sw1->q_meanings++;
		sw1->known = (sw1->known || last_repetition != 0);
		int temp2 = sw2->meanings.size();
		sw2->meanings.push_back(sw1);
		sw2->repetitionsOfMeanings.push_back(NULL);
		sw2->repetitionsOfMeanings[temp2] = new ushort;
		*(sw2->repetitionsOfMeanings[temp2]) = (ushort)which_repetition2;//niewspólna cecha dla dwóch słów
		sw2->lastRepetitionsOfM.push_back(NULL); 
		sw2->lastRepetitionsOfM[temp2] = sw1->lastRepetitionsOfM[temp1];//wspólna cecha dwa dwóch słów
		sw2->q_meanings++;
		sw2->known = (sw2->known || last_repetition != 0);
		return true;
	}
	else return false;
}
void SingleWord::deleteAllMeanings() {
	int inSW2;
	for(int i = q_meanings-1; i >= 0; i--) {
		inSW2 = meanings[i]->findMeaning(this);
		meanings[i]->meanings.erase(meanings[i]->meanings.begin()+inSW2);
		meanings[i]->q_meanings--;

		delete repetitionsOfMeanings[i];
		repetitionsOfMeanings.pop_back();
		delete meanings[i]->repetitionsOfMeanings[inSW2];
		meanings[i]->repetitionsOfMeanings.erase(meanings[i]->repetitionsOfMeanings.begin()+inSW2);

		delete lastRepetitionsOfM[i];
		lastRepetitionsOfM.pop_back();
		meanings[i]->lastRepetitionsOfM.erase(meanings[i]->lastRepetitionsOfM.begin()+inSW2);
		
		for(int j = 0; j < meanings[i]->q_meanings; j++) {
			meanings[i]->known = (meanings[i]->lastRepetitionsOfM[j] != 0 || meanings[i]->known);
		}
		meanings.pop_back();
	}
	q_meanings = 0;
	known = false;
}
bool SingleWord::disconnectSingleWords(SingleWord* sw1, SingleWord* sw2) {
	int inSW1 = sw1->findMeaning(sw2);
	int inSW2 = sw2->findMeaning(sw1);
	if(inSW1 != -1) {
		sw1->meanings.erase(sw1->meanings.begin()+inSW1);
		delete sw1->repetitionsOfMeanings[inSW1];
		delete sw1->lastRepetitionsOfM[inSW1];
		sw1->repetitionsOfMeanings.erase(sw1->repetitionsOfMeanings.begin()+inSW1);
		sw1->lastRepetitionsOfM.erase(sw1->lastRepetitionsOfM.begin()+inSW1);
		sw1->q_meanings--;
		for(int i = 0; i < sw1->q_meanings; i++) {
			sw1->known = (sw1->lastRepetitionsOfM[i] != 0 || sw1->known);
		}
		delete sw2->repetitionsOfMeanings[inSW2];
		sw2->meanings.erase(sw2->meanings.begin()+inSW2);
		sw2->repetitionsOfMeanings.erase(sw2->repetitionsOfMeanings.begin()+inSW2);
		sw2->lastRepetitionsOfM.erase(sw2->lastRepetitionsOfM.begin()+inSW2);
		sw2->q_meanings--;
		for(int i = 0; i < sw2->q_meanings; i++) {
			sw2->known = (sw2->lastRepetitionsOfM[i] != 0 || sw2->known);
		}
		return true;
	}
	else return false;
}
bool SingleWord::isEmpty() const{
	return q_meanings == 0 ? true : false;
}
bool SingleWord::isConnectedWith(SingleWord* meaning) const{
	for(ushort i = 0; i < q_meanings; i++){
		if(meaning == meanings[i])return true;
	}
	return false;
}
void SingleWord::joinOtherSingleWord(SingleWord* sword) {
	for(ushort i = 0; i < sword->q_meanings; i++) {
		if(isConnectedWith(sword->meanings[i]))continue;
		else connectSingleWords(this, sword, 0, 0);
	}
}
int SingleWord::findMeaning(SingleWord *meaning) const{
	for(ushort i = 0; i < q_meanings; i++){
		if(meaning == meanings[i])return i;
	}
	return -1;
}
string SingleWord::getSound() const{
	return sound;
}
string SingleWord::getSpelling() const{
	return spelling;
}
void SingleWord::setSound(const string &Asound) {
	sound = Asound;
}
void SingleWord::setSpelling(const string &Aspelling) {
	spelling = Aspelling;
}
SingleWord * SingleWord::getMeaning(const ushort &number) const {
	if(number >= q_meanings)throw Error::newError(Error::BAD_ARGUMENT, "", __LINE__, __FILE__);
	return meanings[number];
}
ushort SingleWord::getNumberMeanings() const {
	return q_meanings;
}
SingleWord SingleWord::newSingleWord(const string &spelling, const string &sound) {
	SingleWord neww(spelling, sound);
	return neww;
}

void SingleWord::setFlag(const string &flag_name, const string &flag) {
	flag_names.push_back(flag_name);
	flags.push_back(flag);
}
string SingleWord::getFlag(const string &flag_name) const {
	for(int i = 0; i < flag_names.size(); i++) {
		if(flag_names[i] == flag_name)return flags[i];
	}
	return "";
}
