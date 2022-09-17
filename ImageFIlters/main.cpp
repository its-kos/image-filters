#include "ppm.h"
#include <iostream>
#include <string>
#include "Filter.h"
#include <boost/program_options.hpp>

using namespace image;
namespace po = boost::program_options;

int main(int argc, char* argv[]) {

	std::string arg, cfilter, imagePath;

	/* Handling command line options
		Available options:
			[-h| --help]	Show help menu
			[-v| --version]	Display version information
			[-i| --image]	User-supplied image
			[-f| --filter]	User-supplied filter
	*/

	// Adding all the available options
	po::options_description desc("Program options");
	desc.add_options()

		/* Here, the operator `()` is overloaded, so
		calls to that operator add options to the 
		`options_description` object */
		("help,h", "Display help menu")
		("version,v", po::value<int>(), "Display program version")
		("image,i", po::value<std::string>(&imagePath), "User-specified input image file(s)")
		("filter,f", po::value<std::string>(&cfilter), "User-specified filter");


	// Parsing the options from the command line and storing them 
	// in a `variables_map m`
	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	if ((vm.empty() == true) || (vm.count("help"))) {
		std::cout << desc << std::endl;
		return 0;
	} 

	if (vm.count("version")) {
		std::cout << "Version: Beta 1.0" << std::endl;
	}
	
	if (vm.count("image")) {
		std::cout << "Image(s): " << vm["image"].as<std::string>() << std::endl;
	} else {
		std::cerr << "Error, no Image given" << std::endl;
		return 1;
	}

	if (vm.count("filter")) {
		std::cout << "Filter(s): " << vm["filter"].as<std::string>() << std::endl;
	} else {
		std::cout << "Warning, no filter provided. Doing nothing..." << std::endl;
		return 0;
	}

	//if (argc == 2) {

	//	arg = argv[1];
	//	if (arg.find(".ppm") != std::string::npos) {
	//		// Print usage help
	//	} else {
	//		std::cerr << argv[1] << " is not a valid 'PPM' image" << std::endl;
	//		return 1;
	//	}

	//} else {

	//	int i = 1;

	//	arg = argv[1];
	//	if (arg.find(".ppm") == std::string::npos) {
	//		std::cerr << argv[1] << " is not a valid 'PPM' image" << std::endl;
	//		return 1;
	//	}

	//	do {
	//		arg = argv[++i];
	//		if (_stricmp(arg.c_str(), "-f") != 0) {
	//			// print usage help
	//		} else {
	//			arg = argv[++i];
	//			if (_stricmp(arg.c_str(), "linear") == 0) {
	//				// do the linear thing
	//			} else if (_stricmp(arg.c_str(), "gamma") == 0) {
	//				// do the gamma thing
	//			} else {
	//				std::cout << "That filter is not yet supported / Does not exist" << std::endl;
	//				return 0;
	//			}
	//		}
	//	} while (i < argc - 1)

		/*float aR, aG, aB, cR, cG, cB, g;
		

		if (lastArg.find(".ppm") == -1) {
			std::cout << "Error, no Image or wrong format (Only the ppm image format is supported)" << std::endl;
		} else {

			imagePath = lastArg;
			Image passedImage, newImage;

			passedImage.load(imagePath, "ppm");
			newImage = Image(passedImage);

			int i = 0;
			while (i < argc - 2) {

				argument = argv[++i];
				if (argument.compare("-f") != 0) {
					std::cout << "Error, expected a filter." << std::endl;
					return 0;
				}

				argument = argv[++i];
				if (argument.compare("linear") == 0) {
					if ((check(argv[++i]) == 1) && (check(argv[i + 1]) == 1) && (check(argv[i + 2]) == 1) && (check(argv[i + 3]) == 1) && (check(argv[i + 4]) == 1) && (check(argv[i + 5]) == 1)) {

						aR = stof(argv[i]);
						aG = stof(argv[i + 1]);
						aB = stof(argv[i + 2]);

						cR = stof(argv[i + 3]);
						cG = stof(argv[i + 4]);
						cB = stof(argv[i + 5]);

						FilterLinear* linear = new FilterLinear(aR, aG, aB, cR, cG, cB);

						std::cout << "Applying linear filter" << std::endl;
						newImage = *linear << passedImage;

						i += 5;

					} else {
						std::cout << "Error, expected filter parameters." << std::endl;
						return 0;
					}

				} else if (argument.compare("gamma") == 0) {

					if (check(argv[++i])) {

						g = stof(argv[i]);
						FilterGamma* gamma = new FilterGamma(g);

						std::cout << "Applying gamma filter" << std::endl;
						newImage = *gamma << passedImage;

					} else {
						std::cout << "Error, expected a filter parameter." << std::endl;
						return 0;
					}

				} else {
					std::cout << "Error, expected a filter name." << std::endl;
					return 0;
				}
			}

			const int pos = imagePath.find_last_of('\\');
			if (pos == -1) {

				const int pos = imagePath.find_last_of('/');
				if (pos == -1) {
					imagePath.insert(0, "filtered_");
				} else {
					imagePath.insert(pos, "filtered_");
				}
			} else {
				imagePath.insert(pos, "filtered_");
			}
			std::cout << "Saving image: " + imagePath << std::endl;
			newImage.save(imagePath, "ppm");
			return 0;
		}*/
}
