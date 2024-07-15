/* ----------------------------------- Local -------------------------------- */
#include "qtils/serializer/base_serialization.h"

#include "qtils/serializer/archive.h"
#include "qtils/serializer/archive_property.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QVariantHash>
#include <QVariantList>
#include <QVariantMap>
/* -------------------------------------------------------------------------- */

namespace qtils {

/* --------------------------------- Help Macros ---------------------------- */

#define VARIANT_TYPES(F)                               \
  F(QMetaType::Bool, bool)                             \
  F(QMetaType::Int, int)                               \
  F(QMetaType::UInt, unsigned int)                     \
  F(QMetaType::LongLong, qlonglong)                    \
  F(QMetaType::ULongLong, qulonglong)                  \
  F(QMetaType::Double, double)                         \
  F(QMetaType::Long, qlonglong)                        \
  F(QMetaType::Short, short)                           \
  F(QMetaType::Char, char)                             \
  F(QMetaType::ULong, qulonglong)                      \
  F(QMetaType::UShort, ushort)                         \
  F(QMetaType::UChar, uchar)                           \
  F(QMetaType::Float, float)                           \
  F(QMetaType::QChar, QChar)                           \
  F(QMetaType::QString, QString)                       \
  F(QMetaType::QStringList, QStringList)               \
  F(QMetaType::QByteArray, QByteArray)                 \
  F(QMetaType::QBitArray, QBitArray)                   \
  F(QMetaType::QDate, QDate)                           \
  F(QMetaType::QTime, QTime)                           \
  F(QMetaType::QDateTime, QDateTime)                   \
  F(QMetaType::QUrl, QUrl)                             \
  F(QMetaType::QLocale, QLocale)                       \
  F(QMetaType::QRect, QRect)                           \
  F(QMetaType::QRectF, QRectF)                         \
  F(QMetaType::QSize, QSize)                           \
  F(QMetaType::QSizeF, QSizeF)                         \
  F(QMetaType::QLine, QLine)                           \
  F(QMetaType::QLineF, QLineF)                         \
  F(QMetaType::QPoint, QPoint)                         \
  F(QMetaType::QPointF, QPointF)                       \
  F(QMetaType::QEasingCurve, QEasingCurve)             \
  F(QMetaType::QUuid, QUuid)                           \
  F(QMetaType::QRegularExpression, QRegularExpression) \
  F(QMetaType::SChar, signed char)                     \
  F(QMetaType::QVariantMap, QVariantMap)               \
  F(QMetaType::QVariantList, QVariantList)             \
  F(QMetaType::QVariantHash, QVariantHash)             \
  F(QMetaType::Char16, char16_t)                       \
  F(QMetaType::Char32, char32_t)                       \
  F(QMetaType::QColor, QColor)

#define SERIALIZE_VARIANT(FROM, TO)             \
  case FROM: {                                  \
    const auto value = variant.value<TO>();     \
    archive << ArchiveProperty("value", value); \
    break;                                      \
  }

#define DESERIALIZE_VARIANT(FROM, TO)           \
  case FROM: {                                  \
    TO value;                                   \
    archive >> ArchiveProperty("value", value); \
    variant = QVariant::fromValue<TO>(value);   \
    break;                                      \
  }

/* ---------------------------------- QVariant ------------------------------ */

void serialize(OArchive& archive, const QVariant& variant) {
  const auto meta_type = variant.metaType();
  const auto type_id = meta_type.id();
  Q_ASSERT(type_id != QMetaType::UnknownType);

  archive << ArchiveProperty("type", type_id);

  switch (meta_type.id()) { VARIANT_TYPES(SERIALIZE_VARIANT) }
}

void deserialize(IArchive& archive, QVariant& variant) {
  int type_id;
  archive >> ArchiveProperty("type", type_id);
  Q_ASSERT(type_id != QMetaType::UnknownType);

  constexpr auto z = IsDereferenceable<QByteArray>;
  auto t1 = QByteArray{};
  auto b = (*t1);

  switch (type_id) { VARIANT_TYPES(DESERIALIZE_VARIANT) }
}

/* ----------------------------------- QRect -------------------------------- */

void serialize(OArchive& archive, const QRect& rect) {
  const auto position = rect.topLeft();
  const auto size = rect.size();

  archive << ArchiveProperty("position", position);
  archive << ArchiveProperty("size", size);
}

void serialize(OArchive& archive, const QRectF& rect) {
  const auto position = rect.topLeft();
  const auto size = rect.size();

  archive << ArchiveProperty("position", position);
  archive << ArchiveProperty("size", size);
}

void deserialize(IArchive& archive, QRect& rect) {
  QPoint position;
  QSize size;

  archive >> ArchiveProperty("position", position);
  archive >> ArchiveProperty("size", size);

  rect.setTopLeft(position);
  rect.setSize(size);
}

void deserialize(IArchive& archive, QRectF& rect) {
  QPointF position;
  QSizeF size;

  archive >> ArchiveProperty("position", position);
  archive >> ArchiveProperty("size", size);

  rect.setTopLeft(position);
  rect.setSize(size);
}

/* ----------------------------------- QPoint ------------------------------- */

void serialize(OArchive& archive, const QPoint& point) {
  const auto x = point.x();
  const auto y = point.y();

  archive << ArchiveProperty("x", x);
  archive << ArchiveProperty("y", y);
}

void serialize(OArchive& archive, const QPointF& point) {
  const auto x = point.x();
  const auto y = point.y();

  archive << ArchiveProperty("x", x);
  archive << ArchiveProperty("y", y);
}

void deserialize(IArchive& archive, QPoint& point) {
  archive >> ArchiveProperty("x", point.rx());
  archive >> ArchiveProperty("y", point.ry());
}

void deserialize(IArchive& archive, QPointF& point) {
  archive >> ArchiveProperty("x", point.rx());
  archive >> ArchiveProperty("y", point.ry());
}

/* ----------------------------------- QSize -------------------------------- */

void serialize(OArchive& archive, const QSize& size) {
  const auto width = size.width();
  const auto height = size.height();

  archive << ArchiveProperty("width", width);
  archive << ArchiveProperty("height", height);
}

void serialize(OArchive& archive, const QSizeF& size) {
  const auto width = size.width();
  const auto height = size.height();

  archive << ArchiveProperty("width", width);
  archive << ArchiveProperty("height", height);
}

void deserialize(IArchive& archive, QSize& size) {
  archive >> ArchiveProperty("width", size.rwidth());
  archive >> ArchiveProperty("height", size.rheight());
}

void deserialize(IArchive& archive, QSizeF& size) {
  qreal width, height;

  archive >> ArchiveProperty("width", size.rwidth());
  archive >> ArchiveProperty("height", size.rheight());
}

}  // namespace qtils