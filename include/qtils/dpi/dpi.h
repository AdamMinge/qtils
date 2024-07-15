#ifndef QTILS_DPI_DPI_H
#define QTILS_DPI_DPI_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QPoint>
#include <QRectF>
#include <QSize>
#include <QtGlobal>
/* ----------------------------------- Local -------------------------------- */
#include "qtils/dpi/export.h"
/* -------------------------------------------------------------------------- */

namespace qtils {

[[nodiscard]] DPI_API int defaultDpi();
[[nodiscard]] DPI_API qreal defaultDpiScale();

[[nodiscard]] DPI_API int dpiScaled(int value);
[[nodiscard]] DPI_API qreal dpiScaled(qreal value);
[[nodiscard]] DPI_API QSize dpiScaled(const QSize &value);
[[nodiscard]] DPI_API QPoint dpiScaled(const QPoint &value);
[[nodiscard]] DPI_API QRectF dpiScaled(const QRectF &value);

}  // namespace qtils

#endif  // QTILS_DPI_DPI_H
