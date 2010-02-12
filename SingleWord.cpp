/* 
 * File:   SingleWord.cpp
 * Author: godlark
 *
 * Created on 18 grudzień 2009, 17:07
 */

#include "SingleWord.h"
#include <iostream>

typedef unsigned short int ushort;
using namespace std;

SingleWord::SingleWord(const string Aspelling, const string Asound) {
    spelling = Aspelling;
    sound = Asound;
    oplev = MIN_OPLEV;
    hralev = MAX_HRALEV;
    q_meanings = 0;
    time_lastud = 0;
    known = false;
    meanings = vector<SingleWord *>(0);
    repetitionsOfMeanings = vector<ushort*>(0);
    lastRepetitionsOfM = vector<time_t*>(0);
}
SingleWord::SingleWord(SingleWord const *sw) {
    spelling = sw->spelling;
    sound = sw->sound;
    oplev = sw->oplev;
    hralev = sw->hralev;
    q_meanings = sw->q_meanings;
    time_lastud = sw->time_lastud;
    meanings = vector<SingleWord*>(sw->meanings); // czy napewno skopiuje wektor
    lastRepetitionsOfM = vector<time_t*>(sw->lastRepetitionsOfM);
    repetitionsOfMeanings = vector<ushort*>(sw->repetitionsOfMeanings);
}
void SingleWord::setTimeLastRepetition(ushort number_meaning, time_t lasttime) {
    if(number_meaning >= q_meanings)throw Error::newError(Error::BAD_ARGUMENT, "", __LINE__, __FILE__);
    *lastRepetitionsOfM[number_meaning] = lasttime;
    known = (known || lasttime != 0);
    meanings[number_meaning]->known = (meanings[number_meaning]->known || lasttime != 0);
}
bool SingleWord::isKnown() const{
    return known;
}
ushort SingleWord::getWhichRepetition(ushort number_meaning) const {
    if(number_meaning >= q_meanings)throw Error::newError(Error::BAD_ARGUMENT, "", __LINE__, __FILE__);
    return *repetitionsOfMeanings[number_meaning];
}
void SingleWord::setWhichRepetition(ushort number_meaning, ushort which_repetition) const {
    if(number_meaning >= q_meanings)throw Error::newError(Error::BAD_ARGUMENT, "", __LINE__, __FILE__);
    *repetitionsOfMeanings[number_meaning] = which_repetition;
}
time_t SingleWord::getTimeLastRepetition(ushort number_meaning) const {
    if(number_meaning >= q_meanings)throw Error::newError(Error::BAD_ARGUMENT, "", __LINE__, __FILE__);
    return *lastRepetitionsOfM[number_meaning];
}
time_t SingleWord::getTimeNextRepetition(ushort number_meaning, vector<time_t> repetitionsTime) const {
    if(number_meaning >= q_meanings)throw Error::newError(Error::BAD_ARGUMENT, "", __LINE__, __FILE__);
    if(*repetitionsOfMeanings[number_meaning] >= repetitionsTime.size())throw Error::newError(Error::BAD_ARGUMENT, "", __LINE__, __FILE__);
    return *lastRepetitionsOfM[number_meaning] + repetitionsTime[*repetitionsOfMeanings[number_meaning]];
}
bool SingleWord::connectSingleWords(SingleWord *sw1, SingleWord *sw2, ushort which_repetition, time_t last_repetition) {
    if(!sw1->isConnectedWith(sw2)) {
        int temp1 = sw1->meanings.size();
        sw1->meanings.push_back(sw2);
        sw1->repetitionsOfMeanings.push_back(NULL);
        sw1->repetitionsOfMeanings[temp1] = new ushort;
        *(sw1->repetitionsOfMeanings[temp1]) = which_repetition;
        sw1->lastRepetitionsOfM.push_back(NULL);
        sw1->lastRepetitionsOfM[temp1] = new time_t;
        *(sw1->lastRepetitionsOfM[temp1]) = last_repetition;
        sw1->q_meanings++;
        sw1->known = (sw1->known || last_repetition != 0);
        int temp2 = sw2->meanings.size();
        sw2->meanings.push_back(sw1);
        sw2->repetitionsOfMeanings.push_back(NULL);
        sw2->repetitionsOfMeanings[temp2] = sw1->repetitionsOfMeanings[temp1];
        sw2->lastRepetitionsOfM.push_back(NULL);
        sw2->lastRepetitionsOfM[temp2] = sw1->lastRepetitionsOfM[temp1];
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
ushort SingleWord::getHralev() const{
    return hralev;
}
ushort SingleWord::getOplev() const{
    return oplev;
}
time_t SingleWord::getTime_lastud() const{
    return time_lastud;
}
void SingleWord::setSound(string Asound) {
    sound = Asound;
}
void SingleWord::setSpelling(string Aspelling) {
    spelling = Aspelling;
}
void SingleWord::setHralev(int Ahralev)
{
	if(Ahralev > MAX_HRALEV)hralev = MAX_HRALEV;
	else if(Ahralev < MIN_HRALEV)hralev = MIN_HRALEV;
	else hralev = Ahralev;
}
void SingleWord::setOplev(ushort Aoplev)
{
	if(Aoplev > MAX_OPLEV)oplev = MAX_OPLEV;
	else if(Aoplev < MIN_OPLEV)oplev = MIN_OPLEV;
	else oplev = Aoplev;
}
void SingleWord::setOplev(time_t nowTime)
{
	unsigned int max_way_time = ceil((oplev*86400)/hralev);
	unsigned int way_time = (unsigned int)nowTime - time_lastud;
	ushort old_oplev = oplev;	
	if(way_time > max_way_time)way_time = max_way_time;	
	setOplev((ushort)(oplev-((way_time*hralev)/86400)));
	if(oplev != old_oplev)setTime_lastud(nowTime);
}
void SingleWord::setTime_lastud(time_t Atime_lastud)
{
	time_lastud = Atime_lastud;
}
SingleWord * SingleWord::getMeaning(ushort number) const {
    if(number >= q_meanings)throw Error::newError(Error::BAD_ARGUMENT, "", __LINE__, __FILE__);
    return meanings[number];
}
ushort SingleWord::getNumberMeanings() const {
    return q_meanings;
}
SingleWord SingleWord::newSingleWord(string spelling, string sound) {
    SingleWord neww(spelling, sound);
    return neww;
}