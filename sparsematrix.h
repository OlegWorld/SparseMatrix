#pragma once

#include <unordered_map>
#include <tuple>
#include <iostream>

namespace std {
    template <> struct hash<std::pair<size_t, size_t>> {
        using argument_type = std::pair<size_t, size_t>;
        using result_type = size_t;

        result_type operator()(const argument_type& s) const noexcept
        {
            const result_type h1 ( std::hash<size_t>{}(s.first) );
            const result_type h2 ( std::hash<size_t>{}(s.second) );
            return h1 + (h2 << 32u);
        }
    };
}

template <class T, T DefVal>
class Matrix {
    using low_layer_map = std::unordered_map<std::pair<size_t, size_t>, T>;

public:
    class Value {
    public:
        Value(Matrix& parent, std::pair<size_t, size_t>&& coord)
        :   m_parent(parent),
            m_coordinates(std::move(coord))
        { }

        Value& operator=(const T& val) {
            m_parent.set_value(m_coordinates, val);

            return *this;
        }

        bool operator==(const T& val) const noexcept {
            return m_parent.get_value(m_coordinates) == val;
        }

        T get() const noexcept {
            return m_parent.get_value(m_coordinates);
        }

    private:
        Matrix& m_parent;
        std::pair<size_t, size_t> m_coordinates;
    };

    class iterator {
    public:
        explicit iterator(typename low_layer_map::iterator&& it)
        :   m_it(std::move(it))
        { }

        std::tuple<size_t, size_t, T> operator*() const {
            return std::make_tuple(m_it->first.first,
                                   m_it->first.second,
                                   m_it->second);
        }

        iterator& operator++() {
            ++m_it;
            return *this;
        }

        bool operator!=(const iterator& rhs) const noexcept {
            return m_it != rhs.m_it;
        }

    private:
        typename low_layer_map::iterator m_it;
    };

    Matrix() noexcept = default;
    Matrix(const Matrix& rhs) = default;
    Matrix(Matrix&& rhs) noexcept = default;
    ~Matrix() = default;

    Matrix& operator=(const Matrix& rhs) = default;
    Matrix& operator=(Matrix&& rhs) noexcept = default;

    iterator begin() {
        return iterator(m_map.begin());
    }

    iterator end() {
        return iterator(m_map.end());
    }

    size_t size() const noexcept {
        return m_map.size();
    }

    Value operator()(size_t x, size_t y) {
        return Value(*this, std::make_pair(x, y));
    }

    T get_value(const std::pair<size_t, size_t>& coord) const noexcept {
        if (!m_map.count(coord))
            return DefVal;
        else
            return m_map.at(coord);
    }

    void set_value(const std::pair<size_t, size_t>& coord, const T& val) {
        if (val == DefVal) {
            m_map.erase(coord);
        } else {
            m_map[coord] = val;
        }
    }

private:
    low_layer_map m_map;
};

template <class T, T DefVal>
void print_submatrix(Matrix<T, DefVal>& m, size_t x1, size_t y1, size_t x2, size_t y2) {
    for(size_t i = x1; i < x2 + 1; i++) {
        for(size_t j = y1; j < y2 + 1; j++) {
            std::cout << m(i, j).get() << ' ';
        }
        std::cout << std::endl;
    }
}

template <class T, T DefVal>
void print_cells(Matrix<T, DefVal>& m) {
    for (const auto& c : m)
    {
        size_t x, y;
        int v;
        std::tie(x, y, v) = c;
        std::cout << "matrix(" << x << ", " << y << ") = " << v << std::endl;
    }
}