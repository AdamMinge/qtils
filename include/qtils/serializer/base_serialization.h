#ifndef QTILS_SERIALIZER_BASE_SERIALIZATION_H
#define QTILS_SERIALIZER_BASE_SERIALIZATION_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QBitArray>
#include <QByteArrayList>
#include <QColor>
#include <QDate>
#include <QDateTime>
#include <QEasingCurve>
#include <QLine>
#include <QPoint>
#include <QPointF>
#include <QRect>
#include <QRectF>
#include <QRegularExpression>
#include <QSize>
#include <QSizeF>
#include <QUrl>
#include <QUuid>
#include <QVariant>
/* ----------------------------------- Local -------------------------------- */
#include "qtils/serializer/export.h"
/* -------------------------------------------------------------------------- */

namespace qtils {

class OArchive;
class IArchive;

/* ---------------------------------- QVariant ------------------------------ */

void serialize(OArchive& archive, const QVariant& variant);

void deserialize(IArchive& archive, QVariant& variant);

/* ----------------------------------- QRect -------------------------------- */

void serialize(OArchive& archive, const QRect& rect);
void serialize(OArchive& archive, const QRectF& rect);

void deserialize(IArchive& archive, QRect& rect);
void deserialize(IArchive& archive, QRectF& rect);

/* ----------------------------------- QPoint ------------------------------- */

void serialize(OArchive& archive, const QPoint& point);
void serialize(OArchive& archive, const QPointF& point);

void deserialize(IArchive& archive, QPoint& point);
void deserialize(IArchive& archive, QPointF& point);

/* ----------------------------------- QSize -------------------------------- */

void serialize(OArchive& archive, const QSize& size);
void serialize(OArchive& archive, const QSizeF& size);

void deserialize(IArchive& archive, QSize& size);
void deserialize(IArchive& archive, QSizeF& size);

}  // namespace qtils

#endif  // QTILS_SERIALIZER_BASE_SERIALIZATION_H
