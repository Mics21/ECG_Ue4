#include "hermite_spline.h"
#include <math.h>


// Initialize the curve and store a reference of the control points
hermite_spline::hermite_spline(vector<point2d>& control_points): abstract_curve(control_points)
{

}




// Evaluate the curve at "t"
point2d hermite_spline::evaluate(double t)
{
	int n = control_points.size();

	/*********
	Task 4.1.5.    Implement the evaluation of a spline point. A point
	               is built using the control points and their tangents. You
	               only have to do the calculation for one spline segment.
	               See the script for the calculation of points for one segment.
	Aufgabe 4.1.5. Implementieren Sie die Auswertung eines Spline-Punktes. Dieser
	               wird ueber die Kontrollpunkte und Tangenten bestimmt. Die Berechnung
                   soll lediglich fuer ein Segment erfolgen. Im Skript finden Sie
                   genauere Informationen dazu.
    ***********/

	point2d hermite(0.0, 0.0);

	//Hermite-Kurve erst ab 3 Kontrollpunkten
	if(n<3) return point2d (0.0, 0.0);

	
	point2d p_begin, p_end, tan_begin, tan_end;
	//Start- und End-Kontrollpunkte
	p_begin = get_control_points().at(0);
	p_end = get_control_points().at(n-1);
	//Start- und End-Tangenten
	tan_begin = get_control_points().at(1) - p_begin;
	tan_end = p_end - get_control_points().at(n-2);

	hermite = evaluate_basis(0, t)*p_begin+evaluate_basis(1,t)*tan_begin+evaluate_basis(2,t)*tan_end+evaluate_basis(3,t)*p_end;

	//Hermite-Interpolations-Formel - Folie Nr. 20
	return hermite;
}




// Evaluate a basis as a function of the control point "point_num"
// (counted from zero) and the domain parameter t
double hermite_spline::evaluate_basis(int point_num, double t)
{
	/***********
	Task 4.1.5.    Implement the evaluation of the basis function for the
	               point "point_num" at "t". You will find the formulas for
	               one segment directly in the script. Use the appropriate
	               formula for the right value of "point_num".
	Aufgabe 4.1.5. Implementieren Sie die Auswertung der Basisfunktion des
	               Punktes "point_num" an der Stelle "t". Sie finden die
                   Formeln fuer ein Segment im Skript. Verwenden Sie fuer
                   jeden Wert von "point_num" die entsprechende Berechnungs-
                   Vorschrift.
	***********/

	// Grad 3 - siehe Folie Nr. 21
	switch (point_num)
	{
	case 0:
		return (1-t)*(1-t)*(1+2*t);
	case 1:
		return t*(1-t)*(1-t);
	case 2:
		return -t*t*(1-t);
	case 3:
		return (3-2*t)*t*t;
	}	
	return 0.0;
	
}



// Set debug text
void hermite_spline::set_text(stringstream &stream)
{
	stream<<"Type: Hermite (simple)";
}