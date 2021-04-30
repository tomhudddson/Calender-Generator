#ifndef GENERATOR_H
#define GENERATOR_H

#include "HtmlWriter.h"

#define NUM_MONTHS  12

class Generator
{
public:

    void generateCalendar(HtmlWriter& writer);

private:
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

    void generateMonth(HtmlWriter& writer, 
                    const std::string& monthName,
                    const unsigned int wkStart,
                    const unsigned int wkEnd);
};

#endif  // GENERATOR_H