#ifndef QTILS_COLOR_COLOR_H
#define QTILS_COLOR_COLOR_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QColor>
#include <QString>
/* ----------------------------------- Local -------------------------------- */
#include "qtils/color/export.h"
/* -------------------------------------------------------------------------- */

namespace qtils {

[[nodiscard]] COLOR_API QString getColorName(const QColor &color);

}  // namespace qtils

#endif  // QTILS_COLOR_COLOR_H
