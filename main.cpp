#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <algorithm>
using namespace std;

string insertZerosBetweenDigits(const string& input) {
    if (input.length() <= 1) return input;

    string output;
    for (size_t i = 0; i < input.length(); ++i) {
        output += input[i];
        if (i != input.length() - 1) {
            output += '0';
        }
    }
    return output;
}

string zamienZera(const string& urojona, const string& rzeczywista) {
    string wynik = urojona;
    int idxRzeczywista = 0;

    for (size_t i = 0; i < wynik.size(); ++i) {
        if (wynik[i] == '0') {
            // Szukamy kolejnej cyfry z rzeczywistej
            while (idxRzeczywista < rzeczywista.size() && !isdigit(rzeczywista[idxRzeczywista])) {
                ++idxRzeczywista;
            }

            if (idxRzeczywista < rzeczywista.size()) {
                wynik[i] = rzeczywista[idxRzeczywista];
                ++idxRzeczywista;
            }
        }
    }
    return wynik;
}

string polacz_liczby(const string& str1, const string& str2) {
    size_t dot1 = str1.find('.');
    size_t dot2 = str2.find('.');

    string integer_part1 = str1.substr(0, dot1 != string::npos ? dot1 : str1.length());
    string fractional_part1 = dot1 != string::npos ? str1.substr(dot1 + 1) : "";

    string integer_part2 = str2.substr(0, dot2 != string::npos ? dot2 : str2.length());
    string fractional_part2 = dot2 != string::npos ? str2.substr(dot2 + 1) : "";

    int max_frac_len = max(fractional_part1.length(), fractional_part2.length());

    fractional_part1.append(max_frac_len - fractional_part1.length(), '0');
    fractional_part2.append(max_frac_len - fractional_part2.length(), '0');

    int max_int_len = max(integer_part1.length(), integer_part2.length());

    // Uzupełnij część całkowitą zerami
    integer_part1.insert(0, max_int_len - integer_part1.length(), '0');
    integer_part2.insert(0, max_int_len - integer_part2.length(), '0');

    string result_integer, result_fraction;
    for (int i = 0; i < max_int_len; ++i) {
        char sum = (integer_part1[i] - '0') + (integer_part2[i] - '0') + '0';
        result_integer.push_back(sum);
    }

    for (int i = 0; i < max_frac_len; ++i) {
        char sum = (fractional_part1[i] - '0') + (fractional_part2[i] - '0') + '0';
        result_fraction.push_back(sum);
    }

    return result_integer + "." + result_fraction;
}

string convertIntegerTo2iReal(int numberInt) {
    if (numberInt == 0) return "0";

    string result;
    while (numberInt != 0) {
        int remainder = numberInt % -4;

        if (remainder < 0) {
            remainder += 4;
            numberInt = (numberInt - remainder) / -4;
        } else {
            numberInt /= -4;
        }

        result = to_string(remainder) + result;
    }

    return insertZerosBetweenDigits(result);
}

string convertTo2iReal(double number) {
    if (number == 0) return "0";

    double intPart;
    double fracPart = modf(number, &intPart);

    int baseInt = static_cast<int>(intPart);

    string fractionalResult = "";

    if (fracPart != 0.0) {
        if (baseInt > 0) {
            baseInt += 1;
        }
        fracPart = number - floor(number);
        fracPart *= -4;
        int digit = static_cast<int>(floor(fracPart));
        if (digit < 0) digit += 4;

        // Add zero between digits if more digits are needed
        fractionalResult = ".0" + to_string(digit);
    }

    string result = convertIntegerTo2iReal(baseInt) + fractionalResult;


    return result;
}

string convertIntegerTo2iImag(int numberInt) {
    if (numberInt == 0) return "0";

    string result;
    while (numberInt != 0) {
        int remainder = numberInt % -4;

        if (remainder < 0) {
            remainder += 4;
            numberInt = (numberInt - remainder) / -4;
        } else {
            numberInt /= -4;
        }

        result = to_string(remainder) + result;
    }

    return result;
}

string convertTo2iImag(double number) {
    if (number == 0) return "0";

    if (number == 1) return "10.2";

    number/=2;
    double intPart;
    double fracPart = modf(number, &intPart);

    int baseInt = static_cast<int>(intPart);
    string fractionalResult = "";

    if (fracPart != 0.0) {
        if (baseInt > 0) {
            baseInt += 1;
        }
        fracPart = number - floor(number);
        fracPart *= -4;
        int digit = static_cast<int>(floor(fracPart));
        if (digit < 0) digit += 4;
        fractionalResult = "." + to_string(digit);
    }

    string result = convertIntegerTo2iReal(baseInt) + fractionalResult;

    size_t dotPos = result.find('.');
    if (dotPos != string::npos) {
        result.insert(dotPos, "0");
    }
    else {
        result += "0";
    }
    return result;
}

int main() {
    double numberReal;
    cout << "Podaj  rzeczywista: ";
    cin >> numberReal;

     string resultReal = convertTo2iReal(numberReal);
    cout << "Czesc rzeczywista: " << resultReal << endl;

    double numberImaginary;
    cout << "Podaj liczbe urojona: ";
    cin >> numberImaginary;

    string resultImaginary = convertTo2iImag(numberImaginary);
    cout << "Czesc urojona: " << resultImaginary << endl;



    string wynik = polacz_liczby(resultReal, resultImaginary);
    cout << wynik << endl;
    return 0;
}