/*
 * Copyright (c) 2019 Samsung Electronics Co., Ltd. All Rights Reserved
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

#ifndef __LOGO_REORDER_DECODE_PASS_H__
#define __LOGO_REORDER_DECODE_PASS_H__

#include <logo/Pass.h>

#include <loco.h>
#include <loco/IR/Nodes.h>

namespace logo
{

/**
 * @brief Reorder XXXDecode -> ? as ? -> XXXDecode if possible
 *
 * This transformation increases the chance of domain conversion simplification.
 */
template <typename T> struct ReorderDecodePass;

template <> struct ReorderDecodePass<loco::TensorBiasAdd> final : public Pass
{
  const char *name(void) const final { return "ReorderDecodePass<TensorBiasAdd> "; }

  bool run(loco::Graph *g);
};

template <> struct ReorderDecodePass<loco::ReLU> final : public Pass
{
  const char *name(void) const final { return "ReorderDecodePass<ReLU> "; }

  bool run(loco::Graph *g);
};

} // namespace logo

#endif // __LOGO_REORDER_DECODE_PASS_H__
