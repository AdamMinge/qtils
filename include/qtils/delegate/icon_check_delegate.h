#ifndef QTILS_DELEGATE_ICON_CHECK_DELEGATE_H
#define QTILS_DELEGATE_ICON_CHECK_DELEGATE_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QItemDelegate>
/* ----------------------------------- Local -------------------------------- */
#include "qtils/delegate/export.h"
/* -------------------------------------------------------------------------- */

namespace qtils {

class QtIconCheckDelegate : public QItemDelegate {
 public:
  enum IconType { VisibilityIcon, LockedIcon };

 public:
  explicit QtIconCheckDelegate(QIcon checked_icon, QIcon unchecked_icon,
                               bool exclusive, QObject *parent = nullptr);
  ~QtIconCheckDelegate() override;

  void setIconSize(const QSize &size);
  [[nodiscard]] QSize getIconSize() const;

  bool editorEvent(QEvent *event, QAbstractItemModel *model,
                   const QStyleOptionViewItem &option,
                   const QModelIndex &index) override;

 protected:
  void drawCheck(QPainter *painter, const QStyleOptionViewItem &option,
                 const QRect &rect, Qt::CheckState state) const override;

  void drawDisplay(QPainter *painter, const QStyleOptionViewItem &option,
                   const QRect &rect, const QString &text) const override;

  QSize sizeHint(const QStyleOptionViewItem &option,
                 const QModelIndex &index) const override;

 private:
  QIcon m_checked_icon;
  QIcon m_unchecked_icon;
  QSize m_icon_size;
  bool m_exclusive;
};

}  // namespace qtils

#endif  // QTILS_DELEGATE_ICON_CHECK_DELEGATE_H
