#include <iostream>
#include <cstdio>
#include "maxWordLength.h"

using namespace std;
FILE * fin;

int main(int argc, char* argv[]){
    if (argc == 3){
        fin = fopen(argv[2], "r");
        max_Word_Length word_list;
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
    else if(argv[1][1] == 'n'){

    }
    else {
        fin = fopen(argv[4], "r");
        max_Word_Length word_list;
        word_list.Init(fin);
        if(argc > 5){//head and tail
            word_list.maxWordHeadAndTail(argv[2][0], argv[4][0]);
        }
        else if(argv[1][1] == 'h'){//head
            word_list.maxWordHead(argv[2][0]);
        }
        else {//tail
            word_list.maxWordTail(argv[2][0]);
        }
    }
}