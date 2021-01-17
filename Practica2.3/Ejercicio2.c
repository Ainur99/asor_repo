#include <stdio.h>
#include <string.h>
#include <sched.h>

int main() {
	
	int pol, max, min;
	struct sched_param p;
	char* policy;
	
	pol = sched_getscheduler(0);
	sched_getparam(0, &p);
	max = sched_get_priority_max(pol);
	min = sched_get_priority_min(pol);
	
	switch(pol) {
		case SCHED_OTHER:
			policy = "SCHED_OTHER";
			break;
		case SCHED_FIFO:
			policy = "SCHED_FIFO";
			break;
		case SCHED_RR:
			policy = "SCHED_RR";
			break;
		default:
			policy = "not found";
	}
	printf("Politica de planificacion: %s\nPrioridad: %i\nValor minimo: %i\nValor maximo: %i\n", policy, p.sched_priority, min, max);
	
	return 0;
}
