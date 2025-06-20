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

unsigned int _imageWidth;
unsigned int _imageHeight;

/**
 * These function declarations will be flagged by VSCode for not being "member functions", but
 * they in fact are. The const keyword is necessary here. This is due to the way this file is included in
 * @file hextree.h
 */

void Render(PNG &img, const Node *nd, bool fulldepth, unsigned int maxlevel) const;
bool isLeafNode(const Node *nd) const;

// Recursive helper for Clear()
void Clear(Node*& nd);

struct RGBSum
{
    long r, g, b;
};

/**
 * summedAreaTable is a 2D vector of RGBSums
 * Contains the cumalative r, g, b values of any pixel from [x][y] to origin
 */
// vector<vector<RGBSum>> summedAreaTable;

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

// void createSummedAreaTable(unsigned int imageWidth, unsigned int imageHeight, const PNG &imIn);

// RGBAPixel calculateAverage(pair<unsigned int, unsigned int> ul, pair<unsigned int, unsigned int> lr);

RGBAPixel averageFromChildren(Node *A, Node *B, Node *C, Node *D, Node *E, Node *F, pair<unsigned int, unsigned int> ul, pair<unsigned int, unsigned int> lr);


/**
 * Recursive helper for Prune. Pushes highest prunable subtrees of nd to the stack                                                                               
 * @pre An unpruned subtree
 * @param nd the root node of a subtree
 * @param tolerance the tolerance for whether or not to prune the subtree.                                                   e
 */
/*
int getPrunableSubtrees(Node* nd, double tolerance, std::stack<Node*>* st) const;
*/

void pruneNode(Node*& nd, double tolerance);

/**
 * Recursive helper for pruneNode. Returns whether or not all leaves in the subtree are within tolerance to the avg pixel
 */
bool shouldPrune(Node* nd, double tolerance, RGBAPixel& avg) const;

/**
 * Recursive helper for flipHorizontal. Flips the current node into the correct spot relative to to the entire image
 */
void flipHorizontalHelper(Node*& nd, int globalChange);

/**
 * Recursive helper for copy. Copies the current node and attaches it to the given insertion point
 */
void copyHelper(Node* nd, Node*& insert);