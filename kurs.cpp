/*
#################################################################################
#                           Konkord 														#
#                      Version 0.0.2009.04.19												#
#               This program was created for learning words									#
#	 		from different languages.											#
#																				#
#    Copyright(C) 2009 Sławomir Domagała										#
#																				#
#    This program is free software: you can redistribute it and/or modify	#
#    it under the terms of the GNU General Public License as published by	#
#    the Free Software Foundation, either version 3 of the License, or		#
#    (at your option) any later version.										#
#																				#
#    This program is distributed in the hope that it will be useful,		#
#    but WITHOUT ANY WARRANTY; without even the implied warranty of		#
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the		#
#    GNU General Public License for more details.								#
#																				#
#    You should have received a copy of the GNU General Public License		#
#    along with this program.  If not, see <http://www.gnu.org/licenses/>	#
#																				#
#    E-mail: godlark@gmail.com													#
#################################################################################		
*/
#include "kurs.hpp"

using namespace std;

string Word::getFirst() const
{
	return this->first;
}
string Word::getSecond() const
{
	return this->second;
}
unsigned int Word::getTime_lastud() const
{
	return this->time_lastud;
}
USI Word::getHralev() const
{
	return this->hralev;
}
USI Word::getOplev() const
{
	return this->oplev;
}
void Word::setFirst(string _first)
{
	first = _first;
}
void Word::setSecond(string _second)
{
	second = _second;
}
void Word::setTime_lastud(unsigned int time_lastud)
{
	this->time_lastud = time_lastud;
}
void Word::setHralev(int _hralev)
{
	if(_hralev > MAX_HRALEV)hralev = MAX_HRALEV;
	else if(_hralev < MIN_HRALEV)hralev = MIN_HRALEV;
	else hralev = _hralev;
}
void Word::setOplev(USI _oplev)
{
	if(_oplev > MAX_OPLEV)oplev = MAX_OPLEV;
	else if(_oplev < MIN_OPLEV)oplev = MIN_OPLEV;
	else oplev = _oplev;
}
void Word::setOplev(time_t nowTime)
{
	unsigned int max_way_time = ceil((oplev*86400)/hralev);
	unsigned int way_time = (unsigned int)nowTime - time_lastud;
	USI old_oplev = oplev;	
	if(way_time > max_way_time)way_time = max_way_time;	
	setOplev((USI)(oplev-((way_time*hralev)/86400)));
	if(oplev != old_oplev)setTime_lastud(nowTime);
}
Word::Word(string _first, string _second)
{
	first = _first;
	second = _second;
	hralev = MIN_HRALEV;
	oplev = MIN_OPLEV;
	time_lastud = 0;
}
Word::Word()//Word("","")
{
	first = "";
	second = "";
	hralev = MIN_HRALEV;
	oplev = MIN_OPLEV;
	time_lastud = 0;
}
Word Word::newWord(string first, string second)//trzeba to wykorzystać, świeżo dodana funkcja
{
	Word word(first, second);
	return word;
}
istream &operator >>(istream &str, Word &word)
{
	string line;
	size_t found;
	getline(str, line);
	found=line.find('\t');
	printf("%s\n", line.c_str());
	if(found == string::npos)
	{
		str.clear(str.rdstate() | ios::failbit);
	}
	if(found == 0)word.setFirst("");
	else word.setFirst(line.substr(0, found));
	if(found == line.length()-1)word.setSecond("");
	else word.setSecond(line.substr(found+1));
	return str;
}
Kurs::Kurs(const string &name, const string &lang1, const string &lang2, const string &filename, const USI &askQKW, const USI &askQNW,  RegisterOfErrors &_ROE)
{
	this->name = name;
	this->lang1 = lang1;
	this->lang2 = lang2;
	this->filename = filename;
	this->qAllWords = 0;
	this->qKnownWords = 0;
	this->askQKW = askQKW;
	this->askQNW = askQNW;
	this->ifChangeKurs = true;
	ROE = &_ROE;
}
Kurs::Kurs(string file_to_open,  RegisterOfErrors &_ROE)
{
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
	filename = decode_text(_filename);
	fscanf(plik, "%hu %hu", &qAllWords, &qKnownWords);
	//koniec wczytywania danych kursu
	USI _hralev, _oplev;
	unsigned int _time_lastud;
	Word *word = new Word();//przeciążyć wczytywanie do Word, oraz zmienić przeciążanie do Word na przeciążanie do pair_string
	for(USI i = 0; i < qAllWords; i++)
	{
		char _first[100], _second[100];
		fscanf(plik, "%s\t%s\t%hu %hu %u\n", _first, _second, &_hralev, &_oplev, &_time_lastud);
		word->setFirst(decode_text(_first));
		word->setSecond(decode_text(_second));
		word->setHralev(_hralev);
		word->setOplev(_oplev);
		word->setTime_lastud(_time_lastud);
		this->words.push_back(*word);
	}
	ROE = &_ROE;
}
void Kurs::addWord(string first, string second)
{
	if(this->qAllWords >= 65535)
	{
		throw Error::newError(Error::OUTPASS_MAX_SIZE_OF_ARRAY, "void Kurs::addWord(string first, string second)", __LINE__, __FILE__);
	}
	words.push_back(Word::newWord(first, second));
	qAllWords = words.size();
	ifChangeKurs = true;
}
void Kurs::addWord(Word &word)
{
	if(this->qAllWords >= 65535)
	{
		throw Error::newError(Error::OUTPASS_MAX_SIZE_OF_ARRAY, "void Kurs::addWord(Word word)", __LINE__, __FILE__);
	}
	words.push_back(word);
	qAllWords = words.size();
	ifChangeKurs = true;
}
void Kurs::aktualizuj()
{
	time_t nowTime;
	ifChangeKurs = true;
	nowTime = time(NULL);
	qKnownWords = 0;
	for(USI i = 0; i < qAllWords; i++)
	{
		words[i].setOplev(nowTime);
		if(words[i].getOplev() != 0)qKnownWords++;	
	}
}
USI Kurs::compare_words(string aa, string bb)
{
	USI a = aa.length();
	USI b = bb.length();
				
	USI **tablice = new USI*[2];
	tablice[0] = new USI[a+1];
	tablice[1] = new USI[a+1];

	tablice[0][0] = 1;
	for(USI i = 1; i <= a; i++)
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
	USI *temp;
	for(USI i = 1; i < b; i++)
	{
		tablice[1][0] = i+1;
		for(USI j = 1; j <= a; j++)
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
	return tablice[0][a];
}
string Kurs::decode_text(string oryginal)
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
void Kurs::delWord(USI number)
{
	if(number >= this->qAllWords)
	{
		throw Error::newError(Error::OUTPASS_ABOVE_SPACE_OF_ARRAY, "void delWord(USI number)", __LINE__, __FILE__);
	}
	words.erase(words.begin()+number);
	qAllWords = words.size();
	ifChangeKurs = true;
}
string Kurs::encode_text(string oryginal)
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
vector<USI> Kurs::findWord(boost::regex searched_string) const
{
	vector<USI> found_words;
	for(USI i = 0; i < qAllWords; i++)
	{
		if(regex_match(words[i].getFirst(), searched_string) || regex_match(words[i].getSecond(), searched_string))
		{
			found_words.push_back(i);
		}
	}
	return found_words;
}
vector<USI> Kurs::getUnknownWords(USI quantityOfWords) const
{
	if(quantityOfWords > this->qAllWords - this->qKnownWords)quantityOfWords = this->qAllWords - this->qKnownWords;
	vector<USI> wordsToAsk;
	for(USI i = 0, j = 0; i < this->qAllWords && j < quantityOfWords; i++)
	{
		if(words[i].getOplev() == 0)
		{
			wordsToAsk.push_back(i);
			j++;
		}
	}
	return wordsToAsk;
}
vector<USI> Kurs::getKnownWords(USI quantityOfWords) const
{
	if(quantityOfWords > qKnownWords)quantityOfWords = qKnownWords;
	priority_queue<WordAndNumber, vector<WordAndNumber>, compareWord> Q;
	WordAndNumber wan;
	for(USI i = 0; i < qAllWords; i++)
	{
		if(words[i].getOplev() != 0)
		{
			wan.slowo = &words[i];
			wan.number = i;
			Q.push(wan);
		}
	}
	vector<USI> wordsToAsk;
	for(USI i = 0; i < quantityOfWords; i++)
	{
		wordsToAsk.push_back(Q.top().number);
		Q.pop();
	}
	return wordsToAsk;
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
USI Kurs::getQAllWords() const
{
	return this->qAllWords;
}
USI Kurs::getQKnownWords() const
{
	return this->qKnownWords;
}
USI Kurs::getAskQKW() const
{
	return this->askQKW;
}
USI Kurs::getAskQNW() const
{
	return this->askQNW;
}
Word Kurs::getWord(USI number) const
{
	if(number >= this->qAllWords)
	{
		throw Error::newError(Error::BAD_ARGUMENT, "Word Kurs::getWord(USI number)", __LINE__, __FILE__);
	}
	return this->words[number];
}
vector<Word> Kurs::getWords(USI &from, USI &_to) const
{
	vector<Word> _words;
	if(from >= this->qAllWords || _to >= this->qAllWords)
	{
		throw Error::newError(Error::OUTPASS_ABOVE_SPACE_OF_ARRAY, "vector<Word> Kurs::getWords(USI &from, USI &_to)", __LINE__, __FILE__);
	}
	if(_to < from && _to != 0)
	{
		throw Error::newError(Error::BAD_ARGUMENT, "vector<Word> Kurs::getWords(USI &from, USI &_to)", __LINE__, __FILE__);
	}
	if(_to == 0)_to = qAllWords-1;
	for(USI i = from; i <= _to; i++)
	{
		_words.push_back(words[i]);
	}
	return _words;
}
void Kurs::increaseQKnownWords(short int quantity)
{
	qKnownWords += quantity;
}
void Kurs::readWordsFromFile(string file_to_open)
{
	ifstream plik;
	plik.open(file_to_open.c_str(), ios::binary);
	if(!plik.is_open())throw Error::newError(Error::ERROR_SAVE_FILE, "void Kurs::readWordsFromFile(string file_to_open)", __LINE__, __FILE__);
	
	USI number_of_words;
	Word *word = new Word();
	plik >> number_of_words;
	string clear_buf; //zostaje biały znak po ilości słów
	getline(plik, clear_buf);
	for(USI i = 0; i < number_of_words; i++)
	{
		plik >> *word;
		if(plik.fail())
		{
			plik.clear(plik.rdstate() & ~ios::failbit);
			ROE->addError(Error::newError(Error::IGNORED_LINE_IN_FILE, "void Kurs::readWordsFromFile(string file_to_open)", __LINE__, __FILE__));
			continue;
		}
		if(plik.eof())throw Error::newError(Error::ERROR_READ_FILE, "void Kurs::readWordsFromFile(string file_to_open)", __LINE__, __FILE__);
		addWord(*word);
	}
	plik.close();
}
void Kurs::repairWord(USI numberOfWords, USI krakl, double czas, double oplev)
{
	//krakl is number of word in element Word, what user wrote
	//now is allowed for number 0 and 1, where 0 marks word in first language, 1 marks word in second language
	if(krakl == 0)czas /= words[numberOfWords].getFirst().length();
	else if(krakl == 1)czas /= words[numberOfWords].getSecond().length();
	
	if(oplev > 1000)oplev = 1000;
	oplev /= czas;
	int procent = (((words[numberOfWords].getOplev()*1000)/oplev)-1000)/2;
	
	words[numberOfWords].setHralev((words[numberOfWords].getHralev()*procent)/1000+words[numberOfWords].getHralev());
	words[numberOfWords].setOplev((USI)oplev);
	words[numberOfWords].setTime_lastud(time(NULL));
	
	ifChangeKurs = true;
}
void Kurs::saveKurs(string file_to_save)
{
	FILE *plik;
	plik = fopen(file_to_save.c_str(), "w");
	if(plik == NULL)throw Error::newError(Error::ERROR_SAVE_FILE, "Kurs::Kurs(string file_to_open)", __LINE__, __FILE__);
	this->ifChangeKurs = false;
	fprintf(plik, "%s\n", encode_text(name).c_str());
	fprintf(plik, "%s\t%s\n", encode_text(lang1).c_str(), encode_text(lang2).c_str());
	fprintf(plik, "%s\t%hu %hu\n", encode_text(file_to_save).c_str(), askQKW, askQNW);
	fprintf(plik, "%hu %hu\n", qAllWords, qKnownWords);
		
	for(USI i = 0; i < qAllWords; i++)
	{
		fprintf(plik, "%s\t%s\t%hu %hu %u\n", encode_text(words[i].getFirst()).c_str(), encode_text(words[i].getSecond()).c_str(), words[i].getHralev(), words[i].getOplev(), words[i].getTime_lastud());
	}
	fclose(plik);
}
void Kurs::setName(string _name)
{
	name = _name;
	ifChangeKurs = true;
}
void Kurs::setLang1(string _lang1)
{
	lang1 = _lang1;
	ifChangeKurs = true;
}
void Kurs::setLang2(string _lang2)
{
	lang2 = _lang2;
	ifChangeKurs = true;
}
void Kurs::setFilename(string _filename)
{
	filename = _filename;
	ifChangeKurs = true;
}
void Kurs::setIfChangeKurs(bool _ifChangeKurs)
{
	ifChangeKurs = _ifChangeKurs;
}
void Kurs::setAskQKW(USI _askQKW)
{
	askQKW = _askQKW;
	ifChangeKurs = true;
}
void Kurs::setAskQNW(USI _askQNW)
{
	askQNW = _askQNW;
	ifChangeKurs = true;
}
void Kurs::setWord(USI number, string first, string second)
{
	if(number >= this->qAllWords)
	{
		throw Error::newError(Error::OUTPASS_ABOVE_SPACE_OF_ARRAY, "void setWord(USI number, string first, string second)", __LINE__, __FILE__);
	}
	words[number].setFirst(first);
	words[number].setSecond(second);
	ifChangeKurs = true;
}