#include "HtmlAttribute.h"

AttributeList::AttributeList()
    : m_attributes()
{

}

void AttributeList::addAttribute(const std::string& attribute)
{
    m_attributes.push_back(attribute);
}