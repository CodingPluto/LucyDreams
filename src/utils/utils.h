#include <string.h>
#include <sstream>
#include <random>
#include <unistd.h>
#include <iostream>
#ifndef SRC_UTILS_H_
#define SRC_UTILS_H_
#define DEFAULT_DELAY 0.01
#define ONE_SECOND 1000000
// Copyright (C) 2022 Chris Watson
char sign(float value);
void wait(double seconds);
void printOut(const char character, double delay = DEFAULT_DELAY);
void printOut(std::string text, double delay = DEFAULT_DELAY, bool newLine = true);
void printOut(const char *text, double delay = DEFAULT_DELAY, bool newLine = true);
bool isInt(std::string &text);
int stringToInt(std::string text);
std::string intToString(int numbers);
std::string toLower(std::string text);
char toLower(char character);
char toUpper(char character);
std::string toUpper(std::string text);
std::string capitalize(std::string text);
void whitespace(int newLines, int delay = 0);
void border(char borderChar, int length, int thickness = 1, bool newLine = true, int delay = 0);
long long getIntInput();
std::string getInput(bool allowSpaces = false);
int generateRandomNumber(int min, int max);
void setSeed(unsigned int seed);
void clampMax(float &variable, float clampValue);

void clampMin(float &variable, float clampValue);

template<typename T>
std::string addressToString(T object)
{
    std::ostringstream address;
    address << (void const *)object;
    return address.str();
}


#endif
