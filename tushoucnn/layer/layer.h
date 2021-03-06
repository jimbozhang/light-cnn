// Copyright 2017-2018  Junbo Zhang
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
// THIS CODE IS PROVIDED *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED
// WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE,
// MERCHANTABLITY OR NON-INFRINGEMENT.
// See the Apache 2 License for the specific language governing permissions and
// limitations under the License.

#ifndef TUSHOUCNN_LAYER_LAYER_H
#define TUSHOUCNN_LAYER_LAYER_H

#include <string>
#include <vector>
#include <map>
#include "base/tensor.h"

namespace tushoucnn {

typedef std::map<std::string, std::string> LayerHParams;

class Layer {
public:
  virtual Tensor &fprop(Tensor &data) {
    return data;
  }

  void load_hparams(LayerHParams &hparams) {
    hparams_ = hparams;
  }

  virtual void load_params() {}

protected:
  LayerHParams hparams_;

  std::vector<FeatType> read_params_file(std::string key) {
    std::vector<FeatType> params;
    if (hparams_.find(key) != hparams_.end()) {
      std::ifstream fin;
      fin.open(hparams_[key].c_str());
      assert(fin.is_open());
      while (! fin.eof()) {
        FeatType tok;
        fin >> tok;
        params.push_back(tok);
      }
      fin.close();
    }
    return params;
  }
};

} // namespace tushoucnn
#endif // TUSHOUCNN_LAYER_LAYER_H_
