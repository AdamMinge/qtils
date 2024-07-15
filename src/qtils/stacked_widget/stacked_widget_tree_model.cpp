/* ----------------------------------- Local--------------------------------- */
#include "qtils/stacked_widget/stacked_widget_tree_model.h"
/* -------------------------------------------------------------------------- */

namespace qtils {

/* ------------------------- QtStackedWidgetTreeItem----------------------- */

QtStackedWidgetTreeItem::QtStackedWidgetTreeItem(
    QWidget *widget, QIcon icon,
    std::initializer_list<QtStackedWidgetTreeItem *> children)
    : m_parent(nullptr), m_icon(std::move(icon)), m_widget(widget) {
  std::for_each(children.begin(), children.end(),
                [this](auto child) { addChild(child); });
}

QtStackedWidgetTreeItem::~QtStackedWidgetTreeItem() { qDeleteAll(m_children); }

QtStackedWidgetTreeItem *QtStackedWidgetTreeItem::getParent() {
  return m_parent;
}

void QtStackedWidgetTreeItem::addChild(QtStackedWidgetTreeItem *child) {
  if (!m_children.contains(child)) {
    if (child->m_parent) child->m_parent->removeChild(child);

    m_children.append(child);
    child->m_parent = this;
  }
}

void QtStackedWidgetTreeItem::removeChild(QtStackedWidgetTreeItem *child) {
  if (m_children.contains(child)) {
    m_children.removeOne(child);
    child->m_parent = nullptr;
  }
}

const QtStackedWidgetTreeItem *QtStackedWidgetTreeItem::getChild(
    int row) const {
  if (row < 0 || row >= m_children.size()) return nullptr;
  return m_children.at(row);
}

QtStackedWidgetTreeItem *QtStackedWidgetTreeItem::getChild(int row) {
  if (row < 0 || row >= m_children.size()) return nullptr;
  return m_children.at(row);
}

int QtStackedWidgetTreeItem::getChildCount() const {
  return static_cast<int>(m_children.size());
}

int QtStackedWidgetTreeItem::findChild(QtStackedWidgetTreeItem *child) const {
  return static_cast<int>(m_children.indexOf(child));
}

void QtStackedWidgetTreeItem::setWidget(QWidget *widget) { m_widget = widget; }

QWidget *QtStackedWidgetTreeItem::getWidget() const { return m_widget; }

void QtStackedWidgetTreeItem::setIcon(QIcon icon) { m_icon = std::move(icon); }

QIcon QtStackedWidgetTreeItem::getIcon() const { return m_icon; }

/* ------------------------- QtStackedWidgetTreeModel---------------------- */

QtStackedWidgetTreeModel::QtStackedWidgetTreeModel(QObject *parent)
    : QAbstractItemModel(parent) {}

QtStackedWidgetTreeModel::~QtStackedWidgetTreeModel() {
  qDeleteAll(m_root_items);
}

void QtStackedWidgetTreeModel::append(QtStackedWidgetTreeItem *item,
                                      const QModelIndex &parent) {
  if (parent.isValid()) {
    auto parent_item =
        static_cast<QtStackedWidgetTreeItem *>(parent.internalPointer());
    Q_ASSERT(parent_item);

    const auto row = parent_item->getChildCount();
    beginInsertRows(parent, row, row);
    parent_item->addChild(item);
    endInsertRows();
  } else {
    const auto row = static_cast<int>(m_root_items.count());
    beginInsertRows(parent, row, row);
    m_root_items.append(item);
    endInsertRows();
  }
}

void QtStackedWidgetTreeModel::remove(const QModelIndex &index) {
  auto item = static_cast<QtStackedWidgetTreeItem *>(index.internalPointer());
  Q_ASSERT(item);

  if (auto parent_item = item->getParent(); parent_item) {
    const auto row = parent_item->findChild(item);
    beginRemoveRows(index.parent(), row, row);
    parent_item->removeChild(item);
    endRemoveRows();
  } else {
    const auto row = static_cast<int>(m_root_items.indexOf(item));
    beginRemoveRows(index.parent(), row, row);
    m_root_items.removeOne(item);
    endRemoveRows();
  }
}

Qt::ItemFlags QtStackedWidgetTreeModel::flags(const QModelIndex &index) const {
  auto widget = data(index, Role::WidgetRole).value<QWidget *>();
  auto flags =
      index.isValid() ? QAbstractItemModel::flags(index) : Qt::NoItemFlags;

  if (!widget) flags &= ~Qt::ItemIsSelectable;
  return flags;
}

QVariant QtStackedWidgetTreeModel::data(const QModelIndex &index,
                                        int role) const {
  if (!index.isValid()) return QVariant{};

  auto item = static_cast<QtStackedWidgetTreeItem *>(index.internalPointer());
  switch (role) {
    case Qt::DisplayRole:
    case Role::NameRole:
      return item->getWidget()->windowTitle();

    case Role::WidgetRole:
      return QVariant::fromValue(item->getWidget());

    case Role::ObjectNameRole:
      return item->getWidget()->objectName();

    case Qt::DecorationRole:
    case Role::IconRole:
      return item->getIcon();

    default:
      return QVariant{};
  }
}

QVariant QtStackedWidgetTreeModel::headerData(int section,
                                              Qt::Orientation orientation,
                                              int role) const {
  if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
    return QVariant{};

  switch (section)  // NOLINT(hicpp-multiway-paths-covered)
  {
    case Column::NameColumn:
      return tr("Name");
    default:
      return QVariant{};
  }
}

QModelIndex QtStackedWidgetTreeModel::index(int row, int column,
                                            const QModelIndex &parent) const {
  QtStackedWidgetTreeItem *parent_item{nullptr};
  if (parent.isValid()) {
    parent_item =
        static_cast<QtStackedWidgetTreeItem *>(parent.internalPointer());
    return createIndex(row, column, parent_item->getChild(row));
  } else {
    return createIndex(row, column, m_root_items.at(row));
  }
}

QModelIndex QtStackedWidgetTreeModel::parent(const QModelIndex &index) const {
  if (!index.isValid()) return QModelIndex{};

  auto child_item =
      static_cast<QtStackedWidgetTreeItem *>(index.internalPointer());
  auto item = child_item->getParent();

  if (m_root_items.contains(item)) {
    auto row = static_cast<int>(m_root_items.indexOf(item));
    return createIndex(row, 0, item);
  } else {
    auto parent_item = item ? item->getParent() : nullptr;
    if (!parent_item) return QModelIndex{};

    auto row = parent_item->findChild(item);
    return createIndex(row, 0, item);
  }
}

int QtStackedWidgetTreeModel::rowCount(const QModelIndex &parent) const {
  if (!parent.isValid())
    return static_cast<int>(m_root_items.size());
  else
    return static_cast<QtStackedWidgetTreeItem *>(parent.internalPointer())
        ->getChildCount();
}

int QtStackedWidgetTreeModel::columnCount(const QModelIndex &parent) const {
  return 1;
}

QModelIndex QtStackedWidgetTreeModel::getIndexBy(
    Role role, const QVariant &value, const QModelIndex &parent) const {
  return getIndexBy(*this, role, value, parent);
}

QModelIndex QtStackedWidgetTreeModel::getIndexBy(
    const QAbstractItemModel &model, Role role, const QVariant &value,
    const QModelIndex &parent) {
  for (auto row = 0; row < model.rowCount(parent); ++row) {
    const auto current_index = model.index(row, 0, parent);
    const auto current_value = model.data(current_index, role);

    if (value == current_value) return current_index;

    if (auto index = getIndexBy(model, role, value, current_index);
        index.isValid())
      return index;
  }

  return QModelIndex{};
}

}  // namespace qtils
