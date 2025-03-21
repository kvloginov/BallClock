#include <GyverGFX.h>

#define MX_LED_AMOUNT 128
#define MX_XY_VIRT_W 39
#define MX_XY_VIRT_H 13
#define MX_REAL_H (MX_XY_VIRT_H / 2) + 1
#define MX_DIAG_W 20
#define MX_DIAG_H 7
// not mapped pixel
#define NM UINT8_MAX

// BallMatrix
class BallMatrix : public GyverGFX
{
public:
    BallMatrix()
    {
        setModeXY();
    }

    // strip
    void setLED(uint8_t idx, uint32_t color);
    uint32_t getLED(uint8_t idx);
    void begin();
    void update();
    void setBright(uint8_t bright);
    void clear();

    // gfx
    void fastSet(int x, int y)
    {
        if (_buf16 != getColor())
        {
            _buf16 = getColor();
            _buf32 = getColor24full();
        }
        setLED(x, y, _buf32);
    }

    // matrix
    int ledXY(int x, int y);
    int ledDiag(int x, int y);

    void setLED(int x, int y, uint32_t color)
    {
        int led = _diag_mode ? ledDiag(x, y) : ledXY(x, y);
        if (led != NM)
            setLED(led, color);
    }
    uint32_t getLED(int x, int y)
    {
        int led = _diag_mode ? ledDiag(x, y) : ledXY(x, y);
        return (led != NM) ? getLED(led) : 0;
    }

    void setModeXY()
    {
        _diag_mode = false;
        size(MX_XY_VIRT_W, MX_XY_VIRT_H);
    }

    void setModeDiag()
    {
        _diag_mode = true;
        size(MX_DIAG_W, MX_DIAG_H);
    }

private:
    bool _diag_mode = false;
    uint16_t _buf16;
    uint32_t _buf32;
};

// TODO: remove all public variables
extern BallMatrix matrix;