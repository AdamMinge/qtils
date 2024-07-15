/* ------------------------------------ Qt ---------------------------------- */
#include <QGuiApplication>
#include <QScreen>
/* ----------------------------------- Local -------------------------------- */
#include "qtils/dpi/dpi.h"
/* -------------------------------------------------------------------------- */

namespace qtils {

int defaultDpi() {
  static auto dpi = [] {
    if (const auto screen = QGuiApplication::primaryScreen())
      return static_cast<int>(screen->logicalDotsPerInchX());

#ifdef Q_OS_MAC
    return 72;
#else
    return 96;
#endif
  }();

  return dpi;
}

qreal defaultDpiScale() {
  static auto dpi = [] {
    if (const auto screen = QGuiApplication::primaryScreen())
      return screen->logicalDotsPerInchX() / 96.0;
    return 1.0;
  }();

  return dpi;
}

int dpiScaled(int value) {
  return qRound(dpiScaled(static_cast<qreal>(value)));
}

qreal dpiScaled(qreal value) {
#ifdef Q_OS_MAC
  return value;
#else
  static const auto scale = defaultDpiScale();
  return value * scale;
#endif
}

QSize dpiScaled(const QSize &value) {
  return QSize(dpiScaled(value.width()), dpiScaled(value.height()));
}

QPoint dpiScaled(const QPoint &value) {
  return QPoint(dpiScaled(value.x()), dpiScaled(value.y()));
}

QRectF dpiScaled(const QRectF &value) {
  return QRectF(dpiScaled(value.x()), dpiScaled(value.y()),
                dpiScaled(value.width()), dpiScaled(value.height()));
}

}  // namespace qtils
