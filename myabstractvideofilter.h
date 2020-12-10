#ifndef MYABSTRACTVIDEOFILTER_H
#define MYABSTRACTVIDEOFILTER_H

#include <QAbstractVideoFilter>
#include <QVideoFilterRunnable>
#include <QPainter>

class MyAbstractVideoFilter : public QAbstractVideoFilter
{
    Q_OBJECT
public:
    MyAbstractVideoFilter(QObject* parent=nullptr);
    QVideoFilterRunnable* createFilterRunnable() Q_DECL_OVERRIDE;
};

class MyVideoFilterRunnable : public QVideoFilterRunnable
{
public:
    MyVideoFilterRunnable();
    QVideoFrame run(QVideoFrame *qVideoFrame, const QVideoSurfaceFormat &qVideoSurfaceFormat, RunFlags runFlags);
    QImage videoFrameToImage(QVideoFrame qVideoFrame);
};

#endif // MYABSTRACTVIDEOFILTER_H
