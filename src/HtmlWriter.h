#ifndef HTML_FILE_H
#define HTML_FILE_H

#include <string>
#include <fstream>
#include <stack>

typedef enum
{
    DOCTYPE,
    HTML,
    HEAD,
    BODY
} TagType;

typedef enum 
{
    HREF
} AttributeType;

typedef struct AttributeStruct
{
    AttributeType  type;
    std::string    data;

    AttributeStruct(const AttributeType type, const std::string& data)
        : type(type), data(data)
    {

    } 
} Attribute;

class HtmlWriter     
{
public:
    HtmlWriter(const std::string& filepath);
    ~HtmlWriter();

    void singleTag(const TagType tagType);
    void openTag(const TagType tagType);
    void closeTag(const TagType tagType);

private:
    std::string m_filepath;
    std::ofstream m_hfos;

    unsigned int m_openTags;

    void writeString(const std::string& s);
};

#endif  // HTML_FILE_H