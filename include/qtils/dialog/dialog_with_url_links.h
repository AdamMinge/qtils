#ifndef QTILS_DIALOG_DIALOG_WITH_URL_LINKS_H
#define QTILS_DIALOG_DIALOG_WITH_URL_LINKS_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDialog>
#include <QPointer>
#include <QUrl>
/* ----------------------------------- Local -------------------------------- */
#include "qtils/dialog/export.h"
/* -------------------------------------------------------------------------- */

namespace qtils {

template <typename TYPE>
class DIALOG_API QtDialogWithUrlLinks : public QDialog {
 public:
  static void show(const QUrl &url = QUrl{}, QWidget *parent = nullptr);
  static void exec(const QUrl &url = QUrl{}, QWidget *parent = nullptr);

  virtual void setUrl(const QUrl &url);

 protected:
  explicit QtDialogWithUrlLinks(QWidget *parent = nullptr);
  ~QtDialogWithUrlLinks() override;
};

template <typename TYPE>
void QtDialogWithUrlLinks<TYPE>::show(const QUrl &url, QWidget *parent) {
  static QPointer<TYPE> dialog = nullptr;

  if (!dialog) {
    dialog = new TYPE(parent);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
  }

  dialog->setUrl(url);
  dialog->QDialog::show();
  dialog->QDialog::activateWindow();
  dialog->QDialog::raise();
}

template <typename TYPE>
void QtDialogWithUrlLinks<TYPE>::exec(const QUrl &url, QWidget *parent) {
  static QPointer<TYPE> dialog = nullptr;

  if (!dialog) {
    dialog = new TYPE(parent);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    QObject::connect(dialog, &QDialog::destroyed, []() { dialog = nullptr; });
  }

  dialog->setUrl(url);
  dialog->QDialog::exec();
}

template <typename TYPE>
void QtDialogWithUrlLinks<TYPE>::setUrl(const QUrl &url) {}

template <typename TYPE>
QtDialogWithUrlLinks<TYPE>::QtDialogWithUrlLinks(QWidget *parent)
    : QDialog(parent) {}

template <typename TYPE>
QtDialogWithUrlLinks<TYPE>::~QtDialogWithUrlLinks() = default;

}  // namespace qtils

#endif  // QTILS_DIALOG_DIALOG_WITH_URL_LINKS_H
