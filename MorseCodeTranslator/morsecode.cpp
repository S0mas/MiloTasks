#include "morsecode.h"
/*!
 * Max supported size of morse code signs with this hash function is 8
 *             8bit dash part  8bit dot part
 * 16bit int      00001110        00010001
 *             ->     ---     +      .   .
 *             ->          .---.
 */
uint16_t MorseCode::hash(const QString &morseCode) const noexcept {
    uint16_t result = 0;
    for(auto index = 0u; index < morseCode.size(); ++index)
        if(morseCode[index] == '.')
            result |= (1 << index);
        else if(morseCode[index] == '-')
            result |= (1 << (index+8));
    return result;
}

QString MorseCode::getMorseCode(const char &sign) const noexcept {
    return morseSigns[static_cast<uint8_t>(sign)];
}

QChar MorseCode::getNormalSign(const QString &morseCode) const noexcept {
    return QChar::fromLatin1(normalSigns[hash(morseCode)]);
}

/*!
 * At the end of each morse code element, there should be ' ' and two ' ' between words in translation.
 * Therefore ' ' should be translated to ' ' and last ' ' in translation should be erased (if it is not empty text)
 */
MorseCode::MorseCode() {
    for(auto& element : morseSigns)
        element = "";
    morseSigns['A'] = ".- ";
    morseSigns['a'] = ".- ";

    morseSigns['B'] = "-... ";
    morseSigns['b'] = "-... ";

    morseSigns['C'] = "-.-. ";
    morseSigns['c'] = "-.-. ";

    morseSigns['D'] = "-.. ";
    morseSigns['d'] = "-.. ";

    morseSigns['E'] = ". ";
    morseSigns['e'] = ". ";

    morseSigns['F'] = "..-. ";
    morseSigns['f'] = "..-. ";

    morseSigns['G'] = "--. ";
    morseSigns['g'] = "--. ";

    morseSigns['H'] = ".... ";
    morseSigns['h'] = ".... ";

    morseSigns['I'] = ".. ";
    morseSigns['i'] = ".. ";

    morseSigns['J'] = ".--- ";
    morseSigns['j'] = ".--- ";

    morseSigns['K'] = "-.- ";
    morseSigns['k'] = "-.- ";

    morseSigns['L'] = ".-.. ";
    morseSigns['l'] = ".-.. ";

    morseSigns['M'] = "-- ";
    morseSigns['m'] = "-- ";

    morseSigns['N'] = "-. ";
    morseSigns['n'] = "-. ";

    morseSigns['O'] = "--- ";
    morseSigns['o'] = "--- ";

    morseSigns['P'] = ".--. ";
    morseSigns['p'] = ".--. ";

    morseSigns['Q'] = "--.- ";
    morseSigns['q'] = "--.- ";

    morseSigns['R'] = ".-. ";
    morseSigns['r'] = ".-. ";

    morseSigns['S'] = "... ";
    morseSigns['s'] = "... ";

    morseSigns['T'] = "- ";
    morseSigns['t'] = "- ";

    morseSigns['U'] = "..- ";
    morseSigns['u'] = "..- ";

    morseSigns['V'] = "...- ";
    morseSigns['v'] = "...- ";

    morseSigns['W'] = ".-- ";
    morseSigns['w'] = ".-- ";

    morseSigns['X'] = "-..- ";
    morseSigns['x'] = "-..- ";

    morseSigns['Y'] = "-.-- ";
    morseSigns['y'] = "-.-- ";

    morseSigns['Z'] = "--.. ";
    morseSigns['z'] = "--.. ";

    morseSigns['1'] = ".---- ";

    morseSigns['2'] = "..--- ";

    morseSigns['3'] = "...-- ";

    morseSigns['4'] = "....- ";

    morseSigns['5'] = "..... ";

    morseSigns['6'] = "-.... ";

    morseSigns['7'] = "--... ";

    morseSigns['8'] = "---.. ";

    morseSigns['9'] = "----. ";

    morseSigns['0'] = "----- ";

    morseSigns[','] = "--..-- ";

    morseSigns['?'] = "..--.. ";

    morseSigns['.'] = ".--.--.- ";

    morseSigns['!'] = "-.-.-- ";

    morseSigns['='] = "--...- ";

    morseSigns['+'] = ".--.-. ";

    morseSigns['-'] = "--....- ";

    morseSigns['_'] = "..----.- ";

    morseSigns['"'] = ".--..-. ";

    morseSigns['$'] = "...--..- ";

    morseSigns['&'] = ".--... ";

    morseSigns['/'] = "--..--.- ";

    morseSigns[' '] = " ";

    for(auto& element : normalSigns)
        element = 0;

    for(auto asciiCode = 0u; asciiCode < morseSigns.size(); ++asciiCode)
        normalSigns[hash(morseSigns[asciiCode])] = static_cast<char>(asciiCode);
}

QString MorseCode::translateToMorseCode(const QString &normalText) const {
    QString result;
    result.reserve(normalText.size()*5);
    for(auto const& c : normalText)
        result += getMorseCode(c.toLatin1());
    if(result.size() != 0)
        result.chop(1);
    return result;
}

QString MorseCode::translateToNormalText(const QString &morseCode) const {
    QString result;
    result.reserve(morseCode.size()/5);
    QString letterCode;
    letterCode.reserve(7);
    bool wordEnd = false;
    for(auto const& c : morseCode){
        if(c != ' '){
            wordEnd = false;
            letterCode += c;
        }
        else {
            if(!wordEnd) {
                wordEnd = true;
                result += getNormalSign(letterCode);
                letterCode.clear();
            }
            else {
                wordEnd = false;
                result += ' ';
            }
        }
    }

    if(letterCode.size() != 0)
        result += getNormalSign(letterCode);
    return result;
}
