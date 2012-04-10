#include <qapplication.h>
#include <qmainwindow.h>
#include "mainwindow.hpp"
#include "../RegisterOfErrors.hpp"
#include <clocale>

extern std::string* Error::DescriptionOfErrors;

int main (int argc, char *argv[])
{
   std::locale::global(std::locale("en_US"));
   setlocale(LC_ALL, "en_US");
   Error::setDescriptionOfErrors();
   QApplication app(argc, argv);
   MainWindow window;
   window.show();
   return app.exec();
}
