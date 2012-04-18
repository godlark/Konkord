/*				Konkord 
 *			Version 0.0.2009.04.19
 *	This program was created for learning words
 *			from different languages.
 *	Copyright(C) 2009 Sławomir Domagała	
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
typedef unsigned int uint;

string toString(int number) {
	//ASSERT IN
	assert(number >= 0);
	
	string s_number = "";
	if(number == 0)s_number = "0";
	while(number != 0) {
		s_number = (char)(number%10+(int)'0') + s_number;
		number -= number%10;
		number /= 10;
	}
	return s_number;
}
int toInteger(string s_number) {
	//ASSERT IN
	assert(s_number.length() > 0);
	
	int size = s_number.length();
	int number = 0;
	int ten = 1;
	for(int i = size-1; i >= 0; i--, ten *= 10) {
	number += ten*((int)s_number[i]-48);
	}
	return number;
}

Kurs::~Kurs() {
	for(int i = 0; i < wordl1.size(); i++) {
		assert(wordl1[i] != NULL);
		wordl1[i]->deleteAllMeanings();
		delete wordl1[i];
	}
	for(int i = 0; i < wordl2.size(); i++) {
		assert(wordl2[i] != NULL);
		wordl2[i]->deleteAllMeanings();
		delete wordl2[i];
	}
	delete repetitionAnn;
	delete repetitionAnnTrainingData;
	assert(emptySingleWord != NULL);
	delete emptySingleWord;
}
void Kurs::addSingleWords(const vector<string> &spellings, const vector<string> &sounds, const vector<string> &meanings_spelling, const vector<string> &meanings_sound) {
	//ASSERT IN
	assert(spellings.size() == sounds.size() && meanings_spelling.size() == meanings_sound.size());
	assert(spellings.size() != 0 && meanings_spelling.size() != 0);
	
	SingleWord *singleWord;
	for(uint i = 0; i < spellings.size(); i++) {
		singleWord = new SingleWord(spellings[i], sounds[i]);
		wordl1.push_back(singleWord);
	}
	for(uint i = 0; i < meanings_spelling.size(); i++) {
		singleWord = new SingleWord(meanings_spelling[i], meanings_sound[i]);
		wordl2.push_back(singleWord);
		for(uint j = wordl1.size() - sounds.size(); j < wordl1.size(); j++) {
			SingleWord::connectSingleWords(wordl2[wordl2.size()-1], wordl1[j], 0, 0, 0); //łączy ostatnio dodane słowo dodane do wordl2 z...
			nConnections++;
		}
	}
	nAllSingleWords = wordl1.size() + wordl2.size();
	
	//ASSERT OUT
	for(int i = 0; i < spellings.size(); i++) {
		assert(wordl1[wordl1.size()-spellings.size()+i]->getSpelling() == spellings[i]);
		for(int j = 0; j < meanings_spelling.size(); j++) {
			assert(wordl2[wordl2.size()-meanings_spelling.size()+j]->getSpelling() == meanings_spelling[j]);
			assert(wordl1[wordl1.size()-spellings.size()+i]->isConnectedWith(wordl2[wordl2.size()-meanings_spelling.size()+j]));
		}
	}
}
void Kurs::addSingleWord(const SingleWord &singleWord, const uint &where) {
	//ASSERT IN
	
	uint singleWordNo;
	if(where == 0) {
		wordl1.push_back(new SingleWord(&singleWord));
		singleWordNo = wordl1.size()-1;
		SingleWord::connectSingleWords(wordl1[singleWordNo], emptySingleWord, 0, 0, 0);
	}
	else {
		wordl2.push_back(new SingleWord(&singleWord));
		singleWordNo = wordl1.size() + wordl2.size() - 1;
		SingleWord::connectSingleWords(wordl2[singleWordNo-wordl1.size()], emptySingleWord, 0, 0, 0);
	}
	nAllSingleWords = wordl1.size() + wordl2.size();
}
void Kurs::connectSingleWords(const uint &singleWord1No, const uint &singleWord2No) {
	//ASSERT IN
	assert(singleWord1No < wordl1.size() && (singleWord2No < wordl1.size()+wordl2.size() && singleWord2No > wordl1.size()));
	
	if(wordl1[singleWord1No]->isConnectedWith(emptySingleWord))SingleWord::disconnectSingleWords(wordl1[singleWord1No], emptySingleWord);
	if(wordl2[singleWord2No-wordl1.size()]->isConnectedWith(emptySingleWord))SingleWord::disconnectSingleWords(wordl2[singleWord2No-wordl1.size()], emptySingleWord);
	SingleWord::connectSingleWords(wordl1[singleWord1No], wordl2[singleWord2No-wordl1.size()], 0, 0, 0);
	nConnections++;
}
void Kurs::disconnectSingleWords(const uint &singleWord1No, const uint &singleWord2No) {
	//ASSERT IN
	assert(singleWord1No < wordl1.size() && (singleWord2No < wordl1.size()+wordl2.size() && singleWord2No > wordl1.size()));
	
	SingleWord::disconnectSingleWords(wordl1[singleWord1No], wordl2[singleWord2No-wordl1.size()]);
	nConnections--;
	if(wordl1[singleWord1No]->getNumberMeanings() == 0)SingleWord::connectSingleWords(wordl1[singleWord1No], emptySingleWord, 0, 0, 0);
	if(wordl2[singleWord2No-wordl1.size()]->getNumberMeanings() == 0)SingleWord::connectSingleWords(wordl2[singleWord2No-wordl1.size()], emptySingleWord, 0, 0, 0);
}
void Kurs::delSingleWord(const uint &singleWordNo) {
	//ASSERT IN
	assert(singleWordNo < wordl1.size() || (singleWordNo < wordl1.size()+wordl2.size() && singleWordNo > wordl1.size()));
	
	uint nAllMeanings;
	SingleWord* meaning;
	vector<SingleWord*>::iterator position;
	if(singleWordNo < wordl1.size()) {
		nAllMeanings = wordl1[singleWordNo]->getNumberMeanings();
		for(int i = 0; i < nAllMeanings; i++) {
			meaning = (wordl1[singleWordNo]->getMeaning(i)); //znaczenia słowa z tablicy wordl1 jest w tablicy wordl2
			SingleWord::disconnectSingleWords(wordl1[singleWordNo], meaning);
			if(meaning->getNumberMeanings() == 0) {
				SingleWord::connectSingleWords(meaning, emptySingleWord, 0, 0, 0);
			}
			nConnections--;
		}
		delete wordl1[singleWordNo];
		wordl1.erase(wordl1.begin() + singleWordNo);
	}
	else if(singleWordNo < wordl1.size() + wordl2.size()) {
		nAllMeanings = wordl2[singleWordNo-wordl1.size()]->getNumberMeanings();
		for(int i = 0; i < nAllMeanings; i++) {
			meaning = (wordl2[singleWordNo-wordl1.size()]->getMeaning(i)); //znaczenia słowa z tablicy wordl1 jest w tablicy wordl2
			SingleWord::disconnectSingleWords(wordl2[singleWordNo-wordl1.size()], meaning);
			if(meaning->getNumberMeanings() == 0) {
				SingleWord::connectSingleWords(meaning, emptySingleWord, 0, 0, 0);
			}
			nConnections--;
		}
		delete wordl2[singleWordNo-wordl1.size()];
		wordl2.erase(wordl2.begin() + singleWordNo-wordl1.size());
	}
	nAllSingleWords = wordl1.size() + wordl2.size();
}
vector<uint> Kurs::findWord(const boost::regex &searchedString) const {
	vector<uint> found_words;
	for(uint i = 0; i < wordl1.size(); i++) {   
		if(regex_match(wordl1[i]->getSpelling(), searchedString)) {
			found_words.push_back(i);
		}
	}
	for(uint i = 0; i < wordl2.size(); i++) {
		if(regex_match(wordl2[i]->getSpelling(), searchedString)) {
			found_words.push_back(i+wordl1.size());
		}
	}
	return found_words;
}
vector<uint> Kurs::getWordsToRepetition(uint &nWords) const{
	//howManyWords jest liczbą słów do przepytania, rozmiar zwracanego vectora to liczba słów do przepytania i liczba połączeń do powtórzenia
	if(nWords > wordl1.size() + wordl2.size())nWords = wordl1.size() + wordl2.size();
	uint tNWords = 0;
	priority_queue<WordToRepetition, vector<WordToRepetition>, compareWords>Q;
	WordToRepetition wtr;
	time_t nowTime = time(NULL);
	//pobieranie słów z tablic i dodawanie ich do kolejki priorytetowej sortującej według zmiennej priority
	
	for(uint i = 0; i < wordl1.size(); i++) {
		if(wordl1[i]->isConnectedWith(emptySingleWord) || !wordl1[i]->isKnown())continue; //ze słów pustych i nie poznanych nie można przeptywać
		
		uint countConnections = wordl1[i]->getNumberMeanings();
		wtr.priority = 0;
		wtr.parttime = 0;
		for(uint j = 0; j < countConnections; j++) {;
			wtr.parttime += nowTime-wordl1[i]->getTimeLastRepetition(j);
			wtr.priority += makePredictions(nowTime-wordl1[i]->getTimeLastRepetition(j), wordl1[i]->getRepetitionLevelNumber(j), true);
		}
		wtr.priority /= countConnections;
		wtr.parttime /= countConnections;
		wtr.nr_word = i;
		if(wtr.priority < 0.7*(double)maxOplev) {
			tNWords++;
		}
		Q.push(wtr);
		
	}
	for(uint i = 0; i < wordl2.size(); i++) {
		if(wordl2[i]->isConnectedWith(emptySingleWord) || !wordl2[i]->isKnown())continue; //ze słów pustych i nie poznanych nie można przeptywać
		
		uint countConnections = wordl2[i]->getNumberMeanings();
		wtr.priority = 0;
		wtr.parttime = 0;
		for(uint j = 0; j < countConnections; j++) {
			wtr.parttime += nowTime-wordl2[i]->getTimeLastRepetition(j);
			wtr.priority += makePredictions(nowTime-wordl2[i]->getTimeLastRepetition(j), wordl2[i]->getRepetitionLevelNumber(j), false);
		}
		wtr.priority /= countConnections;
		wtr.parttime /= countConnections;
		wtr.nr_word = i+wordl1.size();
		if(wtr.priority < 0.7*(double)maxOplev) {
			tNWords++;
		}
		Q.push(wtr);
	}
	//koniec pobieranie słów z tablicy

	//1 liczba to ilość sugerowanych na następny dzień słów do przepytania
	vector<uint> WordsToRepetition = vector<uint>(0);
	WordsToRepetition.push_back(tNWords);
	//słowa do przepytania i połączenia do powtórzenia
	vector<uint> ConnectionsToRepetition = vector<uint>(0);
	

	//pobieranie górnych słów z kolejki priorytetowej i dodawanie ich do WordsToRepetition
	//dodawanie połączeń tych słów do ConnectionsToRepetition
	SingleWord *sword;
	for(uint i = 0; i < nWords; i++) {
		WordsToRepetition.push_back(Q.top().nr_word);//dodaje słowo do przepytania
		
		if(Q.top().nr_word < wordl1.size())sword = wordl1[Q.top().nr_word];
		else sword = wordl2[Q.top().nr_word-wordl1.size()];
		
		int whereInOther;
		for(uint j = 0; j < sword->getNumberMeanings(); j++) {
			string _j = toString(j);
			if(sword->getFlag(_j) == "use") {//jeśli połączenie zostało już dodanie do ConnectionsToRepetition to pomiń i usuń z przepytywanych
				WordsToRepetition.erase(WordsToRepetition.end()-1);
				i--;
				break;
			}
			whereInOther = sword->getMeaning(j)->findMeaning(sword);
			string _whereInOther = toString(whereInOther);
			sword->getMeaning(j)->setFlag(_whereInOther, "use");//ustawianie flagi, która informuje, że polączenie zostało już dodane
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
vector<uint> Kurs::getUnknownSingleWords(const uint &nWords) const {
	//if(quantityOfWords > qAllWords - qKnownWords)quantityOfWords = qAllWords - qKnownWords;
	vector<uint> wordsToAsk;
	time_t lasttime = time(NULL);
	for(uint i = 0, j = 0; i < nAllSingleWords && j < nWords; i++) {
		if(i < wordl1.size()) {
			if(!wordl1[i]->isKnown() && !wordl1[i]->isConnectedWith(emptySingleWord)) {
				wordsToAsk.push_back(i);
				uint number_connections = wordl1[i]->getNumberMeanings();
				for(uint k = 0; k < number_connections; k++) {
					wordl1[i]->setTimeLastRepetition(k, lasttime);
				}
		j++;
			}
		}
		else {
			if(!wordl2[i-wordl1.size()]->isKnown() && !wordl2[i-wordl1.size()]->isConnectedWith(emptySingleWord)) {
				wordsToAsk.push_back(i);
				uint number_connections = wordl2[i-wordl1.size()]->getNumberMeanings();
				for(uint k = 0; k < number_connections; k++) {
					wordl2[i-wordl1.size()]->setTimeLastRepetition(k, lasttime);
				}
		j++;
			}
		}
	}
	return wordsToAsk;
}
uint Kurs::getNAllSingleWords() const {
	return nAllSingleWords;
}
uint Kurs::getNKnownSingleWords() const {
	return nKnownSingleWords;
}
uint Kurs::getNSingleWords_1() const {
	return wordl1.size();
}
uint Kurs::getNSingleWords_2() const {
	return wordl2.size();
}
uint Kurs::getMaxOplev() const {
    return maxOplev;
}
SingleWord const* Kurs::getSingleWord(const uint &singleWordNo) const {
	if(singleWordNo >= nAllSingleWords)throw Error::newError(Error::BAD_ARGUMENT, "", __LINE__, __FILE__);
	return singleWordNo < wordl1.size() ? wordl1[singleWordNo] : wordl2[singleWordNo-wordl1.size()];
}
vector<SingleWord const*> Kurs::getSingleWords(const uint &from, uint &_to) const {
	vector<SingleWord const*> _words;
	if(from >= nAllSingleWords || _to >= nAllSingleWords)throw Error::newError(Error::BAD_ARGUMENT, "", __LINE__, __FILE__);
	else if(_to < from && _to != 0)throw Error::newError(Error::BAD_ARGUMENT, "", __LINE__, __FILE__);
	if(_to == 0)_to = nAllSingleWords;
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
bool Kurs::isSingleWordFLorSL(const uint &singleWordNo) const {
	return singleWordNo < wordl1.size() ? true : false; //not sesne ist throw Error for word_number > nAllSingleWords
}
double Kurs::makePredictions(const int &time, const uint &repetitionLevelNo, const bool& isFromFirstLanguage) const {
	double *inputs = new double[3];
	inputs[0] = 1/(double)time;
	inputs[1] = repetitionLevelNo;
	inputs[2] = (uint)(!isFromFirstLanguage)*2-1;
	double *outputs = repetitionAnn->run(inputs);
	if(outputs[0]*maxOplev < 0.0001)return 0.0001;
	else return outputs[0]*maxOplev;
}
void Kurs::repairPredictions() {
    repetitionAnnTrainingData->update();
    const int max_neurons = 100;
	const int neurons_between_reports = 1;
	const double desired_error = 0.00001;
	
	repetitionAnn = new FANN::neural_net();
	repetitionAnn->create_shortcut(2, 3, 1);
	repetitionAnn->cascadetrain_on_data(repetitionAnnTrainingData->getData(), max_neurons, neurons_between_reports, desired_error);
}

void Kurs::setRepetitionData(const uint &singleWordNo, const time_t &czas, vector<double> &connectionsOplev) {
	//ASSERT IN
	assert(singleWordNo < wordl1.size()+wordl2.size());
	SingleWord *sword = singleWordNo < wordl1.size() ? wordl1[singleWordNo] : wordl2[singleWordNo-wordl1.size()];
	assert(connectionsOplev.size() == sword->getNumberMeanings());

	time_t nowTime = time(NULL);
	double predicted_score;
	double deviation;
	for(uint i = 0; i < sword->getNumberMeanings(); i++) {
		predicted_score = 0;
		deviation = 0;
		
		if(connectionsOplev[i] > maxOplev)connectionsOplev[i] = maxOplev;
		
		predicted_score = makePredictions(nowTime-sword->getTimeLastRepetition(i), sword->getRepetitionLevelNumber(i), singleWordNo < wordl1.size());
		
		// UPDATING TRAINING FILE
		deviation = ((connectionsOplev[i]-predicted_score)*maxOplev)/predicted_score;
		if(deviation != 0) {
            repetitionAnnTrainingData->addLine({1/(double)(nowTime-sword->getTimeLastRepetition(i)), (double)sword->getRepetitionLevelNumber(i), (double)(singleWordNo < wordl1.size() ? -1 : 1)}, {connectionsOplev[i]/maxOplev});
		}
		// END UPDATING
		
		sword->setTimeLastRepetition(i, nowTime);	
		
		uint repetition = sword->getRepetitionLevelNumber(i);
		if(deviation >= 0) repetition++;
		sword->setRepetitionLevelNumber(i, repetition);
	}
	
	//ASSERT OUT
}
void Kurs::setSingleWord(const uint &singleWordNo, const string &spelling, const string &sound) {
	//ASSERT IN
	assert(singleWordNo < wordl1.size()+wordl2.size());
	
	SingleWord *sword = singleWordNo < wordl1.size() ? wordl1[singleWordNo] : wordl2[singleWordNo-wordl1.size()];
	sword->setSpelling(spelling);
	sword->setSound(sound);
}
void Kurs::setMeaningForSingleWord(const uint &singleWordNo, const uint &singleWordMeaningNo, const string &spelling, const string &sound) {
	//ASSERT IN
	assert(singleWordNo < wordl1.size()+wordl2.size());
	SingleWord *sword = singleWordNo < wordl1.size() ? wordl1[singleWordNo] : wordl2[singleWordNo-wordl1.size()];
	assert(singleWordMeaningNo < sword->getNumberMeanings());
	assert(sword->getMeaning(singleWordMeaningNo) != emptySingleWord);
	
	sword->getMeaning(singleWordMeaningNo)->setSpelling(spelling);
	sword->getMeaning(singleWordMeaningNo)->setSound(sound);
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
string Kurs::readSingleWordsFromFile(const string &filename)
{
	ifstream file;
	file.open(filename.c_str(), ios::binary);
	if(!file.is_open())throw Error::newError(Error::ERROR_OPEN_FILE, "", __LINE__, __FILE__);
	string message;
	uint number_of_words;
	file >> number_of_words;
	string clear_buf; //zostaje biały znak po ilości słów
	getline(file, clear_buf);
	string line;
	for(uint i = 0; i < number_of_words; i++) {
        getline(file, line);
        if(file.eof())throw Error::newError(Error::ERROR_READ_FILE, "", __LINE__, __FILE__);
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
	nAllSingleWords = wordl1.size() + wordl2.size();
	file.close();
	return message;
}
void Kurs::unitSingleWords(const uint &singleWord1No, const uint &singleWord2No) {//ulepszyć
	//ASSERT IN
	assert(singleWord1No < wordl1.size() + wordl2.size() && singleWord2No < wordl1.size() + wordl2.size());
	assert(singleWord1No != singleWord2No);
	
	if(wordl1[singleWord1No]->getMeaning(0) == emptySingleWord)SingleWord::disconnectSingleWords(wordl1[singleWord1No], emptySingleWord);
	if(wordl2[singleWord2No-wordl1.size()]->getMeaning(0) == emptySingleWord)SingleWord::disconnectSingleWords(wordl2[singleWord2No-wordl1.size()], emptySingleWord);
	if(singleWord1No >= wordl1.size() && singleWord2No >= wordl1.size()) {
		wordl2[singleWord1No-wordl1.size()]->joinOtherSingleWord(wordl2[singleWord2No-wordl1.size()]);
		if(wordl2[singleWord2No-wordl1.size()]->isKnown() == false)nKnownSingleWords--;
		wordl2.erase(wordl2.begin() + singleWord2No - wordl1.size());
		if(wordl2[singleWord1No-wordl1.size()]->getNumberMeanings() == 0)SingleWord::connectSingleWords(wordl2[singleWord1No-wordl1.size()], emptySingleWord, 0, 0, 0);
	}
	else if(singleWord1No < wordl1.size() && singleWord2No < wordl1.size()) {
		wordl1[singleWord1No]->joinOtherSingleWord(wordl1[singleWord2No]);
		if(wordl1[singleWord2No]->isKnown() == false)nKnownSingleWords--;
		wordl1.erase(wordl1.begin() + singleWord2No);
		if(wordl1[singleWord1No]->getNumberMeanings() == 0)SingleWord::connectSingleWords(wordl1[singleWord1No], emptySingleWord, 0, 0, 0);
	}
	nAllSingleWords = wordl1.size() + wordl2.size();
}
Kurs::Kurs(RegisterOfErrors &AROE) {
	nAllSingleWords = 0;
	nKnownSingleWords = 0;
	nConnections = 0;
	maxOplev = 12;
	wordl1 = vector<SingleWord *>(0);
	wordl2 = vector<SingleWord *>(0);
	repetitionAnn = new FANN::neural_net();
	repetitionAnn->create_standard(3, 3, 1, 1);
	repetitionAnnTrainingData = new TrainingData(3, 1);
	repetitionAnnTrainingData->setMaxLines(1200);
	ROE = &AROE;
	emptySingleWord = new SingleWord("BRAK ZNACZENIA", "");
}
Kurs::Kurs(const string &filename, RegisterOfErrors &_ROE) {
	emptySingleWord = new SingleWord("BRAK ZNACZENIA", "");
	ROE = &_ROE;
	
	ifstream file;
	file.open(filename.c_str());
	if(!file.is_open())throw Error::newError(Error::ERROR_OPEN_FILE, "", __LINE__, __FILE__);

	string firstline;
	getline(file, firstline);
	
	if(firstline == "new version") {
		uint numberWordsFL;
		uint numberWordsSL;
		file >> numberWordsFL;
		file.ignore(INT_MAX, '\n');
		file >> numberWordsSL;
		file.ignore(INT_MAX, '\n');
		file >> nConnections;
		file.ignore(INT_MAX, '\n');
		file >> maxOplev;
		file.ignore(INT_MAX, '\n');
		
		string repetitionAnnFileName;
		file >> repetitionAnnFileName;
		repetitionAnn = new FANN::neural_net();
		repetitionAnn->create_from_file(repetitionAnnFileName);
		file.ignore(INT_MAX, '\n');
		
		string repetitionAnnTrainingDataFileName;
		file >> repetitionAnnTrainingDataFileName;
		repetitionAnnTrainingData = new TrainingData(repetitionAnnTrainingDataFileName);
		file.ignore(INT_MAX, '\n');
		
		uint maxLinesInRepetitionAnnTrainingData;
		file >> maxLinesInRepetitionAnnTrainingData;
		repetitionAnnTrainingData->setMaxLines(maxLinesInRepetitionAnnTrainingData);
		file.ignore(INT_MAX, '\n');
	
		nAllSingleWords = numberWordsFL + numberWordsSL;

		SingleWord sword("", "");
		string spelling;
		nKnownSingleWords = 0;
		for(uint i = 0; i < numberWordsFL; i++) {
			getline(file, spelling);
			sword.setSpelling(spelling);
			wordl1.push_back(new SingleWord(sword));
			SingleWord::connectSingleWords(wordl1[i], emptySingleWord, 0, 0, 0);
		}
		for(uint i = 0; i < numberWordsSL; i++) {
			getline(file, spelling);
			sword.setSpelling(spelling);
			wordl2.push_back(new SingleWord(sword));
			SingleWord::connectSingleWords(wordl2[i], emptySingleWord, 0, 0, 0);
		}
		uint singleWord1No;
		uint singleWord2No;
		uint repetitionLevel1No;
		uint repetitionLevel2No;
		time_t timeLastRepetition;
		for(uint i = 0; i < nConnections; i++) {
			file >> singleWord1No;
			file >> singleWord2No;
			file >> repetitionLevel1No;
			file >> repetitionLevel2No;
			file >> timeLastRepetition;

			file.ignore(INT_MAX, '\n');
			assert(singleWord1No < wordl1.size() && (singleWord2No < wordl1.size()+wordl2.size() && singleWord2No >= wordl1.size()));
			if(emptySingleWord->isConnectedWith(wordl1[singleWord1No]))SingleWord::disconnectSingleWords(wordl1[singleWord1No], emptySingleWord);
			if(emptySingleWord->isConnectedWith(wordl2[singleWord2No-wordl1.size()]))SingleWord::disconnectSingleWords(wordl2[singleWord2No-wordl1.size()], emptySingleWord);
			assert(!wordl1[singleWord1No]->isConnectedWith(wordl2[singleWord2No-wordl1.size()]));
			SingleWord::connectSingleWords(wordl1[singleWord1No], wordl2[singleWord2No-wordl1.size()], repetitionLevel1No, repetitionLevel2No, timeLastRepetition);
		}

		for(uint i = 0; i < numberWordsFL; i++) {
			if(wordl1[i]->isKnown())nKnownSingleWords++;
		}
		for(uint i = 0; i < numberWordsSL; i++) {
			if(wordl2[i]->isKnown())nKnownSingleWords++;
		}
	}
	file.close();
}
uint Kurs::compare_words(const string &aa, const string &bb)
{
	uint a = aa.length();
	uint b = bb.length();
				
	uint **tablice = new uint*[2];
	tablice[0] = new uint[a+1];
	tablice[1] = new uint[a+1];

	tablice[0][0] = 1;
	for(uint i = 1; i <= a; i++)
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
	uint *temp;
	for(uint i = 1; i < b; i++)
	{
		tablice[1][0] = i+1;
		for(uint j = 1; j <= a; j++)
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
		uint wynik = tablice[0][a];
		delete [] tablice[0];
		delete [] tablice[1];
		
	return wynik;
}
string Kurs::decodeText(const string &oryginal)
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
string Kurs::encodeText(const string &oryginal)
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
void Kurs::increaseNKnownWords(const short int &quantity)
{
	nKnownSingleWords += quantity;
}
void Kurs::saveKurs(const string &filename, const string &repetitionAnnFileName, const string &repetitionAnnTrainingDataFileName) const
{	
	ofstream file;
	file.open(filename.c_str());
	if(!file.is_open())throw Error::newError(Error::ERROR_OPEN_FILE, "", __LINE__, __FILE__);
	file << "new version" << endl;
	file << wordl1.size() << endl;
	file << wordl2.size() << endl;
	file << nConnections << endl;
	file << maxOplev << endl;
	file << repetitionAnnFileName << endl;
	file << repetitionAnnTrainingDataFileName << endl;
	file << repetitionAnnTrainingData->getMaxLines() << endl;
	
	repetitionAnn->save(repetitionAnnFileName);
	repetitionAnnTrainingData->save(repetitionAnnTrainingDataFileName);

	for(uint i = 0; i < wordl1.size(); i++) {
		file << wordl1[i]->getSpelling() << endl;
	}
	for(uint i = 0; i < wordl2.size(); i++) {
		file << wordl2[i]->getSpelling() << endl;
		wordl2[i]->id = i+wordl1.size();
	}
	int inSecondWord;
	for(uint i = 0; i < wordl1.size(); i++) {
        for(uint j = 0; j < wordl1[i]->getNumberMeanings(); j++) {
            if(wordl1[i]->getMeaning(j) != emptySingleWord) {
                file << i << "\t";
                file << wordl1[i]->getMeaning(j)->id << "\t";
                file << wordl1[i]->getRepetitionLevelNumber(j) << "\t";
                inSecondWord = wordl1[i]->getMeaning(j)->findMeaning(wordl1[i]);
                file << wordl1[i]->getMeaning(j)->getRepetitionLevelNumber(inSecondWord) << "\t";
                file << wordl1[i]->getTimeLastRepetition(j) << endl;
            }
        }
	}
	file.close();
	
}