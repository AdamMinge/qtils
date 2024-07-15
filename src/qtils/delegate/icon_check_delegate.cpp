/* ----------------------------------- Local -------------------------------- */
#include "qtils/delegate/icon_check_delegate.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
#include <QMouseEvent>
#include <QPainter>
/* ----------------------------------- Qtils -------------------------------- */
#include <qtils/dpi/dpi.h>
/* -------------------------------------------------------------------------- */

namespace qtils {

QtIconCheckDelegate::QtIconCheckDelegate(QIcon checked_icon,
                                         QIcon unchecked_icon, bool exclusive,
                                         QObject *parent)
    : QItemDelegate(parent),
      m_checked_icon(std::move(checked_icon)),
      m_unchecked_icon(std::move(unchecked_icon)),
      m_icon_size(qtils::dpiScaled(QSize(16, 16))),
      m_exclusive(exclusive) {
  setClipping(false);
}

QtIconCheckDelegate::~QtIconCheckDelegate() = default;

void QtIconCheckDelegate::setIconSize(const QSize &size) { m_icon_size = size; }

QSize QtIconCheckDelegate::getIconSize() const { return m_icon_size; }

bool QtIconCheckDelegate::editorEvent(QEvent *event, QAbstractItemModel *model,
                                      const QStyleOptionViewItem &option,
                                      const QModelIndex &index) {
  if (!m_exclusive)
    return QItemDelegate::editorEvent(event, model, option, index);

  Qt::ItemFlags flags = model->flags(index);
  if (!(flags & Qt::ItemIsUserCheckable) ||
      !(option.state & QStyle::State_Enabled) || !(flags & Qt::ItemIsEnabled))
    return false;

  QVariant value = index.data(Qt::CheckStateRole);
  if (!value.isValid()) return false;

  if ((event->type() == QEvent::MouseButtonRelease) ||
      (event->type() == QEvent::MouseButtonDblClick) ||
      (event->type() == QEvent::MouseButtonPress)) {
    QMouseEvent *me = static_cast<QMouseEvent *>(event);
    if (me->button() != Qt::LeftButton) return false;

    if ((event->type() == QEvent::MouseButtonPress) ||
        (event->type() == QEvent::MouseButtonDblClick))
      return true;

  } else if (event->type() == QEvent::KeyPress) {
    if (static_cast<QKeyEvent *>(event)->key() != Qt::Key_Space &&
        static_cast<QKeyEvent *>(event)->key() != Qt::Key_Select)
      return false;
  } else {
    return false;
  }

  Qt::CheckState state = static_cast<Qt::CheckState>(value.toInt());
  if (flags & Qt::ItemIsUserTristate)
    state = static_cast<Qt::CheckState>((state + 1) % 3);
  else
    state = (state == Qt::Checked) ? Qt::Unchecked : Qt::Checked;
  return model->setData(index, state, Qt::CheckStateRole);
}

void QtIconCheckDelegate::drawCheck(QPainter *painter,
                                    const QStyleOptionViewItem &opt,
                                    const QRect &rect,
                                    Qt::CheckState state) const {
  const QRect &r = m_exclusive ? opt.rect : rect;
  const QIcon &icon =
      (state == Qt::Checked) ? m_checked_icon : m_unchecked_icon;
  const QPixmap &pixmap = icon.pixmap(m_exclusive ? m_icon_size : r.size());

  QSize layoutSize = pixmap.size() / pixmap.devicePixelRatio();
  QRect targetRect(QPoint(0, 0), layoutSize);
  targetRect.moveCenter(r.center());

  painter->drawPixmap(targetRect, pixmap);
}

void QtIconCheckDelegate::drawDisplay(QPainter *painter,
                                      const QStyleOptionViewItem &option,
                                      const QRect &rect,
                                      const QString &text) const {
  if (m_exclusive) return;
  QItemDelegate::drawDisplay(painter, option, rect, text);
}

QSize QtIconCheckDelegate::sizeHint(const QStyleOptionViewItem &option,
                                    const QModelIndex &index) const {
  if (m_exclusive) return qtils::dpiScaled(QSize(22, 20));
  return QItemDelegate::sizeHint(option, index);
}

}  // namespace qtils