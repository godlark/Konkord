#include "mainwindow.hpp"
#include <iostream>
#include <QAction>

using namespace std;

MainWindow::MainWindow() {
    QTextCodec::setCodecForTr (QTextCodec::codecForName ("UTF-8"));

    serviceOfTasks = new ServiceOfTasks(this);

    initializeActions();
    initializeMenus();
}

void MainWindow::initializeMenus() {
    mainMenu = new QMenu(tr("Główne"), this);
    menuBar()->addMenu(mainMenu);
    mainMenu->addAction(closeCourse);
    mainMenu->addAction(newCourse);
    mainMenu->addAction(openCourse);
    mainMenu->addAction(saveCourse);
    mainMenu->addAction(saveCourseAs);
    mainMenu->addAction(changeCourse);
    mainMenu->addAction(closeProgram);

    courseMenu = new QMenu(tr("Kurs"), this);
    menuBar()->addMenu(courseMenu);
    courseMenu->addAction(repeatWords);
    courseMenu->addAction(learnWords);
    courseMenu->addAction(editWord);
    courseMenu->addAction(deleteWord);
    courseMenu->addAction(connectWords);
    courseMenu->addAction(disconnectWords);
    courseMenu->addAction(addWord);
    courseMenu->addAction(addWords);
    courseMenu->addAction(printCourse);
    courseMenu->addAction(AprintWords);
    courseMenu->addAction(setupCourse);
    courseMenu->addAction(readWords);
    courseMenu->addAction(findWords);
}

void MainWindow::initializeActions() {
    closeCourse = new QAction(tr("&Zamknij kurs"), this);
    newCourse = new QAction(tr("&Nowy kurs"), this);
    openCourse = new QAction(tr("&Otwórz kurs"), this);
    saveCourse = new QAction(tr("&Zapisz kurs"), this);
    saveCourseAs = new QAction(tr("&Zapisz kurs jako"), this);
    changeCourse = new QAction(tr("&Przełącz kurs"), this);
    closeProgram = new QAction(tr("&Zamknij program"), this);

    repeatWords = new QAction(tr("&Powtórz poznane słowa"), this);
    learnWords = new QAction(tr("&Naucz się nowych"), this);
    editWord = new QAction(tr("&Edytuj słow"), this);
    deleteWord = new QAction(tr("&Usuń słowo"), this);
    connectWords = new QAction(tr("&Połącz słowa"), this);
    disconnectWords = new QAction(tr("&Rozłącz słowa"), this);
    addWord = new QAction(tr("&Dodaj słowo"), this);
    addWords = new QAction(tr("&Dodaj słowa"), this);
    printCourse = new QAction(tr("&Wyświetl informacje na temat kursu"), this);
    AprintWords = new QAction(tr("&Wyświetl słowa"), this);
    setupCourse = new QAction(tr("&Ustawienia kursu"), this);
    readWords = new QAction(tr("&Wczytaj słowa z pliku"), this);
    findWords = new QAction(tr("&Znajdź słowa"), this);

    connect(closeCourse, SIGNAL(triggered()), this, SLOT(slotCloseCourse()));
    connect(newCourse, SIGNAL(triggered()), this, SLOT(slotNewCourse()));
    connect(openCourse, SIGNAL(triggered()), this, SLOT(slotOpenCourse()));
    connect(saveCourse, SIGNAL(triggered()), this, SLOT(slotSaveCourse()));
    connect(saveCourseAs, SIGNAL(triggered()), this, SLOT(slotSaveCourseAs()));
    connect(changeCourse, SIGNAL(triggered()), this, SLOT(slotChangeCourse()));
    connect(closeProgram, SIGNAL(triggered()), this, SLOT(slotCloseProgram()));

    connect(repeatWords, SIGNAL(triggered()), this, SLOT(slotRepeatWords()));
    connect(learnWords, SIGNAL(triggered()), this, SLOT(slotLearnWords()));
    connect(editWord, SIGNAL(triggered()), this, SLOT(slotEditWord()));
    connect(deleteWord, SIGNAL(triggered()), this, SLOT(slotDeleteWord()));
    connect(connectWords, SIGNAL(triggered()), this, SLOT(slotConnectWords()));
    connect(disconnectWords, SIGNAL(triggered()), this, SLOT(slotDisconnectWords()));
    connect(addWord, SIGNAL(triggered()), this, SLOT(slotAddWord()));
    connect(addWords, SIGNAL(triggered()), this, SLOT(slotAddWords()));
    connect(printCourse, SIGNAL(triggered()), this, SLOT(slotPrintCourse()));
    connect(AprintWords, SIGNAL(triggered()), this, SLOT(slotAPrintWords()));
    connect(setupCourse, SIGNAL(triggered()), this, SLOT(slotSetupCourse()));
    connect(readWords, SIGNAL(triggered()), this, SLOT(slotReadWords()));
    connect(findWords, SIGNAL(triggered()), this, SLOT(slotFindWords()));
}

void MainWindow::slotCloseCourse() {
    serviceOfTasks->doAction(3);
}

void MainWindow::slotNewCourse() {
    serviceOfTasks->doAction(10);
}

void MainWindow::slotOpenCourse() {
    serviceOfTasks->doAction(11);
}

void MainWindow::slotSaveCourse() {
    serviceOfTasks->doAction(14);
}

void MainWindow::slotSaveCourseAs() {
    serviceOfTasks->doAction(15);
}

void MainWindow::slotChangeCourse() {
    serviceOfTasks->doAction(17);
}

void MainWindow::slotCloseProgram() {
    serviceOfTasks->closeProgram();
    exit(1);
}

void MainWindow::slotRepeatWords() {
    serviceOfTasks->doAction(1);
}

void MainWindow::slotLearnWords() {
    serviceOfTasks->doAction(2);
}

void MainWindow::slotEditWord() {
    serviceOfTasks->doAction(4);
}

void MainWindow::slotDeleteWord() {
    serviceOfTasks->doAction(5);
}

void MainWindow::slotConnectWords() {
    serviceOfTasks->doAction(6);
}

void MainWindow::slotDisconnectWords() {
    serviceOfTasks->doAction(7);
}

void MainWindow::slotAddWord() {
    serviceOfTasks->doAction(8);
}

void MainWindow::slotAddWords() {
    serviceOfTasks->doAction(9);
}

void MainWindow::slotPrintCourse() {
    serviceOfTasks->doAction(12);
}

void MainWindow::slotAPrintWords() {
    serviceOfTasks->doAction(13);
}

void MainWindow::slotSetupCourse() {
    serviceOfTasks->doAction(16);
}

void MainWindow::slotReadWords() {
    serviceOfTasks->doAction(18);
}

void MainWindow::slotFindWords() {
    serviceOfTasks->doAction(19);
}


void MainWindow::run() {
        cout << "dupa" << endl;
}

string MainWindow::askWord(SingleWord const *sword, ushort nr_word) {
        system("clear");
        cout << "Numer słowa: " << nr_word << endl;
        cout << "Napisz znaczenia tego wyrażenia:\n\"" << sword->getSpelling() << "\"";
        string temp;
        getline(cin, temp);
        return temp;
}
void MainWindow::printMessage(string title, string something) {
        cout << "***" << title << "***" << endl;
        cout << something << endl;
}
void MainWindow::printWords(string description, SingleWord const *swords[], ushort const *numbersWords, vector<ushort> numbersConnections, short time) {
        cout << description << endl;
        SingleWord const *mean;
        ushort number_connections = numbersConnections.size()/2;
        for(ushort i = 0; i < number_connections; i++) {
                cout << "Numer słowa: " << numbersWords[numbersConnections[i*2]] << endl;
                mean = swords[numbersConnections[i*2]]->getMeaning(numbersConnections[(i*2)+1]);
                cout << swords[numbersConnections[i*2]]->getSpelling() << "\t\t" << mean->getSpelling() << endl;
                cout << "***" << endl;
        }
        if(time >= 0)sleep(time);
        else cin.get();
}

Variable MainWindow::dialogWindow(string text, ushort type) {
        Variable temp;
        temp.type = type;
        string teemp;
        cout << text << ": " << endl;
        bool repeat = true;
        while(repeat){
                switch(type) {
                        case 0:
                                getline(cin, teemp);
                                temp._string = new string(teemp);
                                break;
                        case 1:
                                cin >> temp._ushort;
                                break;
                }
                if(cin.fail()) {
                        cout << "\nNiepoprawne dane, wpisz jeszcze raz" << endl;
                        cin.clear();
                }
                else repeat = false;
                if(type != 0)cin.ignore(INT_MAX, '\n');
        }
        return temp;
}

void MainWindow::infoWindow(string const *descriptions, Variable *values, ushort number) {
        for(ushort i = 0; i < number; i++) {
                cout << descriptions[i] << ": ";
                switch(values[i].type) {
                        case 0:
                                cout << *(values[i]._string) << endl;
                                break;
                        case 1:
                                cout << values[i]._ushort << endl;
                                break;
                }
        }
}

Variables MainWindow::optionWindow(string const *descriptions, Variable *values, ushort number) {
        ushort wybor = 0;
        Variables vs;
        vs.number = number;
        vs.v = values;
        do {
                string teemp;
                cout << "Opcje kursu to: " << endl;
                for(ushort i = 0; i < number; i++)
                {
                        cout << i+1 << ". " << descriptions[i] << endl;
                }
                cout << "Aby zmienić opcję kursu, wpisz numer znajdujący się przy niej, jeśli nie chcesz zmienić już żadnej opcji wpisz '0'" << endl;
                cin >> wybor;
                cout << "Obecna wartość to: ";
                bool repeat = true;
                while(repeat){
                        switch(values[wybor-1].type) {
                                case 0:
                                        cout << *(values[wybor-1]._string) << endl;
                                        cout << "Podaj nową wartość: ";
                                        cin >> teemp;
                                        values[wybor-1]._string = new string(teemp);
                                        break;
                                case 1:
                                        cout << values[wybor-1]._ushort << endl;
                                        cout << "Podaj nową wartość: ";
                                        cin >> values[wybor-1]._ushort;
                                        break;
                        }
                        if(cin.fail()) {
                                cout << "\nNiepoprawne dane, wpisz jeszcze raz" << endl;
                                cin.clear();
                        }
                        else repeat = false;
                        if(values[wybor-1].type != 0)cin.ignore(INT_MAX, '\n');
                }

        }while(wybor != 0);
}

ushort MainWindow::radioWindow(string description, string const *values, ushort defaultOption, ushort number) {
        cout << description << endl;
        cout << "Kurs aktywny oznaczony jest gwiazdką" << endl;
        for(ushort i = 0; i < number; i++) {
                if(i == defaultOption)cout << "*";
                cout << i << ". " << values[i] << endl;
        }
        cout << "Wpisz numer opcji, którą wybierasz: ";
        ushort temp;
        bool repeat = true;
        while(repeat){
                cin >> temp;
                if(cin.fail()) {
                  cout << "\nNiepoprawne dane, wpisz jeszcze raz" << endl;
                  cin.clear();
                }
                else repeat = false;
                cin.ignore(INT_MAX, '\n');
        }
        return temp;
}

char MainWindow::Yes_No_Cancel(string description)
{
        char znak;
        cout << description << endl;
        cout << "Tak(T)" << endl;
        cout << "Nie(N)\tAnuluj(A)" << endl;
        bool repeat = true;
        while(repeat){
                cin >> znak;
                if(cin.fail()) {
                  cout << "\nNiepoprawne dane, wpisz jeszcze raz" << endl;
                  cin.clear();
                }
                else repeat = false;
                cin.ignore(INT_MAX, '\n');
        }
        if(znak == 'T')return 1;
        if(znak == 'N')return 0;
        else return 2;
}
