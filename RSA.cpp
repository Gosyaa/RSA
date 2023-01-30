#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

//Возведение в степень
long long power(long long a, long long p, long long N) {
	long long ans = 1;
	for (int i = 0; i < p; i++) {
		ans *= a;
		ans %= N;
	}
	return ans;
}
//Быстрое возведение в степень
long long fast_power(long long a, long long p, long long N) {
	long long ans = 1;
	while (p > 0) {
		if (p % 2 == 1) {
			ans = (ans * a) % N;
		}
		a = (a * a) % N;
		p /= 2;
	}
	return ans;
}
//Расширенный алгоритм Евклида
long long ex_gcd(long long a, long long b, long long* x, long long* y) {
	if (a == 0) {
		*x = 0;
		*y = 1;
		return b;
	}

	long long x1, y1;
	long long gcd = ex_gcd(b % a, a, &x1, &y1);
	*x = y1 - (b / a) * x1;
	*y = x1;
	return gcd;
}

int main() {

	long long p = 29, q = 83, e = 23, d = 599; // Ключи и модуль шифрования и простые числа p и q
	long long N = p * q, dp = d % (p - 1), dq = d % (q - 1); // Дополнительные переменные для оптимизации дешифрования
	long long x, y;
	ex_gcd(q, p, &x, &y);
	long long q_inv = x % p;
	string s;
	getline(cin, s);
	//Строка, которую предстоит расшифровать
	int n = s.length();
	vector <long long> encr(n); //Строка в зашифрованном виде
	vector <long long> decr(n); //Строка в расшифрованном виде
	string str_ans = ""; //Строка вв исходном виде, если алгоритм рабоатет правильно - должна совпасть с исходной
	for (int i = 0; i < n; i++) {
		encr[i] = fast_power(long long(s[i]), e, N); //Формула шифрования RSA
		long long decr1 = fast_power(encr[i], dp, p), decr2 = fast_power(encr[i], dq, q);
		long long h = (q_inv * (decr1 - decr2)) % p;
		if (decr1 < decr2 && h != 0) {
			h = p + h;
		}
		decr[i] = (decr2 + h * q) % N;
		//Дешифрование с помощью китайской теоремы об остатках
		str_ans += char(decr[i]);
	}
	cout << str_ans << endl; //Выводим строку после процесса шифрования и дешифрования, чтобы сравнить с исходной
}