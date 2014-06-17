#include "bezier_curve.h"
#include <math.h>


// Initialize the curve and store a reference of the control points
bezier_curve::bezier_curve(vector<point2d>& control_points): abstract_curve(control_points)
{

}




// A helper function to calculate "n choose k"
double bezier_curve::binomial_coefficient(int n, int k)
{
	// ... functionality to be added!
	if (( k == 0 ) || ( n == k)) return 1;
	else {
        return binomial_coefficient(n-1,k) + binomial_coefficient(n-1,k-1);
    }
}




// Evaluate a basis as a function of the control point "point_num"
// (counted from zero) and the domain parameter t
double bezier_curve::evaluate_basis(int point_num, double t)
{
	int n = control_points.size()-1;
	int i = point_num;

	/**********
	Task 4.1.4.    Implement the evaluation of the Bernstein basis. You can use
	               the method "binomial_coefficient" above (which must also be
	               implemented) for the calculation if wanted.
	Aufgabe 4.1.4. Implementieren Sie die Auswertung der Bernsteinbasis. Sie koennen
	               die Methode "binomial_coeffizient" von oben (die allerdings 
                   ebenfalls noch nicht implementiert ist) fuer die Berechnung
                   nutzen.
   ************/

	return binomial_coefficient(n,i)*pow(1-t, n-i)*pow(t, i);
}



// Set debug text
void bezier_curve::set_text(stringstream &stream)
{
	stream<<"Type: Bezier";
}