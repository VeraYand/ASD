#include "monom.h"

std::ostream& operator<< (std::ostream& out, const Monom& monom) {
    out << monom.to_string();
    return out;
}

std::istream& operator>> (std::istream& in, Monom& monom) {
    std::string m;
    in >> m;
    monom = Monom::parse(m);
    return in;
}


Monom::Monom(const Monom& other) : _coeff(other._coeff) {
    for (int i = 0; i < VARS_COUNT; i++) {
        _powers[i] = other._powers[i];
    }
}

Monom::Monom(double coeff, const int* powers) : _coeff(coeff) {
    for (int i = 0; i < VARS_COUNT; i++) {
        _powers[i] = (powers ? powers[i] : 0);
    }
}

bool Monom::operator>(const Monom& other) const {
    for (int i = 0; i < VARS_COUNT; i++) {
        if (_powers[i] > other._powers[i]) return true;
        if (_powers[i] < other._powers[i]) return false;
    }
    return false;
}

bool Monom::operator<(const Monom& other) const {
    return other > *this;
}

bool Monom::operator==(const Monom& other) const {
    for (int i = 0; i < VARS_COUNT; i++)
        if (_powers[i] != other._powers[i]) return false;
    return true;
}

bool Monom::operator!=(const Monom& other) const {
    return !(*this == other);
}

Monom Monom::operator+(const Monom& other) const {
    if (*this != other)
        throw std::logic_error("Degrees must match for addition");
    return Monom(_coeff + other._coeff, _powers);
}

Monom Monom::operator-(const Monom& other) const {
    if (*this != other)
        throw std::logic_error("Degrees must match for subtraction");
    return Monom(_coeff - other._coeff, _powers);
}

Monom Monom::operator*(const Monom& other) const {
    int res_powers[VARS_COUNT];
    for (int i = 0; i < VARS_COUNT; i++)
        res_powers[i] = _powers[i] + other._powers[i];
    return Monom(_coeff * other._coeff, res_powers);
}

Monom Monom::operator/(const Monom& other) const {
    if (other._coeff == 0)
        throw std::logic_error("Division by zero");

    int res_powers[VARS_COUNT];
    for (int i = 0; i < VARS_COUNT; i++) {
        if (_powers[i] < other._powers[i])
            throw std::logic_error("Resulting power would be negative");
        res_powers[i] = _powers[i] - other._powers[i];
    }
    return Monom(_coeff / other._coeff, res_powers);
}

Monom& Monom::operator*=(double val) {
    _coeff *= val;
    return *this;
}

Monom& Monom::operator/=(double val) {
    if (val == 0) throw std::logic_error("Division by zero");
    _coeff /= val;
    return *this;
}


double Monom::calculate(const double values[VARS_COUNT]){
    double res = _coeff;
    for (int i = 0; i < VARS_COUNT; i++) {
        res *= pow(values[i], _powers[i]);
    }
    return res;
}

std::string Monom::read_num(const std::string& str, int& pos) {
    std::string num;
    while (pos < str.size() && (std::isdigit(str[pos]) || str[pos] == '.')) {
        num += str[pos];
        pos++;
    }
    return num;
}

Monom Monom::parse(const std::string& str) {
    if (str.empty()) throw std::logic_error("Empty monom");

    double coeff = 1.0;
    int powers[] = { 0, 0, 0 };
    bool found[] = { false, false, false };
    int sign = 1;
    int pos = 0;

    if (str[pos] == '-') {
        sign = -1;
        pos++;
    }
    else if (str[pos] == '+') {
        pos++;
    }

    if (pos < str.size() && (std::isdigit(str[pos]) || str[pos] == '.')) {
        std::string num_str = read_num(str, pos);
        if (!num_str.empty()) {
            coeff = std::stod(num_str) * sign;
        }
        else {
            coeff = sign;
        }
    }
    else {
        coeff = sign;
    }

    while (pos < str.size()) {
        int var;
        char var_char = str[pos];

        if (var_char == 'x' || var_char == 'X') var = 0;
        else if (var_char == 'y' || var_char == 'Y') var = 1;
        else if (var_char == 'z' || var_char == 'Z') var = 2;
        else throw std::logic_error("Invalid character in monom");

        if (found[var]) throw std::logic_error("Variable has been already met");
        found[var] = true;
        pos++;

        int power = 1;
        if (pos < str.size() && str[pos] == '^') {
            pos++;
            if (pos < str.size() && str[pos] == '-') {
                throw std::logic_error("Power can't be negative");
            }

            std::string num_str = read_num(str, pos);
            if (num_str.empty()) {
                throw std::logic_error("Invalid number input for power");
            }
            if (num_str.find('.') != std::string::npos) {
                throw std::logic_error("Power must be integer");
            }
            power = std::stoi(num_str);
            if (power < 0) throw std::logic_error("Power can't be negative");
        }
        powers[var] += power;
    }

    return Monom(coeff, powers);
}

std::string Monom::to_string() const {
    std::stringstream ss;
    if (_coeff == 0) {
        return "0";
    }

    if (_coeff != 1 || (_powers[0] == 0 && _powers[1] == 0 && _powers[2] == 0)) {
        ss << _coeff;
    }
    else if (_coeff == -1) {
        ss << "-";
    }

    char vars[] = { 'x', 'y', 'z' };
    for (int i = 0; i < VARS_COUNT; i++) {
        if (_powers[i] > 0) {
            ss << vars[i];
            if (_powers[i] > 1) {
                ss << "^" << _powers[i];
            }
        }
    }

    return ss.str();
}
