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
#include "nakladka.hpp"

using namespace std;

extern string* Error::DescriptionOfErrors;

Menu::Menu()
{
	QOK = 0;
	activ_kurs = NULL;
	nr_activ_kurs = -1;
	ilosc_opcji_0 = 9;
	ilosc_opcji_3 = 12;
	//opcje menu głównego 
	tekst_opcji_0 = new string[ilosc_opcji_0];
	tekst_opcji_0[0] = "Zamknij program";
	tekst_opcji_0[1] = "Nowy kurs";
	tekst_opcji_0[2] = "Otwórz kurs";
	tekst_opcji_0[3] = "Kurs ->";
	tekst_opcji_0[4] = "Przełącz kurs";
	tekst_opcji_0[5] = "Zapisz kurs";
	tekst_opcji_0[6] = "Zapisz kurs jako...";
	tekst_opcji_0[7] = "Zamknij kurs";
	tekst_opcji_0[8] = "O programie";
	activ_opcji_0 = new bool[ilosc_opcji_0];
	//opcje podmenu nr 3
	tekst_opcji_3 = new string[ilosc_opcji_3];
	tekst_opcji_3[0] = "Zamknij podmenu";
	tekst_opcji_3[1] = "Zmień domyślne ustawienia kursu";
	tekst_opcji_3[2] = "Wypisz informacje na temat kursu";
	tekst_opcji_3[3] = "Dodaj słowo";
	tekst_opcji_3[4] = "Wypisz słowo";
	tekst_opcji_3[5] = "Wypisz słowa";
	tekst_opcji_3[6] = "Edytuj słowo";
	tekst_opcji_3[7] = "Usuń słowo";
	tekst_opcji_3[8] = "Przepytaj ze starych słów";
	tekst_opcji_3[9] = "Naucz mnie nowych słów";
	tekst_opcji_3[10] = "Wczytaj słowa z pliku";
	tekst_opcji_3[11] = "Znajdź...";
	activ_opcji_3 = new bool[ilosc_opcji_3];
}
void Menu::printOptions(string *&tekst_opcji, bool *&activ_opcji, USI ilosc_opcji)
{
	printf("Aby wybrać opcję, wpisz numer, który znajduje się przy niej. Jeśli przed opcją jest \'#\' to opcja jest nieaktywna.\n");
	for(int i = 0; i < ilosc_opcji; i++)
	{
		if(!activ_opcji[i])printf("%c ", '#');
		printf("%hu %s\n", i, tekst_opcji[i].c_str());
	}
}
USI Menu::scanfOption(bool *&activ_opcji, USI ilosc_opcji)
{
	USI wybor;
	scanf("%hu", &wybor);
	if((wybor >= ilosc_opcji || !activ_opcji[wybor]))return ilosc_opcji; //oznacza, że nieprawidłowe
	else return wybor;
}
void Menu::menu_3()
{
	short int wybor = 0;
	USI option1;
	USI option2;
	string _option1;
	string _option2;
	Word word;
	bool error = false;
	char znak;
	do
	{
		zaktualizuj_menu_3();
		if(wybor >= 0)
		{
			this->printOptions(this->tekst_opcji_3, this->activ_opcji_3, this->ilosc_opcji_3);
			wybor = this->scanfOption(this->activ_opcji_3, this->ilosc_opcji_3);
		}
		else
		{
			wybor *= -1;
		}
		switch(wybor)
		{
			case 0:
				printf("Wybrałeś opcję \"%s\"\n", this->tekst_opcji_3[0].c_str());
				break;
			case 1:
				printf("Wybrałeś opcję \"%s\"\n", this->tekst_opcji_3[1].c_str());
				settingsKurs();
				break;
			case 2:
				printf("Wybrałeś opcję \"%s\"\n", this->tekst_opcji_3[2].c_str());
				printInfoKurs();
				break;
			case 3:
			{
				printf("Wybrałeś opcję \"%s\"\n", this->tekst_opcji_3[3].c_str());
				printf("Podaj słowo w pierwszym języku\n");
				getline(cin, _option1);
				getline(cin, _option1);
				printf("Podaj słowo w drugim języku\n");
				getline(cin, _option2);
				try
				{
					activ_kurs->addWord(_option1, _option2);
				}
				catch(Error &errorek)
				{
					at_error(errorek, error, wybor);
				}
				if(!error)printf("Dodanie słowa powiodło się. \n");
				break;
			}
			case 4:
			{
				printf("Wybrałeś opcję \"%s\"\n", this->tekst_opcji_3[4].c_str());
				printf("Podaj numer słowa.\n");
				scanf("%hu", &option1);
				try
				{
					word = activ_kurs->getWord(option1);
				}
				catch(Error &errorek)
				{
					at_error(errorek, error, wybor);
				}
				if(!error)printf("%s\t%s\n", word.getFirst().c_str(), word.getSecond().c_str());
				break;
			}
			case 5:
			{
				printf("Wybrałeś opcję \"%s\"\n", this->tekst_opcji_3[5].c_str());
				printf("Podaj numer słowa, od którego zacząć pobierania słów.\n");
				scanf("%hu", &option1);
				printf("Podaj numer słowa, na którym zakończyć pobieranie. Jeśli wpiszesz 0, słowa będą pobierane do końca vectora.\n");
				scanf("%hu", &option2);
				vector<Word> words;
				try
				{
					words = activ_kurs->getWords(option1, option2);
				}
				catch(Error &errorek)
				{
					at_error(errorek, error, wybor);
				}
				if(!error)
				{   
					USI rozmiar = option2-option1+1;
					for(USI i = 0; i < rozmiar; i++)
					{
						printf("%hu. %s\t%s\n", i+option1, words[i].getFirst().c_str(), words[i].getSecond().c_str());
					}
				}
				break;
			}
			case 6:
			{
				printf("Wybrałeś opcję \"%s\"\n", this->tekst_opcji_3[6].c_str());
				printf("Podaj numer słowa, które chcesz wyedytować.\n");
				scanf("%hu", &option1);
				try
				{
					word = activ_kurs->getWord(option1);
				}
				catch(Error &errorek)
				{
					at_error(errorek, error, wybor);
				}
				if(!error)
				{
					printf("%s\t%s\n", word.getFirst().c_str(), word.getSecond().c_str());
					printf("Podaj słowo w pierwszym języku(wpisz '*', a słowo w pierwszym języku zostanie niezmienione)\n");
					getline(cin, _option1);
					getline(cin, _option1);
					if(_option1 == "*")_option1 = word.getFirst();
					printf("Podaj słowo w drugim języku(wpisz '*', a słowo w drugim języku zostanie niezmienione)\n");
					getline(cin, _option2);
					if(_option2 == "*")_option2 = word.getSecond();
					activ_kurs->setWord(option1, _option1, _option2);//nie ma sensu łapania wyjątku, ponieważ na 100% go nie będzie[patrz łapanie wyjątku funkcji getWord()
				}
				break;
			}
			case 7:
			{
				printf("Wybrałeś opcję \"%s\"\n", this->tekst_opcji_3[7].c_str());
				printf("Podaj numer słowa, które chcesz usunąć.\n");
				scanf("%hu", &option1);
				try
				{
					word = activ_kurs->getWord(option1);
				}
				catch(Error &errorek)
				{
					at_error(errorek, error, wybor);
				}
				if(!error)
				{
					char znak;
					printf("%s\t%s\n", word.getFirst().c_str(), word.getSecond().c_str());
					printf("Czy napewno chcesz usunąć to słowo?\n");
					do
					{
						printf("Tak(T)/Nie(N): ");
						scanf("%c", &znak);
						if(znak == 'T')
						{
							activ_kurs->delWord(option1);
							printf("Usunięto słowo.\n");
							//nie ma sensu łapania wyjątku, ponieważ na 100% go nie będzie[patrz łapanie wyjątku funkcji getWord()
						}
						else if(znak == 'N')printf("Anulowano.\n");								
					}while(znak != 'T' && znak != 'N');
				}
				break;
			}
			case 8:
				printf("Wybrałeś opcję \"%s\"\n", this->tekst_opcji_3[8].c_str());
				przepytaj_ze_starych();
				break;
			case 9:
				printf("Wybrałeś opcję \"%s\"\n", this->tekst_opcji_3[9].c_str());
				naucz_nowych();
				break;
			case 10:
			{
				printf("Wybrałeś opcję \"%s\"\n", this->tekst_opcji_3[10].c_str());
				printf("Podaj nazwę pliku, w którym znajdują się słówka"
					"Format pliku:"
					"*pierwsza linia - liczba bez znaku, oznaczające liczbę słówek - oznaczona jako 'n'"
					"*kolejne 'n' lini - słówko w pierwszym języku + znak tabulacji + słówko w drugim języku\n");
				getline(cin, _option1);
				getline(cin, _option1);
				try
				{
					activ_kurs->readWordsFromFile(_option1);
				}
				catch(Error &errorek)
				{
					at_error(errorek, error, wybor);
				}
				break;
			}
			case 11:
			{
				printf("Wybrałeś opcję \"%s\"\n", this->tekst_opcji_3[11].c_str());
				printf("Podaj wyrażenie regularne zgodne z formatem używanym w Perlu\n");
				getline(cin, _option1);
				getline(cin, _option1);
				boost::regex *searched_string;
				try
				{
					searched_string = new boost::regex(_option1.c_str());
				}
				catch(boost::regex_error re_error)
				{
					Error errorek(Error::BOOST__REGEX_ERROR, "void Menu::menu_3()", __LINE__, __FILE__);
					at_error(errorek, error, wybor);
				}
				if(!error)
				{
					vector<USI> found_words = activ_kurs->findWord(*searched_string);
					for(USI i = 0; i < found_words.size(); i++)
					{
						printf("%hu %s %s\n", found_words[i], activ_kurs->getWord(found_words[i]).getFirst().c_str(), activ_kurs->getWord(found_words[i]).getSecond().c_str());
					}
				}
				break;
			}
			default:
				printf("Podałeś nieprawidłowy numer opcji.\n");
						
		}
		printf("\n");
		error = false;
	}while(wybor != 0);
}
void Menu::settingsKurs()
{
	string zmienna;
	USI zmienna2;
	USI wybor = 0;
	do
	{
		printf("Wybierz co chcesz zmienić: \n"
			"0. Nic\n"
			"1. Nazwę kursu\n"
			"2. Nazwę pierwszego języka\n"
			"3. Nazwę drugiego języka\n"
			"4. Nazwę pliku, do którego domyślnie zapisywany jest kursu\n"
			"5. Ilość słów, które chcesz poznawać co lekcję\n"
			"6. Ilość słów, z których chcesz być przepytywany co lekcję\n");
		scanf("%hu", &wybor);
		switch(wybor)
		{
			case 0:
				printf("Nic nie chcesz zmieniać\n");
				break;
			case 1:
				printf("Chcesz zmienić nazwę kursu\n");
				printf("Obecna nazwa kursu: \"%s\"\n", activ_kurs->getName().c_str());
				printf("Podaj nazwę kursu: ");
				getline(cin, zmienna);
				getline(cin, zmienna);
				activ_kurs->setName(zmienna);
				printf("Nowa nazwa kursu: \"%s\"\n", activ_kurs->getName().c_str());
				break;
			case 2:
				printf("Chcesz zmienić nazwę pierwszego języka\n");
				printf("Obecna nazwa pierwszego języka: \"%s\"\n", activ_kurs->getLang1().c_str());
				printf("Podaj nazwę pierwszego języka: ");
				getline(cin, zmienna);
				getline(cin, zmienna);
				activ_kurs->setLang1(zmienna);
				printf("Nowa nazwa pierwszego języka: \"%s\"\n", activ_kurs->getLang1().c_str());
				break;
			case 3:
				printf("Chcesz zmienić nazwę drugiego języka\n");
				printf("Obecna nazwa drugiego języka: \"%s\"\n", activ_kurs->getLang2().c_str());
				printf("Podaj nazwę drugiego języka: ");
				getline(cin, zmienna);
				getline(cin, zmienna);
				activ_kurs->setLang2(zmienna);
				printf("Nowa nazwa drugiego języka: \"%s\"\n", activ_kurs->getLang2().c_str());
				break;
			case 4:
				printf("Chcesz zmienić nazwę pliku, do którego ma być domyślnie zapisywany kurs\n");
				printf("Obecna nazwa tego pliku: \"%s\"\n", activ_kurs->getFilename().c_str());
				printf("Podaj nazwę pliku: ");
				getline(cin, zmienna);
				getline(cin, zmienna);
				activ_kurs->setFilename(zmienna);
				printf("Nowa nazwa pliku: \"%s\"\n", activ_kurs->getFilename().c_str());
				break;
			case 5:
				printf("Chcesz zmienić ilość poznawanyach słów co lekcję.\n");
				printf("Obecna ilość poznawanych słów co lekcję: %hu\n", activ_kurs->getAskQNW());
				printf("Podaj ilość poznawanych słów co lekcję: ");
				scanf("%hu", &zmienna2);
				activ_kurs->setAskQNW(zmienna2);
				printf("Nowa ilość poznawanych słów co lekcję: %hu\n", activ_kurs->getAskQNW());
				break;
			case 6:
				printf("Chcesz zmienić ilość słów, z których mam Cię przepytywać\n");
				printf("Obecna ilość słów... : %hu\n", activ_kurs->getAskQKW());
				printf("Podaj ilość słów... : ");
				scanf("%hu", &zmienna2);
				activ_kurs->setAskQKW(zmienna2);
				printf("Nowa ilość słów... : %hu\n", activ_kurs->getAskQKW());
				break;
			default:
				printf("Podałeś nieprawidłowy numer opcji.\n");
		}
		printf("\n");
	}while(wybor != 0);
}
void Menu::newKurs()
{
	string name, lang1, lang2, filename;
	USI askQKW, askQNW;
	printf("Podaj nazwę kursu.\n");
	getline(cin, name);
	getline(cin, name);
	printf("Podaj nazwę pierwszego języka.\n");
	getline(cin, lang1);
	printf("Podaj nazwę drugiego języka.\n");
	getline(cin, lang2);
	printf("Podaj domyślną nazwę pliku kursu.\n");
	getline(cin, filename);
	printf("Podaj domyślną ilość słówek, z których użytkownik ma być przepytywany.\n");
	scanf("%hu", &askQKW);
	printf("Podaj domyślną ilość słówek, które użytkownik ma poznawać co każde uruchomienie programu.\n");
	scanf("%hu", &askQNW);
	Kurs *kurs = new Kurs(name, lang1, lang2, filename, askQKW, askQNW, globalROE);
	/* Otwarcie kursu */
	{
		kursy.push_back(kurs);
		QOK++;
		nr_activ_kurs = QOK-1;
		activ_kurs = kursy[nr_activ_kurs];
		
		activ_opcji_0[3] = true;
		activ_opcji_0[5] = true;
		activ_opcji_0[6] = true;
		if(QOK > 1)activ_opcji_0[4] = true;
		zaktualizuj_menu_3();
		printf("Kurs został utworzony.\n");
	}
	/* ############# */
}
void Menu::openKurs()
{
	string filename;
	printf("Podaj nazwę pliku do otwarcia.\n");
	getline(cin, filename);
	getline(cin, filename);
	Kurs *kurs;
	try
	{
		kurs = new Kurs(filename, globalROE);
	}
	catch(Error &errorek)
	{
		errorek.addNextFunction("Kurs* openKurs()");
		throw;
	}
	kursy.push_back(kurs);
	QOK++;
	nr_activ_kurs = QOK-1;
	activ_kurs = kursy[nr_activ_kurs];
	activ_kurs->aktualizuj();
	printf("Kurs został otworzony.\n");
}
void Menu::switchKurs()
{
	printf("Jest otwartych %hu kurs.\n", QOK);
	printf("Numeru kursów od 0 do %hu.\n", QOK-1);
	printf("Kurs aktywny jest oznaczony jest gwiazdką.\n");
	for(USI i = 0; i < QOK; i++)
	{
		if(i == nr_activ_kurs)printf("*");
		printf("%hu %s\n", i, kursy[i]->getName().c_str());
	}
	printf("Wpisz numer kursu, na który chcesz się przełączyć.\n");
	USI numberOfKurs;
	scanf("%hu", &numberOfKurs);
	if(numberOfKurs >= QOK)
	{
		printf("Nieprawidłowy numer kursu.\n");
	}
	else
	{
		nr_activ_kurs = numberOfKurs;
		activ_kurs = kursy[numberOfKurs];
	}
}
void Menu::saveKurs(USI nr_kurs)
{
	try
	{
		kursy[nr_kurs]->saveKurs(kursy[nr_kurs]->getFilename());
	}
	catch(Error &errorek)
	{
		errorek.addNextFunction("Kurs* openKurs()");
		throw;
	}
	printf("Kurs został zapisany.\n");
}
void Menu::saveKursAs(USI nr_kurs)
{
	string filename;
	printf("Podaj nazwę pliku, do którego chcesz zapisać kurs.\n");
	getline(cin, filename);
	getline(cin, filename);
	try
	{
		kursy[nr_kurs]->saveKurs(filename);
	}
	catch(Error &errorek)
	{
		errorek.addNextFunction("Kurs* openKurs()");
		throw;
	}
	printf("Kurs został zapisany.\n");
}		
void Menu::printInfoKurs()
{
	printf("Nazwa kursu: \"%s\"\n", activ_kurs->getName().c_str());
	printf("Nazwa pierwszego języka: \"%s\"\n", activ_kurs->getLang1().c_str());
	printf("Nazwa drugiego języka: \"%s\"\n", activ_kurs->getLang2().c_str());
	printf("Nazwa pliku, do którego domyślnie zapisywany jest kurs: \"%s\"\n", activ_kurs->getFilename().c_str());
	printf("Ilość poznawanych słów co lekcję: %hu\n", activ_kurs->getAskQNW());
	printf("Ilość słów, których chcesz być przepytywany : %hu\n", activ_kurs->getAskQKW());
	printf("Ilość wszystkich słów w kursie: %hu\n", activ_kurs->getQAllWords());
	printf("Ilość poznanych słów: %hu\n", activ_kurs->getQKnownWords());
	if(activ_kurs->isKursChanged())printf("Od ostatniego zapisu kurs został zmieniony.\n");
	else printf("Od ostatniego zapisu kurs nie został zmieniony.\n");
}
void Menu::przepytaj_ze_starych()
{
	system("clear");
			
	USI ilosc_slow;
	time_t _time;
	string wyraz;
	USI poziom_opanowania;
	printf("Podaj ilość słów, z których chcesz być przepytywany, podaj 0 dla domyślnej wartości ustawionej w kursie.\n");
	scanf("%hu", &ilosc_slow);
	if(ilosc_slow == 0)ilosc_slow = activ_kurs->getAskQKW();
	vector <USI> slowa = activ_kurs->getKnownWords(ilosc_slow);
	ilosc_slow = slowa.size();
	printf("Wpisz brakujące słowa.\n");
	USI krakl;
	for(USI i = 0; i < ilosc_slow; i++)
	{
		srand ( time(NULL) );//przygotowanie totalizatora
		printf("Język:\t%s\t%s\n", activ_kurs->getLang1().c_str(), activ_kurs->getLang2().c_str());
		krakl = rand()%2;
		if(krakl)
		{
			printf("\t*brakujące*\t%s\n", activ_kurs->getWord(slowa[i]).getSecond().c_str());
			_time = time(NULL);
			getline(cin, wyraz);
			getline(cin, wyraz);
			_time = time(NULL) - _time;
			printf("Prawidłowa wersja to: %s\n", activ_kurs->getWord(slowa[i]).getFirst().c_str());
		}
		else
		{
			printf("\t%s\t*brakujące*\n", activ_kurs->getWord(slowa[i]).getFirst().c_str());
			_time = time(NULL);
			getline(cin, wyraz);
			getline(cin, wyraz);
			_time = time(NULL) - _time;
			printf("Prawidłowa wersja to: %s\n", activ_kurs->getWord(slowa[i]).getSecond().c_str());
		}
		printf("Na ile oceniasz od 1 do 1000 oceniasz swoje odgadnięcie słowa(nie uwzględniając czasu?\n");
		scanf("%hu", &poziom_opanowania);
		if(poziom_opanowania > 1000)poziom_opanowania = 1000;
		activ_kurs->repairWord(slowa[i], krakl, _time, poziom_opanowania);
	}
}
void Menu::naucz_nowych()
{
	system("clear");
			
	USI ilosc_slow;
	time_t _time;
	string wyraz;
	USI poziom_opanowania;
	printf("Podaj ilość słów, których chcesz się nauczyć, podaj 0 dla domyślnej wartości ustawionej w kursie.\n");
	scanf("%hu", &ilosc_slow);
	if(ilosc_slow == 0)ilosc_slow = activ_kurs->getAskQNW();
	vector <USI> slowa = activ_kurs->getUnknownWords(ilosc_slow);
	ilosc_slow = slowa.size();
	activ_kurs->increaseQKnownWords(ilosc_slow);
			
	printf("Język:\t%s\t%s\n", activ_kurs->getLang1().c_str(), activ_kurs->getLang2().c_str());
	for(USI i = 0; i < ilosc_slow; i++)
	{
		printf("\t%s\t%s\n", activ_kurs->getWord(slowa[i]).getFirst().c_str(), activ_kurs->getWord(slowa[i]).getSecond().c_str());
	}
			
	sleep(ilosc_slow*2);
	system("clear");
			
	printf("A teraz wpisz brakujące słowa.\n");
	USI krakl;
	for(USI i = 0; i < ilosc_slow; i++)
	{
		srand ( time(NULL) );//przygotowanie totalizatora
		printf("Język:\t%s\t%s\n", activ_kurs->getLang1().c_str(), activ_kurs->getLang2().c_str());
		krakl = rand()%2;
		if(krakl)
		{
			printf("\t*brakujące*\t%s\n", activ_kurs->getWord(slowa[i]).getSecond().c_str());
			_time = time(NULL);
			getline(cin, wyraz);
			getline(cin, wyraz);
			_time = time(NULL) - _time;
			printf("Prawidłowa wersja to: %s\t%s\n", activ_kurs->getWord(slowa[i]).getFirst().c_str(), activ_kurs->getWord(slowa[i]).getSecond().c_str());
		}
		else
		{
			printf("\t%s\t*brakujące*\n", activ_kurs->getWord(slowa[i]).getFirst().c_str());
			_time = time(NULL);
			getline(cin, wyraz);
			getline(cin, wyraz);
			_time = time(NULL) - _time;
			printf("Prawidłowa wersja to: %s\t%s\n", activ_kurs->getWord(slowa[i]).getFirst().c_str(), activ_kurs->getWord(slowa[i]).getSecond().c_str());
		}
		printf("Na ile oceniasz od 1 do 1000 oceniasz swoje odgadnięcie słowa(nie uwzględniając czasu?\n");
		scanf("%hu", &poziom_opanowania);
		if(poziom_opanowania > 1000)poziom_opanowania = 1000;
		activ_kurs->repairWord(slowa[i], krakl, _time, poziom_opanowania);
	}
}
void Menu::zaktualizuj_menu_3()
{
	activ_opcji_3[0] = true;
	activ_opcji_3[1] = true;
	activ_opcji_3[2] = true;
	activ_opcji_3[3] = true;
	activ_opcji_3[10] = true;
	if(activ_kurs->getQAllWords() == 0)
	{
		for(USI i = 4; i <= 9; i++)
		{
			activ_opcji_3[i] = false;
		}
	}
	else
	{
		for(USI i = 4; i <= 9; i++)
		{
			activ_opcji_3[i] = true;
		}
		activ_opcji_3[11] = true;
	}
	if(activ_kurs->getQKnownWords() == activ_kurs->getQAllWords())activ_opcji_3[9]=false;
	if(activ_kurs->getQKnownWords() == 0)activ_opcji_3[8]=false;
}
void Menu::zaktualizuj_menu_0()
{
	activ_opcji_0[0] = true;
	activ_opcji_0[1] = true;
	activ_opcji_0[2] = true;
	activ_opcji_0[8] = true;
	if(QOK > 0)
	{
		activ_opcji_0[3] = true;
		if(QOK > 1)activ_opcji_0[4] = true;
		else activ_opcji_0[4] = false;
		if(activ_kurs->isKursChanged())activ_opcji_0[5] = true;
		else activ_opcji_0[5] = false;
		activ_opcji_0[6] = true;
		activ_opcji_0[7] = true;
	}
	else 
	{
		activ_opcji_0[3] = false;
		activ_opcji_0[4] = false;
		activ_opcji_0[5] = false;
		activ_opcji_0[6] = false;
		activ_opcji_0[7] = false;
	}
}
void Menu::at_error(Error& errorek, bool &local_variable_error, short int &local_variable_wybor)
{
	char znak;
	globalROE.addError(errorek);
	local_variable_error = true;
	printf("Błąd: %s\n", errorek.getDescription().c_str());
	printf("Czy chcesz wybrać ponownie tę opcję?\n");
	printf("Tak(T)/Nie(N): ");
	scanf("%c", &znak);
	if(znak == 'T')
	{
		local_variable_wybor *= -1;
	}
}
bool Menu::closeKurs(USI nr_kurs)
{
	char znak;
	string wyraz;
	if(nr_kurs >= QOK)throw Error::newError(Error::OUTPASS_MAX_SIZE_OF_ARRAY, "void Menu::closeKurs(USI nr_kurs)", __LINE__, __FILE__);
	if(kursy[nr_kurs]->isKursChanged())
	{
		printf("Zapisać zmieniony kurs (ODPOWIEDŹ \"Nie\" SPOWODUJE UTRATĘ ZMIAN))\n"
			"Tak(T)\n"
			"Nie(N)\tAnuluj(A)\n");
		getline(cin, wyraz);
		scanf("%c", &znak);
		if(znak == 'T')
		{
			saveKurs(nr_kurs);
			simple_closeKurs(nr_kurs);
			return true;
		}
		if(znak == 'N')
		{
			simple_closeKurs(nr_kurs);
			return true;
		}
		printf("Anulowano\n");
		return false;
	}
	simple_closeKurs(nr_kurs);
	return true;
}
void Menu::simple_closeKurs(USI nr_kurs)
{
	vector<Kurs*>::iterator to_deleted = kursy.begin();
	for(USI i = 0; i < nr_kurs; i++, to_deleted++){}
	kursy.erase(to_deleted);
	QOK--;
	if(QOK == 0)
	{
		activ_kurs = NULL;
		nr_activ_kurs = -1;
	}
	else
	{
		activ_kurs = kursy[0];
		nr_activ_kurs = 0;
	}
}
int main()
{
	Error::setDescriptionOfErrors();
	Menu *menu = new Menu();
	short int wybor = 0;
	char znak;
	bool error;
	cout << "Konkord Copyright(C) 2009 Sławomir Domagała" << endl
	     << "This program comes with ABSOLUTELY NO WARRANTY; for details see \"O programie\"." << endl
    	 << "This is free software, and you are welcome to redistribute it" << endl
    	 << "under certain conditions; see \"O programie\" for details." << endl
		 << endl;
	do
	{
		menu->zaktualizuj_menu_0();
		error = false;
		
		if(wybor >= 0)
		{	
			menu->printOptions(menu->tekst_opcji_0, menu->activ_opcji_0, menu->ilosc_opcji_0);
			wybor = menu->scanfOption(menu->activ_opcji_0, menu->ilosc_opcji_0);
		}
		else
		{
			wybor *= -1;
		}
		switch(wybor)
		{
			case 0:
				printf("Wybrałeś opcję \"%s\"\n", menu->tekst_opcji_0[0].c_str());
				for(USI i = 0; i < menu->QOK; i++)
				{
					if(!(menu->closeKurs(i)))wybor = 10;//unused number
				}
				break;
			case 1:
				printf("Wybrałeś opcję \"%s\"\n", menu->tekst_opcji_0[1].c_str());
				menu->newKurs();
				break;
			case 2:
				printf("Wybrałeś opcję \"%s\"\n", menu->tekst_opcji_0[2].c_str());
				try
				{   
					menu->openKurs();
				}
				catch(Error &errorek)
				{
					menu->at_error(errorek, error, wybor);
				}
				break;
			case 3:
				printf("Wybrałeś opcję \"%s\"\n", menu->tekst_opcji_0[3].c_str());
				menu->menu_3();
				break;
			case 4:
				printf("Wybrałeś opcję \"%s\"\n", menu->tekst_opcji_0[4].c_str());
				menu->switchKurs();
				break;
			case 5:
				printf("Wybrałeś opcję \"%s\"\n", menu->tekst_opcji_0[5].c_str());
				menu->saveKurs(menu->nr_activ_kurs);
				break;
			case 6:
				printf("Wybrałeś opcję \"%s\"\n", menu->tekst_opcji_0[6].c_str());
				try
				{
					menu->saveKursAs(menu->nr_activ_kurs);
				}
				catch(Error &errorek)
				{
					menu->at_error(errorek, error, wybor);
				}
				break;
			case 7:
				printf("Wybrałeś opcję \"%s\"\n", menu->tekst_opcji_0[7].c_str());
				menu->closeKurs(menu->nr_activ_kurs);
				break;
			case 8:
				cout << "\t\t\tKonkord" << endl
				     <<	"\t\tVersion 0.0.2009.04.19" << endl
				     << "\tThis program was created for learning words" << endl
	 			     << "\t\tfrom different languages." << endl
				     << endl
    				 << "Copyright(C) 2009 Sławomir Domagała" << endl
				     << endl
    				 << "This program is free software: you can redistribute it and/or modify" << endl
   				     << "it under the terms of the GNU General Public License as published by" << endl
    				 << "the Free Software Foundation, either version 3 of the License, or" << endl
    				 << "(at your option) any later version." << endl
    				 << endl
    				 << "This program is distributed in the hope that it will be useful," << endl
    				 << "but WITHOUT ANY WARRANTY; without even the implied warranty of" << endl
    				 << "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the" << endl
    				 << "GNU General Public License for more details." << endl
    				 << endl
    				 << "You should have received a copy of the GNU General Public License" << endl
    				 << "along with this program.  If not, see <http://www.gnu.org/licenses/>" << endl
				     << endl
   	 			     << "E-mail: godlark@gmail.com" << endl;
				sleep(10);
				break;
			default:
				printf("Podałeś nieprawidłowy numer opcji.\n");
		}
		system("clear");
	}while(wybor != 0);
	printf("Do zobaczenia\n");
	return 0;
}