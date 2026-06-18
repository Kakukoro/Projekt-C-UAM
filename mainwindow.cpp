#include "mainwindow.h"
#include <QMessageBox>
#include <QDebug>
<<<<<<< Updated upstream
#include <QChartView>
#include <QBarSet>
#include <QBarSeries>
#include <QBarCategoryAxis>
#include <QLineSeries>
#include <QValueAxis>
#include <QStringList>
#include <QChart>

using namespace QT_CHARTS_NAMESPACE;
=======
#include <QtCharts/QChartView>    // Qt Charts headers
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChart>

// NO using namespace QtCharts; (Qt 6 does NOT use a namespace for Charts)
>>>>>>> Stashed changes

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    // Główne okno i układ
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Grupa wejścia
    QGroupBox *inputGroup = new QGroupBox("Wejście", this);
    QVBoxLayout *inputLayout = new QVBoxLayout(inputGroup);

    sequenceInput = new QLineEdit(this);
    sequenceInput->setPlaceholderText("Wprowadź sekwencję (np. ATGC...)");
    inputLayout->addWidget(sequenceInput);

    motifInput = new QLineEdit(this);
    motifInput->setPlaceholderText("Wprowadź motyw do wyszukania");
    inputLayout->addWidget(motifInput);

    secondSequenceInput = new QLineEdit(this);
    secondSequenceInput->setPlaceholderText("Wprowadź drugą sekwencję do porównania mutacji");
    inputLayout->addWidget(secondSequenceInput);

    // Grupa wyjścia
    QGroupBox *outputGroup = new QGroupBox("Wynik", this);
    QVBoxLayout *outputLayout = new QVBoxLayout(outputGroup);

    output = new QTextEdit(this);
    output->setReadOnly(true);
    outputLayout->addWidget(output);

    // Grupa przycisków
    QGroupBox *buttonsGroup = new QGroupBox("Operacje", this);
    QHBoxLayout *buttonsLayout = new QHBoxLayout(buttonsGroup);

    // Deklaruj przyciski jako zmienne lokalne (nie muszą być memberami, jeśli nie są używane poza konstruktorem)
    QPushButton *analyzeButton = new QPushButton("Analizuj Sekwencję", this);
    QPushButton *transcribeButton = new QPushButton("Transkrypcja (DNA → RNA)", this);
    QPushButton *complementaryButton = new QPushButton("Nić Komplementarna", this);
    QPushButton *translateButton = new QPushButton("Translacja (RNA → Białko)", this);
    QPushButton *motifButton = new QPushButton("Wyszukaj Motyw", this);
    QPushButton *mutationButton = new QPushButton("Analizuj Mutacje", this);

    buttonsLayout->addWidget(analyzeButton);
    buttonsLayout->addWidget(transcribeButton);
    buttonsLayout->addWidget(complementaryButton);
    buttonsLayout->addWidget(translateButton);
    buttonsLayout->addWidget(motifButton);
    buttonsLayout->addWidget(mutationButton);

    // Dodaj grupy do głównego układu
    mainLayout->addWidget(inputGroup);
    mainLayout->addWidget(buttonsGroup);
    mainLayout->addWidget(outputGroup);

    setCentralWidget(centralWidget);

    // Połącz przyciski ze slotami
    connect(analyzeButton, &QPushButton::clicked, this, &MainWindow::analizujSekwencje);
    connect(transcribeButton, &QPushButton::clicked, this, &MainWindow::transkrybujDNA);
    connect(complementaryButton, &QPushButton::clicked, this, &MainWindow::pobierzNicKomplementarna);
    connect(translateButton, &QPushButton::clicked, this, &MainWindow::tlumaczRNA);
    connect(motifButton, &QPushButton::clicked, this, &MainWindow::wyszukajMotyw);
    connect(mutationButton, &QPushButton::clicked, this, &MainWindow::analizujMutacje);

    // Załaduj DLL
    if (!zaladujDLL()) {
        QMessageBox::critical(this, "Błąd", "Nie udało się załadować biblioteki BioAnalyzer!");
    }
}

bool MainWindow::zaladujDLL() {
    dll = new QLibrary("BioAnalyzer", this);
    qDebug() << "Próba załadowania DLL z:" << dll->fileName();
    if (!dll->load()) {
        qWarning() << "Nie udało się załadować biblioteki:" << dll->errorString();
        return false;
    }
    qDebug() << "DLL załadowana pomyślnie!";

    // Rozwiąż funkcje (polskie nazwy!)
    rozpoznajTypFunc = (RozpoznajTypFunc)dll->resolve("rozpoznajTyp");
    analizujSekwencjeFunc = (AnalizujSekwencjeFunc)dll->resolve("analizujSekwencje");
    transkrypcjaFunc = (TranskrypcjaFunc)dll->resolve("transkrypcja");
    nicKomplementarnaFunc = (NicKomplementarnaFunc)dll->resolve("nicKomplementarna");
    translacjaFunc = (TranslacjaFunc)dll->resolve("translacja");
    wyszukajMotywFunc = (WyszukajMotywFunc)dll->resolve("wyszukajMotyw");
    analizujMutacjeFunc = (AnalizujMutacjeFunc)dll->resolve("analizujMutacje");
    pobierzSkladProcentowyFunc = (PobierzSkladProcentowyFunc)dll->resolve("pobierzSkladProcentowy");
    obliczGCFunc = (ObliczGCFunc)dll->resolve("obliczGC");
<<<<<<< Updated upstream
    
    if (!rozpoznajTypFunc || !analizujSekwencjeFunc || !transkrypcjaFunc ||
        !nicKomplementarnaFunc || !translacjaFunc || !wyszukajMotywFunc || !analizujMutacjeFunc) || !pobierzSkladProcentowyFunc || !obliczGCFunc) {
=======

    if (!rozpoznajTypFunc || !analizujSekwencjeFunc || !transkrypcjaFunc ||
        !nicKomplementarnaFunc || !translacjaFunc || !wyszukajMotywFunc ||
        !analizujMutacjeFunc || !pobierzSkladProcentowyFunc || !obliczGCFunc) {
>>>>>>> Stashed changes
        qWarning() << "Nie udało się rozpoznać jednej lub więcej funkcji!";
        return false;
    }
    return true;
}

void MainWindow::analizujSekwencje() {
    QString seq = sequenceInput->text();
    if (seq.isEmpty()) {
        output->append("Wprowadź sekwencję.");
        return;
    }

<<<<<<< Updated upstream
    // 1. Dotychczasowa analiza tekstowa
    const char* result = analizujSekwencjeFunc(seq.toStdString().c_str());
    output->append(QString::fromUtf8(result));

    // wykres = rozklad nukleotydow (Słupkowy)
    
=======
    // Text analysis
    const char* result = analizujSekwencjeFunc(seq.toStdString().c_str());
    output->append(QString::fromUtf8(result));

    // Bar chart: Nucleotide composition
>>>>>>> Stashed changes
    double pctA = 25.0, pctT = 25.0, pctG = 25.0, pctC = 25.0;
    if (pobierzSkladProcentowyFunc) {
        QString skladStr = QString::fromUtf8(pobierzSkladProcentowyFunc(seq.toStdString().c_str()));
        QStringList lista = skladStr.split(",");
        if (lista.size() == 4) {
            pctA = lista[0].toDouble();
            pctT = lista[1].toDouble();
            pctG = lista[2].toDouble();
            pctC = lista[3].toDouble();
        }
    }

<<<<<<< Updated upstream
=======
    // Use Qt Charts classes directly (no namespace)
>>>>>>> Stashed changes
    QBarSet *set = new QBarSet("Nukleotydy (%)");
    *set << pctA << pctT << pctG << pctC;

    QBarSeries *barSeries = new QBarSeries();
    barSeries->append(set);

    QChart *barChart = new QChart();
    barChart->addSeries(barSeries);
    barChart->setTitle("Skład procentowy sekwencji");
    barChart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    categories << "Adenina (A)" << "Tymina (T)" << "Guanina (G)" << "Cytozyna (C)";
    QBarCategoryAxis *axisXBar = new QBarCategoryAxis();
    axisXBar->append(categories);
    barChart->addAxis(axisXBar, Qt::AlignBottom);
    barSeries->attachAxis(axisXBar);

    QValueAxis *axisYBar = new QValueAxis();
    axisYBar->setRange(0, 100);
    axisYBar->setTitleText("Zawartość %");
    barChart->addAxis(axisYBar, Qt::AlignLeft);
    barSeries->attachAxis(axisYBar);

<<<<<<< Updated upstream
    QChartView *barChartView = new QChartView(barChart);
    barChartView->setRenderHint(QPainter::Antialiasing);
    barChartView->resize(500, 400);
=======
    QChartView *barChartView = new QChartView(barChart, this);
    barChartView->setRenderHint(QPainter::Antialiasing);
>>>>>>> Stashed changes
    barChartView->setWindowTitle("Rozkład ATGC");
    barChartView->setAttribute(Qt::WA_DeleteOnClose);
    barChartView->show();

<<<<<<< Updated upstream
    // wykres 2 = zawartosc GC (Liniowy)
    
=======
    // Line chart: GC content (sliding window)
>>>>>>> Stashed changes
    QLineSeries *lineSeries = new QLineSeries();
    lineSeries->setName("Zawartość GC (%)");

    int maxX = 0;
    if (obliczGCFunc) {
<<<<<<< Updated upstream
        // Okno przesuwne o wielkości 10 nukleotydów
        QString gcStr = QString::fromUtf8(obliczGCFunc(seq.toStdString().c_str(), 10));
        QStringList punkty = gcStr.split(",", Qt::SkipEmptyParts);
        
=======
        QString gcStr = QString::fromUtf8(obliczGCFunc(seq.toStdString().c_str(), 10));
        QStringList punkty = gcStr.split(",", Qt::SkipEmptyParts);
>>>>>>> Stashed changes
        for (int i = 0; i < punkty.size(); ++i) {
            lineSeries->append(i, punkty[i].toDouble());
        }
        maxX = punkty.size() - 1;
    } else {
<<<<<<< Updated upstream
        // Wartości demonstracyjne (fallback)
=======
        // Fallback: Demo values
>>>>>>> Stashed changes
        for (int i = 0; i < seq.length(); ++i) {
            lineSeries->append(i, 40.0 + (i % 3) * 10.0);
        }
        maxX = seq.length() - 1;
    }

    QChart *lineChart = new QChart();
    lineChart->addSeries(lineSeries);
    lineChart->setTitle("Wykres GC-Content (Okno przesuwne)");
    lineChart->setAnimationOptions(QChart::SeriesAnimations);

    QValueAxis *axisXLine = new QValueAxis();
    axisXLine->setRange(0, maxX > 0 ? maxX : 10);
    axisXLine->setTitleText("Pozycja w sekwencji (Okno)");
    axisXLine->setLabelFormat("%d");
    lineChart->addAxis(axisXLine, Qt::AlignBottom);
    lineSeries->attachAxis(axisXLine);

    QValueAxis *axisYLine = new QValueAxis();
    axisYLine->setRange(0, 100);
    axisYLine->setTitleText("Procent (%)");
    lineChart->addAxis(axisYLine, Qt::AlignLeft);
    lineSeries->attachAxis(axisYLine);

<<<<<<< Updated upstream
    QChartView *lineChartView = new QChartView(lineChart);
    lineChartView->setRenderHint(QPainter::Antialiasing);
    lineChartView->resize(600, 400);
    lineChartView->setWindowTitle("Analiza GC-Content");
    lineChartView->setAttribute(Qt::WA_DeleteOnClose);
    
    // Przesunięcie okna, żeby się nie nakładały
    lineChartView->move(barChartView->x() + 520, barChartView->y());
=======
    QChartView *lineChartView = new QChartView(lineChart, this);
    lineChartView->setRenderHint(QPainter::Antialiasing);
    lineChartView->setWindowTitle("Analiza GC-Content");
    lineChartView->setAttribute(Qt::WA_DeleteOnClose);
    lineChartView->move(barChartView->x() + barChartView->width() + 10, barChartView->y());
>>>>>>> Stashed changes
    lineChartView->show();
}

// Rest of your slot implementations (transkrybujDNA, pobierzNicKomplementarna, etc.)
void MainWindow::transkrybujDNA() {
    QString dna = sequenceInput->text();
    if (dna.isEmpty()) {
        output->append("Wprowadź sekwencję DNA.");
        return;
    }
    const char* result = transkrypcjaFunc(dna.toStdString().c_str());
    output->append("Transkrypcja (DNA → RNA): " + QString::fromUtf8(result));
}

void MainWindow::pobierzNicKomplementarna() {
    QString dna = sequenceInput->text();
    if (dna.isEmpty()) {
        output->append("Wprowadź sekwencję DNA.");
        return;
    }
    const char* result = nicKomplementarnaFunc(dna.toStdString().c_str());
    output->append("Nić komplementarna: " + QString::fromUtf8(result));
}

void MainWindow::tlumaczRNA() {
    QString rna = sequenceInput->text();
    if (rna.isEmpty()) {
        output->append("Wprowadź sekwencję RNA.");
        return;
    }
    const char* result = translacjaFunc(rna.toStdString().c_str());
    output->append("Translacja (RNA → Białko): " + QString::fromUtf8(result));
}

void MainWindow::wyszukajMotyw() {
    QString seq = sequenceInput->text();
    QString motif = motifInput->text();
    if (seq.isEmpty() || motif.isEmpty()) {
        output->append("Wprowadź zarówno sekwencję, jak i motyw.");
        return;
    }
    const char* result = wyszukajMotywFunc(seq.toStdString().c_str(), motif.toStdString().c_str());
    output->append(QString::fromUtf8(result));
}

void MainWindow::analizujMutacje() {
    QString seq1 = sequenceInput->text();
    QString seq2 = secondSequenceInput->text();
    if (seq1.isEmpty() || seq2.isEmpty()) {
        output->append("Wprowadź obie sekwencje.");
        return;
    }
    const char* result = analizujMutacjeFunc(seq1.toStdString().c_str(), seq2.toStdString().c_str());
    output->append(QString::fromUtf8(result));
}
