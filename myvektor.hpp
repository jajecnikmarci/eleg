//
// Created by Jajecnik Marcell on 2023. 05. 04..
//

#ifndef SKELETON_MYVEKTOR_HPP
#define SKELETON_MYVEKTOR_HPP

#include <iostream>
#include <cstring>
#include <stdexcept>

/**@brief Indexelhetőséghez std::vektor mintájára saját vektor template
 *
 * @tparam T Tárolt objektumok fajtája
 *
 * @param m_buffer Az adat buffer elejére mutató pointer
 * @param m_capacity A maximális kapacitás a jelenlegi foglalt területtel
 * @param m_size A jelenleg tárolt objektumok száma
 */
template<typename T>
class MyVector {
private:

    T* m_buffer;

    size_t m_capacity;

    size_t m_size;

    /**@brief Helyfoglalás a tárolandó adatoknak (privát mivel kívülről nem szükséges az elérése
     *
     * @param new_capacity Az új kívánt kapacitás mérete
     */
    void reserve(size_t new_capacity) {
        if (new_capacity <= m_capacity) {
            return;
        }
        T* new_buffer = new T[new_capacity];
        memcpy(new_buffer, m_buffer, m_size * sizeof(T));
        delete[] m_buffer;
        m_buffer = new_buffer;
        m_capacity = new_capacity;
    }

public:
    /**@brief Alapértékes konstruktor
     *
     */
    MyVector(): m_capacity(10), m_size(0) {
        m_buffer = new T[m_capacity];
    }

    /**@brief Bejövő objektum tárolása
     *
     * @param value Bejövő objektum
     */
    void push_back(T value) {
        if (m_size == m_capacity) {
            reserve(m_capacity * 2);
        }
        m_buffer[m_size] = value;
        m_size++;
    }

    /**@brief Visszaadja a tárolt objektumok számát
     *
     * @return tárolt objektumok száma
     */
    size_t size() const {
        return m_size;
    }

    /**@brief Visszaadja a jelenlegi kapacitást
     *
     * @return jelenlegi kapacitás
     */
    size_t capacity() const {
        return m_capacity;
    }

    /**@brief Egy elem eltávolítása a tárolt objektumok közül egy bizonyos helyről
     *
     * @param pos Az eltávolítandó objektum indexe
     */
    void erase(size_t pos) {
        if (pos >= m_size) {
            return;
        }
        for (size_t i = pos; i < m_size - 1; i++) {
            m_buffer[i] = m_buffer[i + 1];
        }
        m_size--;
    }

    /**@brief Utolsó objektum eltávolítása
     *
     */
    void pop_back() {
        if (m_size > 0) {
            m_size--;
        }
    }

    /**@brief [] operátor az indexelhetőséghez
     *
     * @param i Az elérni kívánt objektum indexe
     * @return Visszaadandó objektum
     */
    T& operator[](size_t i) {
        if ((i<0 || i>=m_size)) throw std::range_error("Index error");
        return m_buffer[i];
    }

    /**@brief [] operátor az indexelhetőséghez constans formában is
     *
     * @param i Az elérni kívánt objektum indexe
     * @return Visszaadandó objektum
     */
    const T& operator[](size_t i) const {
        if ((i<0 || i>=m_size)) throw std::range_error("Index error");
        return m_buffer[i];
    };

    /**@brief Destruktor
     *
     */
    ~MyVector() {
        delete[] m_buffer;
    }
};


#endif //SKELETON_MYVEKTOR_HPP
