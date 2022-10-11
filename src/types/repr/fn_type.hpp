#pragma once

#include <types/repr/builtins.hpp>

#include <types/type.hpp>

#include <fmt/format.h>

#include <vector>

namespace types {

class FnType : public Type {
 public:
  FnType(std::vector<Type*> arg_types, Type* return_type = &builtin_unit)
      : arg_types_{arg_types}, return_type_{return_type} {
    FMT_ASSERT(return_type_, "Nullptr return type");
  }

  bool IsEqual(Type* other) override {
    return other->IsEqual(this);
  }

  bool IsEqual(PointerType*) override {
    return false;
  }

  bool IsEqual(BuiltinType*) override {
    // TODO: is builtin a function taking no arguments?
    return false;
  }

  bool IsEqual(StructType*) override {
    return false;
  }

  bool IsEqual(FnType* other) override {
    if (!return_type_->IsEqual(other->return_type_) ||
        arg_types_.size() != other->arg_types_.size()) {
      return false;
    }

    for (std::size_t i = 0; i < arg_types_.size(); i++) {
      if (!arg_types_[i]->IsEqual(other->arg_types_[i])) {
        return false;
      }
    }

    return true;
  }

  Type* GetReturnType() {
    return return_type_;
  }

 private:
  std::vector<Type*> arg_types_;
  Type* return_type_ = nullptr;
};

}  // namespace types
