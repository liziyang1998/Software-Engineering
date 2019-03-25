#ifndef MAXWORDLENGTH
#define MAXWORDLENGTH
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

class max_Word_Length
{
private:
//储存单词和数量
    int wordNumber = 0;
    string wordList[10000];
//储存正反边和点的入度出度以及拓扑过程用到的队列
    vector<int>Edge[2][10000];
    int nodeIn[2][10000];//0 = 入度 1 = 出度
    queue<int>node;
//把单词编号放到对应开头和结尾数组中
    int wordHead[26][1000];
    int wordTail[26][1000];
//最长单词数目和路径
    int mmaxWord[10000];
    int maxWordPre[10000];
//最长字母数目和路径
    int mmaxLength[10000];
    int maxLengthPre[10000];
//搜索过程中用到的保存路径和最大值
    int tmpWordPre[10000];
    int tmpLengthPre[10000];
    int tmp_max = 0;
//搜索过程中当前最大值对应的单词编号
    int tmp_x = 0;
//标记数组
    bool flag[10000];
public:
//调试
    void Print();
//初始化
    int Init(FILE * fin);
    void makeEdge();//建边
//最长单词数目
    void maxWord();
    void maxWordDfs(int x);
//最多字母
    void maxLength();
    void maxLengthDfs(int x);
//同一递归输出前驱（用于递归输出单词）
    void Print_DFS(int *a, int x);
//分别对应指定头尾
//指定头
//指定尾
    void maxWordHeadAndTail(char head, char tail);
    void maxWordHead(char head);
    void maxWordTail(char tail);
//利用标记分别对应三种情况进行搜索求解
    void maxWordHeadAndTailDfs(int flag_head, int h, int flag_tail, int t, int anti);
//搜索指定长度的单词
    void wordLength(int n);
    void wordLengthDfs(int x, int n);
};

int max_Word_Length::Init(FILE *fin)
{
    char tmp;
    while(!feof(fin)){
        char ch = fgetc(fin);
        if(ch == EOF){
            if((tmp >= 'a' && tmp <= 'z') || (tmp >= 'A' && tmp <= 'Z'))
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
        tmp = ch;
    }
}

void max_Word_Length::Print()//Debug
{
    for (int i = 0; i < wordNumber; i++){
        cout << wordList[i] << endl;
    }
}

/*
建边过程中采用分别保存头尾的方法，降低循环的复杂度
*/
void max_Word_Length::makeEdge()
{
    for (int i = 0; i < wordNumber; i++){
    //对单词的头和尾把编号分别放到相应的数组中
        int h = wordList[i][0] - 'a';
        int t = wordList[i][wordList[i].size() - 1] - 'a';
        wordHead[h][++wordHead[h][0]] = i;
        wordTail[t][++wordTail[t][0]] = i;
    }
    //连边
    for (int i = 0; i < wordNumber; i++){
        int t = wordList[i][wordList[i].size() - 1] - 'a';
        for (int j = 1; j <= wordHead[t][0]; j++){
            if (i == wordHead[t][j]) continue;
            Edge[0][i].push_back(wordHead[t][j]);
            Edge[1][wordHead[t][j]].push_back(i);
            nodeIn[0][wordHead[t][j]]++;
            nodeIn[1][i]++;
        }
    }
}

/*
对于真实数据可猜想，环并不多，直接搜索有些暴力，尝试采用拓扑优化
先将没有环的部分用拓扑排序找出最长的单词长度，然后对于环的部分采用暴力搜索
不过两者时间复杂度基本一致
*/
void max_Word_Length::maxWord()
{
    //设置拓扑排序，找入度为0的点
    for (int i = 0; i < wordNumber; i++)
        maxWordPre[i] = -1, tmpWordPre[i] = -1;
    for (int i = 0; i < wordNumber; i++){
        mmaxWord[i] = 1;
        if(nodeIn[i] == 0){
            node.push(i); flag[i] = true; maxWordPre[i] = -1;
        }
    }
    //拓扑排序找最大值
    vector<int>::iterator It;
    while(!node.empty()){
        int curNode = node.front();
        node.pop();
        for (It = Edge[0][curNode].begin(); It != Edge[0][curNode].end(); It++){
            if (flag[*It]) continue;
            if (mmaxWord[*It] < mmaxWord[curNode] + 1){
                mmaxWord[*It] = mmaxWord[curNode] + 1;
                maxWordPre[*It] = curNode;
            }
            nodeIn[0][*It]--;
            if(nodeIn[*It] == 0){
                node.push(*It);
                flag[*It] = true;
            } 
        }
    }
    //如果排序后有入度不为0的点，那么存在环，搜索
    bool tmp_flag = false;
    for (int i = 0; i < wordNumber; i++){
        if (nodeIn[i] != 0)//有环 dfs
            tmp_flag = true;
    }
    if(!tmp_flag){
        //不存在环
        int mmmaxWord = 0;
        for (int i = 0; i < wordNumber; i++){
            mmmaxWord = max(mmmaxWord, mmaxWord[i]);
        }
        //单个单词不成链
        if (mmmaxWord == 1){
            printf("No Word Chain\n");
            return;
        }
        //找到最大值，递归求解
        for (int i = 0; i < wordNumber; i++){
            if (mmaxWord[i] == mmmaxWord){
                Print_DFS(maxWordPre, i);
                cout << wordList[i] << endl;
                return;
            }
        }
    }
    else {
        //如果有环
        for (int j = 0; j < wordNumber; j++)
            tmpWordPre[j] = maxWordPre[j];
        for (int i = 0; i < wordNumber; i++){
            if (nodeIn[i] != 0 && flag[i] == false){
                flag[i] = true;
                maxWordDfs(i);
                flag[i] = false;
            }
        }
        Print_DFS(maxWordPre, tmp_x);
        cout << wordList[tmp_x] << endl;
    }
}

void max_Word_Length::Print_DFS(int *a, int x)//递归数组a，a为传进来的不同的前驱数组
{
    if(a[x] == -1 || a[x] == x)return;
    Print_DFS(a, a[x]);
    cout << wordList[a[x]] << endl;
}

void max_Word_Length::maxWordDfs(int x) //对于环查dfs
{
    vector<int>::iterator It;
    for (It = Edge[0][x].begin(); It != Edge[0][x].end(); It++){
        if(!flag[*It]){
            if(mmaxWord[*It] < mmaxWord[x] + 1){
                int tmp = mmaxWord[*It];

                mmaxWord[*It] = mmaxWord[x] + 1;
                flag[*It] = true;
                tmpWordPre[*It] = x;
                
                maxWordDfs(*It);

                mmaxWord[*It] = tmp;
                flag[*It] = false;
                tmpWordPre[*It] = -1;
            } 
        }
    }
    if (tmp_max < mmaxWord[x]){
        tmp_max = mmaxWord[x];
        tmp_x = x;
        for (int i = 0; i < wordNumber; i++)
            maxWordPre[i] = tmpWordPre[i];
    }
}

void max_Word_Length::maxLength()//对于最多字母数目，同样可以先拓扑排序再搜索，这里直接写了搜索，因为两者时间复杂度一致均为 O(VE)
{
    for (int i = 0; i < wordNumber; i++)
        maxLengthPre[i] = -1, tmpLengthPre[i] = -1;
    for (int i = 0; i < wordNumber; i++)
        mmaxLength[i] = wordList[i].size();
    for (int i = 0; i < wordNumber; i++){
        flag[i] = true;
        maxLengthDfs(i);
        flag[i] = false;
    }
    Print_DFS(maxLengthPre, tmp_x);
    cout << wordList[tmp_x] << endl;
}

void max_Word_Length::maxLengthDfs(int x)
{
    vector<int>::iterator It;
    for (It = Edge[0][x].begin(); It != Edge[0][x].end(); It++){
        if(flag[*It])continue;
        if (mmaxLength[*It] < mmaxLength[x] + wordList[*It].size()){
            // cout << wordList[x] << " " << wordList[*It] << endl;
            int tmp = mmaxLength[*It];
            mmaxLength[*It] = mmaxLength[x] + wordList[*It].size();
            flag[*It] = true;
            tmpLengthPre[*It] = x;

            maxLengthDfs(*It);
            
            flag[*It] = false;
            mmaxLength[*It] = tmp;
            tmpLengthPre[*It] = -1;
        }
    }
    if(tmp_max < mmaxLength[x]){
        tmp_max = mmaxLength[x];
        tmp_x = x;
        for (int i = 0; i < wordNumber; i++)
            maxLengthPre[i] = tmpLengthPre[i];
    }
}

void max_Word_Length::maxWordHead(char head)
{
    int h = head - 'a';
    for (int i = 0; i < wordNumber; i++)
        maxWordPre[i] = -1, tmpWordPre[i] = -1;
    for (int i = 1; i <= wordHead[h][0]; i++)
        mmaxWord[wordHead[h][i]] = 1;
    //对于指定的开头字母可以根据初始化时保存下的wordHead数组迅速找到单词中所有以h开头的字母的编号
    //对于maxWordHeadAndTailDfs函数传入不同的参数可以搜索不同的结果
    for (int i = 1; i <= wordHead[h][0]; i++){
        flag[wordHead[h][i]] = true;
        maxWordHeadAndTailDfs(1, wordHead[h][i], 0, 0, 0);
        flag[wordHead[h][i]] = false; 
    }
    Print_DFS(maxWordPre, tmp_x);
    cout << wordList[tmp_x] << endl;
}

void max_Word_Length::maxWordTail(char tail)//方法同搜索以指定字母开头
{
    int t = tail - 'a';
    for (int i = 0; i < wordNumber; i++)
        maxWordPre[i] = -1, tmpWordPre[i] = -1;
    for (int i = 1; i <= wordTail[t][0]; i++)
        mmaxWord[wordTail[t][i]] = 1;
    for (int i = 1; i <= wordTail[t][0]; i++){
        flag[wordTail[t][i]] = true;
        maxWordHeadAndTailDfs(0, 0, 1, wordTail[t][i], 1);
        flag[wordTail[t][i]] = false;
    }
    while(maxWordPre[tmp_x] != -1){
        cout << wordList[tmp_x] << endl;
        tmp_x = maxWordPre[tmp_x];
    }
    cout << wordList[tmp_x] << endl;
}

void max_Word_Length::maxWordHeadAndTail(char head, char tail)
{
    int h = head - 'a';
    int t = tail - 'a';
    for (int i = 0; i < wordNumber; i++)
        maxWordPre[i] = -1, tmpWordPre[i] = -1;
    for (int i = 1; i <= wordHead[h][0]; i++)
        mmaxWord[wordHead[h][i]] = 1;
    //通过指定参数和dfs中的方法完成找以h开拓以t结尾的单词链
    for (int i = 1; i <= wordHead[h][0]; i++){
        flag[wordHead[h][i]] = true;
        maxWordHeadAndTailDfs(1, wordHead[h][i], 1, t, 0);
        flag[wordHead[h][i]] = false;
    }
    Print_DFS(maxWordPre, tmp_x);
    cout << wordList[tmp_x] << endl;

}

void max_Word_Length::maxWordHeadAndTailDfs(int flag_head, int h, int flag_tail, int t, int anti)
{
    //根据参数不同，功能不同，过程基本一样，边界判断不同
    if (flag_head){
        if (flag_tail){
            vector<int>::iterator It;
            for (It = Edge[anti][h].begin(); It != Edge[anti][h].end(); It++){
                if(!flag[*It]){
                    if(mmaxWord[*It] < mmaxWord[h] + 1){
                        int tmp = mmaxWord[*It];

                        mmaxWord[*It] = mmaxWord[h] + 1;
                        flag[*It] = true;
                        tmpWordPre[*It] = h;

                        if((wordList[*It][wordList[*It].size() - 1] - 'a') == t){
                            if (tmp_max < mmaxWord[*It]){
                                tmp_max = mmaxWord[*It];
                                tmp_x = *It;
                                for (int i = 0; i < wordNumber; i++)
                                    maxWordPre[i] = tmpWordPre[i];
                            }
                        }
                        
                        maxWordHeadAndTailDfs(1, *It, 1, t, 0);

                        mmaxWord[*It] = tmp;
                        flag[*It] = false;
                        tmpWordPre[*It] = -1;
                    }
                }
            }
        }
        else {
            vector<int>::iterator It;
            for (It = Edge[anti][h].begin(); It != Edge[anti][h].end(); It++){
                if(!flag[*It]){
                    if(mmaxWord[*It] < mmaxWord[h] + 1){
                        int tmp = mmaxWord[*It];

                        mmaxWord[*It] = mmaxWord[h] + 1;
                        flag[*It] = true;
                        tmpWordPre[*It] = h;
                        
                        maxWordHeadAndTailDfs(1, *It, 0, 0, 0);

                        mmaxWord[*It] = tmp;
                        flag[*It] = false;
                        tmpWordPre[*It] = -1;
                    }
                }
            }
            if (tmp_max < mmaxWord[h]){
                tmp_max = mmaxWord[h];
                tmp_x = h;
                for (int i = 0; i < wordNumber; i++)
                    maxWordPre[i] = tmpWordPre[i];
            }
        }
    }
    else {
           vector<int>::iterator It;
           for (It = Edge[anti][t].begin(); It != Edge[anti][t].end(); It++){
               if(!flag[*It]){
                   if(mmaxWord[*It] < mmaxWord[t] + 1){
                       int tmp = mmaxWord[*It];

                       mmaxWord[*It] = mmaxWord[t] + 1;
                       flag[*It] = true;
                       tmpWordPre[*It] = t;
                       
                       maxWordHeadAndTailDfs(0, 0, 1, *It, 1);

                       mmaxWord[*It] = tmp;
                       flag[*It] = false;
                       tmpWordPre[*It] = -1;
                   }
               }
           }
           if (tmp_max < mmaxWord[t]){
               tmp_max = mmaxWord[t];
               tmp_x = t;
               for (int i = 0; i < wordNumber; i++)
                   maxWordPre[i] = tmpWordPre[i];
           }
    }
}

void max_Word_Length::wordLength(int n)
{
    
}

#endif