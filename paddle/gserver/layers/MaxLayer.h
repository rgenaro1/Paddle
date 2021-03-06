/* Copyright (c) 2016 Baidu, Inc. All Rights Reserve.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License. */


#pragma once

#include "Layer.h"
#include "paddle/math/Matrix.h"
#include "paddle/utils/ThreadLocal.h"

namespace paddle {

/**
 * A layer for "internal max" for sequence input.
 * Input: one or more sequences. Each sequence contains some instances.
 * If MaxLevel = kNonSeq:
 *    Output: output size is the number of input sequences (NOT input instances)
 *    output[i] = max_{for each instance in this sequence}{input[i]}
 * If MaxLevel = kSeq:
 *    Check input sequence must has sub-sequence
 *    Output: output size is the number of input sub-sequences
 *    output[i] = max_{for each instance in this sub-sequence}{input[i]}
 */

class MaxLayer : public Layer {
protected:
  std::unique_ptr<Weight> biases_;
  // maxIndex_[i][j] = k : the value at (i, j) is from input[k].
  IVectorPtr maxIndex_;
  int type_;

public:
  explicit MaxLayer(const LayerConfig& config) : Layer(config) {}
  enum MaxLevel {kNonSeq = 0, kSeq = 1 };

  ~MaxLayer() {}

  bool init(const LayerMap& layerMap, const ParameterMap& parameterMap);

  void forward(PassType passType);
  void backward(const UpdateCallback& callback = nullptr);
};

}  // namespace paddle
