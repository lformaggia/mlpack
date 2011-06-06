/**
 * @file main.cc
 * @author Chip Mappus
 *
 * main for using infomax ICA method.
 */

#include "infomax_ica.h"
#include "test_infomax_ica.h"
#include <fastlib/fastlib.h>
#include <fastlib/fx/io.h>
#include <fastlib/data/dataset.h>

#include <armadillo>
#include <fastlib/base/arma_compat.h>



PARAM_STRING_REQ("data", "The name of the file containing mixture data.", "info");


using namespace mlpack;

int main(int argc, char *argv[]) {
  IO::ParseCommandLine(argc, argv);

  const char *data_file_name = IO::GetValue<std::string>("info/data").c_str();
  double lambda = IO::GetValue<double>("info/lambda");
  int B = IO::GetValue<int>("info/B");
  double epsilon = IO::GetValue<double>("info/epsilon");

  Matrix dataset;
  arma::mat tmp_dataset;
  data::Load(data_file_name, tmp_dataset);
  arma_compat::armaToMatrix(tmp_dataset, dataset);
  InfomaxICA *ica = new InfomaxICA(lambda, B, epsilon);

  ica->applyICA(dataset);  
  Matrix west;
  ica->getUnmixing(west);
  //ica->displayMatrix(west);
}
