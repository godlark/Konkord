#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QMenuBar>
#include "../interface.hpp"
#include "../engine.hpp"
#include <string>
#include <vector>
#include <QTextCodec>
#include <QRadioButton>
#include "maction.hpp"

class MainWindow: public QMainWindow, public Interface {
    Q_OBJECT
private:

    ServiceOfTasks *serviceOfTasks;
    QMenu *mainMenu;
    QMenu *menuChangeCourse;
    MAction **courses2Change;
    int numberCourses;
    
    MAction *closeCourse;
    MAction *newCourse;
    MAction *openCourse;
    MAction *saveCourse;
    MAction *saveCourseAs;
    MAction *closeProgram;

    QMenu *courseMenu;
    MAction *repeatWords;
    MAction *learnWords;
    MAction *editWord;
    MAction *deleteWord;
    MAction *connectWords;
    MAction *disconnectWords;
    MAction *addWord;
    MAction *addWords;
    MAction *printCourse;
    MAction *AprintWords;
    MAction *setupCourse;
    MAction *readWords;
    MAction *findWords;

    void initializeMenus();
    void initializeActions();
public:
    MainWindow();

    std::string askWord(SingleWord const *sword, ushort nr_word);//nr_lang = 0 lub = 1
    void printWords(std::string description, SingleWord const **swords, ushort const *numbersWords, std::vector<ushort> numbersConnections, short time);
    Variable dialogWindow(std::string text, ushort type);
    void infoWindow(std::string const *descriptions, Variable *values, ushort number);
    ushort radioWindow(std::string description, std::string const *values, ushort defaultOption, ushort number);
    char Yes_No_Cancel(std::string description);
    Variables optionWindow(std::string const *descriptions, Variable *values, ushort number);
    void printMessage(std::string title, std::string something);
    void reloadListCourses();
    void run();
public slots:
    void slotCloseCourse();
    void slotNewCourse();
    void slotOpenCourse();
    void slotSaveCourse();
    void slotSaveCourseAs();
    void slotChangeCourse(MAction*);
    void slotCloseProgram();

    void slotRepeatWords();
    void slotLearnWords();
    void slotEditWord();
    void slotDeleteWord();
    void slotConnectWords();
    void slotDisconnectWords();
    void slotAddWord();
    void slotAddWords();
    void slotPrintCourse();
    void slotAPrintWords();
    void slotSetupCourse();
    void slotReadWords();
    void slotFindWords();
};


#endif // MAINWINDOW_HPP
