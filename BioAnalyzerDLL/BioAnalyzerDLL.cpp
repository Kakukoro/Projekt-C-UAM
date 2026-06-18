// BioAnalyzerDLL.cpp
#include "BioAnalyzerDLL.h"  // MUST be first (defines BIOANALYZERDLL_API)
#include <string>
#include <sstream>
#include <cctype>   // For std::toupper
#include <map>
#include <vector>
#include <algorithm>

// --- Helper Functions ---

// Detect sequence type (DNA, RNA, or Protein)
std::string rozpoznajTypImpl(const std::string& seq) {
    bool maT = false;
    bool maU = false;
    bool maInneNukleotydy = false;
    for (char c : seq) {
        char uc = std::toupper(static_cast<unsigned char>(c));
        if (uc == 'T') maT = true;
        else if (uc == 'U') maU = true;
        else if (uc != 'A' && uc != 'C' && uc != 'G') {
            maInneNukleotydy = true;
        }
    }
    if (maInneNukleotydy) return "Bialko";
    if (maU && !maT) return "RNA";
    return "DNA";
}

// Basic sequence analysis
std::string analizujSekwencjeImpl(const std::string& seq) {
    std::ostringstream oss;
    oss << "\n--- PODSTAWOWA ANALIZA ---\n";
    oss << "Dlugosc sekwencji: " << seq.length() << " aminokwasow/nukleotydow.\n";

    std::map<char, int> liczniki;
    int gcCount = 0;
    int nukiCount = 0;
    for (char c : seq) {
        char uc = std::toupper(static_cast<unsigned char>(c));
        liczniki[uc]++;
        if (uc == 'G' || uc == 'C') gcCount++;
        if (uc == 'A' || uc == 'T' || uc == 'U' || uc == 'G' || uc == 'C') nukiCount++;
    }

    oss << "Liczba poszczegolnych elementow:\n";
    for (auto const& [znak, ilosc] : liczniki)
        oss << "  " << znak << ": " << ilosc << "\n";

    if (nukiCount > 0) {
        double gcProcent = (static_cast<double>(gcCount) / seq.length()) * 100.0;
        oss << "Zawartosc GC: " << gcProcent << "%\n";
    }
    return oss.str();
}

// DNA transcription to RNA
std::string transkrypcjaImpl(const std::string& dna) {
    std::string rna = dna;
    for (char& c : rna) {
        if (std::toupper(static_cast<unsigned char>(c)) == 'T') c = 'U';
        else if (std::toupper(static_cast<unsigned char>(c)) == 't') c = 'u';
    }
    return rna;
}

// Complementary strand
std::string nicKomplementarnaImpl(const std::string& dna) {
    std::string komplementarna;
    for (char c : dna) {
        switch (std::toupper(static_cast<unsigned char>(c))) {
        case 'A': komplementarna += 'T'; break;
        case 'T': komplementarna += 'A'; break;
        case 'C': komplementarna += 'G'; break;
        case 'G': komplementarna += 'C'; break;
        default:  komplementarna += c;
        }
    }
    return komplementarna;
}

// RNA translation to protein
std::string translacjaImpl(const std::string& rna) {
    std::map<std::string, char> kodony = {
        {"AUG", 'M'}, {"UUU", 'F'}, {"UUC", 'F'}, {"UUA", 'L'}, {"UUG", 'L'},
        {"UCU", 'S'}, {"UCC", 'S'}, {"UCA", 'S'}, {"UCG", 'S'}, {"UAU", 'Y'},
        {"UAC", 'Y'}, {"UGU", 'C'}, {"UGC", 'C'}, {"UGG", 'W'}, {"CUU", 'L'},
        {"CUC", 'L'}, {"CUA", 'L'}, {"CUG", 'L'}, {"CCU", 'P'}, {"CCC", 'P'},
        {"CCA", 'P'}, {"CCG", 'P'}, {"CAU", 'H'}, {"CAC", 'H'}, {"CAA", 'Q'},
        {"CAG", 'Q'}, {"CGU", 'R'}, {"CGC", 'R'}, {"CGA", 'R'}, {"CGG", 'R'},
        {"AUU", 'I'}, {"AUC", 'I'}, {"AUA", 'I'}, {"ACU", 'T'}, {"ACC", 'T'},
        {"ACA", 'T'}, {"ACG", 'T'}, {"AAU", 'N'}, {"AAC", 'N'}, {"AAA", 'K'},
        {"AAG", 'K'}, {"AGU", 'S'}, {"AGC", 'S'}, {"AGA", 'R'}, {"AGG", 'R'},
        {"GUU", 'V'}, {"GUC", 'V'}, {"GUA", 'V'}, {"GUG", 'V'}, {"GCU", 'A'},
        {"GCC", 'A'}, {"GCA", 'A'}, {"GCG", 'A'}, {"GAU", 'D'}, {"GAC", 'D'},
        {"GAA", 'E'}, {"GAG", 'E'}, {"GGU", 'G'}, {"GGC", 'G'}, {"GGA", 'G'},
        {"GGG", 'G'}, {"UAA", '*'}, {"UAG", '*'}, {"UGA", '*'}
    };

    std::string bialko;
    for (size_t i = 0; i + 2 < rna.length(); i += 3) {
        std::string kodon = rna.substr(i, 3);
        for (char& c : kodon) c = std::toupper(static_cast<unsigned char>(c));
        if (kodony.count(kodon)) {
            char aminokwas = kodony[kodon];
            if (aminokwas == '*') {
                bialko += "[Kodon STOP na pozycji " + std::to_string(i) + "]";
                break;
            }
            if (aminokwas == 'M' && i == 0)
                bialko += "[Kodon START na pozycji " + std::to_string(i) + "]";
            bialko += aminokwas;
        }
    }
    return bialko;
}

// Motif search
std::string wyszukajMotywImpl(const std::string& seq, const std::string& motyw) {
    std::ostringstream oss;
    oss << "\n--- WYSZUKIWANIE MOTYWU ---\n";
    size_t pos = seq.find(motyw);
    if (pos == std::string::npos) {
        oss << "Nie znaleziono motywu: " << motyw << "\n";
        return oss.str();
    }
    while (pos != std::string::npos) {
        oss << "Znaleziono motyw '" << motyw << "' na pozycji: " << pos << "\n";
        pos = seq.find(motyw, pos + 1);
    }
    return oss.str();
}

// Mutation analysis
std::string analizujMutacjeImpl(const std::string& seq1, const std::string& seq2) {
    std::ostringstream oss;
    oss << "\n--- ANALIZA MUTACJI ---\n";
    if (seq1.length() != seq2.length()) {
        oss << "Sekwencje maja rozne dlugosci. Porownanie uproszczone (pozycja po pozycji) niemozliwe.\n";
        return oss.str();
    }

    int mutacje = 0;
    for (size_t i = 0; i < seq1.length(); ++i) {
        if (std::toupper(static_cast<unsigned char>(seq1[i])) != std::toupper(static_cast<unsigned char>(seq2[i]))) {
            oss << "Mutacja (Substytucja) na pozycji " << i
                << ": " << seq1[i] << " -> " << seq2[i] << "\n";
            mutacje++;
        }
    }
    if (mutacje == 0) oss << "Sekwencje sa identyczne!\n";
    return oss.str();
}

// Percentage composition
std::string pobierzSkladProcentowyImpl(const std::string& seq) {
    int countA = 0, countT = 0, countG = 0, countC = 0;
    for (char c : seq) {
        char uc = std::toupper(static_cast<unsigned char>(c));
        if (uc == 'A') countA++;
        else if (uc == 'T') countT++;
        else if (uc == 'G') countG++;
        else if (uc == 'C') countC++;
    }
    int total = countA + countT + countG + countC;
    if (total == 0) return "0,0,0,0";

    double pctA = (static_cast<double>(countA) / total) * 100.0;
    double pctT = (static_cast<double>(countT) / total) * 100.0;
    double pctG = (static_cast<double>(countG) / total) * 100.0;
    double pctC = (static_cast<double>(countC) / total) * 100.0;

    return std::to_string(pctA) + "," + std::to_string(pctT) + "," +
           std::to_string(pctG) + "," + std::to_string(pctC);
}

// GC content in sliding window
std::string obliczGCImpl(const std::string& seq, int windowSize) {
    std::ostringstream oss;
    if (seq.empty() || windowSize <= 0 || windowSize > static_cast<int>(seq.length())) {
        return "";
    }

    for (size_t i = 0; i <= seq.length() - windowSize; ++i) {
        int gcCount = 0;
        for (size_t j = i; j < i + windowSize; ++j) {
            char c = std::toupper(static_cast<unsigned char>(seq[j]));
            if (c == 'G' || c == 'C') gcCount++;
        }
        double gcPercent = (static_cast<double>(gcCount) / windowSize) * 100.0;
        oss << gcPercent;
        if (i < seq.length() - windowSize) oss << ",";
    }
    return oss.str();
}

// --- Exported C functions ---
extern "C" {
BIOANALYZERDLL_API const char* rozpoznajTyp(const char* seq) {
    static std::string result = rozpoznajTypImpl(seq);
    return result.c_str();
}

BIOANALYZERDLL_API const char* analizujSekwencje(const char* seq) {
    static std::string result = analizujSekwencjeImpl(seq);
    return result.c_str();
}

BIOANALYZERDLL_API const char* transkrypcja(const char* dna) {
    static std::string result = transkrypcjaImpl(dna);
    return result.c_str();
}

BIOANALYZERDLL_API const char* nicKomplementarna(const char* dna) {
    static std::string result = nicKomplementarnaImpl(dna);
    return result.c_str();
}

BIOANALYZERDLL_API const char* translacja(const char* rna) {
    static std::string result = translacjaImpl(rna);
    return result.c_str();
}

BIOANALYZERDLL_API const char* wyszukajMotyw(const char* seq, const char* motyw) {
    static std::string result = wyszukajMotywImpl(seq, motyw);
    return result.c_str();
}

BIOANALYZERDLL_API const char* analizujMutacje(const char* seq1, const char* seq2) {
    static std::string result = analizujMutacjeImpl(seq1, seq2);
    return result.c_str();
}

BIOANALYZERDLL_API const char* pobierzSkladProcentowy(const char* seq) {
    static std::string result = pobierzSkladProcentowyImpl(seq);
    return result.c_str();
}

BIOANALYZERDLL_API const char* obliczGC(const char* seq, int windowSize) {
    static std::string result = obliczGCImpl(seq, windowSize);
    return result.c_str();
}
}