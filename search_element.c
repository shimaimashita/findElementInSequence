#include <stdio.h>
#include <stdlib.h>

void merge(int *array, int left_border, int center, int right_border)
{
	int first_part = center - left_border + 1,
		second_part = right_border - center;
	int *right_array, *left_array;
	left_array = (int *) malloc(first_part * sizeof(int));
	right_array = (int *) malloc(second_part * sizeof(int));
	int counter = left_border;
	for (int i = 0; i < first_part; i++)
		left_array[i] = array[counter++];
	for (int i = 0; i < second_part; i++)
		right_array[i] = array[counter++];

	int i, j, left_state, right_state;
	i = j = left_state = right_state = 0;
	for (int k = left_border; k  <= right_border; k++){
		if (right_state){
			array[k] = left_array[i];
			i++;
		} else if (left_state){
			array[k] = right_array[j];
			j++;
		} else if (left_array[i] < right_array[j]){
			array[k] = left_array[i];
			i++;
		} else {
			array[k] = right_array[j];
			j++;
		}
		if (j >= second_part)
			right_state = 1;
		if (i >= first_part)
			left_state = 1;
	}
	free(left_array);
	free(right_array);
}

void merge_sort(int *array, int left_border, int right_border)
{
	int center;
	if (left_border < right_border){
		center = (left_border + right_border) / 2;
		merge_sort(array, left_border, center);
		merge_sort(array, center + 1, right_border);
		merge(array, left_border, center, right_border);
	}
}

int binary_search(int *array, int left_border, int right_border, int x)
{
	int center = -1;
	if (left_border < right_border){
		center = (right_border + left_border) / 2;
		if (array[center] > x)
			binary_search(array, left_border, center, x);
		else if (array[center] < x)
			binary_search(array, center + 1, right_border, x);
	}
	return center;
}
				



int main()
{
	int n, x;
	printf("Enter number of elements\n");
	scanf("%d", &n);
	int *array;
	array = (int *) malloc(n * sizeof(int));
	for (int i = 0; i < n; i++){
		printf("Enter %dth number\n", i + 1);
		scanf("%d", &array[i]);
	}
	printf("Enter x\n");
	scanf("%d", &x);
	merge_sort(array, 0, n - 1);
	for (int i = 0; i < n; i++){
		printf("%d ", array[i]);
	}
	int answer;
	if ((answer = binary_search(array, 0, n - 1, x)) != -1 
			&& answer != n && array[answer] == x)
		printf("Pos of %d is %d\n", x, answer + 1);
	else
		printf("Array hasn't %d\n", x);
	return 0;
}
