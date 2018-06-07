#include "PathSearch.h"
using namespace std;


int main(/*const int nStartX, const int nStartY,
	const int nTargetX, const int nTargetY,
	const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
	int* pOutBuffer, const int nOutBufferSize*/) {

	PathSearch search = PathSearch();

	int nStartX = 0, nStartY = 0;
	int nTargetX = 3, nTargetY = 2;
	int nMapWidth = 4, nMapHeight = 3;
	int nOutBufferSize = 12;

	unsigned char pMap[] = { 1, 1, 1, 1,
							 0, 1, 0, 1,
							 0, 1, 1, 1 };

	int pOutBuffer[12];

	int length = search.FindPath(nStartX, nStartY, nTargetX, nTargetY,
		pMap, nMapWidth, nMapHeight, pOutBuffer, nOutBufferSize);

	//	returns length of shortest path
	return length;
}