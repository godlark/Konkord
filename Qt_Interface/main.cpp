#include <qapplication.h>
#include <qmainwindow.h>
#include "mainwindow.hpp"
#include "../RegisterOfErrors.hpp"

using namespace std;

extern string* Error::DescriptionOfErrors;

int main (int argc, char *argv[])
{
   Error::setDescriptionOfErrors();
   QApplication app(argc, argv);
   MainWindow window;

   window.show();

   return app.exec();
}
