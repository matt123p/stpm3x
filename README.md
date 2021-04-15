# STPM3x library

Manufacturers web-site:
https://www.st.com/en/data-converters/stpm32.html

_Warning_ THIS LIBRARY IS IN DEVELOPMENT AND CURRENTLY UNTESTED.  DO NOT USE IN PRODUCTION.

## Introduction

The STMicroelectronics STPM3x series of chips are for monitoring mains electricity.  You can also purchase a development board, which
this library has been developed against.

For more information about the chip and this library please download the datasheet directly from the STMicro web-site.  There is 
also (slightly harder to find) a datasheet that gives a little more detail on the math required.  This is called "U2066 Getting started 
with the STPM3x", and can be found by Googling that title.

## This library

This library has been written specifically to work with the ESP32 processor and specifically uses the floating point hardware support.  
This library will probably work on simpler processors with software floating point support, but it is not recommended because it will
cause your code to increase in size (for the floating point library) and run significantly slower.

For the purposes of testing and debugging, it is obviously much easier to run this library directly on a PC, and so a Visual Studio project
is included to build and run the library.

## Current Status

The library will connect and talk to the STPM3x chipset, however, it is untested.  Not all the features of the STPM3x are implemented, as only
the features I require for my project are currently implemented.

## Use

To use this library in you own project, you will need to copy the source files in to your own project.
