#include <iostream>
#include <string>
#include "Filter.h"
#include "ppm.h"
#include <boost/program_options.hpp>

using namespace image;
namespace po = boost::program_options;

int main(int argc, char* argv[]) {

	std::string arg, cfilter, imagePath;
	float aR, aG, aB, cR, cG, cB, g;

	/*	
	 *	Handling command line options
	 *	Available options:
	 *		[-h| --help]	   Display help menu
	 *		[-v| --version]	   Display version information
	 *		[-i| --image]	   User-supplied image (Required)
	 *		[-f| --filter]	   User-supplied filter (Optional)
	 *		[-p| --parameters] Filter parameters (Required)
	 *		[-l| --loglevel]   User-supplied logging level (Optional)
	 */

	// Adding all the available options
	po::options_description desc("Program options");
	desc.add_options()

		/*	
		 *	Here, the operator `()` is overloaded, so
		 *	calls to that operator add options to the 
		 *	`options_description` object.
		 */
		("help,h", "Display help menu")
		("version,v", "Display program version")
		("image,i", po::value<std::vector<std::string>>()->multitoken()->implicit_value({}, ""), "User-supplied input file(s) (Required)")
		("filter,f", po::value<std::string>()->implicit_value("")->implicit_value(""), "User-supplied filter (Optional)")
		("parameter,p", po::value<std::vector<float>>()->multitoken(), "Filter parameters (Required)")
	    ("loglevel,l", po::value<unsigned int>(), "User-supplied logging level -- 0 = All (Default), 1 = Errors only, 2 = Warnings only (Optional)");


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
		return 0;
	}
	
	// TODO: Implement multiple image processing
	if (vm.count("image") && (vm["image"].as<std::vector<std::string>>().size() >= 1)) {

		// Right now we dont support multiple images
		if (vm["image"].as<std::vector<std::string>>().size() > 1) { 
			std::cout << "Right now only 1 image at the time is supported" << std::endl;
			return 0;
		}

		imagePath = vm["image"].as<std::vector<std::string>>()[0];
		if (imagePath.find(".ppm") == std::string::npos) {
			std::cerr << "[Error] " << imagePath << " is not a valid `PPM` image" << std::endl;
			return 1;
		}

	} else {
		std::cerr << "[Error] No Image(s) given" << std::endl;
		return 1;
	}

	if (vm.count("filter")) {
		std::string filter = vm["filter"].as<std::string>();
		if (filter == "Linear" || filter == "linear" || filter == "LINEAR") {
			if (vm.count("parameter")) {
				std::vector<float> arg_vec = vm["parameter"].as<std::vector<float>>();
				if (arg_vec.size() == 6) {

					Image passedImage, newImage;

					aR = arg_vec[0];
					aG = arg_vec[1];
					aB = arg_vec[2];
					cR = arg_vec[3];
					cG = arg_vec[4];
					cB = arg_vec[5];

					FilterLinear* linear = new FilterLinear(aR, aG, aB, cR, cG, cB);

					std::cout << "[Info] Applying `Linear` filter with parameters: ";
					std::cout << aR << ", ";
					std::cout << aG << ", ";
					std::cout << aB << ", ";
					std::cout << cR << ", ";
					std::cout << cG << ", ";
					std::cout << cB << std::endl;
					newImage = *linear << passedImage;

					passedImage.load(imagePath, "ppm");
					newImage = Image(passedImage);

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

				} else {
					std::cerr << "[Error] " << filter << " filter requires 6 parameters, " << arg_vec.size() << " passed" << std::endl;
				}
			} else {
				std::cout << desc << std::endl;
			}
		} else if (filter == "Gamma" || filter == "gamma" || filter == "GAMMA") {
			if (vm.count("parameter")) {
				std::vector<float> arg_vec = vm["parameter"].as<std::vector<float>>();
				std::cout << arg_vec.size() << std::endl;
				if (arg_vec.size() == 1) {

					Image passedImage, newImage;

					g = arg_vec[0];

					FilterGamma* gamma = new FilterGamma(g);

					std::cout << "[Info] Applying `Gamma` filter with parameter: " << g << std::endl;
					newImage = *gamma << passedImage;

					passedImage.load(imagePath, "ppm");
					newImage = Image(passedImage);

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

					std::cout << "[Info] Saving image: " + imagePath << std::endl;
					newImage.save(imagePath, "ppm");

				} else {
					std::cerr << "[Error] " << filter << " filter requires 1 parameters, " << arg_vec.size() << " passed" << std::endl;
				}
			} else {
				std::cout << desc << std::endl;
			}
		} else {
			std::cerr << "[Error] " << filter << " is not supported right now" << std::endl;
		}
	} else {
		std::cout << "[Warning] No filter provided. Doing nothing..." << std::endl;
		return 0;
	}

	return 0;
}

