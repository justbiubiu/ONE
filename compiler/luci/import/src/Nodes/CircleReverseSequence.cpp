/*
 * Copyright (c) 2020 Samsung Electronics Co., Ltd. All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "luci/Import/Nodes/CircleReverseSequence.h"

#include <luci/IR/Nodes/CircleReverseSequence.h>

#include <loco.h>

namespace luci
{

bool CircleReverseSequenceGraphBuilder::validate(const ValidateArgs &args) const
{
  const auto &inputs = args.op.inputs;
  const auto &outputs = args.op.outputs;

  if (inputs.size() != 2)
    return false;
  if (outputs.size() != 1)
    return false;

  const auto &tensors = args.reader.tensors();
  const auto &tensor_in = tensors.at(inputs.at(0));
  const auto &tensor_lengths = tensors.at(inputs.at(1));
  const auto &tensor_out = tensors.at(outputs[0]);

  switch (tensor_lengths->type)
  {
    case circle::TensorType_INT32:
    case circle::TensorType_INT64:
      break;
    default:
      return false;
  }

  if (tensor_in->type != tensor_out->type)
    return false;

  return true;
}

CircleNode *CircleReverseSequenceGraphBuilder::build_node(const circle::OperatorT &op,
                                                          const std::vector<CircleNode *> &inputs,
                                                          loco::Graph *graph) const
{
  auto *node = graph->nodes()->create<CircleReverseSequence>();
  node->input(inputs.at(0));
  node->seq_lengths(inputs.at(1));

  const auto *options = op.builtin_options.AsReverseSequenceOptions();
  node->seq_axis(options->seq_dim);
  node->batch_axis(options->batch_dim);

  return node;
}

} // namespace luci
