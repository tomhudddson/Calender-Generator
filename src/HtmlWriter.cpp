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

void HtmlWriter::writeTag(const TagType tagType, const unsigned int flag)
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

    switch (tagType)
    {
    case TagType::HTML:
        (flag == OPEN_TAG) ? writeString("<html>") : writeString("</html>");
        break;

    case TagType::HEAD:
        (flag == OPEN_TAG) ? writeString("<head>") : writeString("</head>");
        break;
    
    case TagType::BODY:
        (flag == OPEN_TAG) ? writeString("<body>") : writeString("</body>");
        break;

    default:
        // No valid open tag found so return here to prevent the function
        // reaching its end and opening or closing a valid tag. 
        std::cout << "Invalid tag given!" << std::endl;
        return;
    }

    (flag == OPEN_TAG) ? m_openTags++ : m_openTags--;
}

void HtmlWriter::specialTag(const TagType tagType)
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

void HtmlWriter::writeString(const std::string& s)
{
    m_hfos.open(m_filepath, std::ios::app);
    m_hfos << std::string(m_openTags * TAB_SIZE, ' ') << s << "\n";
    m_hfos.close();
}