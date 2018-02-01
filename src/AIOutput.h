#ifndef AIOUTPUT_H
#define AIOUTPUT_H

#include <string>
#include <cstdio>
#include <vector>
#include "GameObject2D.h"

namespace AIIO {
	class AIOutput {
		public:
			AIOutput(std::string fileName);
			~AIOutput();

			void addOutData(std::string data);
			void addOutData(Graphics::GameObject2D* data);
			void writeData();
		private:
			FILE* outFile;
			std::vector<Graphics::GameObject2D*> objs;
			int num = 0;
			std::string outFrame;
	};
};

#endif
