#include "ini_parser.h"
#include <cstring>
#include <fstream>
#include <vector>


namespace qh
{
    template<class _StringVector,class Stringtype,class _DelimType>
        inline void StringSplit(const Stringtype& str,const _DelimType& delims,
                unsigned int maxSplits,_StringVector& ret)
        {
            unsigned int numSplits = 0;
            size_t start,pos;
            start = 0;
            do
            {
                pos = str.find(delims,start);
                if(pos == start)
                {
                    start = pos+delims.size();
                }
                else if(pos == Stringtype::npos||(maxSplits&&numSplits+1==maxSplits))
                {
                    ret.push_back(Stringtype());
                    *(ret.rbegin()) = Stringtype(str.data()+start,str.size()-start);
                    break;
                }
                else
                {
                    ret.push_back(Stringtype());
                    *(ret.rbegin()) = Stringtype(str.data()+start,pos-start);
                    start  = pos+delims.size();
                }
                ++numSplits;
            }
            while(pos!=Stringtype::npos);
        }
    INIParser::INIParser(){}
    
    INIParser::~INIParser(){}

    bool INIParser::Parse(const std::string& file_path)
    {
        std::ifstream file(file_path.c_str());
        if(!file)
            return false;
        file.seekg(0,std::ios::end);
        size_t len = file.tellg();
        if(len<0)
            return false;
        char *buffer = new char [len+1];
        if(0 == buffer)
            return false;
        file.seekg(0,std::ios::beg);
        file.read(buffer,len);
        buffer[len = file.gcount()] = 0;
        Parse(buffer,len);
        delete[] buffer;
        return true;
    }

    bool INIParser::Parse(const char *ini_data,size_t ini_data_len,
            const std::string& line_seperator,const std::string& key_value_seperator)
    {
        std::vector<std::string> subvec;
        StringSplit(std::string(ini_data),line_seperator,ini_data_len,subvec);
        size_t i = 0;
        std::string section = "default";
        for(;i<subvec.size();i++)
        {
            std::string subline = subvec[i];
            size_t pos = subline.find(key_value_seperator);
            if(pos == std::string::npos)
            {
                section = subline.substr(subline.find('[')+1,subline.find(']')-1);
                continue;
            }
            std::string key = subline.substr(0,pos);
            std::string value = subline.substr(pos+1);
            sectionmap[section][key] = value;
        }
        subvec.clear();
        return true;
    }

    const std::string& INIParser::Get(const std::string& key,bool *found)
    {
        std::string section = "default";
        return Get(section,key,found);
    }

    const std::string& INIParser::Get(const std::string& section,
            const std::string& key,bool *found)
    {
        if(key.empty())
            return key;
        SectionMap::iterator it;
        it = sectionmap.find(section);
        if(found != NULL)
            *found = false;
        if(it == sectionmap.end())
            return "";
        KeyMap::iterator keyit;
        keyit = it->second.find(key);
        if(keyit == it->second.end())
            return "";
        if(found != NULL)
            *found = true;
        return keyit->second;
    }

}
