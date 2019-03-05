from sys import *
from queue import *

def A_star(vfrom, vto, e):
	queue = PriorityQueue()
	for i in e[vfrom]:
		queue.put((i[0] + abs(int(vto) - int(i[1])), i[1], vfrom+' '+i[1]))
	cur = queue.get()
	while cur[1] != vto and queue.qsize() != 0:
		if cur[1] not in e:
			cur = queue.get()
			continue
		for i in e[cur[1]]:
			if i[1] in cur[2]:
				continue
			queue.put((cur[0]+i[0]-abs(int(vto) - int(cur[1]))+abs(int(vto) - int(i[1])), i[1], cur[2]+' '+i[1]))
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
