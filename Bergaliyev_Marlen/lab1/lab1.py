def fill_square(square, x1, y1, x2, y2, color):
	for i in range(x1, x2):
		for j in range(y1, y2):
			square[i][j] = color

	
def search_empty(n, square):
	ans = None
	for i in range(0, n):
		for j in range(0, n):
			if square[i][j] == 0:
				ans = [i, j]
				break
		if not ans is None:
			break
	if not ans is None:
		for j in range(0, n-max(ans[0],ans[1])):
			if square[ans[0]+j][ans[1]+j] != 0:
				j -= 1
				break
		for i in range(0, n-ans[1]):
			if square[ans[0]][ans[1]+i] != 0:
				i -= 1
				break
		ans.append(min(j+1, i+1))
		return ans

def quadration(n):
	if n % 2 == 0:
		return [[0, 0, n//2], [n//2, 0, n//2], [0, n//2, n//2], [n//2, n//2, n//2]]
	for k in range(3, n+1):
		if n % k == 0:
			break
	ans = _quadration(k)
	c = n // k
	for i in ans:
		i[0] *= c
		i[0] += 1
		i[1] *= c
		i[1] += 1
		i[2] *= c
	return ans


def _quadration(n):
	square = [[0 for i in range(0, n)] for j in range(0, n)]
	z = (n+1)//2
	c = n//2
	cur = 1
	fill_square(square, 0, 0, z, z, cur)
	cur += 1
	fill_square(square, 0, z, c, n, cur)
	cur += 1
	fill_square(square, z, 0, n, c, cur)
	cur += 1
	ans = [[0, 0, z], [0, z, c], [z, 0, c]]
	best = []
	best_count = n*n
	d = 0
	for k in range(2, z+1):
		for i in range(2, k+1):
			if k % i == 0:
				break
		if i == k and abs(2*d-z) > abs(2*k-z):
			d = k 
	k = d
	if k == z or k == 0:
		return backtraking(square, ans, cur, n*n, n)
	square1 = [j.copy() for j in square]
	ans1 = [j.copy() for j in ans]
	fill_square(square1, n-k, n-k, n, n, cur)
	ans1.append([n-k, n-k, k])
	fill_square(square1, c, n-z+k, c+z-k, n, cur+1)
	ans1.append([c, n-z+k, z-k])
	best1 = backtraking(square1, ans1, cur+2, best_count, n)
	if len(best1) < best_count and len(best1) != 0:
		best = best1
		best_count = len(best1)
	square1 = [j.copy() for j in square]
	ans1 = [j.copy() for j in ans]
	fill_square(square1, n-z+k, n-z+k, n, n, cur)
	ans1.append([n-z+k, n-z+k, z-k])
	fill_square(square1, c, n-k, c+k, n, cur+1)
	ans1.append([c, n-k, k])
	best1 = backtraking(square1, ans1, cur+2, best_count, n)
	if len(best1) < best_count and len(best1) != 0:
		best = best1
		best_count = len(best1)
	return best


def backtraking(square, ans, cur, best_count, n):
	best = []
	end = cur-1
	while cur != end:
		new = search_empty(n, square)
		if new is None:
			if best_count > len(ans):
				best = [ans[i].copy() for i in range(0, len(ans))]
				best_count = len(best)
		while new is None or len(ans) > best_count:
			new = None
			if len(ans) == end:
				return best
			if ans[-1][2] == 1:
				square[ans[-1][0]][ans[-1][1]] = 0
				ans.pop(-1)
				continue
			for i in range(ans[-1][0], ans[-1][0]+ans[-1][2]):
				square[i][ans[-1][1]+ans[-1][2]-1] = 0
			for j in range(ans[-1][1], ans[-1][1]+ans[-1][2]-1):
				square[ans[-1][0]+ans[-1][2]-1][j] = 0
			ans[-1][2] -= 1
			cur = len(ans) + 1
			break
		if new is None:
			continue
		while square[new[0]+new[2]-1][new[1]+new[2]-1] != 0 or square[new[0]][new[1]+new[2]-1] != 0:
			new[2] -= 1
		fill_square(square, new[0], new[1], new[0]+new[2], new[1]+new[2], cur)
		ans.append(new)
		cur += 1
	return best
			
		
def main():
	n = int(input())
	ans = quadration(n)
	print(len(ans))
	for i in ans:
		print(*i)

if __name__ == '__main__':
	main()
