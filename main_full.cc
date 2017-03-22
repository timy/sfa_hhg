#include <cstdio>
#include <complex>

#define complex std::complex<double>
#define Ip 0.5
#define w0 0.057
#define sigma 1240.2
#define E0 0.08
#define nt 10001
#define t0 -3000.
#define t1  3000.

inline complex dipole(double k) {
  double dnom = (k*k + 2*Ip);
  return -complex(0., 1.) * 11.3137 * pow(2.*Ip, 1.25) * k / (M_PI * dnom * dnom * dnom); // pow(2., 3.5)
}

int main(int argc, char* argv[]) {
  double time[nt];
  double Ef[nt], Af[nt], alpha[nt];
  double dt = (t1 - t0) / (nt - 1.);
  printf("dt: %lf\n", dt);
  for (int it = 0; it < nt; it ++) {
    time[it] = t0 + it * dt;
    Ef[it] = E0 * exp( - time[it] * time[it] / (sigma * sigma) ) * cos( w0 * time[it] );
    if (it == 0) {
      Af[it] = 0.;
      alpha[it] = 0.;
    } else {
      Af[it] = Af[it-1] - Ef[it-1] * dt;
      alpha[it] = alpha[it-1] + Af[it-1] * dt;
    }
  }
  complex d[nt];
  for (int it = 0; it < nt; it ++) {
    d[it] = 0.;
    complex S = 0.;
    for (int itau = 1; itau <= it; itau ++) {
      int itp = it - itau; // ionization time
      double ks;
      ks = (alpha[itp] - alpha[it]) / (itau * dt);
      double k = ks + Af[itp];
      double integrand = 0.5 * k * k + Ip;
      if (itau == 0 || itau == it)
        integrand *= 0.5;
      S += integrand * (-dt);
      d[it] += conj(dipole(ks + Af[it])) * dipole(ks + Af[itp]) * Ef[itp] * exp(-complex(0., 1.) * S)
        * pow((2.*M_PI/(itau * dt)), 1.5);
    }
    d[it] *= complex(0., 1.) * (-dt);
    if (it % 100 == 0) printf("progress: %f\n", 1.0 * it / nt);
  }

  FILE* file = fopen("data.dat", "w");
  for (int it = 0; it < nt; it ++)
    fprintf(file, "%lf %lf %lf %lf %lf %lf\n",
            time[it], Ef[it], Af[it], alpha[it], d[it].real(), d[it].imag());
  fclose(file);
  return 0;
}
