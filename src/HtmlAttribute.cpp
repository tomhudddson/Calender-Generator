#include "HtmlAttribute.h"

AttributeList::AttributeList()
    : m_attributes()
{

}

AttributeList::AttributeList(const std::string& attribute)
    : m_attributes()
{
    addAttribute(attribute);
}

void AttributeList::addAttribute(const std::string& attribute)
{
    m_attributes.push_back(attribute);
}

size_t AttributeList::nAttributes() const
{
    return m_attributes.size();
}