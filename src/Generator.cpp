#include "Generator.h"

void Generator::generateCalendar(HtmlWriter& writer)
{
	writer.specialTag(TagType::DOCTYPE);
    
    // Start of html block.
	writer.writeTag(TagType::HTML, OPEN_TAG, AttributeList());

    // Start of head block.
	writer.writeTag(TagType::HEAD, OPEN_TAG, AttributeList());

    // End of head block.
	writer.writeTag(TagType::HEAD, CLOSE_TAG, AttributeList());

    // Start of body block.
	writer.writeTag(TagType::BODY, OPEN_TAG, AttributeList());  

    for (int i = 0; i < NUM_MONTHS; i++)
    {
        generateMonth(writer, m_months[i], i * 5, 5 + (i * 5));
    }

    // End of the body block.
	writer.writeTag(TagType::BODY, CLOSE_TAG, AttributeList());

    // End of the html block.
	writer.writeTag(TagType::HTML, CLOSE_TAG, AttributeList());
}

void Generator::generateMonth(HtmlWriter& writer, 
                        const std::string& monthName,
                        const unsigned int wkStart,
                        const unsigned int wkEnd)
{
    AttributeList tableAttributes;
	tableAttributes.addAttribute(R"(border="1")");
	tableAttributes.addAttribute(R"(cellspacing="0")");
	tableAttributes.addAttribute(R"(cellpadding="4px")");
	tableAttributes.addAttribute(R"(width="200")");

    AttributeList titleRowAttributes;
    titleRowAttributes.addAttribute(R"(style="background-color: #ccffcc")");
    titleRowAttributes.addAttribute(R"(colspan="8")");

    AttributeList header2Attributes;
    header2Attributes.addAttribute(R"(style="padding: 0; margin: 0;")");

    AttributeList wkColAttributes;
    wkColAttributes.addAttribute(R"(style="background-color: #e6e6e6; font-size: 16px; font-weight: normal;")");

    AttributeList wkDayColHeaderAttributes;
    wkDayColHeaderAttributes.addAttribute(R"(style="background-color: #e6e6e6; font-size: 20px; font-weight: normal;")");

    AttributeList satColAttributes;
    satColAttributes.addAttribute(R"(style="background-color: #ffffcc; font-size: 20px;")");

    AttributeList sunColAttributes;
    sunColAttributes.addAttribute(R"(style="background-color: #ffcc99; font-size: 20px;")");

    AttributeList wkDayColAttributes;
    wkDayColAttributes.addAttribute(R"(style="font-size: 20px; font-weight: normal;")");

    // Start of table block.
	writer.writeTag(TagType::TABLE, OPEN_TAG, tableAttributes);

    // Title row.
    writer.writeTag(TagType::TR, OPEN_TAG);
    writer.writeTag(TagType::TH, OPEN_TAG, titleRowAttributes);
    writer.writeTag(TagType::H2, OPEN_TAG, header2Attributes);
    writer.writeData(monthName);
    writer.writeTag(TagType::H2, CLOSE_TAG);
    writer.writeTag(TagType::TH, CLOSE_TAG);
    writer.writeTag(TagType::TR, CLOSE_TAG);

    // Column description row.
    writer.writeTag(TagType::TR, OPEN_TAG);

    writer.writeTag(TagType::TH, OPEN_TAG, wkColAttributes);
    writer.writeData("Wk");
    writer.writeTag(TagType::TH, CLOSE_TAG);
    
    // Generate weekday column headers.
    std::string wkDays[7] = { "Mo", "Tu", "We", "Th", "Fr"};
    for (int i = 0; i < 5; i++) 
    {
        writer.writeTag(TagType::TH, OPEN_TAG, wkDayColHeaderAttributes);
        writer.writeData(wkDays[i]);
        writer.writeTag(TagType::TH, CLOSE_TAG);
    } 
    
    // Generate weekend column headers.
    writer.writeTag(TagType::TH, OPEN_TAG, satColAttributes);
    writer.writeData("Sa");
    writer.writeTag(TagType::TH, CLOSE_TAG);
    writer.writeTag(TagType::TH, OPEN_TAG, sunColAttributes);
    writer.writeData("Su");
    writer.writeTag(TagType::TH, CLOSE_TAG);

    // End of title row.
    writer.writeTag(TagType::TR, CLOSE_TAG);

    // Start of calendar rows.
    for (int i = wkStart; i <= wkEnd; i++)
    {
        writer.writeTag(TagType::TR, OPEN_TAG);

        // Week number column.
        writer.writeTag(TagType::TH, OPEN_TAG, wkColAttributes);
        writer.writeData(std::to_string(i));
        writer.writeTag(TagType::TH, CLOSE_TAG);

        // Week day columns.
        for (int j = 0; j < 5; j++)
        {
            writer.writeTag(TagType::TH, OPEN_TAG, wkDayColAttributes);
            writer.writeData("0");
            writer.writeTag(TagType::TH, CLOSE_TAG);
        }
        
        // Saturday column.
        writer.writeTag(TagType::TH, OPEN_TAG, satColAttributes);
        writer.writeData("0");
        writer.writeTag(TagType::TH, CLOSE_TAG);

        // Sunday column.
        writer.writeTag(TagType::TH, OPEN_TAG, sunColAttributes);
        writer.writeData("0");
        writer.writeTag(TagType::TH, CLOSE_TAG);

        writer.writeTag(TagType::TR, CLOSE_TAG);
    }

    // End of table block.
	writer.writeTag(TagType::TABLE, CLOSE_TAG, AttributeList());
}