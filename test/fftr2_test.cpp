/*****************************************************************************
 *                               fftr2_test.cpp
 *
 * Radix 2 based FFT testing.
 *
 * Zhang Ming, 2010-04
 *****************************************************************************/


#include <iostream>
#include <iomanip>
#include <fftr2.h>


using namespace std;
using namespace itlab;


int LENGTH = 32;


int main()
{
    int     i, j, index, rows = LENGTH/4;

    Vector<double> xn(LENGTH);
    Vector< complex<double> > yn(LENGTH),
                              Xk(LENGTH);
    FFTR2<double> Fourier;

    cout << "The original signal is: " << endl;
    for( i=0; i<rows; i++ )
    {
        cout << endl;
        for( j=0; j<3; j++ )
        {
            index = 3*i+j;
            xn[index] = i+j;
            cout << setiosflags(ios::fixed) << setprecision(6);
            cout << "\t" << xn[index];
        }
    }
    cout << endl << endl;

    Fourier.fft( xn, Xk );

    cout << "The Fourier transform of original signal is:" << endl;
    for( i=0; i<rows; i++ )
    {
        cout << endl;
        for( j=0; j<3; j++ )
        {
            index = 3*i+j;
            cout << setiosflags(ios::fixed) << setprecision(6);
            cout << "\t" << Xk[index];
        }
    }
    cout << endl << endl;

    Fourier.ifft( Xk, xn );
    cout << "The inverse Fourier thansform is" << endl;
    for( i=0; i<rows; i++ )
    {
        cout << endl;
        for( j=0; j<3; j++ )
        {
            index = 3*i+j;
            cout << setiosflags(ios::fixed) << setprecision(6);
            cout << "\t" << xn[index];
        }
    }
    cout << endl << endl;

    cout << "The original signal is: " << endl;
    for( i=0; i<rows; i++ )
    {
        cout << endl;
        for( j=0; j<3; j++ )
        {
            index = 3*i+j;
            yn[index] = complex<double>(i,j);
            cout << setiosflags(ios::fixed) << setprecision(6);
            cout << "\t" << yn[index];
        }
    }
    cout << endl << endl;

    Fourier.fft( yn );
    cout << "The Fourier transform of original signal is:" << endl;
    for( i=0; i<rows; i++ )
    {
        cout << endl;
        for( j=0; j<3; j++ )
        {
            index = 3*i+j;
            cout << setiosflags(ios::fixed) << setprecision(6);
            cout << "\t" << yn[index];
        }
    }
    cout << endl << endl;

    Fourier.ifft( yn );
    cout << "The inverse Fourier thansform is" << endl;
    for( i=0; i<rows; i++ )
    {
        cout << endl;
        for( j=0; j<3; j++ )
        {
            index = 3*i+j;
            cout << setiosflags(ios::fixed) << setprecision(6);
            cout << "\t" << yn[index];
        }
    }

    cout << endl << endl;
    return 0;
}
