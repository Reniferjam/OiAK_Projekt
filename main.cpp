#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <vector>
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

string addInBase2i(const string& a, const string& b) {
    int maxLen = max(a.length(), b.length());
    vector<int> result(maxLen + 10, 0); // Dłuższy wektor dla przeniesień

    string aPadded = string(maxLen - a.length(), '0') + a;
    string bPadded = string(maxLen - b.length(), '0') + b;

    for (int i = 0; i < maxLen; ++i) {
        result[i] += (aPadded[maxLen - 1 - i] - '0') + (bPadded[maxLen - 1 - i] - '0');
    }

    for (int i = 0; i < result.size(); ++i) {
        while (result[i] > 3) {
            result[i] -= 4;
            result[i + 2] -= 1;
        }
        while (result[i] < 0) {
            result[i] += 4;
            result[i + 2] += 1;
        }
    }

    while (result.size() > 1 && result.back() == 0)
        result.pop_back();

    string sum;
    for (int i = result.size() - 1; i >= 0; --i)
        sum += to_string(result[i]);

    return sum;
}

string subtractInBase2i(const string& a, const string& b) {
    int maxLen = std::max(a.length(), b.length());
    vector<int> result(maxLen + 10, 0); // Dłuższy wektor na przeniesienia

    string aPadded = string(maxLen - a.length(), '0') + a;
    string bPadded = string(maxLen - b.length(), '0') + b;

    for (int i = 0; i < maxLen; ++i) {
        result[i] += (aPadded[maxLen - 1 - i] - '0') - (bPadded[maxLen - 1 - i] - '0');
    }

    for (int i = 0; i < result.size(); ++i) {
        while (result[i] < 0) {
            result[i] += 4;
            result[i + 2] += 1;
        }
        while (result[i] > 3) {
            result[i] -= 4;
            result[i + 2] -= 1;
        }
    }

    while (result.size() > 1 && result.back() == 0)
        result.pop_back();

    string diff;
    for (int i = result.size() - 1; i >= 0; --i)
        diff += to_string(result[i]);

    return diff;
}

string newNumber() {
    double numberReal;
    cout << "Podaj  rzeczywista: ";
    cin >> numberReal;

    string resultReal = convertTo2iReal(numberReal);

    double numberImaginary;
    cout << "Podaj liczbe urojona: ";
    cin >> numberImaginary;

    string resultImaginary = convertTo2iImag(numberImaginary);

    string wynik = polacz_liczby(resultReal, resultImaginary);
    cout << "Wprowadzona liczba: " + wynik << endl;
    return wynik;
}

vector<int> fromString(const string& s) {
    vector<int> digits;
    for (int i = s.size() - 1; i >= 0; --i)
        digits.push_back(s[i] - '0');
    return digits;
}

string toString(const vector<int>& digits) {
    string s;
    bool leading = true;
    for (int i = digits.size() - 1; i >= 0; --i) {
        if (leading && digits[i] == 0) continue;
        leading = false;
        s += (char)(digits[i] + '0');
    }
    return s.empty() ? "0" : s;
}

void normalize(vector<int>& digits) {
    for (size_t i = 0; i < digits.size(); ++i) {
        while (digits[i] > 3) {
            digits[i] -= 4;
            if (i + 2 >= digits.size()) digits.resize(i + 3, 0);
            digits[i + 2] -= 1;
        }
        while (digits[i] < 0) {
            digits[i] += 4;
            if (i + 2 >= digits.size()) digits.resize(i + 3, 0);
            digits[i + 2] += 1;
        }
    }
}

vector<int> multiply2i(const vector<int>& a, const vector<int>& b) {
    vector<int> result(a.size() + b.size(), 0);

    for (size_t i = 0; i < b.size(); ++i) {
        int digitB = b[i];
        for (size_t j = 0; j < a.size(); ++j) {
            result[i + j] += digitB * a[j];
        }
    }

    normalize(result);
    return result;
}

void subtractMenu(string num1,string num2) {
    cout << "  " + num1 << endl;
    cout << " -" + num2 << endl;

    for (int i = 0; i < num2.length() + 2; ++i) {
        cout << "-";
    }
    cout << endl;
    cout << subtractInBase2i(num1, num2) << endl;
    cout << endl;
}

void addMenu(string num1,string num2) {
    cout << "  " + num1 << endl;
    cout << " +" + num2 << endl;

    for (int i = 0; i < num2.length() + 2; ++i) {
        cout << "-";
    }
    cout << endl;
    cout << addInBase2i(num1, num2) << endl;
    cout << endl;
}

void multiplyMenu(string num1,string num2) {
    cout << "  " + num1 << endl;
    cout << " *" + num2 << endl;

    vector<int> a = fromString(num1);
    vector<int> b = fromString(num2);

    vector<int> result = multiply2i(a, b);

    for (int i = 0; i < num2.length() + 2; ++i) {
        cout << "-";
    }
    cout << endl;
    cout << toString(result) << endl;
    cout << endl;
}

void menu() {
    int x = 0;
    string num1;
    string num2;
    string liczba;
    while (true) {
        cout << endl;
        cout << "Menu konwersji 2i" << endl;
        cout << "1.Konwersja liczby na system 2i" << endl;
        cout << "2.Dodawanie w systemie 2i" << endl;
        cout << "3.Odejmowanie w systemie 2i" << endl;
        cout << "4.Mnozenie w systemie 2i" << endl;
        cin >> x;
        switch (x) {
            case 1:
                 liczba = newNumber();
            break;
            case 2:

                cout << "Podaj pierwsza liczbe: ";
                cin >> num1;
                cout << "Podaj druga liczbe: ";
                cin >> num2;
                addMenu(num1, num2);
            break;
            case 3:
                cout << "Podaj pierwsza liczbe: ";
                cin >> num1;
                cout << "Podaj druga liczbe: ";
                cin >> num2;
                subtractMenu(num1, num2);
            break;
            case 4:
                cout << "Podaj pierwsza liczbe: ";
                cin >> num1;
                cout << "Podaj druga liczbe: ";
                cin >> num2;
                multiplyMenu(num1, num2);
            break;
            default:
                return;
        }
    }
}
int main() {
    // string num1 = newNumber();
    // string num2 = newNumber();
    // string num1 = "11201";
    // string num2 = "20121";
    //
    // subtractMenu(num1, num2);
    // addMenu(num1, num2);
    //
    // multiplyMenu(num1, num2);

    menu();
    return 0;
}