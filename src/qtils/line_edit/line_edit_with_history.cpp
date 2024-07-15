/* ----------------------------------- Local -------------------------------- */
#include "qtils/line_edit/line_edit_with_history.h"
/* -------------------------------------------------------------------------- */

namespace qtils {

QtLineEditWithHistory::QtLineEditWithHistory(QWidget *parent)
    : QLineEdit(parent), m_history({}), m_history_position(0) {}

QtLineEditWithHistory::~QtLineEditWithHistory() = default;

void QtLineEditWithHistory::appendToHistory(QString text) {
  m_history.append(std::move(text));
  m_history_position = m_history.size();
  clear();
}

void QtLineEditWithHistory::setHistory(QStringList history) {
  m_history = (std::move(history));
  m_history_position = m_history.size();
  clear();
}

QStringList QtLineEditWithHistory::getHistory() const { return m_history; }

void QtLineEditWithHistory::move(qsizetype direction) {
  auto new_history_position =
      qBound(0, m_history_position + direction, m_history.size());
  if (new_history_position != m_history_position) {
    if (new_history_position < m_history.size())
      setText(m_history.at(new_history_position));
    else
      clear();

    m_history_position = new_history_position;
  }
}

void QtLineEditWithHistory::moveNext() { move(1); }

void QtLineEditWithHistory::movePrev() { move(-1); }

}  // namespace qtils
