#include <KApplication>
#include <KAboutData>
#include <KCmdLineArgs>
 
#include "mainwindow.h"
 
int main (int argc, char *argv[])
{
  KAboutData aboutData( "tutorial4", "tutorial4",
      ki18n("Anant Text Editor"), "2.0",
      ki18n("A simple text area which can load and saveand help you preview HTML encoded files."),
      KAboutData::License_GPL,
      ki18n("Copyright (c) 2013 Developer") );
  KCmdLineArgs::init( argc, argv, &aboutData );
  KApplication app;
 
  MainWindow* window = new MainWindow();
  window->show();
  return app.exec();
}