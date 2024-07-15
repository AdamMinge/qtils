#ifndef QTILS_LINE_EDIT_DIR_BROWSER_LINE_EDIT_H
#define QTILS_LINE_EDIT_DIR_BROWSER_LINE_EDIT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QLineEdit>
#include <QStringList>
/* ----------------------------------- Local -------------------------------- */
#include "qtils/line_edit/export.h"
/* -------------------------------------------------------------------------- */

namespace qtils {

class LINE_EDIT_API QtDirBrowserLineEdit : public QLineEdit {
  Q_OBJECT

 public:
  explicit QtDirBrowserLineEdit(QWidget *parent = nullptr);
  ~QtDirBrowserLineEdit() override;

  void setBrowserCaption(const QString &caption);
  void setBrowserDir(const QString &dir);

  [[nodiscard]] QString getBrowserCaption() const;
  [[nodiscard]] QString getBrowserDir() const;

 Q_SIGNALS:
  void browserCaptionChanged(const QString &caption);
  void browserDirChanged(const QString &dir);

 protected Q_SLOTS:
  void browserPressed();

 private:
  QString m_browser_caption;
  QString m_browser_dir;
};

}  // namespace qtils

#endif  // QTILS_LINE_EDIT_DIR_BROWSER_LINE_EDIT_H
