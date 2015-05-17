#include <stdio.h>
#include <stdlib.h>
#include <cassert>
#include <cstring>
#include "qh_string.h"


int main(int argc, char* argv[])
{
    //TODO 在这里添加单元测试，越多越好，代码路径覆盖率越全越好
    //TODO 单元测试写法请参考INIParser那个项目，不要写一堆printf，要用assert进行断言判断。

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

