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
#ifndef kurs_hpp
#define kurs_hpp

#include "RegisterOfErrors.hpp"
#include "SingleWord.hpp"

#include <boost/regex.hpp>
#include <string>
#include <vector>

typedef unsigned short int ushort;

class SingleWordAndIndex {
    public:
        ushort index;
        const SingleWord *sword;
};
class WordToRepetition {
    public :
        ushort nr_word;
		double priority;
};
class compareWords {
    public:
        bool operator() (WordToRepetition swani1, WordToRepetition swani2) {
            if(swani1.priority >= swani2.priority)return true;
            if(swani1.priority < swani2.priority)return false;
		}
};
class Kurs
{
	private:
		std::string name;
		std::string lang1;
		std::string lang2;
		std::string filename;
		SingleWord *emptyWord;
		std::vector<SingleWord*> wordl1;
		std::vector<SingleWord*> wordl2;
		
		std::vector<double*> new_repetitionsLevels;
		std::vector<time_t> new_repetitionsTime;
		std::vector<double> new_repetitionsAverageError;
		std::vector<unsigned int> new_repetitionsStabilization;
		
		ushort qAllSingleWords;
		ushort qKnownSingleWords;
		ushort askQKW; //ilość przepytywanych znanych słów
		ushort askQNW;	//ilość przepytywanych nowych słów
		bool ifChangeKurs; //czy zmieniono kurs od ostatniego zapisania lub wczytania
		RegisterOfErrors *ROE;
		ushort numberConnections;
		static ushort compare_words(const std::string &aa, const std::string &bb);//zwraca najkrótszą drogę pomiędzy słowami
		static std::string decode_text(const std::string &oryginal);
		static std::string encode_text(const std::string &oryginal);
		void increaseQKnownSingleWords(const short int &quantity);
		void repairRepetitionLevels(const ushort &which_repetition, const double &deviation, const int &parttime, const double& predicted_score);
		double *logs;
	public:
		Kurs(const std::string &file_to_open, RegisterOfErrors &_ROE);
		Kurs(const std::string &name, const std::string &lang1, const std::string &lang2, const std::string &filename, const ushort &askQKW, const ushort &askQNW,  RegisterOfErrors &_ROE);
		void addSingleWords(const std::vector<std::string> &spellings, const std::vector<std::string> &sounds, const std::vector<std::string> &meanings_spelling, const std::vector<std::string> &meanings_sound);
		void addSingleWord(const SingleWord &singleWord, const ushort &where);
		void connectSingleWords(const ushort &number1, const ushort &number2);
		void disconnectSingleWords(const ushort &number1, const ushort &number2);
		void delSingleWord(const ushort &number);
		std::vector<ushort> findWord(const boost::regex &searched_string) const;
		std::vector<ushort> getUnknownSingleWords(const ushort &quantityOfWords) const;
		std::vector<ushort>  getWordsToRepetition(ushort &howManyWords) const;
		std::string getName() const;
		std::string getLang1() const;
		std::string getLang2() const;
		std::string getFilename() const;
		void increaseQKnownWords(const short int &quantity);
		bool isKursChanged() const;
		ushort getQAllSingleWords() const;
		ushort getQKnownSingleWords() const;
		ushort getQSingleWords_1() const; //std::vector<SingleWord> wordl1;
		ushort getQSingleWords_2() const; //std::vector<SingleWord> wordl1;
		ushort getAskQKW() const;
		ushort getAskQNW() const;
		SingleWord const* getSingleWord(const ushort &number) const;
		std::vector<SingleWord const*> getSingleWords(const ushort &from, ushort &to) const;
		bool isSingleWordFLorSL(const ushort &word_number) const; //first_language - true, second_language - false
		void repairPredictions(const ushort &word_number, const time_t &czas, std::vector<double> &oplev_connections);
		std::string readSingleWordsFromFile(const std::string &file_to_open);
		void saveKurs(const std::string &file_to_save); //zrobić na consta
		void setName(const std::string &_name);
		void setLang1(const std::string &_lang1);
		void setLang2(const std::string &_lang2);
		void setFilename(const std::string &_filename);
		void setIfChangeKurs(const bool &_ifChangeKurs);
		void setAskQKW(const ushort &_askQKW);
		void setAskQNW(const ushort &_askQNW);
		void setWord(const ushort &number, const std::string &first, const std::string &second);
		void setSingleWord(const ushort &number, const std::string &spelling, const std::string &sound);
		void setMeaningForSingleWord(const ushort &number_word, const ushort &number_meaning, const std::string &spelling, const std::string &sound);
		void unitSingleWords(const ushort &number1, const ushort &number2);
		~Kurs();
		static void takeOutSWFromLine(std::vector<std::string> &spellings, std::vector<std::string> &sounds, const std::string &rest);
};

#endif
