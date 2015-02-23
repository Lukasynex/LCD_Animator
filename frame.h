#ifndef FRAME_H
#define FRAME_H

#include <stdint.h>

#define FRAME_ROWS                  17
#define FRAME_COLS                  95
#define SINGLE_CHARACTER_ROWS        8
#define SINGLE_CHARACTER_COLS        5


class Frame
{
protected:
    uint8_t m_frameData[FRAME_ROWS][FRAME_COLS/8];
    static int xLen;
    static int yLen;

public:
    Frame(void) {}
    void setByte(int v_row, int v_col, uint8_t v_data);
    uint8_t getByte(int v_row, int v_col) const;
};

#endif // FRAME_H
