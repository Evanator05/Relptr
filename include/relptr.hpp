#pragma once
#include <vector>
#include <cinttypes>
#include <limits>

template<typename Tag, typename T>
struct RelptrBase {
    static inline T* base = nullptr;

    static void set_base(T* b) { base = b; }
    static T* get_base() { return base; }
};

template<typename Tag, typename T>
struct RelptrBaseVector {
    static inline std::vector<T>* vec = nullptr;

    static void set_base(std::vector<T>& v) { vec = &v; }
    static T* get_base() { return vec ? vec->data() : nullptr; }
};

template<typename T, typename BaseProvider, typename I = uint32_t>
class Relptr {
public:
    I offset;

    static constexpr I null_value =
        std::numeric_limits<I>::max();

    Relptr(I i) : offset(i) {}
    Relptr() : offset(null_value) {}

    T* Resolve() const {
        if (offset == null_value) return nullptr;

        T* base = BaseProvider::get_base();
        return base + offset;
    }

    T* operator->() const { return Resolve(); }
    T& operator*() const { return *Resolve(); }
    operator T*() const { return Resolve(); }
};