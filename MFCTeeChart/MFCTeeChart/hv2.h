#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <fstream>
#include <memory.h>

using namespace std;

#define ERROR(x)  fprintf(stderr, x), fprintf(stderr, "\n"), exit(1)



double drand(double from, double to)
{

	double j;
	j = from + (double)((to - from)*rand() / (RAND_MAX + 1.0));
	return (j);

}
int  Dominates(double  point1[], double  point2[], int  noObjectives)
/* returns true if 'point1' dominates 'points2' with respect to the
to the first 'noObjectives' objectives */
{

	int  i;
	int  betterInAnyObjective;

	betterInAnyObjective = 0;
	for (i = 0; i < noObjectives && point1[i] <= point2[i]; i++)
		if (point1[i] < point2[i])
			betterInAnyObjective = 1;
	return (i >= noObjectives && betterInAnyObjective);

} /* Dominates */

void  Swap(double  *front[], int  i, int  j)
{

	double  *temp;

	temp = front[i];
	front[i] = front[j];
	front[j] = temp;

} /* Swap */

int  FilterNondominatedSet(double  *front[], int  noPoints, int  noObjectives)
/* all nondominated points regarding the first 'noObjectives' dimensions
are collected; the points referenced by 'front[0..noPoints-1]' are
considered; 'front' is resorted, such that 'front[0..n-1]' contains
the nondominated points; n is returned */
{

	int  i, j;
	int  n;

	n = noPoints;
	i = 0;
	while (i < n) {

		j = i + 1;
		while (j < n) {

			if (Dominates(front[i], front[j], noObjectives)) {

				/* remove point 'j' */
				n--;
				Swap(front, j, n);

			}
			else if (Dominates(front[j], front[i], noObjectives)) {

				/* remove point 'i'; ensure that the point copied to index 'i'
				is considered in the next outer loop (thus, decrement i) */
				n--;
				Swap(front, i, n);
				i--;
				break;

			}
			else
				j++;

		}
		i++;

	}
	return n;

} /* FilterNondominatedSet */


double  SurfaceUnchangedTo(double  *front[], int  noPoints, int  objective)
/* calculate next value regarding dimension 'objective'; consider
points referenced in 'front[0..noPoints-1]' */
{

	int     i;
	double  maxValue, value;

	if (noPoints < 1)  ERROR("run-time error");
	maxValue = front[0][objective];
	for (i = 1; i < noPoints; i++) {

		value = front[i][objective];
		if (value > maxValue)  maxValue = value;

	}
	return maxValue;

} /* SurfaceUnchangedTo */

int  ReduceNondominatedSet(double  *front[], int  noPoints, int  objective,
	double  threshold)
	/* remove all points which have a value <= 'threshold' regarding the
	dimension 'objective'; the points referenced by
	'front[0..noPoints-1]' are considered; 'front' is resorted, such that
	'front[0..n-1]' contains the remaining points; 'n' is returned */
{

	int  n;
	int  i;

	n = noPoints;
	for (i = 0; i < n; i++)
		if (front[i][objective] >= threshold) {

			n--;
			Swap(front, i, n);

		}
	return n;

} /* ReduceNondominatedSet */

double  CalculateHypervolume(double  *front[], int  noPoints,
	int  noObjectives, double upperbound)
{

	int     n;
	double  volume, distance;

	volume = 0;
	distance = upperbound;
	n = noPoints;
	while (n > 0) {

		int     noNondominatedPoints;
		double  tempVolume, tempDistance;

		noNondominatedPoints = FilterNondominatedSet(front, n, noObjectives - 1);
		tempVolume = 0;
		if (noObjectives < 3) {

			if (noNondominatedPoints < 1)  ERROR("run-time error");
			tempVolume = upperbound - front[0][0];

		}
		else
			tempVolume = CalculateHypervolume(front, noNondominatedPoints,
				noObjectives - 1, upperbound);
		tempDistance = SurfaceUnchangedTo(front, n, noObjectives - 1);
		volume += tempVolume * (distance - tempDistance);
		distance = tempDistance;
		n = ReduceNondominatedSet(front, n, noObjectives - 1, distance);

	}

	return volume;

} /* CalculateHypervolume */

int  ReadFront(double  **frontPtr[], FILE  *file, int  noObjectives)
{

	int     noPoints;
	int     i;
	double  value;

	/* check file and count points */
	noPoints = 0;
	while (!feof(file)) {

		for (i = 0; i < noObjectives && fscanf(file, "%lf", &value) != EOF; i++);
		if (i > 0 && i < noObjectives)  ERROR("data in file incomplete");
		noPoints++;

	}
	/* allocate memory */
	*frontPtr = (double **)malloc(noPoints * sizeof(double *));
	if (*frontPtr == NULL)  ERROR("memory allocation failed");
	for (i = 0; i < noPoints; i++) {

		(*frontPtr)[i] = (double *)malloc(noObjectives * sizeof(double));
		if ((*frontPtr)[i] == NULL)  ERROR("memory allocation failed");

	}
	/* read data */
	rewind(file);
	noPoints = 0;
	while (!feof(file)) {

		for (i = 0; i < noObjectives; i++) {

			if (fscanf(file, "%lf", &value) != EOF)
				(*frontPtr)[noPoints][i] = value;
			else
				break;
			//printf("%lf ",value);

		}
		if (i > 0 && i < noObjectives)  ERROR("data in file incomplete");
		noPoints++;

	}
	if (noPoints < 1)  ERROR("file contains no data");
	return noPoints;

} /* ReadFront */

int  MergeFronts(double  **frontPtr[], double  *front1[], int  sizeFront1,
	double*  front2[], int  sizeFront2, int  noObjectives)
{

	int  i, j;
	int  noPoints;

	/* allocate memory */
	noPoints = sizeFront1 + sizeFront2;
	*frontPtr = (double **)malloc(noPoints * sizeof(double *));
	if (*frontPtr == NULL)  ERROR("memory allocation failed");
	for (i = 0; i < noPoints; i++) {

		(*frontPtr)[i] = (double *)malloc(noObjectives * sizeof(double));
		if ((*frontPtr)[i] == NULL)  ERROR("memory allocation failed");

	}
	/* copy points */
	noPoints = 0;
	for (i = 0; i < sizeFront1; i++) {

		for (j = 0; j < noObjectives; j++)
			(*frontPtr)[noPoints][j] = front1[i][j];
		noPoints++;

	}
	for (i = 0; i < sizeFront2; i++) {

		for (j = 0; j < noObjectives; j++)
			(*frontPtr)[noPoints][j] = front2[i][j];
		noPoints++;

	}

	return noPoints;

} /* MergeFronts */

