#pragma once

enum class EGameState
{
    NOT_STARTED,
    PLAYING,
    SPECTATING,
    ENDED,
};

enum class EView
{
    MAIN,
    LOBBY,
    HELP,
    GAME,
    RESULTS,
};

enum class EConnState
{
    CONNECTED,
    CONNECTING,
    DISCONNECTED,
};

enum class MoveDirection
{
    UP,
    DOWN,
    RIGHT,
    LEFT,
    NO_DIR, // need at starting, and when blocked in obstacle
};

struct Position {
    int x;
    int y;

    Position(int x = 0, int y = 0) : x(x), y(y) {}
};