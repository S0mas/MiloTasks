#pragma once
#include <array>
#include <limits>
#include <QObject>
#include <QString>

class MorseCode : public QObject {
    Q_OBJECT
    std::array<char, std::numeric_limits<uint16_t>::max()+1> normalSigns;
    std::array<QString, std::numeric_limits<uint8_t>::max()+1> morseSigns;
    uint16_t hash(const QString& morseCode) const noexcept;
    QString getMorseCode(const char& sign) const noexcept;
    QChar getNormalSign(const QString& morseCode) const noexcept;
public:
    MorseCode();
    Q_INVOKABLE QString translateToMorseCode(const QString& normalText) const;
    Q_INVOKABLE QString translateToNormalText(const QString& morseCode) const;
};
