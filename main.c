#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/* Function Prototypes */
int **create_matrix(int rows, int cols);
void fill_matrix(int **matrix, int rows, int cols);
int find_max_path_recursive(int **matrix, int r, int c, int rows, int cols);
void free_matrix(int **matrix, int rows);

void fill_array_random(int *arr, int n);
int recursive_sum(int *arr, int n);
void calculate_stats(int *arr, int n, double *mean, double *std_dev);
void selection_sort(int *arr, int n);
int recursive_binary_search(int *arr, int low, int high, int target);

int main() {
    srand((unsigned int)time(NULL));

    printf("==================================================\n");
    printf("   C RECURSIVE GRID PATHFINDER & STATS\n");
    printf("==================================================\n");

    /* PART 1: Grid Path Finder */
    int rows = 4, cols = 4;
    printf("\n[1] Generating %dx%d Dynamic Matrix for Pathfinder...\n", rows, cols);
    int **matrix = create_matrix(rows, cols);
    fill_matrix(matrix, rows, cols);

    printf("Matrix Values:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }

    int max_score = find_max_path_recursive(matrix, 0, 0, rows, cols);
    printf("-> Maximum Path Score from (0,0) to (%d,%d): %d\n", rows - 1, cols - 1, max_score);
    free_matrix(matrix, rows);

    /* PART 2: Statistical Analysis & Binary Search */
    int n = 10;
    printf("\n[2] Generating Array of %d Elements for Stats & Search...\n", n);
    int *arr = (int *)malloc(n * sizeof(int));
    fill_array_random(arr, n);

    double mean, std_dev;
    calculate_stats(arr, n, &mean, &std_dev);
    printf("Array Sum: %d | Mean: %.2f | Std Dev: %.2f\n", recursive_sum(arr, n), mean, std_dev);

    selection_sort(arr, n);
    printf("Sorted Array: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    int target = arr[3]; // Search for an existing element
    int index = recursive_binary_search(arr, 0, n - 1, target);
    if (index != -1) {
        printf("-> Target %d found at index %d using Recursive Binary Search.\n", target, index);
    } else {
        printf("-> Target %d not found.\n", target);
    }

    free(arr);
    printf("\n[INFO] All dynamic memory freed successfully.\n");
    return 0;
}

/* Part 1 Implementations */
int **create_matrix(int rows, int cols) {
    int **matrix = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        *(matrix + i) = (int *)malloc(cols * sizeof(int));
    }
    return matrix;
}

void fill_matrix(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            *(*(matrix + i) + j) = (rand() % 9) + 1;
        }
    }
}

int find_max_path_recursive(int **matrix, int r, int c, int rows, int cols) {
    if (r >= rows || c >= cols) return 0;
    if (r == rows - 1 && c == cols - 1) return *(*(matrix + r) + c);

    int right = find_max_path_recursive(matrix, r, c + 1, rows, cols);
    int down = find_max_path_recursive(matrix, r + 1, c, rows, cols);

    return *(*(matrix + r) + c) + ((right > down) ? right : down);
}

void free_matrix(int **matrix, int rows) {
    for (int i = 0; i < rows; i++) free(matrix[i]);
    free(matrix);
}

/* Part 2 Implementations */
void fill_array_random(int *arr, int n) {
    for (int i = 0; i < n; i++) *(arr + i) = (rand() % 50) + 1;
}

int recursive_sum(int *arr, int n) {
    if (n <= 0) return 0;
    return recursive_sum(arr, n - 1) + arr[n - 1];
}

void calculate_stats(int *arr, int n, double *mean, double *std_dev) {
    *mean = (double)recursive_sum(arr, n) / n;
    double sq_sum = 0.0;
    for (int i = 0; i < n; i++) sq_sum += pow(arr[i] - *mean, 2);
    *std_dev = sqrt(sq_sum / n);
}

void selection_sort(int *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) min_idx = j;
        }
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

int recursive_binary_search(int *arr, int low, int high, int target) {
    if (low > high) return -1;
    int mid = low + (high - low) / 2;
    if (arr[mid] == target) return mid;
    if (arr[mid] > target) return recursive_binary_search(arr, low, mid - 1, target);
    return recursive_binary_search(arr, mid + 1, high, target);
}