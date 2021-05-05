#ifndef HTML_ATTRIBUTE_H
#define HTML_ATTRIBUTE_H

#include <string>
#include <vector>
#include <ostream>

typedef enum 
{
    HREF,
    STYLE,
    BORDER,
    CALLSPACING,
    CELLPADDING,
    WIDTH,
    FONT_SIZE,
    FONT_WEIGHT
} AttributeType;

typedef struct AttributeStruct
{
    AttributeType  type;
    std::string    data;

    AttributeStruct(const AttributeType type, const std::string& data)
        : type(type), data(data)
    {} 
} Attribute;

class AttributeList
{
public:
    AttributeList();
    AttributeList(const std::string& attribute);

    void addAttribute(const std::string& attribute);
    size_t nAttributes() const;

    std::vector<std::string>::const_iterator begin() const
    {
        return m_attributes.begin();
    }
    
    std::vector<std::string>::const_iterator end() const
    {
        return m_attributes.end();
    }

private:
    std::vector<std::string> m_attributes;
};

#endif  // HTML_ATTRIBUTE_H