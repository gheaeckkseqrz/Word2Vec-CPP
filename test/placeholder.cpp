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

#include "placeholder.hpp"
#include "tensor.hpp"
#include <gtest/gtest.h>

using ArrayType = fetch::math::Tensor<int, 1>;

TEST(placeholder_test, setData)
{
  ArrayType data({8});
  for (uint64_t i(0) ; i < data.Size() ; ++i)
  {
    data.Set(i, i);
  }
  fetch::ml::ops::PlaceHolder<ArrayType, 1> op;
  op.SetData(data);
  ArrayType prediction = op.fetch::ml::template Ops<ArrayType, 1>::Forward({});
  for (uint64_t i(0) ; i < data.Size() ; ++i)
  {
    EXPECT_EQ(data.Get(i), i);
  }  
}

// TEST(placeholder_test, resetData)
// {
//   fetch::math::Tensor<int> data(8);
//   fetch::math::Tensor<int> gt(8);
//   {
//     std::uint64_t i(0);
//     for (int e : {1, 2, 3, 4, 5, 6, 7, 8})
//     {
//       data.Set(i, e);
//       gt.Set(i, e);
//       i++;
//     }
//   }
//   fetch::ml::ops::PlaceHolder<fetch::math::Tensor<int>> op;
//   op.SetData(data);
//   fetch::math::Tensor<int> prediction = op.Forward({});

//   // test correct values
//   ASSERT_TRUE(prediction.AllClose(gt));

//   // reset
//   {
//     std::uint64_t i(0);
//     for (int e : {12, 13, -14, 15, 16, -17, 18, 19})
//     {
//       data.Set(i, e);
//       gt.Set(i, e);
//       i++;
//     }
//   }

//   op.SetData(data);
//   prediction = op.Forward({});

//   // test correct values
//   ASSERT_TRUE(prediction.AllClose(gt));
// }