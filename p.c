#include <stdio.h>
#include <stdlib.h>

#define N 100

// Структура с последовательностью ходов
struct solve
{
	int set[N][3];
	int max[3];
	int n;
};

// Инициализация структуры
struct solve init_solve(int a, int b, int c)
{
	struct solve s;
	s.max[0] = a;
	s.max[1] = b;
	s.max[2] = c;
	s.set[0][0] = a;
	s.set[0][1] = 0;
	s.set[0][2] = 0;
	s.n = 0;
	return s;
};

// Вывод всей последовательности
void print_solve(struct solve s)
{
	for (int i = 0; i <= s.n; i++)
	{
		printf("%2d %2d %2d\n", s.set[i][0], s.set[i][1], s.set[i][2]);
	}
	printf("%d шагов\n", s.n);
}

// Переливание из сосуда i в сосуд j
void pour(struct solve *s, int i, int j)
{
	int diff = s->max[j] - s->set[s->n][j];
	if (diff > s->set[s->n][i]) diff = s->set[s->n][i];
	s->set[s->n + 1][i] = s->set[s->n][i] - diff;
	s->set[s->n + 1][j] = s->set[s->n][j] + diff;
	s->set[s->n + 1][3 - i - j] = s->set[s->n][3 - i - j];
	s->n++;
}

// Проверка на выход из алгоритма
int exit_check(struct solve s, int r)
{
	if (s.set[s.n][0] == r || s.set[s.n][1] == r || s.set[s.n][2] == r) 
	{
		return 1;
	}
	if (s.n > 1)
	{
		for (int i = 0; i < s.n; i++)
		{
			if (s.set[s.n][0] == s.set[i][0] && s.set[s.n][1] == s.set[i][1] && s.set[s.n][2] == s.set[i][2]) return -1;
		}
		return 0;
	}
	return 0;
}

// Алгоритм
int algorithm(struct solve *s, int r)
{
	int res = 0;
	while (1)
	{
		pour(s, 0, 1); if (res = exit_check(*s, r)) return res;
		pour(s, 1, 2); if (res = exit_check(*s, r)) return res;
		while (s->set[s->n][1] != 0)
		{
			pour(s, 2, 0); if (res = exit_check(*s, r)) return res;
			pour(s, 1, 2); if (res = exit_check(*s, r)) return res;
		}
	}
}

// Проверка корректности ввода
int input_check(int *a, int *b, int *c, int *r)
{
	char x = 0;
	scanf("%d %d %d %d%c", a, b, c, r, &x);
	if (x != 10) return 0;
	return 1;
}

// НОД
int NOD(int a, int b)
{
	while (a != b)
	{
		if (a > b) a = a - b;
		if (b > a) b = b - a;
	}
	return a;
}

// Проверка логики
int logic_check(int a, int b, int c, int r)
{
	// Проверка условности: a > b > c > 0
	if (a > b && b > c && c > 0)
	{
		// Задача сводится к двум сосудам и бесконечному источнику
		if (a >= b + c)
		{
			if ((0 < r && r <= b || a - b < r && r < a) && r % NOD(b, c) == 0) return 1;
		}
		else
		{
			return 1;
		}
	}	
	return 0;
}

int main(int argc, char *argv[])
{
	if (argc >= 5)
	{
		int a = atoi(argv[1]), b = atoi(argv[2]), c = atoi(argv[3]), r = atoi(argv[4]);
		if (logic_check(a, b, c, r))
		{
			struct solve s = init_solve(a, b, c);
			int res = algorithm(&s, r);
			if (res == -1) printf("Встречен цикл, решения нет.\n");
			else print_solve(s);
		}
		else
		{
			printf("При данных значениях нет решения.\n");
		}
	}
	else
	{
		printf("Некорректные входные данные.\n");
	}
	return 0;
}
