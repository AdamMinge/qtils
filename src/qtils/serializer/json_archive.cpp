/* ----------------------------------- Local -------------------------------- */
#include "qtils/serializer/json_archive.h"

#include "qtils/serializer/priv/json_archive_p.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
/* -------------------------------------------------------------------------- */

namespace {

/* --------------------------------- Overloaded ----------------------------- */

template <class... Ts>
struct overloaded : Ts... {
  using Ts::operator()...;
};

}  // namespace

namespace qtils {

/* --------------------------------- JsonArchive ---------------------------- */

JsonArchive::JsonArchive(QIODevice& device) : m_device(device) {
  if (m_device.isReadable()) {
    QByteArray jsonData = device.readAll();
    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonData);
    m_root = jsonDocument.isNull() ? QJsonObject() : jsonDocument.object();
  }
}

void JsonArchive::push(const QString& key) {
  m_stack.push(ValueWithKey{.value = value()[key], .key = key});
}

void JsonArchive::push(qsizetype number) {
  auto& target = value();
  if (!target.isArray()) target = QJsonArray{};

  auto array = target.toArray();
  while (array.count() <= number) array.append(QJsonValue{});
  target = array;

  m_stack.push(ValueWithKey{.value = array.at(number), .key = number});
}

void JsonArchive::pop() {
  auto value_with_key = m_stack.top();
  m_stack.pop();

  std::visit(
      overloaded{[this, value = value_with_key.value](const QString& key) {
                   auto object = this->value().toObject();
                   object.insert(key, value);
                   this->value() = object;
                 },
                 [this, value = value_with_key.value](qsizetype key) {
                   auto array = this->value().toArray();
                   array.removeAt(key);
                   array.insert(key, value);
                   this->value() = array;
                 }},
      value_with_key.key);
}

const QJsonValue& JsonArchive::value() const {
  return m_stack.empty() ? m_root : m_stack.top().value;
}

QJsonValue& JsonArchive::value() {
  return m_stack.empty() ? m_root : m_stack.top().value;
}

void JsonArchive::save() {
  Q_ASSERT(m_device.isWritable());

  auto json_object = m_root.toObject();
  auto json_document = QJsonDocument(json_object);
  auto json_data_bytes = json_document.toJson();

  m_device.write(json_data_bytes);
}

/* -------------------------------- OJsonArchive ---------------------------- */

OJsonArchive::OJsonArchive(QIODevice& device)
    : m_archive(std::make_unique<JsonArchive>(device)) {}

OJsonArchive::~OJsonArchive() { m_archive->save(); }

void OJsonArchive::saveStart(const QString& name) { m_archive->push(name); }

void OJsonArchive::saveEnd(const QString& name) { m_archive->pop(); }

void OJsonArchive::arrayStart(qsizetype i) { m_archive->push(i); }

void OJsonArchive::arrayEnd(qsizetype i) { m_archive->pop(); }

void OJsonArchive::save(const QVariant& value) {
  auto& data = m_archive->value();
  auto input = QJsonValue::fromVariant(value);

  if (data.isNull() || data.isUndefined()) {
    data = input;
  } else if (data.isArray()) {
    auto array = data.toArray();
    array.append(input);
    data = array;
  } else {
    QJsonValue temp(QJsonValue::Array);
    temp.swap(data);

    auto array = data.toArray();
    array.append(temp);
    array.append(input);
    data = array;
  }
}

/* -------------------------------- IJsonArchive ---------------------------- */

IJsonArchive::IJsonArchive(QIODevice& device)
    : m_archive(std::make_unique<JsonArchive>(device)) {}

IJsonArchive::~IJsonArchive() = default;

void IJsonArchive::loadStart(const QString& name) { m_archive->push(name); }

void IJsonArchive::loadEnd(const QString& name) { m_archive->pop(); }

void IJsonArchive::arrayStart(qsizetype i) { m_archive->push(i); }

void IJsonArchive::arrayEnd(qsizetype i) { m_archive->pop(); }

QVariant IJsonArchive::load() { return m_archive->value().toVariant(); }

QStringList IJsonArchive::getChildNames() const {
  auto names = QStringList{};
  if (auto& value = m_archive->value(); value.isObject()) {
    auto object = value.toObject();
    names = object.keys();
  }

  return names;
}

qsizetype IJsonArchive::getChildCount() const {
  qsizetype size = 0;
  if (auto& value = m_archive->value(); value.isArray()) {
    auto array = value.toArray();
    size = array.size();
  }

  return size;
}

}  // namespace qtils