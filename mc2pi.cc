#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>

bool no_neg = true;
int base = 12;
struct energy {
	int initMass = 1;
	int initLight = 1;
	
	int inlight = 1;
	int outlight = 1;
	int inenergy[9];

	int inmass = 1;
	int outmass = 1;
	int outenergy[9];

	int piField = 9;
};

int mc2_neg(int m, int c){
	int base = 10;
	return ((((c-2) + m + (c-2))) % base)* - 1;
}
int mc2_posi(int m, int c){
	int base = 10;
	return ((c-2) + m + (c-2)) % base;
}
struct energy mc2(struct energy cmc){
	struct energy ret;
	int c = cmc.initLight >= 0 ? cmc.initLight : cmc.inlight;
	int m = cmc.initMass >= 0 ? cmc.initMass : cmc.inmass;
	bool continuation = (cmc.initMass >= 0 || cmc.initMass >= 0) ? false : true;
	int fsize = 9;
	int cp = c;
	int mp = m;

	ret.initMass = -1;
	ret.initLight = -1;	
	
	if(continuation){
		cp = cmc.inlight;
		mp = cmc.inmass;
	}
	for(int j = 0; j<1; j++){
		printf("in     Energy : ");
		for(int i=0; i<fsize; i++){
			int e = mc2_neg(mp, cp);//((((cp-2) + mp + (cp-2))) % base)* - 1; 
			if(no_neg && e < 0)
				e*=-1;
						
			ret.inenergy[i] = e;
			printf("%d ", e);
			mp += m;
		}
		printf("\n");
		cp = cp == 0 ? cp-1 : cp-cp;
		ret.inmass = mp;
		ret.inlight = cp;
	}

	cp = c;
	if(continuation){
		cp = cmc.outlight;
		mp = cmc.outmass;
	}
	for(int j = 0; j<1; j++){
		mp = m;
		printf("out    Energy : ");
		for(int i=0; i<fsize; i++){
			int e = mc2_posi(mp, cp);//((cp-2) + mp + (cp-2)) % base;
			if(no_neg && e < 0)
				e*=-1;
			ret.outenergy[i] = e;
			printf("%d ", e);
			mp += m;
		}
		printf("\n");
		cp = cp == 0 ? cp+1 : cp+cp;
		ret.outmass = mp;
		ret.outlight = cp;
	}
	return ret;
}
int main(int argc, char* argv[]){
	if(argc != 3){
		printf("Provide inputs : %s mass light\n", argv[0]);
		return 1;
	}
	
	int m = std::atoi(argv[1]);
	int c = std::atoi(argv[2]);
	struct energy e;
	e.piField = 9;
	e.initMass = m;
	e.initLight = c;

	for(int i=0; i<7; i++){
		e = mc2(e);
	
		printf("Consumed :\tmass(%d) light(%d) piFrag(%d, %d, %d), (%d, %d, %d), (%d, %d, %d)\n", 
        		e.inmass, e.inlight, 
        		e.inenergy[0],
        		e.inenergy[1],
        		e.inenergy[2],
			e.inenergy[3],
        		e.inenergy[4],
        		e.inenergy[5],
			e.inenergy[6],
        		e.inenergy[7],
        		e.inenergy[8]
		);

		printf("Created :\tmass(%d) light(%d) piFrag(%d, %d, %d), (%d, %d, %d), (%d, %d, %d)\n\n", 
        		e.outlight, e.outmass,
        		e.outenergy[0],
        		e.outenergy[1],
        		e.outenergy[2],
			e.outenergy[3],
                        e.outenergy[4],
                        e.outenergy[5],
			e.outenergy[6],
                        e.outenergy[7],
                        e.outenergy[8]
		);
	}
	return 0;
}
