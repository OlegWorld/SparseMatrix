#pragma once

#include <unordered_map>

namespace std {
    template <> struct hash<std::pair<size_t, size_t>> {
        using argument_type = std::pair<size_t, size_t>;
        using result_type = size_t;

        result_type operator()(const argument_type& s) const noexcept
        {
            const result_type h1 ( std::hash<size_t>{}(s.first) );
            const result_type h2 ( std::hash<size_t>{}(s.second) );
            return h1 + (h2 << 32);
        }
    };
}

template <class T, T Val>
class Matrix {
    using low_layer_map = std::unordered_map<std::pair<size_t, size_t>, T>;

public:
    Matrix() noexcept = default;
    Matrix(const Matrix& rhs) = default;
    Matrix(Matrix&& rhs) noexcept = default;
    ~Matrix() = default;

    Matrix& operator=(const Matrix& rhs) = default;
    Matrix& operator=(Matrix&& rhs) noexcept = default;

    size_t size() const noexcept {
        return m_map.size();
    }

    T& operator()(size_t x, size_t y, T def = Val) noexcept {
        auto p = std::make_pair(x, y);
        if (!m_map.count(p))
            return def;
        else
            return m_map.at(p);
    }

    const T& operator()(size_t x, size_t y, T def = Val) const noexcept {
        auto p = std::make_pair(x, y);
        if (!m_map.count(p))
            return def;
        else
            return m_map.at(p);
    }

    const T& get_element(size_t x, size_t y) const {
        auto p = std::make_pair(x, y);
        if (!m_map.count(p))
            return m_default;
        else
            return m_map.at(p);
    }

private:
    low_layer_map m_map;
    const T m_default = Val;
};