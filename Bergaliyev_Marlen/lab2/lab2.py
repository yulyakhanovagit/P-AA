from sys import *
from queue import *

def A_star(vfrom, vto, e):
	def evristic(x):
		for i in range(0, len(v)):
			if x == v[i]:
				x_i = i
			if vto == v[i]:
				vto_i = i
		return ((vto_i - x_i) / len(v)) * min_edge
	v = [i for i in e]
	for i in e:
		for j in e[i]:
			if j[1] not in v:
				v.append(j[1])
	if vto not in v:
		return None
	v.sort(key=int)
	min_edge = 0
	for i in e:
		for j in e[i]:
			if j[1] == vto and (j[0] < min_edge or min_edge == 0):
				min_edge = j[0]
	queue = PriorityQueue()
	for i in e[vfrom]:
		queue.put((i[0] + evristic(i[1]), i[1], vfrom+' '+i[1]))
	cur = queue.get()
	while cur[1] != vto and queue.qsize() != 0:
		if cur[1] not in e:
			cur = queue.get()
			continue
		for i in e[cur[1]]:
			if i[1] in cur[2]:
				continue
			queue.put((cur[0] + i[0] - evristic(cur[1]) + evristic(i[1]), i[1], cur[2] + ' ' + i[1]))
		cur = queue.get()
	if queue.qsize() == 0 and cur[1] != vto:
		return None
	return cur[2]


def main():
	e = {}
	s = input().split()
	for i in stdin:
		i = i.split()
		if i[0] not in e:
			e[i[0]] = []
		e[i[0]].append((float(i[2]), i[1]))
	print(A_star(*s, e))

if __name__ == '__main__':
	main()
