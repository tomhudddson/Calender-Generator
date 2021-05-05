#include "HtmlWriter.h"

#include <iostream>
#include <sstream>

/**
 * Number of spaces in a tab.
 */
#define TAB_SIZE  4

/**
 * This constructor initialises a HtmlWriter instance with a filepath. 
 * 
 * @param     filepath  The filepath of the output HTML file. All generated
 *       HTML code will be written to this file. If it already exists, its 
 *       content will be overwritten. If it does not exist, it will be created.
 */
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

/**
 * Function overload to allow the user to write a HTML tag without any 
 * attributes.
 * 
 * @param     tagType  The type of HTML tag to write.
 * 
 * @param     flag  The tag flag. For an opening tag pass OPEN_TAG. For a 
 *       closing tag, pass CLOSE_TAG. There are no other flags other than these
 *       two.
 */
void HtmlWriter::writeTag(const TagType tagType, const unsigned int flag)
{
    writeTag(tagType, flag, AttributeList());
}

/**
 * This function writes a HTML tag into the file specified in the constructor.
 * The open and close tags must be written separately, therefore, to write a 
 * full tag - <tag>data</tag> This function must be called twice, with a call to
 * writeData inbetween. This function also formats the code in human-readable
 * format with correct indentations.
 * 
 * This function does not support inline tags in the form 
 * <tag attribute="foo" />.
 * 
 * @param     tagType  Type of the HTML tag.
 * 
 * @param     flag  The flag specifying whether the tag is an opening or closing
 *       tag. For an opening tag pass OPEN_TAG. For a closing tag pass 
 *       CLOSE_TAG.
 * 
 * @param     attributeList  Reference to an AttributeList instance containing
 *       the attributes for the given tag. If there are no attribtues, simply
 *       pass an AttributeList with no attribtues added. Note, this parameter
 *       is ignored if the flag is CLOSE_TAG.
 */
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

    // This tag is a closing tag so remove an indentation level before writing
    // it.
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

/**
 * This function writes a special tag to the output HTML file. Special tags 
 * are HTML tags that do not conform to the standard <open_tag>data</close_tag>
 * format.
 * 
 * @param     tagType  The type of HTML tag, must be a special tag.
 */
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

/**
 * Creates a string containing a HTML open tag along with its attributes. The 
 * tag is in the form <tag attribute_1="a1" attribute_2="a2" ... >.
 * 
 * @param     tag  The string representation of the tag. Must be valid HTML and 
 *       should not include the angle brackets, only the name of the tag.
 * 
 * @param     attributes  Reference to an AttributeList instance containing
 *       the attributes to add to this open tag.
 * 
 * @return
 * 
 *      - The valid HTML open tag string.
 */
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

    // Add each attribute to the tag.
    for (const auto& a : attributes)
    {
        ss << a << " ";
    }

    ss << ">";

    return ss.str();
}

/**
 * Writes a string to the output file with the correct indentation. 
 */
void HtmlWriter::writeString(const std::string& s)
{   
    // Open output file in append mode - no need to worry about if it has been
    // cleared as it gets cleared in the constructor.
    m_hfos.open(m_filepath, std::ios::app);

    // Write the string with correct indentation.
    m_hfos << std::string(m_openTags * TAB_SIZE, ' ') << s << "\n";
    
    m_hfos.close();
}