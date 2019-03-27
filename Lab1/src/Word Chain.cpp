#include <iostream>
#include <cstdio>
#include "maxWordLength.h"
#define Debug1

using namespace std;
FILE * fin;

int main(int argc, char* argv[]){
    // cout << "+++++++++" << endl;
    if (argc == 3){
        fin = fopen(argv[2], "r");
        max_Word_Length word_list;
        word_list.Init(fin);
#ifdef Debug
        word_list.Print();
#endif
        if (argv[1][1] == 'w'){//最长单词链
            word_list.makeEdge();
            word_list.maxWord();
        }
        else if (argv[1][1] == 'c'){//最多字母数目
            word_list.makeEdge();
            word_list.maxLength();
        }
    }
    else if(argv[1][1] == 'n'){//指定单词数
        // cout << "******" << endl;
        fin = fopen(argv[4], "r");
        max_Word_Length word_list;
        word_list.Init(fin);
        // cout << "123121313" << endl;
        word_list.makeEdge();
        int n = 0;
        for (int i = 0; i < strlen(argv[2]); i++){
            n = n * 10 + argv[2][i] - '0';
        }
        // cout << n << endl;
        word_list.wordLength(n);
    }
    else {
        if(argc > 5){//指定头和尾
            fin = fopen(argv[6], "r");
            max_Word_Length word_list;
            word_list.Init(fin);
            word_list.makeEdge();
            word_list.maxWordHeadAndTail(argv[2][0], argv[4][0]);
        }
        else if(argv[1][1] == 'h'){//指定头
            fin = fopen(argv[4], "r");
            max_Word_Length word_list;
            word_list.Init(fin);
            word_list.makeEdge();
            word_list.maxWordHead(argv[2][0]);
        }
        else {//指定尾
            fin = fopen(argv[4], "r");
            max_Word_Length word_list;
            word_list.Init(fin);
            word_list.makeEdge();
            word_list.maxWordTail(argv[2][0]);
        }
    }
    return 0;
}