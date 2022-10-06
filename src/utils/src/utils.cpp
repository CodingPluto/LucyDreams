#include "../utils.h"
char sign(float value)
{
    if (value >= 0)
    {
        return 1;
    }
    else
    {
        return -1;
    }
    return 1;
}
void wait(double seconds)
{
    usleep(ONE_SECOND * seconds);
}

void printOut(const char character, double delay)
{
    wait(delay);
    std::cout << character << std::flush;
}

void printOut(std::string text, double delay, bool newLine)
{
    for (auto it = text.begin(); it != text.end(); ++it)
    {
        wait(delay);
        std::cout << *it << std::flush;
    }
    if (newLine)
    {
        std::cout << std::endl;
    }
}

void printOut(const char *text, double delay, bool newLine)
{
    for (size_t i = 0; i < strlen(text); ++i)
    {
        wait(delay);
        std::cout << text[i] << std::flush;
    }
    if (newLine)
    {
        std::cout << std::endl;
    }
}

bool isInt(std::string &text)
{
    if (text.length() == 0)
    {
        return false;
    }
    for (auto pChar = text.begin(); pChar != text.end(); ++pChar)
    {
        if (*pChar == '-' && pChar == text.begin()){}
        else if (*pChar == '.'){}
        else
        {
            if (*pChar >= '0' && *pChar <= '9'){}
            else
            {
                return false;
            }
        }
    }
    return true;
}

int stringToInt(std::string text)
{
    if (isInt(text))
    {
        std::stringstream convertStream(text);
        int number;
        convertStream >> number;
        return number;
    }
    else
    {
        throw std::invalid_argument("Failed to convert a string to an int");
    }
    return 0;
}

std::string intToString(int numbers)
{
    return std::to_string(numbers);
}

std::string toLower(std::string text)
{
    for (auto it = text.begin(); it != text.end(); ++it)
    {
        if (*it >= 'A' && *it <= 'Z')
        {
            *it += 32;
        }
    }
    return text;
}

char toLower(char character)
{
    if (character >= 'A' && character <= 'Z')
    {
        character += 32;
    }
    return character;
}

char toUpper(char character)
{
    if (character >= 'a' && character <= 'z')
    {
        character -= 32;
    }
    return character;
}

std::string toUpper(std::string text)
{
    for (auto it = text.begin(); it != text.end(); ++it)
    {
        if (*it >= 'a' && *it <= 'z')
        {
            *it -= 32;
        }
    }
    return text;
}

std::string capitalize(std::string text)
{
    if (text.length() > 0 && text[0] >= 'a' && text[0] <= 'z')
    {
        text[0] -= 32;
    }
    return text;

}

void whitespace(int newLines, int delay)
{
    for (int i = 0; i < newLines; ++i)
    {
        printOut('\n', delay);

    }
}

void border(char borderChar, int length, int thickness, bool newLine, int delay)
{
    for (int i = 0; i < thickness; ++i)
    {
        for (int j = 0; j < length; ++j)
        {
            printOut(borderChar, delay);
        }
        if (newLine)
        {
            printOut('\n', delay);
        }
    }
}

long long getIntInput()
{
    printOut("> ", 0, false);
    std::string rawInput;
    std::cin >> rawInput;
    try
    {
        return stringToInt(rawInput);
    }
    catch (const std::invalid_argument &e)
    {
        throw std::invalid_argument("Couldn't Get Int Input!!!");
    }
}

std::string getInput(bool allowSpaces)
{
    printOut("> ", 0, false);
    std::string input;
    if (allowSpaces)
    {
        std::getline(std::cin, input);
    }
    else
    {
        std::cin >> input;
    }
    return input;
}

int generateRandomNumber(int min, int max)
{
    if (max < min)
    {
        throw std::out_of_range("num generation error: [max is more than min]");
    }
    else
    {
        int offset = 0;
        if (min < 0)
        {
            max += abs(min);
            offset += abs(min);
            min = 0;
        }
        return rand() % (max + 1 - min) + min - offset;

    }
}


void setSeed(unsigned int seed)
{
    srand(seed);
}
void clampMax(float &variable, float clampValue)
{
    if (variable > clampValue)
    {
        variable = clampValue;
    }
}
void clampMin(float &variable, float clampValue)
{
    if (variable < clampValue)
    {
        variable = clampValue;
    }
}