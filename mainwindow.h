#pragma once

#include <QMainWindow>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLibrary>
#include <QtCharts/QChartView>    // Qt Charts headers
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChart>

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
    QPushButton *analyzeButton;
    QPushButton *transcribeButton;
    QPushButton *complementaryButton;
    QPushButton *translateButton;
    QPushButton *motifButton;
    QPushButton *mutationButton;

    QLibrary *dll;

    // Typedefs for DLL functions (Polish names)
    typedef const char* (*RozpoznajTypFunc)(const char*);
    typedef const char* (*AnalizujSekwencjeFunc)(const char*);
    typedef const char* (*TranskrypcjaFunc)(const char*);
    typedef const char* (*NicKomplementarnaFunc)(const char*);
    typedef const char* (*TranslacjaFunc)(const char*);
    typedef const char* (*WyszukajMotywFunc)(const char*, const char*);
    typedef const char* (*AnalizujMutacjeFunc)(const char*, const char*);
<<<<<<< Updated upstream
    typedef const char* (*PobierzSkladProcentowyFunc)(const char*);
    typedef const char* (*ObliczGCFunc)(const char*, int);
=======
    typedef const char* (*PobierzSkladProcentowyFunc)(const char*);  // New
    typedef const char* (*ObliczGCFunc)(const char*, int);            // New
>>>>>>> Stashed changes

    // Function pointers
    RozpoznajTypFunc rozpoznajTypFunc;
    AnalizujSekwencjeFunc analizujSekwencjeFunc;
    TranskrypcjaFunc transkrypcjaFunc;
    NicKomplementarnaFunc nicKomplementarnaFunc;
    TranslacjaFunc translacjaFunc;
    WyszukajMotywFunc wyszukajMotywFunc;
    AnalizujMutacjeFunc analizujMutacjeFunc;
<<<<<<< Updated upstream
    PobierzSkladProcentowyFunc pobierzSkladProcentowyFunc;
    ObliczGCFunc obliczGCFunc;
=======
    PobierzSkladProcentowyFunc pobierzSkladProcentowyFunc;  // New
    ObliczGCFunc obliczGCFunc;                              // New
>>>>>>> Stashed changes

    bool zaladujDLL();
};
