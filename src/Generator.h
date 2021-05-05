#ifndef GENERATOR_H
#define GENERATOR_H

#include "HtmlWriter.h"

#define NUM_MONTHS  12

class Generator
{
public:
    Generator();

    void generateCalendar(HtmlWriter& writer, const unsigned int year);

private:
    unsigned int m_wkNumber;

    const std::string m_months[NUM_MONTHS] = {
        "January",
        "February",
        "March",
        "April",
        "May",
        "June",
        "July",
        "August",
        "September",
        "October",
        "November",
        "December"
    };

    const int m_daysInMonths[NUM_MONTHS] = {
        31,  // January
        28,  // Feburary - 29 on a leap year
        31,  // March,
        30,  // April,
        31,  // May,
        30,  // June,
        31,  // July,
        31,  // August
        30,  // September
        31,  // October
        30,  // November,
        31   // December  
    };

    void generateYear(HtmlWriter& writer, const unsigned int year);

    void generateMonth(HtmlWriter& writer, 
                    const unsigned int year,
                    const unsigned int monthIndex);

    void generateTitleRow(HtmlWriter& writer, const unsigned int month);
    
    void generateColDescriptionRow(HtmlWriter& writer,
                                AttributeList& wkColAttributes,
                                AttributeList& satColAttributes,
                                AttributeList& sunColAttributes);                    

    unsigned int getNumberOfDays(const unsigned int year,
                            const unsigned int monthIndex);

    unsigned int getDayOfWeek(const unsigned int day,
                            const unsigned int month,
                            unsigned int year);
};

#endif  // GENERATOR_H