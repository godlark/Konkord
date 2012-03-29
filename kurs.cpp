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
typedef unsigned short int ushort;

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
	for(int i = 0; i < repetitionsLevels.size(); i++) {
		assert(repetitionsLevels[i] != NULL);
		delete repetitionsLevels[i];
	}
	assert(emptyWord != NULL);
	delete emptyWord;
}
void Kurs::addSingleWords(const vector<string> &spellings, const vector<string> &sounds, const vector<string> &meanings_spelling, const vector<string> &meanings_sound) {
	//ASSERT IN
	assert(spellings.size() == sounds.size() && meanings_spelling.size() == meanings_sound.size());
	assert(spellings.size() != 0 && meanings_spelling.size() != 0);
	
	SingleWord *tempsw;
	for(ushort i = 0; i < spellings.size(); i++) {
		tempsw = new SingleWord(spellings[i], sounds[i]);
		wordl1.push_back(tempsw);
	}
	for(ushort i = 0; i < meanings_spelling.size(); i++) {
		tempsw = new SingleWord(meanings_spelling[i], meanings_sound[i]);
		wordl2.push_back(tempsw);
		for(ushort j = wordl1.size() - sounds.size(); j < wordl1.size(); j++) {
			SingleWord::connectSingleWords(wordl2[wordl2.size()-1], wordl1[j], 0, 0, 0); //łączy ostatnio dodane słowo dodane do wordl2 z...
			numberConnections++;
		}
	}
	qAllSingleWords = wordl1.size() + wordl2.size();
	ifChangeKurs = true;
	
	//ASSERT OUT
	for(int i = 0; i < spellings.size(); i++) {
		assert(wordl1[wordl1.size()-spellings.size()+i]->getSpelling() == spellings[i]);
		for(int j = 0; j < meanings_spelling.size(); j++) {
			assert(wordl2[wordl2.size()-meanings_spelling.size()+j]->getSpelling() == meanings_spelling[j]);
			assert(wordl1[wordl1.size()-spellings.size()+i]->isConnectedWith(wordl2[wordl2.size()-meanings_spelling.size()+j]));
		}
	}
}
void Kurs::addSingleWord(const SingleWord &singleWord, const ushort &where) {
	//ASSERT IN
	
	ushort number;
	if(where == 0) {
		wordl1.push_back(new SingleWord(&singleWord));
		number = wordl1.size()-1;
		SingleWord::connectSingleWords(wordl1[number], emptyWord, 0, 0, 0);
	}
	else {
		wordl2.push_back(new SingleWord(&singleWord));
		number = wordl1.size() + wordl2.size() - 1;
		SingleWord::connectSingleWords(wordl2[number-wordl1.size()], emptyWord, 0, 0, 0);
	}
	qAllSingleWords = wordl1.size() + wordl2.size();
	ifChangeKurs = true;
}
void Kurs::connectSingleWords(const ushort &number1, const ushort &number2) {
	//ASSERT IN
	assert(number1 < wordl1.size() && (number2 < wordl1.size()+wordl2.size() && number2 > wordl1.size()));
	
	if(wordl1[number1]->isConnectedWith(emptyWord))SingleWord::disconnectSingleWords(wordl1[number1], emptyWord);
	if(wordl2[number2-wordl1.size()]->isConnectedWith(emptyWord))SingleWord::disconnectSingleWords(wordl2[number2-wordl1.size()], emptyWord);
	SingleWord::connectSingleWords(wordl1[number1], wordl2[number2-wordl1.size()], 0, 0, 0);
	numberConnections++;
	ifChangeKurs = true;
}
void Kurs::disconnectSingleWords(const ushort &number1, const ushort &number2) {
	//ASSERT IN
	assert(number1 < wordl1.size() && (number2 < wordl1.size()+wordl2.size() && number2 > wordl1.size()));
	
	SingleWord::disconnectSingleWords(wordl1[number1], wordl2[number2-wordl1.size()]);
	numberConnections--;
	if(wordl1[number1]->getNumberMeanings() == 0)SingleWord::connectSingleWords(wordl1[number1], emptyWord, 0, 0, 0);
	if(wordl2[number2-wordl1.size()]->getNumberMeanings() == 0)SingleWord::connectSingleWords(wordl2[number2-wordl1.size()], emptyWord, 0, 0, 0);
	ifChangeKurs = true;
}
void Kurs::delSingleWord(const ushort &number) {
	//ASSERT IN
	assert(number < wordl1.size() || (number < wordl1.size()+wordl2.size() && number > wordl1.size()));
	
	ushort qAllMeanings;
	SingleWord* meaning;
	vector<SingleWord*>::iterator position;
	if(number < wordl1.size()) {
		qAllMeanings = wordl1[number]->getNumberMeanings();
		for(int i = 0; i < qAllMeanings; i++) {
			meaning = (wordl1[number]->getMeaning(i)); //znaczenia słowa z tablicy wordl1 jest w tablicy wordl2
			SingleWord::disconnectSingleWords(wordl1[number], meaning);
			if(meaning->getNumberMeanings() == 0) {
				SingleWord::connectSingleWords(meaning, emptyWord, 0, 0, 0);
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
				SingleWord::connectSingleWords(meaning, emptyWord, 0, 0, 0);
			}
			numberConnections--;
		}
		delete wordl2[number-wordl1.size()];
		wordl2.erase(wordl2.begin() + number-wordl1.size());
	}
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
	//howManyWords jest liczbą słów do przepytania, rozmiar zwracanego vectora to liczba słów do przepytania i liczba połączeń do powtórzenia
	if(howManyWords > wordl1.size() + wordl2.size())howManyWords = wordl1.size() + wordl2.size();
	ushort AhowManyWords = 0;
	priority_queue<WordToRepetition, vector<WordToRepetition>, compareWords>Q;
	WordToRepetition wtr;
	time_t nowTime = time(NULL);
	//pobieranie słów z tablic i dodawanie ich do kolejki priorytetowej sortującej według zmiennej priority
	
	for(ushort i = 0; i < wordl1.size(); i++) {
		if(wordl1[i]->isConnectedWith(emptyWord) || !wordl1[i]->isKnown())continue; //ze słów pustych i nie poznanych nie można przeptywać
		
		ushort countConnections = wordl1[i]->getNumberMeanings();
		wtr.priority = 0;
		wtr.parttime = 0;
		for(ushort j = 0; j < countConnections; j++) {;
			wtr.parttime += nowTime-wordl1[i]->getTimeLastRepetition(j);
			wtr.priority += makePredictions(nowTime-wordl1[i]->getTimeLastRepetition(j), wordl1[i]->getWhichRepetition(j));
		}
		wtr.priority /= countConnections;
		wtr.parttime /= countConnections;
		wtr.nr_word = i;
		if(wtr.priority < 700) {
			AhowManyWords++;
		}
		Q.push(wtr);
		
	}
	for(ushort i = 0; i < wordl2.size(); i++) {
		if(wordl2[i]->isConnectedWith(emptyWord) || !wordl2[i]->isKnown())continue; //ze słów pustych i nie poznanych nie można przeptywać
		
		ushort countConnections = wordl2[i]->getNumberMeanings();
		wtr.priority = 0;
		wtr.parttime = 0;
		for(ushort j = 0; j < countConnections; j++) {
			wtr.parttime += nowTime-wordl2[i]->getTimeLastRepetition(j);
			wtr.priority += makePredictions(nowTime-wordl2[i]->getTimeLastRepetition(j), wordl2[i]->getWhichRepetition(j));
		}
		wtr.priority /= countConnections;
		wtr.parttime /= countConnections;
		wtr.nr_word = i+wordl1.size();
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
	SingleWord *sword;
	for(ushort i = 0; i < howManyWords; i++) {
		WordsToRepetition.push_back(Q.top().nr_word);//dodaje słowo do przepytania
		
		if(Q.top().nr_word < wordl1.size())sword = wordl1[Q.top().nr_word];
		else sword = wordl2[Q.top().nr_word-wordl1.size()];
		
		int whereInOther;
		for(ushort j = 0; j < sword->getNumberMeanings(); j++) {
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
double Kurs::makePredictions(const int &time, const ushort &which_repetition) const {
	double *inputs = new double[1];
	inputs[0] = 1/(double)time;
	double *outputs = repetitionsLevels[which_repetition]->run(inputs);
	return outputs[0]*1000;
}
void Kurs::repairPredictions(const ushort &word_number, const time_t &czas, vector<double> &oplev_connections) {
	//ASSERT IN
	assert(word_number < wordl1.size()+wordl2.size());
	SingleWord *sword = word_number < wordl1.size() ? wordl1[word_number] : wordl2[word_number-wordl1.size()];
	assert(oplev_connections.size() == sword->getNumberMeanings());

	double max_oplev = 6;
	time_t nowTime = time(NULL);
	double predicted_score;
	double deviation;
	double *inputs = new double[1];
	double *outputs = new double[1];
	for(ushort i = 0; i < sword->getNumberMeanings(); i++) {
		predicted_score = 0;
		deviation = 0;
		
		if(oplev_connections[i] > max_oplev)oplev_connections[i] = max_oplev;
		oplev_connections[i] *= 1000/max_oplev;
		
		predicted_score = makePredictions(nowTime-sword->getTimeLastRepetition(i), sword->getWhichRepetition(i));
		
		// FANN TRAINING
		inputs[0] = 1/(double)(nowTime-sword->getTimeLastRepetition(i));
		outputs[0] = oplev_connections[i]/1000;
		repetitionsLevels[sword->getWhichRepetition(i)]->train(inputs, outputs);
		// END FANN TRAINING
		
		sword->setTimeLastRepetition(i, nowTime);	
		deviation = ((oplev_connections[i]-predicted_score)*1000)/predicted_score;
		ushort repetition = sword->getWhichRepetition(i);
		if(deviation > 0) {
			repetition++;
			if(repetition == repetitionsLevels.size()) {
				repetitionsLevels.push_back(NULL);
				repetitionsLevels[repetition] = new FANN::neural_net(*repetitionsLevels[repetition-1]);
			}
		}
		sword->setWhichRepetition(i, repetition);
	}
	ifChangeKurs = true;
	
	//ASSERT OUT
}
void Kurs::setSingleWord(const ushort &number, const string &spelling, const string &sound) {
	//ASSERT IN
	assert(number < wordl1.size()+wordl2.size());
	
	SingleWord *sword = number < wordl1.size() ? wordl1[number] : wordl2[number-wordl1.size()];
	sword->setSpelling(spelling);
	sword->setSound(sound);
}
void Kurs::setMeaningForSingleWord(const ushort &number_word, const ushort &number_meaning, const string &spelling, const string &sound) {
	//ASSERT IN
	assert(number_word < wordl1.size()+wordl2.size());
	SingleWord *sword = number_word < wordl1.size() ? wordl1[number_word] : wordl2[number_word-wordl1.size()];
	assert(number_meaning < sword->getNumberMeanings());
	assert(sword->getMeaning(number_meaning) != emptyWord);
	
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
	//ASSERT IN
	assert(number1 < wordl1.size() + wordl2.size() && number2 < wordl1.size() + wordl2.size());
	assert(number1 != number2);
	
	if(wordl1[number1]->getMeaning(0) == emptyWord)SingleWord::disconnectSingleWords(wordl1[number1], emptyWord);
	if(wordl2[number2-wordl1.size()]->getMeaning(0) == emptyWord)SingleWord::disconnectSingleWords(wordl2[number2-wordl1.size()], emptyWord);
	if(number1 >= wordl1.size() && number2 >= wordl1.size()) {
		wordl2[number1-wordl1.size()]->joinOtherSingleWord(wordl2[number2-wordl1.size()]);
		if(wordl2[number2-wordl1.size()]->isKnown() == false)qKnownSingleWords--;
		wordl2.erase(wordl2.begin() + number2 - wordl1.size());
		if(wordl2[number1-wordl1.size()]->getNumberMeanings() == 0)SingleWord::connectSingleWords(wordl2[number1-wordl1.size()], emptyWord, 0, 0, 0);
	}
	else if(number1 < wordl1.size() && number2 < wordl1.size()) {
		wordl1[number1]->joinOtherSingleWord(wordl1[number2]);
		if(wordl1[number2]->isKnown() == false)qKnownSingleWords--;
		wordl1.erase(wordl1.begin() + number2);
		if(wordl1[number1]->getNumberMeanings() == 0)SingleWord::connectSingleWords(wordl1[number1], emptyWord, 0, 0, 0);
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
	
	repetitionsLevels = vector<FANN::neural_net *>(1);
	repetitionsLevels[0] = new FANN::neural_net();
	repetitionsLevels[0]->create_standard(3, 1, 10, 1);

	
	ROE = &_ROE;
	emptyWord = new SingleWord("BRAK ZNACZENIA", "");
}
Kurs::Kurs(const string &file_to_open,  RegisterOfErrors &_ROE)
{
	emptyWord = new SingleWord("BRAK ZNACZENIA", "");
	ROE = &_ROE;
	
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
		
		string ann_filename;
		for(int i = 0; i < qRepetition; i++) {
			file >> ann_filename;
		file.ignore(INT_MAX, '\n');
		
		repetitionsLevels.push_back(NULL);
		repetitionsLevels[i] = new FANN::neural_net();
		repetitionsLevels[i]->create_from_file(ann_filename);
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
		SingleWord::connectSingleWords(wordl1[i], emptyWord, 0, 0, 0);
		}
		for(ushort i = 0; i < numberWordsSL; i++) {
		getline(file, spelling);
		sword.setSpelling(spelling);
			wordl2.push_back(new SingleWord(sword));
		SingleWord::connectSingleWords(wordl2[i], emptyWord, 0, 0, 0);
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
		assert(number1 < wordl1.size() && (number2 < wordl1.size()+wordl2.size() && number2 >= wordl1.size()));
		if(emptyWord->isConnectedWith(wordl1[number1]))SingleWord::disconnectSingleWords(wordl1[number1], emptyWord);
		if(emptyWord->isConnectedWith(wordl2[number2-wordl1.size()]))SingleWord::disconnectSingleWords(wordl2[number2-wordl1.size()], emptyWord);
		assert(!wordl1[number1]->isConnectedWith(wordl2[number2-wordl1.size()]));
		SingleWord::connectSingleWords(wordl1[number1], wordl2[number2-wordl1.size()], which_repetition, which_repetition2, last_repetition);
		}

		for(ushort i = 0; i < numberWordsFL; i++) {
		if(wordl1[i]->isKnown())qKnownSingleWords++;
		}
		for(ushort i = 0; i < numberWordsSL; i++) {
		if(wordl2[i]->isKnown())qKnownSingleWords++;
		}
	}
	else {
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
		
		double new_repetitionLevels;
		time_t new_repetitionTime;
		double new_repetitionAverageError;
		double new_repetitionStabilization;
		for(int i = 0; i < qRepetition; i++) {
		for(int j = 0; j < 12; j++) {
			file >> new_repetitionLevels;
		}
		file >> new_repetitionTime;
		file >> new_repetitionAverageError;
		file >> new_repetitionStabilization;
		file.ignore(INT_MAX, '\n');
			
		repetitionsLevels.push_back(NULL);
		repetitionsLevels[i] = new FANN::neural_net();
		repetitionsLevels[i]->create_standard(3, 1, 10, 1);
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
		SingleWord::connectSingleWords(wordl1[i], emptyWord, 0, 0, 0);
		}
		for(ushort i = 0; i < numberWordsSL; i++) {
		getline(file, spelling);
		sword.setSpelling(spelling);
			wordl2.push_back(new SingleWord(sword));
		SingleWord::connectSingleWords(wordl2[i], emptyWord, 0, 0, 0);
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
		assert(number1 < wordl1.size() && (number2 < wordl1.size()+wordl2.size() && number2 >= wordl1.size()));
		if(emptyWord->isConnectedWith(wordl1[number1]))SingleWord::disconnectSingleWords(wordl1[number1], emptyWord);
		if(emptyWord->isConnectedWith(wordl2[number2-wordl1.size()]))SingleWord::disconnectSingleWords(wordl2[number2-wordl1.size()], emptyWord);
		assert(!wordl1[number1]->isConnectedWith(wordl2[number2-wordl1.size()]));
		SingleWord::connectSingleWords(wordl1[number1], wordl2[number2-wordl1.size()], which_repetition, which_repetition2, last_repetition);
		}

		for(ushort i = 0; i < numberWordsFL; i++) {
		if(wordl1[i]->isKnown())qKnownSingleWords++;
		}
		for(ushort i = 0; i < numberWordsSL; i++) {
		if(wordl2[i]->isKnown())qKnownSingleWords++;
		}
	}
	file.close();
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
	file << "new version" << endl;
	file << name << endl;
	file << wordl1.size() << endl;
	file << wordl2.size() << endl;
	file << numberConnections << endl;
	file << askQKW << endl;
	file << askQNW << endl;
	file << repetitionsLevels.size() << endl; //dać zmienną rozmiaru
	string ann_filename = file_to_save+"_level";
	for(int i = 0; i < repetitionsLevels.size(); i++) {
		file << ann_filename+char('0'+i) << endl;
		repetitionsLevels[i]->save(ann_filename+char('0'+i));
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


