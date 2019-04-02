#include <iostream>
#include <cstdio>
#include "word_Core.h"
#define Debug1

using namespace std;
// FILE * fin;

int gen_chain_word(char* word[], int len, char* result[], char head, char tail)
{
    Core word_list;
    word_list.Init(word, len);
    word_list.makeEdge();
    int ans = 0;
    if (head == '0' && tail == '0'){
        ans = word_list.maxWord(result);
    }
    else if(head != '0' && tail == '0'){
        ans = word_list.maxWordHead(head, result, 0);
    }
    else if(head == '0' && tail != 0){
        ans = word_list.maxWordTail(tail, result, 0);
    }
    else {
        ans = word_list.maxWordHeadAndTail(head, tail, result, 0);
    }
}

int gen_chain_char(char *word[], int len, char *result[], char head, char tail)
{
    Core word_list;
    word_list.Init(word, len);
    word_list.makeEdge();
    int ans = 0;
    if (head == '0' && tail == '0'){
        ans = word_list.maxWord(result);
    }
    else if(head != '0' && tail == '0'){
        ans = word_list.maxWordHead(head, result, 1);
    }
    else if(head == '0' && tail != 0){
        ans = word_list.maxWordTail(tail, result, 1);
    }
    else {
        ans = word_list.maxWordHeadAndTail(head, tail, result, 1);
    }
}
}

int main(int argc, char* argv[]){
//     if (argc == 3){
//         fin = fopen(argv[2], "r");
//         if (fin == NULL){
//             cout << "No File" << endl;
//             return 0;
//         }
//         Core word_list;
//         word_list.Init(fin);
// #ifdef Debug
//         word_list.Print();
// #endif
//         if (argv[1][1] == 'w'){//最长单词链
//             word_list.makeEdge();
//             word_list.maxWord();
//         }
//         else if (argv[1][1] == 'c'){//最多字母数目
//             word_list.makeEdge();
//             word_list.maxLength();
//         }
//     }
//     else if(argv[1][1] == 'n'){//指定单词数
//         fin = fopen(argv[4], "r");
//         if (fin == NULL){
//             cout << "No File" << endl;
//             return 0;
//         }
//         Core word_list;
//         word_list.Init(fin);
//         word_list.makeEdge();
//         int n = 0;
//         for (int i = 0; i < strlen(argv[2]); i++){
//             n = n * 10 + argv[2][i] - '0';
//         }
//         word_list.wordLength(n);
//     }
//     else {
//         if(argc > 5){//指定头和尾
//             fin = fopen(argv[6], "r");
//             if (fin == NULL){
//                 cout << "No File" << endl;
//                 return 0;
//             }
//             Core word_list;
//             word_list.Init(fin);
//             word_list.makeEdge();
//             word_list.maxWordHeadAndTail(argv[2][0], argv[4][0]);
//         }
//         else if(argv[1][1] == 'h'){//指定头
//             fin = fopen(argv[4], "r");
//             if (fin == NULL){
//                 cout << "No File" << endl;
//                 return 0;
//             }
//             Core word_list;
//             word_list.Init(fin);
//             word_list.makeEdge();
//             word_list.maxWordHead(argv[2][0]);
//         }
//         else {//指定尾
//             fin = fopen(argv[4], "r");
//             if (fin == NULL){
//                 cout << "No File" << endl;
//                 return 0;
//             }
//             Core word_list;
//             word_list.Init(fin);
//             word_list.makeEdge();
//             word_list.maxWordTail(argv[2][0]);
//         }
//     }
//     return 0;
}
