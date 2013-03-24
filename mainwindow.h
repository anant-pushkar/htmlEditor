#ifndef MAINWINDOW_H
#define MAINWINDOW_H
 
#include <KXmlGuiWindow>
#include <KTextEdit>
#include <QLabel>
#include<KStatusBar>
 
class MainWindow : public KXmlGuiWindow
{
  Q_OBJECT //новое
 
  public:
    MainWindow(QWidget *parent=0);
 
  private:
    KTextEdit* htmlLabel;
    KTextEdit* textArea;
    void setupActions();
    QString fileName; 
    bool textChange;
    bool htmlChange;
 
  private slots: //новое
    void refreshView();
    void showIndex();
    void newFile(); //новое
    void openFile(); //новое
    void saveFile(); //новое
    void saveFileAs(); //новое
    void saveFileAs(const QString &outputFileName); //новое
};
 
#endif