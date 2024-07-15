/* ---------------------------------- Standard------------------------------- */
#include <stack>
/* ----------------------------------- Local--------------------------------- */
#include "qtils/stacked_widget/stacked_widget.h"
#include "qtils/stacked_widget/stacked_widget_tree_model.h"
/* -------------------------------------------------------------------------- */

namespace qtils {

QtStackedWidget::QtStackedWidget(QWidget *parent)
    : QStackedWidget(parent), m_view(nullptr), m_default_widget(nullptr) {
  setView(nullptr);
  setDefaultWidget(new QWidget(this));
}

QtStackedWidget::~QtStackedWidget() = default;

void QtStackedWidget::setView(QAbstractItemView *view) {
  if (m_view == view) return;

  if (m_view && m_view->selectionModel()) {
    disconnect(m_view->selectionModel(), &QItemSelectionModel::selectionChanged,
               this, &QtStackedWidget::selectionChanged);
    disconnect(m_view->selectionModel(), &QItemSelectionModel::modelChanged,
               this, &QtStackedWidget::modelChanged);
  }

  m_view = view;

  if (m_view && m_view->selectionModel()) {
    connect(m_view->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &QtStackedWidget::selectionChanged);
    connect(m_view->selectionModel(), &QItemSelectionModel::modelChanged, this,
            &QtStackedWidget::modelChanged);
  }

  modelChanged(m_view ? m_view->model() : nullptr);
  selectionChanged(QItemSelection{}, QItemSelection{});
}

void QtStackedWidget::setDefaultWidget(QWidget *widget) {
  Q_ASSERT(widget);
  if (m_default_widget) m_default_widget->deleteLater();
  m_default_widget = widget;

  modelChanged(m_view ? m_view->model() : nullptr);
  selectionChanged(QItemSelection{}, QItemSelection{});
}

const QWidget *QtStackedWidget::getDefaultWidget() const {
  return m_default_widget;
}

const QAbstractItemView *QtStackedWidget::getView() const { return m_view; }

void QtStackedWidget::selectionChanged(const QItemSelection &selected,
                                       const QItemSelection &deselected) {
  const auto selected_indexes = selected.indexes();
  if (!selected_indexes.empty()) {
    const auto current_index = selected_indexes.front();
    auto current_widget =
        current_index.data(QtStackedWidgetTreeModel::Role::WidgetRole)
            .value<QWidget *>();

    if (current_widget) setCurrentWidget(current_widget);
  } else if (!deselected.empty()) {
    setCurrentWidget(m_default_widget);
  }
}

void QtStackedWidget::modelChanged(QAbstractItemModel *model) {
  for (auto i = 0; i < count(); ++i) removeWidget(widget(i));

  addWidget(m_default_widget);
  if (model) {
    auto widgets = getStackedWidgets(model);
    for (auto widget : widgets) addWidget(widget);
  }
}

QList<QWidget *> QtStackedWidget::getStackedWidgets(
    const QAbstractItemModel *model) {
  auto stacked_widgets = QList<QWidget *>{};
  auto indexes_to_process = std::stack<QModelIndex>{};

  for (auto row = 0; row < model->rowCount(QModelIndex{}); ++row)
    indexes_to_process.push(model->index(row, 0, QModelIndex{}));

  while (!indexes_to_process.empty()) {
    auto current_index = indexes_to_process.top();
    indexes_to_process.pop();

    if (current_index.isValid()) {
      for (auto row = 0; row < model->rowCount(current_index); ++row)
        indexes_to_process.push(model->index(row, 0, current_index));

      auto widget =
          current_index.data(QtStackedWidgetTreeModel::Role::WidgetRole)
              .value<QWidget *>();

      if (widget && !stacked_widgets.contains(widget))
        stacked_widgets.append(widget);
    }
  }

  return stacked_widgets;
}

}  // namespace qtils
