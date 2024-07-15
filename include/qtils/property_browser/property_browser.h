/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the tools applications of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QTILS_PROPERTY_BROWSER_PROPERTY_BROWSER_H
#define QTILS_PROPERTY_BROWSER_PROPERTY_BROWSER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QtCore/QSet>
#include <QtWidgets/QWidget>
/* ----------------------------------- Local -------------------------------- */
#include "qtils/property_browser/export.h"
/* -------------------------------------------------------------------------- */

namespace qtils {

class QtAbstractPropertyManager;
class QtPropertyPrivate;

class PROPERTY_BROWSER_API QtProperty {
 public:
  virtual ~QtProperty();

  QList<QtProperty *> subProperties() const;

  QtAbstractPropertyManager *propertyManager() const;

  QString toolTip() const { return valueToolTip(); }  // Compatibility
  QString valueToolTip() const;
  QString descriptionToolTip() const;
  QString statusTip() const;
  QString whatsThis() const;
  QString propertyName() const;
  bool isEnabled() const;
  bool isModified() const;

  bool hasValue() const;
  QIcon valueIcon() const;
  QString valueText() const;

  void setToolTip(const QString &text) {
    setValueToolTip(text);
  }  // Compatibility
  void setValueToolTip(const QString &text);
  void setDescriptionToolTip(const QString &text);
  void setStatusTip(const QString &text);
  void setWhatsThis(const QString &text);
  void setPropertyName(const QString &text);
  void setEnabled(bool enable);
  void setModified(bool modified);

  void addSubProperty(QtProperty *property);
  void insertSubProperty(QtProperty *property, QtProperty *afterProperty);
  void removeSubProperty(QtProperty *property);

 protected:
  explicit QtProperty(QtAbstractPropertyManager *manager);
  void propertyChanged();

 private:
  friend class QtAbstractPropertyManager;
  QScopedPointer<QtPropertyPrivate> d_ptr;
};

class QtAbstractPropertyManagerPrivate;

class PROPERTY_BROWSER_API QtAbstractPropertyManager : public QObject {
  Q_OBJECT
 public:
  explicit QtAbstractPropertyManager(QObject *parent = 0);
  ~QtAbstractPropertyManager();

  QSet<QtProperty *> properties() const;
  void clear() const;

  QtProperty *addProperty(const QString &name = QString());
 Q_SIGNALS:

  void propertyInserted(QtProperty *property, QtProperty *parent,
                        QtProperty *after);
  void propertyChanged(QtProperty *property);
  void propertyRemoved(QtProperty *property, QtProperty *parent);
  void propertyDestroyed(QtProperty *property);

 protected:
  virtual bool hasValue(const QtProperty *property) const;
  virtual QIcon valueIcon(const QtProperty *property) const;
  virtual QString valueText(const QtProperty *property) const;
  virtual void initializeProperty(QtProperty *property) = 0;
  virtual void uninitializeProperty(QtProperty *property);
  virtual QtProperty *createProperty();

 private:
  friend class QtProperty;
  QScopedPointer<QtAbstractPropertyManagerPrivate> d_ptr;
  Q_DECLARE_PRIVATE(QtAbstractPropertyManager)
  Q_DISABLE_COPY_MOVE(QtAbstractPropertyManager)
};

class PROPERTY_BROWSER_API QtAbstractEditorFactoryBase : public QObject {
  Q_OBJECT
 public:
  virtual QWidget *createEditor(QtProperty *property, QWidget *parent) = 0;

 protected:
  explicit QtAbstractEditorFactoryBase(QObject *parent = 0) : QObject(parent) {}

  virtual void breakConnection(QtAbstractPropertyManager *manager) = 0;
 protected Q_SLOTS:
  virtual void managerDestroyed(QObject *manager) = 0;

  friend class QtAbstractPropertyBrowser;
};

template <typename PROPERTY_MANAGER>
class PROPERTY_BROWSER_API QtAbstractEditorFactory
    : public QtAbstractEditorFactoryBase {
 public:
  explicit QtAbstractEditorFactory(QObject *parent)
      : QtAbstractEditorFactoryBase(parent) {}
  QWidget *createEditor(QtProperty *property, QWidget *parent) override {
    for (PROPERTY_MANAGER *manager : qAsConst(m_managers)) {
      if (manager == property->propertyManager()) {
        return createEditor(manager, property, parent);
      }
    }
    return 0;
  }
  void addPropertyManager(PROPERTY_MANAGER *manager) {
    if (m_managers.contains(manager)) return;
    m_managers.insert(manager);
    connectPropertyManager(manager);
    connect(manager, SIGNAL(destroyed(QObject *)), this,
            SLOT(managerDestroyed(QObject *)));
  }
  void removePropertyManager(PROPERTY_MANAGER *manager) {
    if (!m_managers.contains(manager)) return;
    disconnect(manager, SIGNAL(destroyed(QObject *)), this,
               SLOT(managerDestroyed(QObject *)));
    disconnectPropertyManager(manager);
    m_managers.remove(manager);
  }
  QSet<PROPERTY_MANAGER *> propertyManagers() const { return m_managers; }
  PROPERTY_MANAGER *propertyManager(QtProperty *property) const {
    QtAbstractPropertyManager *manager = property->propertyManager();
    for (PROPERTY_MANAGER *m : qAsConst(m_managers)) {
      if (m == manager) {
        return m;
      }
    }
    return 0;
  }

 protected:
  virtual void connectPropertyManager(PROPERTY_MANAGER *manager) = 0;
  virtual QWidget *createEditor(PROPERTY_MANAGER *manager, QtProperty *property,
                                QWidget *parent) = 0;
  virtual void disconnectPropertyManager(PROPERTY_MANAGER *manager) = 0;
  void managerDestroyed(QObject *manager) override {
    for (PROPERTY_MANAGER *m : qAsConst(m_managers)) {
      if (m == manager) {
        m_managers.remove(m);
        return;
      }
    }
  }

 private:
  void breakConnection(QtAbstractPropertyManager *manager) override {
    for (PROPERTY_MANAGER *m : qAsConst(m_managers)) {
      if (m == manager) {
        removePropertyManager(m);
        return;
      }
    }
  }

 private:
  QSet<PROPERTY_MANAGER *> m_managers;
  friend class QtAbstractPropertyEditor;
};

class QtAbstractPropertyBrowser;
class QtBrowserItemPrivate;

class PROPERTY_BROWSER_API QtBrowserItem {
 public:
  QtProperty *property() const;
  QtBrowserItem *parent() const;
  QList<QtBrowserItem *> children() const;
  QtAbstractPropertyBrowser *browser() const;

 private:
  explicit QtBrowserItem(QtAbstractPropertyBrowser *browser,
                         QtProperty *property, QtBrowserItem *parent);
  ~QtBrowserItem();
  QScopedPointer<QtBrowserItemPrivate> d_ptr;
  friend class QtAbstractPropertyBrowserPrivate;
};

class QtAbstractPropertyBrowserPrivate;

class PROPERTY_BROWSER_API QtAbstractPropertyBrowser : public QWidget {
  Q_OBJECT
 public:
  explicit QtAbstractPropertyBrowser(QWidget *parent = 0);
  ~QtAbstractPropertyBrowser();

  QList<QtProperty *> properties() const;
  QList<QtBrowserItem *> items(QtProperty *property) const;
  QtBrowserItem *topLevelItem(QtProperty *property) const;
  QList<QtBrowserItem *> topLevelItems() const;
  void clear();

  template <typename PROPERTY_MANAGER>
  void setFactoryForManager(
      PROPERTY_MANAGER *manager,
      QtAbstractEditorFactory<PROPERTY_MANAGER> *factory) {
    QtAbstractPropertyManager *abstractManager = manager;
    QtAbstractEditorFactoryBase *abstractFactory = factory;

    if (addFactory(abstractManager, abstractFactory))
      factory->addPropertyManager(manager);
  }

  void unsetFactoryForManager(QtAbstractPropertyManager *manager);

  QtBrowserItem *currentItem() const;
  void setCurrentItem(QtBrowserItem *);

 Q_SIGNALS:
  void currentItemChanged(QtBrowserItem *);

 public Q_SLOTS:

  QtBrowserItem *addProperty(QtProperty *property);
  QtBrowserItem *insertProperty(QtProperty *property,
                                QtProperty *afterProperty);
  void removeProperty(QtProperty *property);

 protected:
  virtual void itemInserted(QtBrowserItem *item, QtBrowserItem *afterItem) = 0;
  virtual void itemRemoved(QtBrowserItem *item) = 0;
  // can be tooltip, statustip, whatsthis, name, icon, text.
  virtual void itemChanged(QtBrowserItem *item) = 0;

  virtual QWidget *createEditor(QtProperty *property, QWidget *parent);

 private:
  bool addFactory(QtAbstractPropertyManager *abstractManager,
                  QtAbstractEditorFactoryBase *abstractFactory);

  QScopedPointer<QtAbstractPropertyBrowserPrivate> d_ptr;
  Q_DECLARE_PRIVATE(QtAbstractPropertyBrowser)
  Q_DISABLE_COPY_MOVE(QtAbstractPropertyBrowser)
  Q_PRIVATE_SLOT(d_func(), void slotPropertyInserted(QtProperty *, QtProperty *,
                                                     QtProperty *))
  Q_PRIVATE_SLOT(d_func(), void slotPropertyRemoved(QtProperty *, QtProperty *))
  Q_PRIVATE_SLOT(d_func(), void slotPropertyDestroyed(QtProperty *))
  Q_PRIVATE_SLOT(d_func(), void slotPropertyDataChanged(QtProperty *))
};

}  // namespace qtils

#endif  // QTPROPERTYBROWSER_H