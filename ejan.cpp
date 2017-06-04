#include <stdio.h> //argc, *argv[]
#include <sys/stat.h> //stat

#include <iostream> //cout, endl
#include <tuple> //tuple
#include <string> //string
#include <cstdlib> //EXIT_SUCCESS, EXIT_FAILURE

#include <omp.h> //openmp

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>


int main(int argc, char *argv[]) {
  using namespace std;
  using namespace cv;

  if (argc != 2) {
    cout << "need image path" <<endl;
    return EXIT_FAILURE;
  }

  const char* FILEPATH = argv[1];
  struct stat isExists;

  if (stat(FILEPATH, &isExists) != 0) {
    cout << "cannot find: " << FILEPATH << endl;
    return EXIT_FAILURE;
  }

  const int R = 2;
  const int G = 1;
  const int B = 0;

  #ifdef _OPENMP
  omp_lock_t locker;
  omp_init_lock(&locker);
  #endif

  Mat image = imread(FILEPATH);
  const int RES = image.rows * image.cols;

  set<tuple<int, int, int>> st;

//  cout
//    << "res: " << RES
//    << "(x :" << image.cols
//    << ", y :" << image.rows
//    << ")" << endl;
//  int progress = 0;
//  cout << "starting.." << endl;

  for(int y = 0; y < image.rows; ++y){
    Vec3b *src = image.ptr<Vec3b>(y);
    #ifdef _OPENMP
    #pragma omp parallel for
    #endif
    for(int x = 0; x < image.cols; ++x){
      #ifdef _OPENMP
      omp_set_lock(&locker);
      #endif
//     cout << progress++ * 100 / RES << "%" << "\r" << flush;
      st.insert(make_tuple(src[x](R), src[x](G), src[x](B)));
      #ifdef _OPENMP
      omp_unset_lock(&locker);
      #endif
    }
  }

//  cout << "colors: " << st.size() << endl;
  const float RATIO = st.size() / static_cast<float>(RES);
//  cout << "ratio: " << RATIO << endl;
  cout << RATIO << endl;
  return EXIT_SUCCESS;
}
