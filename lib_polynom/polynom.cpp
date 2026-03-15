#include "polynom.h"

Polynom::Polynom() {}

Polynom::Polynom(const Polynom& other) : _items(other._items) {}

Polynom::Polynom(const Monom& m) {
    if (m.getCoeff() != 0) {
        _items.push_back(m);
    }
}

Polynom& Polynom::operator=(const Polynom& other) {
    if (this != &other) {
        while (!_items.is_empty()) {
            _items.pop_front();
        }
        for (auto it = other._items.begin(); it != other._items.end(); ++it) {
            _items.push_back(*it);
        }
    }
    return *this;
}

Polynom& Polynom::operator+=(const Polynom& other) {
    List<Monom> res;
    auto it1 = _items.begin();
    auto it2 = other._items.begin();
    auto end1 = _items.end();
    auto end2 = other._items.end();

    while (it1 != end1 || it2 != end2) {
        if (it1 != end1 && (it2 == end2 || (*it1) > (*it2))) {
            res.push_back(*it1);
            ++it1;
        }
        else if (it2 != end2 && (it1 == end1 || (*it2) > (*it1))) {
            res.push_back(*it2);
            ++it2;
        }
        else {
            Monom sum = (*it1) + (*it2);
            if (sum.getCoeff() != 0) {
                res.push_back(sum);
            }
            ++it1;
            ++it2;
        }
    }

    while (!_items.is_empty()) {
        _items.pop_front();
    }

    for (auto it = res.begin(); it != res.end(); ++it) {
        _items.push_back(*it);
    }

    return *this;
}

Polynom& Polynom::operator-=(const Polynom& other) {
    List<Monom> res;
    auto it1 = _items.begin();
    auto it2 = other._items.begin();
    auto end1 = _items.end();
    auto end2 = other._items.end();

    while (it1 != end1 || it2 != end2) {
        if (it1 != end1 && (it2 == end2 || (*it1) > (*it2))) {
            res.push_back(*it1);
            ++it1;
        }
        else if (it2 != end2 && (it1 == end1 || (*it2) > (*it1))) {
            Monom neg = *it2;
            Monom neg_monom(-neg.getCoeff(), neg.getPowers());
            res.push_back(neg_monom);
            ++it2;
        }
        else {
            Monom diff = (*it1) - (*it2);
            if (diff.getCoeff() != 0) {
                res.push_back(diff);
            }
            ++it1;
            ++it2;
        }
    }
    while (!_items.is_empty()) {
        _items.pop_front();
    }

    for (auto it = res.begin(); it != res.end(); ++it) {
        _items.push_back(*it);
    }

    return *this;
}

Polynom& Polynom::operator*=(const Monom& m) {
    if (m.getCoeff() == 0) {
        while (!_items.is_empty()) {
            _items.pop_front();
        }
        return *this;
    }

    List<Monom> res;
    for (auto it = _items.begin(); it != _items.end(); ++it) {
        Monom product = (*it) * m;
        res.push_back(product);
    }

    while (!_items.is_empty()) {
        _items.pop_front();
    }

    for (auto it = res.begin(); it != res.end(); ++it) {
        _items.push_back(*it);
    }

    return *this;
}

Polynom& Polynom::operator/=(const Monom& m) {
    if (m.getCoeff() == 0) {
        throw std::logic_error("Division by zero");
    }

    List<Monom> res;
    for (auto it = _items.begin(); it != _items.end(); ++it) {
        Monom quotient = (*it) / m;
        res.push_back(quotient);
    }

    while (!_items.is_empty()) {
        _items.pop_front();
    }

    for (auto it = res.begin(); it != res.end(); ++it) {
        _items.push_back(*it);
    }

    return *this;
}

Polynom Polynom::operator+(const Polynom& other) const {
    return Polynom(*this) += other;
}

Polynom Polynom::operator-(const Polynom& other) const {
    return Polynom(*this) -= other;
}

Polynom Polynom::operator*(const Monom& m) const {
    return Polynom(*this) *= m;
}

Polynom Polynom::operator/(const Monom& m) const {
    return Polynom(*this) /= m;
}

Polynom operator+(const Monom& m, const Polynom& p) {
    return Polynom(m) + p;
}

Polynom operator*(const Monom& m, const Polynom& p) {
    Polynom result(p);
    return result *= m;
}

Polynom operator-(const Monom& m, const Polynom& p) {
    return Polynom(m) - p;
}

std::ostream& operator<<(std::ostream& os, const Polynom& p) {
    os << p.to_string();
    return os;
}

std::istream& operator>>(std::istream& is, Polynom& p) {
    std::string str;
    std::getline(is, str);

    while (!p._items.is_empty()) {
        p._items.pop_front();
    }

    size_t pos = 0;
    size_t start = 0;

    while (pos <= str.size()) {
        if (pos == str.size() || str[pos] == '+' || str[pos] == '-') {
            if (pos > start) {
                std::string monom_str = str.substr(start, pos - start);
                if (!monom_str.empty()) {
                    try {
                        Monom m = Monom::parse(monom_str);
                        p += m;
                    }
                    catch (const std::logic_error& e) {
                    }
                }
            }

            if (pos < str.size()) {
                start = pos;
            }
            pos++;
        }
        else {
            pos++;
        }
    }

    return is;
}

void Polynom::sort() {
    if (_items.count() <= 1) return;

    List<Monom> sorted;

    for (auto it = _items.begin(); it != _items.end(); ++it) {
        bool inserted = false;

        if (sorted.is_empty()) {
            sorted.push_back(*it);
            continue;
        }

        auto sorted_it = sorted.begin();
        size_t pos = 0;

        while (sorted_it != sorted.end()) {
            if (*it > *sorted_it) {
                if (pos == 0) {
                    sorted.push_front(*it);
                }
                else {
                    auto prev = sorted.begin();
                    for (size_t i = 0; i < pos - 1; i++) {
                        ++prev;
                    }
                    Node<Monom>* prev_node = nullptr;
                    Node<Monom>* curr_node = sorted.head();
                    for (size_t i = 0; i < pos; i++) {
                        prev_node = curr_node;
                        curr_node = curr_node->next;
                    }
                    sorted.insert(prev_node, *it);
                }
                inserted = true;
                break;
            }
            ++sorted_it;
            ++pos;
        }

        if (!inserted) {
            sorted.push_back(*it);
        }
    }

    while (!_items.is_empty()) {
        _items.pop_front();
    }

    for (auto it = sorted.begin(); it != sorted.end(); ++it) {
        _items.push_back(*it);
    }
}

bool Polynom::is_sorted() const {
    if (_items.count() <= 1) return true;

    auto prev = _items.begin();
    auto curr = _items.begin();
    ++curr;

    while (curr != _items.end()) {
        if (*prev < *curr) return false;
        prev = curr;
        ++curr;
    }
    return true;
}

void Polynom::remove_zero_monoms() {
    List<Monom> res;

    for (auto it = _items.begin(); it != _items.end(); ++it) {
        if (it->getCoeff() != 0) {
            res.push_back(*it);
        }
    }

    while (!_items.is_empty()) {
        _items.pop_front();
    }

    for (auto it = res.begin(); it != res.end(); ++it) {
        _items.push_back(*it);
    }
}

void Polynom::insert_monom(const Monom& monom) {
    if (monom.getCoeff() == 0) return;

    List<Monom> res;
    bool inserted = false;

    for (auto it = _items.begin(); it != _items.end(); ++it) {
        if (!inserted && *it == monom) {
            Monom sum = *it + monom;
            if (sum.getCoeff() != 0) {
                res.push_back(sum);
            }
            inserted = true;
        }
        else if (!inserted && *it > monom) {
            res.push_back(monom);
            res.push_back(*it);
            inserted = true;
        }
        else {
            res.push_back(*it);
        }
    }

    if (!inserted) {
        res.push_back(monom);
    }

    while (!_items.is_empty()) {
        _items.pop_front();
    }

    for (auto it = res.begin(); it != res.end(); ++it) {
        _items.push_back(*it);
    }
}

double Polynom::calculate(const double* values) const {
    double result = 0.0;
    for (auto it = _items.begin(); it != _items.end(); ++it) {
        double term = it->getCoeff();
        const int* powers = it->getPowers();

        for (int i = 0; i < VARS_COUNT; i++) {
            if (powers[i] > 0) {
                term *= std::pow(values[i], powers[i]);
            }
        }

        result += term;
    }
    return result;
}

bool Polynom::is_zero() const {
    return _items.is_empty();
}

std::string Polynom::to_string() const {
    if (_items.is_empty()) {
        return "0";
    }

    std::stringstream ss;
    bool first = true;

    for (auto it = _items.begin(); it != _items.end(); ++it) {
        double coeff = it->getCoeff();
        const int* powers = it->getPowers();

        if (!first && coeff > 0) {
            ss << " + ";
        }
        else if (!first && coeff < 0) {
            ss << " - ";
            coeff = -coeff;  
        }
        else if (first && coeff < 0) {
            ss << "-";
            coeff = -coeff;
        }

        bool has_vars = false;
        for (int i = 0; i < VARS_COUNT; i++) {
            if (powers[i] > 0) {
                has_vars = true;
                break;
            }
        }

        if (std::abs(coeff - 1.0) > 1e-10 || !has_vars) {
            ss << std::noshowpoint << coeff;
        }

        const char vars[] = { 'x', 'y', 'z' };
        for (int i = 0; i < VARS_COUNT; i++) {
            if (powers[i] > 0) {
                ss << vars[i];
                if (powers[i] > 1) {
                    ss << "^" << powers[i];
                }
            }
        }

        first = false;
    }

    return ss.str();
}

size_t Polynom::size() const { return _items.count(); }
