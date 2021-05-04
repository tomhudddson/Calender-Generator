#include "Generator.h"

#include <iostream>

/**
 * Minimum supported date is October 1582.
 */
#define MIN_YEAR   1582
#define MIN_MONTH  9        // October (January = 0) 

/**
 * Generate a yearly calendar for a given year, its preceding year, and its 
 * following year. The output is written to a static HTML page.
 * 
 * @param     writer  Reference to the HtmlWriter instance which will be used
 *       to generate the static HTML page.
 * 
 * @param     year  The year to base the generation around. The given year is 
 *       generated, its preceding year is also generated and the following year
 *       is generated. The minimum supported year is October 1582 so no year
 *       before that can be given to this function. If exactly 1582 is given, 
 *       or 1583 is given, then only October, November and December will be
 *       generated.
 */
void Generator::generateCalendar(HtmlWriter& writer, 
                            const unsigned int year)
{
    if (year < MIN_YEAR)
    {
        std::cout << "Minimum supported year is 1582. Please run the program "
                    "again but use a year greater than or equal to 1582." << 
                    std::endl;
        return;
    }

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

    // If 1582 is the given year, then there is no need to attempt to generate
    // year - 1 (1581). Therefore, only generate the given year (1582) and the
    // given year + 1 (1583). If the given year is greater 1583, then generate
    // all three years.
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

    std::cout << "Calendar generated successfully!" << std::endl;
}

/**
 * This function generates the HTML for one year. 
 */
void Generator::generateYear(HtmlWriter& writer, const unsigned int year)
{
    writer.writeTag(TagType::TH, OPEN_TAG);

    writer.writeTag(TagType::H1, OPEN_TAG);
    writer.writeData(std::to_string(year));
    writer.writeTag(TagType::H1, CLOSE_TAG);

    unsigned int currentWk = 1;

    int i = (year == 1582) ? 9 : 0;

    for (i; i < NUM_MONTHS; i++)
    {
        generateMonth(writer, year, i, currentWk, currentWk + 5);
        currentWk += 6;
    }

    writer.writeTag(TagType::TH, CLOSE_TAG);
}

/**
 * This function generates the HTML for month consists of a table with 8 rows 
 * and 8 columns in the following layout:
 *   
 *           Title
 *   Wk Mo Tu We Th Fr Sa Su
 *   1  -  -  -  -  -  -  -   
 *   2  -  -  -  -  -  -  - 
 *   3  -  -  -  -  -  -  - 
 *   4  -  -  -  -  -  -  - 
 *   5  -  -  -  -  -  -  - 
 *   6  -  -  -  -  -  -  - 
 * 
 * The first row is known as the title row. The second row is known as the 
 * column description row. The '-' contain the actual dates and these are known
 * as calendar cells.
 * 
 * @param     writer  Reference to the HtmlWriter instance that is used to
 *       generate the HTML.
 * 
 * @param     year  The year the month to generate is contained within.
 * 
 * @param     month  The month to generate. The months start at 0 so January = 0
 *       and December = 11.
 * 
 * @param     wkStart  The number of weeks into the year the month begins.
 * 
 * @param     wkEnd  The number of weeks into the year the month ends.
 */
void Generator::generateMonth(HtmlWriter& writer,
                        const unsigned int year,
                        const unsigned int month,
                        const unsigned int wkStart,
                        const unsigned int wkEnd)
{
    // HTML Attributes for the table.
    AttributeList tableAttributes;
    tableAttributes.addAttribute(R"(border="1")");
    tableAttributes.addAttribute(R"(cellspacing="0")");
    tableAttributes.addAttribute(R"(cellpadding="4px")");
    tableAttributes.addAttribute(R"(width="200")");

    // HTML attributes for the week number column, including the column header.
    AttributeList wkColAttributes;
    wkColAttributes.addAttribute(R"(style="background-color: #e6e6e6; font-size: 16px; font-weight: normal;")");

    // HTML attributes for the saturday column, including the column header 
    // cell.
    AttributeList satColAttributes;
    satColAttributes.addAttribute(R"(style="background-color: #ffffcc; font-size: 20px;")");

    // Html attribute for the sunday column, including the column header.
    AttributeList sunColAttributes;
    sunColAttributes.addAttribute(R"(style="background-color: #ffcc99; font-size: 20px;")");

    // HTML attribute for the week day cells.
    AttributeList wkDayColAttributes;
    wkDayColAttributes.addAttribute(R"(style="font-size: 20px; font-weight: normal;")");

    /**
     * Start of table block.
     */

    writer.writeTag(TagType::TABLE, OPEN_TAG, tableAttributes);


    generateTitleRow(writer, month);
    generateColDescriptionRow(writer, 
                        wkColAttributes, 
                        satColAttributes,
                        sunColAttributes);

    // Total number of days in the given month. Counting starts from 1.
    const unsigned int nDays = getNumberOfDays(year, month);

    // Used to keep track of the current day of the month when calculating days
    // of the week. First day of every month is always 1.
    unsigned int dayOfMonth = 1;

    // Used to calculate the day of the week using the current day of the month.
    // The month parameter requires countring from 1 so January = 1 and 
    // December = 12. This class uses January = 0 and December = 11 so we need
    // to add 1 to the month.
    unsigned int dayOfWeek = getDayOfWeek(dayOfMonth, month + 1, year);

    // Generate the calendar row by row.
    for (int i = wkStart; i <= wkEnd; i++)
    {
        // HTML table row element opening tag for each row.
        writer.writeTag(TagType::TR, OPEN_TAG);

        // Add a week number cell to this row and insert the current week 
        // number into it.
        writer.writeTag(TagType::TH, OPEN_TAG, wkColAttributes);
        writer.writeData(std::to_string(i));
        writer.writeTag(TagType::TH, CLOSE_TAG);

        // Calcaulte the days for only the week days. Days for Saturday and
        // Sunday must be calculated separately since they have different 
        // HTML attributes.
        int j = 1;
        for (j; j <= 5; j++)
        {
            // HTML opening tag for a single calendar cell.
            writer.writeTag(TagType::TH, OPEN_TAG, wkDayColAttributes);
            
            // Some of the cells at the beginning of the month may contain days
            // that belong to the previous month. Therefore, only write
            // the days of the month into a cell if the date is actually in this
            // month. Also, stop writing days into cells when the total number
            // of days in the month has been reached. 
            if (j >= dayOfWeek && dayOfMonth <= nDays)
            {
                // All overlapping cells from previous month have been dealt
                // with and the total number of days has not yet been reached,
                // so write the current day of the month into the next cell.
                writer.writeData(std::to_string(dayOfMonth));
                
                // Get the next day of the week.
                dayOfMonth++;
                dayOfWeek = getDayOfWeek(dayOfMonth, month + 1, year);
            }

            // HTML closing tag for a single calendar cell.
            writer.writeTag(TagType::TH, CLOSE_TAG);
        }
        
        // Saturday column.
        writer.writeTag(TagType::TH, OPEN_TAG, satColAttributes);
        if (j >= dayOfWeek && dayOfMonth <= nDays)
        {
            writer.writeData(std::to_string(dayOfMonth));
            dayOfMonth++;
            dayOfWeek = getDayOfWeek(dayOfMonth, month + 1, year);
        }
        writer.writeTag(TagType::TH, CLOSE_TAG);

        // Sunday column. We don't need to check if all overlapping days 
        // from the previous month have been accounted for as no month will have
        // its first day after its first week.
        writer.writeTag(TagType::TH, OPEN_TAG, sunColAttributes);
        if (dayOfMonth <= nDays)
        {
            writer.writeData(std::to_string(dayOfMonth));
            dayOfMonth++;
            dayOfWeek = getDayOfWeek(dayOfMonth, month + 1, year);
        } 
        writer.writeTag(TagType::TH, CLOSE_TAG);        

        // Closing HTML tag for a single row.
        writer.writeTag(TagType::TR, CLOSE_TAG);
    }

    writer.writeTag(TagType::TABLE, CLOSE_TAG, AttributeList());

    /**
     * End of table block.
     */
}

void Generator::generateTitleRow(HtmlWriter& writer, const unsigned int month)
{
    // HTML attributes for the month title row.
    AttributeList titleRowAttributes;
    titleRowAttributes.addAttribute(R"(style="background-color: #ccffcc")");
    titleRowAttributes.addAttribute(R"(colspan="8")");

    // The month title in the table's title row will be enclosed in a h2 tag.
    // These are the HTML attributes for that h2 tag.
    AttributeList header2Attributes;
    header2Attributes.addAttribute(R"(style="padding: 0; margin: 0;")");

    writer.writeTag(TagType::TR, OPEN_TAG);
    writer.writeTag(TagType::TH, OPEN_TAG, titleRowAttributes);
    writer.writeTag(TagType::H2, OPEN_TAG, header2Attributes);
    writer.writeData(m_months[month]);
    writer.writeTag(TagType::H2, CLOSE_TAG);
    writer.writeTag(TagType::TH, CLOSE_TAG);
    writer.writeTag(TagType::TR, CLOSE_TAG);
}

void Generator::generateColDescriptionRow(HtmlWriter& writer,
                                    AttributeList& wkColAttributes,
                                    AttributeList& satColAttributes,
                                    AttributeList& sunColAttributes)
{
   
    // HTML attributes for the week day column header cells.
    AttributeList wkDayColHeaderAttributes;
    wkDayColHeaderAttributes.addAttribute(R"(style="background-color: #e6e6e6; font-size: 20px; font-weight: normal;")");



    writer.writeTag(TagType::TR, OPEN_TAG);

    // Generate week number column header.
    writer.writeTag(TagType::TH, OPEN_TAG, wkColAttributes);
    writer.writeData("Wk");
    writer.writeTag(TagType::TH, CLOSE_TAG);
    
    // Generate weekday column headers.
    std::string wkDays[5] = { "Mo", "Tu", "We", "Th", "Fr"};
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

    writer.writeTag(TagType::TR, CLOSE_TAG);
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