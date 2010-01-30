/* 
 * File:   SingleWord.h
 * Author: godlark
 *
 * Created on 18 grudzień 2009, 17:03
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
        vector<unsigned int*> lastRepetitionsOfM;
        unsigned int time_lastud; //data ostatniego użycia
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
        unsigned int getTime_lastud() const;
        ushort getHralev() const;
        ushort getOplev() const;
        SingleWord * getMeaning(ushort number) const;
        ushort getNumberMeanings() const;
        unsigned int getTimeLastRepetition(ushort number_meaning) const;
        unsigned int getTimeNextRepetition(ushort number_meaning, vector<unsigned int> repetitionsTime) const;
        ushort getWhichRepetition(ushort number_meaning) const;
        void setWhichRepetition(ushort number_meaning, ushort which_repetition) const;
        void setTimeLastRepetition(ushort number_meaning, unsigned int lasttime);
        
        void setSound(string Asound);
        void setSpelling(string Aspelling);
        void setTime_lastud(unsigned int time_lastud);
        void setHralev(int hralev);
        void setOplev(ushort oplev);
        void setOplev(time_t nowTime);
        
        SingleWord(const string Aspelling, const string Asound);
        static SingleWord newSingleWord(string spelling, string sound);
        SingleWord() {}
        SingleWord(SingleWord const *sw);
        
        static bool connectSingleWords(SingleWord *sw1, SingleWord *sw2, ushort which_repetition, unsigned int last_repetition);
        static bool disconnectSingleWords(SingleWord *sw1, SingleWord *sw2);//powiadamianie o pustych słowach
	static const ushort MAX_OPLEV = 1000;
	static const ushort MAX_HRALEV = 1000;
	static const ushort MIN_OPLEV = 0;
	static const ushort MIN_HRALEV = 1;
};

#endif	/* _SINGLEWORD_H */

