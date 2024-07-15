/* ------------------------------------ Qt ---------------------------------- */
#include <QAbstractItemView>
#include <QComboBox>
#include <QCompleter>
#include <QDialogButtonBox>
#include <QEvent>
#include <QKeyEvent>
#include <QLineEdit>
#include <QToolButton>
/* ----------------------------------- Local -------------------------------- */
#include "qtils/dialog/extended_file_dialog.h"
/* -------------------------------------------------------------------------- */

namespace qtils {

QtExtendedFileDialog::QtExtendedFileDialog(const QFileDialogArgs &args)
    : QFileDialog(args) {
  init();
}

QtExtendedFileDialog::QtExtendedFileDialog(QWidget *parent,
                                           Qt::WindowFlags flags)
    : QFileDialog(parent, flags) {
  init();
}

QtExtendedFileDialog::QtExtendedFileDialog(QWidget *parent,
                                           const QString &caption,
                                           const QString &directory,
                                           const QString &filter)
    : QFileDialog(parent, caption, directory, filter) {
  init();
}

QtExtendedFileDialog::~QtExtendedFileDialog() = default;

QString QtExtendedFileDialog::getExistingDirectory(QWidget *parent,
                                                   const QString &caption,
                                                   const QString &dir,
                                                   QFileDialog::Options options,
                                                   const QString &top_dir) {
  const QStringList schemes = QStringList(QStringLiteral("file"));
  const QUrl selectedUrl = getExistingDirectoryUrl(
      parent, caption, QUrl::fromLocalFile(dir), options, schemes, top_dir);

  if (selectedUrl.isLocalFile() || selectedUrl.isEmpty())
    return selectedUrl.toLocalFile();
  else
    return selectedUrl.toString();
}

QUrl QtExtendedFileDialog::getExistingDirectoryUrl(
    QWidget *parent, const QString &caption, const QUrl &dir,
    QFileDialog::Options options, const QStringList &supportedSchemes,
    const QString &top_dir) {
  QtExtendedFileDialog dialog(parent, caption);
  dialog.setDirectoryUrl(dir);
  dialog.setFileMode(FileMode::Directory);
  dialog.setOptions(options);
  dialog.setSupportedSchemes(supportedSchemes);
  dialog.setTopDir(top_dir);

  if (dialog.exec() == QDialog::Accepted) return dialog.selectedUrls().value(0);
  return QUrl();
}

void QtExtendedFileDialog::init() {
  setOptions(QFileDialog::DontUseNativeDialog);

  connect(this, SIGNAL(directoryEntered(QString)), this, SLOT(checkHistory()));
  connect(this, SIGNAL(directoryEntered(QString)), this,
          SLOT(checkGoToParentAndBack()));
  connect(findChild<QToolButton *>("backButton"), SIGNAL(clicked()), this,
          SLOT(checkGoToParentAndBack()));
  connect(findChild<QToolButton *>("forwardButton"), SIGNAL(clicked()), this,
          SLOT(checkGoToParentAndBack()));
  connect(findChild<QLineEdit *>("fileNameEdit"), SIGNAL(textChanged(QString)),
          this, SLOT(checkLineEdit(QString)));
  connect(findChild<QComboBox *>("lookInCombo"),
          qOverload<int>(&QComboBox::currentIndexChanged), this,
          &QtExtendedFileDialog::checkComboBox);

  findChild<QLineEdit *>("fileNameEdit")->installEventFilter(this);
  findChild<QWidget *>("listView")->installEventFilter(this);
  findChild<QWidget *>("treeView")->installEventFilter(this);
  findChild<QLineEdit *>("fileNameEdit")
      ->completer()
      ->popup()
      ->installEventFilter(this);
}

bool QtExtendedFileDialog::eventFilter(QObject *object, QEvent *event) {
  if (event->type() != QEvent::KeyPress) return false;

  int key = dynamic_cast<QKeyEvent *>(event)->key();
  if (object->objectName() == "listView" ||
      object->objectName() == "treeView") {
    return (Qt::Key_Backspace == key && !pathFits(directory().absolutePath()));
  } else {
    if (Qt::Key_Return != key && Qt::Key_Enter != key) return false;

    QString text = findChild<QLineEdit *>("fileNameEdit")->text();
    QString path = QDir::cleanPath(directory().absolutePath() +
                                   (text.startsWith("/") ? "" : "/") + text);
    bool a = QDir(text).isAbsolute();

    return !((!a && pathFits(path)) || (a && pathFits(text)));
  }
}

void QtExtendedFileDialog::setTopDir(const QString &path) {
  if (path == m_top_dir) return;

  m_top_dir = (!path.isEmpty() && QFileInfo(path).isDir()) ? path : QString();

  if (!pathFits(path, true)) {
    setDirectory(m_top_dir);
    checkHistory();
    checkLineEdit(findChild<QLineEdit *>("fileNameEdit")->text());
  } else {
    auto line_edit = findChild<QLineEdit *>("fileNameEdit");
    line_edit->setText(line_edit->text());
  }

  if (!m_top_dir.isEmpty()) findChild<QWidget *>("sidebar")->hide();

  checkGoToParentAndBack();
}

QString QtExtendedFileDialog::getTopDir() const { return m_top_dir; }

bool QtExtendedFileDialog::pathFits(const QString &path, bool exact) const {
  return m_top_dir.isEmpty() || (path.startsWith(m_top_dir) &&
                                 (exact ? path.length() >= m_top_dir.length()
                                        : path.length() > m_top_dir.length()));
}

void QtExtendedFileDialog::checkHistory() {
  QStringList list = history();
  for (auto i = list.size() - 1; i >= 0; --i) {
    if (!pathFits(list.at(i))) list.removeAt(i);
  }

  setHistory(list);
}

void QtExtendedFileDialog::checkGoToParentAndBack() {
  auto path_fits = pathFits(directory().absolutePath());

  findChild<QToolButton *>("toParentButton")->setEnabled(path_fits);

  if (findChild<QToolButton *>("backButton")->isEnabled())
    findChild<QToolButton *>("backButton")->setEnabled(path_fits);
}

void QtExtendedFileDialog::checkLineEdit(const QString &text) {
  QAbstractButton *btn =
      findChild<QDialogButtonBox *>("buttonBox")->buttons().first();
  QString path = QDir::cleanPath(directory().absolutePath() +
                                 (text.startsWith("/") ? "" : "/") + text);
  bool a = QDir(text).isAbsolute();
  btn->setEnabled(btn->isEnabled() && ((!a && pathFits(path, true)) ||
                                       (a && pathFits(text, true))));
}

void QtExtendedFileDialog::checkComboBox(int index) {
  auto cb = findChild<QComboBox *>("lookInCombo");
  if (index == 0 && cb->model()->rowCount() > 1) {
    for (auto i = 0; i < cb->model()->rowCount(); ++i) {
      if (!pathFits(cb->model()->index(i, 0).data().toString() + "/")) {
        cb->model()->removeRow(i);
        --i;
      }
    }
  }
}

}  // namespace qtils