#include <iostream>

#include "HtmlWriter.h"

int main(int argc, char** argv)
{
	HtmlWriter writer("html_file.html");

	writer.specialTag(TagType::DOCTYPE);
	writer.writeTag(TagType::HTML, OPEN_TAG);

	writer.writeTag(TagType::HEAD, OPEN_TAG);
	writer.writeTag(TagType::HEAD, CLOSE_TAG);

	writer.writeTag(TagType::BODY, OPEN_TAG);
	writer.writeTag(TagType::BODY, CLOSE_TAG);

	writer.writeTag(TagType::HTML, CLOSE_TAG);

	return 0;
}