#pragma once
//------------------------------------------------------------------------------
//
//   Copyright 2018-2019 Fetch.AI Limited
//
//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.
//
//------------------------------------------------------------------------------

#include "ops.hpp"

namespace fetch {
namespace ml {
namespace ops {

template <class T>
class InplaceTranspose : public fetch::ml::BatchOps<T, 2>
{
public:
  using ArrayType    = T;
  using SizeType       = typename ArrayType::SizeType;

  InplaceTranspose()          = default;
  virtual ~InplaceTranspose() = default;

  ArrayType Forward(std::vector<std::reference_wrapper<ArrayType const>> const &inputs,
                    ArrayType &                                                 output)
  {
    (void)output; // Transposing input inplace
    assert(inputs.size() == 1);
    return inputs.front().get().Transpose();
  }

  virtual std::vector<ArrayType> Backward(
      std::vector<std::reference_wrapper<ArrayType const>> const &inputs,
      ArrayType const &                                           errorSignal,
      std::vector<ArrayType>                                     &output)
  {
    assert(inputs.size() == 1 && output.size() == 1);
    output[0] = errorSignal.Transpose();
    return output;
  }

  std::array<SizeType, 2> ComputeOutputShape(
      std::vector<std::reference_wrapper<ArrayType const>> const &inputs) const
  {
    return {inputs.front().get().shape()[1], inputs.front().get().shape()[0]};
  }

  
  static constexpr char const *DESCRIPTOR = "Transpose";
};

}  // namespace ops
}  // namespace ml
}  // namespace fetch
