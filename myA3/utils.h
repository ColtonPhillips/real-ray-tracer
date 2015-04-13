// This is just some useful inlines

#ifndef UTILS
#define UTILS

#include <QColor>

namespace utils {

inline qreal max(qreal a, qreal b){ return a>b?a:b; }
inline qreal min(qreal a, qreal b){ return a<b?a:b; }
inline qreal clamp(qreal num){ return num<0?0:(num>1?1:num);}

inline void convertToViewportRelative(qreal &x, qreal &y)
{
    x = (x*2)-1;
    //flip y to get +y up, -y down
    y = 1-y;
    y = (y*2)-1;
}


inline QColor convertAndClampToColor(QVector3D color)
{
    qreal r = color.x();
    qreal g = color.y();
    qreal b = color.z();

    r = r>255?255:r;
    g = g>255?255:g;
    b = b>255?255:b;

    r = r<0?0:r;
    g = g<0?0:g;
    b = b<0?0:b;
    return QColor(static_cast<int>(r),static_cast<int>(g),static_cast<int>(b));

}

#endif // UTILS

}
