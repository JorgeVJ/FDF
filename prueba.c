#include <stdlib.h>
#include <stdio.h>

int	**add_point(int	**points, int	size, int x, int y, int z)
{
	int	**temp;
	int	i;
	
	temp = malloc(sizeof(int *) * size);
	i = 0;
	while (points && i < size - 1)
	{
		printf(" entra\n");
		temp[i] = malloc(sizeof(int) * 4);
		temp[i][0] = points[i][0];
		temp[i][1] = points[i][1];
		temp[i][2] = points[i][2];
		i++;
	}
	if (points)
		free(points);
	temp[i] = malloc(sizeof(int) * 4);
	temp[i][0] = x;
	temp[i][1] = y;
	temp[i][2] = z;
	return (temp);
}

int	 main(void)
{
	int	**xyzc;

	xyzc = NULL;
	xyzc = add_point(xyzc, 1, 2, 3, 4);
	xyzc = add_point(xyzc, 2, 27, 23, 24);
	xyzc = add_point(xyzc, 3, 275, 233, 241);

	int	i = -1;
	while (++i <= 2)
		printf("%d\n", xyzc[0][i]);

	
	i = -1;
	while (++i <= 2)
		printf("%d\n", xyzc[1][i]);
	
	
	i = -1;
	while (++i <= 2)
		printf("%d\n", xyzc[2][i]);
	
	


/*	xyzc[2] = malloc(sizeof(int) * 4);
	xyzc[2][0] = 50;
	xyzc[2][1] = 60;
	xyzc[2][2] = 70;
	xyzc[2][3] = 80;*/
	
	/*int	i = -1;
	while (++i < 4)
		printf("%d\n", xyzc[1][i]);*/
}
