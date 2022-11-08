/* SPDX-License-Identifier: Apache-2.0 */

#pragma once

#include "function/Extension.h"
#include "function/FunctionMapping.h"
#include "function/FunctionSignature.h"

namespace io::substrait {

class FunctionLookup {
 public:
  FunctionLookup(
      const ExtensionPtr& extension,
      const FunctionMappingPtr& functionMapping)
      : extension_(extension), functionMapping_(functionMapping) {}

  virtual FunctionVariantPtr lookupFunction(
      const FunctionSignature& signature) const;

  virtual ~FunctionLookup() {}

 protected:
  virtual const FunctionMap getFunctionMap() const = 0;

  virtual const FunctionVariantMap& getFunctionVariants() const = 0;

  const FunctionMappingPtr functionMapping_;

  ExtensionPtr extension_;
};

using FunctionLookupPtr = std::shared_ptr<const FunctionLookup>;

class ScalarFunctionLookup : public FunctionLookup {
 public:
  ScalarFunctionLookup(
      const ExtensionPtr& extension,
      const FunctionMappingPtr& functionMapping)
      : FunctionLookup(extension, functionMapping) {}

 protected:
  const FunctionMap getFunctionMap() const override {
    return functionMapping_->scalaMapping();
  }

  const FunctionVariantMap& getFunctionVariants() const override {
    return extension_->scalaFunctionVariantMap();
  }
};

class AggregateFunctionLookup : public FunctionLookup {
 public:
  AggregateFunctionLookup(
      const ExtensionPtr& extension,
      const FunctionMappingPtr& functionMapping)
      : FunctionLookup(extension, functionMapping) {}

 protected:
  const FunctionMap getFunctionMap() const override {
    return functionMapping_->aggregateMapping();
  }

  const FunctionVariantMap& getFunctionVariants() const override {
    return extension_->aggregateFunctionVariantMap();
  }
};

class WindowFunctionLookup : public FunctionLookup {
 public:
  WindowFunctionLookup(
      const ExtensionPtr& extension,
      const FunctionMappingPtr& functionMapping)
      : FunctionLookup(extension, functionMapping) {}

 protected:
  const FunctionMap getFunctionMap() const override {
    return functionMapping_->windowMapping();
  }

  const FunctionVariantMap& getFunctionVariants() const override {
    return extension_->windowFunctionVariantMap();
  }
};

} // namespace io::substrait
