//
//  resource.c
//  Mandelbrot
//
//  Created by Kevin Hoàng on 10.09.22.
//

#include "resource.h"

FILE *load_resource_file(const char *filename, const char *mode)
{
    char *resource_folder_path;

    /* If running on Window, use backslashes in resource path */
#if defined(WIN32) || defined(_WIN32)
    resource_folder_path = "..\\resources\\";
#endif
    resource_folder_path = "../resources/";

    /* Construct the full file path */
    char *path = malloc(strlen(resource_folder_path + 1) + strlen(filename + 1));
    strcat(path, resource_folder_path);
    strcat(path, filename);

    /* Load the file */
    FILE *resource_file = fopen(path, mode);

    if (!resource_file)
    {
        printf("Couldn't open file %s \n", path);
        return -1;
    }

    free(path);

    return resource_file;
}
