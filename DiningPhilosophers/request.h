#pragma once
#include <vector>
#include <QMetaType>

struct Request {
    int sender;
    std::vector<int> resourceIds;
    Request(){}
    Request(const int sender, const std::vector<int>& resourceIds) : sender(sender), resourceIds(resourceIds) {}
};

Q_DECLARE_METATYPE(Request);
