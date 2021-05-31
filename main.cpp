#include <iostream>
#include "bessel.cpp"
using namespace std;

int main()
{
    cout << "\n\n --- Bessel's Interpolation ---";

    double xp;
    cout << "\nInterpolate for: ";
    cin >> xp;

    int choice;
    cout << "\nSelect an option: " << endl
         << "1. Auto-generate values" << endl
         << "2. Specify values" << endl;
    cin >> choice;

    if (choice == 1)
    {
        BesselsInterpolation BI(xp);
        BI.buildDifferenceTable();
        BI.findOrigin();
        BI.findBesselResult();
    }
    else
    {
        int num;
        cout << "\nNo. of terms in table: ";
        cin >> num;

        BesselsInterpolation BI(xp, num);
        BI.buildDifferenceTable();
        BI.findOrigin();
        BI.findBesselResult();
    }

    return 0;
}