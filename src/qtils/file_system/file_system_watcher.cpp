/* ------------------------------------ Qt ---------------------------------- */
#include <QFile>
/* ----------------------------------- Local -------------------------------- */
#include "qtils/file_system/file_system_watcher.h"
/* -------------------------------------------------------------------------- */

namespace qtils {

QtFileSystemWatcher::QtFileSystemWatcher(QObject *parent) : QObject(parent) {
  m_changed_paths_timer.setInterval(500);
  m_changed_paths_timer.setSingleShot(true);

  connect(std::addressof(m_watcher), &QFileSystemWatcher::fileChanged, this,
          &QtFileSystemWatcher::onFileChanged);
  connect(std::addressof(m_watcher), &QFileSystemWatcher::directoryChanged,
          this, &QtFileSystemWatcher::onDirectoryChanged);

  connect(std::addressof(m_changed_paths_timer), &QTimer::timeout, this,
          &QtFileSystemWatcher::pathsChangedTimeout);
}

QtFileSystemWatcher::~QtFileSystemWatcher() = default;

void QtFileSystemWatcher::addPath(const QString &path) {
  if (QFile::exists(path)) m_watcher.addPath(path);
}

void QtFileSystemWatcher::addPaths(const QStringList &paths) {
  for (auto &path : paths) addPath(path);
}

void QtFileSystemWatcher::removePath(const QString &path) {
  m_watcher.removePath(path);
}

void QtFileSystemWatcher::removePaths(const QStringList &paths) {
  for (auto &path : paths) removePath(path);
}

QStringList QtFileSystemWatcher::getPaths() const {
  return getFilePaths() << getDirectoryPaths();
}

QStringList QtFileSystemWatcher::getFilePaths() const {
  return m_watcher.files();
}

QStringList QtFileSystemWatcher::getDirectoryPaths() const {
  return m_watcher.directories();
}

void QtFileSystemWatcher::clear() { m_watcher.removePaths(getPaths()); }

void QtFileSystemWatcher::onFileChanged(const QString &path) {
  m_changed_paths.insert(path);
  m_changed_paths_timer.start();

  Q_EMIT fileChanged(path);
}

void QtFileSystemWatcher::onDirectoryChanged(const QString &path) {
  m_changed_paths.insert(path);
  m_changed_paths_timer.start();

  Q_EMIT directoryChanged(path);
}

void QtFileSystemWatcher::pathsChangedTimeout() {
  const auto changed_paths = m_changed_paths.values();
  const auto file_paths = getFilePaths();
  for (const auto &path : changed_paths) {
    if (file_paths.contains(path) && QFile::exists(path))
      m_watcher.addPath(path);
  }

  Q_EMIT pathsChanged(changed_paths);
  m_changed_paths.clear();
}

}  // namespace qtils
