#include "HtmlWriter.h"

#include <iostream>
#include <sstream>

#define TAB_SIZE  4

HtmlWriter::HtmlWriter(const std::string& filepath)
    : m_filepath(filepath),
    m_hfos(filepath),
    m_openTags(0)
{
    // Open the output file to clear its contents. If it doesn't exist, it will
    // be created.
    m_hfos.open(filepath, std::ios::out | std::ios::trunc);
    m_hfos.close();
}

HtmlWriter::~HtmlWriter()
{

}

void HtmlWriter::writeTag(const TagType tagType, const unsigned int flag)
{
    writeTag(tagType, flag, AttributeList());
}

void HtmlWriter::writeTag(const TagType tagType,
                        const unsigned int flag,
                        const AttributeList& attributeList)
{
    if (flag != OPEN_TAG && flag != CLOSE_TAG)
    {
        std::cout << "Incorrect tag flag! Use either OPEN_TAG or CLOSE_TAG" 
                  << std::endl;
        return;
    }

    if (flag == CLOSE_TAG && m_openTags <= 0)
    {
        std::cout << "No open tags to close" << std::endl;
        return;
    }

    if (flag == CLOSE_TAG) { m_openTags--; }

    switch (tagType)
    {
    case TagType::HTML:
        (flag == OPEN_TAG) ? writeString(createOpenTag("html", attributeList)) : writeString("</html>");
        break;

    case TagType::HEAD:
        (flag == OPEN_TAG) ? writeString(createOpenTag("head", attributeList)) : writeString("</head>");
        break;
    
    case TagType::BODY:
        (flag == OPEN_TAG) ? writeString(createOpenTag("body", attributeList)) : writeString("</body>");
        break;
    
    case TagType::TABLE:
        (flag == OPEN_TAG) ? writeString(createOpenTag("table", attributeList)) : writeString("</table>");
        break;

    case TagType::TR:
        (flag == OPEN_TAG) ? writeString(createOpenTag("tr", attributeList)) : writeString("</tr>");
        break;

    case TagType::TH:
        (flag == OPEN_TAG) ? writeString(createOpenTag("th", attributeList)) : writeString("</th>");
        break;

    case TagType::H1:
        (flag == OPEN_TAG) ? writeString(createOpenTag("h1", attributeList)) : writeString("</h1>");
        break;
        
    case TagType::H2:
        (flag == OPEN_TAG) ? writeString(createOpenTag("h2", attributeList)) : writeString("</h2>");
        break;

    default:
        // No valid open tag found so return here to prevent the function
        // reaching its end and opening or closing a valid tag. 
        std::cout << "Invalid tag given!" << std::endl;
        return;
    }

    if (flag == OPEN_TAG) { m_openTags++; }
}

void HtmlWriter::specialTag(const TagType tagType)
{
    switch (tagType)
    {
        case TagType::DOCTYPE:
            writeString("<!DOCTYPE html>");
            break;

        default:
            std::cout << "Unknown special TagType." << std::endl;
            break;
    }
}

std::string HtmlWriter::createOpenTag(const std::string& tag,
                                const AttributeList& attributes) const
{
    std::stringstream ss;   

    if (attributes.nAttributes() == 0) 
    {
        // No attributes in this function so simply return the tag.
        ss << "<" << tag << ">";
        return ss.str();
    }

    ss << "<" << tag << " ";

    for (const auto& a : attributes)
    {
        ss << a << " ";
    }

    ss << ">";

    return ss.str();
}

void HtmlWriter::writeString(const std::string& s)
{
    m_hfos.open(m_filepath, std::ios::app);
    m_hfos << std::string(m_openTags * TAB_SIZE, ' ') << s << "\n";
    m_hfos.close();
}