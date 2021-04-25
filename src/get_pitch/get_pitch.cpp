/// @file

#include <iostream>
#include <fstream>
#include <string.h>
#include <errno.h>
#include <cmath>

#include "wavfile_mono.h"
#include "pitch_analyzer.h"

#include "docopt.h"

#define FRAME_LEN   0.030 /* 30 ms. */
#define FRAME_SHIFT 0.015 /* 15 ms. */

using namespace std;
using namespace upc;

static const char USAGE[] = R"(
get_pitch - Pitch Detector 

Usage:
    get_pitch [options] <input-wav> <output-txt>
    get_pitch (-h | --help)
    get_pitch --version

Options:
    -h, --help  Show this screen
    --version   Show the version of the project

Arguments:
    input-wav   Wave file with the audio signal
    output-txt  Output file: ASCII file with the result of the detection:
                    - One line per frame with the estimated f0
                    - If considered unvoiced, f0 must be set to f0 = 0
)";

int main(int argc, const char *argv[]) {
	/// \TODO 
	///  Modify the program syntax and the call to **docopt()** in order to
	///  add options and arguments to the program.
    std::map<std::string, docopt::value> args = docopt::docopt(USAGE,
        {argv + 1, argv + argc},	// array of arguments, without the program name
        true,    // show help if requested
        "2.0");  // version string

	std::string input_wav = args["<input-wav>"].asString();
	std::string output_txt = args["<output-txt>"].asString();

  // Read input sound file
  unsigned int rate;
  vector<float> x;
  if (readwav_mono(input_wav, rate, x) != 0) {
    cerr << "Error reading input file " << input_wav << " (" << strerror(errno) << ")\n";
    return -2;
  }

  int n_len = rate * FRAME_LEN;
  int n_shift = rate * FRAME_SHIFT;

  // Define analyzer
  PitchAnalyzer analyzer(n_len, rate, PitchAnalyzer::HAMMING, 50, 500);

  /// \TODO
  /// Preprocess the input signal in order to ease pitch estimation. For instance,
  /// central-clipping or low pass filtering may be used.

  float potencia = 0.0; 
  for(unsigned int n = 0; n < x.size(); n++){
    potencia += fabs(x[n]) * fabs(x[n]); 
  }
  potencia /= x.size(); 

  float thereshold = 0.75 * potencia; 

  for(unsigned int n = 0; n < x.size(); n++){
    if(x[n] >= thereshold){
      x[n] -= thereshold; 
    } else if (x[n]<= thereshold){
      x[n] +=thereshold; 
    } else {
      x[n] = 0; 
    }
  }

  /// \DONE
  /// Hem fet central-clipping. 
  /// Hem calculat la potència i els valors que estaven per sota del valor absolut de la frontera han estat reavaluats a 0.
  /// Els valors que estaven per sobre de la frontera els hi hem restat aquest mateix valor per disminuir l'amplitud de la senyal.
  
  // Iterate for each frame and save values in f0 vector
  vector<float>::iterator iX;
  vector<float> f0;
  for (iX = x.begin(); iX + n_len < x.end(); iX = iX + n_shift) {
    float f = analyzer(iX, iX + n_len);
    f0.push_back(f);
  }

  /// \TODO
  /// Postprocess the estimation in order to supress errors. For instance, a median filter
  /// or time-warping may be used.

  int n = 3; 
  vector<float>finestra(n); 
  for(unsigned int i = 1; i < f0.size()-1; ++i){
    for(unsigned int j = 0; j < n; j++){
      finestra[j]=f0[i-1+j]; 
    }
    sort(finestra.begin(), finestra.end()); 
    f0[i] = finestra[1]; 
  }

  /// \DONE
  /// S'ha utilitzat el filtre de medianes.
  /// Hem utilitzat una finestra (que per poder-la modificar hem creat el valor int n)
  /// Cada llargada de finestra hem ordenat amb la funció sort els seus elements
  /// Hem agafat el valor del mig per retornar-lo al vector final 

  // Write f0 contour into the output file
  ofstream os(output_txt);
  if (!os.good()) {
    cerr << "Error reading output file " << output_txt << " (" << strerror(errno) << ")\n";
    return -3;
  }

  os << 0 << '\n'; //pitch at t=0
  for (iX = f0.begin(); iX != f0.end(); ++iX) 
    os << *iX << '\n';
  os << 0 << '\n';//pitch at t=Dur

  return 0;
}
