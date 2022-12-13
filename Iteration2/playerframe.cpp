#include "playerframe.h"
#include <QtWidgets>
#include <qvideosurfaceformat.h>

PlayerFrame::PlayerFrame(QObject *parent)
    : QAbstractVideoSurface(parent)
    , imgFormat(QImage::Format_Invalid)
{

}

bool PlayerFrame::Videostart(const QVideoSurfaceFormat &format)
{
    QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(format.pixelFormat());
    QSize size = format.frameSize();

    if (imageFormat != QImage::Format_Invalid && !size.isEmpty())
    {
        this->imgFormat = imageFormat;
        QAbstractVideoSurface::start(format);
        return true;

    }
    else return false;
}

void PlayerFrame::fnClearPixmap()
{
    CapImage = QPixmap();
}

void PlayerFrame::stopVideo()
{
    QAbstractVideoSurface::stop();
}

QList<QVideoFrame::PixelFormat> PlayerFrame::supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const
{
    if (handleType == QAbstractVideoBuffer::NoHandle) {
        return QList<QVideoFrame::PixelFormat>()
                << QVideoFrame::Format_RGB32
                << QVideoFrame::Format_ARGB32
                << QVideoFrame::Format_ARGB32_Premultiplied
                << QVideoFrame::Format_RGB565
                << QVideoFrame::Format_RGB555;
    }
    else
    {
        return QList<QVideoFrame::PixelFormat>();
    }
}

bool PlayerFrame::isFormatSupported(const QVideoSurfaceFormat &format) const
{
    QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(format.pixelFormat());
    QSize size = format.frameSize();

    return imageFormat != QImage::Format_Invalid && !size.isEmpty() && format.handleType() == QAbstractVideoBuffer::NoHandle;
}

bool PlayerFrame::present(const QVideoFrame &frame)
{
    if (surfaceFormat().pixelFormat() != frame.pixelFormat() || surfaceFormat().frameSize() != frame.size())
    {
        setError(IncorrectFormatError);
        stop();
        return false;
    }
    else
    {
        if (!CapImage.isNull())
        {
             fnSurfaceStopped(CapImage);
        }

        curFrame = frame;
        if (curFrame.map(QAbstractVideoBuffer::ReadOnly))
        {
            QImage image(
                    curFrame.bits(),
                    curFrame.width(),
                    curFrame.height(),
                    curFrame.bytesPerLine(),
                    imgFormat);
            if (CapImage.isNull())
            {
                    CapImage = QPixmap::fromImage(image.copy(image.rect()));
            }
            curFrame.unmap();
        }
        return true;
    }
}
