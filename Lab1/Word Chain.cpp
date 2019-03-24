#include <iostream>
#include <cstdio>
#include "word.h"

using namespace std;
FILE * fin;

int main(int argc, char* argv[]){
    if (argc == 3){
        fin = fopen(argv[2], "r");
        Word word_list;
        word_list.Init(fin);
        //word_list.Print();
        if (argv[1][1] == 'w'){
            word_list.makeEdge();
            word_list.maxWord();
        }
        else if (argv[1][1] == 'c'){
            word_list.makeEdge();
            word_list.maxLength();
        }
    }
    else {
        
    }
}