#ifndef QTILS_POINTER_LAZY_PTR_H
#define QTILS_POINTER_LAZY_PTR_H

/* ---------------------------------- Standard ------------------------------ */
#include <memory>
/* ----------------------------------- Local -------------------------------- */
#include "qtils/pointer/export.h"
/* -------------------------------------------------------------------------- */

namespace qtils {

template <typename T>
class lazy_ptr {
 public:
  explicit lazy_ptr(std::function<T*()> init) : m_initializer(init) {}

  T& operator*() {
    ensure_initialized();
    return *m_ptr;
  }

  T* operator->() {
    ensure_initialized();
    return m_ptr.get();
  }

  bool is_initialized() const { return static_cast<bool>(m_ptr); }
  void initialize() { ensure_initialized(); }

 private:
  void ensure_initialized() {
    if (!m_ptr) {
      m_ptr.reset(m_initializer());
    }
  }

 private:
  std::unique_ptr<T> m_ptr;
  std::function<T*()> m_initializer;
};

}  // namespace qtils

#endif  // QTILS_POINTER_LAZY_PTR_H
