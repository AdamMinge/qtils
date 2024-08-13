#ifndef QTILS_WIDGET_COLOR_PICKER_H
#define QTILS_WIDGET_COLOR_PICKER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QColor>
#include <QLabel>
#include <QToolButton>
#include <QWidget>
/* ----------------------------------- Local -------------------------------- */
#include "qtils/widget/export.h"
/* -------------------------------------------------------------------------- */

namespace qtils {

class WIDGET_API QtColorPicker : public QWidget {
  Q_OBJECT

 public:
  QtColorPicker(QWidget *parent);

  bool eventFilter(QObject *obj, QEvent *ev) override;

 public Q_SLOTS:
  void setValue(const QColor &value);

 private Q_SLOTS:
  void buttonClicked();

 Q_SIGNALS:
  void valueChanged(const QColor &value);

 private:
  QPixmap brushValuePixmap(const QBrush &b) const;
  QString colorValueText(const QColor &c) const;

 private:
  QColor m_color;
  QLabel *m_pixmap_label;
  QLabel *m_label;
  QToolButton *m_button;
};

}  // namespace qtils

#endif  // QTILS_WIDGET_COLOR_PICKER_H