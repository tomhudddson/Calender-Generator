#include <string>

#include "HtmlWriter.h"
#include "Generator.h"

/**
 * Entry point. The command line paramaters are as follows (in this order):
 *   
 *   1.  Year. The program will generate a calendar for each month in the given
 * 		 year, as well as its preceding year and its following year. The minimum
 * 		 supported year is 1582, and only October onwards will be generated in 
 * 		 1582.
 * 
 *   2.  HTML file name. A string containing the name of the generated HTML 
 * 		 file.
 */
int main(int argc, char** argv)
{
	HtmlWriter writer(argv[2]);
	Generator calendarGenerator;

	calendarGenerator.generateCalendar(writer, (unsigned int)std::stoi(argv[1]));

	return 0;
}