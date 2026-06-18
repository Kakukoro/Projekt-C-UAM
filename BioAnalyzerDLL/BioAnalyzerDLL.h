// BioAnalyzerDLL.h
#pragma once

#ifdef _WIN32
    #ifdef BIOANALYZERDLL_EXPORTS
        #define BIOANALYZERDLL_API __declspec(dllexport)
    #else
        #define BIOANALYZERDLL_API __declspec(dllimport)
    #endif
#else
    #define BIOANALYZERDLL_API __attribute__((visibility("default")))
#endif

#include <string>

extern "C" {
    BIOANALYZERDLL_API const char* rozpoznajTyp(const char* seq);
    BIOANALYZERDLL_API const char* analizujSekwencje(const char* seq);
    BIOANALYZERDLL_API const char* transkrypcja(const char* dna);
    BIOANALYZERDLL_API const char* nicKomplementarna(const char* dna);
    BIOANALYZERDLL_API const char* translacja(const char* rna);
    BIOANALYZERDLL_API const char* wyszukajMotyw(const char* seq, const char* motyw);
    BIOANALYZERDLL_API const char* analizujMutacje(const char* seq1, const char* seq2);
    BIOANALYZERDLL_API const char* pobierzSkladProcentowy(const char* seq);      // New
    BIOANALYZERDLL_API const char* obliczGC(const char* seq, int windowSize); // New
}