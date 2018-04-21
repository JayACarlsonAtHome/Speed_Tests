#include <iostream>
#include <math.h>
#include <cstring>

using sstr = std::string;

//constant expressions
constexpr auto commandPosition = 19;
constexpr auto daysIn400Years = 146097L;
constexpr auto seconds_in_minute = 60;
constexpr auto seconds_in_hour   = 60 * seconds_in_minute;
constexpr auto seconds_in_day    = 24 * seconds_in_hour;
// the actual value is not constant, but we can average over 400 years to make it closer
constexpr auto average_seconds_in_year = (daysIn400Years * seconds_in_day)/400.0;

time_t get_Time()
{
    time_t rawtime;
    time (&rawtime);
    return rawtime;
}

template <typename T>
sstr get_Time_Part(T timePart)
{
    sstr strTimePart = std::to_string(timePart);
    if (timePart < 10) {
        strTimePart = "0" + strTimePart;
    }
    return strTimePart;
}

sstr get_GmtOffset()
{
    time_t theTime;
    struct tm * timeinfo;
    time (&theTime);
    timeinfo = localtime (&theTime);

    long gmt    = timeinfo->tm_gmtoff;
    long gmtHoursOffset = gmt / 3600;

    sstr strGmtOff  = std::to_string(gmtHoursOffset);
    sstr offset;
    if (gmtHoursOffset > -1)
    {
        offset = get_Time_Part<long>(gmtHoursOffset);
        if (gmtHoursOffset == 0)
        {
            strGmtOff = "( " + offset + ")";
        } else
        {
            strGmtOff = "(+" + offset + ")";
        }
    }
    else
    {
        gmtHoursOffset *= -1;
        offset = get_Time_Part<long>(gmtHoursOffset);
        strGmtOff = "(-" + offset + ")";
    }
    return strGmtOff;
}

sstr get_Time_as_String(time_t theTime)
{
    struct tm * timeinfo;
    //if (theTime == 0)
    //{
    //    time (&theTime);
    //}
    timeinfo = localtime (&theTime);

    int hours   = timeinfo->tm_hour;
    int minutes = timeinfo->tm_min;
    int seconds = timeinfo->tm_sec;

    sstr strHours   = get_Time_Part<int>(hours);
    sstr strMinutes = get_Time_Part<int>(minutes);
    sstr strSeconds = get_Time_Part<int>(seconds);

    sstr time = strHours + ":" + strMinutes + ":" + strSeconds + " ";

    return time;
}

sstr padLeftZeros(int max_width, int number)
{
    auto max = pow(10,max_width);
    bool preConditionsMet = false;
    sstr result;
    //pre setup
    sstr strNumber = std::to_string(number);
    unsigned long pad_length = static_cast<unsigned long>(max_width);

    //check preConditions
    if ((number > -1) && (number < max)) {
        preConditionsMet = true;
        pad_length = max_width - strNumber.length();
    }

    if (preConditionsMet) {
        if (pad_length > 0) {
            sstr pad_string = sstr(pad_length, '0');
            result = pad_string;
            result.append(strNumber);
        } else
        {
            result = strNumber;
        }
    }
    else
    {
        result = "Error in padLeftZeros(int max_width, int number);";
    }
    return result;
}

sstr getDuration(time_t stop, time_t start)
{
    // we are going to give a positive duration
    //   even if the parameters get switched

    long long secondsTotal = 0;
    if (start > stop)
    {
        secondsTotal = start - stop;
    }
    else
    {
        secondsTotal = stop - start;
    }

    // We are only showing 3 digits for the year,
    //    and if that is not enough we have other problems...
    int years = static_cast<int>(secondsTotal / average_seconds_in_year);
    long long remainingSeconds = static_cast<long long>(secondsTotal - (years * average_seconds_in_year));

    // We are only showing 3 digits for the year,
    //    and if that is not enough we have other problems...
    if (years > 999) years = 999;
    sstr strYears = padLeftZeros(3, years);

    // There can only be 3 digits here so we are safe with an int
    int days = static_cast<int>(remainingSeconds / seconds_in_day);
    remainingSeconds = remainingSeconds - (days * seconds_in_day);
    sstr strDays = padLeftZeros(3, days);

    // There can only be 2 digits here so we are safe with an int
    int hours = static_cast<int>(remainingSeconds / seconds_in_hour);
    remainingSeconds = remainingSeconds - (hours * seconds_in_hour);
    sstr strHours = padLeftZeros(2, hours);

    // There can only be 2 digits here so we are safe with an int
    int minutes = static_cast<int>(remainingSeconds / seconds_in_minute);
    remainingSeconds = remainingSeconds - (minutes * seconds_in_minute);
    sstr strMinutes = padLeftZeros(2, minutes);

    // There can only be 2 digits here so we are safe with an int
    int seconds = static_cast<int>(remainingSeconds);
    sstr strSeconds = padLeftZeros(2, seconds);

    sstr result = strYears;
    result.append(":");
    result.append(strDays);
    result.append(":");
    result.append(strHours);
    result.append(":");
    result.append(strMinutes);
    result.append(":");
    result.append(strSeconds);
    result.append(" ");
    return result;
}


sstr lowerCaseString1(sstr& some_value)
{
    // unicode lower case conversions require
    // very specialized code, and this is not it
    // but it will handle the english words that
    // we need for this program.

    sstr result;
    int oneChar;
    for (auto idx = 0ul; idx < some_value.length(); ++idx)
    {
        if (std::isupper(some_value.at(idx)))
        {
            oneChar =  std::tolower(some_value.at(idx));
        }
        else
        {
            oneChar = some_value.at(idx);
        }
        result.append({static_cast<char>(oneChar)});
    }
    return result;
}

sstr lowerCaseString2(sstr& some_value)
{
    // unicode lower case conversions require
    // very specialized code, and this is not it
    // but it will handle the english words that
    // we need for this program.

    sstr result;
    int oneChar;
    for (auto idx = 0ul; idx < some_value.length(); ++idx)
    {
        oneChar =  std::tolower(some_value.at(idx));
        result.append({static_cast<char>(oneChar)});
    }
    return result;
}

sstr lowerCaseString3(sstr& some_value)
{

    sstr result;
    int oneChar;
    auto len = some_value.length();
    char strChar[len + 1];
    strcpy(strChar, some_value.c_str());
    for (auto idx = 0ul; idx < len; ++idx)
    {
        oneChar =  std::tolower(strChar[idx]);
        result.append({static_cast<char>(oneChar)});
    }
    return result;
}

/*
sstr lowerCaseString4(sstr& some_value)
{
    int oneChar;
    auto len = some_value.length();
    char strChar1[len + 1];
    char strChar2[len + 1];
    strcpy(strChar1, some_value.c_str());
    for (auto idx = 0ul; idx < len; ++idx)
    {
        strChar2[idx] =  std::tolower(strChar1[idx]);
    }
    sstr result {strChar2};
    return result;
}
*/

sstr lowerCaseString4(sstr& some_value)
{
    auto len = some_value.length();
    char strChar[len+1];
    strcpy(strChar, some_value.c_str());
    for (auto idx = 0ul; idx < len; ++idx)
    {
        strChar[idx] =  std::tolower(strChar[idx]);
    }
    sstr result {strChar};
    return result;
}

sstr lowerCaseString5(sstr& some_value)
{
    auto len = some_value.length();
    char strChar[len+1];
    for (auto idx = 0ul; idx < len; ++idx)
    {
        strChar[idx] =  std::tolower(some_value.at(idx));
    }
    strChar[len] = 0;
    sstr result {strChar};
    return result;
}

sstr lowerCaseString6(sstr& some_value)
{
    auto len = some_value.length();
    char strChar[len + 1];
    for (auto idx = 0ul; idx <= len; ++idx)
    {
        strChar[idx] =  std::tolower(some_value[idx]);
    }
    sstr result {strChar};
    return result;
}


void preTest_Header()
{
    std::cout << "Test : Start    : Stop     : Durations        " << std::endl;
    std::cout << "000x : HH:MM:SS : HH:MM:SS : YYY:DDD:HH:MM:SS " << std::endl;
    std::cout << "==============================================" << std::endl;

}
sstr do_test( int testNumber, int maxTestLoopCount,
              sstr (*funptr)(sstr& text),
              sstr text)
{
    sstr answer = "";
    sstr outTest = padLeftZeros(4, testNumber);
    time_t time1 = get_Time();
    sstr start = get_Time_as_String(time1);
    std::cout << outTest << " : " << start << ": ";
    std::cout.flush();
    for(int i = 0; i < maxTestLoopCount; ++i)
    {
        answer = funptr(text);
    }
    time_t time2 = get_Time();
    sstr stop = get_Time_as_String(time2);
    sstr duration = getDuration(time2, time1);
    std::cout << stop << ": " << duration  << std::endl;
    return answer;
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    preTest_Header();
    sstr test = "aaaaakaakakakaaaaakaaakakaaaaaaHaaaaaaaaaaakqqqqqqqqqqkHoowskkwiskqiakaiqkaqiqkaiqQ";
    int maxLoopCount = 100000000;
    //maxLoopCount = 1;
    //do_test(1, maxLoopCount, lowerCaseString1, test);
    //do_test(2, maxLoopCount, lowerCaseString2, test);
    //do_test(3, maxLoopCount, lowerCaseString3, test);
    do_test(4, maxLoopCount, lowerCaseString4, test);
    do_test(5, maxLoopCount, lowerCaseString5, test);
    do_test(6, maxLoopCount, lowerCaseString6, test);

    sstr test0 = test;
    sstr test1 = lowerCaseString1(test);
    sstr test2 = lowerCaseString2(test);
    sstr test3 = lowerCaseString3(test);
    sstr test4 = lowerCaseString4(test);
    sstr test5 = lowerCaseString5(test);
    sstr test6 = lowerCaseString6(test);

    std::cout << "test0 = ***" << test0 << "***" <<std::endl;
    std::cout << "test1 = ***" << test1 << "***" <<std::endl;
    std::cout << "test2 = ***" << test2 << "***" <<std::endl;
    std::cout << "test3 = ***" << test3 << "***" <<std::endl;
    std::cout << "test4 = ***" << test4 << "***" <<std::endl;
    std::cout << "test5 = ***" << test5 << "***" <<std::endl;
    std::cout << "test6 = ***" << test6 << "***" <<std::endl;

    test = "";
    test0 = test;
    test1 = lowerCaseString1(test);
    test2 = lowerCaseString2(test);
    test3 = lowerCaseString3(test);
    test4 = lowerCaseString4(test);
    test5 = lowerCaseString5(test);
    test6 = lowerCaseString6(test);

    std::cout << "test0 = ***" << test0 << "***" <<std::endl;
    std::cout << "test1 = ***" << test1 << "***" <<std::endl;
    std::cout << "test2 = ***" << test2 << "***" <<std::endl;
    std::cout << "test3 = ***" << test3 << "***" <<std::endl;
    std::cout << "test4 = ***" << test4 << "***" <<std::endl;
    std::cout << "test5 = ***" << test5 << "***" <<std::endl;
    std::cout << "test6 = ***" << test6 << "***" <<std::endl;


    return 0;
}