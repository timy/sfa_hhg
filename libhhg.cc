#include <cstdio>
#include <complex>

#define complex std::complex<double>
#define Ip 0.5

inline complex dipole(double k) {
  double dnom = (k*k + 2*Ip);
  return -complex(0., 1.) * 11.3137 * pow(2.*Ip, 1.25) * k / (M_PI * dnom * dnom * dnom); // pow(2., 3.5)
}

extern "C" void calc_hhg(long nt, double dt, double* Ef, double* dout) {

  double *Af = new double[nt];
  double *alpha = new double[nt];
  complex* d = new complex[nt];

  for (int it = 0; it < nt; it ++) {
    if (it == 0) {
      Af[it] = 0.;
      alpha[it] = 0.;
    } else {
      Af[it] = Af[it-1] - Ef[it-1] * dt;
      alpha[it] = alpha[it-1] + Af[it-1] * dt;
    }
  }

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
    dout[it] = d[it].real();
    if (it % 100 == 0) printf("progress: %f\n", 1.0 * it / nt);
  }

  delete[] d;
  delete[] Af;
  delete[] alpha;
}
