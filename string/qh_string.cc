#include "qh_string.h"

#include <string.h>
#include <stdexcept>

namespace qh
{
    // TODO 将在这里写实现代码

    string::string()
        : data_(NULL), len_(0)
    {
    }

    string::string( const char* s )
    {
        len_ = strlen(s);
        data_ = new char[len_+1];
        strcpy(data_,s);
    }

    string::string( const char* s, size_t len )
    {
        len_ = len;
        data_ = new char[len+1];
        strncpy(data_,s,len);
        data_[len] = '\0';
    }

    string::string( const string& rhs )
    {
        len_ = rhs.len_;
        data_ = new char[len_+1];
        strcpy(data_,rhs.data_);
    }


    inline bool operator==(const string &lhs,const string &rhs)
    {
        if(lhs.c_str()==NULL||rhs.c_str()==NULL)
            return (lhs.size()==rhs.size());
        return (!strcmp(lhs.c_str(),rhs.c_str())&&(lhs.size()==rhs.size()));
    }
    
    inline bool operator!=(const string &lhs,const string &rhs)
    {
        return !(lhs == rhs);
    }

    string& string::operator=( const string& rhs )
    {
        if(*this != rhs)
        {
            delete[] data_;
            data_ = new char[rhs.len_+1];
            strcpy(data_,rhs.data_);
            len_ = rhs.len_;
        }
        return *this;
    }

    string::~string()
    {
        if(!data_)
        {
            delete[] data_;
            data_ = NULL;
            len_ = 0;
        }
    }

    size_t string::size() const
    {
        return len_;
    }

    const char* string::data() const
    {
        char *temp = new char[len_];
        strncpy(temp,data_,len_);
        return temp;
    }

    const char* string::c_str() const
    {
        return data_;
    }

    char* string::operator[]( size_t index )
    {
        if(index<0||index>len_-1)
            throw std::out_of_range("Out of range");
        return &data_[index];
    }
}
