#include <iostream>

#include "HtmlWriter.h"

int main(int argc, char** argv)
{
	HtmlWriter writer("html_file.html");

	writer.singleTag(TagType::DOCTYPE);
	writer.openTag(TagType::HTML);

	writer.openTag(TagType::HEAD);
	writer.closeTag(TagType::HEAD);

	writer.openTag(TagType::BODY);
	writer.closeTag(TagType::BODY);

	writer.closeTag(TagType::HTML);

	return 0;
}