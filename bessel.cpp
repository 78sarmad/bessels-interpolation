#include <iostream>
#include <time.h>
using namespace std;

class BesselsInterpolation
{
private:
    int n;
    double xp, xo, p;
    int origin_index;

    // dynamic arrays for difference table
    double *x, *fx;
    double *delta, *delta_sq, *delta_cube, *delta_quad;

public:
    // generate table itself for 5 terms
    BesselsInterpolation(double xp)
    {
        this->xp = xp;
        this->n = 5;
        x = new double[n];
        fx = new double[n];

        generateValues();
    }

    // initialize class with xp and no. of terms
    BesselsInterpolation(double xp, int num)
    {
        this->xp = xp;
        this->n = num;
        x = new double[n];
        fx = new double[n];

        getInputValues();
    }

    void generateValues()
    {
        srand(1);
        for (int i = 0; i < n; i++)
        {
            x[i] = i + 1;
            fx[i] = rand() % 10;
        }
    }

    // fill difference table from user input
    void getInputValues()
    {
        cout << "\n";
        for (int i = 0; i < n; i++)
        {
            cout << "Enter value for x[" << i << "]: ";
            cin >> x[i];

            cout << "Enter value for fx[" << i << "]: ";
            cin >> fx[i];
        }
    }

    // construct difference table
    void buildDifferenceTable()
    {
        delta = new double[n];
        delta_sq = new double[n];
        delta_cube = new double[n];
        delta_quad = new double[n];

        // calculate values of delta
        for (int i = n - 1; i >= 0; i--)
        {
            if (i - 1 >= 0)
                delta[i] = fx[i] - fx[i - 1];
        }

        // calculate values of delta square
        for (int j = n - 1; j >= 0; j--)
        {
            if (j - 1 >= 0)
                delta_sq[j] = delta[j] - delta[j - 1];
        }

        // calculate values of delta cube
        for (int k = n - 1; k >= 0; k--)
        {
            if (k - 1 >= 0)
                delta_cube[k] = delta_sq[k] - delta_sq[k - 1];
        }

        // calculate values of delta quad
        for (int l = n - 1; l >= 0; l--)
        {
            if (l - 1 >= 0)
                delta_quad[l] = delta_cube[l] - delta_cube[l - 1];
        }

        // print difference table
        cout << "\nx: ";
        for (int i = 0; i < n; i++)
            cout << "\t\t" << x[i];

        cout << "\nfx: ";
        for (int i = 0; i < n; i++)
            cout << "\t\t" << fx[i];

        cout << "\ndelta: ";
        for (int i = 1; i < n; i++)
            cout << "\t\t" << delta[i];

        cout << "\ndelta^2: ";
        for (int i = 2; i < n; i++)
            cout << "\t\t" << delta_sq[i];

        cout << "\ndelta^3: ";
        for (int i = 3; i < n; i++)
            cout << "\t\t" << delta_cube[i];

        cout << "\ndelta^4: ";
        for (int i = 4; i < n; i++)
            cout << "\t\t" << delta_quad[i];
    }

    // find step size
    double findInterval()
    {
        double h = x[1] - x[0];
        return h;
    }

    // calculate p for a specified origin
    double calculateP(int xo)
    {
        return ((xp - xo) / findInterval());
    }

    // select origin for interpolation
    void findOrigin()
    {
        for (int i = 0; i < n; i++)
        {
            p = calculateP(x[i]);
            xo = x[i];
            origin_index = i;

            if (p >= 0 && p <= 1)
                break;
            else
                continue;
        }

        cout << "\n\nOrigin (selected): " << xo;
        cout << "\nOrigin Index: " << origin_index;
        cout << "\nValue of P at Origin: " << p;
    }

    // calculate factorial for a number
    int factorial(int n)
    {
        if (n > 1)
            return n * factorial(n - 1);
        else
            return 1;
    }

    // calculate bessel interpolation's first term
    double calcFirstTerm()
    {
        return fx[origin_index]; // value of f at origin
    }

    // calculate bessel interpolation's second term
    double calcSecondTerm()
    {
        double sigma1by2 = delta[origin_index];
        return (p * sigma1by2);
    }

    // calculate bessel interpolation's third term
    double calcThirdTerm()
    {
        double sigmaSq0 = delta_sq[origin_index];
        double sigmaSq1 = delta_sq[origin_index + 1];

        return ((p * (p - 1) * (sigmaSq0 + sigmaSq1)) / (2 * factorial(2)));
    }

    // calculate bessel interpolation's fourth term
    double calcFourthTerm()
    {
        double sigmaCube1by2 = delta_cube[origin_index];

        return ((p * (p - 1) * (p - 1 / 2) * sigmaCube1by2) / (factorial(3)));
    }

    // calculate bessel interpolation's fifth term
    double calcFifthTerm()
    {
        double sigmaQuad0 = delta_quad[origin_index];
        double sigmaQuad1 = delta_quad[origin_index + 1];

        return (((p + 1) * p * (p - 1) * (p - 2) * (sigmaQuad0 + sigmaQuad1)) / (2 * factorial(4)));
    }

    void findBesselResult()
    {
        double result = calcFirstTerm() + calcSecondTerm() + calcThirdTerm() + calcFourthTerm() + calcFifthTerm();
        cout << "\n\n-> Bessel's Interpolation Result: " << result << endl
             << endl;
    }
};
