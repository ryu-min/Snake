#ifndef COMMON_H
#define COMMON_H

#include <QString>

namespace SnakeGame
{

    const int DOT_WIDTH   = 20;
    const int DOT_HEIGH   = 20;
    const int FIELD_WIDTH = 20;
    const int FIELD_HEIGH = 20;

    enum class SnakeLevel
    {
        EASY,
        MEDIUM,
        HARD,
        UNKNOWN,
    };

    inline QString levelToString(SnakeLevel level)
    {
        switch (level)
        {
        case SnakeLevel::EASY:      return "Легкий";
        case SnakeLevel::MEDIUM:    return "Средний";
        case SnakeLevel::HARD:      return "Сложный";
        case SnakeLevel::UNKNOWN:   return "Неизвестный уровень";
        default:                    return "";
        }
    }

    inline int delayByLevel(SnakeLevel level)
    {
        switch (level)
        {
            case SnakeLevel::EASY:      return 220;
            case SnakeLevel::MEDIUM:    return 160;
            case SnakeLevel::HARD:      return 110;
            case SnakeLevel::UNKNOWN:   return 220;
            default: return 220;
        }
    }

    inline SnakeLevel stringToLevel(const QString & level)
    {
        if      (level.toLower() == "легкий")   return SnakeLevel::EASY;
        else if (level.toLower() == "средний")  return SnakeLevel::MEDIUM;
        else if (level.toLower() == "сложный")  return SnakeLevel::HARD;
        else                                    return SnakeLevel::UNKNOWN;
    }


}


#endif // COMMON_H
