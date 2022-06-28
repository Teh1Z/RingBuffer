#ifndef RINGBUFFER_RINGBUFFER_H
#define RINGBUFFER_RINGBUFFER_H

#include <iostream>
#include <stdexcept>


template<typename T>
class RingBuffer {
private:
    T* _buf;
    size_t _size;
    T* _pHead;
    T* _pTail;
    bool _empty;

public:
    // default constructor
    explicit RingBuffer(size_t sz) {
        if (!sz) { std::invalid_argument(""); }
        _size = sz;
        _buf = new T[_size];
        _pHead = _buf;
        _pTail = _buf;
        _empty = true;
    }

    // copy constructor
    RingBuffer(const RingBuffer& other) {
        _size = other.getCount();
        _empty = other.isEmpty();
        _buf = new T[_size];
        std::copy(other._buf, other._buf + other.getCount(), _buf);
        _pHead = _buf + (other._pHead - other._buf);
        _pTail = _buf + (other._pTail - other._buf);
    }

    inline ~RingBuffer() { delete[] _buf; }

    inline size_t getSize() const { return _size; }

    size_t getCount() const {
        if (_pHead == _pTail) { return _size * !_empty; }
        if (_pHead < _pTail) { return _pTail - _pHead; }
        return _size - (_pHead - _pTail);
    }

    inline size_t getFree() const { return _size - getCount(); }

    inline bool isEmpty() const { return _empty; }

    inline bool isFull() const { return _size == getCount(); }

    void push(const T& value) {
        if (isFull()) { throw std::out_of_range(""); }
        *_pTail = value;
        _pTail++;
        if (_empty) { _empty = false; }
        if (_pTail == _buf + _size) { _pTail = _buf; }
    }

    T& front() {
        if (isEmpty()) { throw std::out_of_range(""); }
        return *_pHead;
    }

    const T& front() const {
        if (isEmpty()) { throw std::out_of_range(""); }
        return *_pHead;
    }

    T& back() {
        if (isEmpty()) { throw std::out_of_range(""); }
        if (_pTail - 1 < _buf) { return *(_buf + _size - 1); }
        return *(_pTail - 1);
    }

    const T& back() const {
        if (isEmpty()) { throw std::out_of_range(""); }
        if (_pTail - 1 < _buf) { return *(_buf + _size - 1); }
        return *(_pTail - 1);
    }

    // returns the oldest element (*_pHead)
    T pop() {
        if (isEmpty()) { throw std::out_of_range(""); }
        T value = *_pHead;
        _pHead++;
        if (_pHead == _buf + _size) { _pHead = _buf; }
        if (_pHead == _pTail) { _empty = true; }
        return value;
    }

    RingBuffer& operator=(const RingBuffer& rhv) {
        RingBuffer temp(rhv);
        RingBuffer::swap(*this, temp);
        return *this;
    }

private:
    static void swap(RingBuffer& lhv, RingBuffer& rhv) {
        T* _tempBuf = lhv._buf;
        T* _tempHead = lhv._pHead;
        T* _tempTail = lhv._pTail;
        bool _tempEmpty = lhv.isEmpty();
        size_t _tempSize = lhv.getCount();

        lhv._buf = rhv._buf;
        lhv._pHead = rhv._pHead;
        lhv._pTail = rhv._pTail;
        lhv._empty = rhv.isEmpty();
        lhv._size = rhv.getCount();

        rhv._buf = _tempBuf;
        rhv._pHead = _tempHead;
        rhv._pTail = _tempTail;
        rhv._empty = _tempEmpty;
        rhv._size = _tempSize;
    }
};

#endif //RINGBUFFER_RINGBUFFER_H
