#ifndef HTML_FILE_H
#define HTML_FILE_H

#include <string>
#include <fstream>

#include "HtmlAttribute.h"

#define OPEN_TAG    1u
#define CLOSE_TAG   2u

/**
 * List of HTML tags the HtmlWriter class supports.
 */
typedef enum
{
    // Special tag - must use the HtmlWriter::specialTag function to write this.
    DOCTYPE,

    HTML,
    HEAD,
    BODY,
    TABLE,
    TR,
    TH,
    H1,
    H2
} TagType;

/**
 * This class allows a user to write static HTML code to a HTML file. The output
 * file is set in the constructor. The writeTag function can write either an
 * open tag or a close tag. writeTag must be called twice to make a full tag.
 * The writeData function writes a string to the HTML file and should be called
 * between the first writeTag call and the second writeTag call to wrap the 
 * written data inside the specified tag. Special single tags, such as the 
 * doctype tag, are written using the specialTag function.
 */
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
    /**
     * File path of the output HTML file.
     */
    std::string m_filepath;

    /**
     * HTML file output stream (hfos).
     */
    std::ofstream m_hfos;

    // Counter to keep track of the number of times a tag has been openeing
    // without being closed. Each open tag that has not been closed corresponds
    // to one indentation level.
    unsigned int m_openTags;

    std::string createOpenTag(const std::string& tag,
                        const AttributeList& attributes) const;

    void writeString(const std::string& s);
};

#endif  // HTML_FILE_H