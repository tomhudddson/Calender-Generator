#include "HtmlWriter.h"

#include <iostream>
#include <iomanip>

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
            writeString("<html>");
            break;

        case TagType::HEAD:
            writeString("<head>");
            break;

        case TagType::BODY:
            writeString("<body>");
            break;

        default:
            // No valid open tag found so return here to prevent the function
            // reaching its end and opening a valid tag. 
            std::cout << "Invalid opening tag given!" << std::endl;
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
            writeString("</html>");
            break;

        case TagType::HEAD:
            writeString("</head>");
            break;

        case TagType::BODY:
            writeString("</body>");
            break;

        default:
            // No valid open tag found so return here to prevent the function
            // reaching its end and opening a valid tag. 
            std::cout << "Invalid closing tag given!" << std::endl;
            return;
    }

    m_openTags--;
}

void HtmlWriter::writeString(const std::string& s)
{
    m_hfos.open(m_filepath, std::ios::app);
    m_hfos << std::string(m_openTags * TAB_SIZE, ' ') << s << "\n";
    m_hfos.close();
}