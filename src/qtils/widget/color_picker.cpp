/* ----------------------------------- Local -------------------------------- */
#include "qtils/widget/color_picker.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QColorDialog>
#include <QCoreApplication>
#include <QEvent>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QPainter>
/* -------------------------------------------------------------------------- */

namespace qtils {

QtColorPicker::QtColorPicker(QWidget *parent)
    : QWidget(parent),
      m_pixmap_label(new QLabel),
      m_label(new QLabel),
      m_button(new QToolButton) {
  QHBoxLayout *lt = new QHBoxLayout(this);
  lt->setContentsMargins(4, 0, 0, 0);
  lt->setSpacing(0);
  lt->addWidget(m_pixmap_label);
  lt->addWidget(m_label);
  lt->addItem(
      new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Ignored));

  m_button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Ignored);
  m_button->setFixedWidth(20);
  setFocusProxy(m_button);
  setFocusPolicy(m_button->focusPolicy());
  m_button->setText(tr("..."));
  m_button->installEventFilter(this);
  connect(m_button, SIGNAL(clicked()), this, SLOT(buttonClicked()));
  lt->addWidget(m_button);
  m_pixmap_label->setPixmap(brushValuePixmap(QBrush(m_color)));
  m_label->setText(colorValueText(m_color));
}

void QtColorPicker::setValue(const QColor &c) {
  if (m_color != c) {
    m_color = c;
    m_pixmap_label->setPixmap(brushValuePixmap(QBrush(c)));
    m_label->setText(colorValueText(c));
  }
}

void QtColorPicker::buttonClicked() {
  const QColor newColor = QColorDialog::getColor(
      m_color, this, QString(), QColorDialog::ShowAlphaChannel);
  if (newColor.isValid() && newColor != m_color) {
    setValue(newColor);
    emit valueChanged(m_color);
  }
}

bool QtColorPicker::eventFilter(QObject *obj, QEvent *ev) {
  if (obj == m_button) {
    switch (ev->type()) {
      case QEvent::KeyPress:
      case QEvent::KeyRelease: {
        switch (static_cast<const QKeyEvent *>(ev)->key()) {
          case Qt::Key_Escape:
          case Qt::Key_Enter:
          case Qt::Key_Return:
            ev->ignore();
            return true;
          default:
            break;
        }
      } break;
      default:
        break;
    }
  }
  return QWidget::eventFilter(obj, ev);
}

QPixmap QtColorPicker::brushValuePixmap(const QBrush &b) const {
  QImage img(16, 16, QImage::Format_ARGB32_Premultiplied);
  img.fill(0);

  QPainter painter(&img);
  painter.setCompositionMode(QPainter::CompositionMode_Source);
  painter.fillRect(0, 0, img.width(), img.height(), b);
  QColor color = b.color();
  if (color.alpha() != 255) {  // indicate alpha by an inset
    QBrush opaqueBrush = b;
    color.setAlpha(255);
    opaqueBrush.setColor(color);
    painter.fillRect(img.width() / 4, img.height() / 4, img.width() / 2,
                     img.height() / 2, opaqueBrush);
  }
  painter.end();
  return QPixmap::fromImage(img);
}

QString QtColorPicker::colorValueText(const QColor &c) const {
  return tr("[%1, %2, %3] (%4)")
      .arg(c.red())
      .arg(c.green())
      .arg(c.blue())
      .arg(c.alpha());
}

}  // namespace qtils