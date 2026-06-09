#pragma once

#include "StrHelper.h"
#include <stdbool.h>
#include <filesystem>
#include <istream>
#include <string>
#include <stack>


namespace omfl
{

#pragma region Argument

    class Argument
    {
    private:

#pragma region Поля
        bool isArray;
        std::string section;
        std::string key;
        std::string value;
        std::vector<Argument> subValues;
#pragma endregion

#pragma region Методы

        std::string GetPath()
        {
            return this->section + '.' + this->key;
        }

#pragma endregion

    public:

#pragma region Поля

#pragma endregion

#pragma region Методы

#pragma region Array

        bool IsArray()
        {
            return this->isArray;
        };
#pragma endregion

#pragma region Int

        bool IsInt()
        {
            return StrHelper().IsInt(this->value);
        }

        int AsInt()
        {
            return StrHelper().IsInt(this->value);
        }

        int AsIntOrDefault(int value)
        {
            if (this->IsInt())
                return this->AsInt();
            else
                return value;
        }

#pragma endregion

#pragma region Float

        bool IsFloat()
        {
            return StrHelper().IsFloat(this->value);
        }

        float AsFloat()
        {
            return StrHelper().ToFloat(this->value);
        }

        float AsFloatOrDefault(float value)
        {
            if (this->IsFloat())
                return this->AsFloat();
            else
                return value;
        }

#pragma endregion

#pragma region Bool

        bool IsBool()
        {
            return StrHelper().IsBool(this->value);
        }

        bool AsBool()
        {
            return StrHelper().ToBool(this->value);
        }

#pragma endregion

#pragma region String

        bool IsString()
        {
            return !this->IsInt() && !this->IsFloat() && !this->IsBool();
        }

        std::string AsString()
        {
            return this->value;
        }

        std::string AsStringOrDefault(std::string str)
        {
            if (this->IsString())
                return this->value;
            else
                return str;
        }

#pragma endregion

#pragma region Get

        Argument Get(std::string str)
        {
            return *this;
        }

#pragma endregion

#pragma region Other

        std::string FieldToString(std::string name, std::string value, int level = 0)
        {
            StrHelper strHelper = StrHelper();
            std::stringstream ss;
            ss << strHelper.GetSeparator("\t", level) << name << ": " << value << std::endl;
            return ss.str();
        }

        std::string ToString(int level = 0)
        {
            StrHelper strHelper = StrHelper();
            std::string str = "";
            str += this->FieldToString("Section", this->section, level);
            str += this->FieldToString("Key", this->key, level);
            str += this->FieldToString("Value", this->value, level);
            str += this->FieldToString("IsArray", this->isArray ? "true" : "false", level);
            str += this->FieldToString("SubValues",
                this->subValues.size() == 0 ? "Empty" : std::to_string(this->subValues.size()),
                level);
            for (Argument item : this->subValues)
            {
                str += item.ToString(level + 1);
            }
            str += strHelper.GetSeparator("\t", level);
            str += strHelper.GetSeparator("_", 20);
            str += "\n";
            return str;
        }

#pragma endregion


#pragma endregion

#pragma region Конструкторы/Деструкторы

        Argument()
        {

        }

        Argument(const Argument& arg)
        {
            this->key = arg.key;
            this->section = arg.section;
            this->value = arg.value;
            this->isArray = arg.isArray;
            this->subValues = arg.subValues;
        }

        Argument(std::string str)
        {

        }

        Argument(std::string section, std::string key, std::string value, bool isArray = false)
        {
            this->section = section;
            this->key = key;
            this->isArray = isArray;
            StrHelper strHelper = StrHelper();
            if (strHelper.Contains(value, "[],") && value[0] == '[' && value[value.size() - 1] == ']')
            {
                isArray = true;
#pragma region Обход строки
                std::stack<Argument> argStack;
                std::string buffer = "";
                Argument* currentArg = this;
                bool isInsideString = false;
                for (int i = 0; i < value.length(); i++)
                {
                    if (value[i] == '"')
                    {
                        if (!isInsideString)
                            isInsideString = true;
                        else
                        {
                            currentArg->subValues.push_back(Argument(currentArg->section, currentArg->key, buffer));
                            isInsideString = false;
                            buffer = "";
                        }
                        continue;
                    }
                    if (value[i] == '[')
                    {
                        if (currentArg->isArray == true)
                        {
                            argStack.push(*currentArg);
                            currentArg = new Argument(this->section, this->key, "", true);
                        }
                        else
                        {
                            this->isArray = true;
                        }
                        continue;
                    }
                    if (value[i] == ']')
                    {
                        if (buffer.length() > 0)
                            currentArg->subValues.push_back(Argument(currentArg->section, currentArg->key, buffer));
                        if (argStack.size() > 0)
                        {
                            Argument parent = argStack.top();
                            argStack.pop();
                            parent.subValues.push_back(*currentArg);
                            currentArg = new Argument(parent);
                        }
                        buffer = "";
                        continue;
                    }
                    else if (value[i] == ' ')
                    {
                        if (isInsideString)
                            buffer += value[i];
                        continue;
                    }
                    else if (value[i] == ',')
                    {
                        if (buffer.length() > 0)
                        {
                            currentArg->subValues.push_back(Argument(currentArg->section, currentArg->key, buffer));
                            buffer = "";
                            continue;
                        }
                        continue;
                    }
                    else
                    {
                        buffer += value[i];
                    }
                }
                if (buffer.length() > 0)
                    currentArg->subValues.push_back(Argument(currentArg->section, currentArg->key, buffer));
                this->subValues = currentArg->subValues;
#pragma endregion
            }
            else
            {
                this->value = value;
            }
        }

#pragma endregion

#pragma region Операторы

        Argument& operator[](int index)
        {
            return this->subValues[index];
        }

#pragma endregion

#pragma region Обработчики событий

#pragma endregion
    };

#pragma  endregion

#pragma  region Parser

    class Parser
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

        Parser _parse(const std::filesystem::path& path) const
        {
            return *this;
        };

        Parser _parse(const std::string& str) const
        {
            return *this;
        }


        bool valid() const
        {
            return false;
        }

        Argument Get(const char* string) const
        {
            return Argument("");
        }

#pragma endregion

#pragma region Конструкторы/Деструкторы

#pragma endregion

#pragma region Операторы

#pragma endregion

#pragma region Обработчики событий

#pragma endregion


    };

    static Parser parse(const std::filesystem::path& path)
    {
        Parser parser = Parser();
        return parser._parse(path);
    };

    static Parser parse(const std::string& str)
    {
        Parser parser = Parser();
        return parser._parse(str);
    }

#pragma  endregion

}