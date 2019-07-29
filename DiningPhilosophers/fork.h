#pragma once

class Fork {
    inline static unsigned idCounter;
    bool dirty = true;
public:
    const unsigned id;
    Fork() : id(idCounter++){}

    void clean() noexcept {
        dirty = false;
    }

    bool isDirty() const noexcept {
        return dirty;
    }

    bool isClean() const noexcept {
        return !isDirty();
    }

    void use() noexcept {
        dirty = true;
    }
};
