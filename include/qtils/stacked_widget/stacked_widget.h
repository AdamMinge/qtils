#ifndef QTILS_STACKED_WIDGET_STACKED_WIDGET_H
#define QTILS_STACKED_WIDGET_STACKED_WIDGET_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QAbstractItemView>
#include <QPointer>
#include <QStackedWidget>
/* ----------------------------------- Local -------------------------------- */
#include "qtils/stacked_widget/export.h"
/* -------------------------------------------------------------------------- */

namespace qtils {

class STACKED_WIDGET_API QtStackedWidget : public QStackedWidget {
  Q_OBJECT

 public:
  explicit QtStackedWidget(QWidget *parent = nullptr);
  ~QtStackedWidget() override;

  void setView(QAbstractItemView *view);
  [[nodiscard]] const QAbstractItemView *getView() const;

  void setDefaultWidget(QWidget *widget);
  [[nodiscard]] const QWidget *getDefaultWidget() const;

 private Q_SLOTS:
  void selectionChanged(const QItemSelection &selected,
                        const QItemSelection &deselected);
  void modelChanged(QAbstractItemModel *model);

 private:
  [[nodiscard]] static QList<QWidget *> getStackedWidgets(
      const QAbstractItemModel *model);

 private:
  QAbstractItemView *m_view;
  QPointer<QWidget> m_default_widget;
};

}  // namespace qtils

#endif  // QTILS_STACKED_WIDGET_STACKED_WIDGET_H