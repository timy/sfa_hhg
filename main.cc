#include <cstdio>
#include <complex>

#define complex std::complex<double>
#define Ip 0.5
#define w0 0.057
#define sigma 206.7
#define E0 0.08
#define nt 10001
#define t0 -500.
#define t1 500.

extern "C" void calc_hhg(long, double, double*, double*);

int main(int argc, char* argv[]) {
  double time[nt];
  double Ef[nt], Af[nt], alpha[nt];
  double dt = (t1 - t0) / (nt - 1.);
  for (int it = 0; it < nt; it ++) {
    time[it] = t0 + it * dt;
    Ef[it] = E0 * exp( - time[it] * time[it] / (sigma * sigma) ) * cos( w0 * time[it] );
  }

  double dout[nt];
  calc_hhg(nt, dt, Ef, dout);
  return 0;
}
