/**
 * @file hextree-private.h
 * @description student declaration of private HexTree functions
 *              CPSC 221 PA3
 *
 *              SUBMIT THIS FILE.
 *
 *				Simply declare your function prototypes here.
 *              No other scaffolding is necessary.
 */

// begin your declarations below
struct RGBSum
{
    long r, g, b;
};

/**
 * summedAreaTable is a 2D vector of RGBSums
 * Contains the cumalative r, g, b values of any pixel from [x][y] to origin
 */
vector<vector<RGBSum>> summedAreaTable;

/**
 * Returns an RGBSum with the sums the values of two given RGBSums
 * @param a An RGBSum
 * @param b An RGBSum
 */
RGBSum addRGBASums(RGBSum a, RGBSum b);

/**
 * Returns an RGBSum with the difference the values of two given RGBSums
 * @pre a > b
 * @param a An RGBSum
 * @param b RGBSum to subtract from a
 */
RGBSum subtractRGBASums(RGBSum a, RGBSum b);

// Returns an RGBSum given an RGBAPixel
RGBSum pixelToSum(const RGBAPixel p);

void createSummedAreaTable(unsigned int imageWidth, unsigned int imageHeight, const PNG &imIn);

RGBAPixel calculateAverage(pair<unsigned int, unsigned int> ul, pair<unsigned int, unsigned int> lr);

RGBAPixel averageFromChildren(Node *A, Node *B, Node *C, Node *D, Node *E, Node *F, pair<unsigned int, unsigned int> ul, pair<unsigned int, unsigned int> lr);