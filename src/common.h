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
};