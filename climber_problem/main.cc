/*************************************************************************
    > File Name: main.cc
    > Author: Chongge
    > IPLab705  
    > Created Time: Wed 13 May 2015 05:25:11 PM CST
    > Description: 
 ************************************************************************/
#include <stdio.h>
#include <assert.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstring>
using namespace std;

#define H_ARRAYSIZE(a) \
    ((sizeof(a) / sizeof(*(a))) / \
    static_cast<size_t>(!(sizeof(a) % sizeof(*(a)))))

int walkspace(const vector<vector<int> >&);

int resolve(const char* input)
{
    if(input==NULL)
        return 0;
    vector<vector<int> > mons;
    //int len = strlen(input);
    int i=0;const char *p = input;
    int temp = 0;
    while(p[i]!='\n')
    {
        temp = temp*10+p[i]-'0';
        i++;
    }
    int num = temp;
    i++;
    vector<int> vec;
    temp = 0;
    while(p[i]!='\0')
    {
        if(p[i]=='\n')
        {
            vec.push_back(temp);
            mons.push_back(vec);
            vec.clear();
            temp = 0;
        }
        else if(p[i]==',')
        {
            vec.push_back(temp);
            temp = 0;
        }
        else
        {
            temp += temp*10+p[i]-'0';
        }
        i++;
    }
    if(num!=mons.size())
        return 0;
    return walkspace(mons);
}

int walkspace(const vector<vector<int> >&mon)
{
    if(mon.size()<=0)
        return 0;
    int total = 0;
    int cur = 0;
    int high = 0;
    int dis = 0;
    int len = mon.size();
    for(int i=0;i<len;i++)
    {
        if(mon[i][0]>cur+dis)
        {
            total += high+mon[i][0]-cur+mon[i][2];
        }
        else
        {
            total += mon[i][0]-cur+abs(mon[i][2]-high);//next mount maybe low
        }
        cur = mon[i][0];
        high = mon[i][2];
        dis = mon[i][1]-mon[i][0];
    }
    total += mon[len-1][1]-mon[len-1][0]+high;
    return total;
}

int main(int argc, char* argv[]) 
{
    const char* input[] = {
        "3\n1,3,2\n2,4,4\n6,7,5\n", //The giving example
        "1\n1,2,1\n",
        "2\n1,2,1\n2,3,2\n",
        "3\n1,2,1\n2,3,2\n3,6,1\n",
        "4\n1,2,1\n2,3,2\n3,6,1\n5,8,2\n",
        "5\n1,2,1\n2,3,2\n3,6,1\n5,8,2\n7,9,1\n",
        "1\n0,1,1\n",
        "2\n0,1,1\n2,4,3\n",
        "3\n0,1,1\n2,4,3\n3,5,1\n",
        "4\n0,1,1\n2,4,3\n3,5,1\n5,6,1\n",
        "5\n0,1,1\n2,4,3\n3,5,1\n5,6,1\n6,8,3\n",
        //TODO please add more test case here
        };//must end with "\n";
    int expectedSteps[] = {25, 4, 7, 10, 14, 15, 3, 12, 13, 14, 20};
    for (size_t i = 0; i < H_ARRAYSIZE(input); ++i)
    {
        assert(resolve(input[i]) == expectedSteps[i]);
    }
    return 0;
}
