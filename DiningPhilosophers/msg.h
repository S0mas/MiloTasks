#pragma once
#include "fork.h"

class Msg {
public:
    const unsigned receiverId;
    Fork* fork;
    Msg(const unsigned philosopherId, Fork* fork) : receiverId(philosopherId), fork(fork) {}
};
