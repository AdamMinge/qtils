#ifndef QTILS_SERIALIZER_JSON_ARCHIVE_H
#define QTILS_SERIALIZER_JSON_ARCHIVE_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QIODevice>
/* ----------------------------------- Local -------------------------------- */
#include "qtils/serializer/archive.h"
#include "qtils/serializer/export.h"
/* -------------------------------------------------------------------------- */

namespace qtils {

class JsonArchive;

/* -------------------------------- OJsonArchive ---------------------------- */

class SERIALIZER_API OJsonArchive : public OArchive {
 public:
  explicit OJsonArchive(QIODevice& device);
  ~OJsonArchive() override;

 protected:
  void saveStart(const QString& name) override;
  void saveEnd(const QString& name) override;

  void arrayStart(qsizetype i) override;
  void arrayEnd(qsizetype i) override;

  void save(const QVariant& value) override;

 private:
  std::unique_ptr<JsonArchive> m_archive;
};

/* -------------------------------- IJsonArchive ---------------------------- */

class SERIALIZER_API IJsonArchive : public IArchive {
  class Impl;

 public:
  explicit IJsonArchive(QIODevice& device);
  ~IJsonArchive() override;

 protected:
  void loadStart(const QString& name) override;
  void loadEnd(const QString& name) override;

  void arrayStart(qsizetype i) override;
  void arrayEnd(qsizetype i) override;

  QVariant load() override;

 protected:
  [[nodiscard]] QStringList getChildNames() const override;
  [[nodiscard]] qsizetype getChildCount() const override;

 private:
  std::unique_ptr<JsonArchive> m_archive;
};

}  // namespace qtils

#endif  // QTILS_SERIALIZER_JSON_ARCHIVE_H
