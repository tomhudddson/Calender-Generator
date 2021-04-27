#ifndef HTML_FILE_H
#define HTML_FILE_H

#include <string>

class HtmlWriter     
{
public:
    HtmlWriter(const std::string& filepath);
    ~HtmlWriter();

private:
    std::string m_filepath;
};

#endif  // HTML_FILE_H