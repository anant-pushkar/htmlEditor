#include "mainwindow.h"
 
#include <KApplication>
#include <KAction>
#include <KLocale>
#include <KActionCollection>
#include <KStandardAction>
#include <KFileDialog> //новое
#include <KMessageBox> //новое
#include <KIO/NetAccess> //новое
#include <KSaveFile> //новое
#include <QTextStream> //новое
#include <qboxlayout.h>
 
MainWindow::MainWindow(QWidget *parent)
    : KXmlGuiWindow(parent),
      fileName(QString()) //новое
{
  QHBoxLayout* layout = new QHBoxLayout;
  QLabel* panel = new QLabel;
  panel->setLayout(layout);
  
  textArea = new KTextEdit;
  textArea->setTabStopWidth(40);
  htmlLabel = new KTextEdit;
  //htmlLabel->setEnabled(false);
  layout->addWidget(textArea);
  layout->addWidget(htmlLabel);
  setCentralWidget(panel);
 
  setupActions();
}

void MainWindow::refreshView(){
    textChange=true;
    if(htmlChange==false){
	htmlLabel->setHtml(textArea->toPlainText().toUtf8());
    }
    textChange=false;
}

void MainWindow::showIndex(){
  htmlChange=true;
  if(textChange==false){
    QString htmlStr=htmlLabel->toHtml();
    textArea->setPlainText(htmlStr);
  }
  htmlChange=false;
}

void MainWindow::setupActions()
{
  textChange=false;
  htmlChange=false;
  KAction* clearAction = new KAction(this);
  clearAction->setText(i18n("Clear"));
  clearAction->setIcon(KIcon("document-new"));
  clearAction->setShortcut(Qt::CTRL + Qt::Key_W);
  actionCollection()->addAction("clear", clearAction);
  connect(clearAction, SIGNAL(triggered(bool)),
          textArea, SLOT(clear()));
  
  KAction* refreshAction = new KAction(this);
  refreshAction->setText(i18n("Refresh"));
  refreshAction->setIcon(KIcon("document-refresh"));
  refreshAction->setShortcut(Qt::CTRL + Qt::Key_R);
  actionCollection()->addAction("Refresh", refreshAction);
  connect(refreshAction, SIGNAL(triggered(bool)),
          this , SLOT(refreshView()));
  
  connect(textArea , SIGNAL(textChanged()),
	  this , SLOT(refreshView()));
  
  connect(htmlLabel , SIGNAL(textChanged()),
	  this , SLOT(showIndex()));
 
  KStandardAction::quit(kapp, SLOT(quit()),
                        actionCollection());
 
  KStandardAction::open(this, SLOT(openFile()),
                        actionCollection()); //новое
 
  KStandardAction::save(this, SLOT(saveFile()),
                        actionCollection()); //новое
 
  KStandardAction::saveAs(this, SLOT(saveFileAs()),
                        actionCollection()); //новое
 
  KStandardAction::openNew(this, SLOT(newFile()),
                        actionCollection()); //новое
 
  setupGUI();
}
 
//Дальше все новое
 
void MainWindow::newFile()
{
  fileName.clear();
  textArea->clear();
}
 
void MainWindow::saveFileAs(const QString &outputFileName)
{
  KSaveFile file(outputFileName);
  file.open();
 
  QByteArray outputByteArray;
  outputByteArray.append(textArea->toPlainText().toUtf8());
  file.write(outputByteArray);
  file.finalize();
  file.close();
 
  fileName = outputFileName;
}
 
void MainWindow::saveFileAs()
{
  saveFileAs(KFileDialog::getSaveFileName());
}
 
void MainWindow::saveFile()
{
  if(!fileName.isEmpty())
  {
    saveFileAs(fileName);
  }
  else
  {
    saveFileAs();
  }
}
 
void MainWindow::openFile()
{
  QString fileNameFromDialog = KFileDialog::getOpenFileName();
 
  QString tmpFile;
  if(KIO::NetAccess::download(fileNameFromDialog, tmpFile, 
         this))
  {
    QFile file(tmpFile);
    file.open(QIODevice::ReadOnly);
    QString data = QTextStream(&file).readAll();
    htmlLabel->setHtml(data);
    textArea->setPlainText(data);
    fileName = fileNameFromDialog;
 
    KIO::NetAccess::removeTempFile(tmpFile);
  }
  else
  {
    KMessageBox::error(this, 
        KIO::NetAccess::lastErrorString());
  }
}