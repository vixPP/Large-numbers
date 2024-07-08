﻿#include <iostream>
#include <string>
#include <algorithm>

class big_integer 
{
public:

    big_integer(const std::string& value) : value(value) {}

    big_integer(big_integer&& other) noexcept : value(std::move(other.value)) {}

    big_integer& operator=(big_integer&& other) noexcept 
    {
        value = std::move(other.value);
        return *this;
    }

    big_integer operator+(const big_integer& other) const 
    {
        std::string result;
        int carry = 0;
        int i = value.size() - 1;
        int j = other.value.size() - 1;

        while (i >= 0 || j >= 0 || carry) 
        {
            int sum = carry;
            if (i >= 0) sum += value[i--] - '0';
            if (j >= 0) sum += other.value[j--] - '0';
            result = std::to_string(sum % 10) + result;
            carry = sum / 10;
        }

        return big_integer(result);
    }

    big_integer operator*(int multiplier) const
    {
        std::string result;
        int carry = 0;
        for (int i = value.size() - 1; i >= 0; i--) 
        {
            int product = (value[i] - '0') * multiplier + carry;
            result = std::to_string(product % 10) + result;
            carry = product / 10;
        }
        if (carry) result = std::to_string(carry) + result;
        return big_integer(result);
    }

    friend std::ostream& operator<<(std::ostream& os, const big_integer& num);

private:
    std::string value;
};

std::ostream& operator<<(std::ostream& os, const big_integer& num)
{
    os << num.value;
    return os;
}


int main() 
{

    auto number1 = big_integer("114575");
    auto number2 = big_integer("78524");
    auto result = number1 + number2;
    std::cout << result << std::endl; // Выведет 193099

    return 0;
}