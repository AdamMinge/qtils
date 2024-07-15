/* ------------------------------------ Qt ---------------------------------- */
#include <QDir>
#include <QEvent>
#include <QFileInfo>
/* ----------------------------------- Local -------------------------------- */
#include "qtils/widget/name_and_path_filler.h"
/* ------------------------------------ Ui ---------------------------------- */
#include "ui_name_and_path_filler.h"
/* -------------------------------------------------------------------------- */

namespace qtils {

QtNameAndPathFiller::QtNameAndPathFiller(QWidget *parent)
    : QWidget(parent),
      m_ui(new Ui::QtNameAndPathFiller),
      m_name_validations(NameValidation::All),
      m_path_validations(PathValidation::All) {
  initUi();
  initConnections();

  retranslateUi();
}

QtNameAndPathFiller::~QtNameAndPathFiller() = default;

void QtNameAndPathFiller::setNameValidations(NameValidations validations) {
  m_name_validations = validations;
  nameChanged();
}

QtNameAndPathFiller::NameValidations QtNameAndPathFiller::getNameValidations()
    const {
  return m_name_validations;
}

void QtNameAndPathFiller::setPathValidations(PathValidations validations) {
  m_path_validations = validations;
  pathChanged();
}

QtNameAndPathFiller::PathValidations QtNameAndPathFiller::getPathValidations()
    const {
  return m_path_validations;
}

void QtNameAndPathFiller::setBrowserDir(const QDir &dir) {
  m_ui->m_path_edit->setBrowserDir(dir.path());
}

QDir QtNameAndPathFiller::getBrowserDir() const {
  return QDir{m_ui->m_path_edit->text()};
}

void QtNameAndPathFiller::setName(const QString &name) {
  m_ui->m_name_edit->setText(name);
}

QString QtNameAndPathFiller::getName() const {
  return m_ui->m_name_edit->text();
}

void QtNameAndPathFiller::setPath(const QString &path) {
  m_ui->m_path_edit->setText(path);
}

QString QtNameAndPathFiller::getPath() const {
  return m_ui->m_path_edit->text();
}

bool QtNameAndPathFiller::isValid() const {
  const auto hasNameError = !m_ui->m_name_error_message->text().isEmpty();
  const auto hasPathError = !m_ui->m_path_error_message->text().isEmpty();

  return !hasNameError && !hasPathError;
}

void QtNameAndPathFiller::changeEvent(QEvent *event) {
  QWidget::changeEvent(event);
  switch (event->type()) {
    case QEvent::LanguageChange:
      retranslateUi();
      break;
    default:
      break;
  }
}

void QtNameAndPathFiller::nameChanged() {
  const auto name = m_ui->m_name_edit->text();
  const auto path = m_ui->m_path_edit->text();

  auto name_is_empty =
      m_name_validations.testFlag(NameValidation::NotEmpty) && name.isEmpty();
  auto name_is_not_unique =
      !QDir(path).entryList(QStringList{} << QString("%1.*").arg(name)).empty();

  auto error_message = QString{};
  if (name_is_empty || name_is_not_unique)
    error_message = getNameErrorMessage();

  m_ui->m_name_error_message->setText(error_message);
  m_ui->m_name_error_message->setVisible(!error_message.isEmpty());

  Q_EMIT nameChanged(name);
  Q_EMIT validStateChanged(isValid());
}

void QtNameAndPathFiller::pathChanged() {
  const auto path = m_ui->m_path_edit->text();

  auto file_info = QFileInfo{path};
  auto dir = QDir{path};

  auto path_is_empty =
      m_path_validations.testFlag(PathValidation::NotEmpty) && path.isEmpty();
  auto dir_is_not_empty =
      m_path_validations.testFlag(PathValidation::DirIsEmpty) && !dir.isEmpty();
  auto path_is_incorrect =
      m_path_validations.testFlag(PathValidation::DirExists) &&
      (!file_info.exists() ||
       ((!file_info.isDir()) || (!file_info.isWritable())));

  auto error_message = QString{};
  if (path_is_empty || dir_is_not_empty || path_is_incorrect)
    error_message = getPathErrorMessage();

  m_ui->m_path_error_message->setText(error_message);
  m_ui->m_path_error_message->setVisible(!error_message.isEmpty());

  Q_EMIT pathChanged(path);
  Q_EMIT validStateChanged(isValid());
}

void QtNameAndPathFiller::initUi() {
  m_ui->setupUi(this);

  m_ui->m_path_edit->setBrowserCaption(tr("Select Directory"));
  m_ui->m_path_edit->setBrowserDir(QString{});

  nameChanged();
  pathChanged();
}

void QtNameAndPathFiller::initConnections() {
  connect(m_ui->m_name_edit, &QLineEdit::textChanged, this,
          qOverload<>(&QtNameAndPathFiller::nameChanged));

  connect(m_ui->m_path_edit, &QLineEdit::textChanged, this,
          qOverload<>(&QtNameAndPathFiller::pathChanged));
  connect(m_ui->m_path_edit, &QLineEdit::textChanged, this,
          qOverload<>(&QtNameAndPathFiller::nameChanged));
}

void QtNameAndPathFiller::retranslateUi() { m_ui->retranslateUi(this); }

QString QtNameAndPathFiller::getNameErrorMessage() const {
  auto error_message = QString{};

  if (m_name_validations.testFlag(NameValidation::NotEmpty))
    error_message = tr("Please choose some name");
  if (m_name_validations.testFlag(NameValidation::Unique))
    error_message = tr("Please enter unique name");

  return error_message;
}

QString QtNameAndPathFiller::getPathErrorMessage() const {
  auto error_message = QString{};

  if (m_path_validations.testFlag(PathValidation::NotEmpty))
    error_message = tr("Please enter some path");
  if (m_path_validations.testFlag(PathValidation::DirExists))
    error_message = tr("Please choose some folder");
  if (m_path_validations.testFlag(PathValidation::DirIsEmpty))
    error_message = tr("Please choose an empty folder");

  return error_message;
}

}  // namespace qtils
