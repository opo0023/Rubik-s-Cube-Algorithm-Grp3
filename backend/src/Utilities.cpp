#include "Utilities.h"
#include <sstream>

std::string join(const std::vector<std::string>& v, const std::string& sep){
    std::ostringstream oss;
    for(size_t i=0;i<v.size();++i){
        if(i) oss << sep;
        oss << v[i];
    }
    return oss.str();
}
