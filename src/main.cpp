#include <iostream>

#include "HtmlWriter.h"
#include "Generator.h"

int main(int argc, char** argv)
{
	HtmlWriter writer("html_file.html");
	Generator calendarGenerator;

	calendarGenerator.generateCalendar(writer, 1582);

	return 0;
}