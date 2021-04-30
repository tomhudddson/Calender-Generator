#ifndef HTML_FILE_H
#define HTML_FILE_H

#include <string>
#include <fstream>

#include "HtmlAttribute.h"

#define OPEN_TAG    1u
#define CLOSE_TAG   2u

typedef enum
{
    DOCTYPE,
    HTML,
    HEAD,
    BODY,
    TABLE,
    TR,
    TH,
    H2
} TagType;


class HtmlWriter     
{
public:
    HtmlWriter(const std::string& filepath);
    ~HtmlWriter();

    void writeTag(const TagType type, const unsigned int flag);

    void writeTag(const TagType type, 
                const unsigned int flag,
                const AttributeList& attributeList);
    
    void specialTag(const TagType tagType); 

    inline void writeData(const std::string& data)
    {
    writeString(data);
    }

private:
    std::string m_filepath;
    std::ofstream m_hfos;

    unsigned int m_openTags;

    

    std::string createOpenTag(const std::string& tag,
                        const AttributeList& attributes) const;

    void writeString(const std::string& s);
};

#endif  // HTML_FILE_H