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
#ifndef kurs_hpp
#define kurs_hpp

#include <cstdio>
#include <string>
#include <vector>
#include <ctime>
#include <queue>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <boost/regex.hpp>
#include <cmath>
#include <climits>

#include "RegisterOfErrors.h"
#include "SingleWord.h"

typedef unsigned short int ushort;
using namespace std;

class SingleWordAndIndex {
    public:
        ushort index;
        const SingleWord *sword;
};
class compareSingleWords
{
    public:
        bool operator() (SingleWordAndIndex swani1, SingleWordAndIndex swani2) {
            //rosnąco według oplev
            if(swani1.sword->getOplev() > swani2.sword->getOplev())return true;
            if(swani1.sword->getOplev() < swani2.sword->getOplev())return false;
            //malejąco według hralev
            if(swani1.sword->getHralev() < swani2.sword->getHralev())return true;
            if(swani1.sword->getHralev() > swani2.sword->getHralev())return false;
            //rosnąco według time_lastud
            if(swani1.sword->getTime_lastud() >= swani2.sword->getTime_lastud())return true;
            if(swani1.sword->getTime_lastud() < swani2.sword->getTime_lastud())return false;
        }
};
class ConnectionToRepetition {
    public :
        ushort nr_word;
        ushort nr_connection;
        unsigned int nextTimeOfRepetition;
};
class compareConnections {
    public:
        bool operator() (ConnectionToRepetition swani1, ConnectionToRepetition swani2) {
            //malejąco według nextTimeOfRepetition
            if(swani1.nextTimeOfRepetition < swani2.nextTimeOfRepetition)return true;
            if(swani1.nextTimeOfRepetition > swani2.nextTimeOfRepetition)return false;
        }
};
class Kurs
{
		private:
			string name;
			string lang1;
			string lang2;
			string filename;
                        vector<SingleWord*> wordl1;
                        vector<SingleWord*> wordl2;
                        vector<time_t> repetitionsTime; //in seconds
                        vector<unsigned int> repetitionsHowMany;
                        vector<double> repetitionsGrade;
                        ushort qAllSingleWords;
                        ushort qKnownSingleWords;
			ushort askQKW; //ilość przepytywanych znanych słów
			ushort askQNW;	//ilość przepytywanych nowych słów
			bool ifChangeKurs; //czy zmieniono kurs od ostatniego zapisania lub wczytania
			RegisterOfErrors *ROE;
                        ushort numberConnections;
			static ushort compare_words(string aa, string bb);//zwraca najkrótszą drogę pomiędzy słowami
			static string decode_text(string oryginal);
			static string encode_text(string oryginal);
                        void increaseQKnownSingleWords(short int quantity);
                        void repairRepetition(ushort which_repetition, double oplev_connection);
                        void setRepetitionForConnection(ushort nr_word, ushort nr_connection, double oplev_connection);
		public:
			Kurs(string file_to_open, RegisterOfErrors &_ROE);
			Kurs(const string &name, const string &lang1, const string &lang2, const string &filename, const ushort &askQKW, const ushort &askQNW,  RegisterOfErrors &_ROE);
                        void addSingleWords(const vector<string> &spellings, const vector<string> &sounds, const vector<string> &meanings_spelling, const vector<string> &meanings_sound);
                        void addSingleWord(const SingleWord &singleWord, ushort where);
                        void connectSingleWords(ushort number1, ushort number2);
                        void disconnectSingleWords(ushort number1, ushort number2);
                        void delSingleWord(ushort number);
                        vector<ushort> findWord(boost::regex searched_string) const;
                        vector<ushort> getKnownSingleWords(ushort quantityOfWords) const;
                        vector<ushort> getUnknownSingleWords(ushort quantityOfWords) const;
                        vector<ushort> getConnectionsToRepetition(ushort &howMany);
			string getName() const;
			string getLang1() const;
			string getLang2() const;
			string getFilename() const;
			void increaseQKnownWords(short int quantity);
			bool isKursChanged() const;
                        ushort getQAllSingleWords() const;
			ushort getQKnownSingleWords() const;
                        ushort getQSingleWords_1() const; //vector<SingleWord> wordl1;
                        ushort getQSingleWords_2() const; //vector<SingleWord> wordl1;
			ushort getAskQKW() const;
			ushort getAskQNW() const;
                        SingleWord const* getSingleWord(ushort number) const;
                        vector<SingleWord const*> getSingleWords(ushort from, ushort to) const;
                        void repairSingleWord_new(ushort word_number, time_t czas, vector<double> oplev_connections);
                        string readSingleWordsFromFile(string file_to_open);
			void saveKurs(string file_to_save); //zrobić na consta
			void setName(string _name);
			void setLang1(string _lang1);
			void setLang2(string _lang2);
			void setFilename(string _filename);
			void setIfChangeKurs(bool _ifChangeKurs);
			void setAskQKW(ushort _askQKW);
			void setAskQNW(ushort _askQNW);
			void setWord(ushort number, string first, string second);
                        void setSingleWord(ushort number, string spelling, string sound);
                        void unitSingleWords(ushort number1, ushort number2);
                        ~Kurs();
                        static void takeOutSWFromLine(vector<string> &spellings, vector<string> &sounds, string rest);
};
#endif