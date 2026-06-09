#pragma  once
#ifndef LAB6_STRHELPER_H
#define LAB6_STRHELPER_H

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <regex>

class StrHelper
{

private:

#pragma region Поля

#pragma endregion

#pragma region Методы


#pragma endregion

public:

#pragma region Поля

#pragma endregion

#pragma region Методы

    int CharIndex(std::string str, char c)
    {
        for (int i = 0; i < str.length(); i++)
            if (str[i] == c)
                return i;
        return -1;
    }

    /// <summary>
    /// Объединяет строки с списке в одну строку
    /// </summary>
    /// <param name="lines">список</param>
    /// <returns></returns>
    std::string Join(std::vector<std::string> lines)
    {
        return Join(lines, "");
    }

    /// <summary>
    /// Объединяет строки с списке в одну строку
    /// </summary>
    /// <param name="lines">список</param>
    /// <param name="spacer">разделитель</param>
    /// <returns></returns>
    std::string Join(std::vector<std::string> lines, std::string spacer)
    {
        std::string res = "";
        for (int i = 0; i < lines.size(); i++)
            res += lines[i] + spacer;;
        return res;
    }

    /// <summary>
    /// Заменяет все вхождения
    /// указанной подстроки в строке
    /// </summary>
    /// <param name="s">исходная строка</param>
    /// <param name="search">искомая подстрока</param>
    /// <param name="replace">замена для подстроки</param>
    void ReplaceAll(std::string& s, const std::string& search, const std::string& replace)
    {
        for (size_t pos = 0;; pos += replace.length())
        {
            // Locate the substring to replace
            pos = s.find(search, pos);
            if (pos == std::string::npos) break;
            // Replace by erasing and inserting
            s.erase(pos, search.length());
            s.insert(pos, replace);
        }
    }

    /// <summary>
    /// Заменяет все вхождения
    /// указанной подстроки в строке
    /// </summary>
    /// <param name="str">исходная строка</param>
    /// <param name="what">что заменять</param>
    /// <param name="replace">на что заменять</param>
    /// <returns></returns>
    std::string Replace(std::string str, std::string what, std::string replace)
    {
        while (str.find(what) != -1 && what.length() > 0)
            str = str.replace(str.find(what), what.size(), replace);
        return str;
    }

    std::string Replace(std::string str, std::vector<char> what, std::string replace)
    {
        for (int i = 0; i < what.size(); i++)
        {
            std::string whatStr = "";
            whatStr += what[i];
            str = this->Replace(str, whatStr, replace);
        }
        return str;
    }

    /// <summary>
    /// разбивает строку по разделителям
    /// </summary>
    /// <param name="str">строка</param>
    /// <param name="delimiters">строка с разделителями</param>
    /// /// <param name="notDelete">строка с элементами, которые не нужно удалять</param>
    /// <returns>массив строк</returns>
    //TODO: переделать на вектора
//    std::vector<std::string> Split(std::string str, std::string delimiters, std::string notDelete) {
//        std::string buffer = "";
//        std::vector<std::string> res;
//        for (int i = 0; i < str.size(); i++) {
//            char c = str[i];
//            if (delimiters.find(c) == std::string::npos)
//                buffer += c;
//            else if (buffer.length() > 0) {
//                res.push_back(buffer);
//                buffer = "";
//            }
//            if (notDelete.find(c) != std::string::npos) {
//                std::string temp;
//                temp += c;
//                res.push_back(temp);
//            }
//        }
//        if (buffer.length() > 0) {
//            res.push_back(buffer);
//            buffer = "";
//        }
//        return res;
//    }

    std::vector<std::string> Split(std::string str, std::string delimiter, bool addEmptyStrings = true)
    {
        size_t pos = 0;
        std::string token;
        std::vector<std::string> res;
        while ((pos = str.find(delimiter)) != std::string::npos)
        {
            token = str.substr(0, pos);
            if (token.length() == 0)
            {
                if (addEmptyStrings)
                    res.push_back(token);
            }
            else
                res.push_back(token);
            str.erase(0, pos + delimiter.length());
        }
        if (str.length() == 0)
        {
            if (addEmptyStrings)
                res.push_back(str);
        }
        else
            res.push_back(str);
        return res;
    }


    /// <summary>
    /// разбивает строку по разделителям
    /// </summary>
    /// <param name="str">строка</param>
    /// <param name="delimiter">разделитель</param>
    std::vector<std::string> Split(std::string str, char delimiter)
    {
        std::vector<std::string> internal;
        std::stringstream ss(str);
        std::string tok;
        while (getline(ss, tok, delimiter))
        {
            internal.push_back(tok);
        }
        return internal;
    }

    /// <summary>
    /// Проверяет содержит ли строка указанные символы и возвращает число совпадающих символов
    /// </summary>
    /// <param name="str">строка для проверки</param>
    /// <param name="collection">символы в одной строке</param>
    /// <returns>число совпадающих символов</returns>
    int ContainsCount(std::string str, std::string collection)
    {
        if (str.length() == 0)
            return 0;
        int counter = 0;
        for (int i = 0; i < collection.size(); i++)
            if (str.find(collection[i]) != std::string::npos)
                counter++;
        return counter;
    }

    int ContainsCount(std::string str, char c)
    {
        if (str.length() == 0)
            return 0;
        int counter = 0;
        for (int i = 0; i < str.size(); i++)
            if (str[i] == c)
                counter++;
        return counter;
    }


    /// <summary>
    /// Проверяет содержит ли строка указанные символы
    /// </summary>
    /// <param name="str">строка для проверки</param>
    /// <param name="collection">символы в одной строке</param>
    /// <returns></returns>
    bool ContainsAny(std::string str, std::string collection)
    {
        return this->ContainsCount(str, collection) > 0;
    }

    /// <summary>
    /// Проверяет содержит ли строка ВСЕ указанные символы
    /// </summary>
    /// <param name="str">строка для проверки</param>
    /// <param name="collection">символы в одной строке</param>
    /// <returns></returns>
    bool ContainsAll(std::string str, std::string collection)
    {
        return this->ContainsCount(str, collection) == collection.length();
    }

    /// <summary>
    ///
    /// </summary>
    /// <param name="str"></param>
    /// <param name="strFind"></param>
    /// <returns></returns>
    bool ContainsStr(std::string str, std::string strFind)
    {
        return (str.find(strFind) != std::string::npos);
    }

    std::string ToLower(const std::string& str)
    {
        std::string res = "";
        for (char c : str)
            res += tolower(c);
        return res;
    }

    std::string ToUpper(const std::string& str)
    {
        std::string res = "";
        for (char c : str)
            res += toupper(c);
        return res;
    }

    int ToInt(const std::string& str)
    {
        return atoi(str.c_str());
    }

    double ToFloat(const std::string& str)
    {
        return atof(str.c_str());
    }

    bool ToBool(const std::string& str)
    {
        return this->ToLower(str) == "true";
    }


    bool IsFloat(std::string str)
    {
        std::string signs = "+-";
        std::string digits = "1234567890";
        std::string delimiters = ".,";
        std::string alphabet = "+-.,1234567890";
        int delimitersCount = 0;
        int signsCount = 0;
        int digitCount = 0;
        for (size_t i = 0; i < str.length(); i++)
        {
            char currentChar = str[i];
#pragma region Знаки
            if (signs.find(currentChar) != std::string::npos)
            {
                signsCount++;
                if (i != 0)
                    return false;
                if (digitCount > 0)
                    return false;
                if (signsCount > 1)
                    return false;
            }
#pragma endregion

#pragma region Разделители
            if (delimiters.find(currentChar) != std::string::npos)
            {
                delimitersCount++;
                if (delimitersCount > 1)
                    return false;
                if (i == 0)
                    return false;
                if (digitCount < 1)
                    return false;
                if (i == str.length() - 1)
                    return false;
            }
#pragma endregion

#pragma region Цифры
            if (currentChar == '0' && digitCount == 0 && signsCount == 0)
                return false;
            if (digits.find(currentChar) != std::string::npos)
            {
                digitCount++;
            }
#pragma endregion

            if (alphabet.find(currentChar) == std::string::npos)
                return false;
        }
        if ((signsCount > 0 || delimitersCount > 0) && digitCount == 0)
            return false;
        return delimitersCount == 1;
        //return true;
    }

    /// <summary>
    /// Поверяет, является ли строка числом
    /// </summary>
    /// <param name="s">строка</param>
    /// <returns>true - если является числом</returns>
    bool IsInt(const std::string& s)
    {
        std::regex rgx(R"(^(\s)*[-+]?(\d)+(\s)*$)");
        return std::regex_match(s.begin(), s.end(), rgx);
    }

    bool IsBool(const std::string& s)
    {
        return this->ToLower(s) == "true" || this->ToLower(s) == "false";
    }

    //https://regex101.com/r/1YB7PF/1
    bool IsString(const std::string& s, bool checkQuotes = false)
    {
        if (checkQuotes)
        {
            std::regex rgx(R"(^(\s)*\"([a-zA-Z0-9\-_\s\[\],.]+)\"(\s)*$)");
            return std::regex_match(s.begin(), s.end(), rgx);
        }
        else
        {
            std::regex rgx(R"(^(\s)*[a-zA-Z0-9\-_\s]+(\s)*$)");
            return std::regex_match(s.begin(), s.end(), rgx);
        }
    }

    //Проверка на комментарий начинающийся на #
    bool IsComment(const std::string& s)
    {
        std::regex rgx(R"(^(\s)*#[\s|\S|\w]*$)");
        return std::regex_match(s.begin(), s.end(), rgx);
    }

    /// <summary>
    ///
    /// </summary>
    /// <param name="values"></param>
    /// <returns></returns>
    std::vector<std::string> RemoveCopies(std::vector<std::string> values)
    {
        std::string valuesStr = "";
        for (int i = 0; i < values.size(); i++)
            if (!ContainsStr(valuesStr, values[i]))
            {
                valuesStr += values[i];
                valuesStr += " ";
            }
        values = Split(valuesStr, ' ');
        return values;
    }

    /// <summary>
    /// удаляет вхождения данного символа в строке
    /// </summary>
    /// <param name="str">строка</param>
    /// <param name="c">символ для удаления</param>
    /// <returns>строка с удаленными символами</returns>
    std::string Remove(std::string str, char c)
    {
        std::string temp = "";
        for (int i = 0; i < str.length(); i++)
            if (str[i] != c)
                temp += str[i];
        return temp;
    }

    std::string RemoveLastSpaces(std::string str)
    {
        if (str.length() > 0)
        {
            while (str[str.length() - 1] == ' ')
            {
                str = str.substr(0, str.length() - 1);
            }
        }
        return str;
    }

    std::string RemoveFirstSpaces(std::string str)
    {
        if (str.length() > 0)
        {
            while (str.length() > 0 && str[0] == ' ')
            {
                str = str.substr(1, str.length());
            }
        }
        return str;
    }

    std::string RemoveComment(std::string str, std::string commentDelimeter)
    {
        int index = str.find(commentDelimeter);
        if (index != std::string::npos)
        {
            return str.substr(0, index);
        }
        return str;
    }

    std::string GetSeparator(std::string separatorItem, int count)
    {
        std::string str = "";
        for (int i = 0; i < count; i++)
            str += separatorItem;
        return str;
    }
    // key = 1 # fhajkfhkajfh
#pragma endregion

#pragma region Конструкторы/Деструкторы

    StrHelper() {}

    ~StrHelper() {}

#pragma endregion

#pragma region Операторы

#pragma endregion

#pragma region Обработчики событий

#pragma endregion
};


#endif //LAB6_STRHELPER_H
