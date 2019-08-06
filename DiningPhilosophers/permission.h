#pragma once
#include <vector>
#include <QMetaType>

struct Permission {
    int sender;
    std::vector<int> resourceIds;
    Permission(){}
    Permission(const int sender, const std::vector<int>& resourceIds) : sender(sender), resourceIds(resourceIds) {}
};

Q_DECLARE_METATYPE(Permission);
