#include <stdio.h>
#include <stdlib.h>
#include <cassert>
#include <cstring>
#include "qh_string.h"


int main(int argc, char* argv[])
{
    //TODO ��������ӵ�Ԫ���ԣ�Խ��Խ�ã�����·��������ԽȫԽ��
    //TODO ��Ԫ����д����ο�INIParser�Ǹ���Ŀ����Ҫдһ��printf��Ҫ��assert���ж����жϡ�

    qh::string nullString;
    assert(nullString.size()==0&&nullString.c_str()==NULL);

    const char *test = "1234";
    qh::string charString(test);
    assert(charString.size()==4&&!strcmp(charString.c_str(),test));

    nullString = charString;
    assert(nullString == charString);

    qh::string copyString(charString);
    assert(copyString == charString);

    assert(!strcmp(copyString[2],"34"));

#ifdef WIN32
    system("pause");
#endif

	return 0;
}

