#include "imagecropper.h"

#include <getopt.h>

#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>

static void about()
{
    std::cout << "********************************************************\n"
              << "********************************************************\n"
              << "***                                                  ***\n"
              << "**                    ImageCropper                    **\n"
              << "**                 Hadrien Decoudras                  **\n"
              << "**                     2017-02-25                     **\n"
              << "**                    Public domain                   **\n"
              << "***                                                  ***\n"
              << "********************************************************\n"
              << "********************************************************\n\n"
              << "This software is intended to be used for cropping a set\n"
              << "of images with the same region of interest.\n"
              << "It has been designed especially for cropping stereo\n"
              << "videos.\n\n";
}

static void use()
{
    std::cout << "imagecropper <option_1...option_n>:\n"
              << "  --init-x    <integer>   Beginning offset of the crop on the x-axis.\n"
              << "  --init-y    <integer>   Beginning offset of the crop on the y-axis.\n"
              << "  --width     <integer>   Width of the crop.\n"
              << "  --height    <integer>   Height of the crop.\n"
              << "  --file      <string>    File containing image pathes\n"
              << "  --help                  Displays this menu.\n\n"
              << "  -b short option for --base-name.\n"
              << "  -x short option for --init-x.\n"
              << "  -y short option for --init-y.\n"
              << "  -w short option for --width.\n"
              << "  -h short option for --height or --help.\n"
              << "  -f short option for --file\n";
}

int main(int argc, char** argv)
{
    about();

    if(argc == 2)
    {
        if((strcmp(argv[1], "-h") == 0) || (strcmp(argv[1], "--help") == 0))
        {
            use();
            std::exit(0);
        }
        else
        {
            std::cerr << "Wrong argument!\nType imagecropper --help or -h for further details.\n";
            std::exit(-1);
        }
    }
    else if(argc < 7)
    {
        std::cerr << "Invalid number of arguments\nType imagecropper --help or -h for further details.\n";
        std::exit(-1);
    }

    static struct option long_options[] = {
                {"init-x",              required_argument, 0, 'x'},
                {"init-y",              required_argument, 0, 'y'},
                {"width",               required_argument, 0, 'w'},
                {"height",              required_argument, 0, 'h'},
                {"file",                required_argument, 0, 'f'},
                {0,                     0,                 0,  0 }
    };

    int opt = 0;
    int long_index = 0;

    int x, y, w, h;
    std::string fName;

    while((opt = getopt_long(argc, argv, "x:y:w:h:f:", long_options, &long_index)) != -1)
    {
        switch(opt)
        {
            case 'x':
            {
                x = std::stoi(std::string(optarg));
                break;
            }

            case 'y':
            {
                y = std::stoi(std::string(optarg));
                break;
            }

            case 'w':
            {
                w = std::stoi(std::string(optarg));
                break;
            }

            case 'h':
            {
                h = std::stoi(std::string(optarg));
                break;
            }

            case 'f':
            {
                fName = std::string(optarg);
                break;
            }

            default:
            {
                std::exit(-1);
            }
        }
    }

    std::ifstream ifs(fName);
    std::string path;
    std::vector<std::string> imagePathes;

    if(ifs)
    {
        while(getline(ifs, path))
        {
            imagePathes.push_back(path);       
        }
    }
    else
    {
        std::cerr << "File: " + fName + " not found!\n";
        std::exit(-1);
    }

    ifs.close();

    ImageCropper ic(cv::Rect(x, y, w, h));
    ic.createDirectory();

    for(std::size_t i = 0; i < imagePathes.size(); ++i)
    {
        ic.load(imagePathes.at(i));
        ic.save();
    }

    std::cout << ic.getCount() << " image(s) processed over " << imagePathes.size() << "\n";
    
    return 0;
}

