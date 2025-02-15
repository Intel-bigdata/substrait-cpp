/* SPDX-License-Identifier: Apache-2.0 */

#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "substrait/function/Function.h"
#include "substrait/function/FunctionSignature.h"
#include "substrait/type/Type.h"

namespace io::substrait {

struct TypeVariant {
  std::string name;
  std::string uri;
};

using TypeVariantPtr = std::shared_ptr<TypeVariant>;

using FunctionVariantMap =
    std::unordered_map<std::string, std::vector<FunctionImplementationPtr>>;

using TypeVariantMap = std::unordered_map<std::string, TypeVariantPtr>;

class Extension {
 public:
  /// Deserialize default substrait extension by given basePath
  /// @throws exception if file not found
  static std::shared_ptr<Extension> load(const std::string& basePath);

  /// Deserialize substrait extension by given basePath and extensionFiles.
  static std::shared_ptr<Extension> load(
      const std::string& basePath,
      const std::vector<std::string>& extensionFiles);

  /// Deserialize substrait extension by given extensionFiles.
  static std::shared_ptr<Extension> load(
      const std::vector<std::string>& extensionFiles);

  /// Add a scalar function variant.
  void addScalarFunctionVariant(const FunctionImplementationPtr& functionVariant);

  /// Add a aggregate function variant.
  void addAggregateFunctionVariant(const FunctionImplementationPtr& functionVariant);

  /// Add a window function variant.
  void addWindowFunctionVariant(const FunctionImplementationPtr& functionVariant);

  /// Add a type variant.
  void addTypeVariant(const TypeVariantPtr& functionVariant);

  /// Lookup type variant by given type name.
  /// @return matched type variant
  TypeVariantPtr lookupType(const std::string& typeName) const;

  const FunctionVariantMap& scalaFunctionVariantMap() const {
    return scalarFunctionVariantMap_;
  }

  const FunctionVariantMap& windowFunctionVariantMap() const {
    return windowFunctionVariantMap_;
  }

  const FunctionVariantMap& aggregateFunctionVariantMap() const {
    return aggregateFunctionVariantMap_;
  }

 private:
  FunctionVariantMap scalarFunctionVariantMap_;

  FunctionVariantMap aggregateFunctionVariantMap_;

  FunctionVariantMap windowFunctionVariantMap_;

  TypeVariantMap typeVariantMap_;
};

using ExtensionPtr = std::shared_ptr<const Extension>;

} // namespace io::substrait
