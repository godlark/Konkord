#include "mainwindow.hpp"
#include <iostream>
#include <QAction>
#include <QFileDialog>

using namespace std;

MainWindow::MainWindow() {
    QTextCodec::setCodecForTr (QTextCodec::codecForName ("UTF-8"));

    serviceOfTasks = new ServiceOfTasks(this);

    initializeActions();
    initializeMenus();
}

void MainWindow::initializeMenus() {
    mainMenu = new QMenu(tr("Główne"), this);
    menuChangeCourse = new QMenu(tr("Przełącz kurs"), this);
    
    menuBar()->addMenu(mainMenu);
    mainMenu->addAction(closeCourse);
    mainMenu->addAction(newCourse);
    mainMenu->addAction(openCourse);
    mainMenu->addAction(saveCourse);
    mainMenu->addAction(saveCourseAs);
    mainMenu->addMenu(menuChangeCourse);
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
    courses2Change = new MAction* [1];
    courses2Change[0] = NULL;
    
    closeCourse = new MAction(tr("&Zamknij kurs"), this);
    newCourse = new MAction(tr("&Nowy kurs"), this);
    openCourse = new MAction(tr("&Otwórz kurs"), this);
    saveCourse = new MAction(tr("&Zapisz kurs"), this);
    saveCourseAs = new MAction(tr("&Zapisz kurs jako"), this);
    closeProgram = new MAction(tr("&Zamknij program"), this);

    repeatWords = new MAction(tr("&Powtórz poznane słowa"), this);
    learnWords = new MAction(tr("&Naucz się nowych"), this);
    editWord = new MAction(tr("&Edytuj słow"), this);
    deleteWord = new MAction(tr("&Usuń słowo"), this);
    connectWords = new MAction(tr("&Połącz słowa"), this);
    disconnectWords = new MAction(tr("&Rozłącz słowa"), this);
    addWord = new MAction(tr("&Dodaj słowo"), this);
    addWords = new MAction(tr("&Dodaj słowa"), this);
    printCourse = new MAction(tr("&Wyświetl informacje na temat kursu"), this);
    AprintWords = new MAction(tr("&Wyświetl słowa"), this);
    setupCourse = new MAction(tr("&Ustawienia kursu"), this);
    readWords = new MAction(tr("&Wczytaj słowa z pliku"), this);
    findWords = new MAction(tr("&Znajdź słowa"), this);

    connect(closeCourse, SIGNAL(_triggered(MAction*)), this, SLOT(slotCloseCourse()));
    connect(newCourse, SIGNAL(_triggered(MAction*)), this, SLOT(slotNewCourse()));
    connect(openCourse, SIGNAL(_triggered(MAction*)), this, SLOT(slotOpenCourse()));
    connect(saveCourse, SIGNAL(_triggered(MAction*)), this, SLOT(slotSaveCourse()));
    connect(saveCourseAs, SIGNAL(_triggered(MAction*)), this, SLOT(slotSaveCourseAs()));
    connect(closeProgram, SIGNAL(_triggered(MAction*)), this, SLOT(slotCloseProgram()));

    connect(repeatWords, SIGNAL(_triggered(MAction*)), this, SLOT(slotRepeatWords()));
    connect(learnWords, SIGNAL(_triggered(MAction*)), this, SLOT(slotLearnWords()));
    connect(editWord, SIGNAL(_triggered(MAction*)), this, SLOT(slotEditWord()));
    connect(deleteWord, SIGNAL(_triggered(MAction*)), this, SLOT(slotDeleteWord()));
    connect(connectWords, SIGNAL(_triggered(MAction*)), this, SLOT(slotConnectWords()));
    connect(disconnectWords, SIGNAL(_triggered(MAction*)), this, SLOT(slotDisconnectWords()));
    connect(addWord, SIGNAL(_triggered(MAction*)), this, SLOT(slotAddWord()));
    connect(addWords, SIGNAL(_triggered(MAction*)), this, SLOT(slotAddWords()));
    connect(printCourse, SIGNAL(_triggered(MAction*)), this, SLOT(slotPrintCourse()));
    connect(AprintWords, SIGNAL(_triggered(MAction*)), this, SLOT(slotAPrintWords()));
    connect(setupCourse, SIGNAL(_triggered(MAction*)), this, SLOT(slotSetupCourse()));
    connect(readWords, SIGNAL(_triggered(MAction*)), this, SLOT(slotReadWords()));
    connect(findWords, SIGNAL(_triggered(MAction*)), this, SLOT(slotFindWords()));
}

void MainWindow::slotCloseCourse() {
    serviceOfTasks->doAction(3);
    reloadListCourses();
}

void MainWindow::slotNewCourse() {
    serviceOfTasks->doAction(10);
}

void MainWindow::reloadListCourses() {
    std::vector<std::string> coursesNames = serviceOfTasks->getCoursesNames();
    numberCourses = coursesNames.size();
    menuChangeCourse->clear();
    delete [] courses2Change;
    courses2Change = new MAction* [coursesNames.size()];
    for(int i = 0; i < coursesNames.size(); i++) {
	courses2Change[i] = new MAction(tr(coursesNames[i].c_str()), this);
	menuChangeCourse->addAction(courses2Change[i]);
	connect(courses2Change[i], SIGNAL(_triggered(MAction*)), this, SLOT(slotChangeCourse(MAction*)));
    }
}

void MainWindow::slotOpenCourse() {
    QString filename = QFileDialog::getOpenFileName(this, tr("Otwórz plik"));
    if (filename.isEmpty())return;
    serviceOfTasks->doAction(11, filename.toStdString());
    
    reloadListCourses();
}

void MainWindow::slotSaveCourse() {
    serviceOfTasks->doAction(14);
}

void MainWindow::slotSaveCourseAs() {
	QString filename = QFileDialog::getSaveFileName(this, tr("Zapisz kurs"));
	if (filename.isEmpty())
        return;
    serviceOfTasks->doAction(15, filename.toStdString());
}

void MainWindow::slotChangeCourse(MAction* which_course) {
    cout << numberCourses << endl;
    for(int i = 0; i < numberCourses; i++) {
	if(courses2Change[i] == which_course) {
	    serviceOfTasks->doAction(17, toString(i));
	}
    }
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
    QString filename = QFileDialog::getOpenFileName(this, tr("Otwórz plik"));
    if (filename.isEmpty())
        return;
    serviceOfTasks->doAction(18, filename.toStdString());
}

void MainWindow::slotFindWords() {
    serviceOfTasks->doAction(19);
}


void MainWindow::run() {
        cout << "dupa" << endl;
}

string MainWindow::askWord(SingleWord const *sword, uint nr_word) {
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
void MainWindow::printWords(string description, SingleWord const *swords[], uint const *numbersWords, vector<uint> numbersConnections, short time) {
        cout << description << endl;
        SingleWord const *mean;
        uint number_connections = numbersConnections.size()/2;
        for(uint i = 0; i < number_connections; i++) {
                cout << "Numer słowa: " << numbersWords[numbersConnections[i*2]] << endl;
                mean = swords[numbersConnections[i*2]]->getMeaning(numbersConnections[(i*2)+1]);
                cout << swords[numbersConnections[i*2]]->getSpelling() << "\t\t" << mean->getSpelling() << endl;
                cout << "***" << endl;
        }
        if(time >= 0)sleep(time);
        else cin.get();
}

Variable MainWindow::dialogWindow(string text, uint type) {
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
                                cin >> temp._uint;
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

void MainWindow::infoWindow(string const *descriptions, Variable *values, uint number) {
        for(uint i = 0; i < number; i++) {
                cout << descriptions[i] << ": ";
                switch(values[i].type) {
                        case 0:
                                cout << *(values[i]._string) << endl;
                                break;
                        case 1:
                                cout << values[i]._uint << endl;
                                break;
                }
        }
}

Variables MainWindow::optionWindow(string const *descriptions, Variable *values, uint number) {
        uint wybor = 0;
        Variables vs;
        vs.number = number;
        vs.v = values;
        do {
                string teemp;
                cout << "Opcje kursu to: " << endl;
                for(uint i = 0; i < number; i++)
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
                                        cout << values[wybor-1]._uint << endl;
                                        cout << "Podaj nową wartość: ";
                                        cin >> values[wybor-1]._uint;
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

uint MainWindow::radioWindow(string description, string const *values, uint defaultOption, uint number) {
        cout << description << endl;
        cout << "Kurs aktywny oznaczony jest gwiazdką" << endl;
        for(uint i = 0; i < number; i++) {
                if(i == defaultOption)cout << "*";
                cout << i << ". " << values[i] << endl;
        }
        cout << "Wpisz numer opcji, którą wybierasz: ";
        uint temp;
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
