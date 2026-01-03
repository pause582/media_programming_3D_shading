#ifndef _COLOR_H_
#define _COLOR_H_

#define COLOR_RED    Color(0xd8,0x00,0x00)
#define COLOR_BLUE   Color(0x00,0x00,0xff)
#define COLOR_GREEN  Color(0x00,0xff,0x00)
#define COLOR_YELLOW Color(0xff,0xe2,0x11)
#define COLOR_ORANGE Color(0xff,0xa5,0x00)
#define COLOR_MIKU   Color(0x39,0xc5,0xbb)
#define COLOR_PINK   Color(0xff,0xc0,0xcb)
#define COLOR_WHITE  Color(0xff,0xff,0xff)
#define COLOR_BLACK  Color(0x00,0x00,0x00)

class RGB_container{
    protected:
    double r,g,b;
    public:
    bool isTransparent;
    RGB_container(double R=0,double G=0, double B=0,bool isTransparent = false);
    RGB_container(const RGB_container& c);
    double getR() const;
    double getG() const;
    double getB() const;
    virtual RGB_container operator=(const RGB_container& x);
    virtual RGB_container operator*(double x) const;
    virtual RGB_container operator*(RGB_container const& c)const;
    virtual RGB_container operator+(const RGB_container& x) const;
    virtual RGB_container operator+(double x) const;
    virtual void print();
};

class Color : public RGB_container{
    public:
    Color(double R=0,double G=0, double B=0,bool isTransparent = false);
    Color(const RGB_container& x);
    RGB_container operator=(const RGB_container& x) override;
    RGB_container operator*(double x) const override;
    RGB_container operator+(const RGB_container& x) const override;
    RGB_container operator+(double x) const override;
    void print() override;
};

double luminance(const RGB_container& c);
unsigned char double_to_unsigned_char(double x);

#endif