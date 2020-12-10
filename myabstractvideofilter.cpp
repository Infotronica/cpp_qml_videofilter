#include "myabstractvideofilter.h"
#include "private/qvideoframe_p.h"

/*
    /home/iosef/Qt5.10.1/5.10.1/Src/qtmultimedia/src/multimedia/video/
*/

MyAbstractVideoFilter::MyAbstractVideoFilter(QObject* parent)
    : QAbstractVideoFilter(parent)
{
}

QVideoFilterRunnable* MyAbstractVideoFilter::createFilterRunnable()
{
    return new MyVideoFilterRunnable();
}

MyVideoFilterRunnable::MyVideoFilterRunnable()
{
}

QVideoFrame MyVideoFilterRunnable::run(QVideoFrame *qVideoFrame, const QVideoSurfaceFormat &qVideoSurfaceFormat, RunFlags runFlags)
{
    Q_UNUSED(runFlags)
    Q_UNUSED(qVideoSurfaceFormat)

    QVideoFrame qVideoFrameSalida;
    QString str;
    QImage qImageFrame,qImageEscudo,qImageQt;
    QPainter* qPainter;
    int frameWidth,frameHeight,fontSize,thumbSize;

    if (!qVideoFrame)
    {
        return QVideoFrame();
    }

    frameWidth=qVideoFrame->width();
    frameHeight=qVideoFrame->height();
    qImageFrame = qt_imageFromVideoFrame(*qVideoFrame); // obtenet un QImage del frame
    //qImage = videoFrameToImage(*qVideoFrame); // aun está pendiente

    if (!qVideoFrame->isValid())
    {
        str="VIDEO FRAME VACIO";
        qImageFrame = QImage(frameWidth, frameHeight, QImage::Format_RGB32); // sin usar new
        qImageFrame.fill(Qt::white);
    }
    else if (qImageFrame.isNull())
    {
        str="IMAGEN VACIA";
        qImageFrame = QImage(frameWidth, frameHeight, QImage::Format_RGB32); // sin usar new
        qImageFrame.fill(Qt::white);
    }
    else
    {
        str="SALUDOS DESDE MÉXICO";
    }

    fontSize=frameWidth*0.04;
    thumbSize=frameWidth*0.20;

    qImageEscudo.load(":/img/mx.png");
    qImageEscudo=qImageEscudo.scaled(frameWidth, frameHeight, Qt::KeepAspectRatio);

    qImageQt.load(":/img/Qt_logo_2016.png");
    qImageQt=qImageQt.scaledToWidth(thumbSize);

    qPainter = new QPainter(&qImageFrame);
    qPainter->setPen(Qt::red);
    qPainter->setFont(QFont("Arial", fontSize));
    qPainter->drawText(qImageFrame.rect(), Qt::AlignHCenter | Qt::AlignBottom, str);
    qPainter->drawImage(frameWidth-qImageQt.width(), 0, qImageQt);
    qPainter->setOpacity(0.60); // transparencia
    qPainter->drawImage(0, 0, qImageEscudo); // escudo transparente
    qVideoFrameSalida=QVideoFrame(qImageFrame); // colocar el QImage manipulado en un QVideoFrame
    delete qPainter; // liberar memoria

    return qVideoFrameSalida;
}

QImage MyVideoFilterRunnable::videoFrameToImage(QVideoFrame qVideoFrame) // esta función aun está pendiente
{
    QImage qImage;
    QImage::Format imageFormat;
    QVideoFrame qVideoFrameCopy(qVideoFrame);
    QVideoFrame::PixelFormat pixelFormat;
    int frameWidth,frameHeight;

    qVideoFrameCopy.map(QAbstractVideoBuffer::ReadOnly);
    pixelFormat=qVideoFrameCopy.pixelFormat();
    imageFormat = QVideoFrame::imageFormatFromPixelFormat(pixelFormat);
    frameWidth=qVideoFrameCopy.width();
    frameHeight=qVideoFrameCopy.height();

    if (imageFormat==QImage::Format_Invalid)
    {
        int nBytes = qVideoFrameCopy.mappedBytes();
        qImage = QImage(frameWidth, frameHeight, QImage::Format_RGB32);
        //qImage.loadFromData(qVideoFrameCopy.bits(), nBytes);
        memcpy(qImage.bits(), qVideoFrameCopy.bits(), nBytes);
        //qImage = QImage(qVideoFrameCopy.bits(), qVideoFrameCopy.width(), qVideoFrameCopy.height(), qVideoFrameCopy.bytesPerLine(), QImage::Format_RGB32);
    }
    else
    {
        qImage = QImage(qVideoFrameCopy.bits(), qVideoFrameCopy.width(), qVideoFrameCopy.height(), qVideoFrameCopy.bytesPerLine(), imageFormat);
    }
    qVideoFrameCopy.unmap();

    return qImage;
}
