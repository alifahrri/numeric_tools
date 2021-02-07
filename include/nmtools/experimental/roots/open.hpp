#ifndef NMTOOLS_OPEN_ROOTS_HPP
#define NMTOOLS_OPEN_ROOTS_HPP

#include <map>
#include <cstdio>
#include <cmath>
#include <limits>
#include "nmtools/utility.hpp"

namespace nmtools {
    namespace roots {
        template <typename F, typename G, typename Scalar>
        auto fixed_point(F &f, G &g, Scalar x0, Scalar &xr, Scalar es, size_t imax, size_t &iter, Scalar &ea, Scalar zero = Scalar{1e-6})
        {
            xr = x0;
            iter = 0;
            do {
                auto xrold = xr;
                xr = g(xrold);
                iter = iter+1;
                if(std::fabs(xr) > zero) {
                    ea = std::fabs((xr-xrold)/xr) * Scalar(100.0);
                }
            } while(std::fabs(ea) > std::fabs(es) &&  iter < imax);
        }

        template <typename F, typename DF, typename Scalar>
        auto newton_raphson(F &f, DF &df, Scalar x0, Scalar &xr, Scalar es, size_t imax, size_t &iter, Scalar &ea, Scalar zero = Scalar{1e-6})
        {
            auto g = [&f,&df](Scalar x){
                return (x-(f(x)/df(x)));
            };
            fixed_point(f,g,x0,xr,es,imax,iter,ea,zero);
        }

        template <typename F, typename Scalar>
        auto secant(F &f, Scalar x0, Scalar x_1, Scalar &xr, Scalar es, size_t imax, size_t &iter, Scalar &ea, Scalar zero = Scalar{1e-6})
        {
            auto g = [&f,&x_1](Scalar x){
                auto xr = (x-(f(x)*(x_1-x)/(f(x_1)-f(x))));
                x_1 = x;
                return xr;
            };
            fixed_point(f,g,x0,xr,es,imax,iter,ea,zero);
        }

        template <typename F, typename Scalar>
        auto modified_secant(F &f, Scalar x0, Scalar delta, Scalar &xr, Scalar es, size_t imax, size_t &iter, Scalar &ea, Scalar zero = Scalar{1e-6})
        {
            auto g = [&f,delta](Scalar x){
                return (x-(delta*f(x)/(f(x+delta)-f(x))));
            };
            fixed_point(f,g,x0,xr,es,imax,iter,ea,zero);
        }

        template <typename F, typename Scalar, typename Logger=void>
        auto fzero(F &f, Scalar a, Scalar b, Scalar &xr, Scalar zero = Scalar{1e-6}, Scalar eps = std::numeric_limits<Scalar>::epsilon(), Logger *logger = nullptr)
        {
            Scalar tol = zero;
            auto fa = f(a); auto fb = f(b);
            if(fa*fb>=Scalar(0)) {
                return;
            }
            if(std::fabs(fa) < std::fabs(fb)) {
                std::swap(a,b);
                std::swap(fa,fb);
            }
            auto c = a; auto fc = f(c);
            Scalar s; Scalar d; Scalar fs;
            bool mflag{true};
            LOGVAR(logger, a, b, c, fa, fb, fc, d, s, fs, tol, eps);
            auto in_range = [](Scalar s, Scalar a, Scalar b) {
                auto t0 = (3*a+b)/4;
                auto t1 = b;
                if(t0 > t1) std::swap(t0, t1);
                return (s > t0) && (s < t1);
            };
            do {
                if(std::fabs(fa-fc) > (zero+eps) && std::fabs(fb-fc) > (zero+eps)) {
                    /* inverse quadratic interpolation */
                    s = ((a*fb*fc)/((fa-fb)*(fa-fc)) + (b*fa*fc)/((fb-fa)*(fb-fc)) + (c*fa*fb)/((fc-fa)*(fc-fb)));
                } else {
                    /* secant method */
                    s = b - fb*(b-a)/(fb-fa);
                }
                if(
                    /* condition 1, s is not between (3a+b)/4 and b */
                    (! in_range(s,a,b)) ||
                    /* condition 2, */
                    (mflag && (std::fabs(s-b) >= std::fabs(b-c)/2)) ||
                    /* condition 3, */
                    (!mflag && (std::fabs(s-b) >= std::fabs(c-d)/2)) ||
                    /* condition 4, */
                    (mflag && (std::fabs(b-c) < eps)) ||
                    /* condition 5, */
                    (!mflag && (std::fabs(c-d) < eps))
                ) {
                    /* bisection method */
                    s = (a+b)/2;
                    mflag = true;
                } else {
                    mflag = false;
                }
                fs = f(s);
                d = c;
                c = b;
                LOGVAR(logger, a, b, c, fa, fb, fc, d, s, fs, tol, eps);
                if(fa*fs < Scalar(0)) {
                    b = s;
                } else {
                    a = s;
                }
                if(std::fabs(fa) < std::fabs(fb)) {
                    std::swap(a,b);
                }
                fa = f(a); fb = f(b); fc = f(c);
            } while(std::fabs(fb) > zero && std::fabs(b-a)>tol);
            xr = b;
            LOGVAR(logger, a, b, c, fa, fb, fc, d, s, fs, tol, eps);
        }
    } // namespace roots
} // namespace nmtools
#endif // NMTOOLS_OPEN_ROOTS_HPP