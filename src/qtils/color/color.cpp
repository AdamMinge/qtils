/* ----------------------------------- Local -------------------------------- */
#include "qtils/color/color.h"
/* -------------------------------------------------------------------------- */

namespace qtils {

QString getColorName(const QColor &color) {
  static const auto color_names = QColor::colorNames();
  for (const auto &color_name : color_names)
    if (QColor(color_name) == color) return color_name;

  return QString{};
}

}  // namespace qtils