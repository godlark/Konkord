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

#include "RegisterOfErrors.hpp"

class SingleWord
{
    string sound;
    string spelling;
};
class Word
{
	private:
		string first;
		string second;
		unsigned int time_lastud;//data ostataniego użycia
		USI hralev; //poziom trudności
		USI oplev;//poziom opanowania
	public:
		string getFirst() const;
		string getSecond() const;
		unsigned int getTime_lastud() const;
		USI getHralev() const;
		USI getOplev() const;
		void setFirst(string first);
		void setSecond(string second);
		void setTime_lastud(unsigned int time_lastud);
		void setHralev(int hralev);
		void setOplev(USI oplev);
		void setOplev(time_t nowTime);
		Word(string first, string second);
		Word();
		static Word newWord(string first, string second);//trzeba to wykorzystać, świeżo dodana funkcja
		friend istream &operator >>(istream&, Word&);
		static const USI MAX_OPLEV = 1000;
		static const USI MAX_HRALEV = 1000;
		static const USI MIN_OPLEV = 0;
		static const USI MIN_HRALEV = 1;
};
class WordAndNumber
{
	public:
		USI number;
		const Word *slowo;
};
class compareWord
{
	public:
		bool operator() (WordAndNumber wan1, WordAndNumber wan2)
		{
			//rosnąco według oplev
			if(wan1.slowo->getOplev() > wan2.slowo->getOplev())return true;
			if(wan1.slowo->getOplev() < wan2.slowo->getOplev())return false;
			//malejąco według hralev
			if(wan1.slowo->getHralev() < wan2.slowo->getHralev())return true;
			if(wan1.slowo->getHralev() > wan2.slowo->getHralev())return false;
			//rosnąco według time_lastud
			if(wan1.slowo->getTime_lastud() >= wan2.slowo->getTime_lastud())return true;
			if(wan1.slowo->getTime_lastud() < wan2.slowo->getTime_lastud())return false;
		}
};
class Kurs
{
		private:
			string name;
			string lang1;
			string lang2;
			string filename;
			vector<Word> words;
			USI qAllWords;//ilość ...
			USI qKnownWords; //ilość ...
			USI askQKW; //ilość przepytywanych znanych słów
			USI askQNW;	//ilość przepytywanych nowych słów
			bool ifChangeKurs; //czy zmieniono kurs od ostatniego zapisania lub wczytania
			RegisterOfErrors *ROE;
			static USI compare_words(string aa, string bb);//zwraca najkrótszą drogę pomiędzy słowami
			static string decode_text(string oryginal);
			static string encode_text(string oryginal);
		public:
			Kurs(string file_to_open, RegisterOfErrors &_ROE);
			Kurs(const string &name, const string &lang1, const string &lang2, const string &filename, const USI &askQKW, const USI &askQNW,  RegisterOfErrors &_ROE);
			void addWord(string first, string second);
			void addWord(Word &word);
			void aktualizuj();
			void delWord(USI number);
			vector<USI> findWord(boost::regex searched_string) const;
			vector<USI> getKnownWords(USI quantityOfWords) const;
			vector<USI> getUnknownWords(USI quantityOfWords) const;
			string getName() const;
			string getLang1() const;
			string getLang2() const;
			string getFilename() const;
			void increaseQKnownWords(short int quantity);
			bool isKursChanged() const;
			USI getQAllWords() const;
			USI getQKnownWords() const;
			USI getAskQKW() const;
			USI getAskQNW() const;
			Word getWord(USI number) const;
			vector<Word> getWords(USI &from, USI &_to) const;
			void repairWord(USI numberOfWords, USI krakl, double czas, double oplev);
			void readWordsFromFile(string file_to_open);
			void saveKurs(string file_to_save); //zrobić na consta
			void setName(string _name);
			void setLang1(string _lang1);
			void setLang2(string _lang2);
			void setFilename(string _filename);
			void setIfChangeKurs(bool _ifChangeKurs);
			void setAskQKW(USI _askQKW);
			void setAskQNW(USI _askQNW);
			void setWord(USI number, string first, string second);
};
#endif
