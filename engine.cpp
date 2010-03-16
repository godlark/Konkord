/*
#################################################################################
#						   Konkord 						#								#
#					  Version 0.0.2009.04.19					#							#
#			   This program was created for learning words			#						#
#	 		from different languages.				#							#
#										#										#
#	Copyright(C) 2009 Sławomir Domagała					#					#
#										#										#
#	This program is free software: you can redistribute it and/or modify	#
#	it under the terms of the GNU General Public License as published by	#
#	the Free Software Foundation, either version 3 of the License, or		#
#	(at your option) any later version.					#					#
#										#										#
#	This program is distributed in the hope that it will be useful,		#
#	but WITHOUT ANY WARRANTY; without even the implied warranty of		#
#	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the		#
#	GNU General Public License for more details.				#				#
#										#										#
#	You should have received a copy of the GNU General Public License		#
#	along with this program.  If not, see <http://www.gnu.org/licenses/>	#
#										#										#
#	E-mail: godlark@gmail.com							#						#
#################################################################################		
*/
#include "engine.h"

typedef unsigned short int ushort;
typedef unsigned short int ushort;

//ushort ServiceOfTasks::freeNumber = 4619;

void ServiceOfTasks::setStateActions() {
	if(QOK != 0) {
					
					actionActive[2] = true;
					actionActive[7] = true;
					actionActive[8] = true;
					actionActive[11] = true;
					actionActive[14] = true;
					actionActive[15] = true;
					actionActive[17] = true;
					actionActive[18] = true; //dać warunki jakieś
					if(!saved_courses[activ_course])actionActive[13] = true;
					if(QOK > 1)actionActive[16] = true;
					else actionActive[16] = false;
					if(courses[activ_course]->getQKnownSingleWords() > 0)actionActive[0] = true;
					else actionActive[0] = false;
					if(courses[activ_course]->getQKnownSingleWords() < courses[activ_course]->getQAllSingleWords())actionActive[1] = true;
					else actionActive[1] = false;
					if(courses[activ_course]->getQAllSingleWords() > 0) {
						actionActive[3] = true;
						actionActive[4] = true;
						actionActive[12] = true;
						actionActive[19] = true;
					}
					else {
						actionActive[3] = false;
						actionActive[4] = false;
						actionActive[12] = false;
						actionActive[19] = false;
					}
					if(courses[activ_course]->getQSingleWords_1() > 0 && courses[activ_course]->getQSingleWords_2() > 0) {
						actionActive[5] = true;
						actionActive[6] = true;
					}
					else {
						actionActive[5] = false;
						actionActive[6] = false;
					}
					
				}
				else {
					
					actionActive[0] = false;
					actionActive[1] = false;
					actionActive[2] = false;
					actionActive[3] = false;
					actionActive[4] = false;
					actionActive[5] = false;
					actionActive[6] = false;
					actionActive[7] = false;
					actionActive[8] = false;
					actionActive[11] = false;
					actionActive[12] = false;
					actionActive[13] = false;
					actionActive[14] = false;
					actionActive[15] = false;
					actionActive[16] = false;
					actionActive[17] = false;
					actionActive[18] = false;
					actionActive[19] = false;
				}
}
void ServiceOfTasks::addWord() {
	ushort numberLang = (*dialogWindow)("Jeśli wyrażenie jest w pierwszym języku wpisz 0, jeśli w drugim wpisz inną wartość", 1)._ushort;
	string spelling = (*(*dialogWindow)("Podaj pisownię wyrażenia", 0)._string);
	courses[activ_course]->addSingleWord(SingleWord::newSingleWord(spelling, ""), numberLang == 0 ? 0 : 1);
	(*printMessage)("Dodano słowo", "");
	saved_courses[activ_course] = false;
	setStateActions();
}
void ServiceOfTasks::addWords() {
	string line = (*(*dialogWindow)("Podaj w lini wyrażenia wg schematu: znaczenie_w_pierwszym_języku[tab]I_znaczenie_w_drugim_języku|synonim_I_znaczenie_w_drugim_języku|kolejny_synonim itd.", 0)._string);
	vector<string> spellings;
	vector<string> meanings_spelling;
	vector<string> sounds;
	vector<string> meanings_sound;
	size_t found=line.find('\t');
	if(found == string::npos) {
	   (*printMessage)("Nie znaleziono odstępu [tab]", "");
	}
	if(found == line.length()-1 || found == 0) {
	   (*printMessage)("Po jednej stronie odstępu[tab] nie ma nic", "");
	}
	else {
		Kurs::takeOutSWFromLine(spellings, sounds, line.substr(0, found));
		Kurs::takeOutSWFromLine(meanings_spelling, meanings_sound, line.substr(found+1));
		courses[activ_course]->addSingleWords(spellings, sounds, meanings_spelling, meanings_sound);
		(*printMessage)("Dodano słow", "");
		saved_courses[activ_course] = false;
		setStateActions();
	}
}
void ServiceOfTasks::askKnownWords() {
		ushort number_words;
		time_t atime;
		string spellingWord;
		ushort oplev;
		
		number_words = (*dialogWindow)("Podaj ilość słów, z których chcesz być przepytywany, podaj 0 dla domyślnej wartości ustawionej w kursie", 1)._ushort;
		if(number_words == 0)number_words = courses[activ_course]->getAskQKW();
		vector <ushort> swords = courses[activ_course]->getKnownSingleWords(number_words);
		number_words = swords.size();
		SingleWord const *sword;

		for(ushort i = 0; i < number_words; i++) {
			atime = time(NULL);
			sword = courses[activ_course]->getSingleWord(swords[i]);
			vector<ushort> numbersConnections(2*(sword->getNumberMeanings()));
			vector<double> oplevs(sword->getNumberMeanings());
		char temp1[10];
		sprintf(temp1, "%d/%d", number_words, i);
		(*printMessage)("", temp1);
			(*printMessage)("", "Napisz znaczenia słowa" + ((courses[activ_course]->isSingleWordFLorSL(swords[i]) ? " (poniższe wyrażenie jest w pierwszym języku):\n" : " (poniższe wyrażenie jest w drugim języku):\n") + sword->getSpelling())); //dodać jeszcze wyświetlanie numeru słowa
			for(ushort j = 0; j < sword->getNumberMeanings(); j++) {
				 (*dialogWindow)("Napisz kolejne znaczenie tego słowa", 0);
				 numbersConnections[j*2] = 0;
				 numbersConnections[j*2+1] = j;
			}
			atime = time(NULL) - atime;
			(*printWords)("Poprawna wersja to:", &sword, &swords[i], numbersConnections, sword->getNumberMeanings(), 0);
			char temp[4];
			for(ushort j = 0; j < sword->getNumberMeanings(); j++) {
				sprintf(temp, "%hu", j+1);
				string temp2 = "Na ile oceniasz swoją poprawność znaczenia ";
				temp2 += temp;
				temp2 += " w skali od 1 do 20";
				oplevs[j] = (double)dialogWindow(temp2, 1)._ushort;
				if(oplevs[j] > 20)oplevs[j] = 20;
			}
			courses[activ_course]->repairSingleWord_new(swords[i], atime, oplevs);
		}
		saved_courses[activ_course] = false;
		setStateActions();
}
void ServiceOfTasks::askUnknownWords() {
		ushort number_words;
		time_t atime;
		string spellingWord;
		ushort oplev;
		
		number_words = (*dialogWindow)("Podaj ilość słów, z których chcesz być przepytywany, podaj 0 dla domyślnej wartości ustawionej w kursie", 1)._ushort;
		if(number_words == 0)number_words = courses[activ_course]->getAskQKW();
		vector <ushort> swords = courses[activ_course]->getUnknownSingleWords(number_words);
		number_words = swords.size();
		
		SingleWord const** aswords = new SingleWord const*[number_words];
		ushort * numbers_words = new ushort[number_words];
		vector<ushort> numbersConnections;
		for(ushort i = 0; i < number_words; i++) {
			aswords[i] = courses[activ_course]->getSingleWord(swords[i]);
			numbers_words[i] = swords[i];
			for(ushort j = 0; j < aswords[i]->getNumberMeanings(); j++) {
				numbersConnections.push_back(i);
				numbersConnections.push_back(j);
			}
		}
		(*printWords)("Naciśnij 'ENTER' jeśli się nauczyłeś się słów", aswords, const_cast<ushort* const>(numbers_words), numbersConnections, number_words, -1);
		delete [] aswords;
		delete [] numbers_words;
		
		SingleWord const *sword;
		for(ushort i = 0; i < number_words; i++) {
			atime = time(NULL);
			sword = courses[activ_course]->getSingleWord(swords[i]);
			vector<ushort> numbersConnections(2*sword->getNumberMeanings());
			vector<double> oplevs(sword->getNumberMeanings());
			(*printMessage)("", "Napisz znaczenia słowa:\n" + sword->getSpelling()); //dodać jeszcze wyświetlanie numeru słowa
			for(ushort j = 0; j < sword->getNumberMeanings(); j++) {
				 (*dialogWindow)("Napisz kolejne znaczenie tego słowa", 0);
				 numbersConnections[j*2] = 0;
				 numbersConnections[j*2+1] = j;
			}
			atime = time(NULL) - atime;
			(*printWords)("Poprawna wersja to:", &sword, &swords[i], numbersConnections, sword->getNumberMeanings(), 0);
			char temp[4];
			for(ushort j = 0; j < sword->getNumberMeanings(); j++) {
				sprintf(temp, "%hu", j);
				string temp2 = "Na ile oceniasz swoją poprawność znaczenia ";
				temp2 += temp;
				temp2 += " w skali od 1 do 20";
				oplevs.push_back((double)dialogWindow(temp2, 1)._ushort);
				if(oplevs[j] > 20)oplevs[j] = 20;
			}
			courses[activ_course]->repairSingleWord_new(swords[i], atime, oplevs);
		}
		saved_courses[activ_course] = false;
		setStateActions();
}
void ServiceOfTasks::closeKurs() {
	char znak;
		if(!saved_courses[activ_course]) {
			znak = Yes_No_Cancel("Zapisać zmieniony kurs: "+ courses[activ_course]->getFilename()+" (ODPOWIEDŹ \"Nie\" SPOWODUJE UTRATĘ ZMIAN))");
			if(znak == 1) {
				saveCourse();
				simpleCloseCourse(activ_course);
				setStateActions();
			}
			else if(znak == 0) {
				simpleCloseCourse(activ_course);
				setStateActions();
			}
			else {
				throw Error::newError(Error::CANCELLED, "", __LINE__, __FILE__);
			}
	}
		else {
			simpleCloseCourse(activ_course);
			setStateActions();
		}
}
void ServiceOfTasks::connectWords() {
	ushort numberWord1, numberWord2;
	numberWord1 = (*dialogWindow)("Podaj numer pierwszego wyrażenia, które chcesz połączyć", 1)._ushort;
	numberWord2 = (*dialogWindow)("Podaj numer drugiego wyrażenia, które chcesz połączyć", 1)._ushort;
	SingleWord const *sword;
	try {
		sword = courses[activ_course]->getSingleWord(numberWord1);
	}
	catch (Error &errorek) {
		(*printMessage)("PRZECHWYCONY WYJĄTEK", errorek.toString());
		throw;
	}
	(*printMessage)("Drugie wyrażenie: ", sword->getSpelling());
	try {
		sword = courses[activ_course]->getSingleWord(numberWord2);
	}
	catch (Error &errorek) {
		(*printMessage)("PRZECHWYCONY WYJĄTEK", errorek.toString());
		throw;
	}
	(*printMessage)("Drugie wyrażenie: ", sword->getSpelling());
	try {
		courses[activ_course]->connectSingleWords(numberWord1, numberWord2);
	}
	catch (Error &errorek) {
		(*printMessage)("PRZECHWYCONY WYJĄTEK", errorek.toString());
	}
	(*printMessage)("Połączono słowa", "");
	saved_courses[activ_course] = false;
	setStateActions();
}
void ServiceOfTasks::deleteWord() {
	ushort numberWord;
	numberWord = (*dialogWindow)("Podaj numer słowa, które chcesz usunąć", 1)._ushort;
	SingleWord const *sword;
	try {
		sword = courses[activ_course]->getSingleWord(numberWord);
	}
	catch (Error &errorek) {
		(*printMessage)("PRZECHWYCONY WYJĄTEK", errorek.toString());
		throw;
	}
	vector<ushort> numbersConnections(sword->getNumberMeanings()*2);
	for(ushort j = 0; j < sword->getNumberMeanings(); j++) {
		numbersConnections[j*2] = 0;
		numbersConnections[j*2 + 1] = j;
	}
	(*printWords)("Aktualnie: ", &sword, &numberWord, numbersConnections, numbersConnections.size()/2, 0);
	char znak = Yes_No_Cancel("Czy napewno usunąć?");
	if(znak == 1) {
		courses[activ_course]->delSingleWord(numberWord);
		(*printMessage)("Usunięto", "");
		saved_courses[activ_course] = false;
		setStateActions();
	}
	else if(znak == 0) {
		(*printMessage)("Anulowano", "");
	}
	else {
		(*printMessage)("Anulowano", "");
	}
}
void ServiceOfTasks::disconnectWords() {
	ushort numberWord1, numberWord2;
	numberWord1 = (*dialogWindow)("Podaj numer pierwszego wyrażenia, które chcesz rozłączyć", 1)._ushort;
	numberWord2 = (*dialogWindow)("Podaj numer drugiego wyrażenia, które chcesz rozłączyć", 1)._ushort;
	SingleWord const *sword;
	try {
		sword = courses[activ_course]->getSingleWord(numberWord1);
	}
	catch (Error &errorek) {
		(*printMessage)("PRZECHWYCONY WYJĄTEK", errorek.toString());
		throw;
	}
	(*printMessage)("Drugie wyrażenie: ", sword->getSpelling());
	try {
		sword = courses[activ_course]->getSingleWord(numberWord2);
	}
	catch (Error &errorek) {
		(*printMessage)("PRZECHWYCONY WYJĄTEK", errorek.toString());
		throw;
	}
	(*printMessage)("Drugie wyrażenie: ", sword->getSpelling());
	try {
		courses[activ_course]->disconnectSingleWords(numberWord1, numberWord2);
	}
	catch (Error &errorek) {
		(*printMessage)("PRZECHWYCONY WYJĄTEK", errorek.toString());
	}
	(*printMessage)("Rozłączono słowa", "");
	saved_courses[activ_course] = false;
	setStateActions();
}
void ServiceOfTasks::doAction(ushort number) {
	switch(number) {
		case 1:
			askKnownWords();
			break;
		case 2:
			askUnknownWords();
			break;
		case 3:
			closeKurs();
			break;
		case 4:
			editWord();
			break;
		case 5:
			deleteWord();
			break;
		case 6:
			connectWords();
			break;
		case 7:
			disconnectWords();
			break;
		case 8:
			addWord();
			break;
		case 9:
			addWords();
			break;
		case 10:
			newCourse();
			break;
		case 11:
			openCourse();
			break;
		case 12:
			printInfoCourse();
			break;
		case 13:
			printWordss();
			break;
		case 14:
			saveCourse();
			break;
		case 15:
			saveCourseAs();
			break;
		case 16:
			settingsCourse();
			break;
		case 17:
			switchCourse();
			break;
		case 18:
			readWordsFromFile();
			break;
		case 19:
			repeatWords();
			break;
		case 20:
			findWords();
			break;
	}
}
void ServiceOfTasks::editWord() {
	ushort numberWord;
	numberWord = (*dialogWindow)("Podaj numer słowa, które chcesz edytować", 1)._ushort;
	SingleWord const *sword;
	try {
		sword = courses[activ_course]->getSingleWord(numberWord);
	}
	catch (Error &errorek) {
		(*printMessage)("PRZECHWYCONY WYJĄTEK", errorek.toString());
		throw;
	}
	vector<ushort>numbersConnections;
	for(ushort j = 0; j < sword->getNumberMeanings(); j++) {
		numbersConnections.push_back(0);
		numbersConnections.push_back(j);
	}
	(*printWords)("Aktualnie: ", &sword, &numberWord, numbersConnections, numbersConnections.size()/2, 0);
	ushort what = (*dialogWindow)("Podaj co, chcesz edytować, 0 - główne wyrażenie(po lewej stronie), 1, 2, 3… - dla kolejnych znaczeń tego wyrażenia", 1)._ushort;
	string spelling;
	spelling = (*(*dialogWindow)("Podaj pisownię wyrażenia", 0)._string);
	if(what == 0)courses[activ_course]->setSingleWord(numberWord, spelling, "");
	else courses[activ_course]->setMeaningForSingleWord(numberWord, what-1, spelling, "");
	(*printMessage)("Edytowano", "");
	saved_courses[activ_course] = false;
}
void ServiceOfTasks::newCourse() {
	string name, lang1, lang2, filename;
	ushort askQKW, askQNW;
	
		name = (*(*dialogWindow)("Podaj nazwę kursu", 0)._string);
		lang1 = (*(*dialogWindow)("Podaj nazwę pierwszego języka", 0)._string);
		lang2 = (*(*dialogWindow)("Podaj nazwę drugiego języka", 0)._string);
		filename = (*(*dialogWindow)("Podaj domyślną nazwę pliku, do którego zapisywać kurs", 0)._string);
		askQKW = (*dialogWindow)("Podaj domyślną ilość słówek, z których użytkownik ma być przepytywany", 1)._ushort;
		askQNW = (*dialogWindow)("Podaj domyślną ilość słówek, które użytkownik ma poznawać co każde uruchomienie programu", 1)._ushort;
		
	Kurs *course = new Kurs(name, lang1, lang2, filename, askQKW, askQNW, globalROE);
	/* Otwarcie kursu */
	{
		courses.push_back(course);
				saved_courses.push_back(false);
		QOK++;
		activ_course = QOK-1;
		setStateActions();
		(*printMessage)("Otworzono kurs", "");
	}
}
void ServiceOfTasks::openCourse() {
	string filename = (*(*dialogWindow)("Podaj nazwę pliku do otwarcia.", 0)._string);
	Kurs *course;
	try
	{
			course = new Kurs(filename, globalROE);
	}
	catch (Error &errorek) {
			(*printMessage)("PRZECHWYCONY WYJĄTEK", errorek.toString());
			throw;
		}
	courses.push_back(course);
		saved_courses.push_back(false);
	QOK++;
	activ_course = QOK-1;
	//courses[activ_course]->aktualizuj();
		setStateActions();
}
void ServiceOfTasks::printInfoCourse() const{
		string *descriptions = new string[9];
		Variable *values = new Variable[9];
		descriptions[0] = "Nazwa kursu";
		values[0].type = 0;
		values[0]._string = new string(courses[activ_course]->getName());
		//values[0]._string = courses[activ_course]->getName();
		descriptions[1] = "Nazwa pierwszego języka";
		values[1].type = 0;
		values[1]._string = new string(courses[activ_course]->getLang1());
		descriptions[2] = "Nazwa drugiego języka";
		values[2].type = 0;
		values[2]._string = new string(courses[activ_course]->getLang2());
		descriptions[3] = "Nazwa pliku, do którego domyślnie zapisywany jest kurs";
		values[3].type = 0;
		values[3]._string = new string(courses[activ_course]->getFilename());
		descriptions[4] = "Ilość poznawanych słów co lekcję";
		values[4].type = 1;
		values[4]._ushort = courses[activ_course]->getAskQNW();
		descriptions[5] = "Ilość słów, których chcesz być przepytywany";
		values[5].type = 1;
		values[5]._ushort = courses[activ_course]->getAskQKW();
		descriptions[6] = "Ilość wszystkich słów w kursie";
		values[6].type = 1;
		values[6]._ushort = courses[activ_course]->getQAllSingleWords();
		descriptions[7] = "Ilość poznanych słów";
		values[7].type = 1;
		values[7]._ushort = courses[activ_course]->getQKnownSingleWords();
		descriptions[8] = "Czy kurs został zapisany po dokonaniu zmian";
		values[8].type = 1;
		values[8]._string = courses[activ_course]->isKursChanged() ? new string("NIE") : new string("TAK");
		(*infoWindow)(descriptions, values, 9);
		
		//restore memory
		delete [] descriptions;
		delete [] values;
}
void ServiceOfTasks::printWordss() const {
	ushort from = (*dialogWindow)("Podaj numer słowa, od którego zacząć pobieranie", 1)._ushort;
	ushort ato = (*dialogWindow)("Podaj numer słowa, na którym chcesz zakońćzyć pobieranie, wpisz 0 jeśli do końca", 1)._ushort;
	vector<SingleWord const*> sword_vector = courses[activ_course]->getSingleWords(from, ato); //coś ze wskaźnikiem na stałe
	SingleWord const **swords = new SingleWord const*[sword_vector.size()];
	ushort *numbers = new ushort[sword_vector.size()];
	vector<ushort> numbersConnections;
	for(ushort i = 0; i < sword_vector.size(); i++) {
		swords[i] = sword_vector[i];
		numbers[i] = from + i;
		for(ushort j = 0; j < swords[i]->getNumberMeanings(); j++) {
			numbersConnections.push_back(i);
			numbersConnections.push_back(j);
		}
	}
	(*printWords)("Aby przejść dalej naciśnij 'ENTER'", swords, numbers, numbersConnections, numbersConnections.size()/2, -1);
	delete [] swords;
	delete [] numbers;
}
void ServiceOfTasks::saveCourse() {
	try
	{
		courses[activ_course]->saveKurs(courses[activ_course]->getFilename());
	}
		catch (Error &errorek) {
			(*printMessage)("PRZECHWYCONY WYJĄTEK", errorek.toString());
			throw;
		}
		saved_courses[activ_course] = true;
		actionActive[13] = false;
}
void ServiceOfTasks::saveCourseAs() {
	string filename = (*(*dialogWindow)("Podaj nazwę pliku, do którego chcesz zapisać kurs.", 0)._string);
	try
	{
			courses[activ_course]->saveKurs(filename);
	}
	catch (Error &errorek) {
			(*printMessage)("PRZECHWYCONY WYJĄTEK", errorek.toString());
			throw;
		}
}
void ServiceOfTasks::settingsCourse() {
	string *descriptions = new string[6];
		Variable *values = new Variable[6];
		descriptions[0] = "Nazwa kursu";
		values[0].type = 0;
		values[0]._string = new string(courses[activ_course]->getName());
		descriptions[1] = "Nazwa pierwszego języka";
		values[1].type = 0;
		values[1]._string = new string(courses[activ_course]->getLang1());
		descriptions[2] = "Nazwa drugiego języka";
		values[2].type = 0;
		values[2]._string = new string(courses[activ_course]->getLang2());
		descriptions[3] = "Nazwa pliku, do którego domyślnie zapisywany jest kurs";
		values[3].type = 0;
		values[3]._string = new string(courses[activ_course]->getFilename());
		descriptions[4] = "Ilość poznawanych słów co lekcję";
		values[4].type = 1;
		values[4]._ushort = courses[activ_course]->getAskQNW();
		descriptions[5] = "Ilość słów, których chcesz być przepytywany";
		values[5].type = 1;
		values[5]._ushort = courses[activ_course]->getAskQKW();
		
		values = (*optionWindow)(descriptions, values, 6).v;
		
		courses[activ_course]->setName(*(values[0]._string));
		courses[activ_course]->setLang1(*(values[1]._string));
		courses[activ_course]->setLang2(*(values[2]._string));
		courses[activ_course]->setFilename(*(values[3]._string));
		courses[activ_course]->setAskQNW(values[4]._ushort);
		courses[activ_course]->setAskQKW(values[5]._ushort);
		
		saved_courses[activ_course] = false;
		
		//restore memory
		delete [] descriptions;
		delete [] values;
}
void ServiceOfTasks::simpleCloseCourse(ushort nr_course) {
	vector<Kurs*>::iterator to_deleted = courses.begin();
	//sprawdzić wartości
	delete courses[nr_course];
	courses.erase(to_deleted + nr_course);
	saved_courses.erase(saved_courses.begin() + nr_course);
	QOK--;
	if(QOK == 0)
	{
	activ_course = -1;
	}
	else
	{
		activ_course = 0;
	}
}
void ServiceOfTasks::switchCourse() {
	string *coursesNames = new string[QOK];
		for(ushort i = 0; i < QOK; i++) {
			coursesNames[i] = courses[i]->getName();
		}
		activ_course = (*radioWindow)("Wybierz kurs\n", coursesNames, activ_course, QOK);
		setStateActions();
		delete [] coursesNames;
}
void ServiceOfTasks::readWordsFromFile() {
	string filename = (*((*dialogWindow)("Podaj nazwę pliku", 0)._string));
	string message;
	try {
		message = courses[activ_course]->readSingleWordsFromFile(filename);
	}
	catch (Error &errorek) {
		(*printMessage)("PRZECHWYCONY WYJĄTEK", errorek.toString());
		throw;
	}
	(*printMessage)("KOMUNIKAT", message);
	saved_courses[activ_course] = false;
	setStateActions();
}
bool ServiceOfTasks::isActionActive(ushort numberOfAction) const {
	return actionActive[numberOfAction-1];
}
ushort ServiceOfTasks::getNumberOpenedCourses() const {
	return QOK;
}
bool ServiceOfTasks::closeProgram() {
	while(QOK != 0) {
		try {
			closeKurs();
		}
		catch(Error &errorek) {
			if(errorek.getKindOfError() == Error::CANCELLED) {
						return false;
			}
		}
	}
	return true;
}
void ServiceOfTasks::repeatWords() {//zoptymalizować find do logarytmicznego
	ushort number_connections = (*dialogWindow)("Podaj ilość połączeń, które chcesz powtórzyć", 1)._ushort;
	
	vector<ushort> connectionsToRepetition = courses[activ_course]->getConnectionsToRepetition(number_connections);
	number_connections = connectionsToRepetition.size()/2;
	
	set<ushort> set_numbersWords;
	vector<ushort> numbersConnections(number_connections*2);
	for(ushort i = 0; i < number_connections; i++) {
		set_numbersWords.insert(connectionsToRepetition[i*2]);
	}
	set<ushort>::iterator it;
	ushort i = 0;
	SingleWord const** aswords = new SingleWord const*[set_numbersWords.size()];
	ushort * numbersWords = new ushort[set_numbersWords.size()];
	for(it=set_numbersWords.begin(); it!=set_numbersWords.end(); it++, i++) {
		numbersWords[i] = *it;
		aswords[i] = courses[activ_course]->getSingleWord(numbersWords[i]);
	}
	for(ushort i = 0; i < number_connections; i++) {
		numbersConnections[i*2] = (find(numbersWords, numbersWords+number_connections, connectionsToRepetition[i*2])-numbersWords);
		numbersConnections[i*2 + 1] = connectionsToRepetition[i*2 + 1];
	}
	(*printWords)("Naciśnij 'ENTER' jeśli się nauczyłeś się słów", aswords, const_cast<ushort* const>(numbersWords), numbersConnections, set_numbersWords.size(), -1);
	delete [] aswords;
	delete [] numbersWords;

	saved_courses[activ_course] = false;
	setStateActions();
}
void ServiceOfTasks::findWords() const {
	string temp = *((*dialogWindow)("Podaj wyrażenie regularne zgodne z formatem używanym w Perlu\n", 0)._string);
	boost::regex *searched_string;
	try{
		searched_string = new boost::regex(temp.c_str());
	}
	catch(boost::regex_error re_error){
	Error errorek(Error::BOOST__REGEX_ERROR, "", __LINE__, __FILE__);
		(*printMessage)("PRZECHWYCONY WYJĄTEK", errorek.toString());
		throw;
	}
	vector<ushort> found_words = courses[activ_course]->findWord(*searched_string);
	ushort number_words = found_words.size();
		
	SingleWord const** aswords = new SingleWord const*[number_words];
	ushort * numbers_words = new ushort[number_words];
	vector<ushort> numbersConnections;
	for(ushort i = 0; i < number_words; i++) {
		aswords[i] = courses[activ_course]->getSingleWord(found_words[i]);
		numbers_words[i] = found_words[i];
		for(ushort j = 0; j < aswords[i]->getNumberMeanings(); j++) {
			numbersConnections.push_back(i);
			numbersConnections.push_back(j);
		}
	}
	(*printWords)("Aby kontynuować, naciśnij 'ENTER'", aswords, const_cast<ushort* const>(numbers_words), numbersConnections, number_words, -1);
}
