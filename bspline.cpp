#include "bspline.h"

// Initialize the curve and store a reference of the control points.
// Also the degree of the curve is provided through this constructor
bspline::bspline(vector<point2d>& control_points, int degree):
abstract_curve(control_points)
{
	this->degree = degree;
}




// The specified "control_points_updated" to adjust the knot vector
// when control points are added or removed
void bspline::control_points_updated()
{
	// Update the knot vector
	calculate_knot_vector();

	// Set the valid range for "t"
	if (u.size() != 0) {
		t_min = u[0];
		t_max = u[u.size()-1];
	}
}




// Calculate the knot vector. This method is called from 
// "control_points_updated"
void bspline::calculate_knot_vector()
{
	// Initialize variables according to the script
	int K = control_points.size();
	int g = degree;
	int n = K - g;

	// Clear and resize the knot vector to the right size
	u.clear();

	/*************
	Task 4.1.6.    Fill the knot vector u with the appropriate values for
	               open splines with end point interpolation. The above code
	               initializes variables according to the script.
	Aufgabe 4.1.6. Fuellen Sie den Knotenvektor u mit den passenden Werten
                   fuer offene Splines mit Endpunktinterpolation. Der obige
                   Code initialisiert Variablen wie sie im Skript zu finden sind.
	*************/

	for(int i = 0; i < g; i++){
		u.push_back(0);
	}
	for(int i = 0; i < ((K + g + 1)-(2*g)); i++){
		u.push_back(i);
	}
	for(int i = 0; i < g; i++){
		u.push_back(u[u.size()-1]);
	}
	
}




// Evaluate the basis as a function of the control point "point_num"
// (counted from zero) and the parameter "t".
double bspline::evaluate_basis(int point_num, double t)
{
	/**********
	Task 4.1.6.    Implement the evaluation of the basis function of bsplines
	               for the control point "point_num" at "t". You will find
	               another version with specifyable degree below which you can
	               call from here and use if you want to implement the recursive 
	               approach. The degree of this spline is stored in the variable "degree".
	Aufgabe 4.1.6. Implementieren Sie die Auswertung der Basisfunktion eines
	               BSpline fuer den Kontrollpunkt "point_num" an der Stelle "t".
                   Unten finden Sie eine andere Version mit einstellbarem Grad,
	               die Sie von hier aus aufrufen und verwenden koennen um den rekursiven
	               Berechnungsansatz umzusetzen.
	***********/
	calculate_knot_vector();
	return evaluate_basis(degree, point_num, t);
}




// Another version of the evaluate_basis method with a specifyable
// degree. This method can be used for the recursive evaluation of 
// the basis functions
double bspline::evaluate_basis(int g, int i, double t)
{
	if(g <= 0){
		
		if((u.at(i)) <= t && t < (u.at(i+1))) return 1;
		else return 0;

	}
	double part1_1, part1_2, part2_1, part2_2;
	part1_1 = ( t - (u.at(i)) );
	part1_2 = ( (u.at(i+g)) - (u.at(i)) );

	part2_1 = ( (u.at(i+1+g)) - t);
	part2_2 = ( (u.at(i+1+g)) - (u.at(i+1)) );
	
	if(part1_2 == 0.0){
		return (part2_1 / part2_2) * evaluate_basis(g-1, i+1, t);
	}

	if(part2_2 == 0.0){
		return (part1_1 / part1_2) * evaluate_basis(g-1, i, t);
	}
	
	return ((part1_1 / part1_2) * evaluate_basis(g-1, i, t)) + ((part2_1 / part2_2) * evaluate_basis(g-1, i+1, t));
}



// Set debug text
void bspline::set_text(stringstream &stream)
{
	stream<<"Type: BSpline (with degree "<<degree<<")";
}