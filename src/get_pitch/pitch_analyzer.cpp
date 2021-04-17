/// @file

#include <iostream>
#include <math.h>
#include "pitch_analyzer.h"

using namespace std;

/// Name space of UPC
namespace upc {
  void PitchAnalyzer::autocorrelation(const vector<float> &x, vector<float> &r) const {

    for (unsigned int l = 0; l < r.size(); ++l) {
      r[l] = 0;
      for (unsigned int j = 0; j < x.size() - l; ++j) {
        r[l] += x[j]*x[j+l];
      }
      r[l] /= x.size();
    }

    if (r[0] == 0.0F) //to avoid log() and divide zero 
      r[0] = 1e-10; 
  }

  void PitchAnalyzer::set_window(Window win_type) {
    if (frameLen == 0)
      return;

    window.resize(frameLen);

    switch (win_type) {
      case HAMMING: {
        unsigned int half = (frameLen % 2 == 0) ? frameLen / 2 : (frameLen + 1) / 2;
        unsigned int idx = (frameLen % 2 == 0) ? half - 1 : half - 2;

        for(int i=0; i<half; i++)
          window[i] = 0.5 * (1 - cos(2*M_PI*(i+1) / (frameLen + 1)));

        for(int i=half; i<frameLen; i++) {
          window[i] = window[idx];
          idx--;
        }
        break;
      }
      case RECT:
      default:
        window.assign(frameLen, 1);
    }
  }

  void PitchAnalyzer::set_f0_range(float min_F0, float max_F0) {
    npitch_min = (unsigned int) samplingFreq/max_F0;
    if (npitch_min < 2)
      npitch_min = 2;  // samplingFreq/2

    npitch_max = 1 + (unsigned int) samplingFreq/min_F0;

    //frameLen should include at least 2*T0
    if (npitch_max > frameLen/2)
      npitch_max = frameLen/2;
  }

  bool PitchAnalyzer::unvoiced(float pot, float r1norm, float rmaxnorm) const {
    return (r1norm < 0.9 || rmaxnorm < 0.2 || pot < -38);
  }

  float PitchAnalyzer::compute_pitch(vector<float> & x) const {
    if (x.size() != frameLen)
      return -1.0F;

    //Window input frame
    for (unsigned int i=0; i<x.size(); ++i)
      x[i] *= window[i];

    vector<float> r(npitch_max);

    //Compute correlation
    autocorrelation(x, r);
 
    vector<float>::const_iterator iRMax = r.begin() + npitch_min;

    for (vector<float>::const_iterator iR = iRMax; iR < r.end(); iR++) {
      if(*iR > *iRMax) {
        iRMax = iR;
      }
    }
    unsigned int lag = iRMax - r.begin();

    float pot = 10 * log10(r[0]);

    //You can print these (and other) features, look at them using wavesurfer
    //Based on that, implement a rule for unvoiced
    //change to #if 1 and compile
  #if 0
      if (r[0] > 0.0F)
        cout << pot << '\t' << r[1]/r[0] << '\t' << r[lag]/r[0] << endl;
  #endif
    
    if (unvoiced(pot, r[1]/r[0], r[lag]/r[0]))
      return 0;
    else
      return (float) samplingFreq/(float) lag;
  }
}
