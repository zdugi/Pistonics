#include "AIOutput.h"
#include <cstdio>

AIIO::AIOutput::AIOutput(std::string fileName) {
	outFile = fopen(fileName.c_str(), "w");
}


AIIO::AIOutput::~AIOutput() {
	fclose(outFile);
}


void AIIO::AIOutput::addOutData(std::string data) {
	outFrame.append(data);
	outFrame.append("\n");
}


void AIIO::AIOutput::addOutData(Graphics::GameObject2D* data) {
	objs.push_back(data);
}


void AIIO::AIOutput::writeData() {
	if (outFrame.size() > 0)
		fprintf(outFile,"%s", outFrame.c_str());
	for (std::vector<Graphics::GameObject2D*>::iterator it = objs.begin();
			it != objs.end(); it++) {
		int sT = (*it)->getType();
		int x = (*it)->getShape()->getX();
		int y = (*it)->getShape()->getY();
		fprintf(outFile, "%d %d %d\n", sT, x, y);
	}
	outFrame.empty();
}
