#pragma once

class Request {
public:
    const unsigned senderId;
    const unsigned requestedForkId;
    Request(const unsigned philosopherId, const unsigned requestedForkId) : senderId(philosopherId), requestedForkId(requestedForkId) {}
};
