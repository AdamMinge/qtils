#ifndef QTILS_SERIALIZER_BASE_SERIALIZATION_H
#define QTILS_SERIALIZER_BASE_SERIALIZATION_H

/* ----------------------------------- Local -------------------------------- */
#include "qtils/serializer/archive_property.h"
#include "qtils/serializer/export.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QBitArray>
#include <QDate>
#include <QDateTime>
#include <QHash>
#include <QLine>
#include <QLineF>
#include <QList>
#include <QMap>
#include <QMetaObject>
#include <QMetaProperty>
#include <QMetaType>
#include <QMultiHash>
#include <QMultiMap>
#include <QObject>
#include <QQueue>
#include <QRect>
#include <QRectF>
#include <QSequentialIterable>
#include <QSize>
#include <QStack>
#include <QTime>
#include <QUrl>
#include <QUuid>
#include <QVector>
/* -------------------------------------------------------------------------- */

namespace qtils {

class OArchive;
class IArchive;

/* ---------------------------------- IsGadget ------------------------------ */

namespace details {
template <typename Type, typename = void>
struct IsGadget : std::false_type {};

template <typename Type>
struct IsGadget<
    Type,
    std::enable_if_t<QtPrivate::IsGadgetHelper<Type>::IsGadgetOrDerivedFrom>>
    : std::true_type {};

/* ----------------------------------- IsRect ------------------------------- */

template <typename Type>
concept IsRect = std::is_same_v<Type, QRect> || std::is_same_v<Type, QRectF>;

/* ----------------------------------- IsLine ------------------------------- */

template <typename Type>
concept IsLine = std::is_same_v<Type, QLine> || std::is_same_v<Type, QLineF>;

/* ----------------------------------- IsPoint ------------------------------ */

template <typename Type>
concept IsPoint = std::is_same_v<Type, QPoint> || std::is_same_v<Type, QPointF>;

/* ----------------------------------- IsSize ------------------------------- */

template <typename Type>
concept IsSize = std::is_same_v<Type, QSize> || std::is_same_v<Type, QSizeF>;

/* ----------------------------------- IsTime ------------------------------- */

template <typename Type>
concept IsTime = std::is_same_v<Type, QTime> || std::is_same_v<Type, QDate> ||
    std::is_same_v<Type, QDateTime>;

/* -------------------------- IsMetaTypeSpecialization ---------------------- */

template <typename Type>
concept IsMetaTypeSpecialization = IsRect<Type> || IsLine<Type> ||
    IsPoint<Type> || IsSize<Type> || IsTime<Type>;

/* ---------------------------- IsRegisteredMetaType ------------------------ */

template <typename Type>
concept IsRegisteredMetaType =
    !IsMetaTypeSpecialization<Type> && IsGadget<Type>::value;

/* ----------------------------------- Gadget ------------------------------- */

template <typename Archive>
bool trySerializeVariantGadget(Archive& ar, const QVariant& variant) {
  auto meta_type = variant.metaType();
  auto meta_object = meta_type.metaObject();
  if (!meta_type.flags().testFlag(QMetaType::IsGadget) || !meta_object)
    return false;

  for (auto index = meta_object->propertyOffset();
       index < meta_object->propertyCount(); ++index) {
    auto meta_property = meta_object->property(index);
    auto property = meta_property.readOnGadget(variant.data());

    ar << ArchiveProperty(meta_property.name(), property);
  }

  return true;
}

template <typename Archive>
bool tryDeserializeVariantGadget(Archive& ar, QVariant& variant) {
  auto meta_type = variant.metaType();
  auto meta_object = meta_type.metaObject();
  if (!meta_type.flags().testFlag(QMetaType::IsGadget) || !meta_object)
    return false;

  for (auto index = meta_object->propertyOffset();
       index < meta_object->propertyCount(); ++index) {
    auto meta_property = meta_object->property(index);
    auto property = QVariant(meta_property.metaType());

    ar >> ArchiveProperty(meta_property.name(), property);
    auto s = meta_property.writeOnGadget(variant.data(), property);
  }

  return true;
}

/* ---------------------------------- Base Type ----------------------------- */

template <typename Archive, typename Type>
bool trySerializeVariantBaseType(Archive& ar, const QVariant& variant) {
  if (variant.metaType().id() == qMetaTypeId<Type>()) {
    Type value = variant.value<Type>();
    ar << value;
    return true;
  }

  return false;
}

template <typename Archive, typename Type>
bool tryDeserializeVariantBaseType(Archive& ar, QVariant& variant) {
  if (variant.metaType().id() == qMetaTypeId<Type>()) {
    Type value;
    ar >> value;
    variant.setValue(std::move(value));
    return true;
  }

  return false;
}

/* ----------------------------------- Variant ------------------------------ */

template <typename Archive>
void serializeVariant(Archive& ar, const QVariant& variant) {
  // clang-format off
  using Serializer = std::function<bool(Archive&, const QVariant&)>;

  static auto type_to_serializer = std::map<int, Serializer*>{};
  static auto serializers = std::to_array<Serializer>({
    [](auto& a, auto& v){ return trySerializeVariantBaseType<Archive, QUrl>(a, v); },
    [](auto& a, auto& v){ return trySerializeVariantBaseType<Archive, QUuid>(a, v); },
    [](auto& a, auto& v){ return trySerializeVariantBaseType<Archive, QRectF>(a, v); },
    [](auto& a, auto& v){ return trySerializeVariantBaseType<Archive, QRect>(a, v); },
    [](auto& a, auto& v){ return trySerializeVariantBaseType<Archive, QLineF>(a, v); },
    [](auto& a, auto& v){ return trySerializeVariantBaseType<Archive, QLine>(a, v); },
    [](auto& a, auto& v){ return trySerializeVariantBaseType<Archive, QPointF>(a, v); },
    [](auto& a, auto& v){ return trySerializeVariantBaseType<Archive, QPoint>(a, v); },
    [](auto& a, auto& v){ return trySerializeVariantBaseType<Archive, QSizeF>(a, v); },
    [](auto& a, auto& v){ return trySerializeVariantBaseType<Archive, QSize>(a, v); },
    [](auto& a, auto& v){ return trySerializeVariantBaseType<Archive, QTime>(a, v); },
    [](auto& a, auto& v){ return trySerializeVariantBaseType<Archive, QDate>(a, v); },
    [](auto& a, auto& v){ return trySerializeVariantBaseType<Archive, QDateTime>(a, v); },
    [](auto& a, auto& v){ return trySerializeVariantBaseType<Archive, QByteArray>(a, v); },
    [](auto& a, auto& v){ return trySerializeVariantBaseType<Archive, QString>(a, v); },
    [](auto& a, auto& v){ return trySerializeVariantBaseType<Archive, float>(a, v); },
    [](auto& a, auto& v){ return trySerializeVariantBaseType<Archive, double>(a, v); },
    [](auto& a, auto& v){ return trySerializeVariantBaseType<Archive, bool>(a, v); },
    [](auto& a, auto& v){ return trySerializeVariantBaseType<Archive, qulonglong>(a, v); },
    [](auto& a, auto& v){ return trySerializeVariantBaseType<Archive, qlonglong>(a, v); },
    [](auto& a, auto& v){ return trySerializeVariantBaseType<Archive, uint>(a, v); },
    [](auto& a, auto& v){ return trySerializeVariantBaseType<Archive, int>(a, v); },
    
    [](auto& a, auto& v){ return trySerializeVariantGadget(a, v); }});
  // clang-format on

  if (auto id = variant.metaType().id(); type_to_serializer.contains(id))
    (*type_to_serializer[id])(ar, variant);
  else {
    for (auto& serializer : serializers) {
      if (serializer(ar, variant)) {
        type_to_serializer.insert(
            std::make_pair(variant.metaType().id(), &serializer));
        break;
      }
    }
  }
}

template <typename Archive>
void deserializeVariant(Archive& ar, QVariant& variant) {
  // clang-format off
  using Deserializer = std::function<bool(Archive&, QVariant&)>;

  static auto type_to_deserializer = std::map<int, Deserializer*>{};
  static auto deserializers = std::to_array<Deserializer>({
    [](auto& a, auto& v){ return tryDeserializeVariantBaseType<Archive, QUrl>(a, v); },
    [](auto& a, auto& v){ return tryDeserializeVariantBaseType<Archive, QUuid>(a, v); },
    [](auto& a, auto& v){ return tryDeserializeVariantBaseType<Archive, QRectF>(a, v); },
    [](auto& a, auto& v){ return tryDeserializeVariantBaseType<Archive, QRect>(a, v); },
    [](auto& a, auto& v){ return tryDeserializeVariantBaseType<Archive, QLineF>(a, v); },
    [](auto& a, auto& v){ return tryDeserializeVariantBaseType<Archive, QLine>(a, v); },
    [](auto& a, auto& v){ return tryDeserializeVariantBaseType<Archive, QPointF>(a, v); },
    [](auto& a, auto& v){ return tryDeserializeVariantBaseType<Archive, QPoint>(a, v); },
    [](auto& a, auto& v){ return tryDeserializeVariantBaseType<Archive, QSizeF>(a, v); },
    [](auto& a, auto& v){ return tryDeserializeVariantBaseType<Archive, QSize>(a, v); },
    [](auto& a, auto& v){ return tryDeserializeVariantBaseType<Archive, QTime>(a, v); },
    [](auto& a, auto& v){ return tryDeserializeVariantBaseType<Archive, QDate>(a, v); },
    [](auto& a, auto& v){ return tryDeserializeVariantBaseType<Archive, QDateTime>(a, v); },
    [](auto& a, auto& v){ return tryDeserializeVariantBaseType<Archive, QByteArray>(a, v); },
    [](auto& a, auto& v){ return tryDeserializeVariantBaseType<Archive, QString>(a, v); },
    [](auto& a, auto& v){ return tryDeserializeVariantBaseType<Archive, float>(a, v); },
    [](auto& a, auto& v){ return tryDeserializeVariantBaseType<Archive, double>(a, v); },
    [](auto& a, auto& v){ return tryDeserializeVariantBaseType<Archive, bool>(a, v); },
    [](auto& a, auto& v){ return tryDeserializeVariantBaseType<Archive, qulonglong>(a, v); },
    [](auto& a, auto& v){ return tryDeserializeVariantBaseType<Archive, qlonglong>(a, v); },
    [](auto& a, auto& v){ return tryDeserializeVariantBaseType<Archive, uint>(a, v); },
    [](auto& a, auto& v){ return tryDeserializeVariantBaseType<Archive, int>(a, v); },
    
    [](auto& a, auto& v){ return tryDeserializeVariantGadget(a, v); }});
  // clang-format on

  if (auto id = variant.metaType().id(); type_to_deserializer.contains(id))
    (*type_to_deserializer[id])(ar, variant);
  else {
    for (auto& deserializer : deserializers) {
      if (deserializer(ar, variant)) {
        type_to_deserializer.insert(
            std::make_pair(variant.metaType().id(), &deserializer));
        break;
      }
    }
  }
}

}  // namespace details

/* ----------------------------------- QRect -------------------------------- */

template <typename Archive, details::IsRect Rect>
void serialize(Archive& ar, const Rect& rect) {
  const auto point = rect.topLeft();
  const auto size = rect.size();

  ar << ArchiveProperty("p", point);
  ar << ArchiveProperty("s", size);
}

template <typename Archive, details::IsRect Rect>
void deserialize(Archive& ar, Rect& rect) {
  decltype(rect.topLeft()) point;
  decltype(rect.size()) size;

  ar >> ArchiveProperty("p", point);
  ar >> ArchiveProperty("s", size);
  rect = Rect(point, size);
}

/* ----------------------------------- QLine -------------------------------- */

template <typename Archive, details::IsLine Line>
void serialize(Archive& ar, const Line& line) {
  auto p1 = line.p1(), p2 = line.p2();

  ar << ArchiveProperty("p1", p1);
  ar << ArchiveProperty("p2", p2);
}

template <typename Archive, details::IsLine Line>
void deserialize(Archive& ar, Line& line) {
  decltype(line.p1()) p1, p2;

  ar >> ArchiveProperty("p1", p1);
  ar >> ArchiveProperty("p2", p2);
  line = Line(p1, p2);
}

/* ---------------------------------- QPoint -------------------------------- */

template <typename Archive, details::IsPoint Point>
void serialize(Archive& ar, const Point& point) {
  auto x = point.x(), y = point.y();

  ar << ArchiveProperty("x", x);
  ar << ArchiveProperty("y", y);
}

template <typename Archive, details::IsPoint Point>
void deserialize(Archive& ar, Point& point) {
  decltype(point.x()) x, y;

  ar >> ArchiveProperty("x", x);
  ar >> ArchiveProperty("y", y);
  point = Point(x, y);
}

/* ----------------------------------- QSize -------------------------------- */

template <typename Archive, details::IsSize Size>
void serialize(Archive& ar, const Size& size) {
  auto width = size.width(), height = size.height();

  ar << ArchiveProperty("w", width);
  ar << ArchiveProperty("h", height);
}

template <typename Archive, details::IsSize Size>
void deserialize(Archive& ar, Size& size) {
  decltype(size.width()) width, height;

  ar >> ArchiveProperty("w", width);
  ar >> ArchiveProperty("h", height);
  size = Size(width, height);
}

/* ----------------------------------- QTime -------------------------------- */

template <typename Archive, details::IsTime Time>
void serialize(Archive& ar, const Time& time) {
  auto text = time.toString(Qt::DateFormat::ISODate);

  ar << text;
}

template <typename Archive, details::IsTime Time>
void deserialize(Archive& ar, Time& time) {
  QString text;

  ar >> text;
  time = Time::fromString(text, Qt::DateFormat::ISODate);
}

/* ---------------------------------- QVariant ------------------------------ */

template <typename Archive>
void serialize(Archive& ar, const QVariant& variant) {
  details::serializeVariant(ar, variant);
}

template <typename Archive>
void deserialize(Archive& ar, QVariant& variant) {
  details::deserializeVariant(ar, variant);
}

/* ---------------------------------- QObject ------------------------------- */

template <typename Archive>
void serialize(Archive& ar, const QObject& object) {
  for (auto& property_name : object.dynamicPropertyNames()) {
    auto property = object.property(property_name.constData());
    ar << ArchiveProperty(property_name, property);
  }
}

template <typename Archive>
void deserialize(Archive& ar, QObject& object) {
  for (auto& property_name : object.dynamicPropertyNames()) {
    auto meta_type = object.property(property_name.constData()).metaType();
    auto property = QVariant(meta_type);
    ar >> ArchiveProperty(property_name, property);

    object.setProperty(property_name.constData(), property);
  }
}

/* ---------------------------- RegisteredMetaType -------------------------- */

template <typename Archive, details::IsRegisteredMetaType Object>
void serialize(Archive& ar, const Object& object) {
  QVariant variant = QVariant::fromValue(object);
  ar << variant;
}

template <typename Archive, details::IsRegisteredMetaType Object>
void deserialize(Archive& ar, Object& object) {
  QVariant variant(QMetaType(qMetaTypeId<Object>()));
  ar >> variant;
  object = variant.value<Object>();
}

}  // namespace qtils

#endif  // QTILS_SERIALIZER_BASE_SERIALIZATION_H
