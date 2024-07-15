/* ------------------------------------ Qt ---------------------------------- */
#include <QAction>
#include <QIcon>
/* ----------------------------------- Local -------------------------------- */
#include "qtils/line_edit/file_browser_line_edit.h"
/* ----------------------------------- utils -------------------------------- */
#include <qtils/dialog/extended_file_dialog.h>
/* -------------------------------------------------------------------------- */

namespace qtils {

QtFileBrowserLineEdit::QtFileBrowserLineEdit(QWidget *parent)
    : QLineEdit(parent) {
  auto browser_action =
      addAction(QIcon(":/utils/line_edit/images/32x32/file_browser.png"),
                QLineEdit::TrailingPosition);

  connect(browser_action, &QAction::triggered, this,
          &QtFileBrowserLineEdit::browserPressed);
}

QtFileBrowserLineEdit::~QtFileBrowserLineEdit() = default;

void QtFileBrowserLineEdit::setBrowserCaption(const QString &caption) {
  m_browser_caption = caption;
  Q_EMIT browserCaptionChanged(m_browser_caption);
}

void QtFileBrowserLineEdit::setBrowserDir(const QString &dir) {
  m_browser_dir = dir;
  Q_EMIT browserDirChanged(m_browser_dir);
}

void QtFileBrowserLineEdit::setBrowserFilter(const QString &filter) {
  m_browser_filter = filter;
  Q_EMIT browserFilterChanged(m_browser_filter);
}

QString QtFileBrowserLineEdit::getBrowserCaption() const {
  return m_browser_caption;
}

QString QtFileBrowserLineEdit::getBrowserDir() const { return m_browser_dir; }

QString QtFileBrowserLineEdit::getBrowserFilter() const {
  return m_browser_filter;
}

void QtFileBrowserLineEdit::browserPressed() {
  const auto file_name = QtExtendedFileDialog::getSaveFileName(
      this, m_browser_caption, m_browser_dir, m_browser_filter);

  if (!file_name.isEmpty()) setText(file_name);
}

}  // namespace qtils
