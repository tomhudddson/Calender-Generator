# Gregorian Calendar Generator #

## Introduction ##

This project generates a Gregorian calendar for each month of a given year and
outputs it into a static HTML file. The previous year and the following year
are also generated and outptted to the HTML file.

The Gregorian calendar was introduced in October 1582 as a modification to the 
Julian calendar. Therefore, this generator supports October 1852 and onwards.

## Usage ##

To generate a calendar, the program must first be built. The executable will 
then be found in the bin folder which can be run from the command line. There 
are two command line arguments:

1. Year - An integer. This is the year to generate. Year - 1 and Year + 1
will also be generated. Note, the minimum year is 1582 and if an older year
is given, the calendar will not be generated.

2. HTML File Name - A string. This is the name of the file which the 
outputted HTML is written to. If it does not exist, it will be created and 
if it already exists, it will be overwritten. Unless the filepath is 
explicitly given, the HTML file will be saved in the bin folder. 

## Overview ##

The Calendar Generator is composed of two main classes:

* `HtmlWriter` - this class allows for writing valid HTML to an output file.
* `Generator` - this class generates the Gregorian calendar for the given 
year and uses the `HtmlWriter` to write it to a HTML file.