#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <xdmf_writer.h>

int main(int argc, char *argv[])
{
    //
    // Parse the argument list.
    //
    if (argc != 7)
    {
        fprintf(stderr, "Usage: %s nX nY nZ nXDom nYDom nZDom\n",
                argv[0]);
        exit(-1);
    }

    int nBlocks[3];
    int nodeDims[3];
    int zoneDims[3];

    sscanf(argv[1], "%d", &zoneDims[0]);
    sscanf(argv[2], "%d", &zoneDims[1]);
    sscanf(argv[3], "%d", &zoneDims[2]);
    sscanf(argv[4], "%d", &nBlocks[0]);
    sscanf(argv[5], "%d", &nBlocks[1]);
    sscanf(argv[6], "%d", &nBlocks[2]);

    nodeDims[0] = zoneDims[0] + 1;
    nodeDims[1] = zoneDims[1] + 1;
    nodeDims[2] = zoneDims[2] + 1;

    fprintf(stderr, "nodeDims=%d,%d,%d\n",
            nodeDims[0], nodeDims[1], nodeDims[2]);
    fprintf(stderr, "zoneDims=%d,%d,%d\n",
            zoneDims[0], zoneDims[1], zoneDims[2]);
    fprintf(stderr, "nBlocks=%d,%d,%d\n",
            nBlocks[0], nBlocks[1], nBlocks[2]);

    //
    // Calculate the grid dimensions.
    //
    int nzones = zoneDims[0] * zoneDims[1] * zoneDims[2];
    int nnodes = nodeDims[0] * nodeDims[1] * nodeDims[2];

    //
    // Allocate storage for the raw data.
    //
    float *coords = (float *) malloc(nnodes * 3 * sizeof(float));
    float **vars = (float **) malloc(3 * sizeof(float*));
    vars[0] = (float *) malloc(nzones * sizeof(float));
    vars[1] = (float *) malloc(nnodes * sizeof(float));
    vars[2] = (float *) malloc(nnodes * 3 * sizeof(float));

    //
    // Create the meta data.
    //
    char **varNames = (char **) malloc(sizeof(char*)*3);
    varNames[0] = (char *) malloc(strlen("height")+1);
    strcpy(varNames[0], "height");
    varNames[1] = (char *) malloc(strlen("radius")+1);
    strcpy(varNames[1], "radius");
    varNames[2] = (char *) malloc(strlen("velocity")+1);
    strcpy(varNames[2], "velocity");
    int *varTypes = (int *) malloc(sizeof(int)*3);
    varTypes[0] = XDMF_SCALAR;
    varTypes[1] = XDMF_SCALAR;
    varTypes[2] = XDMF_VECTOR;
    int *varDataTypes = (int *) malloc(sizeof(int)*3);
    varDataTypes[0] = XDMF_FLOAT;
    varDataTypes[1] = XDMF_FLOAT;
    varDataTypes[2] = XDMF_FLOAT;
    int *varCentering = (int *) malloc(sizeof(int)*3);
    varCentering[0] = XDMF_CELL_CENTER;
    varCentering[1] = XDMF_NODE_CENTER;
    varCentering[2] = XDMF_NODE_CENTER;
    int gridDims[3];
    gridDims[0] = zoneDims[0];
    gridDims[1] = zoneDims[1];
    gridDims[2] = zoneDims[2];

    //
    // Write the meta data to the XML file.
    //
    XDMFFile *xdmfFile = XdmfCreate("multi_curv3d.xmf", 1.5);

    XdmfStartMultiBlock(xdmfFile, "grid");

    int iBlock;
    int nTotalBlocks = nBlocks[0] * nBlocks[1] * nBlocks[2];
    for (iBlock = 0; iBlock < nTotalBlocks; iBlock++)
    {
        XdmfWriteCurvBlock(xdmfFile, "multi_curv3d.h5",
            "block", "XYZ", iBlock, XDMF_FLOAT, 3, varNames, varTypes,
            varCentering, varDataTypes, 3, gridDims, NULL, NULL);
    }

    XdmfEndMultiBlock(xdmfFile);

    XdmfClose(xdmfFile);

    //
    // Write the raw data to the HDF5 file.
    //
    HDFFile *hdfFile = HdfCreate("multi_curv3d.h5");

    for (iBlock = 0; iBlock < nTotalBlocks; iBlock++)
    {
        //
        // Create the raw data.
        //
        int id = iBlock;
        int iX = id / (nBlocks[1] * nBlocks[2]);
        id %= (nBlocks[1] * nBlocks[2]);
        int iY = id / nBlocks[2];
        int iZ = id % nBlocks[2];

        int ndx = 0;
        int k;
        for (k = 0; k < nodeDims[2]; k++)
        {
            int j;
            for (j = 0; j < nodeDims[1]; j++)
            {
                int i;
                for (i = 0; i < nodeDims[0]; i++)
                {
                    coords[ndx++] = (float) (i + iX * zoneDims[0]);
                    coords[ndx++] = (float) (j + iY * zoneDims[1]);
                    coords[ndx++] = (float) (k + iZ * zoneDims[2]);
                }
            }
        }

        ndx = 0;
        float *var = vars[0];
        for (k = 0; k < zoneDims[2]; k++)
        {
            int j;
            for (j = 0; j < zoneDims[1]; j++)
            {
                int i;
                for (i = 0; i < zoneDims[0]; i++)
                {
                    var[ndx++] = (float) (j + iY * zoneDims[1]) + 0.5;
                }
            }
        }

        ndx = 0;
        var = vars[1];
        for (k = 0; k < nodeDims[2]; k++)
        {
            int j;
            for (j = 0; j < nodeDims[1]; j++)
            {
                int i;
                for (i = 0; i < nodeDims[0]; i++)
                {
                    double x = (double) (i + iX * zoneDims[0]);
                    double y = (double) (j + iY * zoneDims[1]);
                    double z = (double) (k + iZ * zoneDims[2]);
                    var[ndx++] = (float) sqrt(x*x + y*y + z*z);
                }
            }
        }

        ndx = 0;
        var = vars[2];
        for (k = 0; k < nodeDims[2]; k++)
        {
            int j;
            for (j = 0; j < nodeDims[1]; j++)
            {
                int i;
                for (i = 0; i < nodeDims[0]; i++)
                {
                    var[ndx++] = (float) (i + iX * zoneDims[0]);
                    var[ndx++] = 0.;
                    var[ndx++] = 0.;
                }
            }
        }

        char varname[80];

        sprintf(varname, "XYZ%d", iBlock);
        HdfPutCoords(hdfFile, varname, XDMF_FLOAT, coords, nnodes);

        sprintf(varname, "%s%d", varNames[0], iBlock);
        HdfPutCurvVar(hdfFile, varname, varTypes[0], varCentering[0],
            varDataTypes[0], vars[0], 3, gridDims);

        sprintf(varname, "%s%d", varNames[1], iBlock);
        HdfPutCurvVar(hdfFile, varname, varTypes[1], varCentering[1],
            varDataTypes[1], vars[1], 3, gridDims);

        sprintf(varname, "%s%d", varNames[2], iBlock);
        HdfPutCurvVar(hdfFile, varname, varTypes[2], varCentering[2],
            varDataTypes[2], vars[2], 3, gridDims);
    }

    HdfClose(hdfFile);

    //
    // Free the raw data and meta data.
    //
    free(coords);
    free(vars[0]);
    free(vars[1]);
    free(vars[2]);
    free(vars);

    free(varNames[0]);
    free(varNames[1]);
    free(varNames[2]);
    free(varNames);
    free(varTypes);
    free(varDataTypes);
    free(varCentering);

    return 0; /// TODO: check if return value of 0 is correct
}
