#include <iostream>

#include "HtmlWriter.h"

int main(int argc, char** argv)
{
	HtmlWriter writer("html_file.html");

	//AttributeList dayCellAttributes;
	//dayCellAttributes.addAttribute(AttributeType::STYLE, "font-size: 20px; font-weight: normal;");

	AttributeList tableAttributes;
	tableAttributes.addAttribute("border=\"1\"");
	tableAttributes.addAttribute("cellspacing=\"0\"");
	tableAttributes.addAttribute("cellpadding=\"4px\"");
	tableAttributes.addAttribute("width=\"200\"");

	writer.specialTag(TagType::DOCTYPE);
	writer.writeTag(TagType::HTML, OPEN_TAG, AttributeList());

	writer.writeTag(TagType::HEAD, OPEN_TAG, AttributeList());
	writer.writeTag(TagType::HEAD, CLOSE_TAG, AttributeList());

	writer.writeTag(TagType::BODY, OPEN_TAG, AttributeList());

	writer.writeTag(TagType::TABLE, OPEN_TAG, tableAttributes);
	writer.writeTag(TagType::TABLE, CLOSE_TAG, AttributeList());

	writer.writeTag(TagType::BODY, CLOSE_TAG, AttributeList());

	writer.writeTag(TagType::HTML, CLOSE_TAG, AttributeList());

	return 0;
}