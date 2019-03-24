#ifndef WORD
#define WORD
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>

using namespace std;

class Word
{
public:
    string wordList[10000];
    int wordNumber = 0;
    
    int Init(FILE * fin);
    void Print();
    void makeEdge();
    void maxWord();
    void maxLength();
};

int Word::Init(FILE * fin)
{
    while(!feof(fin)){
        char ch = fgetc(fin);
        if (ch == EOF){
            wordNumber++;
            break;
        }
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')){
            if (ch >= 'a' && ch <= 'z')
                wordList[wordNumber] += ch;
            else wordList[wordNumber] += (ch - 'A' + 'a');
        }
        else {
            wordNumber++;
        }
    }
}

void Word::Print()
{
    for (int i = 0; i < wordNumber; i++){
        cout << wordList[i] << endl;
    }
}

void Word::makeEdge()
{
    
}

void Word::maxWord()
{
}

void Word::maxLength()
{
}

#endif