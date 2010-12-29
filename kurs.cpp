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
#include "kurs.hpp"

#include <cstdio>
#include <ctime>
#include <queue>
#include <stdlib.h>
#include <fstream>
#include <cmath>
#include <climits>
#include <algorithm>
#include <iostream>

using namespace std;
typedef unsigned short int ushort;

Kurs::~Kurs() {
	for(int i = 0; i < wordl1.size(); i++) {
		wordl1[i]->deleteAllMeanings();
		delete wordl1[i];
	}
	for(int i = 0; i < wordl2.size(); i++) {
		wordl2[i]->deleteAllMeanings();
		delete wordl2[i];
	}
	delete logs;
	delete emptyWord;
}
void Kurs::addSingleWords(const vector<string> &spellings, const vector<string> &sounds, const vector<string> &meanings_spelling, const vector<string> &meanings_sound) {
	SingleWord *tempsw;
	if(spellings.size() != sounds.size() || meanings_spelling.size() != meanings_sound.size())throw Error::newError(Error::BAD_ARGUMENT, "", __LINE__, __FILE__);
	for(ushort i = 0; i < spellings.size(); i++) {
		tempsw = new SingleWord(spellings[i], sounds[i]);
		wordl1.push_back(tempsw);
	}
	for(ushort i = 0; i < meanings_spelling.size(); i++) {
		tempsw = new SingleWord(meanings_spelling[i], meanings_sound[i]);
		wordl2.push_back(tempsw);
		for(ushort j = wordl1.size() - sounds.size(); j < wordl1.size(); j++) {
			if(SingleWord::connectSingleWords(wordl2[wordl2.size()-1], wordl1[j], 0, 0)) {//łączy ostatnio dodane słowo dodane do wordl2 z...
				numberConnections++;
			}
		}
	}
	qAllSingleWords = wordl1.size() + wordl2.size();
	ifChangeKurs = true;
}
void Kurs::addSingleWord(const SingleWord &singleWord, const ushort &where) {
	ushort number;
	if(where == 0) {
		wordl1.push_back(new SingleWord(&singleWord));
		number = wordl1.size()-1;
		SingleWord::connectSingleWords(wordl1[number], emptyWord, 0, 0);
	}
	else {
		wordl2.push_back(new SingleWord(&singleWord));
		number = wordl1.size() + wordl2.size() - 1;
		SingleWord::connectSingleWords(wordl2[number-wordl1.size()], emptyWord, 0, 0);
	}
	qAllSingleWords = wordl1.size() + wordl2.size();
	ifChangeKurs = true;
}
void Kurs::connectSingleWords(const ushort &number1, const ushort &number2) {
	if(number1 >= wordl1.size() || (number2 >= wordl1.size()+wordl2.size() || number2 < wordl1.size()))throw Error::newError(Error::BAD_ARGUMENT, "", __LINE__, __FILE__);
	if(SingleWord::connectSingleWords(wordl1[number1], wordl2[number2-wordl1.size()], 0, 0)) {
		numberConnections++;
		if(wordl1[number1]->getMeaning(0) == emptyWord)SingleWord::disconnectSingleWords(wordl1[number1], emptyWord);
		if(wordl2[number2-wordl1.size()]->getMeaning(0) == emptyWord)SingleWord::disconnectSingleWords(wordl2[number2-wordl1.size()], emptyWord);
		ifChangeKurs = true;
	}
	//else jakieś powiadomienie
}
void Kurs::disconnectSingleWords(const ushort &number1, const ushort &number2) {
	if(number1 >= wordl1.size() || (number2 >= wordl1.size()+wordl2.size() || number2 < wordl1.size()))throw Error::newError(Error::BAD_ARGUMENT, "", __LINE__, __FILE__);
	if(SingleWord::disconnectSingleWords(wordl1[number1], wordl2[number2-wordl1.size()])) {
		numberConnections--;
		if(wordl1[number1]->getNumberMeanings() == 0)SingleWord::connectSingleWords(wordl1[number1], emptyWord, 0, 0);
		if(wordl2[number2-wordl1.size()]->getNumberMeanings() == 0)SingleWord::connectSingleWords(wordl2[number2-wordl1.size()], emptyWord, 0, 0);
		ifChangeKurs = true;
	}
	//else jakieś powiadomienie
}
void Kurs::delSingleWord(const ushort &number) {
	ushort qAllMeanings;
	SingleWord* meaning;
	vector<SingleWord*>::iterator position;
	if(number < wordl1.size()) {
		qAllMeanings = wordl1[number]->getNumberMeanings();
		for(int i = 0; i < qAllMeanings; i++) {
			meaning = (wordl1[number]->getMeaning(i)); //znaczenia słowa z tablicy wordl1 jest w tablicy wordl2
			SingleWord::disconnectSingleWords(wordl1[number], meaning);
			if(meaning->getNumberMeanings() == 0) {
				SingleWord::connectSingleWords(meaning, emptyWord, 0, 0);
			}
			numberConnections--;
		}
		delete wordl1[number];
		wordl1.erase(wordl1.begin() + number);
	}
	else if(number < wordl1.size() + wordl2.size()) {
		qAllMeanings = wordl2[number-wordl1.size()]->getNumberMeanings();
		for(int i = 0; i < qAllMeanings; i++) {
			meaning = (wordl2[number-wordl1.size()]->getMeaning(i)); //znaczenia słowa z tablicy wordl1 jest w tablicy wordl2
			SingleWord::disconnectSingleWords(wordl2[number-wordl1.size()], meaning);
			if(meaning->getNumberMeanings() == 0) {
				SingleWord::connectSingleWords(meaning, emptyWord, 0, 0);
			}
			numberConnections--;
		}
		delete wordl2[number-wordl1.size()];
		wordl2.erase(wordl2.begin() + number-wordl1.size());
	}
	/*if(number < wordl1.size()) {
		wordl1[number]->deleteAllMeanings();
		if(wordl1[number]->isKnown())qKnownSingleWords--;
		delete wordl1[number];
		wordl1.erase(wordl1.begin() + number);
	}
	else if(number < wordl1.size() + wordl2.size()) {
		wordl2[number-wordl1.size()]->deleteAllMeanings();
		if(wordl2[number-wordl1.size()]->isKnown())qKnownSingleWords--;
		delete wordl2[number-wordl1.size()];
		wordl2.erase(wordl2.begin() + number-wordl1.size());
	}*/
	else throw Error::newError(Error::BAD_ARGUMENT, "", __LINE__, __FILE__);
	qAllSingleWords = wordl1.size() + wordl2.size();
	ifChangeKurs = true;
}
vector<ushort> Kurs::findWord(const boost::regex &searched_string) const {
	vector<ushort> found_words;
	for(ushort i = 0; i < wordl1.size(); i++) {   
		if(regex_match(wordl1[i]->getSpelling(), searched_string)) {
			found_words.push_back(i);
		}
	}
	for(ushort i = 0; i < wordl2.size(); i++) {
		if(regex_match(wordl2[i]->getSpelling(), searched_string)) {
			found_words.push_back(i+wordl1.size());
		}
	}
	return found_words;
}
vector<ushort> Kurs::getWordsToRepetition(ushort &howManyWords) const{
	//howManyWords jest liczbą słów do przepytania, rozmiar zwracanego vectora to liczba słów do przepytania i liczba połączeń do powtórzenia
	if(howManyWords > wordl1.size() + wordl2.size())howManyWords = wordl1.size() + wordl2.size();
	ushort AhowManyWords = 0;
	priority_queue<WordToRepetition, vector<WordToRepetition>, compareWords>Q;
	WordToRepetition wtr;
	time_t nowTime = time(NULL);
	//pobieranie słów z tablic i dodawanie ich do kolejki priorytetowej sortującej według zmiennej priority
	
	double parttime;
	double predicted_score;
	double divider;
	for(ushort i = 0; i < wordl1.size(); i++) {
		if(wordl1[i]->isConnectedWith(emptyWord) || !wordl1[i]->isKnown())continue; //ze słów pustych i nie poznanych nie można przeptywać
		
		ushort countConnections = wordl1[i]->getNumberMeanings();
		divider = 0;
		predicted_score = 0;
		parttime = 0;
		wtr.priority = 0;
		for(ushort j = 0; j < countConnections; j++) {
			parttime = (double)(nowTime-wordl1[i]->getTimeLastRepetition(j));
			parttime *= 1000;
			parttime /= (double)(new_repetitionsTime[wordl1[i]->getWhichRepetition(j)]);
			if(parttime > 1000)parttime = 1000;
		
			for(int k = 0; k < 11; k++) {
				predicted_score += new_repetitionsLevels[wordl1[i]->getWhichRepetition(j)][k]*logs[abs(k*10-(int)parttime/10)];
				divider += logs[abs(k*10-(int)parttime/10)];
			}
			predicted_score /= divider;
			wtr.priority += predicted_score;
		}
		wtr.priority /= countConnections;
		wtr.nr_word = i;
		if(wtr.priority < 700) {
			AhowManyWords++;
		}
		Q.push(wtr);
		
	}
	for(ushort i = 0; i < wordl2.size(); i++) {
		if(wordl2[i]->isConnectedWith(emptyWord) || !wordl2[i]->isKnown())continue; //ze słów pustych i nie poznanych nie można przeptywać
		
		ushort countConnections = wordl2[i]->getNumberMeanings();
		divider = 0;
		predicted_score = 0;
		parttime = 0;
		wtr.priority = 0;
		for(ushort j = 0; j < countConnections; j++) {
			parttime = (double)(nowTime-wordl2[i]->getTimeLastRepetition(j));
			parttime *= 1000;
			parttime /= (double)(new_repetitionsTime[wordl2[i]->getWhichRepetition(j)]);
			if(parttime > 1000)parttime = 1000;
		
			for(int k = 0; k < 11; k++) {
				predicted_score += new_repetitionsLevels[wordl2[i]->getWhichRepetition(j)][k]*logs[abs(k*10-(int)parttime/10)];
				divider += logs[abs(k*10-(int)parttime/10)];
			}
			predicted_score /= divider;
			wtr.priority += predicted_score;
		}
		wtr.priority /= countConnections;
		wtr.nr_word = i;
		if(wtr.priority < 700) {
			AhowManyWords++;
		}
		Q.push(wtr);
	}
	//koniec pobieranie słów z tablicy

	//1 liczba to ilość sugerowanych na następny dzień słów do przepytania
	vector<ushort> WordsToRepetition = vector<ushort>(0);
	WordsToRepetition.push_back(AhowManyWords);
	//słowa do przepytania i połączenia do powtórzenia
	vector<ushort> ConnectionsToRepetition = vector<ushort>(0);
	

	//pobieranie górnych słów z kolejki priorytetowej i dodawanie ich do WordsToRepetition
	//dodawanie połączeń tych słów do ConnectionsToRepetition
	for(ushort i = 0; i < howManyWords; i++) {
		WordsToRepetition.push_back(Q.top().nr_word);//dodaje słowo do przepytania
		SingleWord *sword;
		if(Q.top().nr_word < wordl1.size())sword = wordl1[Q.top().nr_word];
		else sword = wordl2[Q.top().nr_word-wordl1.size()];
		int whereInOther;
		for(ushort j = 0; j < sword->getNumberMeanings(); j++) {
			//zamiana liczby na string
			string s_number = "";
			int temp_j =  j;
			if(temp_j == 0)s_number = "0";
			while(temp_j != 0) {
				s_number = (char)(temp_j%10+(int)'0') + s_number;
				temp_j -= temp_j%10;
				temp_j /= 10;
			}
			//koniec zamiany liczby j na string
			if(sword->getFlag(s_number) == "use") {//jeśli połączenie zostało już dodanie do ConnectionsToRepetition to pomiń i usuń z przepytywanych
				WordsToRepetition.erase(WordsToRepetition.end()-1);
				i--;
				continue;
			}
			whereInOther = sword->getMeaning(j)->findMeaning(sword);
			//zamiana liczby whereInOther na string
			s_number = "";
			int temp_whereInOther =  whereInOther;
			if(temp_whereInOther == 0)s_number = "0";
			while(temp_whereInOther != 0) {
				s_number = (char)(temp_whereInOther%10+(int)'0') + s_number;
				temp_whereInOther -= temp_whereInOther%10;
				temp_whereInOther /= 10;
			}
			//koniec zamiany liczby whereInOther na string
			sword->getMeaning(j)->setFlag(s_number, "use");//ustawianie flagi, która informuje, że polączenie zostało już dodane
			ConnectionsToRepetition.push_back(Q.top().nr_word);//wstawianie nr_słowa
			ConnectionsToRepetition.push_back(j);//wstawianie nr_połączenia
		}
		Q.pop();
	}
	for(int i = 0; i < Q.size(); i++) {//usuwanie pozostałych elementów z kolejki
		Q.pop();
	}
	for(int i = 0; i < ConnectionsToRepetition.size(); i++) {
		WordsToRepetition.push_back(ConnectionsToRepetition[i]);
	}
	return WordsToRepetition;
}
vector<ushort> Kurs::getUnknownSingleWords(const ushort &quantityOfWords) const {
	//if(quantityOfWords > qAllWords - qKnownWords)quantityOfWords = qAllWords - qKnownWords;
	vector<ushort> wordsToAsk;
	time_t lasttime = time(NULL);
	for(ushort i = 0, j = 0; i < qAllSingleWords && j < quantityOfWords; i++) {
		if(i < wordl1.size()) {
			if(!wordl1[i]->isKnown() && !wordl1[i]->isConnectedWith(emptyWord)) {
				wordsToAsk.push_back(i);
				ushort number_connections = wordl1[i]->getNumberMeanings();
				for(ushort k = 0; k < number_connections; k++) {
					wordl1[i]->setTimeLastRepetition(k, lasttime);
				}
		j++;
			}
		}
		else {
			if(!wordl2[i-wordl1.size()]->isKnown() && !wordl2[i-wordl1.size()]->isConnectedWith(emptyWord)) {
				wordsToAsk.push_back(i);
				ushort number_connections = wordl2[i-wordl1.size()]->getNumberMeanings();
				for(ushort k = 0; k < number_connections; k++) {
					wordl2[i-wordl1.size()]->setTimeLastRepetition(k, lasttime);
				}
		j++;
			}
		}
	}
	return wordsToAsk;
}
ushort Kurs::getQAllSingleWords() const {
	return qAllSingleWords;
}
ushort Kurs::getQKnownSingleWords() const {
	return qKnownSingleWords;
}
ushort Kurs::getQSingleWords_1() const {
	return wordl1.size();
}
ushort Kurs::getQSingleWords_2() const {
	return wordl2.size();
}
SingleWord const* Kurs::getSingleWord(const ushort &number) const {
	if(number >= qAllSingleWords)throw Error::newError(Error::BAD_ARGUMENT, "", __LINE__, __FILE__);
	return number < wordl1.size() ? wordl1[number] : wordl2[number-wordl1.size()];
}
vector<SingleWord const*> Kurs::getSingleWords(const ushort &from, ushort &_to) const {
	vector<SingleWord const*> _words;
	if(from >= qAllSingleWords || _to >= qAllSingleWords)throw Error::newError(Error::BAD_ARGUMENT, "", __LINE__, __FILE__);
	else if(_to < from && _to != 0)throw Error::newError(Error::BAD_ARGUMENT, "", __LINE__, __FILE__);
	if(_to == 0)_to = qAllSingleWords;
	if(from < wordl1.size()) {
		if(_to < wordl1.size())_words.insert(_words.end(), wordl1.begin()+from, wordl1.begin()+_to);
		else {
			_words.insert(_words.end(), wordl1.begin()+from, wordl1.begin()+wordl1.size());
			_words.insert(_words.end(), wordl2.begin(), wordl2.begin()+(_to-wordl1.size()));
		}
	}
	else {
		_words.insert(_words.end(), wordl2.begin()+from-wordl1.size(), wordl2.begin()+_to-wordl1.size());
	}
	return _words;
}
bool Kurs::isSingleWordFLorSL(const ushort &word_number) const {
	return word_number < wordl1.size() ? true : false; //not sesne ist throw Error for word_number > qAllSingleWords
}
void Kurs::repairPredictions(const ushort &word_number, const time_t &czas, vector<double> &oplev_connections) {
	SingleWord *sword = word_number < wordl1.size() ? wordl1[word_number] : wordl2[word_number-wordl1.size()];
	double max_oplev = 20;
	if(oplev_connections.size() < sword->getNumberMeanings())throw Error::newError(Error::BAD_ARGUMENT, "", __LINE__, __FILE__);
	time_t nowTime = time(NULL);
	double parttime;
	double predicted_score;
	double divider;
	double deviation;
	double old10Level;
	for(ushort i = 0; i < sword->getNumberMeanings(); i++) {
		predicted_score = 0;
		parttime = 0;
		divider = 0;
		deviation = 0;
		
		if(oplev_connections[i] > max_oplev)oplev_connections[i] = max_oplev;
		oplev_connections[i] *= 1000/max_oplev;
		
		sword->setTimeLastRepetition(i, nowTime);
		
		parttime = (double)(nowTime-sword->getTimeLastRepetition(i));
		parttime *= 1000;
		parttime /= (double)(new_repetitionsTime[sword->getWhichRepetition(i)]);
		
		if(parttime > 1000) { //poprawić
			deviation = ((new_repetitionsLevels[sword->getWhichRepetition(i)][10] - oplev_connections[i])*1000)/new_repetitionsLevels[sword->getWhichRepetition(i)][10];
			if(abs(deviation) > new_repetitionsAverageError[sword->getWhichRepetition(i)]) {
				old10Level = new_repetitionsLevels[sword->getWhichRepetition(i)][10];
				new_repetitionsLevels[sword->getWhichRepetition(i)][10] = oplev_connections[i]*1000;
				new_repetitionsLevels[sword->getWhichRepetition(i)][10] /= 1000-new_repetitionsAverageError[sword->getWhichRepetition(i)];
				if(new_repetitionsLevels[sword->getWhichRepetition(i)][10] < 1)new_repetitionsLevels[sword->getWhichRepetition(i)][10] = 1;
				if(new_repetitionsLevels[sword->getWhichRepetition(i)][10] > 1000)new_repetitionsLevels[sword->getWhichRepetition(i)][10] = 1000;
				new_repetitionsTime[sword->getWhichRepetition(i)] += (nowTime-sword->getTimeLastRepetition(i)-sword->getWhichRepetition(i))*(old10Level-new_repetitionsLevels[sword->getWhichRepetition(i)][10])/(old10Level-oplev_connections[i]);
			}
			continue;
		}
		
		for(int j = 0; j < 11; j++) {
			predicted_score += new_repetitionsLevels[sword->getWhichRepetition(i)][j]*logs[abs(j*10-(int)parttime/10)];
			divider += logs[abs(j*10-(int)parttime/10)];
		}
		predicted_score /= divider;
				
		deviation = ((oplev_connections[i]-predicted_score)*1000)/predicted_score;
		if(abs(deviation) <= new_repetitionsAverageError[sword->getWhichRepetition(i)]) {
			new_repetitionsAverageError[sword->getWhichRepetition(i)] = new_repetitionsAverageError[sword->getWhichRepetition(i)] * new_repetitionsStabilization[sword->getWhichRepetition(i)] + abs(deviation);
			new_repetitionsAverageError[sword->getWhichRepetition(i)] /= new_repetitionsStabilization[sword->getWhichRepetition(i)]+1;
			new_repetitionsStabilization[sword->getWhichRepetition(i)]++;
		}
		else {
			new_repetitionsAverageError[sword->getWhichRepetition(i)] = new_repetitionsAverageError[sword->getWhichRepetition(i)] * (new_repetitionsStabilization[sword->getWhichRepetition(i)]-1) + new_repetitionsAverageError[sword->getWhichRepetition(i)] + (abs(deviation) - new_repetitionsAverageError[sword->getWhichRepetition(i)])/2;
			new_repetitionsAverageError[sword->getWhichRepetition(i)] /= new_repetitionsStabilization[sword->getWhichRepetition(i)];
			if(deviation > 0) {
				deviation -= new_repetitionsAverageError[sword->getWhichRepetition(i)];
			}
			else {
				deviation += new_repetitionsAverageError[sword->getWhichRepetition(i)];
			}
			repairRepetitionLevels(sword->getWhichRepetition(i), deviation, (int)parttime, predicted_score);
		}
		ushort repetition = sword->getWhichRepetition(i);
		if(deviation > 0) {
			repetition++;
			if(repetition == new_repetitionsTime.size()) {
				new_repetitionsLevels.push_back(NULL);
				new_repetitionsLevels[repetition] = new double[11];
				new_repetitionsLevels[repetition][0] = new_repetitionsLevels[repetition-1][0];
				new_repetitionsLevels[repetition][1] = new_repetitionsLevels[repetition-1][1];
				new_repetitionsLevels[repetition][2] = new_repetitionsLevels[repetition-1][2];
				new_repetitionsLevels[repetition][3] = new_repetitionsLevels[repetition-1][3];
				new_repetitionsLevels[repetition][4] = new_repetitionsLevels[repetition-1][4];
				new_repetitionsLevels[repetition][5] = new_repetitionsLevels[repetition-1][5];
				new_repetitionsLevels[repetition][6] = new_repetitionsLevels[repetition-1][6];
				new_repetitionsLevels[repetition][7] = new_repetitionsLevels[repetition-1][7];
				new_repetitionsLevels[repetition][8] = new_repetitionsLevels[repetition-1][8];
				new_repetitionsLevels[repetition][9] = new_repetitionsLevels[repetition-1][9];
				new_repetitionsLevels[repetition][10] = new_repetitionsLevels[repetition-1][10];
				new_repetitionsTime.push_back(new_repetitionsTime[repetition-1]);
				new_repetitionsAverageError.push_back(5.0);
				new_repetitionsStabilization.push_back(1);
			}
		}
		else {
			if(repetition != 0) {
				repetition--;
			}
		}
		sword->setWhichRepetition(i, repetition);
	}
	ifChangeKurs = true;
}
void Kurs::repairRepetitionLevels(const ushort &which_repetition, const double &deviation, const int &parttime, const double &predicted_score) {
	for(int i = 0; i < 11; i++) {
		new_repetitionsLevels[which_repetition][i] += logs[abs(i*10-parttime/10)]*(1000+deviation)*(predicted_score/1000);
		new_repetitionsLevels[which_repetition][i] /= 1+logs[abs(i*10-parttime/10)];
		if(new_repetitionsLevels[which_repetition][i] > 1000)new_repetitionsLevels[which_repetition][i] = 1000;
		if(new_repetitionsLevels[which_repetition][i] < 0)new_repetitionsLevels[which_repetition][i] = 0;
	}
}
void Kurs::setSingleWord(const ushort &number, const string &spelling, const string &sound) {
	if(number >= qAllSingleWords)throw Error::newError(Error::BAD_ARGUMENT, "", __LINE__, __FILE__);
	SingleWord *sword = number < wordl1.size() ? wordl1[number] : wordl2[number-wordl1.size()];
	sword->setSpelling(spelling);
	sword->setSound(sound);
}
void Kurs::setMeaningForSingleWord(const ushort &number_word, const ushort &number_meaning, const string &spelling, const string &sound) {
	if(number_word >= qAllSingleWords)throw Error::newError(Error::BAD_ARGUMENT, "", __LINE__, __FILE__);
	SingleWord *sword = number_word < wordl1.size() ? wordl1[number_word] : wordl2[number_word-wordl1.size()];
	if(number_meaning >= sword->getNumberMeanings())throw Error::newError(Error::BAD_ARGUMENT, "", __LINE__, __FILE__);
	if(sword->getMeaning(number_meaning) == emptyWord)throw Error::newError(Error::IMPOSSIBLE, "", __LINE__, __FILE__);
	sword->getMeaning(number_meaning)->setSpelling(spelling);
	sword->getMeaning(number_meaning)->setSound(sound);
}
void Kurs::takeOutSWFromLine(vector<string> &spellings, vector<string> &sounds, const string &rest) {
	size_t found=rest.find('|');
	if(found == string::npos)
	{
		if(rest != "") {
			spellings.push_back(rest);
			sounds.push_back("");
		}
	}
	else if(found == 0)takeOutSWFromLine(spellings, sounds, rest.substr(1));
	else {
		spellings.push_back(rest.substr(0, found));
		sounds.push_back("");
		takeOutSWFromLine(spellings, sounds, rest.substr(found+1));
	}
}
string Kurs::readSingleWordsFromFile(const string &file_to_open)
{
	ifstream plik;
	plik.open(file_to_open.c_str(), ios::binary);
	if(!plik.is_open())throw Error::newError(Error::ERROR_OPEN_FILE, "", __LINE__, __FILE__);
	string message;
	ushort number_of_words;
	plik >> number_of_words;
	string clear_buf; //zostaje biały znak po ilości słów
	getline(plik, clear_buf);
	string line;
	for(ushort i = 0; i < number_of_words; i++) {
	getline(plik, line);
		if(plik.eof())throw Error::newError(Error::ERROR_READ_FILE, "", __LINE__, __FILE__);
		size_t found=line.find('\t');
		if(found == string::npos) {
			message += "IGNORED: " + line + "\n";
			continue;
		}
		if(found == line.length()-1 || found == 0) {
			message += "IGNORED: " + line + "\n";
			continue;
		}
		message += "READ: " + line + "\n";
	vector<string> spellings;
		vector<string> meanings_spelling;
		vector<string> sounds;
		vector<string> meanings_sound;
		takeOutSWFromLine(spellings, sounds, line.substr(0, found));
		takeOutSWFromLine(meanings_spelling, meanings_sound, line.substr(found+1));
		addSingleWords(spellings, sounds, meanings_spelling, meanings_sound);
	}
	qAllSingleWords = wordl1.size() + wordl2.size();
	plik.close();
	return message;
}
void Kurs::unitSingleWords(const ushort &number1, const ushort &number2) {//ulepszyć
	if(wordl1[number1]->getMeaning(0) == emptyWord)SingleWord::disconnectSingleWords(wordl1[number1], emptyWord);
	if(wordl2[number2-wordl1.size()]->getMeaning(0) == emptyWord)SingleWord::disconnectSingleWords(wordl2[number2-wordl1.size()], emptyWord);
	if(number1 >= qAllSingleWords || number2 >= qAllSingleWords)throw Error::newError(Error::BAD_ARGUMENT, "",__LINE__, __FILE__);
	if(number1 >= wordl1.size() && number2 >= wordl1.size()) {
		wordl2[number1-wordl1.size()]->joinOtherSingleWord(wordl2[number2-wordl1.size()]);
		if(wordl2[number2-wordl1.size()]->isKnown() == false)qKnownSingleWords--;
		wordl2.erase(wordl2.begin() + number2 - wordl1.size());
		if(wordl2[number1-wordl1.size()]->getNumberMeanings() == 0)SingleWord::connectSingleWords(wordl2[number1-wordl1.size()], emptyWord, 0, 0);
	}
	else if(number1 < wordl1.size() && number2 < wordl1.size()) {
		wordl1[number1]->joinOtherSingleWord(wordl1[number2]);
		if(wordl1[number2]->isKnown() == false)qKnownSingleWords--;
		wordl1.erase(wordl1.begin() + number2);
		if(wordl1[number1]->getNumberMeanings() == 0)SingleWord::connectSingleWords(wordl1[number1], emptyWord, 0, 0);
	}
	qAllSingleWords = wordl1.size() + wordl2.size();
}
Kurs::Kurs(const string &name, const string &lang1, const string &lang2, const string &filename, const ushort &askQKW, const ushort &askQNW,  RegisterOfErrors &_ROE) {
	this->name = name;
	this->lang1 = lang1;
	this->lang2 = lang2;
	this->filename = filename;
	this->qAllSingleWords = 0;
	this->qKnownSingleWords = 0;
	this->askQKW = askQKW;
	this->askQNW = askQNW;
	this->ifChangeKurs = true;
	numberConnections = 0;
	wordl1 = vector<SingleWord *>(0);
	wordl2 = vector<SingleWord *>(0);
	
	double* tempss = new double[11]; //nie robić delete, dopiero w destruktorze kursu
	tempss[0] = 1000;
	tempss[1] = 900;
	tempss[2] = 800;
	tempss[3] = 700;
	tempss[4] = 600;
	tempss[5] = 500;
	tempss[6] = 400;
	tempss[7] = 300;
	tempss[8] = 200;
	tempss[9] = 100;
	tempss[10] = 0;
	new_repetitionsLevels = vector<double*>(1);
	new_repetitionsLevels[0] = tempss;
	new_repetitionsTime = vector<time_t>(1);
	new_repetitionsTime[0] = (3600*24);
	new_repetitionsAverageError = vector<double>(1);
	new_repetitionsAverageError[0] = 50.0;
	new_repetitionsStabilization = vector<unsigned int>(1);
	new_repetitionsStabilization[0] = 1;
	
	ROE = &_ROE;
	emptyWord = new SingleWord("BRAK ZNACZENIA", "");
	logs = new double[101];
	logs[0] = 1000000000;
	logs[100] = 0;
	for(int i = 1; i < 100; i++) {
		logs[i] = (-1)*log10((double)i/100);
	}
}
Kurs::Kurs(const string &file_to_open,  RegisterOfErrors &_ROE)
{
	emptyWord = new SingleWord("BRAK ZNACZENIA", "");
	ROE = &_ROE;
	logs = new double[101];
	logs[0] = 1000000000;
	logs[100] = 0;
	for(int i = 1; i < 100; i++) {
		logs[i] = (-1)*log10((double)i/100);
	}
	
	ifstream file;
	file.open(file_to_open.c_str());
	if(!file.is_open())throw Error::newError(Error::ERROR_OPEN_FILE, "", __LINE__, __FILE__);
	string firstline;
	getline(file, firstline);
	if(firstline == "new version") {
		ushort numberWordsFL;
		ushort numberWordsSL;
		file >> name;
		file.ignore(INT_MAX, '\n');
		file >> numberWordsFL;
		file.ignore(INT_MAX, '\n');
		file >> numberWordsSL;
		file.ignore(INT_MAX, '\n');
		file >> numberConnections;
		file.ignore(INT_MAX, '\n');
		file >> askQKW;
		file.ignore(INT_MAX, '\n');
		file >> askQNW;
		file.ignore(INT_MAX, '\n');
		ushort qRepetition;
		file >> qRepetition;
		file.ignore(INT_MAX, '\n');
		time_t new_repetitionTime;
		ushort repetitionHowMany;
		double repetitionGrade;
		double *tempss;
		for(int i = 0; i < qRepetition; i++) {
			file >> new_repetitionTime;
			file >> repetitionHowMany;
			file >> repetitionGrade;
			file.ignore(INT_MAX, '\n');
			
			tempss = new double[11]; //zwalnianie pamięci dopiero w destruktorze kursu
			tempss[0] = 1000;
			tempss[1] = 900;
			tempss[2] = 800;
			tempss[3] = 700;
			tempss[4] = 600;
			tempss[5] = 500;
			tempss[6] = 400;
			tempss[7] = 300;
			tempss[8] = 200;
			tempss[9] = 100;
			tempss[10] = 0;
			
			new_repetitionsLevels.push_back(tempss);
			new_repetitionsTime.push_back(new_repetitionTime);
			new_repetitionsAverageError.push_back(50.0);
			new_repetitionsStabilization.push_back(1);
		}
		filename = file_to_open;
		qAllSingleWords = numberWordsFL + numberWordsSL;
			
		SingleWord sword("", "");
		ushort oplev;
		ushort hralev;
		string spelling;
		time_t time_lastud;
		qKnownSingleWords = 0;
		ifChangeKurs = false;
		for(ushort i = 0; i < numberWordsFL; i++) {
			getline(file, spelling);
			file >> oplev;
			file >> hralev;
			file >> time_lastud;
			file.ignore(INT_MAX, '\n');
				
			sword.setSpelling(spelling);
			wordl1.push_back(new SingleWord(sword));
			SingleWord::connectSingleWords(wordl1[i], emptyWord, 0, 0);
		}
		for(ushort i = 0; i < numberWordsSL; i++) {
			getline(file, spelling);
			file >> oplev;
			file >> hralev;
			file >> time_lastud;
			file.ignore(INT_MAX, '\n');

			sword.setSpelling(spelling);
			wordl2.push_back(new SingleWord(sword));
			SingleWord::connectSingleWords(wordl2[i], emptyWord, 0, 0);
		}
		ushort number1;
		ushort number2;
		ushort which_repetition;
		time_t last_repetition;
		for(ushort i = 0; i < numberConnections; i++) {
			file >> number1;
			file >> number2;
			file >> which_repetition;
			file >> last_repetition;
				
			file.ignore(INT_MAX, '\n');
			if(number1 >= wordl1.size() || (number2 >= wordl1.size()+wordl2.size() || number2 < wordl1.size()))throw Error::newError(Error::BAD_ARGUMENT, "", __LINE__, __FILE__);
			SingleWord::disconnectSingleWords(wordl1[number1], emptyWord);
			SingleWord::disconnectSingleWords(wordl2[number2-wordl1.size()], emptyWord);
			SingleWord::connectSingleWords(wordl1[number1], wordl2[number2-wordl1.size()], which_repetition, last_repetition);
		}

		for(ushort i = 0; i < numberWordsFL; i++) {
			if(wordl1[i]->isKnown())qKnownSingleWords++;
		}
		for(ushort i = 0; i < numberWordsSL; i++) {
			if(wordl2[i]->isKnown())qKnownSingleWords++;
		}
		file.close();
	}
	else if(firstline == "new version2") {
		ushort numberWordsFL;
		ushort numberWordsSL;
		file >> name;
		file.ignore(INT_MAX, '\n');
		file >> numberWordsFL;
		file.ignore(INT_MAX, '\n');
		file >> numberWordsSL;
		file.ignore(INT_MAX, '\n');
		file >> numberConnections;
		file.ignore(INT_MAX, '\n');
		file >> askQKW;
		file.ignore(INT_MAX, '\n');
		file >> askQNW;
		file.ignore(INT_MAX, '\n');
		ushort qRepetition;
		file >> qRepetition;
		file.ignore(INT_MAX, '\n');
		time_t new_repetitionTime;
		ushort repetitionHowMany;
		double repetitionGrade;
		double *tempss;
		for(int i = 0; i < qRepetition; i++) {
			file >> new_repetitionTime;
			file >> repetitionHowMany;
			file >> repetitionGrade;
			file.ignore(INT_MAX, '\n');
			
			tempss = new double[11]; //zwalnianie pamięci dopiero w destruktorze kursu
			tempss[0] = 1000;
			tempss[1] = 900;
			tempss[2] = 800;
			tempss[3] = 700;
			tempss[4] = 600;
			tempss[5] = 500;
			tempss[6] = 400;
			tempss[7] = 300;
			tempss[8] = 200;
			tempss[9] = 100;
			tempss[10] = 0;
			
			new_repetitionsLevels.push_back(tempss);
			new_repetitionsTime.push_back(new_repetitionTime);
			new_repetitionsAverageError.push_back(50.0);
			new_repetitionsStabilization.push_back(1);
		}
		filename = file_to_open;
		qAllSingleWords = numberWordsFL + numberWordsSL;

		SingleWord sword("", "");
		string spelling;
		qKnownSingleWords = 0;
		ifChangeKurs = false;
		for(ushort i = 0; i < numberWordsFL; i++) {
			getline(file, spelling);
			sword.setSpelling(spelling);
			wordl1.push_back(new SingleWord(sword));
			SingleWord::connectSingleWords(wordl1[i], emptyWord, 0, 0);
		}
		for(ushort i = 0; i < numberWordsSL; i++) {
			getline(file, spelling);
			sword.setSpelling(spelling);
			wordl2.push_back(new SingleWord(sword));
			SingleWord::connectSingleWords(wordl2[i], emptyWord, 0, 0);
		}
		ushort number1;
		ushort number2;
		ushort which_repetition;
		ushort which_repetition2;
		time_t last_repetition;
		for(ushort i = 0; i < numberConnections; i++) {
			file >> number1;
			file >> number2;
			file >> which_repetition;
			file >> which_repetition2;
			file >> last_repetition;

			file.ignore(INT_MAX, '\n');
			if(number1 >= wordl1.size() || (number2 >= wordl1.size()+wordl2.size() || number2 < wordl1.size()))throw Error::newError(Error::BAD_ARGUMENT, "", __LINE__, __FILE__);
			SingleWord::disconnectSingleWords(wordl1[number1], emptyWord);
			SingleWord::disconnectSingleWords(wordl2[number2-wordl1.size()], emptyWord);
			SingleWord::connectSingleWords(wordl1[number1], wordl2[number2-wordl1.size()], which_repetition, last_repetition, which_repetition2);
		}

		for(ushort i = 0; i < numberWordsFL; i++) {
			if(wordl1[i]->isKnown())qKnownSingleWords++;
		}
		for(ushort i = 0; i < numberWordsSL; i++) {
			if(wordl2[i]->isKnown())qKnownSingleWords++;
		}
		file.close();
	}
	else if(firstline == "new version3") {
		ushort numberWordsFL;
		ushort numberWordsSL;
		file >> name;
		file.ignore(INT_MAX, '\n');
		file >> numberWordsFL;
		file.ignore(INT_MAX, '\n');
		file >> numberWordsSL;
		file.ignore(INT_MAX, '\n');
		file >> numberConnections;
		file.ignore(INT_MAX, '\n');
		file >> askQKW;
		file.ignore(INT_MAX, '\n');
		file >> askQNW;
		file.ignore(INT_MAX, '\n');
		ushort qRepetition;
		file >> qRepetition;
		file.ignore(INT_MAX, '\n');
		
		double* new_repetitionLevels;
		time_t new_repetitionTime;
		double new_repetitionAverageError;
		unsigned int new_repetitionStabilization;
		for(int i = 0; i < qRepetition; i++) {
			new_repetitionLevels = new double[11]; //zwolnienie pamięci dopiero w destruktorze kursu
			for(int j = 0; j < 11; j++) {
				file >> new_repetitionLevels[j];
			}
			file >> new_repetitionTime;
			file >> new_repetitionAverageError;
			file >> new_repetitionStabilization;
			file.ignore(INT_MAX, '\n');
			
			new_repetitionsLevels.push_back(new_repetitionLevels);
			new_repetitionsTime.push_back(new_repetitionTime);
			new_repetitionsAverageError.push_back(new_repetitionAverageError);
			new_repetitionsStabilization.push_back(new_repetitionStabilization);
		}
		filename = file_to_open;
		qAllSingleWords = numberWordsFL + numberWordsSL;

		SingleWord sword("", "");
		string spelling;
		qKnownSingleWords = 0;
		ifChangeKurs = false;
		for(ushort i = 0; i < numberWordsFL; i++) {
			getline(file, spelling);
			sword.setSpelling(spelling);
			wordl1.push_back(new SingleWord(sword));
			SingleWord::connectSingleWords(wordl1[i], emptyWord, 0, 0);
		}
		for(ushort i = 0; i < numberWordsSL; i++) {
			getline(file, spelling);
			sword.setSpelling(spelling);
			wordl2.push_back(new SingleWord(sword));
			SingleWord::connectSingleWords(wordl2[i], emptyWord, 0, 0);
		}
		ushort number1;
		ushort number2;
		ushort which_repetition;
		ushort which_repetition2;
		time_t last_repetition;
		for(ushort i = 0; i < numberConnections; i++) {
			file >> number1;
			file >> number2;
			file >> which_repetition;
			file >> which_repetition2;
			file >> last_repetition;

			file.ignore(INT_MAX, '\n');
			if(number1 >= wordl1.size() || (number2 >= wordl1.size()+wordl2.size() || number2 < wordl1.size()))throw Error::newError(Error::BAD_ARGUMENT, "", __LINE__, __FILE__);
			SingleWord::disconnectSingleWords(wordl1[number1], emptyWord);
			SingleWord::disconnectSingleWords(wordl2[number2-wordl1.size()], emptyWord);
			SingleWord::connectSingleWords(wordl1[number1], wordl2[number2-wordl1.size()], which_repetition, last_repetition, which_repetition2);
		}

		for(ushort i = 0; i < numberWordsFL; i++) {
			if(wordl1[i]->isKnown())qKnownSingleWords++;
		}
		for(ushort i = 0; i < numberWordsSL; i++) {
			if(wordl2[i]->isKnown())qKnownSingleWords++;
		}
		file.close();
	}
	else {
		file.close();
		FILE *plik;
		plik = fopen(file_to_open.c_str(), "r");
		if(plik == NULL)throw Error::newError(Error::ERROR_OPEN_FILE, "Kurs::Kurs(string file_to_open)", __LINE__, __FILE__);
		ifChangeKurs = false;
		//początek wczytywania danych kursu
		char _name[100];
		fscanf(plik, "%s", _name);
		name = decode_text(_name);
		char _lang1[100], _lang2[100];
		fscanf(plik, "%s %s", _lang1, _lang2);
		lang1 = decode_text(_lang1);
		lang2 = decode_text(_lang2);
		char _filename[100];
		fscanf(plik, "%s %hu %hu", _filename, &askQKW, &askQNW);
		//filename = decode_text(_filename);
		filename = file_to_open;
		fscanf(plik, "%hu %hu", &qAllSingleWords, &qKnownSingleWords);
		qKnownSingleWords = 0;
		numberConnections = qAllSingleWords;
		qAllSingleWords *= 2;
		
		double* tempss = new double[11]; //nie robić delete, dopiero w destruktorze kursu
		tempss[0] = 1000;
		tempss[1] = 900;
		tempss[2] = 800;
		tempss[3] = 700;
		tempss[4] = 600;
		tempss[5] = 500;
		tempss[6] = 400;
		tempss[7] = 300;
		tempss[8] = 200;
		tempss[9] = 100;
		tempss[10] = 0;
		new_repetitionsLevels.push_back(tempss);
		new_repetitionsTime.push_back(3600*24);
		new_repetitionsAverageError.push_back(50.0);
		new_repetitionsStabilization.push_back(1);

		//koniec wczytywania danych kursu
		ushort _hralev, _oplev;
		time_t _time_lastud;
		SingleWord sword("", "");
		for(ushort i = 0; i < numberConnections; i++) {
			char _first[100], _second[100];
			fscanf(plik, "%s\t%s\t%hu %hu %u\n", _first, _second, &_hralev, &_oplev, &_time_lastud);
			
			sword.setSpelling(decode_text(_first));
			if(_oplev != 0)qKnownSingleWords += 2;
			wordl1.push_back(new SingleWord(sword));
			sword.setSpelling(decode_text(_second));
			wordl2.push_back(new SingleWord(sword));
			SingleWord::connectSingleWords(wordl1[i], wordl2[i], 0, _time_lastud);
		}
		fclose(plik);
		//restore memory
			
	}
}
ushort Kurs::compare_words(const string &aa, const string &bb)
{
	ushort a = aa.length();
	ushort b = bb.length();
				
	ushort **tablice = new ushort*[2];
	tablice[0] = new ushort[a+1];
	tablice[1] = new ushort[a+1];

	tablice[0][0] = 1;
	for(ushort i = 1; i <= a; i++)
	{
		if(bb[0] == aa[i-1])
		{
			tablice[0][i] = i-1;
		}
		else
		{
			if(tablice[0][i-1] < i-1)tablice[0][i] = tablice[0][i-1]+1;
			else tablice[0][i] = i;
		}
	}
	ushort *temp;
	for(ushort i = 1; i < b; i++)
	{
		tablice[1][0] = i+1;
		for(ushort j = 1; j <= a; j++)
		{
			if(bb[i] == aa[j-1])
			{
				tablice[1][j] = tablice[0][j-1];
			}
			else
			{
				if(tablice[0][j] < tablice[1][j-1] && tablice[0][j] < tablice[0][j-1])tablice[1][j] = tablice[0][j]+1;
				else if(tablice[1][j-1] < tablice[0][j] && tablice[1][j-1] < tablice[0][j-1])tablice[1][j] = tablice[1][j-1]+1;
				else tablice[1][j] = tablice[0][j-1]+1;
			}
		}
		temp = tablice[0];
		tablice[0] = tablice[1];
		tablice[1] = temp;
	}
		//restore memory
		ushort wynik = tablice[0][a];
		delete [] tablice[0];
		delete [] tablice[1];
		
	return wynik;
}
string Kurs::decode_text(const string &oryginal)
{
	string wynik = "";
	for(int i = 0; i < oryginal.length(); i++)
	{
		if(oryginal[i] == '&')
		{
			wynik += (char)((oryginal[i+1]-'0')*10+(oryginal[i+2]-'0'));
			i+=2;
		}
		else
		{
			wynik += oryginal[i];
		}
	}
	return wynik;
}
string Kurs::encode_text(const string &oryginal)
{
	string wynik = "";
	for(int i = 0; i < oryginal.length(); i++)
	{
		if(oryginal[i] == '&')wynik += "&38";
		else if(oryginal[i] < 33)
		{
			wynik += "&";
			wynik += (char)(oryginal[i]/10+'0');
			wynik += (char)(oryginal[i]%10+'0');
		}
		else
		{
			wynik += oryginal[i];
		}
	}
	return wynik;
}
string Kurs::getName() const
{
		return this->name;
}
string Kurs::getLang1() const
{
	return this->lang1;
}
string Kurs::getLang2() const
{
	return this->lang2;
}
string Kurs::getFilename() const
{
	return this->filename;
}
bool Kurs::isKursChanged() const
{
	return this->ifChangeKurs;
}
ushort Kurs::getAskQKW() const
{
	return this->askQKW;
}
ushort Kurs::getAskQNW() const
{
	return this->askQNW;
}
void Kurs::increaseQKnownWords(const short int &quantity)
{
	qKnownSingleWords += quantity;
}
void Kurs::saveKurs(const string &file_to_save)
{
	ofstream file;
	file.open(file_to_save.c_str());
	if(!file.is_open())throw Error::newError(Error::ERROR_OPEN_FILE, "", __LINE__, __FILE__);
	file << "new version3" << endl;
	file << name << endl;
	file << wordl1.size() << endl;
	file << wordl2.size() << endl;
	file << numberConnections << endl;
	file << askQKW << endl;
	file << askQNW << endl;
	file << new_repetitionsTime.size() << endl; //dać zmienną rozmiaru
	for(int i = 0; i < new_repetitionsTime.size(); i++) {
		file.precision(10);
		for(int j = 0; j < 11; j++) {
			file << new_repetitionsLevels[i][j] << "\t";
		}
		file << new_repetitionsTime[i] << "\t";
		file << new_repetitionsAverageError[i] << "\t";
		file << new_repetitionsStabilization[i];
		file << endl;
	}
	for(ushort i = 0; i < wordl1.size(); i++) {
		file << wordl1[i]->getSpelling() << endl;
	}
	for(ushort i = 0; i < wordl2.size(); i++) {
		file << wordl2[i]->getSpelling() << endl;
		wordl2[i]->id = i+wordl1.size();
	}
	int inSecondWord;
	for(ushort i = 0; i < wordl1.size(); i++) {
	for(ushort j = 0; j < wordl1[i]->getNumberMeanings(); j++) {
		if(wordl1[i]->getMeaning(j) != emptyWord) {
			file << i << "\t";
			file << wordl1[i]->getMeaning(j)->id << "\t";
			file << wordl1[i]->getWhichRepetition(j) << "\t";
			inSecondWord = wordl1[i]->getMeaning(j)->findMeaning(wordl1[i]);
			file << wordl1[i]->getMeaning(j)->getWhichRepetition(inSecondWord) << "\t";
			file << wordl1[i]->getTimeLastRepetition(j) << endl;
		}
	}
	}
	file.close();
}
void Kurs::setName(const string &_name)
{
	name = _name;
	ifChangeKurs = true;
}
void Kurs::setLang1(const string &_lang1)
{
	lang1 = _lang1;
	ifChangeKurs = true;
}
void Kurs::setLang2(const string &_lang2)
{
	lang2 = _lang2;
	ifChangeKurs = true;
}
void Kurs::setFilename(const string &_filename)
{
	filename = _filename;
	ifChangeKurs = true;
}
void Kurs::setIfChangeKurs(const bool &_ifChangeKurs)
{
	ifChangeKurs = _ifChangeKurs;
}
void Kurs::setAskQKW(const ushort &_askQKW)
{
	askQKW = _askQKW;
	ifChangeKurs = true;
}
void Kurs::setAskQNW(const ushort &_askQNW)
{
	askQNW = _askQNW;
	ifChangeKurs = true;
}


