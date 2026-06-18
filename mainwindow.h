#pragma once

#include <QMainWindow>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLibrary>

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void analizujSekwencje();
    void transkrybujDNA();
    void pobierzNicKomplementarna();
    void tlumaczRNA();
    void wyszukajMotyw();
    void analizujMutacje();

private:
    QLineEdit *sequenceInput;
    QLineEdit *motifInput;
    QLineEdit *secondSequenceInput;
    QTextEdit *output;

    QLibrary *dll;

    // Typedefy dla funkcji z DLL (polskie nazwy!)
    typedef const char* (*RozpoznajTypFunc)(const char*);
    typedef const char* (*AnalizujSekwencjeFunc)(const char*);
    typedef const char* (*TranskrypcjaFunc)(const char*);
    typedef const char* (*NicKomplementarnaFunc)(const char*);
    typedef const char* (*TranslacjaFunc)(const char*);
    typedef const char* (*WyszukajMotywFunc)(const char*, const char*);
    typedef const char* (*AnalizujMutacjeFunc)(const char*, const char*);
    typedef const char* (*PobierzSkladProcentowyFunc)(const char*);
    typedef const char* (*ObliczGCFunc)(const char*, int);

    // Wskaźniki do funkcji DLL
    RozpoznajTypFunc rozpoznajTypFunc;
    AnalizujSekwencjeFunc analizujSekwencjeFunc;
    TranskrypcjaFunc transkrypcjaFunc;
    NicKomplementarnaFunc nicKomplementarnaFunc;
    TranslacjaFunc translacjaFunc;
    WyszukajMotywFunc wyszukajMotywFunc;
    AnalizujMutacjeFunc analizujMutacjeFunc;
    PobierzSkladProcentowyFunc pobierzSkladProcentowyFunc;
    ObliczGCFunc obliczGCFunc;

    bool zaladujDLL();
};
