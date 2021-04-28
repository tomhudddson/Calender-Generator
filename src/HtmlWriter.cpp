#include "HtmlWriter.h"

#include <iostream>

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

void HtmlWriter::singleTag(const TagType tagType)
{
    switch (tagType)
    {
        case TagType::DOCTYPE:
            writeString("<!DOCTYPE html>");
            break;

        default:
            std::cout << "Unknown single TagType." << std::endl;
            break;
    }
}

void HtmlWriter::openTag(const TagType tagType)
{
    switch (tagType)
    {
        case TagType::HTML:
            writeString("<html>\n");
            break;

        case TagType::HEAD:
            writeString("<head>\n");
            break;

        case TagType::BODY:
            writeString("<body>\n");
            break;

        default:
            // No valid open tag found so return here to prevent the function
            // reaching its end and opening a valid tag. 
            return;
    }

    m_openTags++;
}

void HtmlWriter::closeTag(const TagType tagType)
{
    if (m_openTags <= 0)
    {
        std::cout << "No open tags to close" << std::endl;
        return;
    }

    switch (tagType)
    {
        case TagType::HTML:
            writeString("</html>\n");
            break;

        case TagType::HEAD:
            writeString("</head>\n");
            break;

        case TagType::BODY:
            writeString("</body>\n");
            break;

        default:
            // No valid open tag found so return here to prevent the function
            // reaching its end and opening a valid tag. 
            return;
    }

    m_openTags--;
}

void HtmlWriter::writeString(const std::string& s)
{
    m_hfos.open(m_filepath, std::ios::app);
    m_hfos << s;
    m_hfos.close();
}