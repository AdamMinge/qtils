/* ------------------------------------ Qt ---------------------------------- */
#include <QApplication>
#include <QFileInfo>
#include <QPainter>
/* ----------------------------------- Local -------------------------------- */
#include "qtils/stacked_widget/stacked_widget_tree_delegate.h"
#include "qtils/stacked_widget/stacked_widget_tree_model.h"
/* -------------------------------------------------------------------------- */

namespace qtils {

StackedWidgetTreeDelegate::StackedWidgetTreeDelegate(QObject *parent)
    : QStyledItemDelegate(parent), m_margins(0, 0, 0, 0) {}

StackedWidgetTreeDelegate::~StackedWidgetTreeDelegate() = default;

void StackedWidgetTreeDelegate::paint(QPainter *painter,
                                      const QStyleOptionViewItem &option,
                                      const QModelIndex &index) const {
  QStyleOptionViewItem opt(option);
  initStyleOption(&opt, index);

  auto &palette = opt.palette;
  auto &rect = opt.rect;
  auto font = QFont(opt.font);
  auto content_rect = rect.adjusted(m_margins.left(), m_margins.top(),
                                    -m_margins.right(), -m_margins.bottom());

  auto name = index.data(QtStackedWidgetTreeModel::Role::NameRole).toString();

  painter->save();
  painter->setFont(opt.font);

  auto color = opt.state & QStyle::State_Selected ? palette.highlight().color()
                                                  : palette.base().color();

  painter->fillRect(0, rect.top(), rect.width() + rect.left(), rect.height(),
                    color);

  auto style = QApplication::style();
  auto primitive_opt = opt;
  primitive_opt.rect.setRect(0, opt.rect.top(), 20, opt.rect.height());

  style->drawPrimitive(QStyle::PE_IndicatorBranch, &primitive_opt, painter,
                       nullptr);

  font.setBold(!index.parent().isValid());

  painter->setFont(font);
  painter->setPen(palette.text().color());
  painter->drawText(content_rect, Qt::TextSingleLine, name);

  painter->restore();
}

QSize StackedWidgetTreeDelegate::sizeHint(const QStyleOptionViewItem &option,
                                          const QModelIndex &index) const {
  QStyleOptionViewItem opt(option);
  initStyleOption(&opt, index);

  return QSize{opt.rect.width(), QFontMetrics(opt.font).height() +
                                     m_margins.top() + m_margins.bottom()};
}

void StackedWidgetTreeDelegate::setMargins(const QMargins &margins) {
  m_margins = margins;
}

const QMargins &StackedWidgetTreeDelegate::getMargins() const {
  return m_margins;
}

}  // namespace qtils
