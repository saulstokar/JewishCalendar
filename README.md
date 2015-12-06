# JewishCalendar
Synopsis
--------
This program calculates the date of the week the Jewish New Year (Rosh Hashana) falls on f
for a specified Jewish year. It also prints out the reason Rosh Hashana occured on that day.
For details about how the Jewish calendar is calculated (and definitions of the Hebrew terms used below), I highly recommend the web site: http://hebrewcalendar.tripod.com/ 

Example
-------
It the user responds to the prompt with the Hebrew year 5776 (Oct 2015 - 2016) the program prints on the shell:

 Initial setting: Rosh Hashana is on 1
  Using ADU Dehiya
Data for hebrew year 5776
 
 Molad: day 1: hour: 23 helek: 135
 Reason for dehiya: ADU
 Rosh Hashana day: 2 (Monday, 2109284)   

Data stored in file 5776.dat

Initial setting: Rosh Hashana is on 0
Using Molad Zakkein & ADU dehiya
Data for hebrew year 5777
 Molad: day 0: hour: 20 helek: 724
 Reason for dehiya: Molad Zakein & ADU
 Rosh Hashana day: 2 (Monday, 2109669) 
 
 Data stored in file 5777.dat

Length of year 5776: 385 days

Enter first year last year (enter 1 1)

Note: if you enter 2 different Hebrew years on the last line (e.g. 5700 5710), the program prints out the length (alone) of each year in teh specified interval.  

Motivation
----------
I wrote this to better understand the rules of the Jewish calendar as well as to learn/practice c++

Installation
------------

API reference
-------------

Tests
-----
Using the interval option referred to above, I checked that all the years over a large range had "legal" values. 

Contributors
------------
Saul Stokar - I wrote the first version

License 
-------
None. To be shared freely.
 
