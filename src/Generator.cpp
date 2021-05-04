#include "Generator.h"

#include <iostream>

/**
 * Minimum supported date is October 1582.
 */
#define MIN_YEAR   1582
#define MIN_MONTH  10   

void Generator::generateCalendar(HtmlWriter& writer, 
                            const unsigned int year)
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

    // Start of main table block.
    writer.writeTag(TagType::TABLE, OPEN_TAG);

    int i = (year == 1582) ? year : year - 1;

    for (i; i <= (year + 1); i++)
    {
        generateYear(writer, i);
    }

    // End of main table block.
    writer.writeTag(TagType::TABLE, CLOSE_TAG);

    // End of the body block.
    writer.writeTag(TagType::BODY, CLOSE_TAG, AttributeList());

    // End of the html block.
    writer.writeTag(TagType::HTML, CLOSE_TAG, AttributeList());
}

void Generator::generateYear(HtmlWriter& writer, const unsigned int year)
{
    writer.writeTag(TagType::TH, OPEN_TAG);

    writer.writeTag(TagType::H1, OPEN_TAG);
    writer.writeData(std::to_string(year));
    writer.writeTag(TagType::H1, CLOSE_TAG);

    int i = (year == 1582) ? 9 : 0;

    for (i; i < NUM_MONTHS; i++)
    {
        generateMonth(writer, year, i, 39, 44);
    }

    writer.writeTag(TagType::TH, CLOSE_TAG);
}

void Generator::generateMonth(HtmlWriter& writer,
                        const unsigned int year,
                        const unsigned int monthIndex,
                        const unsigned int wkStart,
                        const unsigned int wkEnd)
{
    const std::string monthName = m_months[monthIndex];

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
    const unsigned int nDays = getNumberOfDays(year, monthIndex);
    unsigned int dayOfMonth = 1;
    unsigned int dayOfWeek = getDayOfWeek(dayOfMonth, monthIndex + 1, year);

    for (int i = wkStart; i <= wkEnd; i++)
    {
        writer.writeTag(TagType::TR, OPEN_TAG);

        // Week number column.
        writer.writeTag(TagType::TH, OPEN_TAG, wkColAttributes);
        writer.writeData(std::to_string(i));
        writer.writeTag(TagType::TH, CLOSE_TAG);

        // Week day columns.
        int j = 1;
        for (j; j <= 5; j++)
        {
            writer.writeTag(TagType::TH, OPEN_TAG, wkDayColAttributes);
            if (j >= dayOfWeek && dayOfMonth <= nDays)
            {
                writer.writeData(std::to_string(dayOfMonth));
                dayOfMonth++;
                dayOfWeek = getDayOfWeek(dayOfMonth, monthIndex + 1, year);
            }
            else 
            {
               // writer.writeData("");
            }
            
            writer.writeTag(TagType::TH, CLOSE_TAG);
        }
        
        // Saturday column.
        writer.writeTag(TagType::TH, OPEN_TAG, satColAttributes);
        if (j >= dayOfWeek && dayOfMonth <= nDays)
        {
            writer.writeData(std::to_string(dayOfMonth));
            dayOfMonth++;
            dayOfWeek = getDayOfWeek(dayOfMonth, monthIndex + 1, year);
        }
        else 
        {
           // writer.writeData("");
        }
        writer.writeTag(TagType::TH, CLOSE_TAG);

        // Sunday column.
        writer.writeTag(TagType::TH, OPEN_TAG, sunColAttributes);
        if (dayOfMonth <= nDays)
        {
            writer.writeData(std::to_string(dayOfMonth));
            dayOfMonth++;
            dayOfWeek = getDayOfWeek(dayOfMonth, monthIndex + 1, year);
        } 
        else 
        {
            //writer.writeData("");
        }
        writer.writeTag(TagType::TH, CLOSE_TAG);        

        writer.writeTag(TagType::TR, CLOSE_TAG);
    }

    // End of table block.
    writer.writeTag(TagType::TABLE, CLOSE_TAG, AttributeList());
}

unsigned int Generator::getNumberOfDays(const unsigned int year,
                                    const unsigned int monthIndex)
{
    if (monthIndex == 1)
    {
        // Given month is February so we must calculate whether it is a leap
        // year or not. Every year that is divisible by 4 is a leap year, except
        // years that are divisible by 100. However, every 400 years is also a
        // leap year.
        if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
            return 29;
        else 
            return 28;
    }

    // No other month is affected by leap years so simply lookup the number of
    // days.
    return m_daysInMonths[monthIndex];
}

unsigned int Generator::getDayOfWeek(const unsigned int day,
                                const unsigned int month,
                                unsigned int year)
{
    static unsigned int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
    year -= month < 3;
    return (year + year/4 - year/100 + year/400 + t[month-1] + day) % 7;
}